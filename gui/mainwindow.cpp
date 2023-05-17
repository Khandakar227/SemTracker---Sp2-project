#include <QFile>
#include <QDataStream>
#include <QLabel>
#include <QPushButton>
#include <QDebug>
#include <QSet>
#include <QScrollArea>
#include <QVector>
#include <QTextEdit>
#include <QBoxLayout>
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "examquestioncard.h"
#include "questionstruct.h"
#include "questioncard.h"
#include "testsubjectbutton.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Modify status bar
    ui->statusbar->hide();
    statusbar_timeout = new QTimer(this);
    connect(statusbar_timeout, SIGNAL(timeout()), this, SLOT(hideStatusBar()));

    // Set plaintText in textEdit boxes
    ui->answer_box->setAcceptRichText(false);
    ui->question_box->setAcceptRichText(false);
    ui->subject_box->setAcceptRichText(false);

    ui->mainStackedWidget->setCurrentIndex(0);
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
    ui->mainStackedWidget->setCurrentIndex(3);
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
    QuestionStruct question = {
        QUuid::createUuid(),
        ui->question_box->toPlainText(),
        ui->answer_box->toPlainText(),
        ui->subject_box->toPlainText(),
        QDateTime::currentDateTime()};

    if (question.subject.isEmpty() || question.answer.isEmpty() || question.question.isEmpty())
        notify("Missing an input", "error");
    else
    {
        // Add to a file (questions.bin)
        bool state = addQuestionToDB(&question);
        if (state)
        {
            notify("Question has been added", "success");

            ui->question_box->clear();
            ui->answer_box->clear();
            ui->subject_box->clear();

            ui->mainStackedWidget->setCurrentIndex(0);
        }
        else
            return;
    }
}

void MainWindow::on_cancel_add_ques_btn_clicked()
{
    ui->mainStackedWidget->setCurrentIndex(0);
}

void MainWindow::hideStatusBar()
{
    ui->statusbar->hide();
    statusbar_timeout->stop();
}

