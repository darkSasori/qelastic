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

    ui->method->addItems(methods);

    model = new QJsonModel;
    manager = new QNetworkAccessManager(this);

    ui->btnSend->setShortcut(tr("ctrl+e"));
    ui->btnFormatter->setShortcut(tr("ctrl+f"));
    ui->result->setModel(model);

    connect(ui->btnSend, &QPushButton::clicked, this, &Tab::clickedSend);
    connect(manager, &QNetworkAccessManager::finished, this, &Tab::finished);
    connect(ui->btnFormatter, &QPushButton::clicked, this, &Tab::formatter);
}

Tab::~Tab()
{
    delete ui;
}

void Tab::clickedSend(bool)
{

    auto request = QNetworkRequest(QUrl(ui->lineURL->text()));
    request.setHeader(QNetworkRequest::KnownHeaders::ContentTypeHeader, "application/json");

    switch (ui->method->currentIndex()) {
    case Tab::METHOD_GET:
        manager->get(request);
        break;
    case Tab::METHOD_POST:
        manager->post(request, ui->query->toPlainText().toUtf8());
        break;
    case Tab::METHOD_PUT:
        manager->put(request, ui->query->toPlainText().toUtf8());
        break;
    case Tab::METHOD_DELETE:
        auto reply = QMessageBox::question(
                    this,
                    "Do you want call delete on this URL?",
                    ui->lineURL->text(),
                    QMessageBox::Yes | QMessageBox::No,
                    QMessageBox::No
                    );
        if (reply == QMessageBox::Yes) {
            manager->deleteResource(request);
        }
        break;
    }
}

void Tab::formatter(bool)
{
    auto tmp = new QJsonModel;
    tmp->loadJson(ui->query->toPlainText().toUtf8());
    ui->query->setText(tmp->json().toJson());
}

void Tab::finished(QNetworkReply *reply)
{
    if (reply->error()) {
        QMessageBox::warning(this, "Error", reply->errorString());
        return;
    }
    model->load(reply);
    ui->result->expandToDepth(3);
}
