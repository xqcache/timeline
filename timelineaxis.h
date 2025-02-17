#pragma once

#include <QPainterPath>
#include <QWidget>

class TimeLineView;

class TimeLineAxis : public QWidget {
    Q_OBJECT
public:
    explicit TimeLineAxis(QWidget* parent);

    inline qreal cursorHeight() const;
    inline qreal cursorWidth() const;
    int cursorValue() const;
    int maxCursorValue() const;

    inline int scaleCount() const;
    inline int tickCount() const;

    inline void setCursorHeight(qreal height);

    void moveCursor(int value);
    void updateScale();

signals:
    void cursorValueChanged(int value);

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

    void resizeEvent(QResizeEvent* event) override;
    void paintEvent(QPaintEvent* event) override;

private:
    QPainterPath cursorShape() const;
    QPainterPath shape() const;

private:
    bool cursor_picked_ { false };
    QPointF cursor_pos_ { 0, 0 };
    qreal cursor_height_ = 38.0;

    qreal scale_pixels_ = 10;
    int tick_count_ = 10;
    int value_offset_ = 0;
};

inline qreal TimeLineAxis::cursorHeight() const
{
    return cursor_height_;
}

inline qreal TimeLineAxis::cursorWidth() const
{
    return cursor_height_ * 0.5;
}

inline int TimeLineAxis::scaleCount() const
{
    return qRound(width() / scale_pixels_) / tick_count_ * tick_count_;
}

inline int TimeLineAxis::tickCount() const
{
    return tick_count_;
}

inline void TimeLineAxis::setCursorHeight(qreal height)
{
    cursor_height_ = height;
    update();
}
