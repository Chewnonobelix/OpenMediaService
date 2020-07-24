#include <QtTest>
#include <QSignalSpy>
#include "playlist.h"

// add necessary includes here

class PlaylistTest : public QObject
{
    Q_OBJECT
    
    PlayList model1, model2;
    MediaPointer m1, m2, m3;
    QUuid id = QUuid::createUuid();
    QString name = "Name1";
    int count = 2;
    
public:
    PlaylistTest();
    ~PlaylistTest();
    
private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_id();
    void test_name();
    void test_add();
    void test_get();
    void test_remove();
    void test_swap();
    void test_count();
    void test_copy();    
};

void PlaylistTest::test_id()
{
    QVERIFY(model1.id() != id);
    model1.setId(id);
    QCOMPARE(model1.id(), id);    
}

void PlaylistTest::test_name()
{
    QVERIFY(model1.name() != name);
    QSignalSpy spy(&model1, SIGNAL(nameChanged(QString)));
    model1.setName(name);
    QCOMPARE(spy.count(), 1);
    QCOMPARE(model1.name(), name);    
}

void PlaylistTest::test_add()
{
    QVERIFY(model1.isEmpty());
    QSignalSpy spy(&model1, SIGNAL(countChanged()));
    model1.append(m1);    
    model1.append(m2);    
    model1.append(m3);
    QCOMPARE(spy.count(), 3);
}

void PlaylistTest::test_get()
{
    QCOMPARE(model1.at(1), m2);        
}

void PlaylistTest::test_remove()
{
    QVERIFY(!model1.isEmpty());
    QSignalSpy spy(&model1, SIGNAL(countChanged()));
    model1.remove(2);    
    QCOMPARE(spy.count(), 1);}

void PlaylistTest::test_count()
{
    QCOMPARE(model1.count(), count);  
}

void PlaylistTest::test_copy()
{
    QVERIFY(model2.id() != id);
    model2 = model1;
    QCOMPARE(model2.id(), model1.id());        
}

void PlaylistTest::test_swap()
{
    QVERIFY(model1.at(0) == m1);
    QSignalSpy spy(&model1, SIGNAL(countChanged()));
    model1.swap(0,1);
    QCOMPARE(spy.count(), 1);    
    QCOMPARE(model1.at(0), m2);
}

PlaylistTest::PlaylistTest()
{
    m1 = Media::createMedia(QUuid::createUuid().toByteArray());
    m2 = Media::createMedia(QUuid::createUuid().toByteArray());
    m3 = Media::createMedia(QUuid::createUuid().toByteArray());
}

PlaylistTest::~PlaylistTest()
{
    
}

void PlaylistTest::initTestCase()
{
    
}

void PlaylistTest::cleanupTestCase()
{
    
}

QTEST_APPLESS_MAIN(PlaylistTest)

#include "tst_playlisttest.moc"
