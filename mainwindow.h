#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QSerialPort"
#include "QSerialPortInfo"
#include "QMessageBox"
#include <QDebug>
#include "QTimer"
#include "QIcon"


namespace Ui {
class MainWindow;
}
struct dataRec
{
    char hard[6];
    uint8_t stateOilPump;
    uint8_t WaterPump;
    uint8_t PowderValue;
    uint8_t Engine;
    uint16_t clc;
};
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    //私有变量
    bool serialIsOpen;
    uint run_time_count;
    QString run_time;
    //私有对象
    QTimer *tim;
    QSerialPort serial;
    QIcon iconSerialOn;
    QIcon iconSerialOff;
    QIcon iconSetPWM;
    QIcon iconSetValve;
    QIcon iconHandOn;
    //私有函数
    bool eventFilter(QObject* watched, QEvent* event);
    uint16_t crc16Calc(uint8_t *data, uint8_t len);
    uint8_t crc8Calc(uint8_t *data, uint8_t len);
    void serialSendData(uint8_t deviceId,uint8_t value1,uint8_t value2);
private slots:
    void on_pushButtonSerial_clicked(bool checked);
    void on_pushButtonSetPWM_clicked();
    void on_pushButtonSetValve_clicked();
    void on_pushButtonHandOn_clicked();
    void runtime_acc();
//    void slotrevserialmsg();
};

#endif // MAINWINDOW_H
