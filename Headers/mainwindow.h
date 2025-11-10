#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "Headers/musiccontroller.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
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

    // Playlist management
    void onCreatePlaylist();
    void onDeletePlaylist(int index);
    void onPlaylistSelected(int index);
    void onAddSongsToPlaylist(int playlistIndex);

    // Playlist generation slots
    void onGenerateMoodPlaylist();
    void onGenerateWorkoutPlaylist();
    void onGenerateRelaxationPlaylist();
    void onGeneratePartyPlaylist();

    // NEW: Unified playlist generation handler
    void onGeneratePlaylistRequested(const QString &mood, int duration);

private:
    Ui::MainWindow *ui;
    QStackedWidget *contentStack;
    MusicController *musicController;

    void refreshPlaylists();
    void populateTable(const QVector<QStringList>& data);
    void populatePlaylistTable(const QVector<QStringList>& data);
};

#endif // MAINWINDOW_H
