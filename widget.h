#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
private:
    QPushButton *btnTest;
    void initUi();
    void initSlot();
private slots:
    void btnTestSlots();
};
#endif // WIDGET_H
