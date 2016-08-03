#include <QString>
#include <QtTest>
#include <typeinfo>

#include "cip.h"


class CipTest : public QObject
{
    Q_OBJECT

public:
    CipTest();

private Q_SLOTS:
    void initTestCase();
    void testGetterSetter();
    void testPacketFunctions();
    void cleanupTestCase();

private:

    CIP cip;

    QVector<quint8> data;

    CI_Brick ci_brick;
    QVector<CI_Brick> ciBricks;

    quint8 randByte(int limit=256);
    quint8 randByteUnique();

    void randCip(CIP &cip);

bool dataAreEqual(const QVector<quint8> &value_1, const QVector<quint8> &value_2);
bool ciBricksAreEqual(const QVector<CI_Brick> &value_1, const QVector<CI_Brick> &value_2);
};

CipTest::CipTest()
{
}

void CipTest::initTestCase()
{
    data.fill(0, 255);
}

void CipTest::testGetterSetter()
{
//    QSKIP("OK");

    // request
    qDebug() << "request";
    for (int i = 0; i<=255; i++) {

        cip.setRequest(i);
        QVERIFY(cip.getRequest() == i);
    }

    // profile
    qDebug() << "profile";
    for (int i = 0; i<=255; i++) {

        cip.setProfile(i);
        QVERIFY(cip.getProfile() == i);
    }

    // version
    qDebug() << "version";
    for (int i = 0; i<=255; i++) {

        cip.setVersion(i);
        QVERIFY(cip.getVersion() == i);
    }

    // channel
    qDebug() << "channel";
    for (int i = 0; i<=255; i++) {

        cip.setChannel(i);
        QVERIFY(cip.getChannel() == i);
    }

    // uuid
    qDebug() << "uuid";
//    qDebug() << typeid(cip.getUuid()).name();
    QVERIFY(QString(typeid(cip.getUuid()).name()) == "5QUuid");


    // ipAddress
    qDebug() << "ipAddress";
    QString ipAddr;

    for (int i = 0; i<=255; i++) {

        ipAddr = QString("%1.%2.%3.%4").arg(randByteUnique()).arg(randByteUnique()).arg(randByteUnique()).arg(randByteUnique());
        cip.setIpAddress(QHostAddress(ipAddr));

        QVERIFY(cip.getIpAddress().toString() == ipAddr);
    }

    // ipPort
    qDebug() << "ipPort";
    for (qint16 i = 0; i<=UCHAR_MAX; i++) {

        cip.setIpPort(i);
        QVERIFY(cip.getIpPort() == i);
    }

    // time
    qDebug() << "time";
    QDateTime time;
    for (int i = 0; i<=2550; i++) {

        time = QDateTime::fromTime_t(i*randByteUnique());
        cip.setTime(time);
        QVERIFY(cip.getTime() == time);
    }

    // headType
    qDebug() << "headType";
    for (int i = 0; i<=255; i++) {

        cip.setHeadType((quint8) i);
        QVERIFY(cip.getHeadType() == i);
    }

    // headSize
    qDebug() << "headSize";
    for (int i = 0; i<=255; i++) {

        cip.setHeadSize(i);
        QVERIFY(cip.getHeadSize() == i);
    }

    // headData
    qDebug() << "headData";
    for (int i = 0; i<=255; i++) {

        data.clear();
        data.fill(randByteUnique(), i);

        cip.setHeadData(data);

        QVERIFY(cip.getHeadData() == data);
        QVERIFY(dataAreEqual(cip.getHeadData(), data));
    }

    // ciType
    qDebug() << "ciType";
    for (int i = 0; i<=255; i++) {

        cip.setCiType(i);
        QVERIFY(cip.getCiType() == i);
    }

    // rootCIC
    qDebug() << "rootCIC";
    for (int i=0; i<=255; i++) {
        ci_brick.setContent(i);

        for (int j = 0; j<=255; j++) {
            ci_brick.setMask(j);

            cip.setRootCIC(ci_brick);
            QVERIFY(cip.getRootCIC() == ci_brick);
        }
    }

    // RootCicContent
    for (int i=0; i<=255; i++) {

        cip.setRootCicContent(i);
        QVERIFY(cip.getRootCicContent() == i);
    }

    // RootCicMask
    for (int i=0; i<=255; i++) {

        cip.setRootCicMask(i);
        QVERIFY(cip.getRootCicMask() == i);
    }

    // ciBricks
    qDebug() << "ciBricks";

    ciBricks.clear();
    for (int i=0; i<255; i++) {
        ciBricks.append(CI_Brick(randByteUnique(), randByteUnique()));
    }
    cip.setCiBricks(ciBricks);
    QVERIFY(ciBricksAreEqual(cip.getCiBricks(), ciBricks));



    quint8 testIndex = 100;
    quint8 testLength = 100;

    QVector<CI_Brick> partBricks;
    partBricks.fill(CI_Brick(0, 0), testLength);


    for (int i=0; i<255; i++) {
        if(i >= testIndex && i <= testIndex + testLength) {
          ciBricks[i] =  CI_Brick(0, 0);
        }
    }

    cip.setCiBricks(ciBricks);
    QVERIFY(ciBricksAreEqual(cip.getCiBricks(testIndex, testLength), partBricks));




//    const QVector<CI_Brick> getCiBricks(quint8 index=0, quint8 length=0) const {
//        return ci.getCiBricks(index, length);
//    }
//    void setCiBricks(const QVector<CI_Brick> &value, quint8 index=0) {
//        ci.setCiBricks(value, index);
//    }



    // CiSize
    qDebug() << "CiSize";
    for (int i = 0; i<=255; i++) {

        cip.setCiSize(i);
        QVERIFY(cip.getCiSize() == i);
    }






    // appType
    qDebug() << "appType";
    for (int i = 0; i<=255; i++) {

        cip.setAppType((quint8) i);
        QVERIFY(cip.getAppType() == i);
    }

    // appSize
    qDebug() << "appSize";
    for (int i = 0; i<=255; i++) {

        cip.setAppSize(i);
        QVERIFY(cip.getAppSize() == i);
    }

    // appData
    qDebug() << "appData";
    for (int i = 0; i<=255; i++) {

        data.clear();
        data.fill(randByteUnique(), i);

        cip.setAppData(data);

        QVERIFY(cip.getAppData() == data);
        QVERIFY(dataAreEqual(cip.getAppData(), data));
    }
}


