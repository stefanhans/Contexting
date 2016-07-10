#include <QString>
#include <QtTest>
#include <typeinfo>

#include "ci_head.h"

class Ci_headTest : public QObject
{
    Q_OBJECT

public:
    Ci_headTest();

private Q_SLOTS:
    void initTestCase();
    void testGetterSetter();
    void cleanupTestCase();

private:
    quint8 headDataType;
    quint8 headDataSize;

    QVector<quint8> headData;

    CI_Head ciHead;

    quint8 randByte(int limit=256);
    quint8 randByteUnique();

    bool headDataAreEqual(const QVector<quint8> &value_1, const QVector<quint8> &value_2);
};

Ci_headTest::Ci_headTest()
{
}

void Ci_headTest::initTestCase()
{
    headData.fill(0, 255);
}

void Ci_headTest::testGetterSetter()
{
//    QSKIP("OK");

    // request
    qDebug() << "request";
    for (int i = 0; i<=255; i++) {

        ciHead.setRequest(i);
        QVERIFY(ciHead.getRequest() == i);
    }

    // profile
    qDebug() << "profile";
    for (int i = 0; i<=255; i++) {

        ciHead.setProfile(i);
        QVERIFY(ciHead.getProfile() == i);
    }

    // version
    qDebug() << "version";
    for (int i = 0; i<=255; i++) {

        ciHead.setVersion(i);
        QVERIFY(ciHead.getVersion() == i);
    }

    // channel
    qDebug() << "channel";
    for (int i = 0; i<=255; i++) {

        ciHead.setChannel(i);
        QVERIFY(ciHead.getChannel() == i);
    }

    // uuid
    qDebug() << "uuid";
//    qDebug() << typeid(ciHead.getUuid()).name();
    QVERIFY(QString(typeid(ciHead.getUuid()).name()) == "5QUuid");


    // ipAddress
    qDebug() << "ipAddress";
    QString ipAddr;

    for (int i = 0; i<=255; i++) {

        ipAddr = QString("%1.%2.%3.%4").arg(randByteUnique()).arg(randByteUnique()).arg(randByteUnique()).arg(randByteUnique());
        ciHead.setIpAddress(QHostAddress(ipAddr));

        QVERIFY(ciHead.getIpAddress().toString() == ipAddr);
    }

    // ipPort
    qDebug() << "ipPort";
    for (qint16 i = 0; i<=UCHAR_MAX; i++) {

        ciHead.setIpPort(i);
        QVERIFY(ciHead.getIpPort() == i);
    }

    // time
    qDebug() << "time";
    QDateTime time;
    for (int i = 0; i<=2550; i++) {

        time = QDateTime::fromTime_t(i*randByteUnique());
        ciHead.setTime(time);
        QVERIFY(ciHead.getTime() == time);
    }

    // headDataType
    qDebug() << "headDataType";
    for (int i = 0; i<=255; i++) {

        ciHead.setHeadDataType((quint8) i);
        QVERIFY(ciHead.getHeadDataType() == i);
    }

    // headDataSize
    qDebug() << "headDataSize";
    for (int i = 0; i<=255; i++) {

        ciHead.setHeadDataSize(i);
        QVERIFY(ciHead.getHeadDataSize() == i);
    }

    // headData
    qDebug() << "headData";
    for (int i = 0; i<=255; i++) {

        headData.clear();
        headData.fill(randByteUnique(), i);

        ciHead.setHeadData(headData);

        QVERIFY(ciHead.getHeadData() == headData);
        QVERIFY(headDataAreEqual(ciHead.getHeadData(), headData));
    }
}


void Ci_headTest::cleanupTestCase()
{
}


quint8 Ci_headTest::randByte(int limit)
{

    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());

    return qrand() % limit;
}

quint8 Ci_headTest::randByteUnique()
{
    quint8 rand_1 = randByte();
    quint8 rand_2 = randByte();

    while ( rand_1 == rand_2 ) {
        rand_2 = randByte();
    }

    return rand_2;
}

bool Ci_headTest::headDataAreEqual(const QVector<quint8> &value_1, const QVector<quint8> &value_2) {

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


QTEST_APPLESS_MAIN(Ci_headTest)

#include "tst_ci_headtest.moc"
