#include "server.hpp"

using namespace std;
using namespace boost::asio;
using namespace boost::asio::ip;
using namespace boost::system;
using namespace SSDK::Asio;
using namespace SSDK::Asio::TCP;

const int MaxConnectionNum = 65536;

//>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//constructor & deconstructor

Server::Server(io_service &ios, uint port):
    m_ioService(ios),
    m_acceptor(ios, tcp::endpoint(tcp::v4(), port))
{
    this->m_useableConnectionPool.resize(MaxConnectionNum);
    std::iota(this->m_useableConnectionPool.begin(), this->m_useableConnectionPool.end(), 1);
}

Server::~Server()
{

}

//<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//connection functions

std::shared_ptr<RWHandler> Server::createConnectionHandler()
{
    int connID = this->m_useableConnectionPool.front();//取出可用的最小ID号
    this->m_useableConnectionPool.pop_front();
    shared_ptr<RWHandler> handler = std::make_shared<RWHandler>(this->m_ioService);//创建一个RWHandler

    handler->setId(connID);
//    auto errorHandler = bind( &Connection::handleError, this, _1, _2, _3);

    handler->setErrorHandler([this](std::string ip, unsigned short port,  unsigned short connID)
    {
        cout<<"Release connection! IP["<<ip<<"], Port["<<port<<"] ID["<<connID<<endl;
        releaseConnectID(connID);
    });
    handler->setReceivedHandler(this->m_receivedCallBack);

    return handler;
}

void Server::accept()
{
    cout<<"listening ..." << endl;
    cout<<"" << endl;

    //创建一个连接
    std::shared_ptr<RWHandler> handler = this->createConnectionHandler();

    //一旦发生连接， 执行handler
    this->m_acceptor.async_accept(
                handler->socket(),//带有IP和端口信息, 这里会给socket进行赋值
                [this, handler](const boost::system::error_code& error)
    {
        if(error)//发生错误
        {
             cout << error.value() << " " << error.message() << endl;
             handleAcceptError(handler, error);
             return;
        }
        else
        {
            this->m_handlersMap.insert(make_pair(
                                           handler->Id(),
                                           handler));

            /*和connection不同的是，对于服务端，总是需要监控端口的请求，所有总是需要进行异步的读*/
            handler->receiveAsync();

            cout << "Current connect count: " << m_handlersMap.size() <<endl/*<<
                    "ID:"<<handler->Id()<< endl<<
                    "IP:"<<handler->ip()<<endl<<
                    "Port:"<<handler->port()<<endl;*/;

            //一旦接受返回了，需要重新启动accpet，保持监听状态
            this->accept();
        }
    });
}

void Server::stop()
{
    boost::system::error_code ec;
    this->m_acceptor.cancel(ec);
    this->m_acceptor.close(ec);
    this->m_ioService.stop();
}

void Server::copyDataFrom(int connID, std::vector<char>& dstData)
{
    std::ostringstream message;
    if(connID > MaxConnectionNum)
    {
        message<<"ID["<<connID<<"] is exceed the limit["<<MaxConnectionNum;
        std::string msg = message.str();\

        THROW_EXCEPTION_WITH_OBJ(msg);
    }
    else
    {
        auto it = this->m_handlersMap.find(connID);
        if (it == this->m_handlersMap.end())//还没有使用
        {
            message<<"ID["<<connID<<"] is not used!";
            std::string msg = message.str();\
            THROW_EXCEPTION_WITH_OBJ(msg);
        }
        else//正在使用
        {
          Message& msg = it->second->receivedMessage();

          auto dataSize = msg.bodyLength();
          if(dstData.size()!=dataSize)
          {
              dstData.resize(dataSize);
          }

          for( size_t i = 0; i< dataSize;++i )
          {
              dstData[i] = msg.pBody()[i];
          }
        }
    }
}

void Server::releaseConnectID(int connId)
{
    //从连接列表中移除该ID的连接
    auto it = this->m_handlersMap.find(connId);
    if (it != this->m_handlersMap.end())
        this->m_handlersMap.erase(it);
    cout << "current connect count: " << this->m_handlersMap.size() << endl;

    //把ID号返回
    this->m_useableConnectionPool.push_back(connId);
}

//<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//send functions

shared_ptr<RWHandler> Server::searchConnection(const string& ip, uint port)
{
    auto iter = this->m_handlersMap.begin();
    shared_ptr<RWHandler> handler;
    while(this->m_handlersMap.end() != iter)
    {
        auto endPoint = iter->second->socket().remote_endpoint();
        if(endPoint.address().to_string() == ip &&
            endPoint.port() == port)
        {
            return  iter->second;//找到相应的Handler返回
        }

        ++iter;
    }

    return handler;//走到这一步，说明没有找到，直接返回nullptr的指针
}
shared_ptr<RWHandler>  Server::searchConnection(uint connID)
{
    auto iter = this->m_handlersMap.begin();
    shared_ptr<RWHandler> handler;
    while(this->m_handlersMap.end() != iter)
    {
        if(iter->first == connID)
        {
            return  iter->second;//找到相应的Handler返回
        }

        ++iter;
    }

    return handler;//走到这一步，说明没有找到，直接返回nullptr的指针
}

void Server::sendSync(const string& ip, uint port, const vector<char>& sendedData)
{
    shared_ptr<RWHandler> handler =  this->searchConnection(ip, port);
    if(handler.get() == nullptr)
    {
        ostringstream stringstream;
        stringstream << "Can not to send data to IP["<<ip<<"], Port["<<port<<"]";

        //没有找到
        THROW_EXCEPTION_WITH_OBJ(stringstream.str());
    }
    else
    {
        //找到了相应的Handler
        handler->sendSync(sendedData);
    }
}

void Server::sendAsync(const string& ip, uint port, const std::vector<char>& sendedData)
{
    shared_ptr<RWHandler> handler =  this->searchConnection(ip, port);
    if(handler.get() == nullptr)
    {
        ostringstream stringstream;
        stringstream << "Can not to send data to IP["<<ip<<"], Port["<<port<<"]";

        //没有找到
        THROW_EXCEPTION_WITH_OBJ(stringstream.str());
    }
    else
    {
        //找到了相应的Handler
        handler->sendAsync(sendedData);
    }
}


//<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//handle function

void Server::handleAcceptError(
        shared_ptr<RWHandler> eventHanlder,
        const boost::system::error_code &error)
{
    cout << "Error，error reason：" << error.value() << error.message() << endl;
    //关闭socket，移除读事件处理器
    eventHanlder->close();
    stop();
}

//<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------






