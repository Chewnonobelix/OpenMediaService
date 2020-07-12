#include <QtTest>
#include <QSignalSpy>
#include "media.h"
// add necessary includes here

class MediaTest : public QObject
{
    Q_OBJECT

    Media model1, model2;
    const MD5 id = "testid";
    const QString path = "path1";
    const int count = 1;
    const MediaPlayerGlobal::MediaRole role = MediaPlayerGlobal::Game;
    const QDate added = QDate::currentDate();
    const QDateTime lastFinish = QDateTime::currentDateTime();
    const double currentRead = 99.0;
    const int rate = 2;

public:
    MediaTest();
    ~MediaTest();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_id();
    void test_count();
    void test_role();
    void test_paths();
    void test_isAvailable();
    void test_removePath();
    void test_added();
    void test_lastFinish();
    void test_currentRead();
    void test_rating();

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

void MediaTest::test_id()
{
    QVERIFY(model1.id() != id);
    model1.setId(id);
    QCOMPARE(model1.id(), id);
}

void MediaTest::test_count()
{
    QVERIFY(model1.count() != count);
    QSignalSpy spy(&model1, SIGNAL(countChanged(int)));
    model1.setCount(count);
    QCOMPARE(spy.count(), 1);
    QCOMPARE(model1.count(), count);
}

void MediaTest::test_role()
{
    QFAIL("Not set");
}

void MediaTest::test_paths()
{
    QFAIL("Not set");
}

void MediaTest::test_isAvailable()
{
    QFAIL("Not set");
}

void MediaTest::test_removePath()
{
    QFAIL("Not set");
}

void MediaTest::test_added()
{
    QFAIL("Not set");
}

void MediaTest::test_lastFinish()
{
    QFAIL("Not set");
}

void MediaTest::test_currentRead()
{
    QFAIL("Not set");
}

void MediaTest::test_rating()
{
    QFAIL("Not set");
}


QTEST_APPLESS_MAIN(MediaTest)

#include "tst_mediatest.moc"
