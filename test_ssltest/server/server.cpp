#include "server.h"

using namespace NSNetwork;
Q_DECLARE_METATYPE(qtng::Socket::SocketOption)

RequestHandler::RequestHandler()
    : _nBufferSize(1024 * 1024)
{

}

RequestHandler::~RequestHandler()
{

}

bool RequestHandler::setup()
{
    qDebug() << "RequestHandler::setup";
    return true;
}

void RequestHandler::handle()
{   
    qDebug() << "RequestHandler::handle";
    if(!server)
    {
        return;
    }

    qtng::SslServer<RequestHandler> *pSslServer = dynamic_cast<qtng::SslServer<RequestHandler> *>(server);
    if(!pSslServer)
    {
        return;
    }

    qtng::SslConfiguration sslConfig = pSslServer->sslConfiguration();
    QSharedPointer<qtng::SslSocket> pSslSocket = convertSocketLikeToSslSocket(request);
    if(!pSslSocket.isNull())
    {
        if(pSslSocket->localCertificate().digest(qtng::MessageDigest::Sha256) != sslConfig.localCertificate().digest(qtng::MessageDigest::Sha256))
        {
            qDebug() << "Certificate Error";
            return;
        }
        while(pSslSocket->isValid())
        {

            QByteArray data = pSslSocket->recv(_nBufferSize);
            if(data.isEmpty())
            {
                break;
            }
            qDebug() << sslConfig.privateKey().decrypt(data) << pSslSocket->sslErrors() << pSslSocket->errorString();
        }
    }

    qDebug() << "RequestHandler::handle exit";
}

void RequestHandler::finish()
{
    qDebug() << "RequestHandler::finish";
}

qint32 RequestHandler::bufferSize() const
{
    return _nBufferSize;
}

void RequestHandler::setBufferSize(const qint32& size)
{
    _nBufferSize = size;
}

Server::Server(const qtng::HostAddress& serverAddress, quint16 serverPort)
    : qtng::SslServer<RequestHandler>(serverAddress, serverPort)
{

}

Server::Server(const qtng::HostAddress& serverAddress, quint16 serverPort, const qtng::SslConfiguration& config)
    : qtng::SslServer<RequestHandler>(serverAddress, serverPort, config)
{

}

Server::Server(quint16 serverPort)
    : qtng::SslServer<RequestHandler>(serverPort)
{

}

Server::Server(quint16 serverPort, const qtng::SslConfiguration& config)
    : qtng::SslServer<RequestHandler>(serverPort, config)
{

}
