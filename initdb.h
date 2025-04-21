#ifndef INITDB_H
#define INITDB_H
#include <QDate>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

/*
    This file defines a helper function to open a connection to an
    in-memory SQLITE database and to create a test table.

    If you want to use another database, simply modify the code
    below. All the examples in this directory use this function to
    connect to a database.
*/
//! [0]
QSqlError createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("Host");
    db.setDatabaseName("BaconBank");
    db.setUserName("root");
    db.setPassword("root");
    bool ok = db.open();
    if (!ok) {
        return db.lastError();
    }


    return QSqlError();
}
//! [0]

#endif
