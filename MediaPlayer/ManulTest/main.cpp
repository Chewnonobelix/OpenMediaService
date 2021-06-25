#include <QCoreApplication>
#include <Operation/Arithmetic/additionexpression.h>
#include <Core/valueexpression.h>
#include "testexp.h"

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
    return a.exec();
}
