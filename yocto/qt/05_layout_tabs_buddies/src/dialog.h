#ifndef _DIALOG_H_
#define _DIALOG_H_

#include <QDialog>

namespace Ui {
    class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:
    void on_pushButton_2_clicked();

private:
    Ui::Dialog *ui;
};

#endif  // _DIALOG_H_
