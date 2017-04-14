#ifndef FILEDIALOG_H
#define FILEDIALOG_H

#include <QDialog>
#include <QFileDialog>

namespace Ui {
class FileDialog;
}

class FileDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FileDialog(QWidget *parent = 0);
    ~FileDialog();

private slots:
    void on_pushButtonFile_clicked();

signals:
    void FileOpenSend(QString filename);


private:
    Ui::FileDialog *ui;
};

#endif // FILEDIALOG_H
