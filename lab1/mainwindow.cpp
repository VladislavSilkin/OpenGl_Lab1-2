#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->comboBox_lab_1, &QComboBox::activated, ui->openGL_main, &glScene::slot);
}

MainWindow::~MainWindow()
{
    delete ui;
}

