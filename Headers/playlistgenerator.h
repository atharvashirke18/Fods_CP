#ifndef PLAYLISTGENERATOR_H
#define PLAYLISTGENERATOR_H

#include <QDialog>
#include <QComboBox>
#include <QSpinBox>

class PlaylistGeneratorDialog : public QDialog
{
    Q_OBJECT
public:
    explicit PlaylistGeneratorDialog(QWidget *parent = nullptr);
    QString getSelectedMood() const;
    int getDuration() const;
private:
    QComboBox *moodCombo;
    QSpinBox *durationSpin;
};

#endif