#include "Headers/useranalytics.h"
#include <QHBoxLayout>
#include <QVBoxLayout>

UserAnalytics::UserAnalytics(QWidget *parent) : QWidget(parent)
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    
    QVBoxLayout *genresLayout = new QVBoxLayout();
    genresLayout->addWidget(new QLabel("Top Genres:", this));
    genresList = new QListWidget(this);
    genresLayout->addWidget(genresList);
    
    QVBoxLayout *artistsLayout = new QVBoxLayout();
    artistsLayout->addWidget(new QLabel("Top Artists:", this));
    artistsList = new QListWidget(this);
    artistsLayout->addWidget(artistsList);
    
    layout->addLayout(genresLayout);
    layout->addLayout(artistsLayout);
}

void UserAnalytics::setTopGenres(const QStringList& genres) { genresList->addItems(genres); }
void UserAnalytics::setTopArtists(const QStringList& artists) { artistsList->addItems(artists); }
