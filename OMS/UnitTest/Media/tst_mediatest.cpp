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
    void testMerge_added();
    void testMerge_count();
    void testMerge_lastProbed();
    void testMerge_lastFinish();
    void testMerge_paths();
    void testMerge_tags();
    void testMerge_currentRead();
    void testMerge_rating();
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
    void testMerge_added_data();
    void testMerge_count_data();
    void testMerge_lastProbed_data();
    void testMerge_lastFinish_data();
    void testMerge_paths_data();
    void testMerge_tags_data();
    void testMerge_currentRead_data();
    void testMerge_rating_data();
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
    QFETCH(int, count);
    Media m;
    QSignalSpy spy(&m, &Media::countChanged);

    m.setCount(count);
    QCOMPARE(spy.count(), 1);
    QCOMPARE(m.count(), count);
}

void MediaTest::testRating()
{
    QFETCH(int, rating);
    Media m;
    QSignalSpy spy(&m, &Media::ratingChanged);

    m.setRating(rating);
    QCOMPARE(spy.count(), 1);
    QCOMPARE(m.rating(), rating);
}

void MediaTest::testAdded()
{
    QFETCH(QDate, added);
    Media m;

    m.setAdded(added);

    QCOMPARE(m.added(), added);
}

void MediaTest::testLastFinish()
{
    QFETCH(QDateTime, lastFinish);
    Media m;
    QSignalSpy spy(&m, &Media::lastFinishChanged);

    m.setLastFinish(lastFinish);
    QCOMPARE(spy.count(), 1);
    QCOMPARE(m.lastFinish(), lastFinish);
}

void MediaTest::testCurrentRead()
{
    QFETCH(double, current);
    Media m;
    QSignalSpy spy(&m, &Media::currentReadChanged);

    m.setCurrentRead(current);
    QCOMPARE(spy.count(), 1);
    QCOMPARE(m.currentRead(), current);
}

void MediaTest::testLastProbed()
{
    QFETCH(QDateTime, lastProbed);
    Media m;
    QSignalSpy spy(&m, &Media::lastProbedChanged);

    m.setLastProbed(lastProbed);
    QCOMPARE(spy.count(), 1);
    QCOMPARE(m.lastProbed(), lastProbed);
}

void MediaTest::testTags()
{
    QFETCH(QStringList, tags);
    QFETCH(int, count);
    Media m;
    QSignalSpy spy(&m, &Media::tagsChanged);
    m.setTags(tags);
    QCOMPARE(spy.count(), 1);
    QCOMPARE(m.tags().count(), count);
    tags.sort();
    tags.removeDuplicates();
    QCOMPARE(m.tags(), tags);
}

void MediaTest::testHasTag()
{
    QFETCH(QStringList, tags);
    QFETCH(QString, tag);
    QFETCH(bool, expected);

    Media m;
    QSignalSpy spy(&m, &Media::tagsChanged);
    m.setTags(tags);
    QCOMPARE(spy.count(), 1);
    QCOMPARE(m.hasTag(tag), expected);
}

void MediaTest::testReset()
{
    QFETCH(int, count);
    QFETCH(QDateTime, lastFinish);
    QFETCH(double, currentRead);

    Media m;
    m.setCount(count);
    m.setLastFinish(lastFinish);
    m.setCurrentRead(currentRead);

    QCOMPARE(m.count(), count);
    QCOMPARE(m.lastFinish(), lastFinish);
    QCOMPARE(m.currentRead(), currentRead);

    m.reset();

    QCOMPARE(m.count(), 0);
    QCOMPARE(m.lastFinish(), QDateTime());
    QCOMPARE(m.currentRead(), 0);
}

void MediaTest::testMerge_added()
{
    QFETCH(MediaPointer, m1);
    QFETCH(MediaPointer, m2);
    QFETCH(QDate, added);

    m1->merge(m2);

    QCOMPARE(m1->added(), added);
}

void MediaTest::testMerge_count()
{
    QFETCH(MediaPointer, m1);
    QFETCH(MediaPointer, m2);
    QFETCH(int, count);

    m1->merge(m2);

    QCOMPARE(m1->count(), count);
}

void MediaTest::testMerge_lastProbed()
{
    QFETCH(MediaPointer, m1);
    QFETCH(MediaPointer, m2);
    QFETCH(QDateTime, lastProbed);

    m1->merge(m2);

    QCOMPARE(m1->lastProbed(), lastProbed);
}

void MediaTest::testMerge_lastFinish()
{
    QFETCH(MediaPointer, m1);
    QFETCH(MediaPointer, m2);
    QFETCH(QDateTime, lastFinish);

    m1->merge(m2);

    QCOMPARE(m1->lastFinish(), lastFinish);
}

