#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
    Settings* vSettings = Settings::Instance();
    Settings::Instance()->load();
    ui->checkBox->setChecked(vSettings->autoInit());
    ui->timeEdit->setTime(vSettings->startTime());
    ui->spinBox->setValue(vSettings->lengthTime());

    ui->spinBox_2->setValue(vSettings->salary());
    ui->doubleSpinBox->setValue(vSettings->tax());
    ui->spinBox_3->setValue(vSettings->monthTime());

    ui->tableView->setModel(Settings::Instance()->colorTableModel());
}

void SettingsDialog::write()
{
    Settings* vSettings = Settings::Instance();
    vSettings->setAutoInit(ui->checkBox->isChecked());
    vSettings->setStartTime(ui->timeEdit->time());
    vSettings->setLengthTime(ui->spinBox->value());

    vSettings->setSalary(ui->spinBox_2->value());
    vSettings->setTax(ui->doubleSpinBox->value());
    vSettings->setMonthTime(ui->spinBox_3->value());
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::on_pushButton_clicked()
{
    QApplication::exit(EXIT_SUCCESS);
}

void SettingsDialog::on_pushButton_2_clicked()
{
    Settings::Instance()->colorTableModel()->resetData();
}
