#include <QTest>
#include <QDebug>
#include <QSignalSpy>

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
    void scanTest();
    void scanTest_data();
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
    QTest::addRow("Is valid 2")<<QStringList{"jpg"}<<QStringLiteral("c:/a/path/file.avi")<<false;
    QTest::addRow("Is valid 3")<<QStringList{"jpg", "avi"}<<QStringLiteral("c:/a/path/file.avi")<<true;
}

void LibraryProbeTest::lastProbedTest()
{
    QFETCH(QDateTime, lastProbed);

    LibraryProbe probe;
    QSignalSpy spy(&probe, &LibraryProbe::lastProbedChanged);

    probe.setLastProbed(lastProbed);
    QCOMPARE(spy.count(), 1);
    QCOMPARE(probe.lastProbed(), lastProbed);
}


void LibraryProbeTest::lastProbedTest_data()
{
    QTest::addColumn<QDateTime>("lastProbed");

    QTest::addRow("Last probed 1")<<QDateTime::fromString("02-09-2015 02:15:32", "dd-MM-yyyy hh:mm:ss");
    QTest::addRow("Last probed 2")<<QDateTime::fromString("02-03-2015 02:15:32", "dd-MM-yyyy hh:mm:ss");
    QTest::addRow("Last probed 3")<<QDateTime::fromString("02-09-2020 02:15:32", "dd-MM-yyyy hh:mm:ss");
    QTest::addRow("Last probed 4")<<QDateTime::fromString("02-09-2015 02:45:32", "dd-MM-yyyy hh:mm:ss");
    QTest::addRow("Last probed 5")<<QDateTime::fromString("02-09-2015 18:15:32", "dd-MM-yyyy hh:mm:ss");
}

void LibraryProbeTest::scanTest()
{
    QFETCH(QStringList, sources);
    QFETCH(int, expectedCount);

    LibraryProbe probe;
    probe.setSourceDir(sources);
    probe.setFilters({"jpg"});
    QSignalSpy currentChanged(&probe, &LibraryProbe::currentChanged);
    QSignalSpy mediaFind(&probe, &LibraryProbe::mediaFind);

    auto result = probe.probe();

    QTest::qWait(10000);
//    result.waitForFinished();

    QCOMPARE(mediaFind.count(), expectedCount);
    QCOMPARE(currentChanged.count(), expectedCount);
    QCOMPARE(probe.current(), 100.0);
}

void LibraryProbeTest::scanTest_data()
{
    QTest::addColumn<QStringList>("sources");
    QTest::addColumn<int>("expectedCount");

    QTest::addRow("Probe 1")<<QStringList{TESTDATA}<<13;
    QTest::addRow("Probe 2")<<QStringList{TESTDATA, TESTDATA}<<13;
}

QTEST_APPLESS_MAIN(LibraryProbeTest)

#include "tst_libraryprobe.moc"
