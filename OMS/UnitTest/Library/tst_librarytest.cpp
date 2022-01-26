#include "Model/library.h"
#include <QSignalSpy>
#include <QtTest>

// add necessary includes here

class LibraryTest : public QObject {
	Q_OBJECT

public:
	LibraryTest();
	~LibraryTest();

private slots:
	void initTestCase();
	void cleanupTestCase();

    void idTest();
    void idTest_data();
    void nameTest();
    void nameTest_data();
    void roleTest();
    void roleTest_data();
    void isSharedTest();
    void isSharedTest_data();
    void addSourceDirTest();
    void addSourceDirTest_data();
    void removeSourceDirTest();
    void removeSourceDirTest_data();
    void addMediaTest();
    void addMediaTest_data();
    void removeMediaTest();
    void removeMediaTest_data();
    void addPlaylistTest();
    void addPlaylistTest_data();
    void addSmartPlaylistTest();
    void addSmartPlaylistTest_data();
    void addTagTest();
    void addTagTest_data();
    void removeTagTest();
    void removeTagTest_data();
    void editTagTest();
    void editTagTest_data();
    void tagListTest();
    void tagListTest_data();
    void onProbedChangedTest();
    void onProbedChangedTest_data();
    void onMediasChangedTest();
    void onMediasChangedTest_data();
    void onSmartPlaylistChangedTest();
    void onSmartPlaylistChangedTest_data();
};

LibraryTest::LibraryTest() {}

LibraryTest::~LibraryTest() {}

void LibraryTest::initTestCase() {}

void LibraryTest::cleanupTestCase() {}

void LibraryTest::idTest()
{
    QFETCH(QUuid, id);
    Library l;

    l.setId(id);
    QCOMPARE(l.id(), id);
}

void LibraryTest::idTest_data()
{
    QTest::addColumn<QUuid>("id");

    QTest::addRow("1")<<QUuid::createUuid();
    QTest::addRow("2")<<QUuid::createUuid();
    QTest::addRow("3")<<QUuid::createUuid();
    QTest::addRow("4")<<QUuid::createUuid();
    QTest::addRow("5")<<QUuid::createUuid();
}

void LibraryTest::nameTest()
{
    QFETCH(QString, name);
    Library l;

    QSignalSpy spy(&l, &Library::nameChanged);

    l.setName(name);
    QCOMPARE(spy.count(), 1);
    QCOMPARE(l.name(), name);
}

void LibraryTest::nameTest_data()
{
    QTest::addColumn<QString>("name");

    QTest::addRow("Name 1")<<QString("Library unit test 1");
    QTest::addRow("Name 2")<<QString("Library unit test 2");
    QTest::addRow("Name 3")<<QString("Library unit test 3");
    QTest::addRow("Name 4")<<QString("Library unit test 4");
    QTest::addRow("Name 5")<<QString("Library unit test 5");
}

void LibraryTest::roleTest()
{
    QFETCH(MediaPlayerGlobal::MediaRole, role);
    Library l;

    l.setRole(role);
    QCOMPARE(l.role(), role);
}

void LibraryTest::roleTest_data()
{
    QTest::addColumn<MediaPlayerGlobal::MediaRole>("role");

    QTest::addRow("Undefined")<<MediaPlayerGlobal::MediaRole::Undefined;
    QTest::addRow("Comics")<<MediaPlayerGlobal::MediaRole::Comics;
    QTest::addRow("Video")<<MediaPlayerGlobal::MediaRole::Video;
    QTest::addRow("Audio")<<MediaPlayerGlobal::MediaRole::Audio;
    QTest::addRow("Book")<<MediaPlayerGlobal::MediaRole::Books;
    QTest::addRow("Game")<<MediaPlayerGlobal::MediaRole::Game;
    QTest::addRow("Image")<<MediaPlayerGlobal::MediaRole::Image;
}

void LibraryTest::isSharedTest()
{
    QFETCH(bool, isShared);
    Library l;

    QSignalSpy spy(&l, &Library::isSharedChanged);

    l.setShared(isShared);
    QCOMPARE(spy.count(), 1);
    QCOMPARE(l.isShared(), isShared);
}

void LibraryTest::isSharedTest_data()
{
    QTest::addColumn<bool>("isShared");

    QTest::addRow("True")<<true;
    QTest::addRow("False")<<false;
}

void LibraryTest::addSourceDirTest()
{
    QFETCH(QStringList, paths);
    QFETCH(int, count);

    Library l;
    QSignalSpy spy(&l, &Library::sourceDirChanged);

    for(auto path: paths)
       l.addSourceDir(path);

    QCOMPARE(spy.count(), count);
    QCOMPARE(l.sourceDir().count(), count);
    paths.removeDuplicates();
    QCOMPARE(l.sourceDir(), paths);
}

void LibraryTest::addSourceDirTest_data()
{
    QTest::addColumn<QStringList>("paths");
    QTest::addColumn<int>("count");

    QTest::addRow("Source dir 1")<<QStringList{"Path 1"}<<1;
    QTest::addRow("Source dir 2")<<QStringList{"Path 1", "Path 2"}<<2;
    QTest::addRow("Source dir 2.1")<<QStringList{"Path 1", "Path 2", "Path 1"}<<2;
}

