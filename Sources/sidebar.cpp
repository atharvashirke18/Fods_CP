#include "Headers/sidebar.h"

Sidebar::Sidebar(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setSpacing(5);
    
    homeButton = new QPushButton("🏠 Home", this);
    libraryButton = new QPushButton("📚 Library", this);
    playlistsButton = new QPushButton("🎵 Playlists", this);
    duplicatesButton = new QPushButton("🔍 Duplicates", this);
    historyButton = new QPushButton("📊 History", this);
    settingsButton = new QPushButton("⚙ Settings", this);
    
    layout->addWidget(homeButton);
    layout->addWidget(libraryButton);
    layout->addWidget(playlistsButton);
    layout->addWidget(duplicatesButton);
    layout->addWidget(historyButton);
    layout->addWidget(settingsButton);
    layout->addStretch();
    
    setFixedWidth(150);
    setStyleSheet("QPushButton { text-align: left; padding: 10px; }");
}
