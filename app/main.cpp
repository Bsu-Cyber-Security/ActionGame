#include <QApplication>

#include "app/scene/view.h"

int main(int argc, char** argv) {
    QApplication app(argc, argv);
    View v;
    v.setWindowTitle("Action game Qt/C++");
    v.show();

    return app.exec();
}
