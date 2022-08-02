#include "widget.h"
#include <QApplication>
#include <QSqlDatabase>
#include <QLabel>
#include <QScreen>

Widget::Widget(QWidget *parent)
    : QWidget(parent),
    m_slider(new MoyiSlider),
    m_circular_progress(new MoyiCircularProgress),
    qtCookBook(new QtCookBook)
{
    // set background color
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Window, QBrush(QPixmap(":/image/images/002.png").scaledToHeight(810).scaledToWidth(1440)));
    this->setPalette(palette);

    setWindowTitle(tr("工具箱"));
    initUi();
    initSlot();

    // get the screen resolution
    qDebug() << QGuiApplication::primaryScreen()->geometry();
}

void Widget::initUi() {
    // draw from left to right
    QVBoxLayout *leftMenu = new QVBoxLayout;
    btnQtInfo = new QPushButton(tr("Qt知识"));
    btnQtInfo->setStyleSheet("QPushButton{background-color: rgb(100, 225, 225);border:2px groove gray;border-radius:4px;padding:2px 4px;border-style: outset;}"
                                           "QPushButton:hover{background-color:rgb(229, 241, 251); color: black;}"
                                           "QPushButton:pressed{background-color:rgb(204, 228, 247);border-style: inset;}");
    btnQtInfo->setFixedSize(QSize(100, 80));
    btnCodeGen = new QPushButton(tr("代码生成"));
    btnCodeGen->setStyleSheet("QPushButton{background-color: rgb(100, 225, 225);border:2px groove gray;border-radius:4px;padding:2px 4px;border-style: outset;}"
                              "QPushButton:hover{background-color:rgb(229, 241, 251); color: black;}"
                              "QPushButton:pressed{background-color:rgb(204, 228, 247);border-style: inset;}");
    btnCodeGen->setFixedSize(QSize(100, 80));
    leftMenu->addWidget(btnQtInfo);
    leftMenu->addWidget(btnCodeGen);
    QHBoxLayout *hLayout = new QHBoxLayout;
    btnBase = new QPushButton(tr("基本内容"));
    btnDataStorage = new QPushButton(tr("test button"));
    leftMenu->addWidget(btnBase);
    leftMenu->addWidget(btnDataStorage);
    leftMenu->addWidget(m_slider);
    leftMenu->addWidget(m_circular_progress);
    hLayout->addStretch(1);
    hLayout->addLayout(leftMenu, 3);
    hLayout->addStretch(7);


//    setMaximumSize(QSize(1920,1080));
    setMinimumSize(QSize(1440, 810));
    setBaseSize(QSize(1920,1080));
    setLayout(hLayout);
}

void Widget::initSlot() {
    connect(btnQtInfo, &QPushButton::clicked, this, &Widget::btnQtInfoSlots);
    connect(btnBase, &QPushButton::clicked, this, &Widget::btnBaseSlots);
    connect(btnDataStorage, &QPushButton::clicked, this, &Widget::btnDataStorageSlots);
}

void Widget::btnBaseSlots() {
    qDebug() << "go to base page";
}

void Widget::btnDataStorageSlots() {
    qDebug() << "go to data storage page";
//    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
//    db.setHostName("10.199.245.227");
//    db.setPort(3307);
//    db.setDatabaseName("python_codegen");
//    db.setUserName("apms");
//    db.setPassword("apms123123");
//    bool ok = db.open();
//    qDebug() << ok;
}

void Widget::btnQtInfoSlots() {
    qtCookBook->show();
}

Widget::~Widget()
{

}

