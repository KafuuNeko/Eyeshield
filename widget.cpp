#include "widget.h"
#include "ui_widget.h"

#include <QIcon>
#include <QCloseEvent>
#include <QSettings>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //显示底部菜单
    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(QIcon(":/images/eye.png"));
    trayIcon->setToolTip("护眼提醒程序");
    createMenu();
    trayIcon->setContextMenu(trayMenu);
    trayIcon->show();

    connect(trayIcon, &QSystemTrayIcon::activated, [=](QSystemTrayIcon::ActivationReason reason){ if(reason == QSystemTrayIcon::ActivationReason::DoubleClick) show(); });

    connect(ui->save, &QPushButton::clicked, [=](){ updateConfig(); hide(); });

    connect(ui->cancel, &QPushButton::clicked, [=](){ hide(); });

    timer = new QTimer(this);

    connect(timer, &QTimer::timeout, [=](){
        trayIcon->showMessage("护眼提醒", "请让你的眼睛放松一下吧~");
    });

    initConfig();

    timer->start();

    trayIcon->showMessage("护眼提醒程序启动", "护眼提醒程序已启动，双击托盘图标可打开设置");
}

Widget::~Widget()
{
    delete ui;
}

void Widget::closeEvent(QCloseEvent *event)
{
#ifdef Q_OS_OSX
    if (!event->spontaneous() || !isVisible()) {
        return;
    }
#endif
    if (trayIcon->isVisible()) {
        hide();
        event->ignore();
    }
}

void Widget::createMenu()
{
    trayMenu = new QMenu(this);

    QAction *action;

    action = new QAction("开启开机自启", trayMenu);
    trayMenu->addAction(action);
    connect(action, &QAction::triggered, [=](){ SetMyAppAutoRun(true); });

    action = new QAction("关闭开机自启", trayMenu);
    trayMenu->addAction(action);
    connect(action, &QAction::triggered, [=](){ SetMyAppAutoRun(false); });

    trayMenu->addSeparator();


    action = new QAction("退出", trayMenu);
    trayMenu->addAction(action);
    connect(action, &QAction::triggered, qApp, &QCoreApplication::quit);
}

void Widget::initConfig()
{
    QSettings config("config.ini", QSettings::IniFormat);
    interval = config.value("interval", QVariant(10)).toUInt();
    ui->intervalSet->setValue(interval);
    timer->setInterval(60000 * interval);
}

void Widget::updateConfig()
{
    interval = ui->intervalSet->getValue();

    QSettings config("config.ini", QSettings::IniFormat);
    config.setValue("interval", interval);
    timer->setInterval(60000 * interval);
}

void Widget::SetMyAppAutoRun(bool isstart)
{
    QString application_name = QApplication::applicationName();//获取应用名称
    QSettings *settings = new QSettings(AUTO_RUN, QSettings::NativeFormat);//创建QSetting, 需要添加QSetting头文件
    if(isstart)
    {
        QString application_path = QApplication::applicationFilePath();//找到应用的目录
        settings->setValue(application_name, application_path.replace("/", "\\"));//写入注册表
    }
    else
    {
        settings->remove(application_name);
    }
}
