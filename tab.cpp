#include "tab.h"
#include "ui_tab.h"
#include "highlighter.h"
#include <string>
#include <QMessageBox>

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
    ui->lineURL->setText("http://s-elasticsearch.internal.socialbase.com.br:9200");

    connect(ui->btnSend, &QPushButton::clicked, this, &Tab::clickedSend);
    connect(manager, &QNetworkAccessManager::finished, this, &Tab::finished);
}

Tab::~Tab()
{
    delete ui;
}

void Tab::clickedSend(bool)
{
    manager->get(QNetworkRequest(QUrl(ui->lineURL->text())));
}

void Tab::finished(QNetworkReply *reply)
{
    if (reply->error()) {
        auto msgBox = new QMessageBox;
        msgBox->setText(reply->errorString());
        msgBox->exec();
        return;
    }
    model->load(reply);
    ui->result->expandAll();
}
