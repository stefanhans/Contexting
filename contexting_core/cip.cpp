#include "cip.h"

#include <QDebug>



void CIP::pack() {

    packet.clear();

    // START HEADER
    packet.append(getRequest());
    packet.append(getProfile());
    packet.append(getVersion());
    packet.append(getChannel());

    // UUID
    QByteArray uuid_arr = ciHead.getUuid().toRfc4122();
    for(int j=0; j<16;j++) {
        packet.append(uuid_arr.at(j));
    }

    // IP ADDRESS
    quint32 ip = ciHead.getIpAddress().toIPv4Address();
    quint8 ipSub;

    ipSub = ip>>24;
    packet.append(ipSub);
    ipSub = ip>>16;
    packet.append(ipSub);
    ipSub = ip>>8;
    packet.append(ipSub);
    ipSub = ip;
    packet.append(ipSub);

    // IP PORT
    quint8 portSub;

    portSub = ciHead.getIpPort()>>8;
    packet.append(portSub);
    portSub = ciHead.getIpPort();
    packet.append(portSub);

    // TIME
    uint unixTime = ciHead.getTime().toTime_t();
    QByteArray seconds;
    int pos = 0;

    for(int j = 0; j < 8; j++) {

        seconds[pos++] = unixTime%256;
        unixTime = unixTime >> 8;
    }
    packet.append(seconds);

    // HEADER TYPE
    packet.append(ciHead.getHeadDataType());

    // HEADER SIZE
    quint8 headerSize = ciHead.getHeadDataSize();
    packet.append(headerSize);

    // HEADER DATA
    for (int i=0; i<headerSize; i++) {
        packet.append((quint8) ciHead.getHeadData().at(i));
    }


    // CI TYPE
    packet.append(ci.getCiType());

    // ROOT CIC
    packet.append(ci.getRootCIC().getContent());
    packet.append(ci.getRootCIC().getMask());

    // CIC BRICKS
    quint8 ciSize = ci.getCiSize();
    packet.append(ciSize);

    for (int i=0; i<ciSize; i++) {
        packet.append(ci.getCiBricks().at(i).getContent());
        packet.append(ci.getCiBricks().at(i).getMask());
    }


    // APPLICATION TYPE
    packet.append(ciData.getAppDataType());

    // APPLICATION SIZE
    quint8 appDataSize = ciData.getAppDataSize();
    packet.append(appDataSize);

    // APPLICATION DATA
    for (int i=0; i<appDataSize; i++) {
        packet.append(ciData.getAppData().at(i));
    }
}


/*
 *
 * UNPACK
 *
 */

void CIP::unpack() {

    quint8 byte;
    int b = 0;
    quint8 size;
    QByteArray tmpArray;
    QString cipString;

    // Header: request (1)
    byte = packet.at(b++);
    setRequest(byte);

    // Header: profile (1)
    byte = packet.at(b++);
    setProfile(byte);

    // Header: verion (1)
    byte = packet.at(b++);
    setVersion(byte);

    // Header: channel (1)
    byte = packet.at(b++);
    setChannel(byte);

    // Header: UUID (16)
    tmpArray = packet.mid(b, 16);
    b += 16;
    ciHead.setUuid(QUuid::fromRfc4122(tmpArray));

    // Header: IP address (4)
    tmpArray.clear();
    tmpArray = packet.mid(b, 4);
    b += 4;
    in_addr ip;
    memcpy(&ip, tmpArray, 4);

    setIpAddress(QHostAddress(inet_ntoa(ip)));

    // Header: IP port (2)
    tmpArray.clear();
    tmpArray = packet.mid(b, 2);
    b += 2;
    ciHead.setIpPort((tmpArray.at(0)<<8) + tmpArray.at(1));


    // Header: time (8)
    tmpArray.clear();
    tmpArray = packet.mid(b, 8);
    b += 8;
    time_t unixTime;
    memcpy(&unixTime, tmpArray, 8);

    ciHead.getTime().setTime_t((uint) unixTime);

    // Header: type (1)
    byte = packet.at(b++);
    ciHead.setHeadDataType(byte);

    // Header: size (1)
    byte = packet.at(b++);
    ciHead.setHeadDataSize(byte);
    size = byte;

    // Header: additional data (size)
    tmpArray.clear();
    tmpArray = packet.mid(b, size);
    b += size;
    ciHead.setHeadData(tmpArray);

    // CI: type (1)
    byte = packet.at(b++);
    setCiType(byte);

    // CI root-CIC (2)
    byte = packet.at(b++);
    quint8 content = byte;
    byte = packet.at(b++);
    ci.setRootCicContent(content);
    ci.setRootCicMask(byte);

    // CI: size (1)
    byte = packet.at(b++);
    setCiSize(byte);
    size = byte;

    // CI: additional data (size)
    tmpArray.clear();
    tmpArray = packet.mid(b, size*2);
    b += size*2;
    ci.setCiBricks(tmpArray);

    // Application Data: type (1)
    byte = packet.at(b++);
    ciData.setAppDataType(byte);

    // Application Data: size (1)
    byte = packet.at(b++);
    ciData.setAppDataSize(byte);
    size = byte;

    // Application Data: additional data (size)
    tmpArray.clear();
    tmpArray = packet.mid(b, size);
    b += size;
    ciData.setAppData(tmpArray);
} //


const QByteArray CIP::getPacket() {
    qDebug() << "getPacket().size: " << packet.size();
    if(packet.size() <= 10) {
        pack();
    }
    return packet;
}

void CIP::setPacket(QByteArray &value) {
    packet = value;
}



/*
 *
 * VALIDATE CIP
 *
 */

bool CIP::validatePacket() {

    qDebug() << "packet.size(): " << packet.size();

    if(packet.size() < 42 || packet.size() > 1062) {
        return false;
    }




    int size;
    int additionalBytes;
    bool ok;

    // Header: size
    size = 35;
    additionalBytes = QString("%1").arg((quint8) packet.at(size)).toInt(&ok);
    if(!ok) {
        qDebug() << "Header: size: Cannot convert "<< (quint8) packet.at(size) << " to integer!";
        return false;
    }
    qDebug() << "Header: size: " << additionalBytes;
    size += additionalBytes;

    // CI: size
    size += 4;
    additionalBytes = QString("%1").arg((quint8) packet.at(size)).toInt(&ok);
    if(!ok) {
        qDebug() << "CI: size: Cannot convert "<< (quint8) packet.at(size) << " to integer!";
        return false;
    }
    qDebug() << "CI: size: " << additionalBytes;
    size += additionalBytes*2;

    // Application: size
    size += 2;
    additionalBytes = QString("%1").arg((quint8) packet.at(size)).toInt(&ok);
    if(!ok) {
        qDebug() << "Application: size: Cannot convert "<< (quint8) packet.at(size) << " to integer!";
        return false;
    }
    qDebug() << "Application: size: " << additionalBytes;
    size += additionalBytes;


    qDebug() << "packet.size(): " << packet.size();
    qDebug() << "size: " << size+1;
    if (packet.size() != size+1) {

        qDebug() << "INVALID: CIP size is not consistent!";
        return false;
    }


    return true;
}


