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
    const MediaPlayerGlobal::MediaRole role = MediaPlayerGlobal::MediaRole::Game;
    const QDate added = QDate::currentDate();
    const QDateTime lastFinish = QDateTime::currentDateTime();
    const QDateTime lastProbed = QDateTime::currentDateTime().addDays(5);
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
    void test_lastProbed();
    void test_copy();
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
    QVERIFY(model1.role() != role);
    model1.setRole(role);
    QCOMPARE(model1.role(), role);
}

void MediaTest::test_paths()
{
    QVERIFY(model1.paths().isEmpty());
    model1.setPath(path);
    QCOMPARE(model1.paths().first(), path);
}

void MediaTest::test_isAvailable()
{
    QCOMPARE(model1.isAvailable(), true);
}

void MediaTest::test_removePath()
{
    model1.removePath(path);
    QCOMPARE(model1.isAvailable(), false);
}

void MediaTest::test_added()
{
    QVERIFY(model1.added() != added);
    model1.setAdded(added);
    QCOMPARE(model1.added(), added);
}

void MediaTest::test_lastFinish()
{
    QVERIFY(model1.lastFinish() != lastFinish);
    QSignalSpy spy(&model1, SIGNAL(lastFinishChanged(QDateTime)));
    model1.setLastFinish(lastFinish);
    QCOMPARE(spy.count(), 1);
    QCOMPARE(model1.lastFinish(), lastFinish);
}

void MediaTest::test_currentRead()
{
    QVERIFY(model1.currentRead() != currentRead);
    QSignalSpy spy(&model1, SIGNAL(currentReadChanged(double)));
    model1.setCurrentRead(currentRead);
    QCOMPARE(spy.count(), 1);
    QCOMPARE(model1.currentRead(), currentRead);
}

void MediaTest::test_rating()
{
    QVERIFY(model1.rating() != rate);
    QSignalSpy spy(&model1, SIGNAL(ratingChanged(int)));
    model1.setRating(rate);
    QCOMPARE(spy.count(), 1);
    QCOMPARE(model1.rating(), rate);
}

void MediaTest::test_lastProbed()
{
    QVERIFY(model1.lastProbed() != lastProbed);
    QSignalSpy spy(&model1, SIGNAL(lastProbedChanged(QDateTime)));
    model1.setLastProbed(lastProbed);
    QCOMPARE(spy.count(), 1);
    QCOMPARE(model1.lastProbed(), lastProbed);
}

void MediaTest::test_copy()
{
    QVERIFY(model2.id() != id);
    model2 = model1;
    QCOMPARE(model2.id(), model1.id());
}



QTEST_APPLESS_MAIN(MediaTest)

#include "tst_mediatest.moc"
