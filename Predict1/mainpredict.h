#ifndef MAINPREDICT_H
#define MAINPREDICT_H

#include <QMainWindow>
#include "filedialog.h"
#include "dwritefile.h"
#include "qdebug.h"
#include "params_mat.h"

namespace Ui {
class MainPredict;
}

class MainPredict : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainPredict(QWidget *parent = 0);
    ~MainPredict();
    static int flag_computing;
    static QString OpenFileName;
private slots:
    void on_action_Write_triggered();
    void on_action_Open_triggered();
    void on_pushButton_clicked();

    void on_actionParams_triggered();

public slots:
    void FileOpenReceive(QString filename);
    void DWriteFileReceive(QString filename);

private:
    Ui::MainPredict *ui;
    FileDialog *FileDialog1;
    DWriteFile *DWriteFile1;
    Params_mat *Params_mat1;
};

#endif // MAINPREDICT_H
