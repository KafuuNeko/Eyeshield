#ifndef WIDGET_H
#define WIDGET_H

#define qApp QCoreApplication::instance()
#define AUTO_RUN "HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run"

#include <QMenu>
#include <QTimer>
#include <QWidget>
#include <QSystemTrayIcon>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    Ui::Widget *ui;
    QSystemTrayIcon *trayIcon;
    QMenu *trayMenu;
    uint32_t interval;
    QTimer *timer;

    void createMenu();
    void initConfig();
    void updateConfig();
    void SetMyAppAutoRun(bool isstart);

};
#endif // WIDGET_H
