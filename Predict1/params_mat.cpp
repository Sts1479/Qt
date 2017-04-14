#include "params_mat.h"
#include "ui_params_mat.h"

Params_mat::Params_mat(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Params_mat)
{
    ui->setupUi(this);
}

Params_mat::~Params_mat()
{
    delete ui;
}
