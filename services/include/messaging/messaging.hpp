#ifndef ECHOSERVER_H
#define ECHOSERVER_H

#include <QtCore/QObject>
#include <QtCore/QList>
#include <QtCore/QByteArray>

#include <string>
#include <mongocxx/pool.hpp>
#include <base/basic_controller.hpp>
#include <dbservice/database.hpp>
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>

using namespace cfx;
using namespace utility;
using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace concurrency::streams;

QT_FORWARD_DECLARE_CLASS(QWebSocketServer)
QT_FORWARD_DECLARE_CLASS(QWebSocket)

class Messaging : public QObject,BasicController, Controller{
    Q_OBJECT
public:
    explicit Messaging(quint16 port, bool debug = false, QObject *parent = nullptr);
    ~Messaging();

Q_SIGNALS:
    void closed();

private Q_SLOTS:
    void onNewConnection();
    void processTextMessage(QString message);
    void processBinaryMessage(QByteArray message);
    void socketDisconnected();
private:
    QWebSocketServer *m_pWebSocketServer;
    QList<QWebSocket *> m_clients;
    bool m_debug;

public:
    bool checkServices();
    http_client* AccountClient;
    database* m_db;
    Messaging(std::string,database*);

private:
    std::string messagingUri;
    bool createClients(std::string);

};

#endif //ECHOSERVER_H
