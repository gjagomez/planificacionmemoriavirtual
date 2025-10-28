#include "scheduletimelinewidget.h"

#include <QFontMetrics>
#include <QPainter>
#include <QPaintEvent>
#include <QPalette>
#include <QHash>

namespace {
constexpr int kTopPadding = 20;
constexpr int kBottomPadding = 30;
constexpr int kHorizontalPadding = 20;
}

ScheduleTimelineWidget::ScheduleTimelineWidget(QWidget *parent)
    : QWidget(parent)
{
    setMinimumHeight(220);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
}

void ScheduleTimelineWidget::setTimeline(const QVector<ScheduleEvent> &timeline)
{
    m_timeline = timeline;
    update();
}

void ScheduleTimelineWidget::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.fillRect(rect(), palette().base());

    if (m_timeline.isEmpty()) {
        painter.setPen(palette().color(QPalette::Disabled, QPalette::Text));
        painter.drawText(rect(), Qt::AlignCenter, tr("Ejecuta una simulacion para ver la linea de tiempo"));
        return;
    }

    int maxTime = 0;
    for (const ScheduleEvent &eventItem : m_timeline) {
        maxTime = std::max(maxTime, eventItem.endTime);
    }
    if (maxTime == 0) {
        return;
    }

    const QRect area = rect().adjusted(kHorizontalPadding, kTopPadding, -kHorizontalPadding, -kBottomPadding);
    QFontMetrics fm(font());

    // Dibujar bloques de procesos
    for (const ScheduleEvent &eventItem : m_timeline) {
        const double startRatio = static_cast<double>(eventItem.startTime) / maxTime;
        const double endRatio = static_cast<double>(eventItem.endTime) / maxTime;
        const int left = area.left() + static_cast<int>(area.width() * startRatio);
        const int right = area.left() + static_cast<int>(area.width() * endRatio);
        QRect block(left, area.top(), std::max(1, right - left), area.height() - 20);

        QColor blockColor = colorForProcess(eventItem.pid);
        painter.setPen(Qt::NoPen);
        painter.setBrush(blockColor);
        painter.drawRoundedRect(block, 6, 6);

        // Elegir color de texto con buen contraste
        QColor textColor = blockColor.lightness() < 128 ? Qt::white : Qt::black;
        painter.setPen(textColor);
        QString label = eventItem.pid;
        if (block.width() < fm.horizontalAdvance(label) + 6) {
            label = eventItem.pid.left(3); // Acortar a "p1", "p23", etc.
        }
        painter.drawText(block.adjusted(4, 0, -4, 0), Qt::AlignCenter, label);
    }

    // Dibujar línea de tiempo inferior
    painter.setPen(QPen(palette().color(QPalette::WindowText), 1.2));
    const int baselineY = area.bottom();
    painter.drawLine(area.left(), baselineY, area.right(), baselineY);

    // Etiquetas de tiempo en ticks
    for (const ScheduleEvent &eventItem : m_timeline) {
        const int x = area.left() + static_cast<int>(area.width() * (static_cast<double>(eventItem.startTime) / maxTime));
        painter.drawLine(x, baselineY, x, baselineY + 6);
        const QString label = QString::number(eventItem.startTime);
        painter.drawText(x - fm.horizontalAdvance(label) / 2, baselineY + fm.height() + 2, label);
    }

    // Etiqueta del tiempo final
    const QString endLabel = QString::number(maxTime);
    painter.drawLine(area.right(), baselineY, area.right(), baselineY + 6);
    painter.drawText(area.right() - fm.horizontalAdvance(endLabel) / 2, baselineY + fm.height() + 2, endLabel);
}

QColor ScheduleTimelineWidget::colorForProcess(const QString &pid) const
{
    // Color especial para el estado IDLE
    if (pid.compare(QStringLiteral("IDLE"), Qt::CaseInsensitive) == 0) {
        return QColor(130, 130, 140); // Gris suave
    }

    // Cache estático: asigna el mismo color a cada PID en todas las llamadas
    static QHash<QString, QColor> colorCache;

    if (!colorCache.contains(pid)) {
        const uint hash = qHash(pid);
        const int hue = static_cast<int>(hash % 360);
        // Valores ajustados para colores vivos, legibles y estéticamente agradables
        const int saturation = 180 + (hash % 50);   // 180–229
        const int lightness = 140 + (hash % 40);    // 140–179
        colorCache[pid] = QColor::fromHsl(hue, saturation, lightness);
    }

    return colorCache[pid];
}
