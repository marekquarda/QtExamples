#include "searchdialog.h"
#include "ui_searchdialog.h"
#include <QDebug>

SearchDialog::SearchDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SearchDialog)
{
    ui->setupUi(this);
    //ui->asRegularExpression->setChecked(true);
    connect(ui->asRegularExpression, &QCheckBox::toggled, this, &SearchDialog::updateUIState);
    connect(ui->caseSensitive, &QCheckBox::toggled, this, &SearchDialog::updateUIState);
    updateUIState();
}

SearchDialog::~SearchDialog()
{
    delete ui;
}

void SearchDialog::updateUIState()
{
    qDebug() << "UpdateUIState";
    ui->wholeWords->setEnabled(ui->asRegularExpression->isChecked() && ui->caseSensitive->isChecked());
}
