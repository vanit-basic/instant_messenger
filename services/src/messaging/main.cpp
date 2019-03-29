#include <stdio.h>
#include <usr_interrupt_handler.hpp>
#include <runtime_utils.hpp>
#include <messaging/messaging.hpp>
#include <QtCore/QCoreApplication>
#include <QtCore/QCommandLineParser>
#include <QtCore/QCommandLineOption>
#include <QtCore/QObject>

using namespace web;
using namespace cfx;

int main(int argc, char * argv[])
{
/*	if(argc < 2)
	{
		std::cerr << "Config file is not specified" << std::endl;
		exit (-1);
	}
	else
	{
		std::string path = std::string(argv[1]);
		InterruptHandler::hookSIGINT();
		database* m_db;
		Messaging server(path,m_db);
		if(server.checkServices())
		{

			try {
				server.accept().wait();
				std::cout << "Messaging Service start " << std::endl;

				InterruptHandler::waitForUserInterrupt();

				server.shutdown().wait();
			}
			catch(std::exception & e) {
				std::cerr << "somehitng wrong happen! :(" << '\n';
			}
			catch(...) {
				RuntimeUtils::printStackTrace();
			}
		}
	} */

    QCoreApplication a(argc, argv);

    QCommandLineParser parser;
    parser.setApplicationDescription("QtWebSockets example: echoserver");
    parser.addHelpOption();

    QCommandLineOption dbgOption(QStringList() << "d" << "debug",
            QCoreApplication::translate("main", "Debug output [default: off]."));
    parser.addOption(dbgOption);
    QCommandLineOption portOption(QStringList() << "p" << "port",
            QCoreApplication::translate("main", "Port for echoserver [default: 1205]."),
            QCoreApplication::translate("main", "port"), QLatin1Literal("1205"));
    parser.addOption(portOption);
    parser.process(a);
    bool debug = parser.isSet(dbgOption);
    int port = parser.value(portOption).toInt();

    //EchoServer *server = new EchoServer(quint16(port));
    Messaging* server(quint16(port));
 //   QObject::connect(server, &EchoServer::closed, &a, &QCoreApplication::quit);

    return a.exec();

}

