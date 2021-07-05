#include <QtTest>

#include <Model/library.h>
#include <Model/smartplaylist.h>

// add necessary includes here
const MD5 id1 = "id1", id2 = "id2";
const QString path1 = QStringLiteral(TESTDATA) + "/porte_d_eternite.jpg";
const QString path2 = QStringLiteral(TESTDATA) + "/121813.jpg";
int count1 = 1, count2 = 2, count3 = 3;
SmartGroup group;

class SmartPlaylistTest : public QObject
{
    Q_OBJECT
private:
    MediaPointer m1, m2;
    SmartPlaylistPointer spl1;

public:
    SmartPlaylistTest();
    ~SmartPlaylistTest();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_addRule();
    void test_addGroup();
    void test_setRule();
    void test_addValid();
    void test_addInvalid();
    void test_modify();
};

SmartPlaylistTest::SmartPlaylistTest()
{

}

SmartPlaylistTest::~SmartPlaylistTest()
{

}

void SmartPlaylistTest::initTestCase()
{
    m1 = MediaPointer::create(id1, path1);
    m2 = MediaPointer::create(id2, path2);
    m1->setCount(count1);
    m2->setCount(count2);
    spl1 = SmartPlaylistPointer::create();

}

void SmartPlaylistTest::cleanupTestCase()
{

}

void SmartPlaylistTest::test_addRule()
{
    QVERIFY(group.count() == 0);
    auto rule = group.add().dynamicCast<SmartRule>();
    QCOMPARE(rule.isNull(), false);
    QCOMPARE(group.count(), count1);

    rule = group[group.count() - 1].dynamicCast<SmartRule>();
    rule->setField("count");
    rule->setValue(count2);
    rule->setOp(AbstractRule::Op::Inferior);
}

void SmartPlaylistTest::test_addGroup()
{
    QVERIFY(group.count() == 1);
    auto rule = group.add(true).dynamicCast<SmartGroup>();
    QCOMPARE(rule.isNull(), false);
    QCOMPARE(group.count(), 2);
}

void SmartPlaylistTest::test_setRule()
{
    QVERIFY(spl1->rules().compare(group.clone()) == QPartialOrdering::Unordered);
    spl1->setRules(group);
    QCOMPARE(spl1->rules().compare(group.clone()), QPartialOrdering::Equivalent);
}

void SmartPlaylistTest::test_addValid()
{
    QVERIFY(spl1->rules()[0].dynamicCast<SmartRule>()->field() == "count");
    QVERIFY(spl1->count() == 0);
    spl1->append(m1);
    QCOMPARE(spl1->count(), 1);
}

void SmartPlaylistTest::test_addInvalid()
{
    QVERIFY(spl1->count() == 1);
    spl1->append(m2);
    QCOMPARE(spl1->count(), 1);
}

void SmartPlaylistTest::test_modify()
{
    QVERIFY(spl1->count() == 1);
    m1->setCount(count3);
    QCOMPARE(spl1->count(), 0);
}

QTEST_APPLESS_MAIN(SmartPlaylistTest)

#include "tst_smartplaylisttest.moc"
