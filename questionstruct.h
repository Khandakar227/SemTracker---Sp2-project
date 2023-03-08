#ifndef QUESTIONSTRUCT_H
#define QUESTIONSTRUCT_H

#include <QString>
#include <QDateTime>
#include <QUuid>

struct QuestionStruct {
    QUuid id;
    QString question;
    QString answer;
    QString subject;
    QDateTime created_at;
};

#endif // QUESTIONSTRUCT_H
