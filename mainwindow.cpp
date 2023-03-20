#include "mainwindow.h"
#include "statisticwindow.h"
#include "./ui_mainwindow.h"
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



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Eul- Efficiency Upon Learning");
    this->setWindowIcon(QIcon(":/icons/eul.png"));

    ui->label->setText("Pomodoro");
    ui->lcdNumber->display("00:00");
    ui->lcdNumber->setDigitCount(10);
    ui->lcdNumber->setSegmentStyle(QLCDNumber::Flat);


    // Connect the triggered signal of the newAction to a slot
    connect(ui->action3_day, &QAction::triggered, this,  &MainWindow::show_stat_window_3_days);
    connect(ui->action7_day, &QAction::triggered, this,  &MainWindow::show_stat_window_7_days);
    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::show_database);

    // SQlite database
    QSqlDatabase m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setHostName("localhost");
    m_db.setDatabaseName("Focusdb");
    m_db.setUserName("root");
    m_db.setPassword("");
    bool ok = m_db.open();
    if(!ok)
    {
        qDebug() << "Error connecting to database:" << m_db.lastError().text();
    }
    else{
        QStringList tables = m_db.tables();
        if(!tables.contains("focus_record"))
        {
            QSqlQuery query;
            query.exec("CREATE TABLE focus_record (Date TEXT,Start_time TEXT,End_time TEXT, Duration INTEGER,Type TEXT)");
            qDebug() << "Error creating table in database:" << query.lastError().text();

        }
    }



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openNewWindow()
{
    MainWindow *newWindow = new MainWindow(this);
    newWindow->show();
}


void MainWindow::show_database()
{
    QSqlTableModel *model = new QSqlTableModel;
    model->setTable("focus_record");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();


    QTableView *view = new QTableView;
    view->setModel(model);
    view->show();
}

void MainWindow::saveFocusTime(int time)
{

    QDateTime end_time = QDateTime::currentDateTime();
    QDateTime start_time = QDateTime::currentDateTime().addSecs(time*(-60));
    QSqlQuery query;
    query.prepare("INSERT INTO focus_record (Date,Start_time, End_time,Duration,Type) "
                  "VALUES ( :date,:start,:end,:duration,:type)");

    int duration = start_time.secsTo(end_time);
    QString date = start_time.toString("yyyy-MM-dd");

    query.bindValue(":date", date);
    query.bindValue(":start", start_time.toString("hh:mm:ss"));
    query.bindValue(":end", end_time.toString("hh:mm:ss"));
    query.bindValue(":duration", duration);
    query.bindValue(":type",ui->comboBox->currentText());

    // set back start_time and end_time to null
    start_time = QDateTime();
    end_time = QDateTime();

    if (!query.exec()) {
        qDebug() << "Error inserting data into database:" << query.lastError().text();
    }


}

void MainWindow::play_anime_lofi(){
    m_player = new QMediaPlayer;
    QAudioOutput*audioOutput = new QAudioOutput;
    m_player->setAudioOutput(audioOutput);
    m_player->setSource(QUrl::fromLocalFile("C:/Users/User/OneDrive/Desktop/Qt/focusreal/start_focus.wav"));
    audioOutput->setVolume(30);
    m_player->play();
}

void MainWindow::on_button_30_clicked()
{



    if(m_duration==0)
    {
        play_anime_lofi();
        QMessageBox::information(this,"Pomodoro","Start Focus!");
        // Set the duration of the timer (30 minutes)
        m_duration = 5;/*30*60+1;*/

        // Create a QTimer object and set the interval to 1 second
        QTimer *timer = new QTimer(this);
        timer->setInterval(1000);

        // connect clicked() to stop button to the stop slot of qtimer

        connect(ui->Stop, &QPushButton::clicked, timer, &QTimer::stop);
        // Connect the timeout() signal of the timer to a slot function
        connect(timer, &QTimer::timeout, this, [=]() mutable{
               // Decrement the duration by 1 second
               m_duration -= 1;

               // Update the display of the timer (e.g., a QLCDNumber widget)
               int minutes = m_duration / 60;
               int seconds = m_duration % 60;
               QString timeString = QString("%1:%2").arg(minutes, 2, 10, QChar('0')).arg(seconds, 2, 10, QChar('0'));
               ui->lcdNumber->display(timeString);

               // Check if the duration has reached 0
               if (m_duration <= 0) {
                   // Stop the timer
                   timer->stop();
                   m_player->stop();
                   QString end_text = ui->comboBox->currentText();
                   end_text+=" Time's Up!";
                   // Do something (e.g., play a sound or display a message)
                   QMessageBox::information(this, "Pomodoro Timer", end_text);
                   saveFocusTime(30);
               }
           });

           // Start the timer
           timer->start();
    }
    else
    {
        QMessageBox::information(this,"Pomodoro","Currently in another session");
    }

}




