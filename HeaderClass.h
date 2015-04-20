#ifndef HEADERCLASS_H
#define HEADERCLASS_H

template <typename ElfN_Ehdr>
class HeaderClass
{
protected :
  size_t headerSize;
  int bitInfo;
  ElfN_Ehdr* header;

public :
  QList<ElfDataType> headerMemberList;
  //Program Header Information
  unsigned long prgHeaderOffset;
  uint16_t prgHeaderEntSize;
  uint16_t prgHeaderNumber;

  //Section Header Information
  unsigned long seHeaderOffset;
  uint16_t seHeaderEntSize;
  uint16_t seHeaderNumber;

  HeaderClass(int _bitInfo);
  //~HeaderClass();
  virtual void SetHeader(char* buffer) = 0;
  virtual void PrintHeader() = 0;
  unsigned long CalcurateOffset(void* member, void* header);

};
template<typename ElfN_Ehdr>
HeaderClass<ElfN_Ehdr>::HeaderClass(int _bitInfo)
{
    bitInfo = _bitInfo;
}
template<typename ElfN_Ehdr>
unsigned long HeaderClass<ElfN_Ehdr>::CalcurateOffset(void* member, void* header)
{
    return (unsigned long) ((unsigned char*)member - (unsigned char*) header);
}

#endif // HEADERCLASS_H
