#include "timelineview.h"
#include <QApplication>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    TimeLineView win;
    win.resize(640, 480);
    win.show();

    return app.exec();
}