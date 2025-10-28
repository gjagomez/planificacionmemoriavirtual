#ifndef SCHEDULETIMELINEWIDGET_H
#define SCHEDULETIMELINEWIDGET_H

#include <QWidget>

#include "simulations/scheduling/scheduler.h"

class ScheduleTimelineWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ScheduleTimelineWidget(QWidget *parent = nullptr);

    void setTimeline(const QVector<ScheduleEvent> &timeline);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QColor colorForProcess(const QString &pid) const;
    QVector<ScheduleEvent> m_timeline;
};

#endif // SCHEDULETIMELINEWIDGET_H
