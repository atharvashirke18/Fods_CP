#ifndef SONGLIBRARY_H
#define SONGLIBRARY_H

#include <QWidget>
#include <QTableView>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QStandardItemModel>
#include <QTableWidget>

class SongLibrary : public QWidget
{
    Q_OBJECT
public:
    explicit SongLibrary(QWidget *parent = nullptr);
     QTableWidget *tableWidget;

    void setSongs(const QVector<QStringList> &data);
    QVector<int> getSelectedRows() const;
       QStandardItemModel *model;
           QTableView *tableView;

signals:
    void searchChanged(QString text);
    void rowClicked(int row);

private:
    QLineEdit *searchBox;




};

#endif
