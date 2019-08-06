#include <QTabBar>
#include <QToolButton>
#include <QIcon>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tab.h"

#ifdef QT_DEBUG
#include <QDebug>
#endif

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->toolBar->addAction(QIcon(":/icons/add.png"), "New Tab", [this] () {
        addTab();
    })->setShortcut(tr("ctrl+n"));

    addTab();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addTab()
{
    ui->tabWidget->addTab(new Tab(this), "Tab " + QString::number(ui->tabWidget->count() + 1));

    /*
    auto plus = QIcon(":/icons/close.png");
    auto btn = new QToolButton();
    btn->setIcon(plus);
    btn->setShortcut(tr("ctrl+w"));
    ui->tabWidget->tabBar()->setTabButton(i, QTabBar::RightSide, btn);
    connect(btn, &QToolButton::clicked, this, [this, i] () {
        ui->tabWidget->tabBar()->removeTab(i);
        qDebug() << "Clicked: " << i;
    });
    */
}
