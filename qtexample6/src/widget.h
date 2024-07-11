#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class Widget : public QWidget {
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    bool windowShouldClose();

};

#endif
