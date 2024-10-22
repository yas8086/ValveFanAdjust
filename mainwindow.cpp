#include "mainwindow.h"
#include "ui_mainwindow.h"

static uint8_t timeEngineValue = 0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    setWindowTitle("手动控制风扇电磁阀");
    iconSetPWM.addFile(":/img/设定.png");
    iconSetValve.addFile(":/img/设定.png");
    iconHandOn.addFile(":/img/手动点击.png");
    ui->pushButtonHandOn->setIcon(iconHandOn);
    ui->pushButtonSetPWM->setIcon(iconSetPWM);
    ui->pushButtonSetValve->setIcon(iconSetValve);
    //串口相关
    serialIsOpen = false;
    foreach(const QSerialPortInfo &info,QSerialPortInfo::availablePorts())
    {
        ui->comboBoxSerial->addItem(info.portName());
    }
    ui->pushButtonSerial->setCheckable(true);
    ui->comboBoxSerial->installEventFilter(this);
    connect(&serial,SIGNAL(readyRead()),this,SLOT(slotrevserialmsg()));
    //PWM
    /* 设置页长（两个最大刻度的间距）*/
    ui->dialPWM->setPageStep(10);
    /* 设置刻度可见 */
    ui->dialPWM->setNotchesVisible(true);
    /* 设置两个凹槽之间的目标像素数 */
    ui->dialPWM->setNotchTarget(1.00);
    /* 设置dial值的范围 */
    ui->dialPWM->setRange(0,100);
    ui->spinBoxPWM->setRange(0,100);
    QObject::connect(ui->dialPWM,SIGNAL(valueChanged(int)),ui->spinBoxPWM,SLOT(setValue(int)));
    QObject::connect(ui->spinBoxPWM,SIGNAL(valueChanged(int)),ui->dialPWM,SLOT(setValue(int)));
    //定时器
    tim = new QTimer();
    tim->setInterval(1000);
    run_time_count = 0;
    connect(tim,SIGNAL(timeout()),this,SLOT(runtime_acc()));

}
//定时器槽函数
void MainWindow::runtime_acc()
{
    run_time_count += 1;
    //将秒数转化为时分秒格式
    uint H = run_time_count / (60*60);
    uint M = (run_time_count- (H * 60 * 60)) / 60;
    uint S = (run_time_count - (H * 60 * 60)) - M * 60;
    QString hour = QString::number(H);
    if (hour.length() == 1) hour = "0" + hour;
    QString min = QString::number(M);
    if (min.length() == 1) min = "0" + min;
    QString sec = QString::number(S);
    if (sec.length() == 1) sec = "0" + sec;
    run_time = hour + ":" + min + ":" + sec;

//    run_time = QDateTime::fromTime_t(run_time_count).toString("hh:mm:ss");
    ui->timeCount->setText(run_time);

}
//过滤器
bool MainWindow::eventFilter(QObject* watched, QEvent* event)
{
    if(watched==ui->comboBoxSerial&&event->type()==QEvent::MouseButtonPress)
    {
        ui->comboBoxSerial->clear();
        foreach(const QSerialPortInfo &info,QSerialPortInfo::availablePorts())
        {
            ui->comboBoxSerial->addItem(info.portName());
        }
    }
}
//串口发送数据
//deviceId PWM设定：1         电磁阀设定：2      手动开启电磁阀：3
void MainWindow::serialSendData(uint8_t deviceId,uint8_t value1,uint8_t value2)
{
    QVector<uint8_t> dataSend;
    uint16_t crc16Value;
    dataSend.append(0x0C);
    dataSend.append(0x02);
    dataSend.append(deviceId);
    dataSend.append(value1);
    dataSend.append(value2);
    crc16Value = crc16Calc(dataSend.data(),5);
    dataSend.append(crc16Value >> 8);
    dataSend.append(crc16Value & 0XFF);

    QByteArray dataSendByteArray(reinterpret_cast<const char*>(dataSend.data()), static_cast<int>(dataSend.size()));
    serial.write(dataSendByteArray);
    dataSendByteArray.clear();
    dataSend.clear();
}
//串口接收数据
//void MainWindow::slotrevserialmsg()
//{
//    QByteArray msg;
//    uint16_t deviceId = 0, deviceValue = 0;
//    msg = serial.readAll();
//    if(!msg.isEmpty())
//    {
//        if(msg.data()[0]==0x0C)
//        {
//            uint16_t crc=crc16Calc((uint8_t*)msg.data(),3);
//            if((char(crc>>8)==msg[msg.size()-2])&&(char(crc&0xff)==msg[msg.size()-1]))//有符号和无符号比较一定要注意
//            {
//                deviceId = msg[1];
//                deviceValue = msg[2];
//            }
//        }
//    }
//    //deviceId  失败：0  油泵：1  水泵：2  粉阀：3  发动机：4  复位：5
//    switch (deviceId) {
//    case 0:
//        switch (deviceValue){
//        case 1:
//            ui->pushButtonOilPump->setChecked(true);
//            break;
//        case 2:
//            ui->pushButtonWaterPump->setChecked(true);
//            break;
//        default:
//            break;
//        }
//        QMessageBox::information(nullptr,"提示","打开失败，请重试！");
//        break;
//    case 1:
//        if(deviceValue==1)
//        {
//            QMessageBox::information(nullptr,"提示","油泵打开成功");
//            ui->pushButtonOilPump->setChecked(true);
//            ui->pushButtonOilPump->setText("油泵已开启，点击关闭");
//        }
//        else {
//            ui->pushButtonOilPump->setText("打开");
//        }
//        break;
//    case 2:
//        if(deviceValue==1)
//        {
//            QMessageBox::information(nullptr,"提示","水泵打开成功");
//            ui->pushButtonWaterPump->setChecked(true);
//            ui->pushButtonWaterPump->setText("水泵已开启，点击关闭");
//        }
//        else {
//            ui->pushButtonWaterPump->setText("打开");
//        }
//        break;
//    case 3:
//        QMessageBox::information(nullptr,"提示","粉阀PWM设置成功");
//        break;
//    case 4:
//        QMessageBox::information(nullptr,"提示","发动机设置成功");
//        break;
//    case 5:
//        //油泵
//        ui->pushButtonOilPump->setChecked(false);
//        ui->pushButtonOilPump->setText("打开");
//        //水泵
//        ui->pushButtonWaterPump->setChecked(false);
//        ui->pushButtonWaterPump->setText("打开");
//        //粉阀
//        ui->spinBoxPowderValue->setValue(0);
//        //发动机
//        ui->spinBoxEngine->setValue(0);
//        QMessageBox::information(nullptr,"提示","复位成功");
//        break;
//    default:
//        break;
//    }
//    msg.clear();
//}
//串口打开按钮设置
void MainWindow::on_pushButtonSerial_clicked(bool checked)
{
    if(checked==true)
    {
        serial.setPortName(ui->comboBoxSerial->currentText());//设置串口号
        serial.setBaudRate(57600);//设置波特率
        serial.setDataBits(QSerialPort::Data8);//设置串口数据位8
        serial.setParity(QSerialPort::NoParity);//无校验位
        serial.setStopBits(QSerialPort::OneStop);//1位停止位
        serial.setFlowControl(QSerialPort::NoFlowControl);
        if(!serial.open(QIODevice::ReadWrite))
        {
            QMessageBox::critical(nullptr,"提示","串口打开失败");
            ui->pushButtonSerial->setChecked(false);
        }
        else {
            serialIsOpen = true;
            tim->start();
            QMessageBox::information(nullptr,"提示","串口打开成功");
//            ui->pushButtonSerial->setText("点击关闭");
        }
    }else {
        serial.close();
        tim->stop();
        run_time_count = 0;
        serialIsOpen = false;
//        ui->pushButtonSerial->setText("打开");
    }
}
//风扇设定按钮设置 deviceId:1
void MainWindow::on_pushButtonSetPWM_clicked()
{
    if(serialIsOpen==true){
        serialSendData(1,uint8_t(ui->spinBoxPWM->value()),0x00);
    }
    else {
        QMessageBox::information(nullptr,"提示","风扇PWM设定失败，串口未打开");
    }
}
//电磁阀设定按钮设置 deviceId:2
void MainWindow::on_pushButtonSetValve_clicked()
{
    if(serialIsOpen==true)
    {
        serialSendData(2,uint8_t(ui->spinBoxValveIntervals->value()),uint8_t(ui->doubleSpinBoxValveTime->value()*100));
    }else {
        QMessageBox::information(nullptr,"提示","电磁阀设定失败，串口未打开");
    }

}
//手动排气按钮设置 deviceId:3
void MainWindow::on_pushButtonHandOn_clicked()
{
    if(serialIsOpen==true){
        serialSendData(3,0x01,0x00);    }
    else {
        QMessageBox::information(nullptr,"提示","手动排气失败，串口未打开");
    }
}

//16位CRC校验
uint16_t MainWindow::crc16Calc(uint8_t *data, uint8_t len) {
    uint16_t crc_buf, crc16;
    crc16 = 0xFFFF;
    for(int i=0; i< len;i++){
        crc_buf = data[i] & 0x00FF;
        crc16 ^= crc_buf;
        for(int j = 0; j<8; j++){
            if(crc16 & 0x0001){
                crc16 >>=1;
                crc16 ^= 0xA001;
            }else{
                crc16 >>= 1;
            }
        }
    }
    return crc16;
}
//8位CRC校验
uint8_t MainWindow::crc8Calc(uint8_t *data, uint8_t len) {
    uint8_t crc8 = 0x00;
    for (uint8_t byte=0; byte<len;byte++) {
        crc8 ^= data[byte];
        for (int i = 0; i < 8; ++i) {
            if (crc8 & 0x80) {
                crc8 = uint8_t((crc8 << 1) ^ 0x31);
            } else {
                crc8 <<= 1;
            }
        }
    }
    return crc8;
}

MainWindow::~MainWindow()
{
    delete ui;
}
