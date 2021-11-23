#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>


using namespace qtng;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , group(new CoroutineGroup())
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
    PrivateKey privatekey;
    QFile file1("./privatekey/client_private.key");
    if(!file1.open(QFile::ReadOnly))
        return -1;

    privatekey = PrivateKey::load(file1.readAll(), Ssl::Pem, "racobit123456");
    file1.close();
    sslConfig.setLocalCertificate("./certificate/client.cert");
    sslConfig.setPrivateKey(privatekey);

    return 0;
}


void MainWindow::on_pushButton_clicked()
{
    group->spawnWithName("recv", [this] {
        QSharedPointer<SslSocket> conn(SslSocket::createConnection("news.163.com", 443, sslConfig));
        if (!conn) {
            qDebug() << "can not connect to remote host.";
            return;
        }
        conn->sendall("GET /\r\n\r\n");
        while (true) {
            const QByteArray &buf = conn->recv(1);
            if (buf.isEmpty()) {
                return;
            }
            Coroutine::sleep(0.1);
            qDebug() << buf;
        }
    });
}

void MainWindow::on_pushButton_2_clicked()
{
    group->killall();
}
