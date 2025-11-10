#include "Headers/mainwindow.h"
#include "Headers/sidebar.h"
#include "Headers/songlibrary.h"
#include "Headers/nowplayingbar.h"
#include "Headers/playlistmanager.h"
#include "Headers/duplicatefinder.h"
#include <QHBoxLayout>
#include<QStatusBar>
#include <QVBoxLayout>
#include<QTableView>
#include<QTableWidget>
#include <QMessageBox>
#include <QDockWidget>
#include <QTableWidgetItem>
#include <QDebug>
#include <QInputDialog>
#include <QComboBox>
#include <QDialog>
#include <QDialogButtonBox>
#include <QSpinBox>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(nullptr)
{
    qDebug() << "MainWindow constructor started";
    statusBar()->showMessage("Starting...");

    musicController = new MusicController(this);
    connect(musicController, &MusicController::libraryLoaded, this, &MainWindow::onLibraryLoaded);
    connect(musicController, &MusicController::playlistCreated, this, &MainWindow::refreshPlaylists);

    QWidget *central = new QWidget(this);
    QHBoxLayout *mainLayout = new QHBoxLayout(central);

    Sidebar *sidebar = new Sidebar(this);
    connect(sidebar->homeButton, &QPushButton::clicked, this, &MainWindow::onHomeClicked);
    connect(sidebar->libraryButton, &QPushButton::clicked, this, &MainWindow::onLibraryClicked);
    connect(sidebar->playlistsButton, &QPushButton::clicked, this, &MainWindow::onPlaylistsClicked);
    connect(sidebar->duplicatesButton, &QPushButton::clicked, this, &MainWindow::onDuplicatesClicked);
    connect(sidebar->historyButton, &QPushButton::clicked, this, &MainWindow::onHistoryClicked);

    // Content stack for switching views
    contentStack = new QStackedWidget(this);

    // Page 0: Song Library
    SongLibrary *library = new SongLibrary(this);
    connect(library, &SongLibrary::searchChanged, this, &MainWindow::onSearchTextChanged);
    connect(library, &SongLibrary::rowClicked, this, &MainWindow::onTableRowClicked);
    contentStack->addWidget(library);

    // Page 1: Playlist Manager
    PlaylistManager *playlistManager = new PlaylistManager(this);
    connect(playlistManager, &PlaylistManager::createPlaylistClicked, this, &MainWindow::onCreatePlaylist);
    connect(playlistManager, &PlaylistManager::deletePlaylistClicked, this, &MainWindow::onDeletePlaylist);
    connect(playlistManager, &PlaylistManager::playlistSelected, this, &MainWindow::onPlaylistSelected);

    // UPDATED: Connect to the new generatePlaylistRequested signal instead of individual signals
    connect(playlistManager, &PlaylistManager::generatePlaylistRequested, this, &MainWindow::onGeneratePlaylistRequested);

    // Keep these for backward compatibility if you still want them
    // Or you can remove them since they're now handled by generatePlaylistRequested
    connect(playlistManager, &PlaylistManager::generateMoodClicked, this, &MainWindow::onGenerateMoodPlaylist);
    connect(playlistManager, &PlaylistManager::generateWorkoutClicked, this, &MainWindow::onGenerateWorkoutPlaylist);
    connect(playlistManager, &PlaylistManager::generateRelaxationClicked, this, &MainWindow::onGenerateRelaxationPlaylist);
    connect(playlistManager, &PlaylistManager::generatePartyClicked, this, &MainWindow::onGeneratePartyPlaylist);

    connect(playlistManager, &PlaylistManager::addSongsClicked, this, &MainWindow::onAddSongsToPlaylist);
    contentStack->addWidget(playlistManager);

    // Page 2: Duplicates
    DuplicateFinder *duplicates = new DuplicateFinder(this);
    contentStack->addWidget(duplicates);

    mainLayout->addWidget(sidebar);
    mainLayout->addWidget(contentStack);
    setCentralWidget(central);

    NowPlayingBar *nowPlaying = new NowPlayingBar(this);
    QDockWidget *dock = new QDockWidget(this);
    dock->setWidget(nowPlaying);
    dock->setTitleBarWidget(new QWidget());
    addDockWidget(Qt::BottomDockWidgetArea, dock);

    statusBar()->showMessage("Loading music library...");
    qDebug() << "About to load CSV";
    musicController->loadFromCSV("/home/lucifer/projects/Fods_CP/data/songs.csv");
    qDebug() << "CSV load initiated";
}

