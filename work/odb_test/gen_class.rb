#!/bin/env ruby

require 'pathname'

filename = ARGV[0]
header_filename = filename.sub(/.def$/, '.hxx')
impl_filename = filename.sub(/.def$/, '.cxx')

fields = []
includes = nil
table_name = nil
class_name = nil
File.open(filename, 'r') do |f|
  includes = f.gets.chomp.split[1..-1].map{|i| "#include <#{i}>\n"}
  class_name, table_name = f.gets.chomp.split
  while l = f.gets
    fs = l.chomp.strip.split
    field_name = fs.pop
    if field_name.end_with? '@'
      field_name = field_name[0..-2]
      setter_reference = false
    else
      field_name = field_name
      setter_reference = true
    end
    field_type = fs.join(' ')
    fields << {type: field_type, name: field_name, setter_reference: setter_reference}
  end
end

constructor_args = fields.map{|f|
  ref = f[:setter_reference] ? '&' : ''
  "const #{f[:type]}#{ref} #{f[:name]}"
}.join(', ')

constructor_setter = fields.map{|f|
  f[:name]}.map{|name| "#{name}_(#{name})"
}.join(', ')

fields_reader = fields.map{|f|
  decl = "const #{f[:type]} #{f[:name]} () const"
  {
    decl: "#{decl};",
    impl: "#{decl} {return #{f[:name]}_;}"
  }
}

fields_writer = fields.map{|f|
  ref = f[:setter_reference] ? '&' : ''
  decl = "void #{f[:name]} (#{f[:type]}#{ref} #{f[:name]})"
  {
    decl: "#{decl};",
    impl: "#{decl} {#{f[:name]}_ = #{f[:name]};}",
  }
}

p_fields = 
  fields.map{|f| "  #{f[:type]} #{f[:name]}_;\n" }


# c++ class definition
File.open(header_filename, 'w') do |f|
  f.puts <<~EOL
    #{includes.join}
    #include <odb/core.hxx>
    
    #pragma db object table("#{table_name}")
    class #{class_name}
    {
    public:
      #{class_name} (#{constructor_args});
    
      #{fields_reader.map{|f|f[:decl]}.join("\n  ")}
      #{fields_writer.map{|f|f[:decl]}.join("\n  ")}
    private:
      #{class_name} ();
    
      friend class odb::access;
    
      #pragma db id auto
      unsigned long id_;
    #{p_fields.join}
    };
  EOL
end

# c++ class implementation
File.open(impl_filename, 'w') do |f|
  f.puts <<~EOL
    #{includes.join}
    #include <odb/core.hxx>
    
    #pragma db object table("#{table_name}")
    class #{class_name}
    {
    public:
      #{class_name} (#{constructor_args});
    
      #{fields_reader.map{|f|f[:impl]}.join("\n  ")}
      #{fields_writer.map{|f|f[:impl]}.join("\n  ")}
    
    private:
      #{class_name} () {}
    
      friend class odb::access;
    
      #pragma db id auto
      unsigned long id_;
    #{p_fields.join}
    }
  EOL
end


