#ifndef PARAMS_MAT_H
#define PARAMS_MAT_H

#include <QDialog>

namespace Ui {
class Params_mat;
}

class Params_mat : public QDialog
{
    Q_OBJECT

public:
    explicit Params_mat(QWidget *parent = 0);
    ~Params_mat();

private:
    Ui::Params_mat *ui;
};

#endif // PARAMS_MAT_H
