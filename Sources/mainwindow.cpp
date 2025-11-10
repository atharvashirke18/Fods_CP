#include "Headers/mainwindow.h"
#include "Headers/sidebar.h"
#include "Headers/nowplayingbar.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QDockWidget>
#include <QTimer>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    musicController = new MusicController(this);
    connect(musicController, &MusicController::libraryLoaded, this, &MainWindow::onLibraryLoaded);

    QWidget *central = new QWidget(this);
    QHBoxLayout *mainLayout = new QHBoxLayout(central);

    Sidebar *sidebar = new Sidebar(this);
    connect(sidebar->homeButton, &QPushButton::clicked, this, &MainWindow::onHomeClicked);
    connect(sidebar->libraryButton, &QPushButton::clicked, this, &MainWindow::onLibraryClicked);
    connect(sidebar->playlistsButton, &QPushButton::clicked, this, &MainWindow::onPlaylistsClicked);
    connect(sidebar->duplicatesButton, &QPushButton::clicked, this, &MainWindow::onDuplicatesClicked);
    connect(sidebar->historyButton, &QPushButton::clicked, this, &MainWindow::onHistoryClicked);

    library = new SongLibrary(this);
    connect(library, &SongLibrary::searchChanged, this, &MainWindow::onSearchTextChanged);
    connect(library, &SongLibrary::rowClicked, this, &MainWindow::onTableRowClicked);

    mainLayout->addWidget(sidebar);
    mainLayout->addWidget(library);
    setCentralWidget(central);

    NowPlayingBar *nowPlaying = new NowPlayingBar(this);

    QDockWidget *dock = new QDockWidget(this);
    dock->setWidget(nowPlaying);
    dock->setTitleBarWidget(new QWidget());
    addDockWidget(Qt::BottomDockWidgetArea, dock);

    // ✅ Delay loading slightly so UI doesn't crash
    QTimer::singleShot(200, this, [=](){
        musicController->loadFromCSV("D:/fods/data/songs.csv");
    });
}

MainWindow::~MainWindow() {}

void MainWindow::onLibraryLoaded(int count) {
    QMessageBox::information(this, "Success", QString("Loaded %1 songs!").arg(count));
    onHomeClicked();
}

void MainWindow::onHomeClicked() {
    auto songs = musicController->getAllSongs();
    populateTable(songs);
}

void MainWindow::onLibraryClicked() { onHomeClicked(); }
void MainWindow::onPlaylistsClicked() { QMessageBox::information(this, "Playlists", "Playlist feature coming soon!"); }
void MainWindow::onDuplicatesClicked() {
    auto duplicates = musicController->findDuplicates();
    populateTable(duplicates);
}
void MainWindow::onHistoryClicked() { QMessageBox::information(this, "History", "History feature coming soon!"); }

void MainWindow::onSearchTextChanged(const QString &text) {
    if (text.isEmpty()) { onHomeClicked(); return; }
    auto results = musicController->searchSongs(text);
    populateTable(results);
}

void MainWindow::onTableRowClicked(int row) {
    QMessageBox::information(this, "Song Selected", QString("Selected row: %1").arg(row));
}

void MainWindow::populateTable(const QVector<QStringList>& data)
{
    library->setSongs(data);
}
