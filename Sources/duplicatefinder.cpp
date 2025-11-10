#include "Headers/duplicatefinder.h"
#include <QVBoxLayout>

DuplicateFinder::DuplicateFinder(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    tableWidget = new QTableWidget(this);
    tableWidget->setColumnCount(5);
    tableWidget->setHorizontalHeaderLabels({"Title", "Artist", "Year", "Tempo", "Mood"});
    layout->addWidget(tableWidget);
}

void DuplicateFinder::setDuplicates(const QVector<QStringList>& duplicates)
{
    tableWidget->setRowCount(duplicates.size());
    for (int r = 0; r < duplicates.size(); ++r) {
        for (int c = 0; c < duplicates[r].size(); ++c) {
            tableWidget->setItem(r, c, new QTableWidgetItem(duplicates[r][c]));
        }
    }
}
