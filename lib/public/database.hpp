#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <memory>

#include <QObject>

#include "models/variablemodel.hpp"

/**
 * @brief The Database class предназначен для хранения всех используемых моделей.
 */
class Q_DECL_EXPORT Database : public QObject
{
    Q_OBJECT
public:
    explicit Database(QObject *parent = nullptr);

    std::shared_ptr<VariableModel> _servo_a;
    std::shared_ptr<VariableModel> _servo_b;
    std::shared_ptr<VariableModel> _step_driver_a;
    std::shared_ptr<VariableModel> _step_driver_b;

};

#endif // DATABASE_HPP
