#include <QtWidgets>
#include "myemitter.h"
#include "myreceiver.h"

int main(int argc, char* argv[]) {

    QApplication app(argc, argv);

    auto emitter = new MyEmitter("Hello World");
    emitter->setAttribute(Qt::WA_DeleteOnClose);
    auto receiver = new MyReceiver(&app);

    QObject::connect(emitter, &MyEmitter::aSignal, receiver, &MyReceiver::aSlot);
    emitter->show();

    return app.exec();
}
