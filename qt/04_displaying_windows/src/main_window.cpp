#include "main_window.h"
#include "ui_main_window.h"
#include "my_dialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mDialog(NULL)
{
    ui->setupUi(this);

    setCentralWidget(ui->plainTextEdit);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_Window_triggered()
{
    if (NULL == mDialog) {
        mDialog = new MyDialog(this);
    }
    mDialog->show();

    // MyDialog mDialog;
    // mDialog.setModel(true);
    // mDialog.exec();
}
