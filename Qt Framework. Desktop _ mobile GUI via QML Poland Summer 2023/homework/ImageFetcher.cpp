#include "ImageFetcher.h"
#include <QDir>
#include <QUrl>
#include <QDebug>

ImageFetcher::ImageFetcher(QObject *parent) : QObject(parent)
{
}

QStringList ImageFetcher::getImageList(const QString &folderPath)
{
    QDir directory(QUrl(folderPath).toLocalFile());  // Convert URL to local file path

    // Check if directory exists
    if(!directory.exists()) {
        qWarning() << "Directory does not exist:" << folderPath;
        return QStringList();
    }

    // Optionally refresh the directory listing
    directory.refresh();

    QStringList images = directory.entryList(QStringList() << "*.jpg" << "*.png", QDir::Files);
    QStringList fullPaths;
    for(const QString &image : images)
    {
        fullPaths.append(directory.filePath(image));
    }

    // Log the number of found images
    qDebug() << "Found" << fullPaths.size() << "images in" << folderPath;

    return fullPaths;
}
