#pragma once

#include <QAbstractListModel>

#include <Model/Smart/smartgroup.h>

class SmartModel : public QAbstractTableModel
{
    Q_OBJECT
    enum class SmartRole {OpRole = Qt::UserRole + 1, TypeRole, FieldRole};

    struct Flat {
      int depth = 0;
      QString type;
      QSharedPointer<AbstractRule> rule;
    };

private:
    SmartGroupPointer m_model;
    QList<Flat> m_flat;
    int m_depth = 0;

    QList<Flat> toFlat(SmartGroupPointer, int = 1);
public:
    explicit SmartModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex & = QModelIndex()) const override;
    int columnCount(const QModelIndex& = QModelIndex()) const override;

    QVariant data(const QModelIndex &, int = Qt::DisplayRole) const override;

    bool setData(const QModelIndex &, const QVariant &,
                 int = Qt::EditRole) override;

    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void setModel(SmartGroupPointer);
    Q_INVOKABLE void add(int, bool);
public:
    SmartGroup* group() const;

signals:
    void groupChanged();

private:
};