void CipTest::testPacketFunctions()
{
    QSKIP("OK");

    QByteArray oneCipPacket, controlPacket;

    QVector<CIP> randomCIPs;

    for (int i=0; i<12; i++) {
        randomCIPs.append(CIP());
        randCip(randomCIPs[i]);
        qDebug() << "Uuid: " << randomCIPs.at(i).getUuid().toString();
        qDebug() << "ci_head: " << randomCIPs.at(i).getHeadSize();
        qDebug() << "ci: " << randomCIPs.at(i).getCiSize();
        qDebug() << "ci_data: " << randomCIPs.at(i).getAppSize();


        oneCipPacket = randomCIPs[i].getPacket();


        CIP cipFromOneCipPacket(oneCipPacket);

        controlPacket = cipFromOneCipPacket.getPacket();

        qDebug() << "controlPacket.size(): " << controlPacket.size();
        qDebug() << "oneCipPacket.size(): " << oneCipPacket.size();

        QVERIFY(controlPacket == oneCipPacket);
    }
}

void CipTest::cleanupTestCase()
{
}


quint8 CipTest::randByte(int limit)
{

    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());

    return qrand() % limit;
}

quint8 CipTest::randByteUnique()
{
    quint8 rand_1 = randByte();
    quint8 rand_2 = randByte();

    while ( rand_1 == rand_2 ) {
        rand_2 = randByte();
    }

    return rand_2;
}

void CipTest::randCip(CIP &cip)
{
    cip.setRequest(randByteUnique());
    cip.setProfile(randByteUnique());
    cip.setVersion(randByteUnique());
    cip.setChannel(randByteUnique());
    cip.setIpAddress(QHostAddress(QString("%1.%2.%3.%4").arg(randByteUnique()).arg(randByteUnique()).arg(randByteUnique()).arg(randByteUnique())));
    cip.setIpPort(randByteUnique()*randByteUnique());
    cip.setTime(QDateTime::currentDateTime());
    cip.setHeadType(randByteUnique());
    cip.setHeadSize(randByteUnique());
    for(int i=0; i <cip.getHeadSize(); i++) {
        cip.setHeadData(QVector<quint8>(randByteUnique()), i);
    }

    cip.setCiType(randByteUnique());
    cip.setCiSize(randByteUnique());
    QVector<CI_Brick> ciBricks;
//    for(int i=0; i <cip.getCiSize(); i++) {
//        ciBricks.append(CI_Brick(randByteUnique(), randByteUnique()));
//    }

    cip.setCiBricks(ciBricks);
    cip.setAppType(randByteUnique());
    cip.setAppSize(randByteUnique());
    for(int i=0; i <cip.getAppSize(); i++) {
        cip.setAppData(QVector<quint8>(randByteUnique()), i);
    }
}

bool CipTest::dataAreEqual(const QVector<quint8> &value_1, const QVector<quint8> &value_2) {

    if (value_1.size() != value_2.size()) {
        qDebug() << "headDataAreEqual size: " << value_1.size() << " != " << value_2.size();
        return false;
    }

    for (int i=0; i<value_1.size(); i++) {
        if ( ! (value_1.at(i) == value_2.at(i))) {
            qDebug() << "headDataAreEqual at(" << i << "): " << value_1.at(i) << " != " << value_2.at(i);
            return false;
        }
    }
    return true;
}


bool CipTest::ciBricksAreEqual(const QVector<CI_Brick> &value_1, const QVector<CI_Brick> &value_2) {

    if (value_1.size() != value_2.size()) {
        qDebug() << "ciBricksAreEqual size: " << value_1.size() << " != " << value_2.size();
        return false;
    }

    for (int i=0; i<value_1.size(); i++) {
        if ( ! (((CI_Brick)value_1.at(i)) == ((CI_Brick)value_2.at(i)))) {
            qDebug() << "ciBricksAreEqual at(" << i << "): " << ((CI_Brick)value_1.at(i)).getContent() << " != " << ((CI_Brick)value_2.at(i)).getContent();
            return false;
        }
    }
    return true;
}


QTEST_APPLESS_MAIN(CipTest)

#include "tst_ciptest.moc"
