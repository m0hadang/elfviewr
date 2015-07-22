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
    //uint16_t prgHeaderEntSize;



  public :
    //QList<ElfDataType> prgHeaderMemberList;
    ElfPrgHeaderClass();
    ~ElfPrgHeaderClass();
    QString GetTypeString(u_int32_t type);
    void SetHeader(char* buffer,unsigned long e_phoff, uint16_t e_phentsize, uint16_t e_phnum);
    void ClearHeaderMemberList();
    void SetHeaderMemberList();
    uint16_t prgHeaderNumber;
    QList<QString> p_typeStringList;
    QList< QList<ElfDataType> > p_list;
    ElfN_Phdr* GetHeader();
    size_t GetTotalSize();
    size_t GetOffset();
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
ElfN_Phdr* ElfPrgHeaderClass<ElfN_Phdr>::GetHeader()
{
    return pHeader;
}

template<typename ElfN_Phdr>
size_t ElfPrgHeaderClass<ElfN_Phdr>::GetTotalSize()
{
    return totalHeaderSize;
}

template<typename ElfN_Phdr>
size_t ElfPrgHeaderClass<ElfN_Phdr>::GetOffset()
{
    return prgHeaderOffset;
}

template<typename ElfN_Phdr>
void ElfPrgHeaderClass<ElfN_Phdr>::SetHeader(char* buffer, unsigned long e_phoff, uint16_t e_phentsize, uint16_t e_phnum)
{
   this->baseOffset = buffer;

  //Program 헤더를 가르킨다.
  pHeader = (ElfN_Phdr*)&buffer[e_phoff];
  totalHeaderSize = e_phentsize * e_phnum;
  prgHeaderOffset = e_phoff;
  //prgHeaderEntSize = e_phentsize;
  prgHeaderNumber = e_phnum;
}

template<typename ElfN_Phdr>
void ElfPrgHeaderClass<ElfN_Phdr>::ClearHeaderMemberList()
{
    p_typeStringList.clear();
    p_list.clear();
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

    QString str = GetTypeString(point->p_type);
    p_typeStr.sprintf("[%d] : %s", i, str.toStdString().c_str());
    p_typeStringList.append(p_typeStr);
    p_list.append(this->headerMemberList);

    this->headerMemberList.clear();
  }

  //dumpcode((unsigned char*)header, totalHeaderSize);
}

template<typename ElfN_Phdr>
QString ElfPrgHeaderClass<ElfN_Phdr>::GetTypeString(u_int32_t type)
{
    QString str;
    switch(type)
    {
        case PT_NULL         :/* Program header table entry unused */
                str = "NULL";
                break;
        case PT_LOAD         :/* Loadable program segment */
                str = "LOAD";
                break;
        case PT_DYNAMIC      :/* Dynamic linking information */
                str = "DYNAMIC";
                break;
        case PT_INTERP       :/* Program interpreter */
                str = "INTERP";
                break;
        case PT_NOTE         :/* Auxiliary information */
                str =  "NOTE";
                break;
        case PT_SHLIB        :/* Reserved */
                str =  "SHLIB";
                break;
        case PT_PHDR         :/* Entry for header table itself */
                str =  "PHDR";
                break;
        case PT_TLS          :/* Thread-local storage segment */
                str =  "TLS";
                break;
        case PT_NUM          :/* Number of defined types */
                str =  "NUM";
                break;
        case PT_LOOS         :/* Start of OS-specific */
                str =  "LOOS";
                break;
        case PT_GNU_EH_FRAME :/* GCC .eh_frame_hdr segment */
                str =  "GNU_EH_FRAME";
                break;
        case PT_GNU_STACK    :/* Indicates stack executability */
                str =  "GNU_STACK";
                break;
        case PT_GNU_RELRO    :/* Read-only after relocation */
                str =  "GNU_RELRO";
                break;
        case PT_LOSUNW       :/* Sun Specific segment */
                str =  "LOSUNW";
                break;
        case PT_SUNWSTACK    :/* Stack segment */
                str =  "SUNWSTACK";
                break;
        case PT_HISUNW       :/* End of OS-specific */
                str =  "HISUNW";
                break;
        case PT_LOPROC       :/* Start of processor-specific */
                str =  "LOPROC";
                break;
        case PT_HIPROC       :/* End of processor-specific */
                str =  "HIPROC";
                break;
        default         :/* UNKNOWN */
                str =  "UNKNOWN";
                break;
    }
    return str;
}

#endif // ELFPRGHEADERCLASS_H
