#pragma once

#include <QtWidgets>

class TimeLineAxis;
class TimeLineScene;
class TimeLineView : public QGraphicsView {
    Q_OBJECT
public:
    explicit TimeLineView(QWidget* parent = nullptr);

    void setCursorHeight(qreal height);

protected:
    bool event(QEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;

private slots:
    void onHBarValueChanged(int value);
    void onVBarValueChanged(int value);
    void onCursorValueChanged(int value);

private:
    void setupSignals();

private:
    TimeLineScene* scene_ { nullptr };
    TimeLineAxis* axis_ { nullptr };

    QScrollBar* hbar_ { nullptr };
    QScrollBar* vbar_ { nullptr };
};
