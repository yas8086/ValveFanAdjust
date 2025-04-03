#include "mainwindow.h"
#include "ui_mainwindow.h"

static uint8_t timeEngineValue = 0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    setWindowIcon(QIcon(":/Logo.ico"));
    setWindowTitle("手动控制燃料电池风扇电磁阀（测试用）");
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
    //电磁阀
    ValveStatusRadioGroup = new QButtonGroup();
    ValveStatusRadioGroup->addButton(ui->radioButtonValveClose,0);
    ValveStatusRadioGroup->addButton(ui->radioButtonValveOpen,1);

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
void MainWindow::serialSendData(uint8_t deviceId,uint8_t value1,uint8_t value2,uint8_t value3,uint8_t value4)
{
    QVector<uint8_t> dataSend;
    uint16_t crc16Value;
    dataSend.append(0x0C);
    dataSend.append(0x02);
    dataSend.append(deviceId);
    dataSend.append(value1);
    dataSend.append(value2);
    dataSend.append(value3);
    dataSend.append(value4);
    crc16Value = crc16Calc(dataSend.data(),7);
    dataSend.append(crc16Value >> 8);
    dataSend.append(crc16Value & 0XFF);

    QByteArray dataSendByteArray(reinterpret_cast<const char*>(dataSend.data()), static_cast<int>(dataSend.size()));
    serial.write(dataSendByteArray);
    dataSendByteArray.clear();
    dataSend.clear();
}
//串口接收数据
//地址码 功能码
void MainWindow::slotrevserialmsg()
{
    QByteArray msg;
    Rev_data data;
    Real_Data data1;
    uint8_t deviceId = 0, deviceValue = 0;
    msg = serial.readAll();
    while (msg.size()>=sizeof(Rev_data))
    {
        if(msg.data()[0]==0x0E)
        {
            //参数通信帧
            if(msg.data()[1]==0x01)
            {
                uint16_t crc=crc16Calc((uint8_t*)msg.data(),12);
                if((char(crc>>8)==msg[msg.size()-2])&&(char(crc&0xff)==msg[msg.size()-1]))//有符号和无符号比较一定要注意
                {
                    memcpy(&data,msg.data(),sizeof (Rev_data));
                    Reslove_Data(data,data1);
                    Refresh(data1);
                    msg.remove(0,sizeof (Rev_data));
                }
            }
            else{
                msg.remove(0,1);
            }
            //应答帧
//            if(msg.data()[1]==0x01)
//            {
//                uint16_t crc=crc16Calc((uint8_t*)msg.data(),11);
//                if((char(crc>>8)==msg[msg.size()-2])&&(char(crc&0xff)==msg[msg.size()-1]))//有符号和无符号比较一定要注意
//                {
//                    memcpy(&data,msg.data(),sizeof (Rev_data));
//                    Reslove_Data(data,data1);
//                    Refresh(data1);
//                    msg.remove(0,sizeof (Rev_data));
//                }
//            }

        }
        msg.remove(0,1);
    }
}
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
        serialSendData(1,0x00,0x00,0x00,uint8_t(ui->spinBoxPWM->value()));
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
        uint8_t value1 = (uint16_t(ui->spinBoxValveIntervals->value()*1000)) >> 8;
        uint8_t value2 = (uint16_t(ui->spinBoxValveIntervals->value()*1000)) & 0xff;
        uint8_t value3 = (uint16_t(ui->doubleSpinBoxValveTime->value()*1000)) >> 8;
        uint8_t value4 = (uint16_t(ui->doubleSpinBoxValveTime->value()*1000)) & 0xff;
        serialSendData(2,value1,value2,value3,value4);
    }else {
        QMessageBox::information(nullptr,"提示","电磁阀设定失败，串口未打开");
    }

}
//手动排气按钮设置 deviceId:3
void MainWindow::on_pushButtonHandOn_clicked()
{
    if(serialIsOpen==true){
        serialSendData(3,0x00,0x00,0x00,0x01);    }
    else {
        QMessageBox::information(nullptr,"提示","手动排气失败，串口未打开");
    }
}

void MainWindow::Refresh(Real_Data data)
{
    ui->lineEditT1->setText(QString::number(data.temperature,'f',2));
    ui->lineEditT2->setText(QString::number(data.shell_temperature,'f',2));
//    ui->bat_i->setText(QString::number(data.LI_I,'f',2));
    ValveStatusRadioGroup->button(data.Exhaust_status)->setChecked(true);
}

void MainWindow::Reslove_Data(Rev_data data,Real_Data &data1 )
{
    #pragma pack(1)//设定为1字节对齐
    union Swap
    {
        char a[2];
        unsigned short b;
    };
    #pragma pack(0)//设定为1字节对齐
    Swap swap;


    swap.a[0]=((char *)(&data.temperature))[1];
    swap.a[1]=((char *)(&data.temperature))[0];
    data1.temperature=swap.b/100.00-40;

    swap.a[0]=((char *)(&data.shell_temperature))[1];
    swap.a[1]=((char *)(&data.shell_temperature))[0];
    data1.shell_temperature=swap.b/100.00;

    swap.a[0]=((char *)(&data.environment_temperature))[1];
    swap.a[1]=((char *)(&data.environment_temperature))[0];
    data1.environment_temperature=swap.b;

    swap.a[0]=((char *)(&data.Exhaust_status))[1];
    swap.a[1]=((char *)(&data.Exhaust_status))[0];
    data1.Exhaust_status=swap.b;
//    qDebug()<<"swap传入数据后为："<<swap.a[0]<<swap.a[1]<<swap.b<<endl;
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
