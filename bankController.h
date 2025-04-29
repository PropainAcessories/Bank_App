#ifndef BANKCONTROLLER_H
#define BANKCONTROLLER_H

#include <QModelIndex>
#include <QSize>
#include <QSqlRelationalDelegate>

QT_FORWARD_DECLARE_CLASS(QPainter)

class BankController : public QSqlRelationalDelegate
{
public:
    explicit BankController(int ratingColumn, QObject *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const override;

    QSize sizeHint(const QStyleOptionViewItem &option,
                   const QModelIndex &index) const override;

    bool editorEvent(QEvent *event, QAbstractItemModel *model,
                     const QStyleOptionViewItem &option,
                     const QModelIndex &index) override;

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override;

private:
    // const QIcon starIcon{QStringLiteral(":images/star.svg")};
    // const QIcon starFilledIcon{QStringLiteral(":images/star-filled.svg")};

    const int cellPadding = 6;
    const int iconDimension = 24;
    const int ratingColumn; // 0 in the combobox, otherwise 5
};


#endif // BANKCONTROLLER_H
