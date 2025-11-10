#ifndef DUPLICATEFINDER_H
#define DUPLICATEFINDER_H

#include <QWidget>
#include <QTableWidget>

class DuplicateFinder : public QWidget
{
    Q_OBJECT
public:
    explicit DuplicateFinder(QWidget *parent = nullptr);
    void setDuplicates(const QVector<QStringList>& duplicates);
    QTableWidget *tableWidget;
};

#endif