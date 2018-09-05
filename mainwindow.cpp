#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QScreen>
#include <QtMath>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_uptime(0),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->progressBar->hide();

    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint | Qt::Tool);

    QScreen *screen = QApplication::primaryScreen();
    move(screen->geometry().width() - width(), screen->geometry().height() - height());

    m_oneSecTimer = new QTimer(this);
    connect(m_oneSecTimer, &QTimer::timeout, this, &MainWindow::onOneSecTimerTimeout);
    m_oneSecTimer->start(500);

    m_progressBarHideTimer = new QTimer(this);
    connect(m_progressBarHideTimer, &QTimer::timeout, this, &MainWindow::onProgressBarHideTimerTimeout);

    Settings::Instance()->load();
    m_openSettingsAction = new QAction("Settings", this);
    connect(m_openSettingsAction, &QAction::triggered, this, &MainWindow::onOpenSettingsActionTriggered);
    m_contextMenu = new QMenu(this);
    m_contextMenu->addAction(m_openSettingsAction);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onOpenSettingsActionTriggered(bool checked)
{
    Q_UNUSED(checked);
    QScopedPointer<SettingsDialog> dialog(new SettingsDialog(this));
    int modalResult =  dialog->exec();
    dialog->write();
    if (modalResult == QDialog::Accepted)
        Settings::Instance()->save();
    else
        Settings::Instance()->load();
}

char blinkChar(const char ch, int uptime)
{
    return (uptime % 2 == 0)?' ':ch;
}

void MainWindow::onOneSecTimerTimeout()
{
    Settings *vSettings = Settings::Instance();
    ++m_uptime;
    double fullTimeMSec = vSettings->lengthTime() * 3600 * 1000;
    QTime tim = vSettings->startTime().addMSecs(fullTimeMSec);
    double elapsedMSec = QTime::currentTime().msecsTo(tim);
    double completedMSec = fullTimeMSec - elapsedMSec;
    double percents{static_cast<double>(completedMSec)/fullTimeMSec*100.0};
    double moneyPerMSec = ( vSettings->salary()*(1-vSettings->tax()/100.0) ) / (vSettings->monthTime()*3600*1000 );
    double completedMoney = moneyPerMSec * completedMSec;
    double fullMoney = moneyPerMSec * fullTimeMSec;

    int srcPrc = qMin(static_cast<int>(percents), 100);
    QColor fColor = Settings::Instance()->colorTableModel()->colorAt(srcPrc);
    QColor sColor = Settings::Instance()->colorTableModel()->colorAt(qMin(static_cast<int>(percents+1), 100));

    double fx = (percents - srcPrc) / 1.0;
    double redOffset = ( sColor.red() - fColor.red() ) * fx;
    double greenOffset = ( sColor.green() - fColor.green()) * fx;
    double blueOffset = ( sColor.blue() - fColor.blue() ) * fx;
    ui->label->setStyleSheet(QString("Color: rgb(%1, %2, %3)").arg(fColor.red() + redOffset).arg(fColor.green() + greenOffset).arg(fColor.blue() + blueOffset));

    QString resultString;
    resultString = QString::number(percents, 'g', 4);
    resultString += "%\n" + QString::number(completedMoney, 'g', 4);
    resultString += "$/" + QString::number(fullMoney, 'g', 4) + "$\n";

    if (m_uptime % 30 <= 10)
        resultString += blinkChar('>', m_uptime) + QTime::currentTime().addMSecs(elapsedMSec).toString() + blinkChar('<', m_uptime);
    else
        resultString += "- " + QTime(0,0).addMSecs(elapsedMSec).toString(QString("hh") + blinkChar(':', m_uptime) + "mm" + blinkChar(':', m_uptime) + "ss");

    ui->label->setText(resultString);

    ui->progressBar->setValue(percents);
}

void MainWindow::onProgressBarHideTimerTimeout()
{
    m_progressBarHideTimer->stop();
    ui->progressBar->hide();
    ui->label->show();
}


void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
    m_contextMenu->exec(event->globalPos());
}


void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        ui->progressBar->show();
        ui->label->hide();
        if (m_progressBarHideTimer->isActive())
        {
            m_progressBarHideTimer->stop();
        }
        m_progressBarHideTimer->start(5000);
    }
}


void MainWindow::closeEvent(QCloseEvent *event)
{
    event->ignore();
}
