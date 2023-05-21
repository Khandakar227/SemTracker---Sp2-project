#ifndef QUESTIONCARD_H
#define QUESTIONCARD_H

#include <QWidget>
#include<QLabel>
#include<QPushButton>
#include"questionstruct.h"

class QuestionCard : public QWidget
{
    Q_OBJECT
public:
    explicit QuestionCard(QWidget *parent = nullptr);
    void setQuestion(const QuestionStruct &question, int question_number);

private:
  bool showAnswer;
  QLabel *question_label;
  QLabel *answer_label;
  QLabel *subject_label;
  QLabel *date_label;

  QPushButton *ans_tggl_btn;

private slots:
    void on_ans_tggl_btn_clicked();

signals:

};

#endif // QUESTIONCARD_H
