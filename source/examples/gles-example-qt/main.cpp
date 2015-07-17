
#include <QApplication>
#include <QMainWindow>

#include "glwidget.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    QMainWindow window;
    window.setCentralWidget(new GLWidget());
    window.show();

    return app.exec();
}
