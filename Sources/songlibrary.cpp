#include "Headers/songlibrary.h"
#include <QHeaderView>
#include <QDebug>

SongLibrary::SongLibrary(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    searchBox = new QLineEdit(this);
    searchBox->setPlaceholderText("🔍 Search songs...");
    connect(searchBox, &QLineEdit::textChanged, this, &SongLibrary::searchChanged);

    tableView = new QTableView(this);
    model = new QStandardItemModel(this);
    model->setColumnCount(5);
    model->setHorizontalHeaderLabels({"Title", "Artist", "Year", "Tempo", "Mood"});

    tableView->setModel(model);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->setSelectionMode(QAbstractItemView::MultiSelection); // Enable multi-selection
    tableView->horizontalHeader()->setStretchLastSection(true);

    connect(tableView, &QTableView::clicked, this, [=](const QModelIndex &index){
        emit rowClicked(index.row());
    });

    layout->addWidget(searchBox);
    layout->addWidget(tableView);
}

void SongLibrary::setSongs(const QVector<QStringList> &data)
{
    int rows = data.size();
    model->setRowCount(rows);
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < data[r].size() && c < 5; ++c) {
            model->setItem(r, c, new QStandardItem(data[r][c]));
        }
    }
    qDebug() << "Model now holds" << rows << "songs";
}

QVector<int> SongLibrary::getSelectedRows() const
{
    QVector<int> selectedRows;
    QModelIndexList selectedIndexes = tableView->selectionModel()->selectedRows();

    for (const QModelIndex &index : selectedIndexes) {
        selectedRows.append(index.row());
    }

    return selectedRows;
}
