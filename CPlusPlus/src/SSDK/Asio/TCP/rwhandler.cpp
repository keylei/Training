#include "rwhandler.hpp"

using namespace std;
using namespace boost::asio;
using namespace boost::asio::ip;
using namespace boost::system;
using namespace SSDK::Asio;
using namespace SSDK::Asio::TCP;

//>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//constructor & deconstructor

RWHandler::RWHandler(io_service &ios):
    m_socket(ios)
{

}

RWHandler::~RWHandler()
{

}

//<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//send & receive functions

void RWHandler::receiveSync()
{
    THROW_EXCEPTION_WITH_OBJ("Not supported read sync!");
}
void RWHandler::sendSync(const  char* pData, int64_t len)
{
    boost::system::error_code ec;

    this->m_toSendedMessage.writeData(pData, len);
    auto sendedSize = write(m_socket,
                            buffer(this->m_toSendedMessage.pHeader(),  this->m_toSendedMessage.messageLength()),
                            boost::asio::transfer_all(),
                            ec);

    if(sendedSize == this->m_toSendedMessage.messageLength())
    {
        cout<<"Success to send data! ConnID:"<<this->m_Id<<endl;
    }
    else
    {
         cout<<"Failed to send data!"<<endl;
    }

    cout<<""<<endl;

    if (ec != nullptr)
            handleError(ec);
}
void RWHandler::sendSync(const vector<char>& toSendedData)
{
    this->sendSync(toSendedData.data(),  toSendedData.size());
}

void RWHandler::receiveAsync()
{
    auto self = shared_from_this();

    //先收包头
    this->m_receivedMessage.clearData();

    cout<<""<<endl;//新起一行
    cout<<"Receive async..."<<endl;

    async_read(
                this->m_socket,
                buffer(this->m_receivedMessage.pHeader(), this->m_receivedMessage.headerLength()),
                [this, self](const boost::system::error_code& ec, size_t size)
                {
                    if (ec != nullptr ||  this->m_receivedMessage.headerLength() != size)
                    {
                        handleError(ec);
                        return;
                    }

                    uint64_t bodyLength = Message::parseHeader(this->m_receivedMessage.pHeader());
                    cout<<"Received data! Length:"<<bodyLength<<endl;
//                    if(bodyLength!=0)
                    {
                        //再收包体
                        auto self = shared_from_this();
                        this->m_receivedMessage.writeHeader(bodyLength);
                        async_read(
                                    this->m_socket,
                                    buffer(this->m_receivedMessage.pBody(), bodyLength),
                                    [&,this, self](const boost::system::error_code& ec, size_t size)
                                    {
                                        if(ec != nullptr ||  this->m_receivedMessage.bodyLength() != size)
                                        {
                                            handleError(ec);
                                            return;
                                        }

                                        //正确读取，调用回调函数
                                        if(bodyLength> 0 && nullptr!= this->m_receivedHandler)
                                        {
                                            auto ip = this->m_socket.remote_endpoint().address().to_string();
                                            auto port = this->m_socket.remote_endpoint().port();

                                            this->m_receivedHandler(ip, port, this->m_receivedMessage.buff());
                                        }

                                        receiveAsync();//保存读的状态
                                    }
                             );
                    }
                }
    );
}
void RWHandler::sendAsync( const  char* pData, int64_t len)
{
    /*
     * 代码的逻辑是这样的：
     * 当用户发送数据时，不直接调用异步发送接口，而是将数据放到一个发送队列中，
     * 异步发送接口会循环从队列中取数据发送。
     *
     * 循环发送过程的一个细节需要注意，用户发送数据时，如果发送队列为空时，说明异步发送已经将队列中所有的数据都发送完了，也意味着循环发送结束了，
     * 这时，需要在数据入队列之后再调用一下async_write重新发起异步循环发送。
     */

    bool hasMessage = !this->m_toSendedMessageQueue.empty();
    this->m_toSendedMessage.writeData(pData, len);
    this->m_toSendedMessageQueue.emplace_back( this->m_toSendedMessage);
    if(hasMessage)
    {
        sendAsync();
    }
}
void RWHandler::sendAsync( const vector<char>& sendedData)
{
    /*
     * 代码的逻辑是这样的：
     * 当用户发送数据时，不直接调用异步发送接口，而是将数据放到一个发送队列中，
     * 异步发送接口会循环从队列中取数据发送。
     *
     * 循环发送过程的一个细节需要注意，用户发送数据时，如果发送队列为空时，说明异步发送已经将队列中所有的数据都发送完了，也意味着循环发送结束了，
     * 这时，需要在数据入队列之后再调用一下async_write重新发起异步循环发送。
     */

    bool hasMessage = !this->m_toSendedMessageQueue.empty();
    this->m_toSendedMessage.writeData(sendedData.data(),  sendedData.size());
    this->m_toSendedMessageQueue.emplace_back( this->m_toSendedMessage);
    if(hasMessage)
    {
        sendAsync();
    }
}
void RWHandler::sendAsync()
{
    Message msg = this->m_toSendedMessageQueue.front();
    async_write(this->m_socket,
                buffer(msg.pHeader(),msg.messageLength()),
                [this](const boost::system::error_code& ec, std::size_t size)
                {
                    if(!ec && size != this->m_toSendedMessage.messageLength())//内部没有产生错误并且发送数据的长度等于message的长度
                    {
                         this->m_toSendedMessageQueue.pop_front();

                        if(!this->m_toSendedMessageQueue.empty())
                        {
                            sendAsync();
                        }
                    }
                    else
                    {
                        handleError(ec);
                        if(!this->m_toSendedMessageQueue.empty())
                        {
                            this->m_toSendedMessageQueue.clear();
                        }
                    }
                });
}

void RWHandler::close()
{
    boost::system::error_code ec;
    m_socket.shutdown(tcp::socket::shutdown_send, ec);
    m_socket.close(ec);
}


//<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//handle functions

void RWHandler::handleError(const boost::system::error_code& error)
{
    close();

    cout<<error.message()<<endl;
    if (this->m_errorHandler)
    {
        this->m_errorHandler(this->ip(), this->port(), this->m_Id);
    }
}


//<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
