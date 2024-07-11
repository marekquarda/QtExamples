#ifndef STOP_WATCH_H
#define STOP_WATCH_H

#include <QObject>

class StopWatch : public QObject {
    Q_OBJECT

public:
    explicit StopWatch(QObject *parent = nullptr);

private slots:
    void addOneSecond();

private:
    int m_secs = 0;

};

#endif
