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
    void cleanupTestCase();

private:
    quint8 ciType;
    CI_Brick rootCIC;
    quint8 ciSize;
    QVector<CI_Brick> CI_Bricks;

    CI ci;


    quint8 content;
    quint8 mask;

    CI_Brick ci_brick;
    CI_Brick ci_brick_2;
};

CiTest::CiTest()
{
}

void CiTest::initTestCase()
{
}

void CiTest::testGetterSetter()
{
    for (int i = 0; i<=255; i++) {
        ciType=i;
        ci.setCiType(i);

        QVERIFY2(ci.getCiType() == ciType, "ci.getCiType() == ciType");
    }

    for (int i = 0; i<=255; i++) {
        ciSize=i;
        ci.setCiSize(i);

        QVERIFY2(ci.getCiSize() == ciSize, "ci.getCiSize() == ciSize");
    }

//    ci_brick.setContent(0);
//    ci_brick.setMask(1);
//    ci.setRootCIC(ci_brick);
//    QVERIFY2(ci.getRootCIC() == ci_brick, "ci.getRootCIC() == ci_brick");

//    ci.setRootCicContent(0);
//    ci_brick.setContent(0);
//    ci.setRootCicMask(0);
//    ci_brick.setMask(0);
//    QVERIFY2(ci.getRootCIC().getContent() == ci_brick.getContent(), "ci.getRootCIC().getContent() == ci_brick.getContent()");
//    QVERIFY2(ci.getRootCIC().getMask() == ci_brick.getMask(), "ci.getRootCIC().getMask() == ci_brick.getMask()");

//    ci.setRootCIC(ci_brick);
//    QVERIFY2(ci.getRootCIC().getContent() == ci_brick.getContent(), "ci.getRootCIC().getContent() == ci_brick.getContent()");
//    QVERIFY2(ci.getRootCIC().getMask() == ci_brick.getMask(), "ci.getRootCIC().getMask() == ci_brick.getMask()");

//    QVERIFY2(ci.getRootCIC().getContent() == ci_brick.getContent(), "ci.getRootCIC().getContent() == ci_brick.getContent()");
//    QVERIFY2(ci_brick == ci_brick, "ci_brick == ci_brick");
//    QVERIFY2(ci.getRootCIC() == ci_brick, "ci.getRootCIC() == ci_brick");

}

void CiTest::cleanupTestCase()
{
}

QTEST_APPLESS_MAIN(CiTest)

#include "tst_citest.moc"
