#ifndef ABSTRACTCONTROLLER_H
#define ABSTRACTCONTROLLER_H

#include <QObject>

class AbstractController : public QObject
{
    Q_OBJECT
public:
    explicit AbstractController(QObject *parent = nullptr);
    
signals:
    
};

#endif // ABSTRACTCONTROLLER_H
