#pragma once

#include <QCheckBox>
#include <QGroupBox>
#include <QRadioButton>
#include <QWidget>
#include "qgridlayout.h"
#include "ui_countries.h"

namespace Ui {
    class Countries;
}

class Countries : public QWidget
{
    Q_OBJECT

public:
    explicit Countries(QWidget *parent = nullptr);
    ~Countries();
    QVector<QString> getE() const;

private slots:
    void on_buttonBox_rejected();

    void on_buttonBox_accepted();

signals:
    void fill_lineedit2();

private:
    Ui::Countries *ui;
    QGridLayout *gbox;
    QVector<QString> v;
    QVector<QString> country_code_data;
};
