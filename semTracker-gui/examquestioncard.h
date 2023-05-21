#ifndef EXAMQUESTIONCARD_H
#define EXAMQUESTIONCARD_H

#include <QWidget>
#include<QLabel>
#include"questionstruct.h"

class ExamQuestionCard : public QWidget
{
    Q_OBJECT
    explicit ExamQuestionCard(QWidget *parent = nullptr);
    void setQuestion(const QuestionStruct &question, int question_number);

private:
  QLabel *question_label;
signals:

};

#endif // EXAMQUESTIONCARD_H
