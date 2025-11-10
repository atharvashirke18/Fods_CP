#include "Headers/nowplayingbar.h"
#include <QHBoxLayout>

NowPlayingBar::NowPlayingBar(QWidget *parent) : QWidget(parent)
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    
    songLabel = new QLabel("No song playing", this);
    prevButton = new QPushButton("⏮", this);
    playButton = new QPushButton("▶", this);
    nextButton = new QPushButton("⏭", this);
    progressSlider = new QSlider(Qt::Horizontal, this);
    
    layout->addWidget(songLabel);
    layout->addStretch();
    layout->addWidget(prevButton);
    layout->addWidget(playButton);
    layout->addWidget(nextButton);
    layout->addWidget(progressSlider);
    
    setFixedHeight(60);
}

void NowPlayingBar::setSongInfo(const QString &title) { songLabel->setText(title); }
