#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGui>
#include <QStringRef>
#include <QDebug>
#include <QObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QString>
#include "parser.h"
#include <QTextCodec>

#define HOST_URL "https://www.google.com/calendar/htmlembed?src=o4tbebd20aj4u90j1n7th32qpg@group.calendar.google.com&amp;ctz=Europe/Moscow&amp;gsessionid=OK"
//#define HOST_URL "file:///D:/coding/test/parse2/1.html"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //setWindowFlags( Qt::Desktop | Qt::FramelessWindowHint);
    ui->setupUi(this);
    connectToHost();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connectToHost()
{
    manager=new QNetworkAccessManager;
    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(onFinished(QNetworkReply*)));

    manager->get(QNetworkRequest(QUrl(HOST_URL)));
}

void MainWindow::onFinished(QNetworkReply *reply)
{
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForTr(codec);

    QByteArray html=reply->readAll();
    QString htmlSourse=codec->toUnicode(html);

    Parser MyParser(&htmlSourse);
    QString res=MyParser.parse();
    htmlSourse.clear();
    ui->textBrowser->setHtml(res);
}

