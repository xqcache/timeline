#include "lighttree/lighttreeview.h"
#include "timeline/timelineview.h"
#include <QApplication>
#include <QHBoxLayout>
#include <QSplitter>
#include <QStandardItemModel>
#include <QWidget>

void initModel(QStandardItemModel* model)
{
    for (int i = 15; i > 0; --i) {
        auto* light = new QStandardItem(QString::number(i));
        auto* dimmer = new QStandardItem("Dimmer");
        auto* red = new QStandardItem("Red");
        auto* green = new QStandardItem("Geen");
        auto* blue = new QStandardItem("Blue");
        auto* shutter = new QStandardItem("Shutter");
        light->appendRow(dimmer);
        light->appendRow(red);
        light->appendRow(green);
        light->appendRow(blue);
        light->appendRow(shutter);
        model->appendRow(light);
    }
}

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    QStandardItemModel model;
    initModel(&model);

    QSplitter win;

    LightTreeView* lighttree = new LightTreeView(&win);
    TimeLineView* timeline = new TimeLineView(&win);

    lighttree->setModel(&model);
    timeline->setModel(&model);

    win.addWidget(lighttree);
    win.addWidget(timeline);

    win.setStretchFactor(0, 0);
    win.setStretchFactor(1, 1);
    win.setChildrenCollapsible(false);

    win.resize(640, 480);
    win.show();

    return app.exec();
}