资料总结来源与:
简单理解Socket  [link](http://www.cnblogs.com/dolphinX/p/3460545.html)

# TCP/IP


TCP/IP协议参考模型把所有的TCP/IP系列协议归类到四个抽象层中

- 应用层：TFTP，HTTP，SNMP，FTP，SMTP，DNS，Telnet 等等
- 传输层：TCP，UDP
- 网络层：IP，ICMP，OSPF，EIGRP，IGMP
- 数据链路层：SLIP，CSLIP，PPP，MTU

![image](http://images.cnitblog.com/blog/349217/201312/05230830-04807bb739954461a8bfc7513707f253.jpg)


# Socket

在本地进程通讯中我们可以使用PID来唯一标示一个进程,IP层的ip地址可以唯一标示主机,TCP层协议和端口号可以唯一标示主机的一个进程，这样我们可以利==用ip地址＋协议＋端口号==唯一标示网络中的一个进程。


socket是在应用层和传输层之间的一个抽象层，它把TCP/IP层复杂的操作抽象为几个简单的接口供应用层调用已实现进程在网络中通信

socket起源于UNIX，在Unix一切皆文件哲学的思想下，socket是一种"==打开—读/写—关闭=="模式的实现，服务器和客户端各自维护一个"文件"，在建立连接打开后，可以向自己文件写入内容供对方读取或者读取对方内容，通讯结束时关闭文件

![image](http://images.cnitblog.com/blog/349217/201312/05225723-2ffa89aad91f46099afa530ef8660b20.jpg)

# 三次握手
1. 第一次握手：客户端发送syn包(syn=j)到服务器，并进入SYN_SEND状态，等待服务器确认;　　
2. 第二次握手：服务器收到syn包，必须确认客户的SYN(ack=j+1)，同时自己也发送一个SYN包(syn=k)，即SYN+ACK包，此时服务器进入SYN_RECV状态;　
3. 第三次握手：客户端收到服务器的SYN+ACK包，向服务器发送确认包ACK(ack=k+1)，此包发送完毕，客户端和服务器进入ESTABLISHED状态，完成三次握手。　　握手过程中传送的包里不包含数据，三次握手完毕后，客户端与服务器才正式开始传送数据。


![image](http://hi.csdn.net/attachment/201108/7/0_131271823564Rx.gif)。



