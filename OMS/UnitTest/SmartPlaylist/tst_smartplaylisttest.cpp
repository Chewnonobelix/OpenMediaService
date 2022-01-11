#include <QtTest>

#include <Model/library.h>
#include <Model/smartplaylist.h>

// add necessary includes here
const QString path1 = QStringLiteral(TESTDATA) + "/porte_d_eternite.jpg";
const QString path2 = QStringLiteral(TESTDATA) + "/121813.jpg";
int count1 = 1, count2 = 2, count3 = 3;
SmartGroupPointer group;

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
    m1 = MediaPointer::create(path1);
    m2 = MediaPointer::create(path2);
    m1->setCount(count1);
    m2->setCount(count2);
    spl1 = SmartPlaylistPointer::create();
    group = SmartGroupPointer::create();
}

void SmartPlaylistTest::cleanupTestCase()
{

}

void SmartPlaylistTest::test_addRule()
{
    QVERIFY(group->count() == 0);
    auto rule = group->add().dynamicCast<SmartRule>();
    QCOMPARE(rule.isNull(), false);
    QCOMPARE(group->count(), count1);

    rule = (*group)[0].dynamicCast<SmartRule>();
    QVERIFY(rule->setField("count"));
    QVERIFY(rule->setValue(QVariantList{count2}));
    QVERIFY(rule->setOp(AbstractRule::Op::Inferior));
}

void SmartPlaylistTest::test_addGroup()
{
    QVERIFY(group->count() == 1);
    auto rule = group->add(true).dynamicCast<SmartGroup>();
    QCOMPARE(rule.isNull(), false);
    QCOMPARE(group->count(), 2);
}

void SmartPlaylistTest::test_setRule()
{
    QVERIFY(spl1->rules()->compare(group) == QPartialOrdering::Unordered);
    auto ret = spl1->setRules(group);
    QCOMPARE(ret, true);
    QCOMPARE(spl1->rules()->compare(group), QPartialOrdering::Equivalent);
}

void SmartPlaylistTest::test_addValid()
{
    QVERIFY((*spl1->rules())[0].dynamicCast<SmartRule>()->field() == "count");
    QVERIFY((*spl1->rules())[0].dynamicCast<SmartRule>()->value() == QVariantList{count2});
    QVERIFY((*spl1->rules())[0].dynamicCast<SmartRule>()->op() == AbstractRule::Op::Inferior);

    QVERIFY(spl1->count() == 0);
    auto fut = spl1->append(m1);
    fut.waitForFinished();
    QVERIFY(fut.result());
    QCOMPARE(spl1->count(), 1);
}

void SmartPlaylistTest::test_addInvalid()
{
    QVERIFY(spl1->count() == 1);
    QVERIFY(!spl1->append(m2).result());
    QCOMPARE(spl1->count(), 1);
}

void SmartPlaylistTest::test_modify()
{
    QVERIFY(spl1->count() == 1);
    m1->setCount(count3);
    spl1->onMediaChanged(m1);

    QTest::qWait(2000);
    QCOMPARE(spl1->count(), 0);
}

QTEST_APPLESS_MAIN(SmartPlaylistTest)

#include "tst_smartplaylisttest.moc"
