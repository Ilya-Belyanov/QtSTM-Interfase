#ifndef VARIABLEMODEL_HPP
#define VARIABLEMODEL_HPP

#include <QObject>
#include <QString>

class Q_DECL_EXPORT VariableModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int value READ value WRITE setValue NOTIFY requestValueChanged)
    Q_PROPERTY(int realValue READ realValue WRITE setRealValue NOTIFY realValueChanged)
    Q_PROPERTY(QString name READ name)

public:
    explicit VariableModel(const QString &name, QObject *parent = nullptr);

    void setValue(int value);
    void setRealValue(int value);

    int value(){return _request_value;};
    int realValue(){return _real_value;};
    QString name(){return _name;};

private:
    int _request_value;
    int _real_value;
    QString _name;

signals:
    void requestValueChanged(int value);
    void realValueChanged(int value);
};

#endif // VARIABLEMODEL_HPP