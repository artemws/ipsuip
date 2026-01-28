#pragma once

#include <QGridLayout>
#include <QWidget>
//#include "info.h"
#include "ui_mainland.h"

#include <QCheckBox>

namespace Ui {
    class Mainland;
}

class Mainland : public QWidget
{
    Q_OBJECT

public:
    explicit Mainland(QWidget *parent = nullptr);
    ~Mainland();
    QVector<QString> getE() const;

private slots:
    void on_buttonBox_rejected();

    void on_buttonBox_accepted();

signals:
    void fill_lineedit3();

private:
    Ui::Mainland *ui;
    QGridLayout *gbox;
    QVector<QString> v;
    QVector<QString> mainland_code_data;
};

