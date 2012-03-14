#ifndef HTTPGET_H
#define HTTPGET_H

#include <QObject>
#include <QHttp>
#include <QFile>
#include <QFileInfo>
#include <QUrl>
#include <iostream>
// tada
using namespace std;

class HttpGet : public QObject
{
    Q_OBJECT
public:
    explicit HttpGet(QObject *parent = 0);
    bool getFile(const QUrl &url);// retrieves the file specified by the URL


signals:
    void done();

public slots:
    void httpDone(bool error); // called whenever the transfer is completed
    
private:
    QHttp http; //http connection encapsulator
    QFile file;
};

#endif // HTTPGET_H
