#ifndef SERVER_H
#define SERVER_H
#include <qtnetworkng/qtnetworkng.h>
using namespace qtng;

namespace NSNetwork {
    class RequestHandler : public qtng::BaseRequestHandler
    {
    public:
        RequestHandler();
        virtual ~RequestHandler();

        qint32 bufferSize() const;
        void setBufferSize(const qint32& size);

    protected:
        virtual bool setup();
        virtual void handle();
        virtual void finish();

    private:
        qint32 _nBufferSize;             
    };

    class Server : public qtng::SslServer<RequestHandler>
    {
    public:
        Server(const qtng::HostAddress& serverAddress, quint16 serverPort);
        Server(const qtng::HostAddress& serverAddress, quint16 serverPort, const qtng::SslConfiguration& config);
        Server(quint16 serverPort);
        Server(quint16 serverPort, const qtng::SslConfiguration& config);
    };
}

#endif // SERVER_H
