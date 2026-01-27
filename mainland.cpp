#include "mainland.h"
#include <QGroupBox>
#include <QScrollArea>

Mainland::Mainland(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Mainland)
    , mainland_code_data{"Europe",
                         "EU",
                         "Africa",
                         "AF",
                         "Antarctica",
                         "AN",
                         "Asia",
                         "AS",
                         "North_america",
                         "NA",
                         "Oceania",
                         "OC",
                         "South_america",
                         "SA",
                         "Unknown_or_unspecified",
                         "ZZ"}
{
    ui->setupUi(this);

    gbox = new QGridLayout;
    //gbox->columnMinimumWidth(100);
    //gbox->rowMinimumHeight(100);
    //gbox->setHorizontalSpacing(100);
    //gbox->setVerticalSpacing(100);
    //gbox->setColumnMinimumWidth(100, 100);
    //gbox->setRowMinimumHeight(100, 100);

    for (int i = 0, row = 0, col = 0, value = 0, key = 1; key < mainland_code_data.size();
         ++i, value += 2, key += 2) {
        QCheckBox *checkbox = new QCheckBox(mainland_code_data[value]);
        checkbox->setAccessibleName(mainland_code_data[value]);

        gbox->addWidget(checkbox, row, col++);

        if (col != 0 && col % 6 == 0) {
            row++;
            col = 0;
        }
    }

    //ui->groupBox->setLayout(gbox);

    QGroupBox *groupBox = new QGroupBox;
    groupBox->setFixedSize(400, 400);
    groupBox->setLayout(gbox);

    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setWidgetResizable(true);
    scrollArea->setFixedSize(400, 200);
    //scrollArea->setFont()

    //scrollArea->setLayout(gbox);
    //scrollArea->setWidget(imageLabel);
    scrollArea->setWidget(groupBox);
}

Mainland::~Mainland()
{
    delete ui;
}

QVector<QString> Mainland::getE() const
{
    return v;
}

void Mainland::on_buttonBox_rejected()
{
    close();
}

void Mainland::on_buttonBox_accepted()
{
    for (int i = 0; i < gbox->count(); ++i) {
        QLayoutItem *item = gbox->itemAt(i);

        if (item == nullptr || item->widget() == nullptr)
            continue;

        QCheckBox *cb = qobject_cast<QCheckBox *>(item->widget());
        if (cb->isChecked()) {
            v.emplaceBack(cb->accessibleName());
        }
    }
    close();
    emit fill_lineedit3();
}
