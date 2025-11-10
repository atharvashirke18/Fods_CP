#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Headers/musiccontroller.h"
#include "Headers/songlibrary.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onLibraryLoaded(int count);
    void onHomeClicked();
    void onLibraryClicked();
    void onPlaylistsClicked();
    void onDuplicatesClicked();
    void onHistoryClicked();
    void onSearchTextChanged(const QString &text);
    void onTableRowClicked(int row);

private:
    void populateTable(const QVector<QStringList>& data);

    MusicController *musicController;
    SongLibrary *library; // ✅ stored pointer
};

#endif
