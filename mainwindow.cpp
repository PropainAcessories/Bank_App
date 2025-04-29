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

    // Populate the model
    if (!model->select()) {
        showError(model->lastError());
        return;
    }

    configureWidgets();
    // create the mappings between the UI elements and the SQL model
    createMappings();

    tableView->setCurrentIndex(model->index(0, 0));
    tableView->selectRow(0);

    createMenuBar();
}

void MainWindow::showError(const QSqlError &err)
{
    QMessageBox::critical(this, tr("Unable to initialize Database"),
                          tr("Error initializing database: %1").arg(err.text()));
}
// creates the layout of my window.
void MainWindow::createLayout() {
    tableView = new QTableView(window);
    gridLayout = new QGridLayout(window);
    // labels and combo boxes
    customerLabel = new QLabel(tr("Customer:"), window);
    customerLineEdit = new QLineEdit(window);
    checkingLabel = new QLabel(tr("Checking:"), window);
    checkingComboBox = new QComboBox(window);
    savingsLabel = new QLabel(tr("Savings:"), window);
    savingsComboBox = new QComboBox(window);
    // sets boxes for wqidgets and such
    gridLayout->addWidget(customerLabel, 0, 0, Qt::AlignRight);
    gridLayout->addWidget(customerLineEdit, 0, 1, 1, 3);
    gridLayout->addWidget(checkingLabel, 1, 0, Qt::AlignRight);
    gridLayout->addWidget(checkingComboBox, 1, 1);
    gridLayout->addWidget(savingsLabel, 2, 0, Qt::AlignRight);
    gridLayout->addWidget(savingsComboBox, 2, 1);
    gridLayout->addWidget(tableView, 3, 0, 1, 4, Qt::AlignCenter);
    gridLayout->setColumnStretch(1, 1000);
    gridLayout->setColumnStretch(3, 1000);
    // sets margins
    gridLayout->setContentsMargins(18, 18, 18, 18);
    gridLayout->setSpacing(18);
    gridLayout->setAlignment(Qt::AlignHCenter);
}

void MainWindow::createModel() {
    model->setTable("customer");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    // Id values
    customerIdx = model->fieldIndex("customer");
    checkingIdx = model->fieldIndex("checking");
    savingsIdx = model->fieldIndex("savings");

    // Relations (keys)
    model->setRelation(customerIdx, QSqlRelation("customer", "id", "name"));
    model->setRelation(checkingIdx, QSqlRelation("checking", "id", "name"));
    model->setRelation(savingsIdx, QSqlRelation("savings", "id", "name"));

    // Set the localised header captions
    model->setHeaderData(customerIdx, Qt::Horizontal, tr("Customer Name"));
    model->setHeaderData(checkingIdx, Qt::Horizontal, tr("checking"));
    model->setHeaderData(savingsIdx, Qt::Horizontal, tr("savings"));
    model->setHeaderData(model->fieldIndex("checking"),
                         Qt::Horizontal, tr("Checking"));
    model->setHeaderData(model->fieldIndex("savings"),
                         Qt::Horizontal, tr("Savings"));
}

void MainWindow::configureWidgets()
{
    tableView->setModel(model);
    //finish bankcontroller.cpp bankcontroller.h
    //tableView->setItemDelegate(new BookDelegate(model->fieldIndex("rating"), tableView));
    tableView->setColumnHidden(model->fieldIndex("id"), true);
    tableView->verticalHeader()->setVisible(false);
    tableView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    // Lock and prohibit resizing of the width of the columns
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    tableView->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    tableView->horizontalHeader()->setFixedHeight(tableView->rowHeight(0));

    // increment by two to consider the frame
    tableView->setFixedWidth(tableView->horizontalHeader()->length() +
                             tableView->verticalScrollBar()->sizeHint().width() + 2);
    tableView->setMaximumHeight(tableView->verticalHeader()->length() +
                                tableView->horizontalHeader()->height() + 2);

    // authorComboBox->setModel(model->relationModel(authorIdx));
    // authorComboBox->setModelColumn(model->relationModel(authorIdx)->fieldIndex("name"));

    // genreComboBox->setModel(model->relationModel(genreIdx));
    // genreComboBox->setModelColumn(model->relationModel(genreIdx)->fieldIndex("name"));

    // yearSpinBox->setMaximum(9999);

    // ratingComboBox->setItemDelegate(new BookDelegate(0, this));
    // ratingComboBox->setLabelDrawingMode(QComboBox::LabelDrawingMode::UseDelegate);
    // ratingComboBox->addItems({"0", "1", "2", "3", "4", "5"});

    // ratingComboBox->setIconSize(iconSize());
}

// maps between models
void MainWindow::createMappings()
{
    QDataWidgetMapper *mapper = new QDataWidgetMapper(this);
    mapper->setModel(model);
    //mapper->setItemDelegate(new BookDelegate(model->fieldIndex("rating"), this));
    mapper->addMapping(customerLineEdit, model->fieldIndex("customer"));
    mapper->addMapping(savingsComboBox, savingsIdx);
    mapper->addMapping(checkingComboBox, checkingIdx);
    mapper->addMapping(savingsComboBox, model->fieldIndex("savings"), "currentIndex");
    connect(tableView->selectionModel(),
            &QItemSelectionModel::currentRowChanged,
            mapper,
            &QDataWidgetMapper::setCurrentModelIndex
            );
}

//yoinked from documentation, not touching
void MainWindow::createMenuBar()
{
    QAction *quitAction = new QAction(tr("&Quit"), this);
    QAction *aboutAction = new QAction(tr("&About"), this);
    QAction *aboutQtAction = new QAction(tr("&About Qt"), this);

    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(quitAction);

    QMenu *helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAction);
    helpMenu->addAction(aboutQtAction);

    connect(quitAction, &QAction::triggered, qApp, &QCoreApplication::quit);
    connect(aboutAction, &QAction::triggered, this, &MainWindow::about);
    connect(aboutQtAction, &QAction::triggered, qApp, &QApplication::aboutQt);
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About Books"),
                       tr("<p>The <b>Books</b> example shows how to use Qt SQL classes "
                          "with a model/view framework."));
}

