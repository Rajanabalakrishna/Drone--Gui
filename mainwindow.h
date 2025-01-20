#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QtCore>
#include<QCamera>
#include<QMediaCaptureSession>
#include<QVideoWidget>
#include<QPushButton>
#include<QVBoxLayout>
#include<Qlabel>
#include<QtGui>
#include<QtCharts>
#include<QRegion>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void update(const QString &text);
    ~MainWindow();



private slots:

    void on_lineEdit_textChanged(const QString &arg1);
    void toggleCamera();


private:
    Ui::MainWindow *ui;
    QCamera *camera;
    QMediaCaptureSession *captureSession;
    QVideoWidget *videoWidget;
    QPushButton *toggleButton;
    QLabel *imageLabel;

};
#endif // MAINWINDOW_H
