#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork/QNetworkReply>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void connectToHost();
public slots:
    void onFinished(QNetworkReply* reply);
private:
    Ui::MainWindow *ui;
    QNetworkAccessManager *manager;
};

#endif // MAINWINDOW_H
