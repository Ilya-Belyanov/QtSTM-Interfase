#ifndef VARIABLEMODEL_HPP
#define VARIABLEMODEL_HPP

#include <QObject>
#include <QString>
#include <QVariant>

/**
 * @brief The VariableModel class предоставляет удобную модель для хранения
 * задаваемого и реального значения, имени переменной и т.д.
 * Хранит инвариантное значение, так что можно использовать: int, float, bool и т.д.
 */

class Q_DECL_EXPORT VariableModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QVariant value READ value WRITE setValue NOTIFY requestValueChanged)
    Q_PROPERTY(QVariant realValue READ realValue WRITE setRealValue NOTIFY realValueChanged)
    Q_PROPERTY(QString name READ name)

public:
    explicit VariableModel(const QString &name, QObject *parent = nullptr);

    void setValue(const QVariant &value);
    void setRealValue(const QVariant &value);

    QVariant value(){return _request_value;};
    QVariant realValue(){return _real_value;};
    QString name(){return _name;};

private:
    QVariant _request_value;
    QVariant _real_value;
    QString _name;

signals:
    void requestValueChanged(const QVariant &value);
    void realValueChanged(const QVariant &value);
};

#endif // VARIABLEMODEL_HPP
