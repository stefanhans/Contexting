#include <QString>
#include <QtTest>

#include "ci_brick.h"

class Ci_brickTest : public QObject
{
    Q_OBJECT

public:
    Ci_brickTest();

private Q_SLOTS:
    void initTestCase();
    void testGetterSetter();
    void testCopyAndAssignment();
    void testMaskFunctions();
    void testCompareFunctions();
    void testStringFunctions();
    void testRandomStringFunctions();
    void cleanupTestCase();

private:
    quint8 content;
    quint8 mask;

    CI_Brick ci_brick;
    CI_Brick ci_brick_2;

    quint8 rand;
    quint8 randContent;
    quint8 randMask;

    quint8 randByte();
    quint8 randByteUnique();
};


Ci_brickTest::Ci_brickTest()
{
}

void Ci_brickTest::initTestCase()
{
}


void Ci_brickTest::testGetterSetter()
{    
    //quint8 getContent() const;
    //void setContent(const quint8 &value);

    //quint8 getMask() const;
    //void setMask(const quint8 &value);

    for (int i = 0; i<=255; i++) {
        content=i;
        ci_brick.setContent(i);

        for (int j = 0; j<=255; j++) {
            mask=j;
            ci_brick.setMask(j);

            QVERIFY(ci_brick.getContent() == content);
            QVERIFY(ci_brick.getMask() == mask);
        }
    }
}


void Ci_brickTest::testCopyAndAssignment()
{   
    //bool operator==(const CI_Brick &ci_brick);

    ci_brick_2 = ci_brick;
    QVERIFY(ci_brick_2 == ci_brick);
}


void Ci_brickTest::testMaskFunctions()
{    
    //bool hasEmptyMask() const;

    ci_brick.setMask(0);
    QVERIFY(ci_brick.hasEmptyMask());

    for (int i = 1; i<=255; i++) {
        ci_brick.setMask(i);
        QVERIFY( ! ci_brick.hasEmptyMask());
    }


    //bool hasFullMask() const;

    ci_brick.setMask(255);
    QVERIFY(ci_brick.hasFullMask());

    for (int i = 0; i<255; i++) {
        ci_brick.setMask(i);
        QVERIFY( ! ci_brick.hasFullMask());
    }
}


void Ci_brickTest::testCompareFunctions()
{
    //bool contentMatch(quint8 otherContent) const;

    for (int i = 0; i<=255; i++) {
        ci_brick.setContent(i);
        QVERIFY(ci_brick.contentMatch(i));
    }


    //bool contextMatch(quint8 otherContent, quint8 otherMask) const;

    ci_brick.setContent(0);
    ci_brick.setMask(0);
    QVERIFY2(ci_brick.contextMatch(0, 0), "0,0: ci_brick.contentMatch(0, 0)"); // equal content
    QVERIFY2(ci_brick.contextMatch(0, 1), "0,0: ci_brick.contentMatch(0, 1)"); // equal content and other mask ignores

    ci_brick.setContent(0);
    ci_brick.setMask(1); // mask ignores
    QVERIFY2(ci_brick.contextMatch(0, 0), "0,1: ci_brick.contentMatch(0, 0)"); // equal content
    QVERIFY2(ci_brick.contextMatch(0, 1), "0,1: ci_brick.contentMatch(0, 1)"); // equal content and other mask ignores
    QVERIFY2(ci_brick.contextMatch(1, 1), "0,1: ci_brick.contentMatch(1, 1)"); // unequal content, but both masks ignore


    //bool contentMatch(CI_Brick otherBrick) const;

    for (int i = 0; i<=255; i++) {
        ci_brick.setContent(i);
        ci_brick_2.setContent(i);
        QVERIFY(ci_brick.contentMatch(ci_brick_2));
    }


    //bool contextMatch(CI_Brick otherBrick) const;

    ci_brick.setContent(0);
    ci_brick.setMask(0);
    ci_brick_2.setContent(0);
    ci_brick_2.setMask(0);
    QVERIFY2(ci_brick.contextMatch(ci_brick_2), "0,0: ci_brick.contentMatch(CI_Brick - 0, 0)"); // equal content
    ci_brick_2.setMask(1);
    QVERIFY2(ci_brick.contextMatch(0, 1), "0,0: ci_brick.contentMatch(CI_Brick - 0, 1)"); // equal content and other mask ignores

    ci_brick.setContent(0);
    ci_brick.setMask(1); // mask ignores
    ci_brick_2.setContent(0);
    ci_brick_2.setMask(0);
    QVERIFY2(ci_brick.contextMatch(ci_brick_2), "0,1: ci_brick.contentMatch(CI_Brick - 0, 0)"); // equal content
    ci_brick_2.setMask(1);
    QVERIFY2(ci_brick.contextMatch(ci_brick_2), "0,1: ci_brick.contentMatch(CI_Brick - 0, 1)"); // equal content and other mask ignores
    ci_brick_2.setContent(1);
    QVERIFY2(ci_brick.contextMatch(ci_brick_2), "0,1: ci_brick.contentMatch(CI_Brick - 1, 1)"); // unequal content, but both masks ignore
}


