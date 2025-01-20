#include "speedometer.h"
#include <QPainter>
#include <QPainterPath>
#include <QFontMetricsF>

Speedometer::Speedometer(QWidget *parent) : QWidget(parent) {
    m_powerGradient = QConicalGradient(0, 0, 180);
    m_powerGradient.setColorAt(0, Qt::red);
    m_powerGradient.setColorAt(0.375, Qt::yellow);
    m_powerGradient.setColorAt(0.75, Qt::green);
}

void Speedometer::setSpeed(double speed) {
    m_speed = speed;
    update();
}

void Speedometer::setSpeed(int speed) {
    setSpeed(static_cast<double>(speed));
}

void Speedometer::setPower(double power) {
    m_power = power;
    update();
}

void Speedometer::setPower(int power) {
    setPower(static_cast<double>(power));
}

void Speedometer::setUnit(const QString &unit) {
    m_unit = unit;
    update();
}

void Speedometer::setPowerGradient(const QConicalGradient &gradient) {
    m_powerGradient = gradient;
    update();
}

void Speedometer::setDisplayPowerPath(bool displayPowerPath) {
    m_displayPowerPath = displayPowerPath;
    update();
}

void Speedometer::setUnitTextColor(const QColor &color) {
    m_unitTextColor = color;
    update();
}

void Speedometer::setSpeedTextColor(const QColor &color) {
    m_speedTextColor = color;
    update();
}

void Speedometer::setPowerPathColor(const QColor &color) {
    m_powerPathColor = color;
    update();
}

void Speedometer::setGeometry(int x, int y, int width, int height) {
    m_x = x;
    m_y = y;
    m_width = width;
    m_height = height;

    QWidget::setGeometry(x, y, width, height);
    update();
}

void Speedometer::paintEvent(QPaintEvent *) {
    static const QRectF extRect(-90, -90, 180, 180);
    static const QRectF intRect(-70, -70, 140, 140);
    static const QRectF unitRect(-44, 36, 86, 17);

    int speedInt = static_cast<int>(m_speed);
    int speedDec = static_cast<int>(m_speed * 10.0) % 10;
    QString s_SpeedInt = QString::number(speedInt).append('.');
    QString s_SpeedDec = QString::number(speedDec);

    double powerAngle = m_power * 270.0 / 100.0;

    QPainterPath powerPath;
    powerPath.moveTo(0, -70);
    powerPath.arcTo(extRect, 90, -powerAngle);
    powerPath.lineTo(0, -70);
    powerPath.arcTo(intRect, 90 - powerAngle, powerAngle);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate(width() / 2, height() / 2);
    int side = qMin(width(), height());
    painter.scale(side / 200.0, side / 200.0);

    painter.setBrush(m_powerGradient);
    painter.setPen(Qt::NoPen);
    painter.drawPath(powerPath);

    painter.setPen(m_unitTextColor);
    QFont unitFont = font();
    unitFont.setPointSize(18);
    painter.setFont(unitFont);
    painter.drawText(unitRect, Qt::AlignCenter, m_unit);

    painter.setPen(m_speedTextColor);
    QFont speedFont = font();
    speedFont.setPointSize(48);
    painter.setFont(speedFont);

    QFontMetricsF fm(speedFont);
    double speedWidth = fm.horizontalAdvance(s_SpeedInt);
    double speedDecWidth = fm.horizontalAdvance(s_SpeedDec) / 2.0;

    painter.drawText(-speedWidth / 2, 10, s_SpeedInt);
    painter.setFont(speedFont);
    painter.drawText(speedWidth / 2 - speedDecWidth, 10, s_SpeedDec);
}