void MainWindow::on_button_40_clicked()
{

    if(m_duration==0)
    {
        play_anime_lofi();
        QMessageBox::information(this,"Pomodoro","Start Focus!");

        // Set the duration of the timer (40 minutes)
        m_duration = 40*60+1;

        // Create a QTimer object and set the interval to 1 second
        QTimer *timer = new QTimer(this);
        timer->setInterval(1000);

        // connect clicked() to stop button to the stop slot of qtimer

        connect(ui->Stop, &QPushButton::clicked, timer, &QTimer::stop);
        // Connect the timeout() signal of the timer to a slot function
        connect(timer, &QTimer::timeout, this, [=]() mutable{
            // Decrement the duration by 1 second
            m_duration -= 1;

            // Update the display of the timer (e.g., a QLCDNumber widget)
            int minutes = m_duration / 60;
            int seconds = m_duration % 60;
            QString timeString = QString("%1:%2").arg(minutes, 2, 10, QChar('0')).arg(seconds, 2, 10, QChar('0'));
            ui->lcdNumber->display(timeString);

            // Check if the duration has reached 0
            if (m_duration <= 0) {
                // Stop the timer
                timer->stop();
                m_player->stop();
                QString end_text = ui->comboBox->currentText();
                end_text+=" Time's Up!";
                // Do something (e.g., play a sound or display a message)
                QMessageBox::information(this, "Pomodoro Timer", end_text);
                saveFocusTime(40);
            }
        });

           // Start the timer
           timer->start();
    }
    else
    {
        QMessageBox::information(this,"Pomodoro","Currently in another session");
    }

}


void MainWindow::on_button_60_clicked()
{
    if(m_duration==0)
    {
        play_anime_lofi();
        QMessageBox::information(this,"Pomodoro","Start Focus!");

        // Set the duration of the timer (60 minutes)
        m_duration =60*60+1;

        // Create a QTimer object and set the interval to 1 second
        QTimer *timer = new QTimer(this);
        timer->setInterval(1000);

        // connect clicked() to stop button to the stop slot of qtimer

        connect(ui->Stop, &QPushButton::clicked, timer, &QTimer::stop);
        // Connect the timeout() signal of the timer to a slot function
        connect(timer, &QTimer::timeout, this, [=]() mutable{
            // Decrement the duration by 1 second
            m_duration -= 1;

            // Update the display of the timer (e.g., a QLCDNumber widget)
            int minutes = m_duration / 60;
            int seconds = m_duration % 60;
            QString timeString = QString("%1:%2").arg(minutes, 2, 10, QChar('0')).arg(seconds, 2, 10, QChar('0'));
            ui->lcdNumber->display(timeString);

            // Check if the duration has reached 0
            if (m_duration <= 0) {
                // Stop the timer
                timer->stop();
                m_player->stop();
                QString end_text = ui->comboBox->currentText();
                end_text+=" Time's Up!";
                // Do something (e.g., play a sound or display a message)
                QMessageBox::information(this, "Pomodoro Timer", end_text);
                saveFocusTime(60);
            }
        });

           // Start the timer
           timer->start();
    }
    else
    {
        QMessageBox::information(this,"Pomodoro","Currently in another session");
    }

}


void MainWindow::on_Stop_clicked()
{
    QMessageBox::information(this,"Session Stoped!","You have stopped the current session!");
    m_player->stop();
    ui->lcdNumber->display("00:00");
    m_duration = 0;

}

void MainWindow::show_stat_window_3_days()
{
    StatisticWindow *stat_window =new StatisticWindow(this);
    stat_window->show_3_days();
    stat_window->show();
}

void MainWindow::show_stat_window_7_days()
{
    StatisticWindow *stat_window =new StatisticWindow(this);
    stat_window->show_7_days();
    stat_window->show();

}



