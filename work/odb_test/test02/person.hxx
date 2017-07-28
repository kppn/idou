#include <string>

#include <odb/core.hxx>

#pragma db object table("people")
class Person
{
public:
  Person (const std::string& name, const unsigned short age)
  : name_(name), age_(age)
  {}

  const std::string name () const {return name_;}
  const unsigned short age () const {return age_;}

  void name (std::string& name) {name_ = name;}
  void age (unsigned short age) {age_ = age;}


private:
  Person () {}

  friend class odb::access;

  #pragma db id auto
  unsigned long id_;
  std::string name_;
  unsigned short age_;

};
