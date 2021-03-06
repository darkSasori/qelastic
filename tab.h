#ifndef TAB_H
#define TAB_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include "qjsonmodel.h"

namespace Ui {
class Tab;
}

class Tab : public QWidget
{
    Q_OBJECT

public:
    explicit Tab(QWidget *parent = nullptr);
    ~Tab();

public slots:
    void clickedSend(bool checked = false);
    void finished(QNetworkReply *);
    void formatter(bool checked = false);

private:
    Ui::Tab *ui;
    QJsonModel *model;
    QNetworkAccessManager *manager;


    const QStringList methods = QStringList()
            << "GET"
            << "POST"
            << "PUT"
            << "DELETE";

    enum {
        METHOD_GET,
        METHOD_POST,
        METHOD_PUT,
        METHOD_DELETE
    };
};

#endif // TAB_H
