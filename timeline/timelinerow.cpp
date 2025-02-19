#include "timelinerow.h"
#include "timelinescene.h"
#include <QPainter>

TimeLineRow::TimeLineRow(TimeLineScene& scene)
    : scene_(scene)
{
    scene.addItem(this);
    setAcceptHoverEvents(true);
}

QRectF TimeLineRow::boundingRect() const
{
    return QRectF(0, 0, scene_.viewportSize().width(), 24);
}

void TimeLineRow::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    painter->fillRect(boundingRect(), hovered_ ? Qt::red : Qt::darkRed);
}

void TimeLineRow::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
    hovered_ = true;
    QGraphicsObject::hoverEnterEvent(event);
}

void TimeLineRow::hoverMoveEvent(QGraphicsSceneHoverEvent* event)
{
}

void TimeLineRow::hoverLeaveEvent(QGraphicsSceneHoverEvent* event)
{
    hovered_ = false;
    QGraphicsObject::hoverLeaveEvent(event);
}
