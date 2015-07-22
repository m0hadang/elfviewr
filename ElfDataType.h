#ifndef ELFDATATYPE_H
#define ELFDATATYPE_H
#include <QString>
class ElfDataType
{
public :
    QString memberOffset;//member offset for display (colum)
    QString memberName;//member name for display (colum)
    QString memberValue;//member value for display (colum)
    int dataLen;//member data len
    unsigned long rawOffset;//in dump memory pointer
    unsigned long rawValue;//in dump memory value
private :
    static int bitInfo;

public:
    ElfDataType();
    void SetData(unsigned long _rawOffset, QString _memberName, unsigned long _rawValue, int _dataLen);
    static void SetBitInfo(int _bitInfo)
    {
        bitInfo = _bitInfo;
    }
};


#endif // ELFDATATYPE_H
