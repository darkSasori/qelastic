#include "tab.h"
#include "ui_tab.h"
#include "highlighter.h"

Tab::Tab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tab)
{
    ui->setupUi(this);
    auto highlighter = new Highlighter(ui->textEdit->document());
}

Tab::~Tab()
{
    delete ui;
}
