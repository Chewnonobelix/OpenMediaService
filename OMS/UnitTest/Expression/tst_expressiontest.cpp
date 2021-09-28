#include <QtTest>

#include <Model/Expression/expressionfactory.h>
// add necessary includes here

class ExpressionTest : public QObject
{
    Q_OBJECT

public:
    ExpressionTest();
    ~ExpressionTest();

private slots:
    void inferiorTest();
    void superiorTest();
    void equalTest();
    void inferiorEqualTest();
    void superiorEqualTest();
    void startTest();
    void endTest();
    void containTest();
    void regTest();
};

ExpressionTest::ExpressionTest()
{

}

ExpressionTest::~ExpressionTest()
{

}

void ExpressionTest::inferiorTest()
{
    QVariantList vl1 = {1}, vl2 = {2};
    QVariant v1 = QVariant::fromValue(vl1), v2 = QVariant::fromValue(vl2);
    auto exp = ExpressionFactory::createInferior(v1,v2);

    QCOMPARE(exp->evaluate(), true);
    v1 = QVariant::fromValue(QList<int>{2});
    QCOMPARE(exp->evaluate(), false);
    v1 = QVariant::fromValue(QList<int>{3});
    QCOMPARE(exp->evaluate(), false);
    v1 = QVariant::fromValue(QList<int>{3, 1, 2, 4});
    QCOMPARE(exp->evaluate(), true);
}

void ExpressionTest::superiorTest()
{
    QVariantList vl1 = {3}, vl2 = {2};
    QVariant v1 = QVariant::fromValue(vl1), v2 = QVariant::fromValue(vl2);

    auto exp = ExpressionFactory::createSuperior(v1,v2);

    QCOMPARE(exp->evaluate(), true);
    v1 = {2};
    QCOMPARE(exp->evaluate(), false);
    v1 = {1};
    QCOMPARE(exp->evaluate(), false);
    v1 = QVariant::fromValue(QList<int>{3, 1, 2, 4});
    QCOMPARE(exp->evaluate(), true);
    v1 = QVariant::fromValue(QList<int>{3, 1, 2, 4});
    QCOMPARE(exp->evaluate(), true);
}

void ExpressionTest::equalTest()
{
    QVariantList vl1 = {2}, vl2 = {2};
    QVariant v1 = QVariant::fromValue(vl1), v2 = QVariant::fromValue(vl2);

    auto exp = ExpressionFactory::createEqual(v1,v2);

    QCOMPARE(exp->evaluate(), true);
    v1 = QVariant::fromValue(QList<int>{3});
    QCOMPARE(exp->evaluate(), false);
    v1 = QVariant::fromValue(QList<int>{3, 1, 2, 4});
    QCOMPARE(exp->evaluate(), true);
}

void ExpressionTest::inferiorEqualTest()
{
    QVariantList vl1 = {1}, vl2 = {2};
    QVariant v1 = QVariant::fromValue(vl1), v2 = QVariant::fromValue(vl2);

    auto exp = ExpressionFactory::createInferiorEqual(v1,v2);

    QCOMPARE(exp->evaluate(), true);
    v1 = QVariant::fromValue(QList<int>{2});
    QCOMPARE(exp->evaluate(), true);
    v1 = QVariant::fromValue(QList<int>{3});
    QCOMPARE(exp->evaluate(), false);
    v1 = QVariant::fromValue(QList<int>{3, 1, 2, 4});
    QCOMPARE(exp->evaluate(), true);
}

void ExpressionTest::superiorEqualTest()
{
    QVariantList vl1 = {3}, vl2 = {2};
    QVariant v1 = QVariant::fromValue(vl1), v2 = QVariant::fromValue(vl2);

    auto exp = ExpressionFactory::createSuperiorEqual(v1,v2);

    QCOMPARE(exp->evaluate(), true);
    v1 = QVariant::fromValue(QList<int>{2});
    QCOMPARE(exp->evaluate(), true);
    v1 = QVariant::fromValue(QList<int>{1});
    QCOMPARE(exp->evaluate(), false);
    v1 = QVariant::fromValue(QList<int>{3, 1, 2, 4});
    QCOMPARE(exp->evaluate(), true);
}

void ExpressionTest::startTest()
{
    QVariantList vl1 = {"azerty"}, vl2 = {"aze"};
    QVariant v1 = QVariant::fromValue(vl1), v2 = QVariant::fromValue(vl2);

    auto exp = ExpressionFactory::createStart(v1,v2);

    QCOMPARE(exp->evaluate(), true);
    v1 = QVariant::fromValue(QStringList{"azeqsd"});
    QCOMPARE(exp->evaluate(), true);
    v1 = QVariant::fromValue(QStringList{"eza"});
    QCOMPARE(exp->evaluate(), false);
    v1 = QVariant::fromValue(QStringList{"eza", "azeqsdwxc"});
    QCOMPARE(exp->evaluate(), true);
}

void ExpressionTest::endTest()
{
    QVariantList vl1 = {"azerty"}, vl2 = {"rty"};
    QVariant v1 = QVariant::fromValue(vl1), v2 = QVariant::fromValue(vl2);

    auto exp = ExpressionFactory::createEnd(v1,v2);

    QCOMPARE(exp->evaluate(), true);
    v1 = QVariant::fromValue(QStringList{"qsdrty"});
    QCOMPARE(exp->evaluate(), true);
    v1 = QVariant::fromValue(QStringList{"eza"});
    QCOMPARE(exp->evaluate(), false);
    v1 = QVariant::fromValue(QStringList{"eza", "azeqsdwxcrty"});
    QCOMPARE(exp->evaluate(), true);

}

void ExpressionTest::containTest()
{
    QVariantList vl1 = {"azerty"}, vl2 = {"zer"};
    QVariant v1 = QVariant::fromValue(vl1), v2 = QVariant::fromValue(vl2);

    auto exp = ExpressionFactory::createContain(v1,v2);

    QCOMPARE(exp->evaluate(), true);
    v1 = QVariant::fromValue(QStringList{"azerqsd"});
    QCOMPARE(exp->evaluate(), true);
    v1 = QVariant::fromValue(QStringList{"eza"});
    QCOMPARE(exp->evaluate(), false);
    v1 = QVariant::fromValue(QStringList{"eza", "azeqsazerdwxc"});
    QCOMPARE(exp->evaluate(), true);
}

void ExpressionTest::regTest()
{

}

QTEST_APPLESS_MAIN(ExpressionTest)

#include "tst_expressiontest.moc"
