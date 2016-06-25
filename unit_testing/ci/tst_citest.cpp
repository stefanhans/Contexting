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

        for (int j=0; j<l; j++) {

            randContent = randByte();
            randMask = randByte();

            ci_bricks.append(CI_Brick(randContent, randMask));
        }

        ci.setCiBricks(ci_bricks);

        QVERIFY(ci.ciBricksAreEqual(ci_bricks));

//        QVERIFY(ci.getCiBricks().size() == ci_bricks.size());

//        for (int j=0; j<ci_bricks.size(); j++) {

//            QVERIFY(&(ci.getCiBricks().at(j)) == &(ci_bricks.at(j)));

//            QVERIFY(ci.getCiBricks().at(j).getContent() == ci_bricks.at(j).getContent());
//            QVERIFY(ci.getCiBricks().at(j).getMask() == ci_bricks.at(j).getMask());
//        }
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
            ci.setCiBricks(ci_bricks_2);

            ci.appendCiBricks(ci_bricks);


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

            ci.setCiBricks(ci_bricks);
            QVERIFY(ci.ciBricksAreEqual(ci_bricks));
        }

        // Empty ciBricksAreEqual
        ci_bricks.clear();
        ci.setCiBricks(ci_bricks);
        QVERIFY(ci.ciBricksAreEqual(ci_bricks));





//        for (int i=0; i<l-ci_bricks.size(); i++) {

//            qDebug() << "Length" << l << "Index" << i;

//            ci.setCiBricks(ci_bricks, i);

//            QVERIFY(ci.getCiBricks().size() >= ci_bricks.size());

//            ci_bricks_2 = ci.getCiBricks(i, l);

//            QVERIFY(ci_bricks_2.size() == ci_bricks.size());


//            for (int j=0; j<ci_bricks.size(); j++) {

//                QVERIFY(&(ci_bricks_2.at(j)) == &(ci_bricks.at(j)));

//                QVERIFY(ci_bricks_2.at(j).getContent() == ci_bricks.at(j).getContent());
//                QVERIFY(ci_bricks_2.at(j).getMask() == ci_bricks.at(j).getMask());
//            }
//        }
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
        ci.resizeCiBricks();
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

        ci.setCiBricks(ci_bricks);

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

        ci.setCiBricks(ci_bricks_full);

        rand = randByte();
        ci.setCiSize(rand);
        ci.resizeCiBricks();

        QVERIFY(ci.getCiBricks().size() == rand);
    }


    // ciBricksAreEqual
    qDebug() << "ciBricksAreEqual";

    for (int r=1; r<=1000; r++) {

        ci_bricks.clear();

        rand = randByte();

        for (int j=0; j<=rand; j++) {

            randContent = randByte();
            randMask = randByte();

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
        qDebug() << ci_bricks.at(i).getContent();
    }
    ci.setCiBricks(ci_bricks);
    qDebug() << ci.getFullPath();


    ci_bricks.clear();

    for (int i=0; i<=255; i++) {
        ci_bricks.append(CI_Brick(randByte()));
        qDebug() << ci_bricks.at(randByte()).getContent();
    }
    ci.setCiBricks(ci_bricks);
    qDebug() << ci.getFullPath();

    qDebug() << ci.getRoutingPath();
}



quint8 CiTest::randByte()
{

    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());

    return qrand() % 256;
}

void CiTest::cleanupTestCase()
{
}

QTEST_APPLESS_MAIN(CiTest)

#include "tst_citest.moc"



//    for (int i = 255; i>=0; i--) {

//        ci.setCiSize(i);
//        ci.resizeCiBricks();

//        QVERIFY2(ci.getCiBricks().size() == i, "(--) ci.getCI_Bricks().size() == i");
//    }

//    ci_bricks.fill(CI_Brick(), 256);
//    ci.setCiBricks(ci_bricks);

//    QVERIFY2(ci.getCiBricks().size() == 256, "ci.getCiBricks().size() == 256");

//    for (int i=0; i <=255; i++) {
//        QVERIFY2(ci.getCiBrickContent(i) == 0, "ci.getCiBrickContent(i) == 0");
//    }

//    ci_bricks.clear();
//    ci_bricks.fill(CI_Brick(1, 1), 1);
//    qDebug() << "ci_bricks.size(): " << ci_bricks.size();
//    qDebug() << "ci_bricks.at(0).getContent(): " << ci_bricks.at(0).getContent();
//    qDebug() << "ci_bricks.at(0).getMask(): " << ci_bricks.at(0).getMask();

//    qDebug() << "ci.getCiBricks().size(): " << ci.getCiBricks().size();
//    qDebug() << "ci.getCiBrickContent(0): " << ci.getCiBrickContent(0);
//    qDebug() << "ci.getCiBrickMask(0): " << ci.getCiBrickMask(0);

//    ci.setCiBricks(ci_bricks, 0);
//    qDebug() << "ci.getCiBricks().size(): " << ci.getCiBricks().size();
//    qDebug() << "ci.getCiBrickContent(0): " << ci.getCiBrickContent(0);
//    qDebug() << "ci.getCiBrickMask(0): " << ci.getCiBrickMask(0);
//    qDebug() << "ci.getCiBrickContent(1): " << ci.getCiBrickContent(1);
//    qDebug() << "ci.getCiBrickMask(1): " << ci.getCiBrickMask(1);

//    QVERIFY(ci.getCiBrickContent(0) == ci_bricks.at(0).getContent());
//    QVERIFY(ci.getCiBrickMask(0) == ci_bricks.at(0).getMask());

