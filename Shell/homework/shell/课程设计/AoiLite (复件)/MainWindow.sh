#!/usr/bin/env bash
#=========================================================================
# @usage [TBC grace 这里请把所有的输入选项和参数全部在这里一一列举]
# @brief AOI的主界面
# @author 斗牛组/麒麟组 (该脚本主要由byron和grace负责完成)
# @version 1.00 2017/08/24 note:rime create it
#=========================================================================

declare -i FOV_CNT=6                      # FOV数量
declare LOT_NO                            # 批次号, 由位置参数而来
declare -i currentInspectedTime=0         # 当前的检查一块板子需要的时间
declare -i currentInspectedPCBCnt=0       # 已检测的PCB数量
declare -i allInspectedTargetCnt=0     # 已检测的元件的数量
declare -i allNgTargetCnt=0            # 所有的不良元期间的数量(最后的Ng,排除了误报的)
declare -i falseCallTargetCnt=0        # 所有的误报元件的数量
declare  yield=0                          # 良率(ppm)
declare  falseCallRatio =0                # 误报率(ppm)
declare -i targetCntEachPCB=500        # 每一个PCB板需要检测的元件数量

declare -i isStoppingRequired=1           # 表示是否需要停止, 0:代表不需要停止 1:代表需要停止
declare -i receivedSign=25                # 接受到的信号
declare -i toStopSign=25                  # 停止信号
declare -i toStartSign=26                 # 开始信号
declare -i toExitSign=27                  # 退出软件的信号
declare historyFilePath="LotHistory.txt"  # 批次历史检测数据的文件路径

# @brief 1.显示统计信息: a.当前批次号、b.已检测时间（按秒更新）、c.已检测PCB数量、
#                       d.累计不良元器件数量、e.良率、f.误报率（注意：直通率、良率、
#                         误报率请按元件数的口径来统计，单位ppm）
#        2.显示量率,误报率的柱状图(直接调用HistgramView的函数)
#        3.必须考虑退出主界面下次再进入还是同一批次需要再原有基础上累计计算
#          历史批次统计信息存在history.txt文档中, 需要读取的是:
#          a.搜索当前批次 b.所有检测元件的数量 c.所有检查PCB的数量
#          d.所有误报元件的数量
#
#        要特别注意！必须考虑退出主界面下次再进入还是同一批次需要再原有基础上累计计算
#        历史批次统计信息存在history.txt文档中, 这里涉及到防呆, 需要做好三点:
#        1.文件不存在怎么办
#        2.文件存在但格式错误怎么办
#
# @param ---
# @return ---
showStatisticsInfo() # grace
{
    # 需要记得从history.txt读取目前该批次
}

# @brief 更新统计结果, 具体的要求和showStatisticsInfo一样
#        这里记得把阶段的检测结果需要更新到history.txt中
# @param
# @return
updateStatisticsInfo()  # grace
{

}

# @brief 初始化, 包括了:
#        1.绘制Lane
#        2.绘制PCBView,
#        3.显示统计信息
#        4.信号捕获
#        5.这里需要source所有需要的脚本
#        [TBC grace 这里请把所有需要捕获的信号一一列举]
# @param
# @return
initMainWindow() # grace
{
  # 1.drawLane 调用LaneView函数即可
  # 2.initPCBView 调用PCB函数即可
  # 3.showStatisticsInfo 调用函数即可
  # 4.信号捕获  一共有3个信号: S(start), ctrl+P(停止), Esc(退出)
  # 5.这里需要source所有需要的脚本
}

# @brief 选择工作模式, 一共有4中工作模式:AOI,SPC,GRR,Helper
#        注意:  1.输入--help, 后需要提示是否继续进入主界面
#               2.如果没有选项, 那么默认进入主界面, 但是一定要参数, 参数不对的话需要
#                 提示重新输入
# @param  输入-s/-spc 进入SPC界面
#         输入 -g/--grr 进入GRR界面
#         输入 -h/ --help 进入帮助界面
#         啥选项都没有, 需要验证参数, 如果有错误就进行防呆处理；没错误就继续, 也就是AOI的主界面
# @return 0:正常退出(可以往下执行)
#         1:非正常退出(直接退出程序)
selectMode() # grace
{

}


# @brief 循环检查每一个FOV, 每一个FOV都要进行的工作有: 1.刷新PCBView 2.生成每一个FOV的数据
# @param
# @return
inspectFovList() # byron
{
  for (( i = 0; i < FOV_CNT; i++ )); do
         # 1.高亮显示制定索引的FOV, 调用PCBView中的函数即可
        highlight i -1 # i为FOV索引号, -1代表了FOV中所有的元件全部显示

        # 2.生成每一个FOV的检测数据, 因为一共要生成500个元件的, 分到每一个FOV就是500/FOV_CNT
        # 调用DataHelper中的函数
        generateData

        # 3.根据实际运行情况设置sleep时间, 一般一个FOV平均0.5s
  done
}



# @brief 进入自动检查流程
#        [TBC byron]补充整个检查过程的描述
# @param
# @return
inspectCycle() # byron
{
    # 注意, 以下都是伪代码, 只是为了表示流程, 具体实现代码需要进行验证
    while [[ isStoppingRequired -ne 1 ]]; do

          # 一开始直接判断信号, 如果需要退出的话, 直接退出
          if [[ receivedSign -eq exitSign ]]; then
            exit
          fi

          # 这里需要开始计时, 需要加上之前的累计检测时间

          # S键进入自动检测, 以下是状态机代码

          # 1.loadIn 调用LaneView函数即可
          # 2.slowDown 调用LaneView函数即可
          # 3.clampOn 调用LaneView函数即可
          # 4.inspectFovList # 检测所有的FOV, 需要界面也进行同步的更新
          # 5.clampOff 调用LaneView函数即可
          # 6.loadOut 调用LaneView函数即可
          # 7.updateStatisticsInfo #  更新统计信息
          # 8.exportData # 调用DataHelper中的函数即可

          # 这里结束计时
    done
}

# 主函数
main() # byron
{
  # 1.选择模式
  selectMode

  # 2.初始化(包括界面初始化和信号捕获)
  initMainWindow

  # 3.循环检查
  inspectCycle
}

main
