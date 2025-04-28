#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
QT_FORWARD_DECLARE_CLASS(QComboBox)
QT_FORWARD_DECLARE_CLASS(QGridLayout)
QT_FORWARD_DECLARE_CLASS(QLabel)
QT_FORWARD_DECLARE_CLASS(QLineEdit)
QT_FORWARD_DECLARE_CLASS(QSpinBox)
QT_FORWARD_DECLARE_CLASS(QSqlError)
QT_FORWARD_DECLARE_CLASS(QSqlRelationalTableModel)
QT_FORWARD_DECLARE_CLASS(QTableView)

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void showError(const QSqlError &err);
    QSqlRelationalTableModel *model = nullptr;
    int customerIdx, CheckingIdx, SavingsIdx = 0;

    Ui::MainWindow *ui;
    void createLayout();
    void createModel();
    void configureWidgets();
    void createMappings();
    void createMenuBar();

    QWidget *window = nullptr;


};
#endif // MAINWINDOW_H
