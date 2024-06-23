#ifndef INPUTVALIDATOR_H
#define INPUTVALIDATOR_H

#include <QValidator>
#include <QString>

class InputValidator : public QValidator{
public :
    State validate(QString &input, int&pos) const override;
};

#endif // INPUTVALIDATOR_H
