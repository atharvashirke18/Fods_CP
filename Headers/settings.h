#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>
#include <QPushButton>

class Settings : public QWidget
{
    Q_OBJECT
public:
    explicit Settings(QWidget *parent = nullptr);
    QPushButton *loadLibraryButton;
    QPushButton *resetPreferencesButton;
signals:
    void loadLibraryClicked();
    void resetPreferencesClicked();
};

#endif