void Ci_brickTest::testStringFunctions()
{
    for (int i = 0; i<=255; i++) {
        ci_brick.setContent(i);

        for (int j = 0; j <= 255; j++) {

            ci_brick.setMask(j);

            bool ok;


            //QString contentToHex() const;
            //QString maskToHex() const;

            QVERIFY(((quint8) ci_brick.contentToHex().toUInt(&ok, 16)) == i);
            QVERIFY(((quint8) ci_brick.maskToHex().toUInt(&ok, 16)) == j);


            //QString contentToBinary() const;
            //QString maskToBinary() const;

            QVERIFY(((quint8) ci_brick.contentToBinary().toUInt(&ok, 2)) == i);
            QVERIFY(((quint8) ci_brick.maskToBinary().toUInt(&ok, 2)) == j);


            //QString contentToPath() const;

            QVERIFY(ci_brick.contentToPath() == ci_brick.contentToHex().at(0) + '/' + ci_brick.contentToHex().at(1));


            //QString contextToRoute() const;

            QString route;
            if(ci_brick.maskToHex().at(0) == '0') {
                route += ci_brick.contentToHex().at(0);

                if(ci_brick.maskToHex().at(1) == '0') {
                    route += ci_brick.contentToHex().at(1);
                }
            }
            QVERIFY(ci_brick.contextToRoute() == route);


            //QString contextToRoutePath() const;

            route.clear();
            if(ci_brick.maskToHex().at(0) == '0') {
                route += ci_brick.contentToHex().at(0);

                if(ci_brick.maskToHex().at(1) == '0') {
                    route += '/' + ci_brick.contentToHex().at(1);
                }
            }
            QVERIFY(ci_brick.contextToRoutePath() == route);
        }
    }
}


void Ci_brickTest::testRandomStringFunctions()
{
    for (int i=0; i<100; i++) {

        randContent = randByteUnique();
        randMask = randByteUnique();

        ci_brick.setContent(randContent);
        ci_brick.setMask(randMask);
        bool ok;


        //QString contentToHex() const;
        //QString maskToHex() const;

        QVERIFY(((quint8) ci_brick.contentToHex().toUInt(&ok, 16)) == randContent);
        QVERIFY(((quint8) ci_brick.maskToHex().toUInt(&ok, 16)) == randMask);


        //QString contentToBinary() const;
        //QString maskToBinary() const;

        QVERIFY(((quint8) ci_brick.contentToBinary().toUInt(&ok, 2)) == randContent);
        QVERIFY(((quint8) ci_brick.maskToBinary().toUInt(&ok, 2)) == randMask);


        //QString contentToPath() const;

        QVERIFY(ci_brick.contentToPath() == ci_brick.contentToHex().at(0) + '/' + ci_brick.contentToHex().at(1));


        //QString contextToRoute() const;

        QString route;
        if(ci_brick.maskToHex().at(0) == '0') {
            route += ci_brick.contentToHex().at(0);

            if(ci_brick.maskToHex().at(1) == '0') {
                route += ci_brick.contentToHex().at(1);
            }
        }
        QVERIFY(ci_brick.contextToRoute() == route);


        //QString contextToRoutePath() const;

        route.clear();
        if(ci_brick.maskToHex().at(0) == '0') {
            route += ci_brick.contentToHex().at(0);

            if(ci_brick.maskToHex().at(1) == '0') {
                route += '/' + ci_brick.contentToHex().at(1);
            }
        }
        QVERIFY(ci_brick.contextToRoutePath() == route);

    }
}


quint8 Ci_brickTest::randByte()
{

    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());

    return qrand() % 256;
}

quint8 Ci_brickTest::randByteUnique()
{
    quint8 rand_1 = randByte();
    quint8 rand_2 = randByte();

    while ( rand_1 == rand_2 ) {
        rand_2 = randByte();
    }

    return rand_2;
}

void Ci_brickTest::cleanupTestCase()
{
}



QTEST_APPLESS_MAIN(Ci_brickTest)

#include "tst_ci_bricktest.moc"

