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

void MediaTest::testBasePath()
{
    QFETCH(QString, path);
    QFETCH(QString, result);
    Media m;
    m.setPath(path);

    QCOMPARE(m.basePath(), result);
}

void MediaTest::testRemovePath()
{
    QFETCH(QStringList, paths);
    QFETCH(int, count);
    QFETCH(QString, toRemove);
    QFETCH(bool, expected);

    Media m;

    for(auto it: paths) {
        m.setPath(it);
    }

    QCOMPARE(m.paths().count(), paths.count());
    QCOMPARE(m.removePath(toRemove), expected);
    QCOMPARE(m.paths().count(), count);

}

void MediaTest::testNbPath()
{
    QFETCH(QStringList, paths);
    QFETCH(int, count);

    Media m;

    for(auto it: paths) {
        m.setPath(it);
    }

    QCOMPARE(m.nbPath(), count);
}
void MediaTest::testIsAvailable()
{
    QFETCH(QStringList, paths);
    QFETCH(bool, expected);

    Media m;

    for(auto it: paths) {
        m.setPath(it);
    }

    QCOMPARE(m.isAvailable(), expected);
}

void MediaTest::testCount()
{
    QFAIL("Not implemented");
}

void MediaTest::testRating()
{
    QFAIL("Not implemented");
}

void MediaTest::testAdded()
{
    QFAIL("Not implemented");
}

void MediaTest::testLastFinish()
{
    QFAIL("Not implemented");
}

void MediaTest::testCurrentRead()
{
    QFAIL("Not implemented");
}

void MediaTest::testLastProbed()
{
    QFAIL("Not implemented");
}

void MediaTest::testTags()
{
    QFAIL("Not implemented");
}

void MediaTest::testHasTag()
{
    QFAIL("Not implemented");
}

void MediaTest::testReset()
{
    QFAIL("Not implemented");
}

void MediaTest::testMerge()
{
    QFAIL("Not implemented");
}

void MediaTest::testCreateMedia()
{
    QFAIL("Not implemented");
}

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

void MediaTest::testBasePath_data()
{
    QTest::addColumn<QString>("path");
    QTest::addColumn<QString>("result");

    QTest::addRow("porte.jpg")<<QString("c:/a/path/porte.jpg")<<QString("porte.jpg");
}

void MediaTest::testRemovePath_data()
{
    QTest::addColumn<QStringList>("paths");
    QTest::addColumn<int>("count");
    QTest::addColumn<QString>("toRemove");
    QTest::addColumn<bool>("expected");

    QTest::addRow("OK")<<QStringList{"c:/a/path/f1.jpg"}<<0<<QString("c:/a/path/f1.jpg")<<true;
    QTest::addRow("OK-2")<<QStringList{"c:/a/path/f1.jpg", "c:/a/path/f2.jpg"}<<1<<QString("c:/a/path/f1.jpg")<<true;
    QTest::addRow("NOK")<<QStringList{"c:/a/path/f1.jpg", "c:/a/path/f2.jpg"}<<2<<QString("c:/a/path/f3.jpg")<<false;

}

void MediaTest::testNbPath_data()
{
    QTest::addColumn<QStringList>("paths");
    QTest::addColumn<int>("count");

    QTest::addRow("1")<<QStringList{"c:/a/path/f1.jpg"}<<1;
    QTest::addRow("2")<<QStringList{"c:/a/path/f1.jpg", "c:/a/path/f2.jpg"}<<2;
    QTest::addRow("3")<<QStringList{"c:/a/path/f1.jpg", "c:/a/path/f2.jpg", "c:/a/path/f3.jpg"}<<3;
    QTest::addRow("4")<<QStringList{"c:/a/path/f1.jpg", "c:/a/path/f2.jpg", "c:/a/path/f3.jpg", "c:/a/path/f4.jpg"}<<4;
    QTest::addRow("4")<<QStringList{"c:/a/path/f1.jpg", "c:/a/path/f2.jpg", "c:/a/path/f3.jpg", "c:/a/path/f4.jpg", "c:/a/path/f1.jpg"}<<4;
}

void MediaTest::testIsAvailable_data()
{
    QTest::addColumn<QStringList>("paths");
    QTest::addColumn<bool>("expected");

    QTest::addRow("isAvailable")<<QStringList{QString(TESTDATA) + "porte_d_eternite.jpg"}<<true;
    QTest::addRow("isAvailable - 2")<<QStringList{"c:/a/path/f1.jpg", QString(TESTDATA) + "porte_d_eternite.jpg"}<<true;
    QTest::addRow("!isAvailable")<<QStringList{"c:/a/path/f1.jpg"}<<false;
}

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
