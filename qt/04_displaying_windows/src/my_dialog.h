#ifndef _MY_DIALOG_H_
#define _MY_DIALOG_H_

#include <QDialog>

namespace Ui {
    class MyDialog;
}

class MyDialog : public QDialog
{
    Q_OBJECT

public:
        explicit MyDialog(QWidget *parent = 0);
        ~MyDialog();
private:
        Ui::MyDialog *ui;
};

#endif  // _MY_DIALOG_H_
