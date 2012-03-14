#include "httpget.h"
#include <QtCore/QCoreApplication>
#include <QStringList>

// HTTP GET example:
// ==========================================================================
// set command line argument (from the left bar->Projects->Run->Arguments)
// http://www.w3schools.com/xml/guestbook.asp
//
// gets an xml file from this URL
// rename the guestbook.asp to guestbook.xml after getting the file
// ==========================================================================

// HTTP POST example:
// ==========================================================================
// set command line argument: http://www.posttestserver.com/post.php
// uncomment the POST line in httpget.cpp-line 42, comment out the GET line
// if post is successful, post.php is created and has the link to the data
// ==========================================================================

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    
    QStringList args = a.arguments();
    if (args.count() != 2) {
        return 1;
    }

    HttpGet getter;
    if (!getter.getFile(QUrl(args[1])))
        return 1;

    QObject::connect(&getter, SIGNAL(done()), &a, SLOT(quit()));

    return a.exec();
}
