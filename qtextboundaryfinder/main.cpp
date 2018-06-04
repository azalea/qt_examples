#include <QCoreApplication>
#include <QTextBoundaryFinder>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QString s;
    s = "Times Ob" + QString(QChar::SoftHyphen) + "served Per Panel";
    QTextBoundaryFinder finder(QTextBoundaryFinder::Line, s);
    int pos = 0;
    int prevPos = 0;
    while (pos != -1) {
        qDebug() << "prevPos" << prevPos << "pos" << pos << "line" << s.mid(prevPos, pos-prevPos);
        prevPos = pos;
        pos = finder.toNextBoundary();
    }
    return 0;
}
