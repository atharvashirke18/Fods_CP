#ifndef SONGTABLEMODEL_H
#define SONGTABLEMODEL_H

#include <QAbstractTableModel>
#include <QVector>
#include <QStringList>

class SongTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit SongTableModel(QObject *parent = nullptr) : QAbstractTableModel(parent) {}

    QVector<QStringList> songs;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override {
        Q_UNUSED(parent)
        return songs.size();
    }

    int columnCount(const QModelIndex &parent = QModelIndex()) const override {
        Q_UNUSED(parent)
        return songs.isEmpty() ? 0 : songs[0].size();
    }

    QVariant data(const QModelIndex &index, int role) const override {
        if (!index.isValid() || role != Qt::DisplayRole)
            return QVariant();
        return songs[index.row()][index.column()];
    }

    // ✅ Public safe updater
    void setSongs(const QVector<QStringList> &newSongs) {
        beginResetModel();
        songs = newSongs;
        endResetModel();
    }
};

#endif
