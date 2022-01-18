#include "Model/media.h"
#include <QSignalSpy>
#include <QtTest>
#include <QStringList>

// add necessary includes here

class MediaTest : public QObject
{
    Q_OBJECT


public:
    MediaTest();
    ~MediaTest();

private slots:
    void initTestCase();
    void cleanupTestCase();

    void testId();
    void testFingerprint();
    void testRole();
    void testPaths();
    void testPath();
    void testBasePath();
    void testRemovePath();
    void testNbPath();
    void testIsAvailable();
    void testCount();
    void testRating();
    void testAdded();
    void testLastFinish();
    void testCurrentRead();
    void testLastProbed();
    void testTags();
    void testHasTag();
    void testReset();
    void testMerge();
    void testCreateMedia();
    void testId_data();
    void testFingerprint_data();
    void testRole_data();
    void testPaths_data();
    void testPath_data();
    void testBasePath_data();
    void testRemovePath_data();
    void testNbPath_data();
    void testIsAvailable_data();
    void testCount_data();
    void testRating_data();
    void testAdded_data();
    void testLastFinish_data();
    void testCurrentRead_data();
    void testLastProbed_data();
    void testTags_data();
    void testHasTag_data();
    void testReset_data();
    void testMerge_data();
    void testCreateMedia_data();
};

MediaTest::MediaTest()
{

}

MediaTest::~MediaTest()
{

}

void MediaTest::initTestCase()
{

}

void MediaTest::cleanupTestCase()
{

}

void MediaTest::testId()
{
    QFETCH(QUuid, id);
    Media m;

    m.setId(id);
    QCOMPARE(m.id(), id);
}

void MediaTest::testFingerprint()
{
    QFETCH(MD5, content);
    Media m;

    m.setFingerprint(content);
    QCOMPARE(m.fingerprint(), content);
}

void MediaTest::testRole()
{
    QFETCH(MediaPlayerGlobal::MediaRole, role);
    Media m;

    m.setRole(role);
    QCOMPARE(m.role(), role);
}

void MediaTest::testPaths()
{
    QFETCH(QStringList, paths);
    QFETCH(bool, ret);
    QFETCH(int, count);
    Media m;

    QSignalSpy spy(&m, &Media::isAvailableChanged);

    auto test = true;
    for(auto it: paths) {
        test &= m.setPath(it);
    }

    QSet<QString> expected(paths.begin(), paths.end());
    auto temp = m.paths();
    QSet<QString> result(temp.begin(), temp.end());

    QCOMPARE(test, ret);
    QCOMPARE(spy.count(), count);
    QCOMPARE(result, expected);
}

void MediaTest::testPath()
{
    QFETCH(QStringList, paths);
    QFETCH(bool, ret);
    QFETCH(int, count);

    Media m;

    QSignalSpy spy(&m, &Media::isAvailableChanged);

    auto test = true;
    for(auto it: paths) {
        test &= m.setPath(it);
    }

    QCOMPARE(test, ret);
    QCOMPARE(spy.count(), count);
    QSet<QString> expected(paths.begin(), paths.end());
    auto temp = *expected.begin();

    QCOMPARE(m.path(), temp);
}

void MediaTest::testBasePath(){}
void MediaTest::testRemovePath(){}
void MediaTest::testNbPath(){}
void MediaTest::testIsAvailable(){}
void MediaTest::testCount(){}
void MediaTest::testRating(){}
void MediaTest::testAdded(){}
void MediaTest::testLastFinish(){}
void MediaTest::testCurrentRead(){}
void MediaTest::testLastProbed(){}
void MediaTest::testTags(){}
void MediaTest::testHasTag(){}
void MediaTest::testReset(){}
void MediaTest::testMerge(){}
void MediaTest::testCreateMedia(){}
void MediaTest::testId_data()
{
    QTest::addColumn<QUuid>("id");

    QTest::addRow("1")<<QUuid::createUuid();
    QTest::addRow("2")<<QUuid::createUuid();
    QTest::addRow("3")<<QUuid::createUuid();
    QTest::addRow("4")<<QUuid::createUuid();
    QTest::addRow("5")<<QUuid::createUuid();
}

void MediaTest::testFingerprint_data()
{
    QTest::addColumn<MD5>("content");

    QFile file(QStringLiteral(TESTDATA) + "porte_d_eternite.jpg");
    file.open(QIODevice::ReadOnly);
    QCryptographicHash hash(QCryptographicHash::Md5);
    hash.addData(&file);
    auto md = hash.result();
    file.close();
    QTest::addRow("porte d eternite")<<md;
}

