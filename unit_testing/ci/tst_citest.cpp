#include <QString>
#include <QtTest>

#include "ci_brick.h"
#include "ci.h"

class CiTest : public QObject
{
    Q_OBJECT

public:
    CiTest();

private Q_SLOTS:
    void initTestCase();
    void testGetterSetter();
    void testRandomGetterSetter();
    void testCiBricks();
    void testRandomCiBricks();
    void testPathFunctions();
    void cleanupTestCase();

private:
    quint8 ciType;
    CI_Brick rootCIC;
    quint8 ciSize;
    QVector<CI_Brick> ci_bricks;
    QVector<CI_Brick> ci_bricks_2;
    QVector<CI_Brick> ci_bricks_full;
    QVector<CI_Brick> ci_bricks_empty;

    CI ci;


    quint8 content;
    quint8 mask;

    CI_Brick ci_brick;
    CI_Brick ci_brick_2;

    CI_Brick ci_brick_all_0;
    CI_Brick ci_brick_all_1;

    QByteArray *byteArr;

    quint8 rand;
    quint8 randContent;
    quint8 randMask;

    quint8 randByte();
    quint8 randByteUnique();

    QVector<quint8> testInts;

    bool ciBricksAreEqual(const QVector<CI_Brick> &value_1, const QVector<CI_Brick> &value_2);
};

CiTest::CiTest()
{
}

void CiTest::initTestCase()
{
    ci_bricks.fill(ci_brick, 256);

    for (int i=1; i<=255; i++) {
        ci_bricks[i].setContent(i);
        ci_bricks[i].setMask(i);
    }

    ci_brick_all_0.setContent(0);
    ci_brick_all_0.setMask(0);

    ci_brick_all_1.setContent(1);
    ci_brick_all_1.setMask(1);

    ci_bricks_full.fill(ci_brick_all_0, 255);

    testInts.append(0);
    testInts.append(1);
    testInts.append(2);
    testInts.append(randByteUnique());
    testInts.append(randByteUnique());
    testInts.append(randByteUnique());
    testInts.append(randByteUnique());
    testInts.append(randByteUnique());
    testInts.append(randByteUnique());
    testInts.append(randByteUnique());
    testInts.append(254);
    testInts.append(255);

}

void CiTest::testGetterSetter()
{
    // CiType
    qDebug() << "CiType";
    for (int i = 0; i<=255; i++) {

        ci.setCiType(i);
        QVERIFY(ci.getCiType() == i);
    }

    // RootCIC
    qDebug() << "RootCIC";
    for (int i=0; i<=255; i++) {
        ci_brick.setContent(i);

        for (int j = 0; j<=255; j++) {
            ci_brick.setMask(j);

            ci.setRootCIC(ci_brick);
            QVERIFY(ci.getRootCIC() == ci_brick);
        }
    }

    // RootCicContent
    qDebug() << "RootCicContent";
    for (int i=0; i<=255; i++) {

        ci.setRootCicContent(i);
        QVERIFY(ci.getRootCicContent() == i);
    }

    // RootCicMask
    qDebug() << "RootCicMask";
    for (int i=0; i<=255; i++) {

        ci.setRootCicMask(i);
        QVERIFY(ci.getRootCicMask() == i);
    }

    // CiSize
    qDebug() << "CiSize";
    for (int i = 0; i<=255; i++) {

        ci.setCiSize(i);
        QVERIFY(ci.getCiSize() == i);
    }
}

void CiTest::testRandomGetterSetter()
{
    // CiType
    qDebug() << "CiType";
    for (int i=0; i<1000; i++) {
        rand = randByte();

        ci.setCiType(rand);
        QVERIFY(ci.getCiType() == rand);
    }

    // RootCIC
    qDebug() << "RootCIC";
    for (int i=0; i<100; i++) {
        randContent = randByte();
        ci_brick.setContent(randContent);

        for (int j = 0; j<100; j++) {
            randMask = randByte();
            ci_brick.setMask(randMask);

            ci.setRootCIC(ci_brick);
            QVERIFY(ci.getRootCIC() == ci_brick);
        }
    }

    // RootCicContent
    qDebug() << "RootCicContent";
    for (int i=0; i<1000; i++) {
        randContent = randByte();

        ci.setRootCicContent(randContent);
        QVERIFY(ci.getRootCicContent() == randContent);
    }

    // RootCicMask
    qDebug() << "RootCicMask";
    for (int i=0; i<1000; i++) {
        randMask = randByte();

        ci.setRootCicMask(randMask);
        QVERIFY(ci.getRootCicMask() == randMask);
    }


    // CiSize
    qDebug() << "CiSize";
    for (int i=0; i<1000; i++) {
        rand = randByte();
        ci.setCiSize(rand);

        QVERIFY(ci.getCiSize() == rand);
    }
}

