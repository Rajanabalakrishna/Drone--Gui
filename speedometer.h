#ifndef SPEEDOMETER_H
#define SPEEDOMETER_H

#include <QWidget>
#include <QConicalGradient>
#include <QColor>

class Speedometer : public QWidget {
    Q_OBJECT
    Q_PROPERTY(double speed READ speed WRITE setSpeed)
    Q_PROPERTY(double power READ power WRITE setPower)
    Q_PROPERTY(QString unit READ unit WRITE setUnit)
    Q_PROPERTY(QConicalGradient powerGradient READ powerGradient WRITE setPowerGradient)
    Q_PROPERTY(bool displayPowerPath READ displayPowerPath WRITE setDisplayPowerPath)
    Q_PROPERTY(QColor unitTextColor READ unitTextColor WRITE setUnitTextColor)
    Q_PROPERTY(QColor speedTextColor READ speedTextColor WRITE setSpeedTextColor)
    Q_PROPERTY(QColor powerPathColor READ powerPathColor WRITE setPowerPathColor)

public:
    explicit Speedometer(QWidget *parent = nullptr);

    // Speedometer properties
    double speed() const { return m_speed; }
    void setSpeed(double speed);              // Overload for double
    void setSpeed(int speed);                 // Overload for int

    double power() const { return m_power; }
    void setPower(double power);              // Overload for double
    void setPower(int power);                 // Overload for int

    QString unit() const { return m_unit; }
    void setUnit(const QString &unit);

    QConicalGradient powerGradient() const { return m_powerGradient; }
    void setPowerGradient(const QConicalGradient &gradient);

    bool displayPowerPath() const { return m_displayPowerPath; }
    void setDisplayPowerPath(bool displayPowerPath);

    QColor unitTextColor() const { return m_unitTextColor; }
    void setUnitTextColor(const QColor &color);

    QColor speedTextColor() const { return m_speedTextColor; }
    void setSpeedTextColor(const QColor &color);

    QColor powerPathColor() const { return m_powerPathColor; }
    void setPowerPathColor(const QColor &color);

    // New geometry management methods
    void setGeometry(int x, int y, int width, int height);
    QRect geometry() const { return QRect(m_x, m_y, m_width, m_height); }

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    double m_speed = 0.0;
    double m_power = 0.0;
    QString m_unit = "km/h";
    QConicalGradient m_powerGradient;
    bool m_displayPowerPath = true;
    QColor m_unitTextColor = Qt::gray;
    QColor m_speedTextColor = Qt::black;
    QColor m_powerPathColor = Qt::gray;

    // Geometry attributes
    int m_x = 0;
    int m_y = 0;
    int m_width = 200;
    int m_height = 200;
};

#endif // SPEEDOMETER_H
