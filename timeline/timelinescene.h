#pragma once

#include <QGraphicsScene>

class QStandardItemModel;

class TimeLineAxis;
class TimeLineView;
class TimeLineRow;
class TimeLineScene : public QGraphicsScene {
    Q_OBJECT
public:
    explicit TimeLineScene(TimeLineView& view);

    void setViewportSize(const QSizeF& size);

    inline TimeLineView& view();
    inline const TimeLineView& view() const;
    inline const QSizeF& viewportSize() const;

    void setModel(QStandardItemModel* model);
    inline QStandardItemModel* model() const;

private:
    TimeLineView& view_;
    QSizeF viewport_size_;

    std::vector<TimeLineRow*> row_items_;
    QStandardItemModel* model_ { nullptr };
};

inline TimeLineView& TimeLineScene::view()
{
    return view_;
}

inline const TimeLineView& TimeLineScene::view() const
{
    return view_;
}

inline const QSizeF& TimeLineScene::viewportSize() const
{
    return viewport_size_;
}

inline QStandardItemModel* TimeLineScene::model() const
{
    return model_;
}
