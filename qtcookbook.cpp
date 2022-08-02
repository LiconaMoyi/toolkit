#include "qtcookbook.h"
#include <QVBoxLayout>
#include <QPushButton>

QtCookBook::QtCookBook(QWidget *parent)
    : QWidget{parent}
{
    initUi();
}

void QtCookBook::initUi() {

    QVBoxLayout *vLayout = new QVBoxLayout;
    QPushButton *btnTest = new QPushButton("测试按钮");
    vLayout->addWidget(btnTest);
    setMaximumSize(QSize(1200,900));
    setMinimumSize(QSize(1200,900));
    setLayout(vLayout);

}


