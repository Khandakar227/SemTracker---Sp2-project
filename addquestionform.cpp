#include "addquestionform.h"
#include "ui_addquestionform.h"

AddQuestionForm::AddQuestionForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddQuestionForm)
{
    ui->setupUi(this);
}

AddQuestionForm::~AddQuestionForm()
{
    delete ui;
}
