#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , group(new qtng::CoroutineGroup())
{
    ui->setupUi(this);
    initSsl();
}

MainWindow::~MainWindow()
{
    delete group;
    delete ui;
}

int MainWindow::initSsl()
{
    qtng::PrivateKey privatekey;
    QFile file1("./privatekey/client_private.key");
    if(!file1.open(QFile::ReadOnly))
        return -1;

    privatekey = qtng::PrivateKey::load(file1.readAll(), qtng::Ssl::Pem, "racobit123456");
    file1.close();
    sslConfig.setLocalCertificate("./certificate/client.cert");
    sslConfig.setPrivateKey(privatekey);

    return 0;
}


void MainWindow::on_pushButton_clicked()
{
    group->spawnWithName("recv", [this] {
        QSharedPointer<qtng::SslSocket> conn(qtng::SslSocket::createConnection("192.168.10.34", 8001, sslConfig));
        if (!conn) {
            qDebug() << "can not connect to remote host.";
            return;
        }
        while (true) {
            const QByteArray &buf = conn->recv(1024 * 8);
            if (buf.isEmpty()) {
                return;
            }
            qDebug() << buf;
        }
    });
}

void MainWindow::on_pushButton_2_clicked()
{
    group->killall();
}
