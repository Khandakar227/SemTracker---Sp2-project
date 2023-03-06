#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Modify status bar
    ui->statusbar->hide();
    statusbar_timeout = new QTimer(this);
    connect(statusbar_timeout, SIGNAL(timeout()), this, SLOT(hideStatusBar()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_add_question_btn_clicked()
{
    ui->mainStackedWidget->setCurrentIndex(1);
}


void MainWindow::on_calculate_cgpa_btn_clicked()
{

}


void MainWindow::on_test_memory_btn_clicked()
{

}


void MainWindow::on_attendence_tracker_btn_clicked()
{

}


void MainWindow::on_quiz_marks_btn_clicked()
{

}


void MainWindow::on_statistics_btn_clicked()
{

}


void MainWindow::on_submit_ques_btn_clicked()
{
    notify("Add button was clicked", "success");
    ui->mainStackedWidget->setCurrentIndex(0);
}


void MainWindow::on_cancel_add_ques_btn_clicked()
{
    ui->mainStackedWidget->setCurrentIndex(0);
}

void MainWindow::hideStatusBar() {
    ui->statusbar->hide();
    statusbar_timeout->stop();
}

void MainWindow::notify(QString message, QString _type) {
    ui->statusbar->show();

    if (_type == "info")
        ui->statusbar->setStyleSheet("background-color: #00cda4; color: black; font-size:16px;");
    else if (_type == "success")
        ui->statusbar->setStyleSheet("background-color: #00ae2b; font-size:16px;");
    else if (_type == "warning")
        ui->statusbar->setStyleSheet("background-color: #fff400; color: black; font-size:16px;");
    else
        ui->statusbar->setStyleSheet("background-color: #cd0000; font-size:16px;");

    ui->statusbar->showMessage(message);
    statusbar_timeout->start(5000);
}

void MainWindow::on_actionAddQuestion_triggered()
{
    ui->mainStackedWidget->setCurrentIndex(1);
}

