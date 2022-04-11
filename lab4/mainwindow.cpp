#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    level = 0;
    connect(ui->next, &QPushButton::clicked, ui->openGL_main, &glScene::levelUp);
    connect(ui->previuos, &QPushButton::clicked, ui->openGL_main, &glScene::levelDown);
}

MainWindow::~MainWindow()
{
    delete ui;
}