MainWindow::~MainWindow() {}

void MainWindow::onLibraryLoaded(int count) {
    qDebug() << "Library loaded:" << count << "songs";
    statusBar()->showMessage(QString("Ready - %1 songs loaded").arg(count));
    onHomeClicked();
}

void MainWindow::onHomeClicked() {
    contentStack->setCurrentIndex(0);
    auto songs = musicController->getAllSongs();
    populateTable(songs);
}

void MainWindow::onLibraryClicked() { onHomeClicked(); }

void MainWindow::onPlaylistsClicked() {
    contentStack->setCurrentIndex(1);
    refreshPlaylists();
}

void MainWindow::onDuplicatesClicked() {
    contentStack->setCurrentIndex(2);
    auto duplicates = musicController->findDuplicates();
    DuplicateFinder *finder = qobject_cast<DuplicateFinder*>(contentStack->widget(2));
    if (finder) finder->setDuplicates(duplicates);
}

void MainWindow::onHistoryClicked() {
    QMessageBox::information(this, "History", "History feature coming soon!");
}

void MainWindow::onSearchTextChanged(const QString &text) {
    if (text.isEmpty()) { onHomeClicked(); return; }
    auto results = musicController->searchSongs(text);
    populateTable(results);
}

void MainWindow::onTableRowClicked(int row) {
    statusBar()->showMessage(QString("Selected row: %1").arg(row), 2000);
}

void MainWindow::onCreatePlaylist() {
    bool ok;
    QString name = QInputDialog::getText(this, "Create Playlist", "Playlist name:", QLineEdit::Normal, "", &ok);
    if (ok && !name.isEmpty()) {
        musicController->createPlaylist(name);
        QMessageBox::information(this, "Success", "Playlist created!");
        refreshPlaylists();
    }
}

void MainWindow::onDeletePlaylist(int index) {
    if (index < 0) {
        QMessageBox::warning(this, "Error", "Please select a playlist first!");
        return;
    }
    auto reply = QMessageBox::question(this, "Confirm", "Delete this playlist?",
                                       QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        musicController->deletePlaylist(index);
        refreshPlaylists();
    }
}

void MainWindow::onPlaylistSelected(int index) {
    if (index < 0) return;
    auto songs = musicController->getPlaylistSongs(index);
    populatePlaylistTable(songs);
}

// NEW: Unified handler for playlist generation requests
void MainWindow::onGeneratePlaylistRequested(const QString &mood, int duration) {
    qDebug() << "Generating playlist with mood:" << mood << "duration:" << duration;

    QVector<QStringList> songs;

    // Route to appropriate generation method based on mood
    if (mood == "Happy" || mood == "Sad" || mood == "Energetic" ||
        mood == "Calm" || mood == "Party" || mood == "Neutral") {
        songs = musicController->generateMoodPlaylist(mood, duration);
    } else {
        // Fallback to mood-based generation
        songs = musicController->generateMoodPlaylist(mood, duration);
    }

    if (!songs.isEmpty()) {
        QMessageBox::information(this, "Success",
                                 QString("Generated %1 song %2 playlist (%3 minutes)!")
                                     .arg(songs.size())
                                     .arg(mood)
                                     .arg(duration));
        refreshPlaylists();
        statusBar()->showMessage(QString("Created %1 playlist with %2 songs")
                                     .arg(mood).arg(songs.size()), 5000);
    } else {
        QMessageBox::warning(this, "Error",
                             QString("Failed to generate %1 playlist. No matching songs found.").arg(mood));
    }
}

void MainWindow::onGenerateMoodPlaylist() {
    QDialog dialog(this);
    dialog.setWindowTitle("Generate Mood Playlist");
    QVBoxLayout layout(&dialog);

    layout.addWidget(new QLabel("Select Mood:"));
    QComboBox *moodCombo = new QComboBox(&dialog);
    moodCombo->addItems({"Happy", "Sad", "Energetic", "Calm", "Party", "Neutral"});
    layout.addWidget(moodCombo);

    layout.addWidget(new QLabel("Duration (minutes):"));
    QSpinBox *durationSpin = new QSpinBox(&dialog);
    durationSpin->setRange(5, 120);
    durationSpin->setValue(30);
    layout.addWidget(durationSpin);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);
    layout.addWidget(buttonBox);

    if (dialog.exec() == QDialog::Accepted) {
        auto songs = musicController->generateMoodPlaylist(moodCombo->currentText(), durationSpin->value());
        QMessageBox::information(this, "Success", QString("Generated %1 song playlist!").arg(songs.size()));
        refreshPlaylists();
    }
}

