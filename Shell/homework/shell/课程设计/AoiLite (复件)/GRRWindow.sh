#!/usr/bin/env bash
#=========================================================================
# @usage
# @brief GRR的界面
# @author 斗牛组/麒麟组 (该脚本主要由lynn负责完成)
# @version 1.00 2017/08/24 note:create it
#=========================================================================

declare -i testTimeEachGroup=10       # 每次的测试次数
declare -i testGroupCnt=3             # 测试的组数

declare -i receivedSign=0             # 接受到的信号
declare -i toExitSign=27              # 退出软件的信号

declare grrTestFilePath="grr.txt"     # grr测试结果的导出文件路径

# @brief 初始化
# @param
# @return
initGRRWindow()
{
  # 1.drawLane 调用LaneView函数即可
  # 2.drawPCB 调用PCB函数即可
  # 3.信号捕获  一共有3个信号:Esc(退出)
  # 4.source所有需要的脚本
}

# @brief Grr测试
# @param
# @return
grrTest()
{
  # 1. 生成待检测的FOV列表
  #生成顺序:
  #   中间的FOV, 也就是索引为4的FOV必须检查
  #   四周有4个FOV, 从剩余的FOV列表中随机选取, 不能重复
  #   组后的列表需要进行从小到大的排序
  local toInspectFovList;

  # 2. 开始轮循检查每一个FOV
  for (( i = 0; i < ${#toInspectFovList[@]}; i++ )); do

        # 2.1 生成每个FOV需要检测的元件列表
        local toInspectTargetList; # 待检测的元件列表
        if [[ i -eq 4 ]]; then # 检查到中间的FOV时
         # 随机选取2个元件, 不能重复
         toInspectTargetList[0]=...
         toInspectTargetList[1]=...
        else # 检查到四周的FOV时
          # 随机选取一个元件
          toInspectTargetList[0]=...
        fi

        # 2.2 高亮显示FOV及对应的元件,调用PCBView中的函数
        highlightOn i toInspectTargetList

        # 2.3 生成每一个FOV的检测数据, 因为一共要生成500个元件的, 分到每一个FOV就是500/FOV_CNT
        # 调用DataHelper中的函数
        generateData grrTestFilePath ${#toInspectTargetList[@]}
  done
}


# @brief 启动GRR测试界面
# @param
# @return
startGRRWindow()
{
  # 1. 初始化, 和主界面一样, 主要包括了绘制Lane,PCB, 信号捕获代码
  initGRRWindow

  # 提示信息测试3组, 10次, 让用户确认后再推进,可以进行修改,需要有时间限制, 超过设定时间就是为默认设置
  read testTimeEachGroup
  read testGroupCnt

  # 2. 循环测试得到数据
  while [[ true ]]; do
    # 2.1.一开始需要判断是否需要退出进程, 就是是否按下过Esc

    # 2.2.弹出提示, 告知会测试3组, 每次10次, 用户确认后继续
    for (( i = 0; i < testGroupCnt; i++ )); do #测试3组
        # 提示这是第几组测试
        for (( i = 0; i < testTimeEachGroup; i++ )); do #每组测试10次

          # 2.loadIn 调用LaneView函数即可
          # 3.slowDown 调用LaneView函数即可
          # 4.clampOn 调用LaneView函数即可
          # 5.grrTest # 检测所有的FOV, 需要界面也进行同步的更新
          # 6.clampOff 调用LaneView函数即可
          # 7.loadOut 调用LaneView函数即可
          # 8.exportData # 调用DataHelper中的函数即可

        done
    done

    # 3.提示输入入tolerance,根据输入的tolerance计算并显示最终x-shift、y-shift、
    #   height的GRR值（为了便于用户阅读，之前用户输入的tolerance仍需保留显示）
    #   直接调用datahelper中的函数

    local lslTolerance;
    local uslTolerance;
    read -p "XXX" lslTolerance
    read -p "XXX" uslTolerance
    calcGrr $uslTolerance $lslTolerance grrTestFilePath

    # 4.在界面上显示结果

  done
}
