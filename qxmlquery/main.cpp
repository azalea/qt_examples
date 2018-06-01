#include <QCoreApplication>
#include <iostream>
#include <QXmlQuery>
#include <QXmlResultItems>
#include <QXmlNodeModelIndex>
#include <QBuffer>
#include <QString>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QString s("<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>\n"
              "<bookstore>\n"
              "<book class=\"include\">\n"
                "<title lang=\"zh\">Harry Potter</title>\n"
                "<price>29.99</price>\n"
              "</book>\n"
              "<book>\n"
                "<title lang=\"en\">Learning XML</title>\n"
                "<price>39.95</price>\n"
              "</book>\n"
              "</bookstore>\n");
    std::cout << s.toStdString() << std::endl;
    QXmlQuery query;
    QBuffer device;
    device.setData(s.toUtf8());
    device.open(QIODevice::ReadOnly);
    query.bindVariable("xmlDoc", &device);
    query.setQuery("doc($xmlDoc)//book[@class=\"include\"]/title/@lang");
    QXmlResultItems result;
    query.evaluateTo(&result);
    if (query.isValid()) {
        query.evaluateTo(&result);
        QXmlItem item(result.next());
        while (!item.isNull()) {
            if (item.isAtomicValue()) {
                QString value = item.toAtomicValue().toString();
                std::cout << "Atomic: " << value.toStdString() << std::endl;
            }
            else if (item.isNode()) {
                QXmlNodeModelIndex index = item.toNodeModelIndex();
                QString value = index.stringValue();
                std::cout << "Node: " << value.toStdString() << std::endl;
            }
            item = result.next();
        }
        if (result.hasError()) {
            std::cout << "Runtime error" << std::endl;
        }
    }
    return 0;
}
