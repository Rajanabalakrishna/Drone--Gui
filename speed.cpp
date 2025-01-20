#include "speed.h"
#include <QPainter>
#include <QFont>
#include <QPixmap>
#include <QDebug>

Speed::Speed(QWidget *parent) : QWidget(parent), m_speed(0.0)
{
}

void Speed::setSpeed(double speed)
{
    m_speed = speed;
    update(); // Request a repaint
}

void Speed::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing); // Enable antialiasing for smoother rendering

    // Calculate the center of the widget
    int centerX = width() / 2;
    int centerY = height() / 2;
    int radius = qMin(width(), height()) / 2 - 10; // Adjust padding as needed

    // Draw the thick neon cyan border
    painter.setPen(QPen(QColor(0, 128, 255), 10)); // Neon cyan color and thickness
    painter.setBrush(Qt::NoBrush);
    painter.drawEllipse(centerX - radius, centerY - radius, radius * 2, radius * 2);

    // Draw the background circle
    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(QColor(50, 50, 50))); // Dark gray background
    painter.drawEllipse(centerX - radius, centerY - radius, radius * 2, radius * 2);

    // Draw the blue arc
    painter.setPen(QPen(QColor(0, 128, 255), 7)); // Neon cyan color
    painter.setBrush(Qt::NoBrush);
    painter.drawArc(centerX - radius + 5, centerY - radius + 5, radius * 2 - 10, radius * 2 - 10, 135 * 16, 270 * 16);

    // Draw the needle
    double maxSpeed = 100.0; // Adjust max speed as needed
    double needleAngle = 135 + (m_speed / maxSpeed) * 270; // Calculate needle angle
    QPointF needleEnd = QPointF(centerX + radius * 0.75 * qCos(needleAngle * M_PI / 180),
                                centerY + radius * 0.75 * qSin(needleAngle * M_PI / 180));
    painter.setPen(QPen(QColor(0, 128, 255), 2)); // Neon cyan needle
    painter.drawLine(QPointF(centerX, centerY), needleEnd);

    // Draw speed markings (0, 20, 40, 60, 80, 100)
    QFont font;
    font.setPointSize(8);
    painter.setFont(font);
    painter.setPen(QColor(255, 255, 255)); // White text

    for (int i = 0; i <= 100; i += 20) {
        double angle = 135 + (i / maxSpeed) * 270;
        painter.drawText(QPointF(centerX + (radius - 20) * qCos(angle * M_PI / 180),
                                 centerY + (radius - 20) * qSin(angle * M_PI / 180)),
                         QString::number(i));
    }

    // Draw the fuel gauge icon (replace with your actual icon)
    QPixmap fuelGaugeIcon("C:\\Users\\balak\\Downloads\\icons8-fuel-gas-96.png"); // Replace with the actual icon file path
    painter.drawPixmap(centerX - 20, centerY + radius - 20, 40, 40, fuelGaugeIcon);

    // Draw the battery icon (replace with your actual icon)
    QPixmap batteryIcon("C:\\Users\\balak\\Downloads\\icons8-empty-battery-100.png"); // Replace with the actual icon file path
    painter.drawPixmap(centerX - 20, centerY - radius + 20, 40, 40, batteryIcon);
}
