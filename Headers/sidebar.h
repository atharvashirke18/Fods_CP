#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

class Sidebar : public QWidget
{
    Q_OBJECT
public:
    explicit Sidebar(QWidget *parent = nullptr);
    QPushButton *homeButton;
    QPushButton *libraryButton;
    QPushButton *playlistsButton;
    QPushButton *duplicatesButton;
    QPushButton *historyButton;
    QPushButton *settingsButton;
};

#endif