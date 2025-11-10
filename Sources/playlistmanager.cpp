// playlistmanager.cpp - Fixed with generate dialog implementation

#include "Headers/playlistmanager.h"
#include "Headers/playlistgenerator.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QDebug>
#include <QTimer>
#include <QApplication>
#include <QFileInfo>
#include <QMessageBox>

PlaylistManager::PlaylistManager(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Top area: list of playlists on the left, songs in the selected playlist on the right
    QHBoxLayout *topLayout = new QHBoxLayout();

    playlistList = new QListWidget(this);
    playlistList->setFixedWidth(220);
    playlistList->setSelectionMode(QAbstractItemView::SingleSelection);

    playlistSongsTable = new QTableWidget(this);
    playlistSongsTable->setColumnCount(5);
    playlistSongsTable->setHorizontalHeaderLabels({"Title", "Artist", "Year", "Tempo", "Mood"});
    playlistSongsTable->horizontalHeader()->setStretchLastSection(true);
    playlistSongsTable->setSelectionBehavior(QAbstractItemView::SelectRows);

    topLayout->addWidget(playlistList);
    topLayout->addWidget(playlistSongsTable);

    // Buttons area below
    QHBoxLayout *buttonLayout = new QHBoxLayout();

    createButton = new QPushButton("➕ Create playlist", this);
    deleteButton = new QPushButton("🗑️ Delete playlist", this);
    addSongsButton = new QPushButton("➕ Add songs", this);

    // Generation buttons grouped
    generateMoodButton = new QPushButton("Generate: Mood", this);
    generateWorkoutButton = new QPushButton("Generate: Workout", this);
    generateRelaxationButton = new QPushButton("Generate: Relaxation", this);
    generatePartyButton = new QPushButton("Generate: Party", this);

    buttonLayout->addWidget(createButton);
    buttonLayout->addWidget(deleteButton);
    buttonLayout->addWidget(addSongsButton);
    buttonLayout->addStretch();
    buttonLayout->addWidget(generateMoodButton);
    buttonLayout->addWidget(generateWorkoutButton);
    buttonLayout->addWidget(generateRelaxationButton);
    buttonLayout->addWidget(generatePartyButton);

    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(buttonLayout);

    // Audio control area
    QHBoxLayout *audioLayout = new QHBoxLayout();
    playButton = new QPushButton("▶️ Play", this);
    pauseButton = new QPushButton("⏸️ Pause", this);
    stopButton = new QPushButton("⏹️ Stop", this);
    nextButton = new QPushButton("⏭️ Next", this);
    prevButton = new QPushButton("⏮️ Previous", this);
    statusLabel = new QLabel("Ready", this);

    audioLayout->addWidget(prevButton);
    audioLayout->addWidget(playButton);
    audioLayout->addWidget(pauseButton);
    audioLayout->addWidget(stopButton);
    audioLayout->addWidget(nextButton);
    audioLayout->addWidget(statusLabel);
    audioLayout->addStretch();

    mainLayout->addLayout(audioLayout);

    // Connect signals to the public signals declared in the header
    connect(playlistList, &QListWidget::currentRowChanged, this, &PlaylistManager::playlistSelected);

    connect(createButton, &QPushButton::clicked, this, [this]() {
        emit createPlaylistClicked();
    });

    connect(deleteButton, &QPushButton::clicked, this, [this]() {
        int idx = playlistList->currentRow();
        emit deletePlaylistClicked(idx);
    });

    connect(addSongsButton, &QPushButton::clicked, this, [this]() {
        int idx = playlistList->currentRow();
        emit addSongsClicked(idx);
    });

    // Fixed: Connect generate buttons to local slots instead of just emitting signals
    connect(generateMoodButton, &QPushButton::clicked, this, &PlaylistManager::handleGenerateMood);
    connect(generateWorkoutButton, &QPushButton::clicked, this, &PlaylistManager::handleGenerateWorkout);
    connect(generateRelaxationButton, &QPushButton::clicked, this, &PlaylistManager::handleGenerateRelaxation);
    connect(generatePartyButton, &QPushButton::clicked, this, &PlaylistManager::handleGenerateParty);

    // Audio control connections
    connect(playButton, &QPushButton::clicked, this, [this]() {
        int row = playlistSongsTable->currentRow();
        if (row >= 0) {
            playSongAtRow(row);
        } else {
            statusLabel->setText("No song selected");
        }
    });

    connect(pauseButton, &QPushButton::clicked, this, [this]() {
        pauseAudio();
    });

    connect(stopButton, &QPushButton::clicked, this, [this]() {
        stopAudio();
    });

    connect(nextButton, &QPushButton::clicked, this, [this]() {
        playNextSong();
    });

    connect(prevButton, &QPushButton::clicked, this, [this]() {
        playPreviousSong();
    });

    // Some basic sizing
    playlistSongsTable->setMinimumWidth(400);
    setMinimumSize(700, 400);
}

PlaylistManager::~PlaylistManager()
{
    stopAudio();
}

// NEW: Handle generate mood button
void PlaylistManager::handleGenerateMood()
{
    PlaylistGeneratorDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        QString mood = dialog.getSelectedMood();
        int duration = dialog.getDuration();

        // Emit signal with mood and duration parameters
        emit generatePlaylistRequested(mood, duration);

        QMessageBox::information(this, "Playlist Generation",
                                 QString("Generating %1 playlist for %2 minutes").arg(mood).arg(duration));
    }
}

// NEW: Handle generate workout button
void PlaylistManager::handleGenerateWorkout()
{
    // For workout, use preset mood
    emit generatePlaylistRequested("Energetic", 45);
    QMessageBox::information(this, "Playlist Generation",
                             "Generating Workout playlist (45 minutes, Energetic mood)");
}

