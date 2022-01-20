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
    QFAIL("Not implemented");
}

void LibraryTest::idTest_data() {}

void LibraryTest::nameTest()
{
    QFAIL("Not implemented");
}

void LibraryTest::nameTest_data() {}

void LibraryTest::roleTest()
{
    QFAIL("Not implemented");
}

void LibraryTest::roleTest_data() {}

void LibraryTest::isSharedTest()
{
    QFAIL("Not implemented");
}

void LibraryTest::isSharedTest_data() {}

void LibraryTest::addSourceDirTest()
{
    QFAIL("Not implemented");
}

void LibraryTest::addSourceDirTest_data() {}

void LibraryTest::addMediaTest()
{
    QFAIL("Not implemented");
}

void LibraryTest::addMediaTest_data() {}

void LibraryTest::removeMediaTest()
{
    QFAIL("Not implemented");
}

void LibraryTest::removeMediaTest_data() {}

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
