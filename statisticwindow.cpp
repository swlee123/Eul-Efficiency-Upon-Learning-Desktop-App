#include "statisticwindow.h"
#include "./ui_statisticwindow.h"
#include<Qtimer>
#include<QMessageBox>
#include<QtMultimedia>

#include<QtSql/QSqlDatabase>
#include<QtSql/QSqlError>
#include<QSqlQuery>
#include<iostream>
#include<QTableView>
#include<QSqlTableModel>
#include<QtCharts>

StatisticWindow::StatisticWindow(QWidget *parent)
    : QMainWindow(parent)
    ,stat_ui(new Ui::StatisticWindow)
{
    // Set the window title and size
    stat_ui->setupUi(this);
    setWindowTitle("Previous Statistic");

}

StatisticWindow::~StatisticWindow()
{
    delete stat_ui;
}


int StatisticWindow::calculate_tag_perday(QString tag,QString date)
{
    QSqlQuery query;
    query.prepare("SELECT Duration FROM focus_record WHERE Type = :type AND Date = :date ; ");
    query.bindValue(":type",tag);
    query.bindValue(":date",date);
    if (!query.exec()) {
        qDebug() << "Error retrieving tag and date data from database:" << query.lastError().text();
    }

    int totalDuration = 0;
    while (query.next()) {
        int duration = query.value(0).toInt(); // assuming Duration is stored as an integer
        totalDuration += duration;
    }

    return totalDuration/60;

}

void StatisticWindow::show_3_days()
{

    QString today = QDateTime::currentDateTime().toString("yyyy-MM-dd");
    QString yes = QDateTime::currentDateTime().addDays(-1).toString("yyyy-MM-dd");
    QString yes_yes = QDateTime::currentDateTime().addDays(-2).toString("yyyy-MM-dd");

    QBarSet *set0 = new QBarSet("Coding");
    QBarSet *set1 = new QBarSet("Study");
    QBarSet *set2 = new QBarSet("Reading");
    QBarSet *set3 = new QBarSet("Nap");

    *set0 << calculate_tag_perday("Coding",yes_yes) << calculate_tag_perday("Coding",yes)<<calculate_tag_perday("Coding",today);
    *set1 << calculate_tag_perday("Study",yes_yes)<< calculate_tag_perday("Study",yes)<<calculate_tag_perday("Study",today);
    *set2 << calculate_tag_perday("Reading",yes_yes)<< calculate_tag_perday("Reading",yes)<<calculate_tag_perday("Reading",today);
    *set3 << calculate_tag_perday("Nap",yes_yes)<< calculate_tag_perday("Nap",yes)<<calculate_tag_perday("Nap",today);


    QBarSeries *series = new QBarSeries();
    series->append(set0);
    series->append(set1);
    series->append(set2);
    series->append(set3);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Focus Time Past 3 Days");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QStringList categories;
    categories << yes_yes << yes << today ;
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0,500);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    setCentralWidget(chartView);
    chartView->lower();
}

void StatisticWindow::show_7_days()
{
    QString today = QDateTime::currentDateTime().toString("yyyy-MM-dd");
    QString day1 = QDateTime::currentDateTime().addDays(-1).toString("yyyy-MM-dd");
    QString day2 = QDateTime::currentDateTime().addDays(-2).toString("yyyy-MM-dd");
    QString day3 = QDateTime::currentDateTime().addDays(-3).toString("yyyy-MM-dd");
    QString day4 = QDateTime::currentDateTime().addDays(-4).toString("yyyy-MM-dd");
    QString day5 = QDateTime::currentDateTime().addDays(-5).toString("yyyy-MM-dd");
    QString day6 = QDateTime::currentDateTime().addDays(-6).toString("yyyy-MM-dd");

    QBarSet *set0 = new QBarSet("Coding");
    QBarSet *set1 = new QBarSet("Study");
    QBarSet *set2 = new QBarSet("Reading");
    QBarSet *set3 = new QBarSet("Nap");

    *set0 << calculate_tag_perday("Coding",day6)<< calculate_tag_perday("Coding",day5)<< calculate_tag_perday("Coding",day4)<< calculate_tag_perday("Coding",day3)<< calculate_tag_perday("Coding",day2) << calculate_tag_perday("Coding",day1)<<calculate_tag_perday("Coding",today);
    *set1 << calculate_tag_perday("Study",day6)<< calculate_tag_perday("Study",day5)<< calculate_tag_perday("Study",day4)<< calculate_tag_perday("Study",day3)<< calculate_tag_perday("Study",day2) << calculate_tag_perday("Study",day1)<<calculate_tag_perday("Study",today);
    *set2 << calculate_tag_perday("Reading",day6)<< calculate_tag_perday("Reading",day5)<< calculate_tag_perday("Reading",day4)<< calculate_tag_perday("Reading",day3)<< calculate_tag_perday("Reading",day2) << calculate_tag_perday("Reading",day1)<<calculate_tag_perday("Reading",today);
    *set3 << calculate_tag_perday("Nap",day6)<< calculate_tag_perday("Nap",day5)<< calculate_tag_perday("Nap",day4)<< calculate_tag_perday("Nap",day3)<< calculate_tag_perday("Nap",day2) << calculate_tag_perday("Nap",day1)<<calculate_tag_perday("Nap",today);


    QBarSeries *series = new QBarSeries();
    series->append(set0);
    series->append(set1);
    series->append(set2);
    series->append(set3);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Focus Time Past 7 Days");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QStringList categories;
    categories <<day6<<day5<<day4<<day3<< day2 << day1 << today ;
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0,500);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    setCentralWidget(chartView);
    chartView->lower();
}




