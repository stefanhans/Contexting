#include "ci_head.h"

#include <QDebug>

/*
 * request
 */
quint8 CI_Head::getRequest() const
{
    return request;
}

void CI_Head::setRequest(const quint8 &value)
{
    request = value;
}


/*
 * profile
 */
quint8 CI_Head::getProfile() const
{
    return profile;
}

void CI_Head::setProfile(const quint8 &value)
{
    profile = value;
}


/*
 * version
 */
quint8 CI_Head::getVersion() const
{
    return version;
}

void CI_Head::setVersion(const quint8 &value)
{
    version = value;
}


/*
 * channel
 */
quint8 CI_Head::getChannel() const
{
    return channel;
}

void CI_Head::setChannel(const quint8 &value)
{
    channel = value;
}


/*
 * uuid
 */
QUuid CI_Head::getUuid() const
{
    return uuid;
}

void CI_Head::setUuid(const QUuid &value)
{
    uuid = value;
}


/*
 * ipAddress
 */
QHostAddress CI_Head::getIpAddress() const
{
    return ipAddress;
}

void CI_Head::setIpAddress(const QHostAddress &value)
{
    ipAddress = value;
}


/*
 * ipPort
 */
quint16 CI_Head::getIpPort() const
{
    return ipPort;
}

void CI_Head::setIpPort(const quint16 &value)
{
    ipPort = value;
}


/*
 * time
 */
QDateTime CI_Head::getTime() const
{
    return time;
}

void CI_Head::setTime(const QDateTime &value)
{
    time = value;
}


/*
 * headDataType
 */
quint8 CI_Head::getHeadDataType() const
{
    return headDataType;
}

void CI_Head::setHeadDataType(const quint8 &value)
{
    headDataType = value;
}


/*
 * headDataSize
 */
quint8 CI_Head::getHeadDataSize() const
{
    return headDataSize;
}

void CI_Head::setHeadDataSize(const quint8 &value)
{
    headDataSize = value;
}


/*
 * headData
 */
const QVector<quint8> CI_Head::getHeadData(quint8 index, quint8 length) const
{
    QVector<quint8> out;

    if(length == 0) {
        for (int i = index; i < headDataSize-index; i++) {
            out.append(headDataArray[i]);
        }
    }

    for (int i = index; i < index+length; i++) {
        out.append(headDataArray[i]);
    }
    return out;
}

void CI_Head::setHeadData(const QVector<quint8> &value, quint8 index)
{
    headDataSize = value.size() + index;

    for(int i=0; i<value.size(); i++) {
        headDataArray[index++] = value.at(i);
    }
}

void CI_Head::setHeadData(const QByteArray &value)
{
    headDataSize = value.size();

    for(int i=0; i<value.size();i++) {
        headDataArray[i] = value.at(i);
    }
}
