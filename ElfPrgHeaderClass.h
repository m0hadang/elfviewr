#ifndef ELFPRGHEADERCLASS_H
#define ELFPRGHEADERCLASS_H

#include <elf.h>
#include <QList>
#include <QVector>
#include "ElfDataType.h"
#include "HeaderClass.h"
using namespace std;

template <typename ElfN_Phdr>
class ElfPrgHeaderClass : public HeaderClass<ElfN_Phdr>
{
  private :

    ElfDataType p_type;
    ElfDataType p_offset;
    ElfDataType p_vaddr;
    ElfDataType p_paddr;
    ElfDataType p_filesz;
    ElfDataType p_memsz;
    ElfDataType p_flags;
    ElfDataType p_align;

    ElfN_Phdr* pHeader;

    //ElfN_Phdr* header;
    size_t totalHeaderSize;
    unsigned long prgHeaderOffset;
    uint16_t prgHeaderEntSize;



  public :
    //QList<ElfDataType> prgHeaderMemberList;
    ElfPrgHeaderClass();
    ~ElfPrgHeaderClass();
    void SetHeader(char* buffer,unsigned long e_phoff, uint16_t e_phentsize, uint16_t e_phnum);
    void SetHeaderMemberList();
    uint16_t prgHeaderNumber;
    QList<QString> p_typeStringList;
    QList< QList<ElfDataType> > p_list;
};

template<typename ElfN_Phdr>
ElfPrgHeaderClass<ElfN_Phdr>::ElfPrgHeaderClass()
{
}

template<typename ElfN_Phdr>
ElfPrgHeaderClass<ElfN_Phdr>::~ElfPrgHeaderClass()
{
}

template<typename ElfN_Phdr>
void ElfPrgHeaderClass<ElfN_Phdr>::SetHeader(char* buffer, unsigned long e_phoff, uint16_t e_phentsize, uint16_t e_phnum)
{
   this->baseOffset = buffer;

  //Program 헤더를 가르킨다.
  pHeader = (ElfN_Phdr*)&buffer[e_phoff];
  totalHeaderSize = e_phentsize * e_phnum;
  prgHeaderOffset = e_phoff;
  prgHeaderEntSize = e_phentsize;
  prgHeaderNumber = e_phnum;
}

template<typename ElfN_Phdr>
void ElfPrgHeaderClass<ElfN_Phdr>::SetHeaderMemberList()
{
  // Set Data : 1.Offset  2.Name  3.Value  4.data size 5.bitInfo

  ElfN_Phdr* point = NULL;
  QString p_typeStr;
  for(int i=0; i<prgHeaderNumber; i++)
  {
    point = pHeader + i;
    //cout <<"  -["<<i<<"]"<<endl;
    p_type.SetData(this->CalcurateOffset(&(point->p_type) ,this->baseOffset), "p_type", (unsigned long)point->p_type, sizeof(point->p_type));
    p_offset.SetData(this->CalcurateOffset(&(point->p_offset) ,this->baseOffset), "p_offset", (unsigned long)point->p_offset, sizeof(point->p_offset));
    p_vaddr.SetData(this->CalcurateOffset(&(point->p_vaddr) ,this->baseOffset), "p_vaddr", (unsigned long)point->p_vaddr, sizeof(point->p_vaddr));
    p_paddr.SetData(this->CalcurateOffset(&(point->p_paddr) ,this->baseOffset), "p_paddr", (unsigned long)point->p_paddr, sizeof(point->p_paddr));
    p_filesz.SetData(this->CalcurateOffset(&(point->p_filesz) ,this->baseOffset), "p_filesz", (unsigned long)point->p_filesz, sizeof(point->p_filesz));
    p_memsz.SetData(this->CalcurateOffset(&(point->p_memsz) ,this->baseOffset), "p_memsz", (unsigned long)point->p_memsz, sizeof(point->p_memsz));
    p_flags.SetData(this->CalcurateOffset(&(point->p_flags) ,this->baseOffset), "p_flags", (unsigned long)point->p_flags, sizeof(point->p_flags));
    p_align.SetData(this->CalcurateOffset(&(point->p_align) ,this->baseOffset), "p_align", (unsigned long)point->p_align, sizeof(point->p_align));

    this->headerMemberList.append(p_type);
    this->headerMemberList.append(p_offset);
    this->headerMemberList.append(p_vaddr);
    this->headerMemberList.append(p_paddr);
    this->headerMemberList.append(p_filesz);
    this->headerMemberList.append(p_memsz);
    this->headerMemberList.append(p_flags);
    this->headerMemberList.append(p_align);

    p_typeStr.sprintf("[%d] : %x", i, point->p_type);
    p_typeStringList.append(p_typeStr);
    p_list.append(this->headerMemberList);

    this->headerMemberList.clear();
  }

  //dumpcode((unsigned char*)header, totalHeaderSize);
}

#endif // ELFPRGHEADERCLASS_H
