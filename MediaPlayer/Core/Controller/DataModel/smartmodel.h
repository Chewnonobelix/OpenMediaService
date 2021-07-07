#pragma once

#include <QAbstractListModel>

#include <Model/Smart/smartgroup.h>

class SmartModel : public QAbstractTableModel
{
    Q_OBJECT
    enum class SmartRole {OpRole = Qt::UserRole + 1, TypeRole, FieldRole};
    Q_PROPERTY(SmartGroup* group READ group WRITE setGroup NOTIFY groupChanged)

    struct Flat {
      int depth = 0;
      QString type;
      QSharedPointer<AbstractRule> rule;
    };

private:
    SmartGroup* m_model = nullptr;
    QList<Flat> m_flat;
    int m_depth = 0;

    QList<Flat> toFlat(SmartGroup&, int = 1);
public:
    explicit SmartModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex & = QModelIndex()) const override;
    int columnCount(const QModelIndex& = QModelIndex()) const override;

    QVariant data(const QModelIndex &, int = Qt::DisplayRole) const override;

    bool setData(const QModelIndex &, const QVariant &,
                 int = Qt::EditRole) override;

    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void setModel(SmartGroup*);

public:
    SmartGroup* group() const;
    void setGroup(SmartGroup*);

signals:
    void groupChanged();

private:
};

