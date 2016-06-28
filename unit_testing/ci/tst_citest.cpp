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

    for (int l=1; l<=255; l++) {

        ci_bricks.clear();

        for (int j=0; j<l; j++) {

            ci_bricks.append(CI_Brick(j, l));
        }

        ci.setCiBricks(ci_bricks);

        QVERIFY(ci.ciBricksAreEqual(ci_bricks));
    }

    // CiBrick set/get index/length
    qDebug() << "CiBrick set/get index/length";

    for (int l=1; l<=255; l++) {

        for (int j=0; j<l; j++) {

            randContent = randByte();
            randMask = randByte();

            ci_bricks.append(CI_Brick(randContent, randMask));
        }

        for (int i=0; i<l-ci_bricks.size(); i++) {

            qDebug() << "Length" << l << "Index" << i;

            ci.setCiBricks(ci_bricks, i);

            QVERIFY(ci.getCiBricks().size() >= ci_bricks.size());

            ci_bricks_2 = ci.getCiBricks(i, l);

            QVERIFY(ci_bricks_2.size() == ci_bricks.size());


            for (int j=0; j<ci_bricks.size(); j++) {

                QVERIFY(&(ci_bricks_2.at(j)) == &(ci_bricks.at(j)));

                QVERIFY(ci_bricks_2.at(j).getContent() == ci_bricks.at(j).getContent());
                QVERIFY(ci_bricks_2.at(j).getMask() == ci_bricks.at(j).getMask());
            }
        }
    }

    // appendCiBricks
    qDebug() << "appendCiBricks";

    for (int l=1; l<=2; l++) {
        qDebug() << "for l" << l;

        ci_bricks.clear();

        for (int j=0; j<l; j++) {

            randContent = randByte();
            randMask = randByte();

            ci_bricks.append(CI_Brick(randContent, randMask));
        }

        for (int m=0; m<=2-l; m++) {
            qDebug() << "for m" << m;

            ci_bricks_2.clear();
            ci_bricks_2.fill(CI_Brick(), m);
            ci_bricks_empty.clear();
            ci.setCiBricks(ci_bricks_empty);
            ci.setCiBricks(ci_bricks_2);

            qDebug() << ci.getCiBricks().size();
            qDebug() << ci_bricks_2.size() + ci_bricks.size();

            ci.setCiBricks(ci_bricks, ci_bricks_2.size()-1);


            QVERIFY(ci.getCiBricks().size() == ci_bricks_2.size() + ci_bricks.size());
            QVERIFY(ci.getCiBricks(m, l).size() == ci_bricks.size());


            for (int j=0; j<l; j++) {
                qDebug() << "for j" << j;

//                QVERIFY(&(ci.getCiBricks(m, l).at(j)) == &(ci_bricks.at(j)));

                QVERIFY(ci.getCiBricks(m, l).at(j).getContent() == ci_bricks.at(j).getContent());
                QVERIFY(ci.getCiBricks(m, l).at(j).getMask() == ci_bricks.at(j).getMask());

            }
            qDebug() << "----------";
        }


        // ciBricksAreEqual
        qDebug() << "ciBricksAreEqual";

        for (int r=1; r<=255; r++) {

            ci_bricks.clear();

            for (int j=0; j<=r; j++) {

                randContent = randByte();
                randMask = randByte();

                ci_bricks.append(CI_Brick(randContent, randMask));
            }

//            ci.updateCiBricks(ci_bricks);
            QVERIFY(ci.ciBricksAreEqual(ci_bricks));
        }

        // Empty ciBricksAreEqual
        ci_bricks.clear();
//        ci.updateCiBricks(ci_bricks);
        QVERIFY(ci.ciBricksAreEqual(ci_bricks));
    }


    // CiBrick get/set
    qDebug() << "CiBrick get/set";
//    CI_Brick getCiBrick(quint8 index) const;
//    void setCiBrick(const CI_Brick &value, quint8 index);

    // CiBrickContent get/set
    qDebug() << "CiBrickContent get/set";
