#include <QApplication>
#include "GUIManager.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    GUIManager gui;
    gui.show();

    return app.exec();
}
