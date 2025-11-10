#include "Headers/playlistgenerator.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

PlaylistGeneratorDialog::PlaylistGeneratorDialog(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("Generate Playlist");
    QVBoxLayout *layout = new QVBoxLayout(this);

    layout->addWidget(new QLabel("Select Mood:", this));
    moodCombo = new QComboBox(this);
    moodCombo->addItems({"Happy", "Sad", "Energetic", "Calm", "Party", "Neutral"});

    layout->addWidget(new QLabel("Duration (minutes):", this));
    durationSpin = new QSpinBox(this);
    durationSpin->setRange(5, 120);
    durationSpin->setValue(30);

    QPushButton *okBtn = new QPushButton("Generate", this);
    connect(okBtn, &QPushButton::clicked, this, &QDialog::accept);

    layout->addWidget(moodCombo);
    layout->addWidget(durationSpin);
    layout->addWidget(okBtn);
}

QString PlaylistGeneratorDialog::getSelectedMood() const { return moodCombo->currentText(); }
int PlaylistGeneratorDialog::getDuration() const { return durationSpin->value(); }
