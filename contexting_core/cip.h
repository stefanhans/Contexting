#ifndef CIP_H
#define CIP_H

#include "ci_head.h"
#include "ci.h"
#include "ci_data.h"

#include <arpa/inet.h>

#include <QVector>
#include <QDateTime>


class CIP
{

public:

    CIP() :
        ciHead(),
        ci(),
        ciData() {}


    /*
     * request
     */
    quint8 getRequest() const {
        return ciHead.getRequest();
    }
    void setRequest(const quint8 &value) {
        ciHead.setRequest(value);
    }

    /*
     * profile
     */
    quint8 getProfile() const {
        return ciHead.getProfile();
    }
    void setProfile(const quint8 &value) {
        ciHead.setProfile(value);
    }

    /*
     * version
     */
    quint8 getVersion() const {
        return ciHead.getVersion();
    }
    void setVersion(const quint8 &value) {
        ciHead.setVersion(value);
    }

    /*
     * channel
     */
    quint8 getChannel() const {
        return ciHead.getChannel();
    }
    void setChannel(const quint8 &value) {
        ciHead.setChannel(value);
    }

    /*
     * uuid
     */
    QUuid getUuid() const {
        return ciHead.getUuid();
    }
//    void setUuid(const QUuid &value)
//    {
//        ciHead.setUuid(value);
//    }

    /*
     * ipAddress
     */
    QHostAddress getIpAddress() const {
        return ciHead.getIpAddress();
    }
    void setIpAddress(const QHostAddress &value) {
        ciHead.setIpAddress(value);
    }

    /*
     * ipPort
     */
    quint16 getIpPort() const {
        return ciHead.getIpPort();
    }
    void setIpPort(const quint16 &value) {
        ciHead.setIpPort(value);
    }

    /*
     * time
     */
    QDateTime getTime() const {
        return ciHead.getTime();
    }
    void setTime(const QDateTime &value=QDateTime::currentDateTime()) {
        ciHead.setTime(value);
    }

    /*
     * headType
     */
    quint8 getHeadType() const {
        return ciHead.getHeadDataType();
    }
    void setHeadType(const quint8 &value) {
        ciHead.setHeadDataType(value);
    }


    /*
     * headSize
     */
    quint8 getHeadSize() const {
        return ciHead.getHeadDataSize();
    }
    void setHeadSize(const quint8 &value) {
        ciHead.setHeadDataSize(value);
    }


    /*
     * headData
     */
    const QVector<quint8> getHeadData(quint8 index=0, quint8 length=0) const {
        return ciHead.getHeadData(index, length);
    }
    void setHeadData(const QVector<quint8> &value, quint8 index=0) {
        ciHead.setHeadData(value, index);
    }



    /*
     * ciType
     */
    quint8 getCiType() const {
        return ci.getCiType();
    }
    void setCiType(const quint8 &value) {
        ci.setCiType(value);
    }


    /*
     * rootCIC
     */
    CI_Brick getRootCIC() const {
        return ci.getRootCIC();
    }
    void setRootCIC(const CI_Brick &value) {
        ci.setRootCIC(value);
    }

    quint8 getRootCicContent() const {
        return ci.getRootCicContent();
    }
    void setRootCicContent(const quint8 &value) {
        ci.setRootCicContent(value);
    }

    quint8 getRootCicMask() const {
        return ci.getRootCicMask();
    }
    void setRootCicMask(const quint8 &value) {
        ci.setRootCicMask(value);
    }


    /*
     * ciSize
     */
    quint8 getCiSize() const {
        return ci.getCiSize();
    }
    void setCiSize(const quint8 &value) {
        ci.setCiSize(value);
    }


    /*
     * ciBricks
     */
    const QVector<CI_Brick> getCiBricks(quint8 index=0, quint8 length=0) const {
        return ci.getCiBricks(index, length);
    }
    void setCiBricks(const QVector<CI_Brick> &value, quint8 index=0) {
        ci.setCiBricks(value, index);
    }


    /*
     * Context functions
     */
    QString getContextContent() const {
        return ci.getContextContent();
    }
    QString getContextRoute() const {
        return ci.getContextRoute();
    }


    /*
     * Path functions
     */
    QString getFullPath(const QChar delim='/') const {
        return ci.getFullPath(delim);
    }
    QString getRoutingPath(const QChar delim='/') const {
        return ci.getRoutingPath(delim);
    }



    /*
     * appType
     */
    quint8 getAppType() const {
        return ciData.getAppDataType();
    }
    void setAppType(const quint8 &value) {
        ciData.setAppDataType(value);
    }


    /*
     * appSize
     */
    quint8 getAppSize() const {
        return ciData.getAppDataSize();
    }
    void setAppSize(const quint8 &value) {
        ciData.setAppDataSize(value);
    }


    /*
     * appData
     */
    const QVector<quint8> getAppData(quint8 index=0, quint8 length=0) const {
        return ciData.getAppData(index, length);
    }
    void setAppData(const QVector<quint8> &value, quint8 index=0) {
        ciData.setAppData(value, index);
    }


    /*
     * packet functions
     */
    void pack();
    void unpack();

    bool validatePacket();


private:

    CI_Head ciHead;
    CI ci;
    CI_Data ciData;

    QByteArray packet;

};
#endif // CIP_H
