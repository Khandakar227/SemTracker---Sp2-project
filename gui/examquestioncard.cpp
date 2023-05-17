#include "examquestioncard.h"
#include<QVBoxLayout>
#include<QLabel>
#include<QString>

ExamQuestionCard::ExamQuestionCard(QWidget *parent)
    : QWidget{parent}
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0,0,0,0);

    question_label = new QLabel(this);
    question_label->setObjectName("question_label");
    question_label->setStyleSheet("color: black;font-weight:600;font-size:16px;");
    question_label->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    question_label->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

    layout->addWidget(question_label);
}

void ExamQuestionCard::setQuestion(const QuestionStruct &question, int question_number = 1)
{
     question_label->setText(QString::number(question_number) + ". " + question.question);
}
