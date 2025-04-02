#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QSerialPort"
#include "QSerialPortInfo"
#include "QMessageBox"
#include <QDebug>
#include "QTimer"
#include "QIcon"
#include<QButtonGroup>


namespace Ui {
class MainWindow;
}

struct Rev_data
{
    char hard[4];
    unsigned short temperature;
    unsigned short shell_temperature;
    unsigned short environment_temperature;
    unsigned short Exhaust_status;
    unsigned short clc;
};
struct Real_Data
{
    double temperature;
    double shell_temperature;
    double environment_temperature;
    unsigned short Exhaust_status;
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
    QButtonGroup* ValveStatusRadioGroup;
    //私有函数
    bool eventFilter(QObject* watched, QEvent* event);
    uint16_t crc16Calc(uint8_t *data, uint8_t len);
    uint8_t crc8Calc(uint8_t *data, uint8_t len);
    void Refresh(Real_Data data);
    void Reslove_Data(Rev_data data, Real_Data &data1);
    void serialSendData(uint8_t deviceId,uint8_t value1,uint8_t value2,uint8_t value3,uint8_t value4);
private slots:
    void on_pushButtonSerial_clicked(bool checked);
    void on_pushButtonSetPWM_clicked();
    void on_pushButtonSetValve_clicked();
    void on_pushButtonHandOn_clicked();
    void runtime_acc();
    void slotrevserialmsg();
};

#endif // MAINWINDOW_H
