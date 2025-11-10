#ifndef PLAYLISTMANAGER_H
#define PLAYLISTMANAGER_H

#include <QWidget>
#include <QListWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QLabel>
#include <SFML/Audio.hpp>
#include <memory>

class PlaylistManager : public QWidget
{
    Q_OBJECT

public:
    explicit PlaylistManager(QWidget *parent = nullptr);
    ~PlaylistManager();

    QListWidget *playlistList;
    QTableWidget *playlistSongsTable;

signals:
    void playlistSelected(int index);
    void createPlaylistClicked();
    void deletePlaylistClicked(int index);
    void addSongsClicked(int playlistIndex);
    void generateMoodClicked();
    void generateWorkoutClicked();
    void generateRelaxationClicked();
    void generatePartyClicked();

    // NEW: Signal with parameters for actual playlist generation
    void generatePlaylistRequested(const QString &mood, int duration);

private slots:
    // NEW: Slots to handle generate button clicks
    void handleGenerateMood();
    void handleGenerateWorkout();
    void handleGenerateRelaxation();
    void handleGenerateParty();

    void updateAudioStatus();

private:
    QPushButton *createButton;
    QPushButton *deleteButton;
    QPushButton *addSongsButton;
    QPushButton *generateMoodButton;
    QPushButton *generateWorkoutButton;
    QPushButton *generateRelaxationButton;
    QPushButton *generatePartyButton;

    // Audio controls
    QPushButton *playButton;
    QPushButton *pauseButton;
    QPushButton *stopButton;
    QPushButton *nextButton;
    QPushButton *prevButton;
    QLabel *statusLabel;

    // SFML audio objects
    std::unique_ptr<sf::SoundBuffer> soundBuffer;
    std::unique_ptr<sf::Sound> sound;
    QString currentAudioFile;

    // Audio playback methods
    void playAudio(const QString &filePath);
    void pauseAudio();
    void stopAudio();
    void playSongAtRow(int row);
    void playNextSong();
    void playPreviousSong();
};

#endif // PLAYLISTMANAGER_H