//    quint8 getCiBrickContent(quint8 index);
//    void setCiBrickContent(const quint8 content, quint8 index);

    // CiBrickMask get/set
    qDebug() << "CiBrickMask get/set";
//    quint8 getCiBrickMask(quint8 index);
//    void setCiBrickMask(const quint8 mask, quint8 index);

    // resizeCiBricks
    qDebug() << "resizeCiBricks";
    for (int i = 0; i<=255; i++) {
        ciSize=i;

        ci.setCiSize(i);
//        ci.resizeCiBricks();
        QVERIFY(ci.getCiBricks().size() == i);
    }
}

void CiTest::testRandomCiBricks()
{
    // CiBrick set/get all
    qDebug() << "CiBrick set/get all";
//    const QVector<CI_Brick> getCiBricks() const;
//    void setCiBricks(const QVector<CI_Brick> &value);


    // setCiBricks
    qDebug() << "setCiBricks";
    for (int i=0; i<10; i++) {

        rand = randByte();

        for (int j=0; j<rand; j++) {
            randContent = randByte();
            randMask = randByte();

            ci_bricks.append(CI_Brick(randContent, randMask));
        }

//        ci.updateCiBricks(ci_bricks);

        QVERIFY(ci.getCiBricks().size() == ci_bricks.size());

        QVERIFY(ci.ciBricksAreEqual(ci_bricks));

        for (int j=0; j<ci_bricks.size(); j++) {
            QVERIFY(&(ci.getCiBricks().at(i)) == &(ci_bricks.at(i)));

            QVERIFY(ci.getCiBricks().at(j).getContent() == ci_bricks.at(j).getContent());
            QVERIFY(ci.getCiBricks().at(j).getMask() == ci_bricks.at(j).getMask());
        }
    }

    // CiBrick set/get index/length
    qDebug() << "CiBrick set/get index/length";
//    const QVector<CI_Brick> getCiBricks(quint8 index, quint8 length) const;
//    void setCiBricks(const QVector<CI_Brick> &value, quint8 index);

    // appendCiBricks
    qDebug() << "appendCiBricks";
//    void appendCiBricks(const QVector<CI_Brick> &value);

    // CiBrick get/set
    qDebug() << "CiBrick get/set";
//    CI_Brick getCiBrick(quint8 index) const;
//    void setCiBrick(const CI_Brick &value, quint8 index);

    // CiBrickContent get/set
    qDebug() << "CiBrickContent get/set";
//    quint8 getCiBrickContent(quint8 index);
//    void setCiBrickContent(const quint8 content, quint8 index);

    // CiBrickMask get/set
    qDebug() << "CiBrickMask get/set";
//    quint8 getCiBrickMask(quint8 index);
//    void setCiBrickMask(const quint8 mask, quint8 index);

    // resizeCiBricks
    qDebug() << "resizeCiBricks";
    for (int i=0; i<1000; i++) {

        ci_bricks_full.clear();
        ci_bricks_full.fill(ci_brick, 256);

//        ci.updateCiBricks(ci_bricks_full);

        rand = randByte();
        ci.setCiSize(rand);
//        ci.resizeCiBricks();

        QVERIFY(ci.getCiBricks().size() == rand);
    }


    // ciBricksAreEqual
    qDebug() << "ciBricksAreEqual";

    for (int r=1; r<=10; r++) {

        ci_bricks.clear();

        rand = randByte();

        for (int j=0; j<=rand; j++) {

            randContent = randByteUnique();
            randMask = randByteUnique();

            ci_bricks.append(CI_Brick(randContent, randMask));
        }

        ci.setCiBricks(ci_bricks);
        QVERIFY(ci.ciBricksAreEqual(ci_bricks));
    }
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


void CiTest::cleanupTestCase()
{
}

QTEST_APPLESS_MAIN(CiTest)

#include "tst_citest.moc"

