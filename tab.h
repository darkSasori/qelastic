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

private:
    Ui::Tab *ui;
    QJsonModel *model;
    QNetworkAccessManager *manager;
};

#endif // TAB_H
