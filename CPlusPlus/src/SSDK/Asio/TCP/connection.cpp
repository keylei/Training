#include "connection.hpp"

using namespace std;
using namespace boost;
using namespace boost::asio;
using namespace boost::asio::ip;
using namespace SSDK::Asio;
using namespace SSDK::Asio::TCP;

//>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//constructor & deconstructor

Connection::Connection(io_service &ioService, const string &remoteIP, uint remotePort):
    m_ioservice(ioService),
    m_socket(ioService),
    m_serverEndPoint(tcp::endpoint(address::from_string(remoteIP), remotePort))
{
    createRWHandler(ioService);
}

Connection::~Connection()
{

}

//<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//send functions

void Connection::sendSync(std::vector<char>& sendedData)
{
    if(!this->m_isConnected)
        return;

    this->m_eventHandler->sendSync(sendedData);
}
void Connection::sendAsync(std::vector<char>& sendedData)
{
    if(!this->m_isConnected)
        return;

    this->m_eventHandler->sendAsync(sendedData);
}

//<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//receive functions

void Connection::receiveAsync()
{
    this->m_eventHandler->receiveAsync();
}

void Connection::receiveSync()
{
    this->m_eventHandler->receiveSync();
}

//<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//handler functions

void Connection::createRWHandler(io_service &ioService)
{
    this->m_eventHandler = std::make_shared<RWHandler>(ioService);

    //这里在创建的时候自动设置了重新连接的回调函数，当然也可以
    //手动调用setErrorHandler来设置自己的回调函数
    auto errorHandler = bind( &Connection::handleError, this, _1, _2, _3);
    m_eventHandler->setErrorHandler(errorHandler);
}
void Connection::handleError(std::string ip, unsigned short port,  unsigned short connID)
{
    cout<<"Failed to connect! IP["<<ip<<"], Port["<<port<<"] ID["<<connID<<endl;
    this->m_isConnected = false;
    this->reconnect();
}
void Connection::handleConnectError(const system::error_code &error)
{
    m_isConnected = false;
    cout << error.message() << endl;
    m_eventHandler->close();
}

//<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//connect functions

bool Connection::connect()
{
    if(this->m_isConnected)
    {
        return true;
    }

    this->m_eventHandler->socket().async_connect(
                this->m_serverEndPoint,
                [this](const boost::system::error_code& error)
    {
        if(error)
        {
            /*只有是第一次连接时, 根据需要决定是否需要重新连接;
               如果不是第一次连接时，就不要重新连接了*/
            cout<<"Try to connect to IP:"<< this->remoteIP()<<", Port:"<<this->remotePort()<<endl;

            //如果是通过重新连接即reconnect调用的connect，就不需要再次调用reconnect了
            if(!this->m_isReconnecting && this->m_isReconnectRequired)
                reconnect();
        }
        else
        {
            cout<<"Connect ok" << endl;
            this->m_isConnected = true;

            // 连接成功后发起一个异步读的操作

            //注意：
            //TBC 这里考虑是否需要一连接成功就开启异步读取，
            //如果开启的话会消耗cpu资源，因为存在单向发送数据的情况如客户端向服务端发数据，而不需要服务器反馈
            //如果不开启的话需要后续手动开启，对于大部分需求，都需要双向开启
            //这里暂时默认就开启
            this->m_eventHandler->receiveAsync();
        }
    });

    return this->m_isConnected;
}
void Connection::reconnect()
{
    this-> m_isConnected = false;
    cout << "start to  reconnect to IP:"<< this->remoteIP()<<", Port:"<<this->remotePort()<<endl;
    this->m_eventHandler->close();

    if(nullptr != this->m_reconnectingThread)
    {
        return;
    }
    else
    {
        m_reconnectingThread = std::make_shared<std::thread>([&, this]
        {
            this->m_currentReconnectIndex = 0;
            this->m_isReconnecting = true;

            //循环重连，如果没有达到最大重连次数，继续连接
            while (this->m_currentReconnectIndex < this->m_maxReconnectCnt)
            {
                if(!this->m_isConnected)//连接不成功
                {
                    this->connect();
                }
                else//连接成功，退出
                {
                    break;
                }

                this->m_currentReconnectIndex++;//连接次数+1

                //间隔m_connectIntervalTime时间再进行重新连接
               std::this_thread::sleep_for(std::chrono::milliseconds(this->m_connectIntervalTime));
            }

            //达到最大连接次数以后， 输出超时，退出线程
            if( this->m_currentReconnectIndex >= this->m_maxReconnectCnt)
            {
                 cout<<"time out!"<<endl;
            }

            this->m_isReconnecting = false;
        }
        );
    }
}
void Connection::setReconnectParm(
            bool isRepeatConnect,
            uint maxRepeatConnectCnt,
            uint connectIntervalMS)
{
    this->m_isReconnectRequired = isRepeatConnect;
    this->m_maxReconnectCnt = maxRepeatConnectCnt;
    this->m_connectIntervalTime = connectIntervalMS;
}
void Connection::disconnect()
{
    this->m_isConnected = false;
    this->m_socket.close();
}

//<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
