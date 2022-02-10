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
    void removePlaylistTest();
    void removePlaylistTest_data();
    void removeSmartPlaylistTest();
    void removeSmartPlaylistTest_data();
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
    void addToPlaylistTest();
    void addToPlaylistTest_data();
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
    QFETCH(QList<QUuid>, playlist);
    QFETCH(int, count);

    Library l;
    QSignalSpy spy(&l, &Library::playlistCountChanged);

    for(auto it: playlist) {
        auto m = factory<PlayList>();
        m->setId(it);
        l.addPlaylist(m);
    }

    QCOMPARE(spy.count(), count);
    QCOMPARE(l.playlistCount(), count);
}

void LibraryTest::addPlaylistTest_data()
{
    QTest::addColumn<QList<QUuid>>("playlist");
    QTest::addColumn<int>("count");

    auto m1 = QUuid::createUuid();
    auto m2 = QUuid::createUuid();

    QTest::addRow("Add playlist 1")<<QList<QUuid>{m1}<<1;
    QTest::addRow("Add playlist 2")<<QList<QUuid>{m1, m2}<<2;
    QTest::addRow("Add playlist 3")<<QList<QUuid>{m1, m2, m1}<<2;
}

void LibraryTest::addSmartPlaylistTest()
{
    QFETCH(QList<QUuid>, playlist);
    QFETCH(int, count);

    Library l;
    QSignalSpy spy(&l, &Library::playlistCountChanged);

    for(auto it: playlist) {
        auto m = factory<SmartPlaylist>();
        m->setId(it);
        l.addSmartPlaylist(m);
    }

    QCOMPARE(spy.count(), count);
    QCOMPARE(l.playlistCount(), count);
}

void LibraryTest::addSmartPlaylistTest_data()
{
    QTest::addColumn<QList<QUuid>>("playlist");
    QTest::addColumn<int>("count");

    auto m1 = QUuid::createUuid();
    auto m2 = QUuid::createUuid();

    QTest::addRow("Add Smart playlist 1")<<QList<QUuid>{m1}<<1;
    QTest::addRow("Add Smart playlist 2")<<QList<QUuid>{m1, m2}<<2;
    QTest::addRow("Add Smart playlist 3")<<QList<QUuid>{m1, m2, m1}<<2;
}

void LibraryTest::removePlaylistTest()
{
    QFETCH(QList<QUuid>, playlist);
    QFETCH(QUuid, remove);
    QFETCH(int, count);
    QFETCH(bool, expected);

    Library l;
    for(auto it: playlist) {
        auto m = factory<PlayList>();
        m->setId(it);
        l.addPlaylist(m);
    }

    QSignalSpy spy(&l, &Library::playlistCountChanged);
    QCOMPARE(l.removePlaylist(remove.toString()), expected);
    QCOMPARE(spy.count(), expected ? 1 : 0);
    QCOMPARE(l.playlistCount(), count);
}

void LibraryTest::removePlaylistTest_data()
{
    QTest::addColumn<QList<QUuid>>("playlist");
    QTest::addColumn<QUuid>("remove");
    QTest::addColumn<int>("count");
    QTest::addColumn<bool>("expected");

    auto m1 = QUuid::createUuid();
    auto m2 = QUuid::createUuid();
    auto m3 = QUuid::createUuid();

    QTest::addRow("Remove playlist 1")<<QList<QUuid>{m1}<<m1<<0<<true;
    QTest::addRow("Remove playlist 2")<<QList<QUuid>{m1, m2}<<m1<<1<<true;
    QTest::addRow("Remove playlist 3")<<QList<QUuid>{m1, m2}<<m3<<2<<false;
}

void LibraryTest::removeSmartPlaylistTest()
{
    QFETCH(QList<QUuid>, playlist);
    QFETCH(QUuid, remove);
    QFETCH(int, count);
    QFETCH(bool, expected);

    Library l;
    for(auto it: playlist) {
        auto m = factory<SmartPlaylist>();
        m->setId(it);
        l.addSmartPlaylist(m);
    }

    QSignalSpy spy(&l, &Library::playlistCountChanged);
    QCOMPARE(l.removeSmartPlaylist(remove.toString()), expected);
    QCOMPARE(spy.count(), expected ? 1 : 0);
    QCOMPARE(l.playlistCount(), count);
}

void LibraryTest::removeSmartPlaylistTest_data()
{
    QTest::addColumn<QList<QUuid>>("playlist");
    QTest::addColumn<QUuid>("remove");
    QTest::addColumn<int>("count");
    QTest::addColumn<bool>("expected");

    auto m1 = QUuid::createUuid();
    auto m2 = QUuid::createUuid();
    auto m3 = QUuid::createUuid();

    QTest::addRow("Remove playlist 1")<<QList<QUuid>{m1}<<m1<<0<<true;
    QTest::addRow("Remove playlist 2")<<QList<QUuid>{m1, m2}<<m1<<1<<true;
    QTest::addRow("Remove playlist 3")<<QList<QUuid>{m1, m2}<<m3<<2<<false;
}

