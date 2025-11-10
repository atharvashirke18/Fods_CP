#ifndef SONGLIBRARY_H
#define SONGLIBRARY_H

#include <QWidget>
#include <QTableView>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QStandardItemModel>

class SongLibrary : public QWidget
{
    Q_OBJECT
public:
    explicit SongLibrary(QWidget *parent = nullptr);

    void setSongs(const QVector<QStringList> &data);

signals:
    void searchChanged(QString text);
    void rowClicked(int row);

private:
    QLineEdit *searchBox;
    QTableView *tableView;
    QStandardItemModel *model;
};

#endif
