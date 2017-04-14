#ifndef DWRITEFILE_H
#define DWRITEFILE_H

#include <QDialog>

namespace Ui {
class DWriteFile;
}

class DWriteFile : public QDialog
{
    Q_OBJECT

public:
    explicit DWriteFile(QWidget *parent = 0);
    ~DWriteFile();

signals:
  void DWriteFileSend(QString filename);

private slots:
  void on_pushButton_clicked();

private:
    Ui::DWriteFile *ui;
};

#endif // DWRITEFILE_H
