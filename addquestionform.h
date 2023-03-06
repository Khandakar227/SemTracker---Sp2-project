#ifndef ADDQUESTIONFORM_H
#define ADDQUESTIONFORM_H

#include <QDialog>

namespace Ui {
class AddQuestionForm;
}

class AddQuestionForm : public QDialog
{
    Q_OBJECT

public:
    explicit AddQuestionForm(QWidget *parent = nullptr);
    ~AddQuestionForm();

private:
    Ui::AddQuestionForm *ui;
};

#endif // ADDQUESTIONFORM_H
