# 前言


在SDK中,**xml**,**protocolBufffer**主要用于单个对象的存储, 如配置文件, 不会用于大规模记录的存储,所以这里不在讨论之列

**测试数据:**

    30W行, 20列, 包括了5个Int,1个String,其余全部为double


**测试环境:**

        rime PC: i7  16G  Ubuntu(数据交互全部在机械硬盘上)



以下所有数据全部在基于release下编译, 通过Qt的单元测试QBenchMark测试的数据,单位(s)

## 写入:

        sqlite		json		parquet
         1.41		0.67		 2.36

## 查询:

        sqlite		json		parquet
         0.8		1.17		 1.34

## 文件大小:

        sqlite		json		parquet
         50.7M		165.4M		 48.4M

## 实验结论:

        写入: json   > sqlite > parquet
        查询: sqlite > json   > parquet
    文件大小: parquet> sqlite  > json
