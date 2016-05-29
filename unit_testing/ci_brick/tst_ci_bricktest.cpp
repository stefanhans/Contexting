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
    void cleanupTestCase();

private:
    quint8 content;
    quint8 mask;

    CI_Brick ci_brick;
    CI_Brick ci_brick_2;
};


Ci_brickTest::Ci_brickTest()
{
}

void Ci_brickTest::initTestCase()
{
}

void Ci_brickTest::testGetterSetter()
{
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
    ci_brick_2 = ci_brick;
    QVERIFY(ci_brick_2 == ci_brick);
}

void Ci_brickTest::testMaskFunctions()
{
    ci_brick.setMask(0);
    QVERIFY2(ci_brick.hasEmptyMask(), "hasEmptyMask() FAILED!");

    ci_brick.setMask(255);
    QVERIFY2(ci_brick.hasFullMask(), "hasFullMask() FAILED!");
}

void Ci_brickTest::testCompareFunctions()
{
    for (int i = 0; i<=255; i++) {
        ci_brick.setContent(i);
        QVERIFY2(ci_brick.contentMatch(i), "ci_brick.contentMatch(quint8)");
    }

    ci_brick.setContent(0);
    ci_brick.setMask(0);
    QVERIFY2(ci_brick.contextMatch(0, 0), "0,0: ci_brick.contentMatch(0, 0)"); // equal content
    QVERIFY2(ci_brick.contextMatch(0, 1), "0,0: ci_brick.contentMatch(0, 1)"); // equal content and other mask ignores

    ci_brick.setContent(0);
    ci_brick.setMask(1); // mask ignores
    QVERIFY2(ci_brick.contextMatch(0, 0), "0,1: ci_brick.contentMatch(0, 0)"); // equal content
    QVERIFY2(ci_brick.contextMatch(0, 1), "0,1: ci_brick.contentMatch(0, 1)"); // equal content and other mask ignores
    QVERIFY2(ci_brick.contextMatch(1, 1), "0,1: ci_brick.contentMatch(1, 1)"); // unequal content, but both masks ignore

    for (int i = 0; i<=255; i++) {
        ci_brick.setContent(i);
        ci_brick_2.setContent(i);
        QVERIFY2(ci_brick.contentMatch(ci_brick_2), "ci_brick.contentMatch(CI_Brick)");
    }

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

void Ci_brickTest::cleanupTestCase()
{
}



QTEST_APPLESS_MAIN(Ci_brickTest)

#include "tst_ci_bricktest.moc"