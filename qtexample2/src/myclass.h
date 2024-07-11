#include <QObject>

class MyClass : public QObject
{
    Q_OBJECT // Marker for moc

    public slots:
        void setValue(int value);
};
