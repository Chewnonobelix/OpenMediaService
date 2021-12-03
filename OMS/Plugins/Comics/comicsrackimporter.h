#pragma once

#include <QString>
#include <QObject>
#include <QTemporaryDir>
#include <QProcess>
#include <QDomDocument>
#include <QDomElement>
#include <QFile>

#include <Controller/Plugins/interfaceimporter.h>

class ComicsRackImporter: public InterfaceImporter
{
    Q_OBJECT
    Q_DISABLE_COPY(ComicsRackImporter)

public:
    ComicsRackImporter(QObject* = nullptr);
    ~ComicsRackImporter() = default;
    bool import(QString) override;
    QString name() const override;
    QStringList filters () const override;
};

