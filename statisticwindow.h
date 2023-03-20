#ifndef STATISTICWINDOW_H
#define STATISTICWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QWidget>
#include <QSqlDatabase>


QT_BEGIN_NAMESPACE
namespace Ui { class StatisticWindow;} // include statistic window ,mainwindow in Ui
QT_END_NAMESPACE

// another window class to display statistic

class StatisticWindow : public QMainWindow
{
    Q_OBJECT;
public:
    StatisticWindow(QWidget *parent = nullptr);
    ~StatisticWindow();
    void show_3_days();
    void show_7_days();

private slots:
    int calculate_tag_perday(QString tag,QString date);


private:
    Ui::StatisticWindow *stat_ui;

};

#endif // STATISTICWINDOW_H
