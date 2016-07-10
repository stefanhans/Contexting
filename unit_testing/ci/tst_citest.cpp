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
    void testContextFunctions();
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

    quint8 randByte(int limit=256);
    quint8 randByteUnique();

    QVector<quint8> testMasks;
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

    testMasks.append(0);
    testMasks.append(1);
    testMasks.append(128);

    testInts.append(0);
    testInts.append(1);
    testInts.append(2);
    testInts.append(3);
    testInts.append(4);
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
//    QSKIP("OKAY");

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
//    QSKIP("OKAY");

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
//    QSKIP("OKAY");

    // CiBrick index=0
    qDebug() << "CiBrick index=0";

    for (int l=0; l<=255; l++) {

        ci_bricks.clear();
        ci.setCiBricks(ci_bricks_full);

        ci_bricks.fill(ci_brick_all_1, l);
        ci.setCiBricks(ci_bricks);
        ci.setCiSize(ci_bricks.size());

        QVERIFY(ciBricksAreEqual((QVector<CI_Brick>) ci.getCiBricks(), ci_bricks));
    }

    // CiBrick
    qDebug() << "CiBrick";

    quint8 randIndex;

    foreach(quint8 length, testInts) {

        if(length < 255) {
            randIndex = randByte(255-length);
        }
        else {
            randIndex = 0;
        }

        ci_bricks.clear();
        ci.setCiBricks(ci_bricks_full);

        for (int i=0; i<length; i++) {
            ci_brick.setContent(randByteUnique());
            ci_brick.setMask(randByteUnique());
            ci_bricks.append(ci_brick);
        }

        ci.setCiBricks(ci_bricks, randIndex);

//        qDebug() << "length: " << length << " randIndex: " << randIndex;
//        qDebug() << "ci_brick.size: " << ci_bricks.size() << " ci.size: " << ci.getCiSize();

        QVERIFY(ciBricksAreEqual(ci_bricks, ci.getCiBricks(randIndex, length)));

    }
}

void CiTest::testContextFunctions()
{
    //    QSKIP("OKAY");

    /*
     * QString getContextContent() const
     */
    qDebug() << "QString getContextContent() const;";

    QString context;

    foreach(quint8 length, testInts) {

        context.clear();
        ci_bricks.clear();

        for (int i=0; i<length; i++) {
            rand = randByteUnique();

            context += QString("%1").arg(rand, 2, 16, QLatin1Char('0'));

            ci_brick.setContent(rand);
            ci_bricks.append(ci_brick);

        }
        ci.setCiBricks(ci_bricks);

        //        qDebug() << "context: " << context;
        //        qDebug() << "ci.getContextContent(): " << ci.getContextContent();

        QVERIFY(context == ci.getContextContent());
    }

    /*
     * QString getContextRoute() const
     */
    qDebug() << "QString getContextRoute() const;";

    QString path, route;
    quint8 mask;


    mask = 0;
//    qDebug() << "\nmask: " << mask;

    foreach(quint8 length, testInts) {

        path.clear();
        route.clear();
        ci_bricks.clear();

        for (int i=0; i<length; i++) {

            rand = randByteUnique();

            path += QString("%1").arg(rand, 2, 16, QLatin1Char('0')).at(0);
            path += QString("%1").arg(rand, 2, 16, QLatin1Char('0')).at(1);

            ci_brick.setContent(rand);
            ci_brick.setMask(0);

            ci_bricks.append(ci_brick);
        }
        ci.setCiBricks(ci_bricks);

        route = path;

//        qDebug() << "route: " << route;
//        qDebug() << "ci.getContextRoute(): " << ci.getContextRoute();

        QVERIFY(route == ci.getContextRoute());
    }


    mask = 1;
//    qDebug() << "\nmask: " << mask;

    foreach(quint8 length, testInts) {

        path.clear();
        route.clear();
        ci_bricks.clear();

        for (int i=0; i<length; i++) {
            rand = randByteUnique();

            path += QString("%1").arg(rand, 2, 16, QLatin1Char('0')).at(0);

            ci_brick.setContent(rand);
            ci_brick.setMask(0);

            if (i == length/2) {
                ci_brick.setMask(mask);

                route = path;
            }
            path += QString("%1").arg(rand, 2, 16, QLatin1Char('1')).at(1);

            ci_bricks.append(ci_brick);
        }

        ci.setCiBricks(ci_bricks);

//        qDebug() << "route: " << route;
//        qDebug() << "ci.getContextRoute(): " << ci.getContextRoute();

        QVERIFY(route == ci.getContextRoute());
    }


    mask = 128;
//    qDebug() << "\nmask: " << mask;

    foreach(quint8 length, testInts) {

        path.clear();
        route.clear();
        ci_bricks.clear();

        for (int i=0; i<length; i++) {
            rand = randByteUnique();

            ci_brick.setContent(rand);
            ci_brick.setMask(0);

            if (i == length/2) {
                ci_brick.setMask(mask);

                route = path;
            }

            path += QString("%1").arg(rand, 2, 16, QLatin1Char('0')).at(0);
            path += QString("%1").arg(rand, 2, 16, QLatin1Char('1')).at(1);

            ci_bricks.append(ci_brick);
        }
        ci.setCiBricks(ci_bricks);

//        qDebug() << "route: " << route;
//        qDebug() << "ci.getContextRoute(): " << ci.getContextRoute();

        QVERIFY(route == ci.getContextRoute());
    }
}


