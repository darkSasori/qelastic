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

    connect(ui->btnSend, &QPushButton::clicked, this, &Tab::clickedSend);
    connect(manager, &QNetworkAccessManager::finished, this, &Tab::finished);
}

Tab::~Tab()
{
    delete ui;
}

void Tab::clickedSend(bool)
{
    auto request = QNetworkRequest(QUrl(ui->lineURL->text()));
    request.setHeader(QNetworkRequest::KnownHeaders::ContentTypeHeader, "application/json");
    manager->post(request, ui->query->toPlainText().toUtf8());
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
    ui->result->expandToDepth(3);
}