void CiTest::testCiBricks()
{
    // CiBrick set/get all
    qDebug() << "CiBrick set/get all";

    for (int l=0; l<=255; l++) {

        ci_bricks.clear();
        ci.setCiBricks(ci_bricks_full);

        ci_bricks.fill(ci_brick_all_1, l);
        ci.setCiBricks(ci_bricks);
        ci.setCiSize(ci_bricks.size());

        QVERIFY(ciBricksAreEqual((QVector<CI_Brick>) ci.getCiBricks(), ci_bricks));
    }

    // CiBrick set/get index/length
    qDebug() << "CiBrick set/get index/length";

    foreach(quint8 length, testInts) {

        for (int index=0; index<=255-length; index++) {
            if(index == 255-length) {



                ci_bricks.clear();
                ci.setCiBricks(ci_bricks_full);

                ci_bricks.fill(ci_brick_all_1, length);
                ci.setCiBricks(ci_bricks, index);

                ci_bricks_2 = ci.getCiBricks(index, length);

                //                for (int i=0; i<length; i++) {
                //                    ci_bricks_2.at(i).getContent() ==
                //                }
                //                QVERIFY(ci.ciBricksAreEqual(ci_bricks));

                qDebug() << index << ": " << length << ": " << index + length;
            }
        }

    }

    //    for (int i=0; i <= 255; i++) {
    //        qDebug() << i << ": " << ci_bricks_full.at(i).getContent() << " : " << ci_bricks_full.at(i).getMask();
    //    }
}

void CiTest::testRandomCiBricks()
{
    // CiBrick set/get all
    qDebug() << "CiBrick set/get all";

//    const QVector<CI_Brick> getCiBricks() const;
//    void setCiBricks(const QVector<CI_Brick> &value);


    ci_bricks.clear();

    rand = randByteUnique();
    randContent = randByteUnique();
    randMask = randByteUnique();

}


void CiTest::testPathFunctions()
{
    ci_bricks.clear();

    for (int i=0; i<=255; i++) {
        ci_bricks.append(CI_Brick(i));
//        qDebug() << ci_bricks.at(i).getContent();
    }
    ci.setCiBricks(ci_bricks);
//    qDebug() << ci.getFullPath();


    ci_bricks.clear();

    for (int i=0; i<=255; i++) {
        ci_bricks.append(CI_Brick(randByte()));
//        qDebug() << ci_bricks.at(randByteUnique()).getContent();
    }
    ci.setCiBricks(ci_bricks);

//    qDebug() << ci.getFullPath();

//    qDebug() << ci.getRoutingPath();

}



quint8 CiTest::randByte()
{

    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());

    return qrand() % 256;
}

quint8 CiTest::randByteUnique()
{
    quint8 rand_1 = randByte();
    quint8 rand_2 = randByte();

    while ( rand_1 == rand_2 ) {
        rand_2 = randByte();
    }

    return rand_2;
}



bool CiTest::ciBricksAreEqual(const QVector<CI_Brick> &value_1, const QVector<CI_Brick> &value_2) {

    if (value_1.size() != value_2.size()) {
        qDebug() << "value_1.size(): " << value_1.size();
        qDebug() << "value_2.size(): " << value_2.size();
        return false;
    }

    for (int i=0; i<value_1.size(); i++) {
        if ( ! ((CI_Brick) value_1.at(i) == (CI_Brick) value_2.at(i))) {
            return false;
        }
    }
    return true;
}


void CiTest::cleanupTestCase()
{
}

QTEST_APPLESS_MAIN(CiTest)

#include "tst_citest.moc"

