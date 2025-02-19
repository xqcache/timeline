#include "timelinepoint.h"
#include "timelinescene.h"

TimeLinePoint::TimeLinePoint(TimeLineScene& scene)
    : scene_(scene)
{
}

QRectF TimeLinePoint::boundingRect() const
{
}

void TimeLinePoint::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
}
