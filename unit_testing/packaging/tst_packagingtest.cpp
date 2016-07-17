#include <QString>
#include <QtTest>

class PackagingTest : public QObject
{
    Q_OBJECT

public:
    PackagingTest();

private Q_SLOTS:
    void testCase1();
};

PackagingTest::PackagingTest()
{
}

void PackagingTest::testCase1()
{
    QVERIFY2(true, "Failure123    ");
}

QTEST_APPLESS_MAIN(PackagingTest)

#include "tst_packagingtest.moc"