void MainWindow::notify(QString message, QString _type)
{
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

void MainWindow::on_actionView_Questions_triggered()
{
    ui->mainStackedWidget->setCurrentIndex(2);
}

bool MainWindow::addQuestionToDB(QuestionStruct *question)
{
    QFile question_db("questions.bin"), subject_db("subjects.bin");

    if (!question_db.open(QIODevice::Append))
    {
        notify("Error while opening the database", "error");
        return false;
    }
    QDataStream out(&question_db);
    out << question->id << question->question << question->answer << question->subject << question->created_at;
    question_db.flush();

    if (question_db.error() != QFile::NoError)
    {
        notify("Error while writing to the database", "error");
        return false;
    }

    //// Add Subjects to subjects file
    QSet<QString> subject_set;
    //// Check if subject file exist
    if (subject_db.open(QFile::ReadOnly))
    {

        qInfo() << "Subject file exists";

        QDataStream in(&subject_db);
        //        in.setVersion(QDataStream::Qt_6_4);

        in >> subject_set;

        subject_db.close();
    }
    /// Add the subject to Qset
    subject_set.insert(question->subject);

    /// Add it to subjects file
    if (subject_db.open(QFile::WriteOnly))
    {
        QDataStream subject_out(&subject_db);
        subject_out << subject_set;
    }
    subject_db.flush();

    subject_db.close();
    question_db.close();

    return true;
}

void MainWindow::on_actionView_Questions_2_triggered()
{
    ui->mainStackedWidget->setCurrentIndex(2);
}

// To chnage layout dynamically for some pages
void MainWindow::on_mainStackedWidget_currentChanged(int arg1)
{
    if (arg1 == 2)
    {
        QWidget *scrollWidget = new QWidget();
        QVBoxLayout *layout = new QVBoxLayout(scrollWidget);
        layout->setAlignment(Qt::AlignCenter);

        QFile question_db("questions.bin");
        if (!question_db.open(QFile::ReadOnly | QFile::Text))
        {
            notify("Error while opening the database. No such file", "error");
            ui->status_label->setText("No data found");
            return;
        }

        QDataStream in(&question_db);
        QuestionStruct q;
        int i = 1;

        while (!in.atEnd())
        {
            in >> q.id >> q.question >> q.answer >> q.subject >> q.created_at;
            //        qDebug() << "Read data:" << q.question << q.answer << q.subject;
            QuestionCard *q_card = new QuestionCard();
            q_card->setQuestion(q, i);
            layout->addWidget(q_card);
            i++;
        }

        ui->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        ui->scrollArea->setWidget(scrollWidget);
        question_db.close();
    }
    else if (arg1 == 3)
    {
        QWidget *scrollWidget = new QWidget();
        QVBoxLayout *layout = new QVBoxLayout(scrollWidget);
        layout->setAlignment(Qt::AlignVCenter);

        QLabel *label = new QLabel();
        label->setText("Select Subject: ");
        label->setStyleSheet("font-size: 1.2rem;font-weight:bold;padding-bottom:1rem;");
        layout->addWidget(label);

        QPushButton *all_subject_btn = new QPushButton("All Subject", this);

        all_subject_btn->setStyleSheet("QPushButton{cursor:pointer;border-radius:10px;color: white;background-color: black;height: 60px;border: 1px solid black;margin: 1rem auto;}QPushButton:hover{color:black;background-color: white;}");
        all_subject_btn->setMaximumWidth(800);

        connect(all_subject_btn, &QPushButton::clicked, this, &MainWindow::on_exam_sub_btn_clicked);

        layout->addWidget(all_subject_btn);

        QFile subject_db("subjects.bin");
        // Add buttons for Subject
        QSet<QString> subject_set;
        //// Check if subject file exist
        if (subject_db.open(QFile::ReadOnly | QFile::Text))
        {
            qInfo() << "Subject file exists";
            QDataStream in(&subject_db);
            //        in.setVersion(QDataStream::Qt_6_4);
            in >> subject_set;

            QSet<QString>::iterator i;
            for (i = subject_set.begin(); i != subject_set.end(); ++i)
            {
                QPushButton *sub_btn = new QPushButton(*i, this);

                sub_btn->setStyleSheet("QPushButton{cursor:pointer;border-radius:10px;color: white;background-color: black;height: 60px;border: 1px solid black;margin: 1rem auto;}QPushButton:hover{color:black;background-color: white;}");
                sub_btn->setMaximumWidth(800);

                connect(sub_btn, &QPushButton::clicked, this, [this, sub_btn]() {
                    QVector<QuestionStruct> qs;
                    this->getQuestions(&qs);
                    ui->mainStackedWidget->setCurrentIndex(4);
                    qInfo() << sub_btn->text();
                });

                layout->addWidget(sub_btn);
            }
        }
        subject_db.close();

        ui->test_urself_scrollarea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        ui->test_urself_scrollarea->setWidget(scrollWidget);
    }
}



void MainWindow::on_actionTest_your_memory_triggered()
{
    ui->mainStackedWidget->setCurrentIndex(3);
}



void MainWindow::getQuestions(QVector<QuestionStruct> *qs)
{
    QFile question_db("questions.bin");

    if (!question_db.open(QFile::ReadOnly | QFile::Text))
    {
        notify("Error while opening the database. No such file", "error");
        ui->status_label->setText("No data found");
        return;
    }

    QDataStream in(&question_db);
    QuestionStruct q;

    int i = 1;

    while (!in.atEnd())
    {
        in >> q.id >> q.question >> q.answer >> q.subject >> q.created_at;
        qs->push_back(q);
        i++;
    }
    question_db.close();
    return;
}



void MainWindow::on_exam_sub_btn_clicked()
{
    int pageIndex = 4;  // Set the index of the desired page
    QPushButton* button = qobject_cast<QPushButton*>(sender());


    QWidget* widget = new QWidget(this);

    // Create a QVBoxLayout to manage the labels
    QVBoxLayout* layout = new QVBoxLayout(widget);

    QVector<QuestionStruct> qs;

    //Get all the questions
    getQuestions(&qs);

    // Set all the questions
    int question_number = 1;
    for(QuestionStruct question:qs)
    {
        QWidget* examquestioncard = new QWidget(this);

        QBoxLayout* examquestioncard_layout = new QBoxLayout(examquestioncard);

        QLabel* question_label = new QLabel(this);
        QTextEdit* answer_box = new QTextEdit(widget);

        question_label->setObjectName("question_label");

        question_label->setAlignment(Qt::AlignTop | Qt::AlignLeft);
        question_label->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

        question_label->setText(QString::number(question_number) + ". " + question.question);

        question_number++;

        examquestioncard_layout->addWidget(question_label);
        examquestioncard_layout->addWidget(answer_box);
        // Add the labels to the layout
        layout->addWidget(examquestioncard);
    }

    // Set the layout on the widget
    widget->setLayout(layout);

    ui->test_exam_scrollArea->setWidget(widget);

    ui->mainStackedWidget->setCurrentIndex(pageIndex);  // Optionally, set the current page

    qInfo() << button->text();

//    QVector<QuestionStruct> qs;

//    this->getQuestions(&qs);


//    QVector<QuestionStruct>::const_iterator it;
//    for (it = qs.constBegin(); it != qs.constEnd(); ++it) {
//        qInfo() << it->question;
//    }

//    this->set_exam_questions(qs);
    ui->test_exam_scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
}


void MainWindow::set_exam_questions(QVector<QuestionStruct> qs)
{

}
