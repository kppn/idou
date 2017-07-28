#include <string>

#include <odb/core.hxx>

#pragma db object table("computers")
class Computer
{
public:
  Computer (const std::string& cpu, const unsigned long memory, const unsigned long storage);

  const std::string cpu () const;
  const unsigned long memory () const;
  const unsigned long storage () const;
  void cpu (std::string& cpu);
  void memory (unsigned long memory);
  void storage (unsigned long storage);
private:
  Computer ();

  friend class odb::access;

  #pragma db id auto
  unsigned long id_;
  std::string cpu_;
  unsigned long memory_;
  unsigned long storage_;

};
