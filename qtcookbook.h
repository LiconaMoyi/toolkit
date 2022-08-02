#ifndef QTCOOKBOOK_H
#define QTCOOKBOOK_H

#include <QWidget>

class QtCookBook : public QWidget
{
    Q_OBJECT
public:
    explicit QtCookBook(QWidget *parent = nullptr);

private:
    void initUi();

signals:

};

#endif // QTCOOKBOOK_H
