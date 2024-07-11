#ifndef MYSIGNAL_H
#define MYSIGNAL_H

#include <QPushButton>

class MyEmitter : public QPushButton {
    Q_OBJECT

public:
    explicit MyEmitter(const QString &label, QWidget *parrent = nullptr);

signals:
    void aSignal();
    void anOtherSignal(int, QWidget *);

private:
    void sendSignal();

};

#endif
