#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void hideStatusBar();

    void notify(QString, QString);

    void on_add_question_btn_clicked();

    void on_calculate_cgpa_btn_clicked();

    void on_test_memory_btn_clicked();

    void on_attendence_tracker_btn_clicked();

    void on_quiz_marks_btn_clicked();

    void on_statistics_btn_clicked();

    void on_submit_ques_btn_clicked();

    void on_cancel_add_ques_btn_clicked();

    void on_actionAddQuestion_triggered();

private:
    Ui::MainWindow *ui;
    QTimer *statusbar_timeout;
};
#endif // MAINWINDOW_H
