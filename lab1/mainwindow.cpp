#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->comboBox_lab_1, &QComboBox::activated, ui->openGL_main, &glScene::slot);
    connect(ui->comboBox_transparency, &QComboBox::activated, ui->openGL_main, &glScene::alphaChooseSlot);
    connect(ui->horizontalSlider_transparency, &QSlider::valueChanged, ui->openGL_main, &glScene::alphaRefSlot);
    connect(ui->horizontalSlider_x, &QSlider::valueChanged, ui->openGL_main, &glScene::xSlot);
    connect(ui->horizontalSlider_y, &QSlider::valueChanged, ui->openGL_main, &glScene::ySlot);
    connect(ui->horizontalSlider_height, &QSlider::valueChanged, ui->openGL_main, &glScene::heightSlot);
    connect(ui->horizontalSlider_width, &QSlider::valueChanged, ui->openGL_main, &glScene::widthSlot);
    connect(ui->comboBox_mixing_1, &QComboBox::activated, ui->openGL_main, &glScene::sfactorSlot);
    connect(ui->comboBox_mixing_2, &QComboBox::activated, ui->openGL_main, &glScene::dfactorSlot);

}

MainWindow::~MainWindow()
{
    delete ui;
}

