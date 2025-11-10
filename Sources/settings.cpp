#include "Headers/settings.h"
#include <QVBoxLayout>

Settings::Settings(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    
    loadLibraryButton = new QPushButton("Load Music Library", this);
    resetPreferencesButton = new QPushButton("Reset Preferences", this);
    
    connect(loadLibraryButton, &QPushButton::clicked, this, &Settings::loadLibraryClicked);
    connect(resetPreferencesButton, &QPushButton::clicked, this, &Settings::resetPreferencesClicked);
    
    layout->addWidget(loadLibraryButton);
    layout->addWidget(resetPreferencesButton);
    layout->addStretch();
}
