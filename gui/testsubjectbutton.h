#ifndef TESTSUBJECTBUTTON_H
#define TESTSUBJECTBUTTON_H

#include <QWidget>
#include<QPushButton>
#include<QString>

class TestSubjectButton : public QWidget
{
    Q_OBJECT
public:
    QString subjectName;
    explicit TestSubjectButton(QString subject_name, QWidget *parent = nullptr);

private slots:
    void on_sub_btn_clicked();

private:
    QPushButton *sub_btn;

signals:


};

#endif // TESTSUBJECTBUTTON_H