void LibraryTest::addTagTest()
{
    QFETCH(QList<MediaPlayerGlobal::Tag>, tags);
    QFETCH(QList<MediaPlayerGlobal::Tag>, expected);
    QFETCH(int, count);

    Library l;

    for(auto it: tags) {
        l.addTag(it);
    }

    std::sort(expected.begin(), expected.end(), [](auto it1, auto it2) {
        return it1.first < it2.first;
    });


    auto ltags = l.tags();
    std::sort(ltags.begin(), ltags.end(), [](auto it1, auto it2) {
        return it1.first < it2.first;
    });

    QCOMPARE(ltags.count(), count);
    QCOMPARE(ltags, expected);
}

void LibraryTest::addTagTest_data()
{
    QTest::addColumn<QList<MediaPlayerGlobal::Tag>>("tags");
    QTest::addColumn<QList<MediaPlayerGlobal::Tag>>("expected");
    QTest::addColumn<int>("count");

    MediaPlayerGlobal::Tag t1, t2, t3, t4;
    t1.first = QUuid::createUuid();
    t2.first = QUuid::createUuid();
    t3.first = QUuid::createUuid();
    t4.first = QUuid::createUuid();
    t1.second = "tag 1";
    t2.second = "tag 2";
    t3.second = "tag 3";
    t4.second = "tag 1";

    QTest::addRow("Add tag 1")<<QList<MediaPlayerGlobal::Tag>{t1}<<QList<MediaPlayerGlobal::Tag>{t1}<<1;
    QTest::addRow("Add tag 2")<<QList<MediaPlayerGlobal::Tag>{t1, t2}<<QList<MediaPlayerGlobal::Tag>{t1,t2}<<2;
    QTest::addRow("Add tag 3")<<QList<MediaPlayerGlobal::Tag>{t3, t2}<<QList<MediaPlayerGlobal::Tag>{t2,t3}<<2;
    QTest::addRow("Add tag 4")<<QList<MediaPlayerGlobal::Tag>{t1, t1}<<QList<MediaPlayerGlobal::Tag>{t1}<<1;
    QTest::addRow("Add tag 5")<<QList<MediaPlayerGlobal::Tag>{t1, t1, t2}<<QList<MediaPlayerGlobal::Tag>{t1, t2}<<2;
    QTest::addRow("Add tag 6")<<QList<MediaPlayerGlobal::Tag>{t1, t1, t2, t3}<<QList<MediaPlayerGlobal::Tag>{t1, t2, t3}<<3;
    QTest::addRow("Add tag 7")<<QList<MediaPlayerGlobal::Tag>{t1, t1, t4}<<QList<MediaPlayerGlobal::Tag>{t1}<<1;
}

void LibraryTest::removeTagTest()
{
    QFETCH(QList<MediaPlayerGlobal::Tag>, tags);
    QFETCH(MediaPlayerGlobal::Tag, remove);
    QFETCH(int, count);
    QFETCH(bool, expected);
    QFETCH(QList<MediaPlayerGlobal::Tag>, final);

    Library l;

    for(auto it: tags)
        l.addTag(it);

    QCOMPARE(l.removeTag(remove), expected);
    QCOMPARE(l.tags().count(), count);

    auto func = [](QList<MediaPlayerGlobal::Tag> list) {
        std::sort(list.begin(), list.end(), [](auto it1, auto it2) {
            return it1.first < it2.first;
        });

        return list;
    };

    final = func(final);
    auto ltags = func(l.tags());

    QCOMPARE(ltags, final);
}

void LibraryTest::removeTagTest_data()
{
    QTest::addColumn<QList<MediaPlayerGlobal::Tag>>("tags");
    QTest::addColumn<MediaPlayerGlobal::Tag>("remove");
    QTest::addColumn<int>("count");
    QTest::addColumn<bool>("expected");
    QTest::addColumn<QList<MediaPlayerGlobal::Tag>>("final");

    MediaPlayerGlobal::Tag t1, t2, t3;
    t1.first = QUuid::createUuid();
    t2.first = QUuid::createUuid();
    t3.first = QUuid::createUuid();
    t1.second = "tag 1";
    t2.second = "tag 2";
    t3.second = "tag 3";

    QTest::addRow("Remove tag 1")<<QList<MediaPlayerGlobal::Tag>{t1}<<t1<<0<<true<<QList<MediaPlayerGlobal::Tag>{};
    QTest::addRow("Remove tag 2")<<QList<MediaPlayerGlobal::Tag>{t1}<<t2<<1<<false<<QList<MediaPlayerGlobal::Tag>{t1};
    QTest::addRow("Remove tag 3")<<QList<MediaPlayerGlobal::Tag>{t1, t2}<<t2<<1<<true<<QList<MediaPlayerGlobal::Tag>{t1};
    QTest::addRow("Remove tag 4")<<QList<MediaPlayerGlobal::Tag>{t1, t2}<<t3<<2<<false<<QList<MediaPlayerGlobal::Tag>{t1, t2};
}

