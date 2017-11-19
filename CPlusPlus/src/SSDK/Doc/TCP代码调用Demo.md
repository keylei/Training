# 对于Server端：


```
#include <iostream>
#include <chrono>

#include <boost/asio.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/system/error_code.hpp>
#include <boost/bind.hpp>
#include <boost/thread/thread.hpp>

#include <SSDK/Asio/TCP/server.hpp>

using namespace std;
using namespace boost::asio;
using namespace boost::asio::ip;
using namespace boost::system;
using namespace SSDK::Asio;
using namespace SSDK::Asio::TCP;

void receivedCallBackHandler(
               std::string ip,
               unsigned port,
               const vector<char>& buf)
{
    cout<<"IP:"<<ip<<", Port:"<<port<<endl;
    auto str = string(buf.data()+Message::HEADER_LENGTH);
    cout<< str <<endl;
}

int main()
{
    //>>>-------------------------------------------------------------------------------------------------------------------------------------
    //1. 开启服务端线程
    
    /**
     *异步事件队列中有事件，io_service::run就会一直阻塞不退出，所以只要保证异步事件队列中一直有事件就行了
     * 如何让异步事件队列中一直有事件呢, 有两种办法：
     * 
     * 1.一个简单的办法就是循环发起异步读操作，如果对方一直都不发数据过来，则这个异步读事件就会一直在异步事件队列中，这样io_service::run就不会退出了
     *    但是这样有一个缺点就是io_service::run处于阻塞会阻塞当前线程
     * 2.重新开启一个线程，执行run，通过work和一个专门的线程的线程去run保持io_service不退出的
     * 
     */
    
    io_service service;
    io_service::work serverWork(service);//注意，这一步必不可少
    boost::thread( [&service]{ service.run(); } );//启动一个线程run io_service，目地是不阻塞当前线程

    //>>>-------------------------------------------------------------------------------------------------------------------------------------
    //2.配置监听端口号
    
    /**
      *输入端口号,开启监听
      * 
      */
    
    cout<< "请输出端口号:" <<endl;

    short port {0};
    cin>>port;
    Server server(service, port);
    server.setReceivedHandler(receivedCallBackHandler);
    server.accept();

    //判断是否有成功连接的客户端
    while( server.connectionCnt() == 0 )
    {
            cout<<"No connection!"<<endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    }
     cout<<"Has "<<  server.connectionCnt() << " connections" <<endl ;


    //>>>-------------------------------------------------------------------------------------------------------------------------------------
    //3.发送数据的网络配置
     
     /**
       * 服务端可以给连接的客户端发送数据, 由于可能有多个客户端连接到服务端,所以服务端需要指定发送
       * 数据的客户端,这里通过ID指定, 一个ID就对应了一个IP和端口的组合
       */
     
    cout<<"请输出连接ID:"<<endl;
    uint id;
    cin>>id;

    auto handler =  server.searchConnection(id);
    auto remoteIP = handler->socket().remote_endpoint().address().to_string();
    auto remotePort = handler->socket().remote_endpoint().port();
    cout << "连接配置信息: IP " << remoteIP << ", Port: " << remotePort << endl;
    cout << "" << endl;


    //>>>-------------------------------------------------------------------------------------------------------------------------------------
    //4.反复从屏幕接收数据发送

    /**
     * 每次在屏幕上发送一行数据, 就把这个数据发送给制定的客户端,发送成功后提示输入下一个客户端的ID
     */
    
    string inData = "";
    vector<char> sendedData;
    cout<<"请输出Message:"<<endl;
    while(true)
    {
        getline(cin, inData);
        if(inData.size() > 1 && inData != "")
        {
            sendedData.resize(inData.size());
            memcpy(sendedData.data(), inData.data(), inData.size());
            server.sendSync(remoteIP, remotePort, sendedData);
            cout << "" << endl;

            //切换连接ID
            cout<<"请输出连接ID:"<<endl;
            uint id;
            cin>>id;

            handler =  server.searchConnection(id);
            remoteIP = handler->socket().remote_endpoint().address().to_string();
            remotePort = handler->socket().remote_endpoint().port();
            cout << "连接配置信息: IP " << remoteIP << ", Port: " << remotePort << endl;
            cout << "" << endl;

            cout<<"请输出Message:"<<endl;
        }
    }

    return 0;
}

```

# 对于客户端

```
#include <iostream>

#include <boost/asio.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/system/error_code.hpp>
#include <boost/bind.hpp>
#include <boost/thread/thread.hpp>

#include <SSDK/Asio/TCP/connection.hpp>
#include <SSDK/dataconvert.hpp>

using namespace std;
using namespace boost::asio;
using namespace boost::asio::ip;
using namespace boost::system;
using namespace SSDK::Asio;
using namespace SSDK::Asio::TCP;

void receivedCallBackHandler(
               std::string ip,
               unsigned port,
               const vector<char>& buf)
{
    cout<<"IP:"<<ip<<", Port:"<<port<<endl;
    auto str = string(buf.data()+Message::HEADER_LENGTH);
    cout<< str <<endl;
}

int main()
{
    //>>>-------------------------------------------------------------------------------------------------------------------------------------
    //1. 开启客户端线程
    
    /**
        *异步事件队列中有事件，io_service::run就会一直阻塞不退出，所以只要保证异步事件队列中一直有事件就行了
        * 如何让异步事件队列中一直有事件呢, 有两种办法：
        *
        * 1.一个简单的办法就是循环发起异步读操作，如果对方一直都不发数据过来，则这个异步读事件就会一直在异步事件队列中，这样io_service::run就不会退出了
        *    但是这样有一个缺点就是io_service::run处于阻塞会阻塞当前线程
        * 2.重新开启一个线程，执行run，通过work和一个专门的线程的线程去run保持io_service不退出的
        */
    
    io_service client;
    io_service::work clientWork(client);
    boost::thread( [&client]{ client.run(); } );

    
    //>>>-------------------------------------------------------------------------------------------------------------------------------------
    //2. 配置IP和端口号,并连接 
    
    string ip;
    cout<< "请输入IP地址:" <<endl;
    cin>>ip;

    cout<< "请输入端口号:" <<endl;
    short port;
    cin>>port;

    cout<<"start to connect..."<<endl;
    Connection conn(client,ip, port);
    conn.connect();
     conn.setReceivedHandler(receivedCallBackHandler);

    while(true)//判断是否连接成功, 只有成功了才能执行下一步
    {
        if(conn.isConnected())
        {
            break;
        }
    }

    cout<<"请输出Message:"<<endl;

    //>>>-------------------------------------------------------------------------------------------------------------------------------------
    //3. 反复从屏幕接收数据发送
    
    string inData = "";
    vector<char> sendedData;
    while(true)
    {
        getline(cin, inData);
        if(inData.size() > 1 && inData != "")
        {
            sendedData.resize(inData.size());
            memcpy(sendedData.data(), inData.data(), inData.size());
            conn.sendSync(sendedData);
             cout << "" << endl;
            cout<<"请输出Message:"<<endl;
        }
    }

    return 0;
}

```

