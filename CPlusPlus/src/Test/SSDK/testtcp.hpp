#ifndef TESTTCP_HPP
#define TESTTCP_HPP

#include <iostream>

#include <boost/asio.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/system/error_code.hpp>
#include <boost/bind.hpp>
#include <boost/thread/thread.hpp>

#include "unittester.hpp"

#include "SSDK/Asio/TCP/connection.hpp"
#include "SSDK/Asio/TCP/server.hpp"
#include "SSDK/Asio/TCP/rwhandler.hpp"
#include "SSDK/Asio/message.hpp"
#include "SSDK/dataconvert.hpp"

using namespace std;
using namespace boost::asio;
using namespace boost::asio::ip;
using namespace boost::system;
using namespace SSDK;
using namespace SSDK::Asio;
using namespace SSDK::Asio::TCP;

namespace UnitTester
{
    namespace SSDK
    {
    void receivedCallBackHandler(
            const std::string& ip,
            unsigned port,
            const vector<char>& buf)
    {
        cout<<"IP:"<<ip<<", Port:"<<port<<endl;
        cout<<string(buf.data() + Message::HEADER_LENGTH )<<endl;
    }

        class TestTCP: public QObject
        {
            Q_OBJECT

        private slots:

            void initTestCase()
            {

            }
            void cleanupTestCase()
            {

            }

            /**
             * @brief testSimpleConnection
             *             测试简单的连接
             */
            void testServer()
            {
                //>>>-------------------------------------------------------------------------------------------------------------------------------------
                //1. 创建一个服务器

                io_service service;
                io_service::work serverWork(service);
                boost:: thread serverThread ( [&service]{ service.run(); } );

                Server server(service, 9900);
                server.setReceivedHandler(receivedCallBackHandler);
                server.accept();

                //>>>-------------------------------------------------------------------------------------------------------------------------------------
                //2.创建连接

                io_service client;
                io_service::work clientWork(client);
                boost:: thread clientThread = boost::thread( [&client]{ client.run(); } );

                cout<<"start to connect..."<<endl;
                Connection conn(client,"127.0.0.1", 9900);
                conn.connect();
                conn.setReceivedHandler(receivedCallBackHandler);

                while(true)
                {
                    if(conn.isConnected())
                    {
                        break;
                    }
                }

                //>>>-------------------------------------------------------------------------------------------------------------------------------------
                //3.Client To Server
                std::string context = std::string("ll");
                std::vector<char> clientData(context.size());
                memcpy(clientData.data(),context.data(), context.size());
                conn.sendSync( clientData);

//                context = std::string("aa");
//                conn.sendSync( context);

                //>>>-------------------------------------------------------------------------------------------------------------------------------------
                //4.Server To Client
//                conn.receiveAsync();
//                std::string serverString = "data from server!";
//                std::vector<char> serverData(serverString.size());
//                memcpy(serverData.data(),serverString.data(), serverString.size());
//                auto handler =  server.searchConnection(1);
//                auto ip = handler->socket().remote_endpoint().address().to_string();
//                auto port = handler->socket().remote_endpoint().port();
//                server.sendSync(ip, port, serverData);

//                //输出一个int数组
//                vector<uint64_t> intSrcData{111111111,222222222,33333333,44444444,55555555};
//                vector<char> intDstData;
//                DataConverter::copyToCharVector(intSrcData, 0, intDstData);
//                conn.sendSync( &intDstData[0], 40);

                while(true)
                {

                }
            }

        private:
//            std::thread m_serverThread;
        };//End of testTCP


//        DECLARE_TEST(TestTCP)//TCP需要交互，单元测试只是在本机进行简单的测试，最终需要在Server上测试
    }//End of namespace SSDK
}//End of namespace UnitTester


#endif // TESTTCP_HPP
