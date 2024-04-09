#ifndef _MAIN_WINDOW_H_
#define _MAIN_WINDOW_H_

#include <QMainWindow>
#include "my_dialog.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();

private slots:
        void on_actionNew_Window_triggered();

private:
        Ui::MainWindow *ui;
        MyDialog *mDialog;
};

#endif  // _MAIN_WINDOW_H_
