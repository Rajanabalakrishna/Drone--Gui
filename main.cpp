#include "mainwindow.h"

#include <QApplication>
#include<QWidget>
#include<QCamera>
#include<QMediaCaptureSession>
#include<QVideoSink>
#include<QVideoWidget>
#include<QVBoxLayout>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile file("C:\\New folder (4)\\Motor_Count.qss.txt");
    if(file.open(QFile::ReadOnly))
    {
        QString styleSheet=QLatin1String(file.readAll());
        a.setStyleSheet(styleSheet);
        file.close();

    }
    MainWindow w;



    w.show();
    return a.exec();
}
