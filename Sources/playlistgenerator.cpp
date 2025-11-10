#include "Headers/playlistgenerator.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

PlaylistGeneratorDialog::PlaylistGeneratorDialog(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("Generate Playlist");
    setMinimumWidth(300);

    QVBoxLayout *layout = new QVBoxLayout(this);

    // Mood selection
    layout->addWidget(new QLabel("Select Mood:", this));
    moodCombo = new QComboBox(this);
    moodCombo->addItems({"Happy", "Sad", "Energetic", "Calm", "Party", "Neutral"});
    layout->addWidget(moodCombo);

    // Duration selection
    layout->addWidget(new QLabel("Duration (minutes):", this));
    durationSpin = new QSpinBox(this);
    durationSpin->setRange(5, 120);
    durationSpin->setValue(30);
    durationSpin->setSuffix(" min");
    layout->addWidget(durationSpin);

    // Add some spacing
    layout->addSpacing(10);

    // Buttons
    QPushButton *okBtn = new QPushButton("Generate", this);
    QPushButton *cancelBtn = new QPushButton("Cancel", this);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    buttonLayout->addWidget(cancelBtn);
    buttonLayout->addWidget(okBtn);

    layout->addLayout(buttonLayout);

    // Connect buttons
    connect(okBtn, &QPushButton::clicked, this, &QDialog::accept);
    connect(cancelBtn, &QPushButton::clicked, this, &QDialog::reject);

    // Set default button
    okBtn->setDefault(true);
}

QString PlaylistGeneratorDialog::getSelectedMood() const
{
    return moodCombo->currentText();
}

int PlaylistGeneratorDialog::getDuration() const
{
    return durationSpin->value();
}
