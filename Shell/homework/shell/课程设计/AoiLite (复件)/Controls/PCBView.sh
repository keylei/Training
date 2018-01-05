# #!/usr/bin/env bash
#=========================================================================
# @usage
# @brief  PCBView
# @author 斗牛组/麒麟组 (该脚本主要由lynn负责完成)
# @version 1.00 2017/08/24 note:create it
#=========================================================================

declare -i BOX_CNT_EACH_FOV=4             # 每一个FOV中"[]对"数量
declare -i BOX_CNT_EACH_PCB=36            # 每一个PCB中的"[]对"的数量
declare -i FOV_CNT=9                      # 每一个PCB中的FOV的数量

declare -i PCBViewLeftMargin=2                  # 整个PCBView相对与左边的边距
declare -i PCBViewTopMargin=2                   # 整个PCBView相对与顶边的边距

declare -a xBox_arr                       # 所有"[]对"对应的X坐标数组
declare -a yBox_arr                       # 所有"[]对"对应的y坐标数组
declare -a xFov_arr                       # 所有Fov对应的x坐标数组
declare -a yFov_arr                       # 所有Fov对应的y坐标数组

declare -i isNormal=1                     # 是否处于正常模式: 1代表在正常模式(自动检测模式).0代表非正常模式(如GRR)

# @brief 绘制PCB板,PCB由6*6即36个方格"[]"绿色背景组成组成
# @param
# @return
drawPCB()
{

}

# @brief 绘制FOV列表, 边框默认为白色
# @param
# @return
drawFovList()
{

}

# @brief 初始化,
#        1.主要用于绘制PCB框和FOV框, PCB由6*6即36个方格"[]"绿色背景组成组成,一个FOV
#          包含了4个方格"[]", 即有9个FOV
#        2.每个方块"[]"之间需要留出一个字符的间隔
#        3.自动检测模式下:FOV边框为蓝色, 在检查过程中FOV内的方格也为蓝色;
#        4.非自动检测模式下(GRR):FOV边框为黄色, 在检查过程中FOV内的方格也为黄色;
#        5.source所有需要的脚本
# @param $1 是否处于正常模式
#        $2 控件距离左边的距离
#        $3 控件距离顶边的距离
# @return
initPCBView()
{
  isNormal=$1
  PCBViewLeftMargin=$2
  PCBViewTopMargin=$3

  #1. 绘制PCB
  drawPCB

  #2. 绘制FOV列表
  drawFovList
}

# @brief 高亮显示FOV
# @param $1 需要高亮显示的FOV索引号,范围[0-8],参数需要做好防呆
#        $2 需要高亮显示的Component索引号, 这对应了该FOV中需要高亮的元件, -1为全部显示
#           如果不是-1, 则为一个数组
# @return
highlightOn()
{
  # 根据索引得到需要高亮显示的FOV
}

# @brief 取消高亮
# @param
# @return
hightlightOff()
{

}