void CiTest::testPathFunctions()
{
//    QSKIP("OKAY");

    /*
     * QString getFullPath(const QChar delim='/') const
     */
    qDebug() << "QString getFullPath(const QChar delim='/') const";

    QString path;

    foreach(quint8 length, testInts) {

        path.clear();
        ci_bricks.clear();

        for (int i=0; i<length; i++) {
            rand = randByteUnique();

            path += QString("%1").arg(rand, 2, 16, QLatin1Char('0')).at(0) + '/' + QString("%1").arg(rand, 2, 16, QLatin1Char('0')).at(1) + '/';

            ci_brick.setContent(rand);
            ci_bricks.append(ci_brick);
        }
        ci.setCiBricks(ci_bricks);

        //        qDebug() << "path: " << path;
        //        qDebug() << "ci.getFullPath(): " << ci.getFullPath();

        QVERIFY(path == ci.getFullPath());
    }


    /*
     * QString getRoutingPath(const QChar delim='/') const
     */
    qDebug() << "QString getRoutingPath(const QChar delim='/') const";

    QString route;
    quint8 mask;


    mask = 0;
//    qDebug() << "\nmask: " << mask;

    foreach(quint8 length, testInts) {

        path.clear();
        route.clear();
        ci_bricks.clear();

        for (int i=0; i<length; i++) {
            rand = randByteUnique();

            ci_brick.setContent(rand);
            ci_brick.setMask(0);

            ci_bricks.append(ci_brick);

            path += QString("%1").arg(rand, 2, 16, QLatin1Char('0')).at(0);
            path += "/";
            path += QString("%1").arg(rand, 2, 16, QLatin1Char('0')).at(1);
            path += "/";
        }
        ci.setCiBricks(ci_bricks);

        route = path;

//        qDebug() << "route: " << route;
//        qDebug() << "ci.getRoutingPath(): " << ci.getRoutingPath();

        QVERIFY(route == ci.getRoutingPath());
    }


    mask = 1;
//    qDebug() << "\nmask: " << mask;

    foreach(quint8 length, testInts) {

        path.clear();
        route.clear();
        ci_bricks.clear();

        for (int i=0; i<length; i++) {
            rand = randByteUnique();

            ci_brick.setContent(rand);

            path += QString("%1").arg(rand, 2, 16, QLatin1Char('0')).at(0);
            path += "/";

            ci_brick.setMask(0);

            if (i == length/2) {
                ci_brick.setMask(mask);

                route = path;
            }
            path += QString("%1").arg(rand, 2, 16, QLatin1Char('1')).at(1);
            path += "/";

            ci_bricks.append(ci_brick);
        }

        ci.setCiBricks(ci_bricks);

//        qDebug() << "route: " << route;
//        qDebug() << "ci.getRoutingPath(): " << ci.getRoutingPath();

        QVERIFY(route == ci.getRoutingPath());
    }


    mask = 128;
//    qDebug() << "\nmask: " << mask;

    foreach(quint8 length, testInts) {

        path.clear();
        route.clear();
        ci_bricks.clear();

        for (int i=0; i<length; i++) {
            rand = randByteUnique();

            ci_brick.setContent(rand);
            ci_brick.setMask(0);

            if (i == length/2) {
                ci_brick.setMask(mask);

                route = path;
            }

            path += QString("%1").arg(rand, 2, 16, QLatin1Char('0')).at(0);
            path += "/";
            path += QString("%1").arg(rand, 2, 16, QLatin1Char('1')).at(1);
            path += "/";

            ci_bricks.append(ci_brick);
        }

        ci.setCiBricks(ci_bricks);

//        qDebug() << "route: " << route;
//        qDebug() << "ci.getRoutingPath(): " << ci.getRoutingPath();

        QVERIFY(route == ci.getRoutingPath());
    }
}



quint8 CiTest::randByte(int limit)
{

    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());

    return qrand() % limit;
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
        qDebug() << "ciBricksAreEqual size: " << value_1.size() << " != " << value_2.size();
        return false;
    }

    for (int i=0; i<value_1.size(); i++) {
        if ( ! ((CI_Brick) value_1.at(i) == (CI_Brick) value_2.at(i))) {
            qDebug() << "ciBricksAreEqual at(" << i << ") content: " << ((CI_Brick) value_1.at(i)).getContent() << " != " << ((CI_Brick) value_2.at(i)).getContent();
            qDebug() << "ciBricksAreEqual at(" << i << ") mask: " << ((CI_Brick) value_1.at(i)).getMask() << " != " << ((CI_Brick) value_2.at(i)).getMask();
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

