#include "timelineaxis.h"
#include "timelinescene.h"
#include "timelineview.h"
#include <QMouseEvent>
#include <QPainter>
#include <QPainterPathStroker>

TimeLineAxis::TimeLineAxis(QWidget* parent)
    : QWidget(parent)
{
    setMouseTracking(true);
}

void TimeLineAxis::setMinimum(int val)
{
    if (minimum_ == val) {
        return;
    }
    minimum_ = val;
    update();
}

int TimeLineAxis::value() const
{
    return minimum_ + qRound(+cursor_pos_.x() / scale_pixels_);
}

int TimeLineAxis::minimum() const
{
    return minimum_;
}

int TimeLineAxis::maximum() const
{
    return minimum() + scaleCount();
}

void TimeLineAxis::setValue(int val)
{
    if (val == value()) {
        return;
    }
    if (val > maximum()) {
        minimum_ = val - scaleCount();
    } else if (val < minimum()) {
        minimum_ = val;
    }
    qreal cursor_x = (val - minimum_) * scale_pixels_;
    cursor_pos_.setX(cursor_x);
    update();
    emit cursorValueChanged(val);
}

void TimeLineAxis::mousePressEvent(QMouseEvent* event)
{
    auto guard = qScopeGuard([event] { event->ignore(); });
    if (event->modifiers() == Qt::NoModifier && event->buttons() == Qt::LeftButton) {
        if (shape().contains(event->position())) {
            cursor_picked_ = true;
            setCursor(Qt::SizeAllCursor);
            guard.dismiss();
        }
    }
}

void TimeLineAxis::mouseMoveEvent(QMouseEvent* event)
{
    QPainterPathStroker stroker;
    stroker.setWidth(2);

    if (!shape().contains(event->pos())) {
        event->ignore();
    }
    if (cursor_picked_) {
        qreal x = mapFromGlobal(QCursor::pos()).x() - cursorWidth() / 2;
        int old_value = value();

        if (x > width() - cursorWidth()) {
            ++minimum_;
        } else if (x < 0) {
            --minimum_;
            minimum_ = qMax(0, minimum_);
        }
        x = qMin<qreal>(x, width() - cursorWidth());
        x = qMax(0.0, x);
        x = qRound(x / scale_pixels_) * scale_pixels_;
        cursor_pos_.setX(x);
        update();

        if (old_value != value()) {
            emit cursorValueChanged(value());
        }
    }
}

void TimeLineAxis::mouseReleaseEvent(QMouseEvent* event)
{
    auto guard = qScopeGuard([event] { event->ignore(); });
    if (cursor_picked_) {
        cursor_picked_ = false;
        setCursor(Qt::ArrowCursor);
        guard.dismiss();
    }
}

void TimeLineAxis::resizeEvent(QResizeEvent* event)
{
}

void TimeLineAxis::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    // 绘制刻度线
    {
        painter.save();
        auto pen = painter.pen();
        pen.setWidth(2);
        painter.setPen(pen);

        int tick_label_y = cursorHeight() * 0.85;
        int sub_tick_count = scaleCount() / tick_count_;

        for (int i = 0; i <= tick_count_; ++i) {
            QString tick_label = QString::number(minimum_ + i * sub_tick_count);
            qreal tick_label_width = painter.fontMetrics().boundingRect(tick_label).width();
            qreal x = cursorWidth() / 2 + i * (sub_tick_count * scale_pixels_);
            painter.drawLine(QPointF(x, cursorHeight()), QPointF(x, cursorHeight() * 0.9));

            qreal tick_label_x = x - tick_label_width / 2;
            if (tick_label_x > width()) {
                tick_label_x = x - tick_label_width;
            }
            painter.drawText(tick_label_x, tick_label_y, tick_label);
        }
        painter.restore();
    }
    // 绘制游标
    {
        QColor color(Qt::GlobalColor::magenta);
        color.setAlpha(100);
        painter.setBrush(color);
        painter.drawPath(shape());

        QString value_label = QString::number(value());
        qreal value_label_width = painter.fontMetrics().boundingRect(value_label).width();
        if (cursor_pos_.x() + cursorWidth() + value_label_width > width()) {
            painter.drawText(cursor_pos_.x() - value_label_width - 2, cursor_pos_.y() + painter.fontMetrics().height(), value_label);
        } else {
            painter.drawText(cursor_pos_.x() + cursorWidth() + 2, cursor_pos_.y() + painter.fontMetrics().height(), value_label);
        }
    }
}

QPainterPath TimeLineAxis::cursorShape() const
{
    QPainterPath cursor_shape;
    auto cursor_width = cursorWidth();
    cursor_shape.moveTo(0, 0);
    cursor_shape.lineTo(0, cursor_height_ * 0.8);
    cursor_shape.lineTo(cursor_width / 2, cursor_height_);
    cursor_shape.lineTo(cursor_width, cursor_height_ * 0.8);
    cursor_shape.lineTo(cursor_width, 0);
    cursor_shape.lineTo(0, 0);
    cursor_shape.translate(cursor_pos_);
    return cursor_shape;
}

QPainterPath TimeLineAxis::shape() const
{
    QPainterPath line_path;
    line_path.moveTo(cursorWidth() / 2, cursor_height_);
    line_path.lineTo(cursorWidth() / 2, height());
    line_path.translate(cursor_pos_);
    QPainterPath shape_path;
    shape_path.addPath(cursorShape());
    shape_path.addPath(line_path);
    return shape_path;
}
