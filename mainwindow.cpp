#include "mainwindow.h"
#include "countries.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    for (const auto& i : ipsuip::codes_countries)
        ui->comboBox->addItem(QString::fromStdString(i));
}

MainWindow::~MainWindow()
{
    delete ui;
}
