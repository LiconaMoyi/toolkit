#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSlider>
#include "moyi-ui/moyislider.h"
#include "moyi-ui/moyicircularprogress.h"

#include "qtcookbook.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
private:
    // base content
    QPushButton *btnQtInfo;
    QPushButton *btnCodeGen;
    QPushButton *btnBase;
    QPushButton *btnDataStorage;
    MoyiSlider       *const m_slider;
    MoyiCircularProgress *const m_circular_progress;

    QtCookBook *const qtCookBook;

    void initUi();
    void initSlot();
private slots:
    void btnQtInfoSlots();
    void btnBaseSlots();
    void btnDataStorageSlots();
};
#endif // WIDGET_H
