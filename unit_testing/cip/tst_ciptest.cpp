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
    void cleanupTestCase();

private:
    quint8 headDataType;
    quint8 headDataSize;

    QVector<quint8> headData;

    CIP cip;

    quint8 randByte(int limit=256);
    quint8 randByteUnique();

    bool headDataAreEqual(const QVector<quint8> &value_1, const QVector<quint8> &value_2);
};

CipTest::CipTest()
{
}

void CipTest::initTestCase()
{
    headData.fill(0, 255);
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

        headData.clear();
        headData.fill(randByteUnique(), i);

        cip.setHeadData(headData);

        QVERIFY(cip.getHeadData() == headData);
        QVERIFY(headDataAreEqual(cip.getHeadData(), headData));
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

bool CipTest::headDataAreEqual(const QVector<quint8> &value_1, const QVector<quint8> &value_2) {

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


QTEST_APPLESS_MAIN(CipTest)

#include "tst_ciptest.moc"