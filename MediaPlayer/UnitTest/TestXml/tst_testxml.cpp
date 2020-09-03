#include "Controller/DataXml.h"
#include <QtTest>

// add necessary includes here

class TestXml : public QObject
{
    Q_OBJECT

    DataXml model;
    const QString name1 = "name1", name2 = "name2";
    QUuid id;

public:
    TestXml();
    ~TestXml();

private slots:
    void test_add_library();
    void test_select_library();
    void test_update_library();
    void test_remove_library();
};

TestXml::TestXml()
{

}

TestXml::~TestXml()
{

}

void TestXml::test_add_library()
{
    QVERIFY(model.selectLibrary().isEmpty());
    auto l = model.createLibrary(name1);
    id = l->id();
    QCOMPARE(!id.isNull() && !l.isNull(), true);
}

void TestXml::test_select_library()
{
    QCOMPARE(model.selectLibrary().first()->id(), id);
    QCOMPARE(model.selectLibrary(id).first()->id(), id);
}

void TestXml::test_update_library()
{
    auto l = model.selectLibrary(id).first();
    l->setName(name2);
    QCOMPARE(model.updateLibrary(l), true);
}

void TestXml::test_remove_library()
{
    auto l = model.selectLibrary(id).first();
    QCOMPARE(model.removeLibrary(l), true);
    QVERIFY(model.selectLibrary(id).isEmpty());
}

QTEST_APPLESS_MAIN(TestXml)

#include "tst_testxml.moc"
