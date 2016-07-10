#include "ci_data.h"

#include <QDebug>


/*
 * appDataType
 */
quint8 CI_Data::getAppDataType() const
{
    return appDataType;
}

void CI_Data::setAppDataType(const quint8 &value)
{
    appDataType = value;
}

/*
 * appDataSize
 */
quint8 CI_Data::getAppDataSize() const
{
    return appDataSize;
}

void CI_Data::setAppDataSize(const quint8 &value)
{
    appDataSize = value;
}


/*
 * appData
 */
const QVector<quint8> CI_Data::getAppData(quint8 index, quint8 length) const
{
    QVector<quint8> out;

    if(length == 0) {
        for (int i = index; i < appDataSize-index; i++) {
            out.append(appDataArray[i]);
        }
    }

    for (int i = index; i < index+length; i++) {
        out.append(appDataArray[i]);
    }
    return out;
}

void CI_Data::setAppData(const QVector<quint8> &value, quint8 index)
{
    appDataSize = value.size() + index;

    for(int i=0; i<value.size(); i++) {
        appDataArray[index++] = value.at(i);
    }
}
