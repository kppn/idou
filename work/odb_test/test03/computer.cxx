#include <string>

#include <odb/core.hxx>

#pragma db object table("computers")
class Computer
{
public:
  Computer (const std::string& cpu, const unsigned long memory, const unsigned long storage);

  const std::string cpu () const {return cpu_;}
  const unsigned long memory () const {return memory_;}
  const unsigned long storage () const {return storage_;}
  void cpu (std::string& cpu) {cpu_ = cpu;}
  void memory (unsigned long memory) {memory_ = memory;}
  void storage (unsigned long storage) {storage_ = storage;}

private:
  Computer () {}

  friend class odb::access;

  #pragma db id auto
  unsigned long id_;
  std::string cpu_;
  unsigned long memory_;
  unsigned long storage_;

}