void LibraryTest::editTagTest()
{
    QFETCH(QList<MediaPlayerGlobal::Tag>, tags);
    QFETCH(QUuid, id);
    QFETCH(QString, text);
    QFETCH(bool, expected);

    Library l;
    for(auto it: tags) {
        l.addTag(it);
    }

    MediaPlayerGlobal::Tag edit;
    edit.first = id;
    edit.second = text;

    QCOMPARE(l.editTag(edit), expected);
    auto ltags = l.tags();
    auto it = std::find_if(ltags.begin(), ltags.end(), [id](auto it2) {
        return it2.first == id;
    });

    if(it != ltags.end()) {
        QCOMPARE(it->second, text);
    }
}

void LibraryTest::editTagTest_data()
{
    QTest::addColumn<QList<MediaPlayerGlobal::Tag>>("tags");
    QTest::addColumn<QUuid>("id");
    QTest::addColumn<QString>("text");
    QTest::addColumn<bool>("expected");

    MediaPlayerGlobal::Tag t1, t2, t3;
    t1.first = QUuid::createUuid();
    t2.first = QUuid::createUuid();
    t3.first = QUuid::createUuid();
    t1.second = "tag 1";
    t2.second = "tag 2";
    t3.second = "tag 3";

    QTest::addRow("Edit tag 1")<<QList<MediaPlayerGlobal::Tag>{t1}<<t1.first<<"tag edit"<<true;
    QTest::addRow("Edit tag 2")<<QList<MediaPlayerGlobal::Tag>{t1}<<t2.first<<"tag edit"<<false;
    QTest::addRow("Edit tag 3")<<QList<MediaPlayerGlobal::Tag>{t1, t2}<<t2.first<<"tag edit"<<true;
}

void LibraryTest::tagListTest()
{
    QFETCH(QStringList, list);

    Library l;
    l.setTagList(list);

    for(auto it: list) {
        QCOMPARE(l.hasMetadata(it), true);
    }
}

void LibraryTest::tagListTest_data()
{
    QTest::addColumn<QStringList>("list");

    QTest::addRow("Tags list 1")<<QStringList{"type 1"};
    QTest::addRow("Tags list 2")<<QStringList{"type 2", "type 1"};
    QTest::addRow("Tags list 3")<<QStringList{"type 1", "type 2", "type 3"};
    QTest::addRow("Tags list 4")<<QStringList{"t1", "t2", "t3", "t4"};
}

void LibraryTest::onProbedChangedTest()
{
    QFETCH(double, expected);
    QFETCH(int, mediaCount);

    Library l;
    auto probe = l.probe();
    l.addSourceDir(QStringLiteral(TESTDATA));
    probe->setFilters({"jpg"});
    QSignalSpy spy(&l, &Library::mediasChanged);
    l.scan();

    spy.wait();

    QCOMPARE(spy.count(), 26);
    QCOMPARE(probe->current(), expected);
    QCOMPARE(l.mediaCount(), mediaCount);
}

void LibraryTest::onProbedChangedTest_data()
{
    QTest::addColumn<double>("expected");
    QTest::addColumn<int>("mediaCount");

    QTest::addRow("On probed changed")<<100.0<<13;
}

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

void LibraryTest::addToPlaylistTest()
{
    QFETCH(QUuid, playlist);
    QFETCH(QUuid, media);
    QFETCH(bool, expected);

    Library l;
    auto m = MediaPointer::create(expected ? media : QUuid::createUuid());
    l.addMedia(m);

    auto pl = PlaylistPointer::create();
     pl->setId(playlist);

    l.addPlaylist(pl);

    QCOMPARE(l.addToPlaylist(playlist.toString(), media.toString()), expected);
    QCOMPARE(pl->count(), expected ? 1 : 0);
}

void LibraryTest::addToPlaylistTest_data()
{
    QTest::addColumn<QUuid>("playlist");
    QTest::addColumn<QUuid>("media");
    QTest::addColumn<bool>("expected");

    QTest::addRow("Add to playlist 1")<<QUuid::createUuid()<<QUuid::createUuid()<<true;
    QTest::addRow("Add to playlist 2")<<QUuid::createUuid()<<QUuid::createUuid()<<false;
}

QTEST_MAIN(LibraryTest)

#include "tst_librarytest.moc"
