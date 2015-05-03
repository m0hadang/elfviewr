#ifndef ELFHEADERCLASS_H
#define ELFHEADERCLASS_H

#include <elf.h>
#include <QList>
#include "ElfDataType.h"
#include "HeaderClass.h"
using namespace std;

template <typename ElfN_Ehdr>
class ElfHeaderClass : public HeaderClass<ElfN_Ehdr>
{
  private :
    ElfDataType e_ident;
    ElfDataType e_machine;
    ElfDataType e_type;
    ElfDataType e_version;
    ElfDataType e_entry;
    ElfDataType e_phoff;
    ElfDataType e_shoff;
    ElfDataType e_flags;
    ElfDataType e_ehsize;
    ElfDataType e_phentsize;
    ElfDataType e_phnum;
    ElfDataType e_shentsize;
    ElfDataType e_shnum;
    ElfDataType e_shstrndx;
    ElfN_Ehdr* eHeader;


  public :

    //Program Header Information
    unsigned long prgHeaderOffset;
    uint16_t prgHeaderEntSize;
    uint16_t prgHeaderNumber;

    //Section Header Information
    unsigned long seHeaderOffset;
    uint16_t seHeaderEntSize;
    uint16_t seHeaderNumber;



    ElfHeaderClass();
    ~ElfHeaderClass();
    void SetHeader(char* buffer);
    void PrintHeader();
    //unsigned long CalcurateOffset(void* member, void* header);
};


template<typename ElfN_Ehdr>
ElfHeaderClass<ElfN_Ehdr>::ElfHeaderClass() : HeaderClass<ElfN_Ehdr>()
{
  this->headerSize = sizeof(ElfN_Ehdr);
}

template<typename ElfN_Ehdr>
ElfHeaderClass<ElfN_Ehdr>::~ElfHeaderClass()
{
    //delete header;
}

template<typename ElfN_Ehdr>
void ElfHeaderClass<ElfN_Ehdr>::SetHeader(char* buffer)
{
    //memcpy((char*)header, (char*)buffer, headerSize);

    this->baseOffset = buffer;

    eHeader = (ElfN_Ehdr *)buffer;
    //프로그램 헤더 정보값 초기화
    prgHeaderOffset = this->eHeader->e_phoff;
    prgHeaderEntSize = this->eHeader->e_phentsize;
    prgHeaderNumber = this->eHeader->e_phnum;
    //섹션 헤더 정보값 초기화
    seHeaderOffset = this->eHeader->e_shoff;
    seHeaderEntSize = this->eHeader->e_shentsize;
    seHeaderNumber = this->eHeader->e_shnum;
}

template<typename ElfN_Ehdr>
void ElfHeaderClass<ElfN_Ehdr>::PrintHeader()
{
  //cout << "ELF_HEADER" << endl;
  //cout << hex << " -HeaderSize : " << headerSize << endl;

  // Set Data : 1.Offset  2.Name  3.Value  4.data size 5.bitInfo
  e_ident.SetData(this->CalcurateOffset(&(this->eHeader->e_ident) ,this->baseOffset) , "e_ident", (unsigned long)this->eHeader->e_ident, EI_NIDENT);
  e_type.SetData(this->CalcurateOffset(&(this->eHeader->e_type) ,this->baseOffset), "e_type", (unsigned long)this->eHeader->e_type, sizeof(this->eHeader->e_type));
  e_machine.SetData(this->CalcurateOffset(&(this->eHeader->e_machine) ,this->baseOffset), "e_machine", (unsigned long)this->eHeader->e_machine, sizeof(this->eHeader->e_machine));
  e_version.SetData(this->CalcurateOffset(&(this->eHeader->e_version) ,this->baseOffset), "e_version", (unsigned long)this->eHeader->e_version, sizeof(this->eHeader->e_version));
  e_entry.SetData(this->CalcurateOffset(&(this->eHeader->e_entry) ,this->baseOffset), "e_entry", (unsigned long)this->eHeader->e_entry, sizeof(this->eHeader->e_entry));
  e_phoff.SetData(this->CalcurateOffset(&(this->eHeader->e_phoff) ,this->baseOffset), "e_phoff", (unsigned long)this->eHeader->e_phoff, sizeof(this->eHeader->e_phoff));
  e_shoff.SetData(this->CalcurateOffset(&(this->eHeader->e_shoff) ,this->baseOffset), "e_shoff", (unsigned long)this->eHeader->e_shoff, sizeof(this->eHeader->e_shoff));
  e_flags.SetData(this->CalcurateOffset(&(this->eHeader->e_flags) ,this->baseOffset), "e_flags", (unsigned long)this->eHeader->e_flags, sizeof(this->eHeader->e_flags));
  e_ehsize.SetData(this->CalcurateOffset(&(this->eHeader->e_ehsize) ,this->baseOffset), "e_ehsize", (unsigned long)this->eHeader->e_ehsize, sizeof(this->eHeader->e_ehsize));
  e_phentsize.SetData(this->CalcurateOffset(&(this->eHeader->e_phentsize) ,this->baseOffset), "e_phentsize", (unsigned long)this->eHeader->e_phentsize, sizeof(this->eHeader->e_phentsize));
  e_phnum.SetData(this->CalcurateOffset(&(this->eHeader->e_phnum) ,this->baseOffset) , "e_phnum", (unsigned long)this->eHeader->e_phnum, sizeof(this->eHeader->e_phnum));
  e_shentsize.SetData(this->CalcurateOffset(&(this->eHeader->e_shentsize) , this->baseOffset), "e_shentsize", (unsigned long)this->eHeader->e_shentsize, sizeof(this->eHeader->e_shentsize));
  e_shnum.SetData(this->CalcurateOffset(&(this->eHeader->e_shnum) ,this->baseOffset), "e_shnum", (unsigned long)this->eHeader->e_shnum, sizeof(this->eHeader->e_shnum));
  e_shstrndx.SetData(this->CalcurateOffset(&(this->eHeader->e_shstrndx) ,this->baseOffset), "e_shstrndx", (unsigned long)this->eHeader->e_shstrndx, sizeof(this->eHeader->e_shstrndx));

  this->headerMemberList.append(e_ident);
  this->headerMemberList.append(e_type);
  this->headerMemberList.append(e_machine);
  this->headerMemberList.append(e_version);
  this->headerMemberList.append(e_entry);
  this->headerMemberList.append(e_phoff);
  this->headerMemberList.append(e_shoff);
  this->headerMemberList.append(e_flags);
  this->headerMemberList.append(e_ehsize);
  this->headerMemberList.append(e_phentsize);
  this->headerMemberList.append(e_phnum);
  this->headerMemberList.append(e_shentsize);
  this->headerMemberList.append(e_shnum);
  this->headerMemberList.append(e_shstrndx);
}
/*
template<typename ElfN_Ehdr>
unsigned long ElfHeaderClass<ElfN_Ehdr>::CalcurateOffset(void* member, void* header)
{
    return (unsigned long) ((unsigned char*)member - (unsigned char*) header);
}
*/
#endif // ELFHEADERCLASS_H
