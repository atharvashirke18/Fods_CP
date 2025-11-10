#ifndef USERANALYTICS_H
#define USERANALYTICS_H

#include <QWidget>
#include <QListWidget>
#include <QLabel>

class UserAnalytics : public QWidget
{
    Q_OBJECT
public:
    explicit UserAnalytics(QWidget *parent = nullptr);
    void setTopGenres(const QStringList& genres);
    void setTopArtists(const QStringList& artists);
    QListWidget *genresList;
    QListWidget *artistsList;
};

#endif