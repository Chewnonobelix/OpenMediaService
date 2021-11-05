#include "comicsrackimporter.h"

ComicsRackImporter::ComicsRackImporter(QObject* parent): InterfaceImporter(parent)
{

}

QString ComicsRackImporter::name() const
{
    return "ComicsRack";
}

bool ComicsRackImporter::import(QString path)
{
    if(!path.endsWith(".zip"))
        return false;

    QTemporaryDir temp("temp/comicsRackImport");
    QProcess unzipper;

    unzipper.start("3rdParty/7z", QStringList()<<"x"<<"-o"+temp.path()<<path);
    unzipper.waitForFinished();

    QFile file(temp.path()+"/ComicDb.xml");
    if(!file.open(QIODevice::ReadOnly))
        return false;

    QDomDocument doc;
    if(!doc.setContent(&file)) {
        file.close();
        return false;
    }

    auto root = doc.documentElement();
    auto books = root.elementsByTagName("Books").at(0).toElement().elementsByTagName("Book");

    for(auto it = 0; it < books.count(); it++) {
        auto book = books.at(it).toElement();
        auto media = factory<Media>();
        media->setPath(book.attribute("File"));
        auto added = book.elementsByTagName("Added").at(0).toElement().text();
        media->setAdded(QDate::fromString(added));
        auto size = book.elementsByTagName("FileSize").at(0).toElement().text().toInt();
        media->setMetadata("size", size);
        if(!book.elementsByTagName("LastPageRead").isEmpty()) {
            auto lastPageRead = book.elementsByTagName("LastPageRead").at(0).toElement().text().toInt();
            auto pageCount = book.elementsByTagName("PageCount").at(0).toElement().text().toInt();
            media->setCurrentRead((lastPageRead * 100.0) / pageCount);
        }

        if(!book.elementsByTagName("Opened").isEmpty()) {
            auto opened = book.elementsByTagName("Opened").at(0).toElement().text();
            media->setLastFinish(QDateTime::fromString(opened));
        }

        emit findMedia(media);
    }

    auto watchFolder = root.elementsByTagName("WatchFolders").at(0).toElement().elementsByTagName("WatchFolder");
    for(auto it = 0; it < watchFolder.count(); it++) {
        emit findWatchfolder(watchFolder.at(it).toElement().attribute("Folder"));
    }

    return true;
}

QStringList ComicsRackImporter::filters() const
{
    return {"*.zip"};
}
