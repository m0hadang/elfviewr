#include "ElfDataType.h"
#include "elf.h"

ElfDataType::ElfDataType()
{

}
int ElfDataType::bitInfo = 0;

void ElfDataType::SetData(unsigned long _rawOffset, QString _memberName, unsigned long _rawValue,int _dataLen)
{
    rawOffset = _rawOffset;

    //Offset Setting
    switch(bitInfo)
    {
      case ELFCLASS32:
        memberOffset.sprintf("0x%08x",(unsigned int) _rawOffset);
        break;
      case ELFCLASS64:
        //memberOffset.sprintf("0x%08x%08x", *(((unsigned int*)(&_rawOffset))+1) ,(unsigned int)_rawOffset);
        memberOffset.sprintf("0x%016x" ,(unsigned int)_rawOffset);
        break;
    }

    //Value Setting
    switch(_dataLen)
    {
      case 2: //Data length 2byte
        memberValue.sprintf("0x%04x",(unsigned short) _rawValue);
        break;

      case 4: //Data length 4byte
        memberValue.sprintf("0x%08x",(unsigned int) _rawValue);
        break;

      case 8:  //Data length  8byte
        //memberValue.sprintf("0x%08x%08x", *(((unsigned int*)(&_rawValue))+1) ,(unsigned int)_rawValue);
        memberValue.sprintf("0x%016x", (unsigned int)_rawValue);
        break;

      case EI_NIDENT:  //Data length 16byte
        unsigned char* e_ident = (unsigned char*)_rawValue;
        memberValue.sprintf("%s",e_ident);
        break;
    }

    memberName = _memberName;

    dataLen = _dataLen;
}

