/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDial>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QGroupBox *GroupBoxSeries;
    QGridLayout *gridLayout_4;
    QLabel *label_26;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_3;
    QComboBox *comboBoxSerial;
    QPushButton *pushButtonSerial;
    QSpacerItem *horizontalSpacer_3;
    QLineEdit *timeCount;
    QGroupBox *gridGroupBox;
    QGridLayout *gridLayout_9;
    QGroupBox *GroupBoxFan2;
    QGridLayout *gridLayout_13;
    QHBoxLayout *horizontalLayout_14;
    QLabel *label_23;
    QSpinBox *spinBoxPWM;
    QDial *dialPWM;
    QPushButton *pushButtonSetPWM;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_5;
    QLineEdit *lineEditT1;
    QLabel *label_6;
    QLineEdit *lineEditT2;
    QGroupBox *gridGroupBox1;
    QGridLayout *gridLayout_2;
    QLabel *label_4;
    QDoubleSpinBox *doubleSpinBoxValveTime;
    QLabel *label_2;
    QSpinBox *spinBoxValveIntervals;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QRadioButton *radioButtonValveOpen;
    QRadioButton *radioButtonValveClose;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButtonHandOn;
    QPushButton *pushButtonSetValve;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(407, 481);
        QIcon icon;
        icon.addFile(QStringLiteral(":/img/Logo.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        GroupBoxSeries = new QGroupBox(centralWidget);
        GroupBoxSeries->setObjectName(QStringLiteral("GroupBoxSeries"));
        GroupBoxSeries->setFlat(false);
        gridLayout_4 = new QGridLayout(GroupBoxSeries);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        label_26 = new QLabel(GroupBoxSeries);
        label_26->setObjectName(QStringLiteral("label_26"));

        gridLayout_4->addWidget(label_26, 0, 2, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_3 = new QLabel(GroupBoxSeries);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_4->addWidget(label_3);

        comboBoxSerial = new QComboBox(GroupBoxSeries);
        comboBoxSerial->setObjectName(QStringLiteral("comboBoxSerial"));

        horizontalLayout_4->addWidget(comboBoxSerial);

        pushButtonSerial = new QPushButton(GroupBoxSeries);
        pushButtonSerial->setObjectName(QStringLiteral("pushButtonSerial"));
        pushButtonSerial->setMinimumSize(QSize(52, 17));
        pushButtonSerial->setMaximumSize(QSize(52, 17));
        pushButtonSerial->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"border-image: url(:/img/btncheckoff2.png);\n"
"}\n"
"QPushButton::checked\n"
"{\n"
"border-image: url(:/img/btncheckon2.png);\n"
"}\n"
"QPushButton::unchecked\n"
"{\n"
"border-image: url(:/img/btncheckoff2.png);\n"
"}"));
        pushButtonSerial->setIconSize(QSize(87, 28));

        horizontalLayout_4->addWidget(pushButtonSerial);


        gridLayout_4->addLayout(horizontalLayout_4, 0, 0, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_3, 0, 1, 1, 1);

        timeCount = new QLineEdit(GroupBoxSeries);
        timeCount->setObjectName(QStringLiteral("timeCount"));
        timeCount->setMinimumSize(QSize(120, 20));

        gridLayout_4->addWidget(timeCount, 0, 3, 1, 1);


        gridLayout->addWidget(GroupBoxSeries, 2, 0, 1, 2);

        gridGroupBox = new QGroupBox(centralWidget);
        gridGroupBox->setObjectName(QStringLiteral("gridGroupBox"));
        gridGroupBox->setFlat(false);
        gridLayout_9 = new QGridLayout(gridGroupBox);
        gridLayout_9->setSpacing(6);
        gridLayout_9->setContentsMargins(11, 11, 11, 11);
        gridLayout_9->setObjectName(QStringLiteral("gridLayout_9"));
        GroupBoxFan2 = new QGroupBox(gridGroupBox);
        GroupBoxFan2->setObjectName(QStringLiteral("GroupBoxFan2"));
        GroupBoxFan2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        GroupBoxFan2->setFlat(false);
        gridLayout_13 = new QGridLayout(GroupBoxFan2);
        gridLayout_13->setSpacing(6);
        gridLayout_13->setContentsMargins(11, 11, 11, 11);
        gridLayout_13->setObjectName(QStringLiteral("gridLayout_13"));
        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setSpacing(6);
        horizontalLayout_14->setObjectName(QStringLiteral("horizontalLayout_14"));
        label_23 = new QLabel(GroupBoxFan2);
        label_23->setObjectName(QStringLiteral("label_23"));

        horizontalLayout_14->addWidget(label_23);

        spinBoxPWM = new QSpinBox(GroupBoxFan2);
        spinBoxPWM->setObjectName(QStringLiteral("spinBoxPWM"));
        spinBoxPWM->setValue(13);

        horizontalLayout_14->addWidget(spinBoxPWM);

        dialPWM = new QDial(GroupBoxFan2);
        dialPWM->setObjectName(QStringLiteral("dialPWM"));
        dialPWM->setMinimumSize(QSize(100, 100));
        dialPWM->setFocusPolicy(Qt::ClickFocus);
        dialPWM->setContextMenuPolicy(Qt::CustomContextMenu);
        dialPWM->setOrientation(Qt::Horizontal);

        horizontalLayout_14->addWidget(dialPWM);


        gridLayout_13->addLayout(horizontalLayout_14, 5, 0, 1, 1);

        pushButtonSetPWM = new QPushButton(GroupBoxFan2);
        pushButtonSetPWM->setObjectName(QStringLiteral("pushButtonSetPWM"));

        gridLayout_13->addWidget(pushButtonSetPWM, 6, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_5 = new QLabel(GroupBoxFan2);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_3->addWidget(label_5);

        lineEditT1 = new QLineEdit(GroupBoxFan2);
        lineEditT1->setObjectName(QStringLiteral("lineEditT1"));

        horizontalLayout_3->addWidget(lineEditT1);

        label_6 = new QLabel(GroupBoxFan2);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout_3->addWidget(label_6);

        lineEditT2 = new QLineEdit(GroupBoxFan2);
        lineEditT2->setObjectName(QStringLiteral("lineEditT2"));

        horizontalLayout_3->addWidget(lineEditT2);


        gridLayout_13->addLayout(horizontalLayout_3, 0, 0, 1, 1);


        gridLayout_9->addWidget(GroupBoxFan2, 0, 0, 1, 1);

        gridGroupBox1 = new QGroupBox(gridGroupBox);
        gridGroupBox1->setObjectName(QStringLiteral("gridGroupBox1"));
        gridGroupBox1->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        gridGroupBox1->setFlat(false);
        gridLayout_2 = new QGridLayout(gridGroupBox1);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        label_4 = new QLabel(gridGroupBox1);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout_2->addWidget(label_4, 6, 0, 1, 1);

        doubleSpinBoxValveTime = new QDoubleSpinBox(gridGroupBox1);
        doubleSpinBoxValveTime->setObjectName(QStringLiteral("doubleSpinBoxValveTime"));
        doubleSpinBoxValveTime->setMaximum(3);
        doubleSpinBoxValveTime->setSingleStep(0.1);
        doubleSpinBoxValveTime->setValue(0.4);

        gridLayout_2->addWidget(doubleSpinBoxValveTime, 6, 1, 1, 2);

        label_2 = new QLabel(gridGroupBox1);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout_2->addWidget(label_2, 5, 0, 1, 1);

        spinBoxValveIntervals = new QSpinBox(gridGroupBox1);
        spinBoxValveIntervals->setObjectName(QStringLiteral("spinBoxValveIntervals"));
        spinBoxValveIntervals->setMinimum(1);
        spinBoxValveIntervals->setMaximum(60);
        spinBoxValveIntervals->setValue(15);

        gridLayout_2->addWidget(spinBoxValveIntervals, 5, 1, 1, 2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, 3, -1, 3);
        label = new QLabel(gridGroupBox1);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        radioButtonValveOpen = new QRadioButton(gridGroupBox1);
        radioButtonValveOpen->setObjectName(QStringLiteral("radioButtonValveOpen"));

        horizontalLayout->addWidget(radioButtonValveOpen);

        radioButtonValveClose = new QRadioButton(gridGroupBox1);
        radioButtonValveClose->setObjectName(QStringLiteral("radioButtonValveClose"));

        horizontalLayout->addWidget(radioButtonValveClose);


        gridLayout_2->addLayout(horizontalLayout, 1, 0, 1, 3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(-1, 5, -1, 5);
        pushButtonHandOn = new QPushButton(gridGroupBox1);
        pushButtonHandOn->setObjectName(QStringLiteral("pushButtonHandOn"));
        pushButtonHandOn->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    font-size: 14px;\n"
"}\n"
"QPushButton:hover{\n"
"	color: red;\n"
"}\n"
"//\346\214\211\351\222\256\347\246\201\346\255\242\346\227\266\347\232\204\346\240\267\345\274\217\n"
"QPushButton:disabled{\n"
"	color: blue;\n"
"	border-color: brown;\n"
"    background-color: aqua;\n"
"}"));

        horizontalLayout_2->addWidget(pushButtonHandOn);


        gridLayout_2->addLayout(horizontalLayout_2, 0, 0, 1, 3);

        pushButtonSetValve = new QPushButton(gridGroupBox1);
        pushButtonSetValve->setObjectName(QStringLiteral("pushButtonSetValve"));

        gridLayout_2->addWidget(pushButtonSetValve, 7, 0, 1, 3);


        gridLayout_9->addWidget(gridGroupBox1, 1, 0, 1, 1);


        gridLayout->addWidget(gridGroupBox, 3, 0, 1, 2);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        GroupBoxSeries->setTitle(QApplication::translate("MainWindow", "\344\270\262\345\217\243\350\256\276\347\275\256", Q_NULLPTR));
        label_26->setText(QApplication::translate("MainWindow", "\350\277\220\350\241\214\346\227\266\351\227\264", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "\351\200\211\346\213\251\344\270\262\345\217\243", Q_NULLPTR));
        pushButtonSerial->setText(QString());
        gridGroupBox->setTitle(QApplication::translate("MainWindow", "\346\211\213\345\212\250\346\216\247\345\210\266", Q_NULLPTR));
        GroupBoxFan2->setTitle(QApplication::translate("MainWindow", "\351\243\216\346\211\207\346\216\247\345\210\266", Q_NULLPTR));
        label_23->setText(QApplication::translate("MainWindow", "\351\243\216\346\211\207PWM", Q_NULLPTR));
        pushButtonSetPWM->setText(QApplication::translate("MainWindow", "\350\256\276\345\256\232", Q_NULLPTR));
        label_5->setText(QApplication::translate("MainWindow", "\346\270\251\345\272\2461\357\274\232", Q_NULLPTR));
        label_6->setText(QApplication::translate("MainWindow", "\346\270\251\345\272\2462\357\274\232", Q_NULLPTR));
        gridGroupBox1->setTitle(QApplication::translate("MainWindow", "\347\224\265\347\243\201\351\230\200\346\216\247\345\210\266", Q_NULLPTR));
        label_4->setText(QApplication::translate("MainWindow", "\346\216\222\346\260\224\346\227\266\351\227\264\357\274\210S\357\274\211", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "\346\216\222\346\260\224\351\227\264\351\232\224\357\274\210S\357\274\211", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "\347\224\265\347\243\201\351\230\200\345\275\223\345\211\215\347\212\266\346\200\201", Q_NULLPTR));
        radioButtonValveOpen->setText(QApplication::translate("MainWindow", "\345\274\200", Q_NULLPTR));
        radioButtonValveClose->setText(QApplication::translate("MainWindow", "\345\205\263", Q_NULLPTR));
        pushButtonHandOn->setText(QApplication::translate("MainWindow", "\347\202\271\345\207\273\346\211\213\345\212\250\345\274\200\345\220\257\344\270\200\346\254\241\347\224\265\347\243\201\351\230\200\357\274\214\346\216\222\346\260\224\346\227\266\351\227\2641S", Q_NULLPTR));
        pushButtonSetValve->setText(QApplication::translate("MainWindow", "\350\256\276\345\256\232", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
