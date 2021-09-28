#include <QCoreApplication>
#include <Operation/Arithmetic/additionexpression.h>
#include <Core/valueexpression.h>
#include "testexp.h"
#include <QVariant>
#include <QDate>

Q_LOGGING_CATEGORY(manualtest, "manualtest.log")

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    int i, j;
    i = 3; j = 3;

    TestExp<int&> te;
    ValueExpression<int&> v1(i) ,v2(j);
    te.e1 = v1.clone();
    te.e2 = v2.clone();
    qCDebug(manualtest)<<te.evaluate();
    j = 4;
    qCDebug(manualtest)<<te.evaluate();

    QVariant a1(123), a2("12");
    qCDebug(manualtest)<<(QVariant::compare(a1, a2) == QPartialOrdering::Less);

    QSet<int> set;
    set<<1<<2<<3<<1<<2<<4<<5<<6<<7;
    auto var = QVariant::fromValue(set);

    qDebug()<<var<<var.toList()<<var.value<QList<int>>()<<var.value<QSet<int>>();
    QList<int> list;
    list<<1<<2<<3<<1<<2<<4<<5<<6<<7;
    auto var2 = QVariant::fromValue(list);

    qDebug()<<var2<<var2.toList()<<var2.value<QList<int>>()<<var2.value<QSet<int>>()<<a1.typeName()<<var.typeName()<<a1.toList();
    return a.exec();
}
