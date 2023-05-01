#include "testsubjectbutton.h"
#include<QVBoxLayout>
#include<QPushButton>
#include<QDebug>

TestSubjectButton::TestSubjectButton(QString subject_name, QWidget *parent)
    : QWidget{parent}
{
    subjectName = subject_name;

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0,0,0,0);

    QPushButton *sub_btn = new QPushButton(this);
    sub_btn->setText(subjectName);
    sub_btn->setStyleSheet("QPushButton{cursor:pointer;border-radius:10px;color: white;background-color: black;height: 60px;border: 1px solid black;margin: 1rem auto;}QPushButton:hover{color:black;background-color: white;}");
    sub_btn->setMaximumWidth(800);

    connect(sub_btn, &QPushButton::clicked, this, &TestSubjectButton::on_sub_btn_clicked);

    layout->addWidget(sub_btn);
}

void TestSubjectButton::on_sub_btn_clicked()
{
    qInfo() << subjectName;
}
