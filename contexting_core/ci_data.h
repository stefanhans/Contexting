#ifndef CI_DATA_H
#define CI_DATA_H



#include <QVector>


class CI_Data
{

public:

    CI_Data() :
        appDataType(0),
        appDataSize(),
        appDataArray() {}

    /*
     * appDataType
     */
    quint8 getAppDataType() const;
    void setAppDataType(const quint8 &value);


    /*
     * appDataSize
     */
    quint8 getAppDataSize() const;
    void setAppDataSize(const quint8 &value);


    /*
     * appData
     */
    const QVector<quint8> getAppData(quint8 index=0, quint8 length=0) const;
    void setAppData(const QVector<quint8> &value, quint8 index=0);

private:

    quint8 appDataType;
    quint8 appDataSize;
    quint8 appDataArray[255];

};

#endif // CI_DATA_H
