#include "timelinescene.h"
#include "timelinerow.h"
#include "timelineview.h"

TimeLineScene::TimeLineScene(TimeLineView& view)
    : QGraphicsScene(&view)
    , view_(view)
{
    row_items_.emplace_back(new TimeLineRow(*this));
}

void TimeLineScene::setViewportSize(const QSizeF& size)
{
    viewport_size_ = size;
    setSceneRect(QRectF(QPointF(0, 0), size));
}