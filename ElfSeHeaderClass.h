#ifndef ELFSEHEADERCLASS_H
#define ELFSEHEADERCLASS_H

#include <elf.h>
#include <QList>
#include "ElfDataType.h"
#include "HeaderClass.h"

using namespace std;
template <typename ElfN_Shdr>
class ElfSeHeaderClass : public HeaderClass<ElfN_Shdr>
{
  private :
    ElfDataType sh_name;
    ElfDataType sh_type;
    ElfDataType sh_flags;
    ElfDataType sh_addr;
    ElfDataType sh_offset;
    ElfDataType sh_size;
    ElfDataType sh_link;
    ElfDataType sh_info;
    ElfDataType sh_addralign;
    ElfDataType sh_entsize;


    ElfN_Shdr* sHeader;
    size_t totalHeaderSize;
    unsigned long seHeaderOffset;
    uint16_t seHeaderEntSize;
    uint16_t seHeaderNumber;
  public :
    ElfSeHeaderClass();
    ~ElfSeHeaderClass();
    void SetHeader(char* buffer,unsigned long e_shoff, uint16_t e_shentsize, uint16_t e_shnum);
    void PrintHeader();
};

template<typename ElfN_Shdr>
ElfSeHeaderClass<ElfN_Shdr>::ElfSeHeaderClass()
{
}

template<typename ElfN_Shdr>
ElfSeHeaderClass<ElfN_Shdr>::~ElfSeHeaderClass()
{
}

template<typename ElfN_Shdr>
void ElfSeHeaderClass<ElfN_Shdr>::SetHeader(char* buffer, unsigned long e_shoff, uint16_t e_shentsize, uint16_t e_shnum)
{
  this->baseOffset = buffer;
  //Section 헤더를 가르킨다.

  sHeader = (ElfN_Shdr*)&buffer[e_shoff];
  totalHeaderSize = e_shentsize * e_shnum;
  seHeaderOffset = e_shoff;
  seHeaderEntSize = e_shentsize;
  seHeaderNumber = e_shnum;
}

template<typename ElfN_Shdr>
void ElfSeHeaderClass<ElfN_Shdr>::PrintHeader()
{

    // Set Data : 1.Offset  2.Name  3.Value  4.data size 5.bitInfo

    ElfN_Shdr* point = NULL;
    for(int i=0; i<seHeaderNumber; i++)
    {

        point = sHeader + i;
        sh_name.SetData(this->CalcurateOffset(&(point->sh_name) ,this->baseOffset), "sh_name", (unsigned long)point->sh_name, sizeof(point->sh_name));
        sh_type.SetData(this->CalcurateOffset(&(point->sh_type) ,this->baseOffset), "sh_type", (unsigned long)point->sh_type, sizeof(point->sh_type));
        sh_flags.SetData(this->CalcurateOffset(&(point->sh_flags) ,this->baseOffset), "sh_flags", (unsigned long)point->sh_flags, sizeof(point->sh_flags));
        sh_addr.SetData(this->CalcurateOffset(&(point->sh_addr) ,this->baseOffset), "sh_addr", (unsigned long)point->sh_addr, sizeof(point->sh_addr));
        sh_offset.SetData(this->CalcurateOffset(&(point->sh_offset) ,this->baseOffset), "sh_offset", (unsigned long)point->sh_offset, sizeof(point->sh_offset));
        sh_size.SetData(this->CalcurateOffset(&(point->sh_size) ,this->baseOffset), "sh_size", (unsigned long)point->sh_size, sizeof(point->sh_size));
        sh_link.SetData(this->CalcurateOffset(&(point->sh_link) ,this->baseOffset), "sh_link", (unsigned long)point->sh_link, sizeof(point->sh_link));
        sh_info.SetData(this->CalcurateOffset(&(point->sh_info) ,this->baseOffset), "sh_info", (unsigned long)point->sh_info, sizeof(point->sh_info));
        sh_addralign.SetData(this->CalcurateOffset(&(point->sh_addralign) ,this->baseOffset), "sh_addralign", (unsigned long)point->sh_addralign, sizeof(point->sh_addralign));
        sh_entsize.SetData(this->CalcurateOffset(&(point->sh_entsize) ,this->baseOffset), "sh_entsize", (unsigned long)point->sh_entsize, sizeof(point->sh_entsize));
        this->headerMemberList.append(sh_name);
        this->headerMemberList.append(sh_type);
        this->headerMemberList.append(sh_flags);
        this->headerMemberList.append(sh_addr);
        this->headerMemberList.append(sh_offset);
        this->headerMemberList.append(sh_size);
        this->headerMemberList.append(sh_link);
        this->headerMemberList.append(sh_info);
        this->headerMemberList.append(sh_addralign);
        this->headerMemberList.append(sh_entsize);
    }
  //dumpcode((unsigned char*)header, totalHeaderSize);
}

#endif // ELFSEHEADERCLASS_H
