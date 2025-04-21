#include "mainwindow.h"
#include "initdb.h"
#include <QApplication>
#include <QSqlRelationalTableModel>
#include <QtWidgets>
#include <QtSql>

void initializeModel(QSqlRelationalTableModel *model) {
    model->setTable("Customer");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    // TODO::Set Keys
    model->setRelation(2, QSqlRelation("checking", "id", "name"));
    model->setRelation(3, QSqlRelation("savings", "id", "name"));

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Name"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Checking"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Savings"));

    model->select();
}
// Stolen from docs, may have to edit later
std::unique_ptr<QTableView> createView(const QString &title, QSqlTableModel *model)
{
    //! [4]
    std::unique_ptr<QTableView> view{new QTableView};
    view->setModel(model);
    view->setItemDelegate(new QSqlRelationalDelegate(view.get()));
    //! [4]
    view->setWindowTitle(title);
    return view;
}

void createRelationalTables() {
    QSqlQuery query;
    query.exec("create table customer(id int primary key, name varchar(20), password varchar(20) checking int, savings int)");
    query.exec("insert into customer values(1, 'Bill Teach', imBlackbeard123, 5489, 987)");
    query.exec("insert into customer values(2, 'Marshall Newgate', badPassword, 3918, 871)");
    query.exec("insert into customer values(3, 'Olier levasseur', gibberish, 2141, 195)");
    query.exec("insert into customer values(4, 'Anne Bonny', goodPassword, 6187, 819)");
    query.exec("insert into customer values(5, 'Henry Morgan', rumGuy456, 5667, 437)");

    query.exec("create table checking(id int, balance float)");
    query.exec("insert into customer checking(5489, 10500)");
    query.exec("insert into customer checking(3918, 12000)");
    query.exec("insert into customer checking(2141, 68000)");
    query.exec("insert into customer checking(5667, 27000)");

    query.exec("create table savings(id int, balance float)");
    query.exec("insert into customer savings(871, 219876)");
    query.exec("insert into customer savings(195, 371561)");
    query.exec("insert into customer savings(819, 194375)");
    query.exec("insert into customer savings(437, 457682)");
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    if(!createConnection()) {
        return EXIT_FAILURE;
    }

    // Create table function


    createRelationalTables();

    QSqlRelationalTableModel model;

    initializeModel(&model);

    std::unique_ptr<QTableView> view = createView(QObject::tr("Relational Table Model"), &model);
    view->show();


    MainWindow w;
    w.show();
    return a.exec();
}
