#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "speedometer.h"
#include <QTimer>
#include<QVideoSink>
#include <QRandomGenerator>
#include<QPixmap>
#include <QVBoxLayout>
#include<QRectF>
#include<QGraphicsDropShadowEffect>
#include<QRegion>
#include"speed.h"
#include<QtCharts/QValueAxis>
#include<QtCharts/QChartView>
#include<QPen>
#include<QLinearGradient>
#include<QLinearGradient>

struct HardwareData {
    double speed;
    double torque;
    double esc;
};

HardwareData fetchHardwareData() {
    // Replace with actual hardware interaction logic
    HardwareData data;
    data.speed = rand() % 100;    // Example: Simulated random speed
    data.torque = rand() % 50;    // Example: Simulated random torque
    data.esc = rand() % 20;       // Example: Simulated random ESC
    return data;
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),camera(new QCamera(this)),captureSession(new QMediaCaptureSession(this))
{
    ui->setupUi(this);

    QGroupBox *groupBox = findChild<QGroupBox *>("group1");
    if (!groupBox) {
        qWarning("GroupBox 'group1' not found!");
        return;
    }

    QGroupBox *groupBox2 = findChild<QGroupBox *>("group2");
    if (!groupBox2) {
        qWarning("GroupBox 'group1' not found!");
        return;
    }

    QGroupBox *groupBox3 = findChild<QGroupBox *>("group3");
    if (!groupBox) {
        qWarning("GroupBox 'group1' not found!");
        return;
    }
    QGroupBox *groupBox4 = findChild<QGroupBox *>("group4");
    if (!groupBox) {
        qWarning("GroupBox 'group1' not found!");
        return;
    }

    QGroupBox *groupBox5 = findChild<QGroupBox *>("group5");
    if (!groupBox) {
        qWarning("GroupBox 'group1' not found!");
        return;
    }











    // Create the speedometer widget
    Speed  *speedometerWidget= new Speed(this);

    // Set the geometry of the speedometer widget
    speedometerWidget->setGeometry(550, 400, 200, 200); // Example geometry

    // Add the speedometer widget to the main window
    layout()->addWidget(speedometerWidget);

    QVBoxLayout *layout6 = new QVBoxLayout(groupBox4);
    layout6->addWidget(speedometerWidget);
    groupBox4->setLayout(layout6);



    // Create and apply the shadow effect
    QGraphicsDropShadowEffect* shadow = new QGraphicsDropShadowEffect(this);
    shadow->setBlurRadius(25);
    shadow->setColor(QColor(0, 255, 255));
    shadow->setOffset(0, 0);
    ui->Motor_Count->setGraphicsEffect(shadow);

    ui->Motor_Count->setStyleSheet(
        "color: rgb(0, 255, 255);"
        "color: rgb(0, 255, 255, 150); /* Dimmed color for normal state */"
        "color: rgb(0, 255, 255); /* Bright color for hover state */"
        );

    ui->label->setStyleSheet(
        "background-color: rgba(0, 255, 255,250); /* Neon Cyan background with some transparency */"
        "border-radius: 10px;"
        "color: black;"
        "font-weight: bold;"
        );

    ui->label_2->setStyleSheet(
        "background-color: rgba(0, 255, 255,250); /* Neon Cyan background with some transparency */"
        "border-radius: 10px;"
        "color: black;"
        "font-weight: bold;"
        );

    ui->Motor_Count_2->setGraphicsEffect(shadow);

    ui->Motor_Count_2->setStyleSheet(
        "color: rgb(0, 255, 255);"
        "color: rgb(0, 255, 255, 150); /* Dimmed color for normal state */"
        "color: rgb(0, 255, 255); /* Bright color for hover state */"
        );

    ui->Motor_Count_3->setGraphicsEffect(shadow);

    ui->Motor_Count_3->setStyleSheet(
        "color: rgb(0, 255, 255);"
        "color: rgb(0, 255, 255, 150); /* Dimmed color for normal state */"
        "color: rgb(0, 255, 255); /* Bright color for hover state */"
        );

    ui->Motor_Count_4->setGraphicsEffect(shadow);

    ui->Motor_Count_4->setStyleSheet(
        "color: rgb(0, 255, 255);"
        "color: rgb(0, 255, 255, 150); /* Dimmed color for normal state */"
        "color: rgb(0, 255, 255); /* Bright color for hover state */"
        );








    QVideoWidget *videoWidget=ui->videoWidget;
    // videoWidget->setGeometry(500,500,200,200);

    captureSession->setCamera(camera);
    captureSession->setVideoOutput(videoWidget); // Connect camera output to the video widget

    // Set up the toggle button from the UI
    toggleButton = ui->toggleButton; // Assuming a QPushButton named "toggleButton" in the UI

    // Connect the button click to toggleCamera() slot
    connect(toggleButton, &QPushButton::clicked, this, &MainWindow::toggleCamera);

    imageLabel=new QLabel(this);
    imageLabel->setAlignment(Qt::AlignCenter);

    // QPixmap pixmap("C:\\Users\\balak\\Downloads\\DJI Avata 2 STEALTH Upgrade Propellers - x4 Black.jpg");
    //  if(!pixmap.isNull())
    //   {
    //      imageLabel->setPixmap(pixmap.scaled(400,300,Qt::KeepAspectRatio));
    //   }
    //   else
    //   {
    //       imageLabel->setText("Failed to load image");
    //  }
    //  imageLabel->setGeometry(1040,30,150,100);




    QLineSeries *series =new QLineSeries();
    series->append(0,3);
    series->append(1,5);
    series->append(2,7);
    series->append(3,8);
    series->append(4,1);
    series->append(5,5);
    series->append(6,10);
    series->append(7,9);
    series->append(8,4);
    series->append(9,3);

    QPen pen(QColor(0,255,255,180));
    pen.setWidth(3);
    series->setPen(pen);

    QLinearGradient gradient(QPointF(0,0),QPointF(0,1));
    gradient.setColorAt(0.0,QColor("#000000"));
    gradient.setColorAt(1.0, QColor("#1b1f2f")); // Dark blueish at the bottom  102133
    gradient.setCoordinateMode(QGradient::ObjectBoundingMode);
    QBrush fillBrush(gradient);

    QAreaSeries *areaSeries = new QAreaSeries(series);
    areaSeries->setName("Filled Area");
    areaSeries->setBrush(fillBrush);
    areaSeries->setPen(QPen(QColor(0, 255, 255), 2)); // Light cyan outline


    QLineSeries *torqueSeries=new QLineSeries();
    for(int i=0; i<10; i++)
    {
        torqueSeries->append(i,rand()%50);

    }
    torqueSeries->setPen(pen);
    QAreaSeries *areaSeries1 = new QAreaSeries(torqueSeries);
    areaSeries1->setName("Filled Area");
    areaSeries1->setBrush(fillBrush);
    areaSeries1->setPen(QPen(QColor(0, 255, 255), 2)); // Light cyan outline

    QLineSeries *thrustSeries= new QLineSeries();
    for(int i=0; i<10; i++)
    {
        thrustSeries->append(i,rand()%50);
    }

    thrustSeries->setPen(pen);
    QAreaSeries *areaSeries2 = new QAreaSeries(thrustSeries);
    areaSeries2->setName("Filled Area");
    areaSeries2->setBrush(fillBrush);
    areaSeries2->setPen(QPen(QColor(0, 255, 255), 2)); // Light cyan outline


    QLineSeries *voltageSeries= new QLineSeries();

    voltageSeries->append(0,0);
    voltageSeries->append(1,2.5);
    voltageSeries->append(2,5);
    voltageSeries->append(3,7.5);
    voltageSeries->append(4,10);
    voltageSeries->append(5,7.5);
    voltageSeries->append(6,5);
    voltageSeries->append(7,2.5);
    voltageSeries->append(8,0);

    voltageSeries->setPen(pen);
    QAreaSeries *areaSeries3 = new QAreaSeries(voltageSeries);
    areaSeries3->setName("Filled Area");
    areaSeries3->setBrush(fillBrush);
    areaSeries3->setPen(QPen(QColor(0, 255, 255), 2)); // Light cyan outline




    QChart *chart =new QChart();
    chart->legend()->hide();
    chart->addSeries(areaSeries);
    chart->createDefaultAxes();
    chart->setMargins(QMargins(0,0,0,0));
    chart->setBackgroundRoundness(0);
    chart->axes(Qt::Vertical).first()->setRange(0,100);
    chart->axes(Qt::Horizontal).first()->setRange(0,10);
    //QRectF rect(400,400,500,500);
    chart->setGeometry(200,200,50,50);
    chart->setBackgroundBrush(gradient);
   // chart->setBackgroundPen(Qt::NoPen); // Remove border lines

    QValueAxis *axisX = new QValueAxis();
    axisX->setRange(0, 10);
    //axisX->setTitleText("X Axis");
    axisX->setLinePenColor(QColor(0, 255, 255));
    axisX->setLabelsColor(QColor(0, 255, 255)); // Neon color for labels
    axisX->setGridLineColor(QColor(80, 80, 80, 50));//(QColor(0, 100, 100, 50));

    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0, 40);
   // axisY->setTitleText("Y Axis");
    axisY->setLinePenColor(QColor(0, 255, 255));
    axisY->setLabelsColor(QColor(0, 255, 255));
    axisY->setGridLineColor(QColor(80, 80, 80, 50)); // Faint grid lines


    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisX);
    series->attachAxis(axisY);


    axisX->setGridLinePen(QPen(QColor(0, 255, 255, 50))); // Transparent grid
    axisY->setGridLinePen(QPen(QColor(0, 255, 255, 50)));

    axisX->setGridLineVisible(false);
    axisY->setGridLineVisible(false);

    chart->setVisible(true);

    QChart *voltageChart= new QChart();
    voltageChart->legend()->hide();
    voltageChart->addSeries(voltageSeries);
    voltageChart->createDefaultAxes();
    voltageChart->axes(Qt::Vertical).first()->setRange(0,11);
    voltageChart->axes(Qt::Horizontal).first()->setRange(0,9);
    voltageChart->setVisible(true);

    QChart *chart3 =new QChart();
    //chart->legend()->hide();
    voltageChart->addSeries(areaSeries3);
    // toChart->createDefaultAxes();
    voltageChart->setMargins(QMargins(0,0,0,0));
    voltageChart->setBackgroundRoundness(0);
    voltageChart->axes(Qt::Vertical).first()->setRange(0,100);
    voltageChart->axes(Qt::Horizontal).first()->setRange(0,10);
    //QRectF rect(400,400,500,500);
    //torqueChart->setGeometry(200,200,50,50);
    voltageChart->setBackgroundBrush(gradient);
    // chart->setBackgroundPen(Qt::NoPen); // Remove border lines

    QValueAxis *axisX3 = new QValueAxis();
    axisX3->setRange(0, 10);
    //axisX->setTitleText("X Axis");
    axisX3->setLinePenColor(QColor(0, 255, 255));
    axisX3->setLabelsColor(QColor(0, 255, 255)); // Neon color for labels
    axisX3->setGridLineColor(QColor(80, 80, 80, 50));//(QColor(0, 100, 100, 50));

    QValueAxis *axisY3 = new QValueAxis();
    axisY3->setRange(0, 40);
    // axisY->setTitleText("Y Axis");
    axisY3->setLinePenColor(QColor(0, 255, 255));
    axisY3->setLabelsColor(QColor(0, 255, 255));
    axisY3->setGridLineColor(QColor(80, 80, 80, 50)); // Faint grid lines


    voltageChart->addAxis(axisX3, Qt::AlignBottom);
    voltageChart->addAxis(axisY3, Qt::AlignLeft);
    voltageSeries->attachAxis(axisX3);
    voltageSeries->attachAxis(axisY3);


    axisX3->setGridLinePen(QPen(QColor(0, 255, 255, 50))); // Transparent grid
    axisY3->setGridLinePen(QPen(QColor(0, 255, 255, 50)));

    axisX3->setGridLineVisible(false);
    axisY3->setGridLineVisible(false);




    QChart *thrustChart= new QChart();
    thrustChart->legend()->hide();
    thrustChart->addSeries(thrustSeries);
    thrustChart->createDefaultAxes();
    thrustChart->axes(Qt::Vertical).first()->setRange(0,100);
    thrustChart->axes(Qt::Horizontal).first()->setRange(0,10);
    thrustChart->setVisible(true);

    QChart *chart2 =new QChart();
    //chart->legend()->hide();
    thrustChart->addSeries(areaSeries2);
   // toChart->createDefaultAxes();
    thrustChart->setMargins(QMargins(0,0,0,0));
    thrustChart->setBackgroundRoundness(0);
    thrustChart->axes(Qt::Vertical).first()->setRange(0,100);
    thrustChart->axes(Qt::Horizontal).first()->setRange(0,10);
    //QRectF rect(400,400,500,500);
    //torqueChart->setGeometry(200,200,50,50);
    thrustChart->setBackgroundBrush(gradient);
    // chart->setBackgroundPen(Qt::NoPen); // Remove border lines

    QValueAxis *axisX2 = new QValueAxis();
    axisX2->setRange(0, 10);
    //axisX->setTitleText("X Axis");
    axisX2->setLinePenColor(QColor(0, 255, 255));
    axisX2->setLabelsColor(QColor(0, 255, 255)); // Neon color for labels
    axisX2->setGridLineColor(QColor(80, 80, 80, 50));//(QColor(0, 100, 100, 50));

    QValueAxis *axisY2 = new QValueAxis();
    axisY2->setRange(0, 40);
    // axisY->setTitleText("Y Axis");
    axisY2->setLinePenColor(QColor(0, 255, 255));
    axisY2->setLabelsColor(QColor(0, 255, 255));
    axisY2->setGridLineColor(QColor(80, 80, 80, 50)); // Faint grid lines


    thrustChart->addAxis(axisX2, Qt::AlignBottom);
    thrustChart->addAxis(axisY2, Qt::AlignLeft);
    thrustSeries->attachAxis(axisX2);
    thrustSeries->attachAxis(axisY2);


    axisX2->setGridLinePen(QPen(QColor(0, 255, 255, 50))); // Transparent grid
    axisY2->setGridLinePen(QPen(QColor(0, 255, 255, 50)));

    axisX2->setGridLineVisible(false);
    axisY2->setGridLineVisible(false);




    QChart *torqueChart= new QChart();
    torqueChart->legend()->hide();
    torqueChart->addSeries(torqueSeries);
    torqueChart->createDefaultAxes();
    torqueChart->axes(Qt::Vertical).first()->setRange(0,100);
    torqueChart->axes(Qt::Horizontal).first()->setRange(0,10);
    torqueChart->setVisible(true);
    torqueChart->setGeometry(80,80,100,100);


    QChart *chart1 =new QChart();
    //chart->legend()->hide();
    torqueChart->addSeries(areaSeries1);
    torqueChart->createDefaultAxes();
    torqueChart->setMargins(QMargins(0,0,0,0));
    torqueChart->setBackgroundRoundness(0);
    torqueChart->axes(Qt::Vertical).first()->setRange(0,100);
    torqueChart->axes(Qt::Horizontal).first()->setRange(0,10);
    //QRectF rect(400,400,500,500);
    //torqueChart->setGeometry(200,200,50,50);
    torqueChart->setBackgroundBrush(gradient);
    // chart->setBackgroundPen(Qt::NoPen); // Remove border lines

    QValueAxis *axisX1 = new QValueAxis();
    axisX1->setRange(0, 10);
    //axisX->setTitleText("X Axis");
    axisX1->setLinePenColor(QColor(0, 255, 255));
    axisX1->setLabelsColor(QColor(0, 255, 255)); // Neon color for labels
    axisX1->setGridLineColor(QColor(80, 80, 80, 50));//(QColor(0, 100, 100, 50));

    QValueAxis *axisY1 = new QValueAxis();
    axisY1->setRange(0, 40);
    // axisY->setTitleText("Y Axis");
    axisY1->setLinePenColor(QColor(0, 255, 255));
    axisY1->setLabelsColor(QColor(0, 255, 255));
    axisY1->setGridLineColor(QColor(80, 80, 80, 50)); // Faint grid lines


    torqueChart->addAxis(axisX1, Qt::AlignBottom);
    torqueChart->addAxis(axisY1, Qt::AlignLeft);
    torqueSeries->attachAxis(axisX1);
    torqueSeries->attachAxis(axisY1);


    axisX1->setGridLinePen(QPen(QColor(0, 255, 255, 50))); // Transparent grid
    axisY1->setGridLinePen(QPen(QColor(0, 255, 255, 50)));

    axisX1->setGridLineVisible(false);
    axisY1->setGridLineVisible(false);

    //chart->setVisible(true);



    QChartView *chartview =new QChartView(chart,this);
    chartview->setRenderHint(QPainter::Antialiasing);
    chartview->setVisible(true);
  //   chartview->setBackgroundBrush(QBrush(QColor("#000000")));
    chartview->setContentsMargins(0, 0, 0, 0); // Remove content margins
    chartview->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    chartview->setGeometry(290,400,300,250);

    QVBoxLayout *layout = new QVBoxLayout(groupBox);
    layout->addWidget(chartview);
    groupBox->setLayout(layout);

    QChartView *voltageView= new QChartView(voltageChart,this);
    voltageView->setRenderHint(QPainter::Antialiasing);
    voltageView->setContentsMargins(0, 0, 0, 0);
     voltageView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    voltageView->setVisible(true);
    voltageView->setGeometry(290,150,200,200);

    QVBoxLayout *layout5 = new QVBoxLayout(groupBox3);
    layout5->addWidget(voltageView);
    groupBox3->setLayout(layout5);




    QChartView *thrustView= new QChartView(thrustChart,this);
    thrustView->setRenderHint(QPainter::Antialiasing);
     thrustView->setContentsMargins(0, 0, 0, 0);
    thrustView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    thrustView->setVisible(true);
    thrustView->setGeometry(30,400,200,200);

    QVBoxLayout *layout2 = new QVBoxLayout(groupBox5);
    layout2->addWidget(thrustView);
    groupBox5->setLayout(layout2);



    QChartView *torqueView=new QChartView(torqueChart,this);
    torqueView->setRenderHint(QPainter::Antialiasing);
    torqueView->setContentsMargins(0, 0, 0, 0); // Remove content margins
    torqueView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    torqueView->setVisible(true);
    torqueView->setGeometry(30,140,220,220);

    QVBoxLayout *layout1 = new QVBoxLayout(groupBox2);
    layout1->addWidget(torqueView);
    groupBox2->setLayout(layout1);





    // Create an instance of the Speedometer widget
    Speedometer *speedometer = new Speedometer(this);
    speedometer->setSpeed(0);

    // Example: Set initial speed, power, and unit
    speedometer->setPower(60.0); // Set power usage to 60%
    speedometer->setUnit("km/h"); // Set the unit to "km/h"
    QConicalGradient gradienta(0, 0, 180);
    gradienta.setColorAt(0.0, QColor(0, 255, 255)); // Neon cyan
    gradienta.setColorAt(0.5, QColor(0, 128, 255)); // Bright blue
    gradienta.setColorAt(1.0, QColor(0, 64, 128));  // Deep blue
    speedometer->setPowerGradient(gradienta);

    // Set text colors
    speedometer->setUnitTextColor(QColor(0, 255, 255));  // Neon cyan
    speedometer->setSpeedTextColor(QColor(0, 255, 255)); // Neon cyan

    // Set specific position and size
    speedometer->setGeometry(580, 462, 120, 100); // Place Speedometer at (550, 200) with size 150x150  setGeometry(550, 400, 200, 200); setGeometry(700, 150, 150, 150);



    // Connect QLineEdit to QProgressBar
    connect(ui->Speed, &QLineEdit::textChanged, this, [this](const QString &text) {
        bool ok;
        int value = text.toInt(&ok);
        if (ok) {
            ui->Sprogress->setValue(value); // Update the progress bar
        } else {
            ui->Sprogress->setValue(0); // Handle invalid input
        }
    });

    // Connect QLineEdit to Speedometer
    connect(ui->Speed, &QLineEdit::textChanged, this, [this, speedometer,series,speedometerWidget](const QString &text) {
        bool ok;
        int value = text.toInt(&ok);
        if (ok) {
            speedometer->setSpeed(value/10); // Update the speedometer
            speedometerWidget->setSpeed(value);
            for (int i = 0; i < series->count(); ++i) {
                QPointF point = series->at(i);
                series->replace(i, point.x(), value / 2.0 + i); // Example: Update Y with a formula
            }
        }
    }); // <- Correctly closed parentheses here

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [series]() {
        static int counter = 0;
        HardwareData data = fetchHardwareData();

        // Shift existing points and add new data
        for (int i = 0; i < series->count() - 1; ++i) {
            QPointF point = series->at(i + 1); // Shift points to the left
            series->replace(i, i, point.y());
        }
        series->replace(series->count() - 1, series->count() - 1, data.speed); // Add new speed

        // Example debug output
        qDebug() << "Speed:" << data.speed << "Torque:" << data.torque << "ESC:" << data.esc;

        counter++;
    });
    timer->start(100); // Fetch and update every 100ms



}

MainWindow::~MainWindow()
{
    delete ui;
    delete imageLabel;
}

void MainWindow::toggleCamera()
{
    if (camera->isActive()) {
        camera->stop();
        toggleButton->setText("Start Camera");
    } else {
        camera->start();
        toggleButton->setText("Stop Camera");
    }
}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    // No implementation needed in this case
}







