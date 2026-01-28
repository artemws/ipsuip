#pragma once

#include <QMainWindow>
#include "countries.h"
#include "mainland.h"
#include "ui_mainwindow.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void fill_lineEdit_2();
    void fill_lineEdit_3();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_toolButton_clicked();

    void on_pushButton_clicked();

private:
    Countries *f;
    Mainland *f2;
    QVector<QString> country;
    QVector<QString> mainland;
    Ui::MainWindow *ui;
};

