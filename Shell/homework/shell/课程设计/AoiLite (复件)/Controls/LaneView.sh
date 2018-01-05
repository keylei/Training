#!/usr/bin/env bash
#=========================================================================
# @usage
# @brief LaneView
# @author 斗牛组/麒麟组 (该脚本主要由plato负责完成)
# @version 1.00 2017/08/24 note:create it
#=========================================================================

declare -i laneViewLeftMargin=2                  # 整个LaneView相对与左边的边距
declare -i laneViewTopMargin=2                   # 整个LaneView相对与顶边的边距

declare -i LANE_PCB_HEIGHT=2                     # PCB的高度(单位字符)
declare -i LANE_PCB_WIDTH=8                      # PCB的宽度(单位字符)
declare -i LOADIN_WIDTH=16                       # loadin部分的宽度(单位字符)
declare -i SLOWDOWN_WIDTH=32                     # SlowDown部分的宽度(单位字符)
declare -i LOADOUT_WIDTH=16                      # loadout部分的宽度(单位字符)
declare -i CONVEYOR_HEIGTH=1                     # 传送带的高度(单位字符)

declare -i LOADIN_TIME=1                         # loadin需要的时间(单位秒)
declare -i SLOWDOWN_TIME=2                       # loadin需要的时间(单位秒)
declare -i LOADOUT_TIME=1                        # loadin需要的时间(单位秒)
declare -i ENTER_TIME=1                          # PCB的进板时间(单位s)
declare -i INTERVAL_TIME=0.5                     # LoadIn, LoadOut, SlowDown的传送带之间的间隔时间(单位s)

# LoadIN 0-1- SlowDown 2-3- LoadOut 4-5-
declare -ai PCBPosArr=(0 1 2 3 4 5)              # 表示PCB现有位置的数组
declare -i currentPCBPosIndex=0                  # PCB现在的位置索引

# @brief 更新PCB的位置
# @param $1: 之前PCB处于的位置, 如果是-1代表不需要擦除 范围[0,7],需要防呆
#        $2: 需要绘制的PCB的新位置
#        $3: 需要传送的时间
# @return
updatePCBPosition()
{
    #1. 需要擦除之前PCB的位置
    #2. Sleep相应的时间
    #3. 绘制出最新的PCB的位置
}

# @brief
# @param $1 是否需要擦除原来的PCB,因为有可能是从loadout过来, 此时需要擦除PCB的
#           0不需要擦除 1需要擦除
# @return
loadIn()
{
  #1. 根据$1的参数判断是否要擦除LoadOut处的PCB
  if [[ currentPCBPosIndex -eq 5 ]]; then # 在loadout处需要擦除原来的
    updatePCBPosition 5 0 ENTER_TIME
  fi

  #2. 进行完整的LoadIn流程
  updatePCBPosition 0 1 LOADIN_TIME
}

# @brief
# @param
# @return
loadOut()
{
  updatePCBPosition 3 4 INTERVAL_TIME
  updatePCBPosition 4 5 LOADOUT_TIME
}

# @brief
# @param
# @return
slowDown()
{
  updatePCBPosition 1 2 INTERVAL_TIME

  updatePCBPosition 2 3 SLOWDOWN_TIME
}

# @brief
# @param
# @return
clampOn()
{
  # 把slowDown段的轨道高亮显示
}

# @brief
# @param
# @return
clampOff()
{
  # 把slowDown段的轨道取消高亮
}

# @brief
# @param  $1 控件距离左边的距离
#         $2 控件距离顶边的距离
# @return
initLaneView()
{
  laneViewLeftMargin=$1
  laneViewTopMargin=$2

  # 1.绘制轨道


  # 2.规制PCB
}