// NEW: Handle generate relaxation button
void PlaylistManager::handleGenerateRelaxation()
{
    // For relaxation, use preset mood
    emit generatePlaylistRequested("Calm", 30);
    QMessageBox::information(this, "Playlist Generation",
                             "Generating Relaxation playlist (30 minutes, Calm mood)");
}

// NEW: Handle generate party button
void PlaylistManager::handleGenerateParty()
{
    // For party, use preset mood
    emit generatePlaylistRequested("Party", 60);
    QMessageBox::information(this, "Playlist Generation",
                             "Generating Party playlist (60 minutes, Party mood)");
}

void PlaylistManager::playSongAtRow(int row)
{
    if (row < 0 || row >= playlistSongsTable->rowCount()) {
        statusLabel->setText("Invalid song selection");
        return;
    }

    // Highlight the current row
    playlistSongsTable->selectRow(row);

    // Try to find the audio file with different extensions
    QString audioFile = QString("/home/lucifer/projects/Fods_CP/data/songs/song%1.ogg").arg(row + 1);

    // Check if file exists, if not try other formats
    QFileInfo fileInfo(audioFile);
    if (!fileInfo.exists()) {
        audioFile = QString("/home/lucifer/projects/Fods_CP/data/songs/song%1.wav").arg(row + 1);
        fileInfo.setFile(audioFile);
        if (!fileInfo.exists()) {
            audioFile = QString("/home/lucifer/projects/Fods_CP/data/songs/song%1.mp3").arg(row + 1);
            fileInfo.setFile(audioFile);
        }
    }

    playAudio(audioFile);
}

void PlaylistManager::playNextSong()
{
    int currentRow = playlistSongsTable->currentRow();
    int nextRow = currentRow + 1;

    if (nextRow < playlistSongsTable->rowCount()) {
        playSongAtRow(nextRow);
    } else {
        statusLabel->setText("End of playlist");
        stopAudio();
    }
}

void PlaylistManager::playPreviousSong()
{
    int currentRow = playlistSongsTable->currentRow();
    int prevRow = currentRow - 1;

    if (prevRow >= 0) {
        playSongAtRow(prevRow);
    } else {
        statusLabel->setText("Start of playlist");
    }
}

void PlaylistManager::playAudio(const QString &filePath)
{
    // Check if file exists
    QFileInfo fileInfo(filePath);
    if (!fileInfo.exists()) {
        statusLabel->setText(QString("File not found: %1").arg(filePath));
        qDebug() << "Audio file not found:" << filePath;
        return;
    }

    try {
        // Stop current playback if any
        if (sound) {
            sf::Sound::Status currentStatus = sound->getStatus();
            if (currentStatus == sf::SoundSource::Status::Playing || currentStatus == sf::SoundSource::Status::Paused) {
                sound->stop();
            }
        }

        // Load audio file
        soundBuffer = std::make_unique<sf::SoundBuffer>();
        if (!soundBuffer->loadFromFile(filePath.toStdString())) {
            statusLabel->setText(QString("Failed to load: %1").arg(fileInfo.fileName()));
            qDebug() << "Error loading audio file:" << filePath;
            return;
        }

        // Create and play sound
        sound = std::make_unique<sf::Sound>(*soundBuffer);
        sound->play();
        currentAudioFile = fileInfo.fileName();

        statusLabel->setText(QString("▶️ Playing: %1").arg(currentAudioFile));
        qDebug() << "Playing audio:" << filePath;

        // Update status periodically
        QTimer::singleShot(100, this, &PlaylistManager::updateAudioStatus);
    } catch (const std::exception &e) {
        statusLabel->setText(QString("Error: %1").arg(e.what()));
        qDebug() << "Exception playing audio:" << e.what();
    }
}

void PlaylistManager::pauseAudio()
{
    if (sound) {
        sf::Sound::Status status = sound->getStatus();
        if (status == sf::SoundSource::Status::Playing) {
            sound->pause();
            statusLabel->setText(QString("⏸️ Paused: %1").arg(currentAudioFile));
            qDebug() << "Audio paused";
        } else if (status == sf::SoundSource::Status::Paused) {
            // Resume playback
            sound->play();
            statusLabel->setText(QString("▶️ Playing: %1").arg(currentAudioFile));
            QTimer::singleShot(100, this, &PlaylistManager::updateAudioStatus);
            qDebug() << "Audio resumed";
        }
    }
}

void PlaylistManager::stopAudio()
{
    if (sound) {
        sound->stop();
        statusLabel->setText("⏹️ Stopped");
        qDebug() << "Audio stopped";
    }
}

void PlaylistManager::updateAudioStatus()
{
    if (!sound) return;

    sf::Sound::Status status = sound->getStatus();

    if (status == sf::SoundSource::Status::Playing) {
        int milliseconds = sound->getPlayingOffset().asMilliseconds();
        int seconds = milliseconds / 1000;
        int minutes = seconds / 60;
        seconds = seconds % 60;

        statusLabel->setText(QString("▶️ Playing: %1 [%2:%3]")
                                 .arg(currentAudioFile)
                                 .arg(minutes, 2, 10, QChar('0'))
                                 .arg(seconds, 2, 10, QChar('0')));

        // Continue updating
        QTimer::singleShot(100, this, &PlaylistManager::updateAudioStatus);
    } else if (status == sf::SoundSource::Status::Paused) {
        statusLabel->setText(QString("⏸️ Paused: %1").arg(currentAudioFile));
    } else if (status == sf::SoundSource::Status::Stopped) {
        statusLabel->setText("⏹️ Playback finished");
        // Auto-play next song when current finishes
        QTimer::singleShot(500, this, &PlaylistManager::playNextSong);
    }
}
