#include <QtTest>

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
    void test_case1();

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

void MediaTest::test_case1()
{

}

QTEST_APPLESS_MAIN(MediaTest)

#include "tst_mediatest.moc"
