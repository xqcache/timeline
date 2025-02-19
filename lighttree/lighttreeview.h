#pragma once

#include <QTreeView>

class LightTreeView : public QTreeView {
    Q_OBJECT
public:
    explicit LightTreeView(QWidget* parent = nullptr);
};