#ifndef MYRECEIVER_H
#define MYRECEIVER_H

#include <QObject>

class MyReceiver : public QObject {
    Q_OBJECT

public:
    explicit MyReceiver(QObject *parent = nullptr);

public slots:
        void aSlot();
        void anOtherSlot(int, QObject *);
};

#endif
