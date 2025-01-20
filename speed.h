#ifndef SPEED_H
#define SPEED_H

#include <QWidget>

class Speed : public QWidget
{
    Q_OBJECT

public:
    Speed(QWidget *parent = nullptr);

    void setSpeed(double speed);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    double m_speed;
};

#endif // SPEED_H
