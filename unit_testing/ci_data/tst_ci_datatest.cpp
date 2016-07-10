#include <QString>
#include <QtTest>

#include "ci_data.h"

class Ci_dataTest : public QObject
{
    Q_OBJECT

public:
    Ci_dataTest();

private Q_SLOTS:
    void initTestCase();
    void testGetterSetter();
    void cleanupTestCase();

private:
    quint8 appDataType;
    quint8 appDataSize;

    QVector<quint8> appData;

    CI_Data ciData;

    quint8 randByte(int limit=256);
    quint8 randByteUnique();

    bool appDataAreEqual(const QVector<quint8> &value_1, const QVector<quint8> &value_2);
};

Ci_dataTest::Ci_dataTest()
{
}

void Ci_dataTest::initTestCase()
{
    appData.fill(0, 255);
}

void Ci_dataTest::testGetterSetter()
{
//    QSKIP("OK");

    // appDataType
    qDebug() << "appDataType";
    for (int i = 0; i<=255; i++) {

        ciData.setAppDataType(i);
        QVERIFY(ciData.getAppDataType() == i);
    }

    // appDataSize
    qDebug() << "appDataSize";
    for (int i = 0; i<=255; i++) {

        ciData.setAppDataSize(i);
        QVERIFY(ciData.getAppDataSize() == i);
    }

    // appData
    qDebug() << "appData";
    for (int i = 0; i<=255; i++) {

        appData.clear();
        appData.fill(randByteUnique(), i);

        ciData.setAppData(appData);

        QVERIFY(ciData.getAppData() == appData);
        QVERIFY(appDataAreEqual(ciData.getAppData(), appData));
    }
}


void Ci_dataTest::cleanupTestCase()
{
}



quint8 Ci_dataTest::randByte(int limit)
{

    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());

    return qrand() % limit;
}

quint8 Ci_dataTest::randByteUnique()
{
    quint8 rand_1 = randByte();
    quint8 rand_2 = randByte();

    while ( rand_1 == rand_2 ) {
        rand_2 = randByte();
    }

    return rand_2;
}

bool Ci_dataTest::appDataAreEqual(const QVector<quint8> &value_1, const QVector<quint8> &value_2) {

    if (value_1.size() != value_2.size()) {
        qDebug() << "appDataAreEqual size: " << value_1.size() << " != " << value_2.size();
        return false;
    }

    for (int i=0; i<value_1.size(); i++) {
        if ( ! (value_1.at(i) == value_2.at(i))) {
            qDebug() << "appDataAreEqual at(" << i << "): " << value_1.at(i) << " != " << value_2.at(i);
            return false;
        }
    }
    return true;
}



QTEST_APPLESS_MAIN(Ci_dataTest)

#include "tst_ci_datatest.moc"
