all:
	../gen_class.rb computer.def
	odb --std c++11 -d mysql --generate-query --generate-schema --default-pointer std::shared_ptr  computer.hxx
	g++ -std=c++11 -c computer-odb.cxx

clean:
	rm -f *.hxx
	rm -f *.cxx
	rm -f *odb*
	rm -f *.sql

