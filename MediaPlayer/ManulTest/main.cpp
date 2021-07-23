#include <QCoreApplication>
#include <Operation/Arithmetic/additionexpression.h>
#include <Core/valueexpression.h>
#include "testexp.h"
#include <QVariant>
#include <QDate>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    int i, j;
    i = 3; j = 3;

    TestExp<int&> te;
    ValueExpression<int&> v1(i) ,v2(j);
    te.e1 = v1.clone();
    te.e2 = v2.clone();
    qDebug()<<te.evaluate();
    j = 4;
    qDebug()<<te.evaluate();

    QVariant a1(123), a2("12");
    qDebug()<<(QVariant::compare(a1, a2) == QPartialOrdering::Less);
    return a.exec();
}