void MediaTest::testMerge_paths()
{
    QFETCH(MediaPointer, m1);
    QFETCH(MediaPointer, m2);
    QFETCH(QStringList, paths);

    m1->merge(m2);

    QCOMPARE(m1->paths(), paths);
}

void MediaTest::testMerge_tags()
{
    QFETCH(MediaPointer, m1);
    QFETCH(MediaPointer, m2);
    QFETCH(QStringList, tags);

    m1->merge(m2);

    tags.sort();
    QCOMPARE(m1->tags(), tags);
}

void MediaTest::testMerge_currentRead()
{
    QFETCH(MediaPointer, m1);
    QFETCH(MediaPointer, m2);
    QFETCH(double, currentRead);

    m1->merge(m2);

    QCOMPARE(m1->currentRead(), currentRead);
}

void MediaTest::testMerge_rating()
{
    QFETCH(MediaPointer, m1);
    QFETCH(MediaPointer, m2);
    QFETCH(int, rating);

    m1->merge(m2);

    QCOMPARE(m1->rating(), rating);
}

void MediaTest::testCreateMedia()
{
    QFETCH(QString, path);

    auto m = Media::createMedia(path);

    QCOMPARE(m.isNull(), false);
    QCOMPARE(m->path(), path);
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

void MediaTest::testCount_data()
{
    QTest::addColumn<int>("count");
    QTest::addRow("Count 1")<<1;
    QTest::addRow("Count 2")<<2;
    QTest::addRow("Count 3")<<3;
    QTest::addRow("Count 4")<<4;
    QTest::addRow("Count 5")<<5;
}

void MediaTest::testRating_data()
{
    QTest::addColumn<int>("rating");
    QTest::addRow("Rating 1")<<1;
    QTest::addRow("Rating 2")<<2;
    QTest::addRow("Rating 3")<<3;
    QTest::addRow("Rating 4")<<4;
    QTest::addRow("Rating 5")<<5;
    QTest::addRow("Rating 6")<<6;
    QTest::addRow("Rating 7")<<7;
    QTest::addRow("Rating 8")<<8;
    QTest::addRow("Rating 9")<<9;
    QTest::addRow("Rating 10")<<10;
}

void MediaTest::testAdded_data()
{
    QTest::addColumn<QDate>("added");
    QTest::addRow("Added 1")<<QDate::fromString("31-05-2007", "dd-MM-yyyy");
    QTest::addRow("Added 2")<<QDate::fromString("07-09-2012", "dd-MM-yyyy");
    QTest::addRow("Added 3")<<QDate::fromString("12-12-2012", "dd-MM-yyyy");
    QTest::addRow("Added 4")<<QDate::fromString("25-01-2020", "dd-MM-yyyy");
    QTest::addRow("Added 5")<<QDate::fromString("30-03-2021", "dd-MM-yyyy");
}

void MediaTest::testLastFinish_data()
{
    QTest::addColumn<QDateTime>("lastFinish");
    QTest::addRow("Last finish 1")<<QDateTime::fromString("31-05-2007 12:12:12", "dd-MM-yyyy hh:mm:ss");
    QTest::addRow("Last finish 2")<<QDateTime::fromString("07-09-2012 13:40:27", "dd-MM-yyyy hh:mm:ss");
    QTest::addRow("Last finish 3")<<QDateTime::fromString("12-12-2012 01:03:37", "dd-MM-yyyy hh:mm:ss");
    QTest::addRow("Last finish 4")<<QDateTime::fromString("25-01-2020 10:52:18", "dd-MM-yyyy hh:mm:ss");
    QTest::addRow("Last finish 5")<<QDateTime::fromString("30-03-2021 09:42:42", "dd-MM-yyyy hh:mm:ss");
}

void MediaTest::testCurrentRead_data()
{
    QTest::addColumn<double>("current");
    QTest::addRow("Current read 1")<<10.0;
    QTest::addRow("Current read 2")<<27.3;
    QTest::addRow("Current read 3")<<90.1;
    QTest::addRow("Current read 4")<<67.3;
    QTest::addRow("Current read 5")<<42.42;
}

void MediaTest::testLastProbed_data()
{
    QTest::addColumn<QDateTime>("lastProbed");
    QTest::addRow("Last Probed 1")<<QDateTime::fromString("31-05-2007 12:12:12", "dd-MM-yyyy hh:mm:ss");
    QTest::addRow("Last Probed 2")<<QDateTime::fromString("07-09-2012 13:40:27", "dd-MM-yyyy hh:mm:ss");
    QTest::addRow("Last Probed 3")<<QDateTime::fromString("12-12-2012 01:03:37", "dd-MM-yyyy hh:mm:ss");
    QTest::addRow("Last Probed 4")<<QDateTime::fromString("25-01-2020 10:52:18", "dd-MM-yyyy hh:mm:ss");
    QTest::addRow("Last Probed 5")<<QDateTime::fromString("30-03-2021 09:42:42", "dd-MM-yyyy hh:mm:ss");
}

void MediaTest::testTags_data()
{
    QTest::addColumn<QStringList>("tags");
    QTest::addColumn<int>("count");
    QTest::addRow("Tags 1")<<QStringList{"T1"}<<1;
    QTest::addRow("Tags 2")<<QStringList{"T1", "T2"}<<2;
    QTest::addRow("Tags 3")<<QStringList{"T1", "T2", "T3"}<<3;
    QTest::addRow("Tags 4")<<QStringList{"T1", "T2", "T3", "T4"}<<4;
    QTest::addRow("Tags 5")<<QStringList{"T1", "T2", "T3", "T4", "T5"}<<5;
    QTest::addRow("Tags 6")<<QStringList{"T1", "T2", "T3", "T4", "T5", "T1"}<<5;
}

void MediaTest::testHasTag_data()
{
    QTest::addColumn<QStringList>("tags");
    QTest::addColumn<QString>("tag");
    QTest::addColumn<bool>("expected");

    QTest::addRow("Tags 1")<<QStringList{"T1"}<<QString("T1")<<true;
    QTest::addRow("Tags 2")<<QStringList{"T1", "T2"}<<QString("T1")<<true;
    QTest::addRow("Tags 3")<<QStringList{"T1", "T2"}<<QString("T2")<<true;
    QTest::addRow("Tags 4")<<QStringList{"T1", "T2"}<<QString("T3")<<false;
}

void MediaTest::testReset_data()
{
    QTest::addColumn<int>("count");
    QTest::addColumn<QDateTime>("lastFinish");
    QTest::addColumn<double>("currentRead");

    QTest::addRow("Reset 1")<<1<<QDateTime::fromString("23-06-2021 13:50:34", "dd-MM-yyyy hh:mm:ss")<<42.53;
}

void MediaTest::testMerge_added_data()
{
    QTest::addColumn<MediaPointer>("m1");
    QTest::addColumn<MediaPointer>("m2");
    QTest::addColumn<QDate>("added");

    auto m1 = MediaPointer::create();
    auto m2 = MediaPointer::create();
    auto m3 = MediaPointer::create();
    auto d1 = QDate::fromString("01-02-2020", "dd-MM-yyyy");
    auto d2 = QDate::fromString("02-02-2020", "dd-MM-yyyy");
    auto d3 = QDate::fromString("03-02-2020", "dd-MM-yyyy");
    m1->setAdded(d1);
    m2->setAdded(d2);
    m3->setAdded(d3);

    QTest::addRow("m1 - m2")<<m1<<m2<<d1;
    QTest::addRow("m3 - m2")<<m3<<m2<<d2;
    QTest::addRow("m3 - m1")<<m3<<m1<<d1;
}

void MediaTest::testMerge_count_data()
{
    QTest::addColumn<MediaPointer>("m1");
    QTest::addColumn<MediaPointer>("m2");
    QTest::addColumn<int>("count");

    auto m1 = MediaPointer::create();
    auto m2 = MediaPointer::create();
    auto m3 = MediaPointer::create();
    auto d1 = 1;
    auto d2 = 2;
    auto d3 = 3;
    m1->setCount(d1);
    m2->setCount(d2);
    m3->setCount(d3);

    QTest::addRow("m1 - m2")<<m1<<m2<<d2;
    QTest::addRow("m3 - m2")<<m3<<m2<<d3;
    QTest::addRow("m3 - m1")<<m3<<m1<<d3;
}

void MediaTest::testMerge_lastProbed_data()
{
    QTest::addColumn<MediaPointer>("m1");
    QTest::addColumn<MediaPointer>("m2");
    QTest::addColumn<QDateTime>("lastProbed");

    auto m1 = MediaPointer::create();
    auto m2 = MediaPointer::create();
    auto m3 = MediaPointer::create();
    auto d1 = QDateTime::fromString("01-02-2020 13:35:42", "dd-MM-yyyy hh:mm:ss");
    auto d2 = QDateTime::fromString("02-02-2020 13:35:42", "dd-MM-yyyy hh:mm:ss");
    auto d3 = QDateTime::fromString("03-02-2020 13:35:42", "dd-MM-yyyy hh:mm:ss");
    m1->setLastProbed(d1);
    m2->setLastProbed(d2);
    m3->setLastProbed(d3);

    QTest::addRow("m1 - m2")<<m1<<m2<<d2;
    QTest::addRow("m3 - m2")<<m3<<m2<<d3;
    QTest::addRow("m3 - m1")<<m3<<m1<<d3;
}

void MediaTest::testMerge_lastFinish_data()
{
    QTest::addColumn<MediaPointer>("m1");
    QTest::addColumn<MediaPointer>("m2");
    QTest::addColumn<QDateTime>("lastFinish");

    auto m1 = MediaPointer::create();
    auto m2 = MediaPointer::create();
    auto m3 = MediaPointer::create();
    auto d1 = QDateTime::fromString("01-02-2020 13:35:42", "dd-MM-yyyy hh:mm:ss");
    auto d2 = QDateTime::fromString("02-02-2020 13:35:42", "dd-MM-yyyy hh:mm:ss");
    auto d3 = QDateTime::fromString("03-02-2020 13:35:42", "dd-MM-yyyy hh:mm:ss");
    m1->setLastFinish(d1);
    m2->setLastFinish(d2);
    m3->setLastFinish(d3);

    QTest::addRow("m1 - m2")<<m1<<m2<<d2;
    QTest::addRow("m3 - m2")<<m3<<m2<<d3;
    QTest::addRow("m3 - m1")<<m3<<m1<<d3;
}

void MediaTest::testMerge_paths_data()
{
    QTest::addColumn<MediaPointer>("m1");
    QTest::addColumn<MediaPointer>("m2");
    QTest::addColumn<QStringList>("paths");

    auto m1 = MediaPointer::create();
    auto m2 = MediaPointer::create();
    auto m3 = MediaPointer::create();
    auto d1 = QString("c:/a/path/f1.jpg");
    auto d2 = QString("c:/a/path/f2.jpg");
    auto d3 = QString("c:/a/path/f3.jpg");
    m1->setPath(d1);
    m2->setPath(d2);
    m3->setPath(d3);

    QTest::addRow("m1 - m2")<<m1<<m2<<QSet<QString> {d1, d2}.values();
    QTest::addRow("m3 - m2")<<m3<<m2<<QSet<QString> {d2, d3}.values();
    QTest::addRow("m3 - m1")<<m3<<m1<<QSet<QString> {d1, d2, d3}.values();
}

void MediaTest::testMerge_tags_data()
{
    QTest::addColumn<MediaPointer>("m1");
    QTest::addColumn<MediaPointer>("m2");
    QTest::addColumn<QStringList>("tags");

    auto m1 = MediaPointer::create();
    auto m2 = MediaPointer::create();
    auto m3 = MediaPointer::create();
    auto d1 = QString("T1");
    auto d2 = QString("T2");
    auto d3 = QString("T3");
    m1->setTag(d1);
    m2->setTag(d2);
    m3->setTag(d3);

    QTest::addRow("m1 - m2")<<m1<<m2<<QSet<QString> {d1, d2}.values();
    QTest::addRow("m3 - m2")<<m3<<m2<<QSet<QString> {d3, d2}.values();
    QTest::addRow("m3 - m1")<<m3<<m1<<QSet<QString> {d1, d2, d3}.values();
}

void MediaTest::testMerge_currentRead_data()
{
    QTest::addColumn<MediaPointer>("m1");
    QTest::addColumn<MediaPointer>("m2");
    QTest::addColumn<double>("currentRead");

    auto m1 = MediaPointer::create();
    auto m2 = MediaPointer::create();
    auto m3 = MediaPointer::create();
    auto d1 = 1.2;
    auto d2 = 2.2;
    auto d3 = 3.2;
    m1->setCurrentRead(d1);
    m2->setCurrentRead(d2);
    m3->setCurrentRead(d3);

    QTest::addRow("m1 - m2")<<m1<<m2<<d2;
    QTest::addRow("m3 - m2")<<m3<<m2<<d3;
    QTest::addRow("m3 - m1")<<m3<<m1<<d3;
}

void MediaTest::testMerge_rating_data()
{
    QTest::addColumn<MediaPointer>("m1");
    QTest::addColumn<MediaPointer>("m2");
    QTest::addColumn<int>("rating");

    auto m1 = MediaPointer::create();
    auto m2 = MediaPointer::create();
    auto m3 = MediaPointer::create();
    auto d1 = 1;
    auto d2 = 2;
    auto d3 = 3;
    m1->setRating(d1);
    m2->setRating(d2);
    m3->setRating(d3);

    QTest::addRow("m1 - m2")<<m1<<m2<<d2;
    QTest::addRow("m3 - m2")<<m3<<m2<<d3;
    QTest::addRow("m3 - m1")<<m3<<m1<<d3;
}

void MediaTest::testCreateMedia_data()
{
    QTest::addColumn<QString>("path");
    QTest::addRow("Create 1")<<QString("c:/a/path/f1.jpg");
}


QTEST_APPLESS_MAIN(MediaTest)

#include "tst_mediatest.moc"
