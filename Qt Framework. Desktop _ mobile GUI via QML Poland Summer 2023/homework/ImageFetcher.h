// ImageFetcher.h
#ifndef IMAGEFETCHER_H
#define IMAGEFETCHER_H

#include <QObject>
#include <QDir>
#include <QStringList>

class ImageFetcher : public QObject
{
    Q_OBJECT
public:
    explicit ImageFetcher(QObject *parent = nullptr);

    Q_INVOKABLE QStringList getImageList(const QString &folderPath);
};

#endif // IMAGEFETCHER_H
