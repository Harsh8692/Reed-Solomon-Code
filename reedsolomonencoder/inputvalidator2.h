#ifndef INPUTVALIDATOR2_H
#define INPUTVALIDATOR2_H

class InputValidator2 : public QValidator{
public :
    State validate(QString &input, int&pos) const override;
};


#endif // INPUTVALIDATOR2_H
