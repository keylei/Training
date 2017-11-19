在调用一些开源库时, 由于需要把开源库的以静态库的方式编译到动态库中,此时可能给出现下列错误:

    /usr/bin/ld: /home/rime/Code/CompanyCode/3daoi/src/SSDK/../../lib/protobuf//libprotobuf.a(importer.o): relocation R_X86_64_32S against `_ZTVN6google8protobuf8compiler28SourceTreeDescriptorDatabase24ValidationErrorCollectorE' can not be used when making a shared object; recompile with -fPIC
    
对应的解决方案时:
### 1.  取消安装以便重新编
    sudo make uninstall
    sudo make distclean
    sudo make clean

### 2.  重新配置, 在项目的根目录下生成MakeFile
    ./configure
    
### 3.  找到项目下所有的MakeFile文件, 找到==CXXFLAGS==关键字, 然后加上-fPIC
    CFLAGS = -fPIC
    CFLAGS_FOR_BUILD = -g -O2 -fPIC
    CPP = gcc -E -fPIC
    CPPFLAGS = 
    CPPFLAGS_FOR_BUILD =  -fPIC
    CPP_FOR_BUILD = gcc -E
    CXX = g++ -std=c++11 -fPIC
    CXXCPP = g++ -E -std=c++11 -fPIC
    CXXCPPFLAGS_FOR_BUILD = -fPIC
    CXXCPP_FOR_BUILD = g++ -E
    CXXDEPMODE = depmode=gcc3
    CXXFLAGS =  -g -DNDEBUG -fPIC
    CXXFLAGS_FOR_BUILD = -g -O2 -fPIC
    CXX_FOR_BUILD = g++ -fPIC
    
### 4. 重新Make和Install
    sudo make
    sudo make check
    sudo make install