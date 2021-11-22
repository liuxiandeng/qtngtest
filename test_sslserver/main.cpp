#include <QCoreApplication>
#include <server/server.h>
#include <sslhelper.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    qtng::PrivateKey privatekey;
    //NSNetwork::SSLHelper::createPrivateKey("./privatekey/server_private.key", privatekey, qtng::PrivateKey::Rsa, 2048, qtng::Ssl::Pem, "racobit123456");
    //NSNetwork::SSLHelper::createCertificate("./certificate/server.cert", qtng::PublicKey.load(privatekey.savePublic()), privatekey, "SSLSERVER", "CN", "RACOBIT");

    QFile file("./privatekey/server_private.key");
    if(!file.open(QFile::ReadOnly))
        return -1;

    privatekey = qtng::PrivateKey::load(file.readAll(), qtng::Ssl::Pem, "racobit123456");
    file.close();

    qtng::SslConfiguration sslConfig;
    sslConfig.setLocalCertificate("./certificate/server.cert");
    sslConfig.setPrivateKey(privatekey);

    NSNetwork::Server server(8001, sslConfig);
    server.start();

    return qtng::startQtLoop();
    //return a.exec();
}
