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
    //uint16_t seHeaderEntSize;
    uint16_t seHeaderNumber;
  public :
    ElfSeHeaderClass();
    ~ElfSeHeaderClass();
    QString GetTypeString(u_int32_t type);
    void SetHeader(char* buffer,unsigned long e_shoff, uint16_t e_shentsize, uint16_t e_shnum);
    void ClearHeaderMemberList();
    void SetHeaderMemberList();
    ElfN_Shdr* GetHeader();
    size_t GetTotalSize();
    size_t GetOffset();
    QList<QString> s_typeStringList;
    QList< QList<ElfDataType> > s_list;
};
template<typename ElfN_Shdr>
ElfN_Shdr* ElfSeHeaderClass<ElfN_Shdr>::GetHeader()
{
    return sHeader;
}

template<typename ElfN_Shdr>
size_t ElfSeHeaderClass<ElfN_Shdr>::GetTotalSize()
{
    return totalHeaderSize;
}

template<typename ElfN_Shdr>
size_t ElfSeHeaderClass<ElfN_Shdr>::GetOffset()
{
    return seHeaderOffset;
}

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
  //seHeaderEntSize = e_shentsize;
  seHeaderNumber = e_shnum;
}
template<typename ElfN_Shdr>
void ElfSeHeaderClass<ElfN_Shdr>::ClearHeaderMemberList()
{
    s_typeStringList.clear();
    s_list.clear();
}

template<typename ElfN_Shdr>
void ElfSeHeaderClass<ElfN_Shdr>::SetHeaderMemberList()
{

    // Set Data : 1.Offset  2.Name  3.Value  4.data size 5.bitInfo

    ElfN_Shdr* point = NULL;
    QString s_typeStr;
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
        QString str = GetTypeString(point->sh_type);
        s_typeStr.sprintf("[%d] : %s", i, str.toStdString().c_str());
        s_typeStringList.append(s_typeStr);
        s_list.append(this->headerMemberList);

        this->headerMemberList.clear();
    }
  //dumpcode((unsigned char*)header, totalHeaderSize);
}
template<typename ElfN_Shdr>
QString ElfSeHeaderClass<ElfN_Shdr>::GetTypeString(u_int32_t type)
{
    QString str;
    switch(type)
    {
        case  SHT_NULL :          /* Section header table entry unused */
            str = "NULL";
            break;
        case  SHT_PROGBITS :     /* Program data */
            str = "PROGBITS";
            break;
        case  SHT_SYMTAB :       /* Symbol table */
            str = "SYMTAB";
            break;
        case  SHT_STRTAB :      /* String table */
            str = "STRTAB";
            break;
        case  SHT_RELA  :        /* Relocation entries with addends */
            str = "RELA";
            break;
        case  SHT_HASH :         /* Symbol hash table */
            str = "HASH";
            break;
        case  SHT_DYNAMIC :      /* Dynamic linking information */
            str = "DYNAMIC";
            break;
        case  SHT_NOTE :         /* Notes */
            str = "NOTE";
            break;
        case  SHT_NOBITS :        /* Program space with no data (bss) */
            str = "NOBITS";
            break;
        case  SHT_REL :          /* Relocation entries, no addends */
            str = "REL";
            break;
        case  SHT_SHLIB :        /* Reserved */
            str = "SHLIB";
            break;
        case  SHT_DYNSYM :       /* Dynamic linker symbol table */
            str = "DYNSYM";
            break;
        case  SHT_INIT_ARRAY :   /* Array of constructors */
            str = "INIT_ARRAY";
            break;
        case  SHT_FINI_ARRAY :   /* Array of destructors */
            str = "FINI_ARRAY";
            break;
        case  SHT_PREINIT_ARRAY :/* Array of pre-constructors */
            str = "PREINIT_ARRAY";
            break;
        case  SHT_GROUP :        /*  group */
            str = "GROUP";
            break;
        case  SHT_SYMTAB_SHNDX : /* Extended section indeces */
            str = "SYMTAB_SHNDX";
            break;
        case  SHT_NUM :          /* Number of defined types.  */
            str = "NUM";
            break;
        case  SHT_LOOS :         /* Start OS-specific.  */
            str = "LOOS";
            break;
        case  SHT_GNU_ATTRIBUTES :/* Object attributes.  */
            str = "GNU_ATTRIBUTES";
            break;
        case  SHT_GNU_HASH :     /* GNU-style hash table.  */
            str = "GNU_HASH";
            break;
        case  SHT_GNU_LIBLIST :  /* Prelink library list */
            str = "GNU_LIBLIST";
            break;
        case  SHT_CHECKSUM :     /* Checksum for DSO content.  */
            str = "CHECKSUM";
            break;
        case  SHT_SUNW_move :   /* Sun-specific low bound.  */
            str = "SUNW_move";
            break;
        case  SHT_SUNW_COMDAT :
            str = "SUNW_COMDAT";
            break;
        case  SHT_SUNW_syminfo :
            str = "SUNW_syminfo";
            break;
        case  SHT_GNU_verdef :   /* Version definition section.  */
            str = "GNU_verdef";
            break;
        case  SHT_GNU_verneed :  /* Version needs section.  */
            str = "GNU_verneed";
            break;
        case  SHT_GNU_versym :   /* Version symbol table.  */
            str = "GNU_versym";
            break;
        case  SHT_LOPROC :       /* Start of processor-specific */
            str = "LOPROC";
            break;
        case  SHT_HIPROC :       /* End of processor-specific */
            str = "IPROC";
            break;
        case  SHT_LOUSER :       /* Start of application-specific */
            str = "LOUSER";
            break;
        case  SHT_HIUSER :       /* End of application-specific */
            str = "HIUSER";
            break;
        default :
            str = "UNKNOWN";
            break;
    }
    return str;
}

#endif // ELFSEHEADERCLASS_H
