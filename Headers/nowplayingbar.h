#ifndef NOWPLAYINGBAR_H
#define NOWPLAYINGBAR_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QSlider>

class NowPlayingBar : public QWidget
{
    Q_OBJECT
public:
    explicit NowPlayingBar(QWidget *parent = nullptr);
    void setSongInfo(const QString &title);
    QLabel *songLabel;
    QPushButton *playButton;
    QPushButton *nextButton;
    QPushButton *prevButton;
    QSlider *progressSlider;
};

#endif