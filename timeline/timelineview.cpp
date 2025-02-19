#include "timelineview.h"
#include "timelineaxis.h"
#include "timelinescene.h"

TimeLineView::TimeLineView(QWidget* parent)
    : QGraphicsView(parent)
    , scene_(new TimeLineScene(*this))
    , axis_(new TimeLineAxis(this))
    , hbar_(new QScrollBar(Qt::Horizontal, this))
    , vbar_(new QScrollBar(Qt::Vertical, this))
{
    setScene(scene_);
    setMouseTracking(true);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setViewportMargins(0, qRound(axis_->cursorHeight()), vbar_->sizeHint().width(), hbar_->sizeHint().height());

    hbar_->setMinimum(0);
    vbar_->setMinimum(0);
    hbar_->setMaximum(0);
    vbar_->setMaximum(0);

    setupSignals();
}

void TimeLineView::setAxisHeight(qreal height)
{
    axis_->setCursorHeight(height);
    setViewportMargins(0, qRound(axis_->cursorHeight()), vbar_->sizeHint().width(), hbar_->sizeHint().height());
}

void TimeLineView::setModel(QStandardItemModel* model)
{
    if (scene_) {
        scene_->setModel(model);
    }
}

QStandardItemModel* TimeLineView::model() const
{
    return scene_ ? scene_->model() : nullptr;
}

bool TimeLineView::event(QEvent* event)
{
    switch (event->type()) {
    case QEvent::MouseButtonPress:
    case QEvent::MouseMove:
    case QEvent::MouseButtonRelease:
    case QEvent::MouseButtonDblClick:
        std::ignore = QWidget::event(event);
        return true;
    default:
        break;
    }
    return QGraphicsView::event(event);
}

void TimeLineView::resizeEvent(QResizeEvent* event)
{
    scene_->setViewportSize(viewport()->size());
    axis_->resize(viewport()->width(), viewport()->geometry().bottom());

    vbar_->move(viewport()->geometry().right(), 1);
    hbar_->move(1, viewport()->geometry().bottom());

    vbar_->resize(vbar_->sizeHint().width(), hbar_->geometry().top());
    hbar_->resize(vbar_->geometry().left(), hbar_->sizeHint().height());

    hbar_->setMaximum(qMax(hbar_->maximum(), axis_->scaleCount()));
}

void TimeLineView::onHBarValueChanged(int value)
{
    axis_->setValue(value);
}

void TimeLineView::onVBarValueChanged(int value)
{
}

void TimeLineView::onCursorValueChanged(int value)
{
    hbar_->setMaximum(qMax(hbar_->maximum(), value));
}

void TimeLineView::setupSignals()
{
    connect(hbar_, &QScrollBar::valueChanged, this, &TimeLineView::onHBarValueChanged);
    connect(vbar_, &QScrollBar::valueChanged, this, &TimeLineView::onVBarValueChanged);
    connect(axis_, &TimeLineAxis::cursorValueChanged, this, &TimeLineView::onCursorValueChanged);
}
