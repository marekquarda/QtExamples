#include "myemitter.h"

MyEmitter::MyEmitter(const QString &label, QWidget *parrent) : QPushButton(label, parrent) {
    connect(this, &QPushButton::clicked, this, &MyEmitter::sendSignal);
}

void MyEmitter::sendSignal() {
    emit aSignal();
}
