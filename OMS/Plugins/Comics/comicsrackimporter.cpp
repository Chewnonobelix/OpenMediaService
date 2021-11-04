#include "comicsrackimporter.h"

ComicsRackImporter::ComicsRackImporter(QObject* parent): QObject(parent)
{

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
        auto size = book.elementsByTagName("FileSize")
    }
    return true;
}
