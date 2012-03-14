#include "httpget.h"

// QHttp class works asyncronously. Ensures that the GUI remains responsive.
HttpGet::HttpGet(QObject *parent) :
    QObject(parent)
{
    connect (&http, SIGNAL(done(bool)), this, SLOT(httpDone(bool)));
}

bool HttpGet::getFile(const QUrl &url){

    if (!url.isValid()){
        cerr << "Error: Invalid URL" << endl;
        return false;
    }

    if (url.scheme() != "http"){
        cerr << "Error: URL must start with 'http:'" << endl;
        return false;
    }

    if (url.path().isEmpty()) {
        cerr << "Error: URL has no path" << endl;
        return false;
    }

    QString localFileName = "testvcs.txt";// QString localFileName = QFileInfo(url.path()).fileName();
    if (localFileName.isEmpty())
        localFileName = "httpget.out";

    file.setFileName(localFileName);

    if(!file.open(QIODevice::WriteOnly)) {
        cerr << "Error: cannot open " << qPrintable(file.fileName ())
             << " for writing: " << qPrintable(file.errorString())
                << endl;
        return false;
    }

    http.setHost(url.host(), url.port(80));
    http.get(url.path(), &file); //after getting file rename guestbook.asp as guestbook.xml
    //http.post(url.path(), "ts=10000&name=DUMMYPLAYER&team=1&x=20&y=30" , &file); // dumps the response to post.php
    http.close();
    return true;
}

void HttpGet::httpDone(bool error){

    if (error) {
        cerr << "Error: " << qPrintable(http.errorString()) << endl;
    }else {
        cerr << "File downloaded as " << qPrintable(file.fileName()) << endl;
    }
    file.close();
    emit done();
}
