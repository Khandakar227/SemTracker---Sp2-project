#include "questioncard.h"
#include<QVBoxLayout>
#include<QLabel>
#include<QPushButton>
#include<QString>

QuestionCard::QuestionCard(QWidget *parent)
    : QWidget{parent}
{
    bool showAnswer = false;
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0,0,0,0);

    question_label = new QLabel(this);
    question_label->setObjectName("question_label");
    question_label->setStyleSheet("color: black;font-weight:600;font-size:16px;");
    question_label->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    question_label->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

    answer_label = new QLabel(this);
    answer_label->setObjectName("answer_label");
    answer_label->setStyleSheet("color: black;font-size:16px;padding:12px;");
    answer_label->setWordWrap(true);
    answer_label->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    answer_label->setSizePolicy(QSizePolicy::MinimumExpanding,
                                QSizePolicy::MinimumExpanding);
    answer_label->hide();

    ans_tggl_btn = new QPushButton(showAnswer ?"Hide answer" : "View answer", this);
    ans_tggl_btn->setStyleSheet("background:lightgray;color:white;height:20px;");

    connect(ans_tggl_btn, &QPushButton::clicked, this, &QuestionCard::on_ans_tggl_btn_clicked);

    subject_label = new QLabel(this);
    subject_label->setObjectName("subject_label");
    subject_label->setStyleSheet("color: black; font-size:16px;");
    subject_label->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    subject_label->setSizePolicy(QSizePolicy::MinimumExpanding,
                                 QSizePolicy::MinimumExpanding);
    date_label = new QLabel(this);
    date_label->setObjectName("date_label");
    date_label->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    date_label->setStyleSheet("color: gray;border-bottom: 1px solid lightgray;font-size:14px;padding: 10px 0;");
    date_label->setSizePolicy(QSizePolicy::MinimumExpanding,
                              QSizePolicy::MinimumExpanding);

    layout->addWidget(question_label);
    layout->addWidget(answer_label);
    layout->addWidget(subject_label);
    layout->addWidget(ans_tggl_btn);
    layout->addWidget(date_label);
}

void QuestionCard::on_ans_tggl_btn_clicked() {
    showAnswer = showAnswer ? false : true;

//    qDebug() << QString::number(showAnswer);
    if (showAnswer) {
        answer_label->show();
        ans_tggl_btn->setText("Hide answer");
//        answer_label->adjustSize();
    } else {
        answer_label->hide();
        ans_tggl_btn->setText("View answer");
    }
}

void QuestionCard::setQuestion(const QuestionStruct &question, int question_number = 1) {
  question_label->setText(QString::number(question_number) + ". " + question.question);
  answer_label->setText("Answer:    " + question.answer);
  subject_label->setText("Subject:  " + question.subject);
  date_label->setText("Uploaded at:  " + question.created_at.date().toString());
}
