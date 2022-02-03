#include <QTest>
#include <QDebug>

#include <Model/libraryprobe.h>

class LibraryProbeTest: public QObject
{
    Q_OBJECT

public:
    LibraryProbeTest() = default;
    ~LibraryProbeTest() = default;

private slots:
    void initTestCase();
    void cleanupTestCase();

    void isValidTest();
    void isValidTest_data();
    void lastProbedTest();
    void lastProbedTest_data();

};

void LibraryProbeTest::initTestCase() {}
void LibraryProbeTest::cleanupTestCase() {}

void LibraryProbeTest::isValidTest()
{
    QFETCH(QStringList, exts);
    QFETCH(QString, path);
    QFETCH(bool, expected);

    LibraryProbe probe;
    probe.setFilters(exts);

    QCOMPARE(probe.isValid(path), expected);
}

void LibraryProbeTest::isValidTest_data()
{
    QTest::addColumn<QStringList>("exts");
    QTest::addColumn<QString>("path");
    QTest::addColumn<bool>("expected");

    QTest::addRow("Is valid 1")<<QStringList{"jpg"}<<QStringLiteral("c:/a/path/file.jpg")<<true;
    QTest::addRow("Is valid 1")<<QStringList{"jpg"}<<QStringLiteral("c:/a/path/file.avi")<<false;
    QTest::addRow("Is valid 1")<<QStringList{"jpg", "avi"}<<QStringLiteral("c:/a/path/file.avi")<<true;
}

void LibraryProbeTest::lastProbedTest()
{
    QFAIL("Not implemented");
}


void LibraryProbeTest::lastProbedTest_data() {}

QTEST_APPLESS_MAIN(LibraryProbeTest)

#include "tst_libraryprobe.moc"
