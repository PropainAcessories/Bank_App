//Header Files
#include "mainwindow.h"
#include "initdb.h"
//Qt Libraries
#include <QApplication>
#include <QSqlRelationalTableModel>
#include <QComboBox>
#include <QDataWidgetMapper>
#include <QGridLayout>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QPainter>
#include <QScrollBar>
#include <QSpinBox>
#include <QSqlDatabase>
#include <QTableView>

/*
    model->setTable("customer");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    // TODO::Set Keys
    model->setRelation(2, QSqlRelation("checking", "id", "name"));
    model->setRelation(3, QSqlRelation("savings", "id", "name"));

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Name"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Checking"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Savings"));

    model->select();
*/

// Initialize SQL models

MainWindow::MainWindow(QWidget *parent)
{
    if (!QSqlDatabase::drivers().contains("QMYSQL"))
        QMessageBox::critical(this, tr("Unable to load Database"),
                              (tr)("MySQL driver not found."));
        //Put other UI functions here
    QSqlError err = initDb();
    if (err.type() != QSqlError::NoError) {
        showError(err);
        return;
    }
    window = new QWidget(this);
    setCentralWidget(window);

    createLayout();

    createModel();

}

void MainWindow::showError(const QSqlError &err)
{
    QMessageBox::critical(this, tr("Unable to initialize Database"),
                          tr("Error initializing database: %1").arg(err.text()));
}

void MainWindow::createModel() {

}



