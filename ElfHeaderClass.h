#ifndef ELFHEADERCLASS_H
#define ELFHEADERCLASS_H

#include <stdio.h>
#include <iostream>
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
    //ElfN_Ehdr* header;

    ElfHeaderClass(int bit);
    ~ElfHeaderClass();
    void SetHeader(char* buffer);
    void PrintHeader();
    //unsigned long CalcurateOffset(void* member, void* header);
};


template<typename ElfN_Ehdr>
ElfHeaderClass<ElfN_Ehdr>::ElfHeaderClass(int bit) : HeaderClass<ElfN_Ehdr>(bit)
{

  //header = new ElfN_Ehdr;
  this->bitInfo = bit;
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
    this->header = (ElfN_Ehdr *)buffer;

    //프로그램 헤더 정보값 초기화
    prgHeaderOffset = this->header->e_phoff;
    prgHeaderEntSize = this->header->e_phentsize;
    prgHeaderNumber = this->header->e_phnum;
    //섹션 헤더 정보값 초기화
    seHeaderOffset = this->header->e_shoff;
    seHeaderEntSize = this->header->e_shentsize;
    seHeaderNumber = this->header->e_shnum;
}

template<typename ElfN_Ehdr>
void ElfHeaderClass<ElfN_Ehdr>::PrintHeader()
{
  //cout << "ELF_HEADER" << endl;
  //cout << hex << " -HeaderSize : " << headerSize << endl;

  // Set Data : 1.Offset  2.Name  3.Value  4.data size 5.bitInfo
  e_ident.SetData(this->CalcurateOffset(&(this->header->e_ident) ,this->header) , "e_ident", (unsigned long)this->header->e_ident, EI_NIDENT, this->bitInfo );
  e_type.SetData(this->CalcurateOffset(&(this->header->e_type) ,this->header), "e_type", (unsigned long)this->header->e_type, sizeof(this->header->e_type), this->bitInfo );
  e_machine.SetData(this->CalcurateOffset(&(this->header->e_machine) ,this->header), "e_machine", (unsigned long)this->header->e_machine, sizeof(this->header->e_machine), this->bitInfo );
  e_version.SetData(this->CalcurateOffset(&(this->header->e_version) ,this->header), "e_version", (unsigned long)this->header->e_version, sizeof(this->header->e_version), this->bitInfo );
  e_entry.SetData(this->CalcurateOffset(&(this->header->e_entry) ,this->header), "e_entry", (unsigned long)this->header->e_entry, sizeof(this->header->e_entry), this->bitInfo );
  e_phoff.SetData(this->CalcurateOffset(&(this->header->e_phoff) ,this->header), "e_phoff", (unsigned long)this->header->e_phoff, sizeof(this->header->e_phoff), this->bitInfo );
  e_shoff.SetData(this->CalcurateOffset(&(this->header->e_shoff) ,this->header), "e_shoff", (unsigned long)this->header->e_shoff, sizeof(this->header->e_shoff), this->bitInfo );
  e_flags.SetData(this->CalcurateOffset(&(this->header->e_flags) ,this->header), "e_flags", (unsigned long)this->header->e_flags, sizeof(this->header->e_flags), this->bitInfo );
  e_ehsize.SetData(this->CalcurateOffset(&(this->header->e_ehsize) ,this->header), "e_ehsize", (unsigned long)this->header->e_ehsize, sizeof(this->header->e_ehsize), this->bitInfo );
  e_phentsize.SetData(this->CalcurateOffset(&(this->header->e_phentsize) ,this->header), "e_phentsize", (unsigned long)this->header->e_phentsize, sizeof(this->header->e_phentsize), this->bitInfo );
  e_phnum.SetData(this->CalcurateOffset(&(this->header->e_phnum) ,this->header) , "e_phnum", (unsigned long)this->header->e_phnum, sizeof(this->header->e_phnum), this->bitInfo );
  e_shentsize.SetData(this->CalcurateOffset(&(this->header->e_shentsize) , this->header), "e_shentsize", (unsigned long)this->header->e_shentsize, sizeof(this->header->e_shentsize), this->bitInfo );
  e_shnum.SetData(this->CalcurateOffset(&(this->header->e_shnum) ,this->header), "e_shnum", (unsigned long)this->header->e_shnum, sizeof(this->header->e_shnum), this->bitInfo );
  e_shstrndx.SetData(this->CalcurateOffset(&(this->header->e_shstrndx) ,this->header), "e_shstrndx", (unsigned long)this->header->e_shstrndx, sizeof(this->header->e_shstrndx), this->bitInfo );

  headerMemberList.append(e_ident);
  headerMemberList.append(e_type);
  headerMemberList.append(e_machine);
  headerMemberList.append(e_version);
  headerMemberList.append(e_phoff);
  headerMemberList.append(e_shoff);
  headerMemberList.append(e_ehsize);
  headerMemberList.append(e_phentsize);
  headerMemberList.append(e_phnum);
  headerMemberList.append(e_shentsize);
  headerMemberList.append(e_shnum);
  headerMemberList.append(e_shstrndx);
}
/*
template<typename ElfN_Ehdr>
unsigned long ElfHeaderClass<ElfN_Ehdr>::CalcurateOffset(void* member, void* header)
{
    return (unsigned long) ((unsigned char*)member - (unsigned char*) header);
}
*/
#endif // ELFHEADERCLASS_H
