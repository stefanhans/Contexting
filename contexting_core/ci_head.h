#ifndef CI_HEAD_H
#define CI_HEAD_H

#include <QUuid>
#include <QHostAddress>
#include <QDateTime>
#include <QVector>


class CI_Head
{

public:

    CI_Head() :
        request(0),
        profile(0),
        version(1),
        channel(0),
        uuid(QUuid::createUuid()),
        ipAddress("0.0.0.0"),
        ipPort(0),
        time(QDateTime::currentDateTime()),
        headDataType(0),
        headDataSize(0),
        headDataArray() {}

    /*
     * request
     */
    quint8 getRequest() const;
    void setRequest(const quint8 &value);

    /*
     * profile
     */
    quint8 getProfile() const;
    void setProfile(const quint8 &value);

    /*
     * version
     */
    quint8 getVersion() const;
    void setVersion(const quint8 &value);

    /*
     * channel
     */
    quint8 getChannel() const;
    void setChannel(const quint8 &value);

    /*
     * uuid
     */
    QUuid getUuid() const;
    void setUuid(const QUuid &value);

    /*
     * ipAddress
     */
    QHostAddress getIpAddress() const;
    void setIpAddress(const QHostAddress &value);

    /*
     * ipPort
     */
    quint16 getIpPort() const;
    void setIpPort(const quint16 &value);

    /*
     * time
     */
    QDateTime getTime() const;
    void setTime(const QDateTime &value=QDateTime::currentDateTime());

    /*
     * headDataType
     */
    quint8 getHeadDataType() const;
    void setHeadDataType(const quint8 &value);

    /*
     * headDataSize
     */
    quint8 getHeadDataSize() const;
    void setHeadDataSize(const quint8 &value);


    /*
     * headData
     */
    const QVector<quint8> getHeadData(quint8 index=0, quint8 length=0) const;
    void setHeadData(const QVector<quint8> &value, quint8 index=0);
    void setHeadData(const QByteArray &value);

private:

    quint8 request;
    quint8 profile;
    quint8 version;
    quint8 channel;
    QUuid uuid;
    QHostAddress ipAddress;
    quint16 ipPort;
    QDateTime time;
    quint8 headDataType;
    quint8 headDataSize;
    quint8 headDataArray[255];

};

#endif // CI_HEAD_H
