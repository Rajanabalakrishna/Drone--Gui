#include "compass.h"

Compass::Compass(QWidget *parent)
    : QWidget(parent), m_azimuth(0.0)
{
    // Start timer for periodic updates (optional)
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &Compass::update);
    m_timer->start(100); // Update every 100ms
}

Compass::~Compass()
{
    delete m_timer;
}

void Compass::setAzimuth(qreal azimuth)
{
    if (qFuzzyCompare(m_azimuth, azimuth)) {
        return;
    }

    m_azimuth = azimuth;
    emit azimuthChanged(m_azimuth);
    update();
}

void Compass::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Draw compass background (e.g., circular)
    painter.setBrush(QBrush(Qt::lightGray));
    painter.drawEllipse(rect());

    // Draw compass needle
    float needleAngle = -m_azimuth * M_PI / 180.0; // Convert to radians

    // Calculate needle end point
    QPointF center = rect().center();
    float radius = qMin(width(), height()) * 0.4;
    QPointF needleEnd(center.x() + radius * cos(needleAngle), center.y() + radius * sin(needleAngle));

    // Draw needle
    painter.setPen(QPen(Qt::black, 2));
    painter.drawLine(center, needleEnd);

    // Draw north marker (optional)
    painter.drawLine(center, center + QPointF(radius * 0.8, 0));
}
