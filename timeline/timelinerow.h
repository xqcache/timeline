#pragma once

#include <QGraphicsObject>

class TimeLineScene;
class TimeLineRow : public QGraphicsObject {
    Q_OBJECT
public:
    explicit TimeLineRow(TimeLineScene& scene);

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
    void hoverMoveEvent(QGraphicsSceneHoverEvent* event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;

private:
    TimeLineScene& scene_;
    bool hovered_ { false };
};