void LibraryTest::removeSourceDirTest()
{
    QFETCH(QStringList, paths);
    QFETCH(QString, toRemove);
    QFETCH(int, count);
    QFETCH(bool, expected);

    Library l;
    for(auto it: paths)
        l.addSourceDir(it);

    QSignalSpy spy(&l, &Library::sourceDirChanged);
    QCOMPARE(l.removeSourceDir(toRemove), expected);
    QCOMPARE(spy.count(), expected ? 1 : 0);
    QCOMPARE(l.sourceDir().count(), count);
    paths.removeAll(toRemove);
    paths.removeDuplicates();
    QCOMPARE(l.sourceDir(), paths);
}

void LibraryTest::removeSourceDirTest_data()
{
    QTest::addColumn<QStringList>("paths");
    QTest::addColumn<QString>("toRemove");
    QTest::addColumn<int>("count");
    QTest::addColumn<bool>("expected");

    QTest::addRow("Source dir 1")<<QStringList{"Path 1"}<<QString("Path 1")<<0<<true;
    QTest::addRow("Source dir 2")<<QStringList{"Path 1", "Path 2"}<<QString("Path 2")<<1<<true;
    QTest::addRow("Source dir 3")<<QStringList{"Path 1", "Path 2", "Path 1"}<<QString("Path 3")<<2<<false;
}

void LibraryTest::addMediaTest()
{
    QFETCH(QList<QUuid>, medias);
    QFETCH(int, count);

    Library l;
    QSignalSpy spy(&l, &Library::mediasChanged);

    for(auto it: medias) {
        auto m = factory<Media>(it);
        l.addMedia(m);
    }

    QCOMPARE(spy.count(), medias.count());
    QCOMPARE(l.mediaCount(), count);
}

void LibraryTest::addMediaTest_data()
{
    QTest::addColumn<QList<QUuid>>("medias");
    QTest::addColumn<int>("count");

    auto m1 = QUuid::createUuid();
    auto m2 = QUuid::createUuid();

    QTest::addRow("Add media 1")<<QList<QUuid>{m1}<<1;
    QTest::addRow("Add media 2")<<QList<QUuid>{m1, m2}<<2;
    QTest::addRow("Add media 3")<<QList<QUuid>{m1, m2, m1}<<2;
}

void LibraryTest::removeMediaTest()
{
    QFETCH(QList<QUuid>, medias);
    QFETCH(QUuid, remove);
    QFETCH(int, count);
    QFETCH(bool, expected);

    Library l;
    for(auto it: medias) {
        auto m = factory<Media>(it);
        l.addMedia(m);
    }

    QSignalSpy spy(&l, &Library::mediasChanged);
    QCOMPARE(l.removeMedia(remove.toString()), expected);
    QCOMPARE(spy.count(), expected ? 1 : 0);
    QCOMPARE(l.mediaCount(), count);
}

void LibraryTest::removeMediaTest_data()
{
    QTest::addColumn<QList<QUuid>>("medias");
    QTest::addColumn<QUuid>("remove");
    QTest::addColumn<int>("count");
    QTest::addColumn<bool>("expected");

    auto m1 = QUuid::createUuid();
    auto m2 = QUuid::createUuid();
    auto m3 = QUuid::createUuid();

    QTest::addRow("Remove media 1")<<QList<QUuid>{m1}<<m1<<0<<true;
    QTest::addRow("Remove media 2")<<QList<QUuid>{m1, m2}<<m1<<1<<true;
    QTest::addRow("Remove media 3")<<QList<QUuid>{m1, m2}<<m3<<2<<false;
}

void LibraryTest::addPlaylistTest()
{
    QFAIL("Not implemented");
}

void LibraryTest::addPlaylistTest_data() {}

void LibraryTest::addSmartPlaylistTest()
{
    QFAIL("Not implemented");
}

void LibraryTest::addSmartPlaylistTest_data() {}

void LibraryTest::addTagTest()
{
    QFAIL("Not implemented");
}

void LibraryTest::addTagTest_data() {}

void LibraryTest::removeTagTest()
{
    QFAIL("Not implemented");
}

void LibraryTest::removeTagTest_data() {}

void LibraryTest::editTagTest()
{
    QFAIL("Not implemented");
}

void LibraryTest::editTagTest_data() {}

void LibraryTest::tagListTest()
{
    QFAIL("Not implemented");
}

void LibraryTest::tagListTest_data() {}

void LibraryTest::onProbedChangedTest()
{
    QFAIL("Not implemented");
}

void LibraryTest::onProbedChangedTest_data() {}

void LibraryTest::onMediasChangedTest()
{
    QFAIL("Not implemented");
}

void LibraryTest::onMediasChangedTest_data() {}

void LibraryTest::onSmartPlaylistChangedTest()
{
    QFAIL("Not implemented");
}

void LibraryTest::onSmartPlaylistChangedTest_data() {}

QTEST_APPLESS_MAIN(LibraryTest)

#include "tst_librarytest.moc"
