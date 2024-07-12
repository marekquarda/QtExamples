#ifndef POKUS_H
#define POKUS_H

#include <QAction>

class Pokus : public QAction {
    Q_OBJECT

public:
    explicit Pokus(QAction *parent = nullptr);

public slots:
    void saved();
};

#endif // POKUS_H
