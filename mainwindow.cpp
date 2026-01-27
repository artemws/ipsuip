#include "mainwindow.h"
#include <QDir>
#include <QFileDialog>
#include <QFileSystemModel>
#include <QTreeView>
#include "functions.h"
#include <iostream>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow())
{
    ui->setupUi(this);

    f = new Countries();
    f2 = new Mainland();

    ui->lineEdit->setText(QDir::homePath() + "/Downloads");

    connect(f, &Countries::fill_lineedit2, this, &MainWindow::fill_lineEdit_2);
    connect(f2, &Mainland::fill_lineedit3, this, &MainWindow::fill_lineEdit_3);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    f->show();

}

void MainWindow::fill_lineEdit_2()
{
    country = f->getE();

    qDebug() << "v.size():" << country.size();
    QString s;
    for (const auto& i : country)
        s.append(i).append(" ");

    ui->lineEdit_2->setText(s);
}

void MainWindow::fill_lineEdit_3()
{
    mainland = f2->getE();

    qDebug() << "v.size():" << mainland.size();
    QString s;
    for (const auto& i : mainland)
        s.append(i).append(" ");

    ui->lineEdit_3->setText(s);
}

void MainWindow::on_pushButton_3_clicked()
{
    f2->show();
}

void MainWindow::on_toolButton_clicked()
{
    ui->lineEdit->setText(QFileDialog::getExistingDirectory(this,
                                                            tr("Open Directory"),
                                                            QDir::homePath() + "/Downloads",
                                                            QFileDialog::ShowDirsOnly
                                                                | QFileDialog::DontResolveSymlinks));
}

void MainWindow::on_pushButton_clicked()
{
    std::map<std::string, std::string> cc = ipsuip::map_code_revers(ipsuip::country_code_data);
    std::map<std::string, std::string> mc = ipsuip::map_code_revers(ipsuip::mainland_code_data);

    size_t sum = 100 / (country.size() + mainland.size());

    for (const auto& i : country) {
        std::cout << i.toStdString() << std::endl;
        std::cout << cc[i.toStdString()] << std::endl;
    }
    for (const auto& i : mainland) {
        std::cout << i.toStdString() << std::endl;
        std::cout << mc[i.toStdString()] << std::endl;
    }

    if (!country.empty())
        for (const auto& i : country)
            ipsuip::run_init(cc[i.toStdString()],
                             ui->lineEdit->text().toStdString(),
                             ipsuip::map_code(ipsuip::country_code_data),
                             ipsuip::TYPEPARSING::COUNTRY);

    if (!mainland.empty())
        for (const auto& i : mainland)
            ipsuip::run_init(mc[i.toStdString()],
                             ui->lineEdit->text().toStdString(),
                             ipsuip::map_code(ipsuip::mainland_code_data),
                             ipsuip::TYPEPARSING::CONTINENT);
}
