#include "tab.h"
#include "ui_tab.h"
#include "highlighter.h"
#include <string>

#ifdef QT_DEBUG
#include <QDebug>
#endif

Tab::Tab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tab)
{
    ui->setupUi(this);

    auto highlighter = new Highlighter(ui->query->document());
    model = new QJsonModel;
    manager = new QNetworkAccessManager(this);

    ui->btnSend->setShortcut(tr("ctrl+e"));
    ui->result->setModel(model);

    connect(ui->btnSend, &QPushButton::clicked, this, &Tab::clickedSend);
    connect(manager, &QNetworkAccessManager::finished, this, &Tab::finished);
}

Tab::~Tab()
{
    delete ui;
}

void Tab::clickedSend(bool)
{
    qDebug() << "Start request";
    manager->get(QNetworkRequest(QUrl(ui->lineURL->text())));
}

void Tab::finished(QNetworkReply *reply)
{
    if (reply->error()) {
        qDebug() << "Error: " << reply->errorString();
        return;
    }
    qDebug() << "ok";
}
