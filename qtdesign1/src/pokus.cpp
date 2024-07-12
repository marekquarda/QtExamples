#include "pokus.h"
#include <QDebug>

Pokus::Pokus(QAction *parent) : QAction(parent) {}

void Pokus::saved() {
    qDebug() << "Saved on the other classes via slots";
}
