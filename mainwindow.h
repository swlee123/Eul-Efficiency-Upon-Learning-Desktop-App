#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QWidget>
#include <QSqlDatabase>
#include <QMediaPlayer>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow;
               class StatisticWindow;} // include statistic window ,mainwindow in Ui
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT // MOC ,allow to create signals and slots
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:


    void on_button_30_clicked();

    void on_button_40_clicked();

    void on_button_60_clicked();

    void on_Stop_clicked();

    void openNewWindow();

    void show_stat_window_3_days();

    void show_stat_window_7_days();

    void saveFocusTime(int time);

    void play_anime_lofi();

    void show_database();
private:
    Ui::MainWindow *ui;
    int m_duration = 0;
    QSqlDatabase m_db;
    QMediaPlayer*m_player;
};





#endif // MAINWINDOW_H
