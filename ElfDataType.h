#ifndef ELFDATATYPE_H
#define ELFDATATYPE_H
#include <QString>
class ElfDataType
{
public :
    QString memberOffset;
    QString memberName;
    QString memberValue;
    int dataLen;
    unsigned long rawOffset;
    unsigned long rawValue;

public:
    ElfDataType();
    void SetData(unsigned long _rawOffset, QString _memberName, unsigned long _rawValue, int _dataLen, int _bitInfo);
};


#endif // ELFDATATYPE_H
