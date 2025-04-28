#ifndef INITDB_H
#define INITDB_H
//Imports
#include <QDate>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>

// add customer
void addCustomer(QSqlQuery &q, const QString &name, const QVariant &customerId,
                 const QVariant &checkingId, const QVariant &savingsId)
{
    q.addBindValue(name);
    q.addBindValue(customerId);
    q.addBindValue(checkingId);
    q.addBindValue(savingsId);
    q.exec();
}
// add checking account
QVariant addChecking(QSqlQuery &q, const QString &name, const QVariant &customerId,
                     int balance)
{
    q.addBindValue(name);
    q.addBindValue(customerId);
    q.addBindValue(balance);
    q.exec();
    return q.lastInsertId();
}
// add savings account
QVariant addSavings(QSqlQuery &q, const QString &name, QDate birthdate)
{
    q.addBindValue(name);
    q.addBindValue(birthdate);
    q.exec();
    return q.lastInsertId();
}

//Create tables for customer, checking and savings.
const auto CUSTOMER_SQL = QLatin1String(R"(
    create table customer(id integer primary key, name varchar, password varchar, checking integer,
                       savings integer)
    )");

const auto CHECKING_SQL =  QLatin1String(R"(
    create table checking(id integer primary key, balance float, transaction date)
    )");

const auto SAVINGS_SQL = QLatin1String(R"(
    create table savings(id integer primary key, balance float, transaction date)
    )");

// Insert values into the respective tables.
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

// void createRelationalTables() {
//     QSqlQuery query;
//     query.exec("create table customer(id int primary key, name varchar(20), password varchar(20) checking int, savings int)");
//     query.exec("insert into customer values(1, 'Bill Teach', imBlackbeard123, 5489, 987)");
//     query.exec("insert into customer values(2, 'Marshall Newgate', badPassword, 3918, 871)");
//     query.exec("insert into customer values(3, 'Olier levasseur', gibberish, 2141, 195)");
//     query.exec("insert into customer values(4, 'Anne Bonny', goodPassword, 6187, 819)");
//     query.exec("insert into customer values(5, 'Henry Morgan', rumGuy456, 5667, 437)");

//     query.exec("create table checking(id int, balance float)");
//     query.exec("insert into customer checking(5489, 10500)");
//     query.exec("insert into customer checking(3918, 12000)");
//     query.exec("insert into customer checking(2141, 68000)");
//     query.exec("insert into customer checking(5667, 27000)");

//     query.exec("create table savings(id int, balance float)");
//     query.exec("insert into customer savings(871, 219876)");
//     query.exec("insert into customer savings(195, 371561)");
//     query.exec("insert into customer savings(819, 194375)");
//     query.exec("insert into customer savings(437, 457682)");
// }

//! [0]
QSqlError initDb()
{
    //database connection and information
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("Host");
    db.setDatabaseName("BaconBank");
    db.setUserName("root");
    db.setPassword("root");
    bool ok = db.open();
    if (!ok) {
        return db.lastError();
    }
    // Database tables
    QStringList tables = db.tables();
    if (tables.contains("customer", Qt::CaseInsensitive)
        && tables.contains("checking", Qt::CaseInsensitive) &&
        tables.contains("checking", Qt::CaseInsensitive))
        return QSqlError();
    // Brings the database tables or errors about them
    QSqlQuery q;
    if (!q.exec(CUSTOMER_SQL))
        return q.lastError();
    if (!q.exec(CHECKING_SQL))
        return q.lastError();
    if (!q.exec(SAVINGS_SQL))
        return q.lastError();
    // Inserts stuff into database tables if they are empty
    if (!q.prepare(INSERT_CUSTOMER_SQL))
        return q.lastError();


    if (!q.prepare(INSERT_CHECKING_SQL))
        return q.lastError();


    if (!q.prepare(INSERT_SAVINGS_SQL))
        return q.lastError();

    return QSqlError();
}
//! [0]

#endif
