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
    QVector<CI_Brick> ci_bricks;

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
    ci_bricks.fill(ci_brick, 256);

    for (int i=1; i<=255; i++) {
        ci_bricks[i].setContent(i);
        ci_bricks[i].setMask(i);
    }
}

void CiTest::testGetterSetter()
{
    // CiType
    for (int i = 0; i<=255; i++) {
        ciType=i;
        ci.setCiType(i);

        QVERIFY2(ci.getCiType() == ciType, "ci.getCiType() == ciType");
    }

    // RootCIC
    for (int i=0; i<=255; i++) {
        ci_brick.setContent(i);

        for (int j = 0; j<=255; j++) {
            ci_brick.setMask(j);
            ci.setRootCIC(ci_brick);
            QVERIFY2(ci.getRootCIC() == ci_brick, "ci.getRootCIC() == ci_brick");
        }
    }

    // RootCicContent
    for (int i=0; i<=255; i++) {
        ci.setRootCicContent(i);
        QVERIFY2(ci.getRootCicContent() == i, "ci.getRootCicContent() == i");
    }

    // RootCicMask
    for (int i=0; i<=255; i++) {
        ci.setRootCicMask(i);
        QVERIFY2(ci.getRootCicMask() == i, "ci.getRootCicMask() == i");
    }

    // CiSize
    for (int i = 0; i<=255; i++) {
        ciSize=i;
        ci.setCiSize(i);

        QVERIFY2(ci.getCiSize() == ciSize, "ci.getCiSize() == ciSize");
    }

    // CI_Bricks()
    ci.setCI_Bricks(ci_bricks);
    for (int i=1; i<=255; i++) {
        // QVector<CI_Brick> getCI_Bricks()
        QVERIFY2(&(ci.getCI_Bricks().at(i)) == &(ci_bricks.at(i)), "&(ci.getCI_Bricks().at(i)) == &(ci_bricks.at(i)");
        QVERIFY2(ci.getCI_Bricks().at(i).getContent() == ci_bricks.at(i).getContent(), "ci.getCI_Bricks().at(i).getContent() == ci_bricks.at(i).getContent()");
        QVERIFY2(ci.getCI_Bricks().at(i).getMask() == ci_bricks.at(i).getMask(), "ci.getCI_Bricks().at(i).getMask() == ci_bricks.at(i).getMask()");

        // CI_Brick getCI_Bricks(quint8 index)
        QVERIFY2(ci.getCI_Bricks(i) == ci_bricks.at(i), "ci.getCI_Bricks(i) == ci_bricks.at(i)");
        QVERIFY2(ci.getCI_Bricks(i).getContent() == ci_bricks.at(i).getContent(), "ci.getCI_Bricks(i).getContent() == ci_bricks.at(i).getContent()");
        QVERIFY2(ci.getCI_Bricks(i).getMask() == ci_bricks.at(i).getMask(), "ci.getCI_Bricks(i).getMask() == ci_bricks.at(i).getMask()");
    }

    // CI_BrickContent
    for (int i=1; i<=255; i++) {
        ci.setCI_BrickContent(i, i);
        QVERIFY2(ci.getCI_Bricks().at(i).getContent() == i, "ci.getCI_Bricks().at(i).getContent() == i");
    }

    // CI_BrickMask
    for (int i=1; i<=255; i++) {
        ci.setCI_BrickMask(i, i);
        QVERIFY2(ci.getCI_Bricks().at(i).getMask() == i, "ci.getCI_Bricks().at(i).getMask() == i");
    }

    for (int i=1; i<=255; i++) {
        ci_brick_2.setContent(i);
        ci_brick_2.setMask(i);
        ci.setCI_Brick(ci_brick_2, i);

        QVERIFY2(ci.getCI_Bricks(i) == ci_brick_2, "ci.getCI_Bricks(i) == ci_brick_2");
    }



//    void setCI_Bricks(const QByteArray &value);
//    void setCI_Brick(const CI_Brick &value, quint8 index);
//    void truncateCI_Bricks(quint8 size);
}

void CiTest::cleanupTestCase()
{
}

QTEST_APPLESS_MAIN(CiTest)

#include "tst_citest.moc"
