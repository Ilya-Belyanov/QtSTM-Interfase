#ifndef VARIABLEMODEL_HPP
#define VARIABLEMODEL_HPP

#include <QObject>

class Q_DECL_EXPORT VariableModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int value READ value WRITE setValue NOTIFY requestValueChanged)
    Q_PROPERTY(int realValue READ realValue WRITE setRealValue NOTIFY realValueChanged)

public:
    explicit VariableModel(QObject *parent = nullptr);

    void setValue(int value);
    void setRealValue(int value);

    int value(){return _request_value;};
    int realValue(){return _real_value;};

private:
    int _request_value;
    int _real_value;

signals:
    void requestValueChanged(int value);
    void realValueChanged(int value);
};

#endif // VARIABLEMODEL_HPP