//    ci_bricks.clear();
//    ci_bricks.fill(CI_Brick(28, 1), 1);
//    ci.setCiBricks(ci_bricks, 0);
//    QVERIFY((CI_Brick) ci.getCiBricks().at(0) == (CI_Brick) ci_bricks.at(0));



//    ci_bricks.clear();
//    ci_bricks.fill(CI_Brick(1, 1), randByte());

//    ci.setCiBricks(ci_bricks);
//    qDebug() << "ci.getCiBricks().size(): " << ci.getCiBricks().size();





//    QVERIFY2(false, "CI_Brick getCiBrick(quint8 index) const;");
//    QVERIFY2(false, "void setCiBrick(const CI_Brick &value, quint8 index);");

//    QVERIFY2(false, "quint8 getCiBrickContent(quint8 index);");
//    QVERIFY2(false, "void setCiBrickContent(const quint8 &value, quint8 index);");

//    QVERIFY2(false, "quint8 getCiBrickMask(quint8 index);");
//    QVERIFY2(false, "void setCiBrickMask(const quint8 &value, quint8 index);");









//    for (int i=0; i<=255; i++) {

//        QVERIFY((CI_Brick) ci.getCiBricks().at(i) == (CI_Brick) ci_bricks.at(0));
//    }


////    for (int i=0; i <=255; i++) {

//    int i=1;
//    qDebug() << "i: " << i;
//        ci_bricks.clear();
//        ci_bricks.fill(CI_Brick(1, 1), i);
//        qDebug() << "ci_bricks.size(): " << ci_bricks.size();
//        qDebug() << "ci_bricks.at(i): " << ci_bricks.at(0).getContent();
//        qDebug() << "ci_bricks.at(i): " << ci_bricks.at(1).getContent();

//        for (int j=0; j <=2; j++) {
//            qDebug() << "j: " << j;
//            ci.setCiBricks(ci_bricks, j);

//            qDebug() << "ci.getCiBrickContent(j): " << ci.getCiBrickContent(j);

//            for (int k=0; k<=255; k++) {
//                qDebug() << "k: " << k;

//                if (k<j) {
//                    qDebug() << "ci.getCiBrickContent(k): " << ci.getCiBrickContent(k);
//                    QVERIFY2(ci.getCiBrickContent(k) == 0, "ci.getCiBrickContent(k) == 0");
//                }
//            }
//            ci.getCiBricks().clear();
//            ci.getCiBricks().fill(CI_Brick(), 256);
//            qDebug() << "##################################################";
//        }
////    }



    //    for (int i=0; i<=255; i++) {
    //        byteArr->append((quint8) i);
    //    }
    //    ci.getCI_Bricks().clear();

    //    qDebug() << "byteArr->size(): " << byteArr->size();
    //    ci.setCI_Bricks(*byteArr);


    //    for (int i=0; i<=255; i++) {
    //        qDebug() << "byteArr.at(i): " << QString("%1 %2").arg(i).arg((quint8) byteArr->at(i));
    //    }




//    qDebug() << "\n------------------------------------------------------------------------------------------";

//    // CI_Bricks()
//    ci.setCiBricks(ci_bricks);
//    for (int i=1; i<=255; i++) {

//        // QVector<CI_Brick> getCI_Bricks()
//        QVERIFY2(&(ci.getCiBricks().at(i)) == &(ci_bricks.at(i)), "&(ci.getCI_Bricks().at(i)) == &(ci_bricks.at(i)");
//        QVERIFY2(ci.getCiBricks().at(i).getContent() == ci_bricks.at(i).getContent(), "ci.getCI_Bricks().at(i).getContent() == ci_bricks.at(i).getContent()");
//        QVERIFY2(ci.getCiBricks().at(i).getMask() == ci_bricks.at(i).getMask(), "ci.getCI_Bricks().at(i).getMask() == ci_bricks.at(i).getMask()");

//        // CI_Brick getCI_Bricks(quint8 index)
//        QVERIFY2(ci.getCiBrick(i) == ci_bricks.at(i), "ci.getCI_Bricks(i) == ci_bricks.at(i)");
//        QVERIFY2(ci.getCiBrick(i).getContent() == ci_bricks.at(i).getContent(), "ci.getCI_Bricks(i).getContent() == ci_bricks.at(i).getContent()");
//        QVERIFY2(ci.getCiBrick(i).getMask() == ci_bricks.at(i).getMask(), "ci.getCI_Bricks(i).getMask() == ci_bricks.at(i).getMask()");
//    }

//    for (int i=1; i<=255; i++) {
//        ci_brick_2.setContent(i);
//        ci_brick_2.setMask(i);
//        ci.setCiBrick(ci_brick_2, i);

//        QVERIFY2(ci.getCiBrick(i) == ci_brick_2, "ci.getCI_Bricks(i) == ci_brick_2");
//    }

//    // CI_BrickContent
//    for (int i=1; i<=255; i++) {
//        ci.setCiBrickContent(i, i);
//        QVERIFY2(ci.getCiBricks().at(i).getContent() == i, "ci.getCI_Bricks().at(i).getContent() == i");
//    }

//    // CI_BrickMask
//    for (int i=1; i<=255; i++) {
//        ci.setCiBrickMask(i, i);
//        QVERIFY2(ci.getCiBricks().at(i).getMask() == i, "ci.getCI_Bricks().at(i).getMask() == i");
//    }
