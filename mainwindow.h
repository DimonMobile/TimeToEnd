#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QContextMenuEvent>
#include <QMouseEvent>
#include <QCloseEvent>
#include <QMenu>
#include <QTimer>
#include "settingsdialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QMenu * m_contextMenu;
    QAction * m_openSettingsAction;
    QTimer * m_oneSecTimer;
    QTimer * m_progressBarHideTimer;
    int m_uptime;
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void onOpenSettingsActionTriggered(bool checked);
    void onOneSecTimerTimeout();
    void onProgressBarHideTimerTimeout();
protected:
    virtual void contextMenuEvent(QContextMenuEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void closeEvent(QCloseEvent *event) override;
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
