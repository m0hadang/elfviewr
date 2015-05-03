#ifndef HEADERCLASS_H
#define HEADERCLASS_H
#include <QList>
template <typename ElfN_Hdr>
class HeaderClass
{
protected :
  size_t headerSize;
  void* baseOffset;

public :
  QList<ElfDataType> headerMemberList;

  HeaderClass();
  //~HeaderClass();
  void SetHeader(char* buffer);
  void SetHeader(char* buffer, unsigned long e_phoff, uint16_t e_phentsize, uint16_t e_phnum);
  /*
  virtual void SetHeader(char* buffer) = 0;
  virtual void SetHeader(char* buffer, unsigned long e_phoff, uint16_t e_phentsize, uint16_t e_phnum) = 0;
  */
  virtual void PrintHeader() = 0;
  unsigned long CalcurateOffset(void* member, void* header);

};


template<typename ElfN_Hdr>
HeaderClass<ElfN_Hdr>::HeaderClass()
{

}
template<typename ElfN_Hdr>
unsigned long HeaderClass<ElfN_Hdr>::CalcurateOffset(void* member, void* header)
{
    return (unsigned long) ((unsigned char*)member - (unsigned char*) header);
}

#endif // HEADERCLASS_H