void MediaTest::testRole_data()
{
    QTest::addColumn<MediaPlayerGlobal::MediaRole>("role");

    QTest::addRow("Undefined")<<MediaPlayerGlobal::MediaRole::Undefined;
    QTest::addRow("Comics")<<MediaPlayerGlobal::MediaRole::Comics;
    QTest::addRow("Image")<<MediaPlayerGlobal::MediaRole::Image;
    QTest::addRow("Video")<<MediaPlayerGlobal::MediaRole::Video;
    QTest::addRow("Audio")<<MediaPlayerGlobal::MediaRole::Audio;
    QTest::addRow("Books")<<MediaPlayerGlobal::MediaRole::Books;
    QTest::addRow("Game")<<MediaPlayerGlobal::MediaRole::Game;
}

void MediaTest::testPaths_data()
{
    QTest::addColumn<QStringList>("paths");
    QTest::addColumn<bool>("ret");
    QTest::addColumn<int>("count");

    QTest::addRow("Paths 1")<<QStringList{"c:/a/path.jpg"}<<true<<1;
    QTest::addRow("Paths 2")<<QStringList{"c:/a/path.jpg", "c:/a/path2.jpg"}<<true<<2;
    QTest::addRow("Paths 3")<<QStringList{"c:/a/path.jpg", "c:/a/path2.jpg", "c:/a/path3.jpg"}<<true<<3;
    QTest::addRow("Paths 4")<<QStringList{"c:/a/path.jpg", "c:/a/path2.jpg", "c:/a/path3.jpg", "c:/a/path4.jpg"}<<true<<4;
    QTest::addRow("Paths 5")<<QStringList{"c:/a/path.jpg", "c:/a/path2.jpg", "c:/a/path3.jpg", "c:/a/path4.jpg", "c:/a/path5.jpg"}<<true<<5;
    QTest::addRow("Paths 5 bis")<<QStringList{"c:/a/path.jpg", "c:/a/path2.jpg", "c:/a/path3.jpg", "c:/a/path4.jpg", "c:/a/path5.jpg", "c:/a/path.jpg"}<<false<<5;
}

void MediaTest::testPath_data()
{
    QTest::addColumn<QStringList>("paths");
    QTest::addColumn<bool>("ret");
    QTest::addColumn<int>("count");

    QTest::addRow("Paths 1")<<QStringList{"c:/a/path.jpg"}<<true<<1;
    QTest::addRow("Paths 2")<<QStringList{"c:/a/path.jpg", "c:/a/path2.jpg"}<<true<<2;
    QTest::addRow("Paths 3")<<QStringList{"c:/a/path.jpg", "c:/a/path2.jpg", "c:/a/path3.jpg"}<<true<<3;
    QTest::addRow("Paths 4")<<QStringList{"c:/a/path.jpg", "c:/a/path2.jpg", "c:/a/path3.jpg", "c:/a/path4.jpg"}<<true<<4;
    QTest::addRow("Paths 5")<<QStringList{"c:/a/path.jpg", "c:/a/path2.jpg", "c:/a/path3.jpg", "c:/a/path4.jpg", "c:/a/path5.jpg"}<<true<<5;
    QTest::addRow("Paths 5 bis")<<QStringList{"c:/a/path.jpg", "c:/a/path2.jpg", "c:/a/path3.jpg", "c:/a/path4.jpg", "c:/a/path5.jpg", "c:/a/path.jpg"}<<false<<5;
}

void MediaTest::testBasePath_data(){}
void MediaTest::testRemovePath_data(){}
void MediaTest::testNbPath_data(){}
void MediaTest::testIsAvailable_data(){}
void MediaTest::testCount_data(){}
void MediaTest::testRating_data(){}
void MediaTest::testAdded_data(){}
void MediaTest::testLastFinish_data(){}
void MediaTest::testCurrentRead_data(){}
void MediaTest::testLastProbed_data(){}
void MediaTest::testTags_data(){}
void MediaTest::testHasTag_data(){}
void MediaTest::testReset_data(){}
void MediaTest::testMerge_data(){}
void MediaTest::testCreateMedia_data(){}


QTEST_APPLESS_MAIN(MediaTest)

#include "tst_mediatest.moc"
