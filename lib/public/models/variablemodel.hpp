#ifndef VARIABLEMODEL_HPP
#define VARIABLEMODEL_HPP

#include <QObject>
#include <QString>
#include <QVariant>

/**
 * Переменная может либо задавать значение, либо знать рельное, либо то и то одновременно (обратная связь)
 */
namespace  VariableKeys{
    /**
     * @brief USE_REQUEST - может ли переменная задавать реальное значение
     */
    const unsigned char USE_REQUEST  = 0x01;

    /**
     * @brief NEED_REAL - может ли переменная знать реальное значение
     */
    const unsigned char NEED_REAL    = 0x02;
}

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
    Q_PROPERTY(unsigned char type READ type)
    Q_PROPERTY(QString name READ name)

public:
    explicit VariableModel(const QString &name,
                           const unsigned char &type = VariableKeys::USE_REQUEST,
                           QObject *parent = nullptr);

    void setValue(const QVariant &value);
    void setRealValue(const QVariant &value);

    QVariant value() const {return _request_value;};
    QVariant realValue() const {return _real_value;};
    QString name() const {return _name;};
    unsigned char type() const {return _type;};

private:
    // Задающее значение (если _type & USE_REQUEST)
    QVariant _request_value;

    // Реальное значение (если _type & NEED_REAL)
    QVariant _real_value;

    // Имя переменной - после инициализации поменять уже нельзя
    QString _name;

    // Тип переменной по VariableKeys - после инициализации поменять уже нельзя
    unsigned char _type = 0x00;

signals:
    void requestValueChanged(const QVariant &value);
    void realValueChanged(const QVariant &value);
};

#endif // VARIABLEMODEL_HPP
