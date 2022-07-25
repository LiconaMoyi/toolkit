#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    initUi();
    initSlot();

}

void Widget::initUi() {
    QLayout *vLayout = new QHBoxLayout;
    btnTest = new QPushButton(tr("test button"));
    vLayout->addWidget(btnTest);
    setMaximumSize(QSize(300,400));
    setMinimumSize(QSize(400,400));
    setLayout(vLayout);
}

void Widget::initSlot() {
    connect(btnTest, &QPushButton::clicked, this, &Widget::btnTestSlots);
}

void Widget::btnTestSlots() {
    qDebug() << "btnTest Clicked";
}

Widget::~Widget()
{

}

