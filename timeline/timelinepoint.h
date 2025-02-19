#pragma once

#include <QGraphicsObject>

class TimeLineScene;
class TimeLinePoint : public QGraphicsObject {
    Q_OBJECT
public:
    explicit TimeLinePoint(TimeLineScene& scene);

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;

private:
    TimeLineScene& scene_;
};