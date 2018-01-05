#!/usr/bin/env bash
#=========================================================================
# @usage
# @brief 用户进行数据的处理
# @author 斗牛组/麒麟组 (该脚本主要由plato和grace完成)
# @version 1.00 2017/08/24 note:rime create it
#=========================================================================

declare historyFilePath="LotHistory.txt"  # 批次历史检测数据的文件路径

declare grrTestFilePath="grr.txt"     # grr测试结果的导出文件路径

declare -i xShiftIndex=0                # x偏移的索引
declare -i yShiftIndex=1                # y偏移的索引
declare -i heightIndex=1                # 高度的索引
declare -a cpCpKArr=(0 0 0)             # 分别对应x,y偏移和高度的cp/cpk数据
declare -a grrArr=(0 0 0)               #

# @brief 生成随机数
# @param $1: 最小值
#        $2: 最大值
#        $3: 精度范围
# @return
random() # plato
{
  # 生成随机是
}

# @brief  计算批次的Cp和Cpk,这里的统计项主要是x,y偏移和高度
# @param  $1 对应查询的批次名称
# @return ---
calcCpCpk()  # plato
{
    # 注意这里面要给cpCpKArr赋值, 后续需要获取cp/cpk的值直接从cpCpKArr中根据相应统计项的
}

# @brief 计算Grr数据
# @param $1: 高阈值
#        $2: 低阈值
#        $3:
# @return
calcGrr()
{
  # 注意这里面要给grrArr赋值, 后续需要获取grr的值直接从grrArr中根据相应统计项的
}

# @brief 生成检测数据
#        检测数据有如下字段"Name Lib x-shift y-shift height reuslt confirm", 以Tab符分隔,
#        具体要求见README.md
# @param $1: 输出数据的文件路径
#        $2: 输出数据规模
# @return
generateData()  # grace
{

}

# @brief 导出检测数据
#     注意:
#         1.每个PCB都会有一个对应的数据输出, 输出的位置按照批次定义,不同批次在不同的目录,每块PCB
#           输出数据的文件名按"年月日小时分秒"来自动设定
#         2.目录名就是输入的参数名,也就是批次号, 这里就需要防呆了
#         3.各个批次子目录可以与该脚本在同一根目录下
# @param
# @return
exportData()  # grace
{

}

# @brief 备份数据, 把所有批次中检出的不良与误报方便汇总在对应的文件路径中,然后备份
#        数据字段:序号 时间  元器件名 Lib库类型名 NG或误报类型
# @param $1: 不良数据存的文件路径
#        $2: 误报数据存的文件路径
#        $3: 定时任务的时间间隔(单位:min)
# @return ---
backupData() # grace
{
  # 1.按照制定格式进行输出
  # 2.按照要求进行打包操作
}
