#ifndef INITDB_H
#define INITDB_H
#include <QDate>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

const auto INSERT_CUSTOMER_SQL = QLatin1String(R"(
    insert into customer(id, name, password, checking, savings) values(?, ?, ?, ?, ?)
    )");

const auto INSERT_CHECKING_SQL = QLatin1String(R"(
    insert into checking(id, balance)
                      values(?, ?,)
    )");

const auto INSERT_SAVINGS_SQL = QLatin1String(R"(
    insert into savings(id, balance) values(?, ?)
    )");



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
