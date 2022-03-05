#include <QCoreApplication>
#include "QDir"
#include "QDebug"
#include "quazip.h"
#include "quazipfile.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    if (argc<2) {
        qDebug() << "Specify path to zip fil as first argument";
        return 1;
    }

    QString zipPath = a.arguments().at(1);

    qDebug() << "Provided path was "+zipPath;

    QuaZip zipfile(zipPath);
    zipfile.open(QuaZip::mdUnzip);

    if (zipfile.isOpen()) {
        for (bool f = zipfile.goToFirstFile(); f; f = zipfile.goToNextFile()) {

            QString filePath = zipfile.getCurrentFileName();
            QuaZipFile zFile(zipfile.getZipName(), filePath);

            zFile.open(QIODevice::ReadOnly);
            if (!zFile.isOpen()) {
                qDebug() << "Failed to open zfile";
                return 1;
            }
            qint64 size=zFile.size();
            char * buffer = (char *)malloc(size); // this fails with large files, use a loop
            zFile.read(buffer, size);
            zFile.close();

            qDebug() << "Extracting "+filePath+" ("+QString::number(size)+" bytes)";

            if (QFile::exists("./"+filePath)) QFile::remove("./"+filePath);

            QFile dstFile("./"+filePath);

            dstFile.open(QIODevice::WriteOnly);
            if (dstFile.isOpen()){
                dstFile.write(buffer, size);
                free(buffer);
                dstFile.close();
            }
            else {
                qDebug() << "Could not extract file "+filePath+" "+dstFile.errorString();
                return 1;
            }
        }
    }
    else {
        qDebug() << "Could not open the zip file";
        return 1;
    }
    zipfile.close();

    qDebug() << "Done";

    return 0;
}