void MainWindow::onGenerateWorkoutPlaylist() {
    bool ok;
    int duration = QInputDialog::getInt(this, "Workout Playlist", "Duration (minutes):", 45, 15, 120, 5, &ok);
    if (ok) {
        auto songs = musicController->generateWorkoutPlaylist(duration);
        QMessageBox::information(this, "Success", QString("Generated %1 song workout playlist!").arg(songs.size()));
        refreshPlaylists();
    }
}

void MainWindow::onGenerateRelaxationPlaylist() {
    bool ok;
    int duration = QInputDialog::getInt(this, "Relaxation Playlist", "Duration (minutes):", 30, 10, 90, 5, &ok);
    if (ok) {
        auto songs = musicController->generateRelaxationPlaylist(duration);
        QMessageBox::information(this, "Success", QString("Generated %1 song relaxation playlist!").arg(songs.size()));
        refreshPlaylists();
    }
}

void MainWindow::onGeneratePartyPlaylist() {
    auto songs = musicController->generatePartyPlaylist();
    QMessageBox::information(this, "Success", QString("Generated %1 song party playlist!").arg(songs.size()));
    refreshPlaylists();
}

void MainWindow::onAddSongsToPlaylist(int playlistIndex) {
    if (playlistIndex < 0) {
        QMessageBox::warning(this, "Error", "Please select a playlist first!");
        return;
    }

    // Get the SongLibrary widget
    SongLibrary *lib = qobject_cast<SongLibrary*>(contentStack->widget(0));
    if (!lib) {
        QMessageBox::warning(this, "Error", "Cannot access song library!");
        return;
    }

    // Get selected songs
    QVector<int> selectedRows = lib->getSelectedRows();

    if (selectedRows.isEmpty()) {
        QMessageBox::information(this, "No Selection",
                                 "Please go to the Library tab and select songs to add.\n\n"
                                 "Tip: Hold Ctrl (Cmd on Mac) to select multiple songs.");
        return;
    }

    // Add selected songs to the playlist
    int addedCount = 0;
    for (int row : selectedRows) {
        // Get song data from the model
        QStringList songData;
        for (int col = 0; col < 5; ++col) {
            QStandardItem *item = lib->model->item(row, col);
            if (item) {
                songData.append(item->text());
            } else {
                songData.append("");
            }
        }

        if (!songData.isEmpty()) {
            // Add song to playlist via MusicController
            musicController->addSongToPlaylist(playlistIndex, songData);
            addedCount++;
        }
    }

    if (addedCount > 0) {
        QMessageBox::information(this, "Success",
                                 QString("Added %1 song(s) to the playlist!").arg(addedCount));

        // Refresh the playlist view
        onPlaylistSelected(playlistIndex);

        // Clear selection in library
        lib->tableView->clearSelection();

        statusBar()->showMessage(QString("Added %1 songs to playlist").arg(addedCount), 3000);
    } else {
        QMessageBox::warning(this, "Error", "Failed to add songs to playlist!");
    }
}

void MainWindow::refreshPlaylists() {
    PlaylistManager *manager = qobject_cast<PlaylistManager*>(contentStack->widget(1));
    if (manager) {
        manager->playlistList->clear();
        auto names = musicController->getAllPlaylistNames();
        manager->playlistList->addItems(names);
    }
}

void MainWindow::populateTable(const QVector<QStringList>& data) {
    SongLibrary *lib = qobject_cast<SongLibrary*>(contentStack->widget(0));
    if (!lib) return;
    lib->setSongs(data);
}

void MainWindow::populatePlaylistTable(const QVector<QStringList>& data) {
    PlaylistManager *manager = qobject_cast<PlaylistManager*>(contentStack->widget(1));
    if (!manager) return;

    manager->playlistSongsTable->setRowCount(data.size());
    manager->playlistSongsTable->setColumnCount(5);

    for (int r = 0; r < data.size(); ++r) {
        for (int c = 0; c < data[r].size() && c < 5; ++c) {
            manager->playlistSongsTable->setItem(r, c, new QTableWidgetItem(data[r][c]));
        }
    }
}
