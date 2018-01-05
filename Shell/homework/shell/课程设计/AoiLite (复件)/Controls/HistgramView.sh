#!/usr/bin/env bash
#=========================================================================
# @usage
# @brief 直方图控件
# @author 斗牛组/麒麟组 (该脚本主要由grace负责完成)
# @version  1.00 2017/08/24 note:rime create it
#=========================================================================

declare -i histLeftMargin=2                  # 整个直方图相对与左边的边距
declare -i histTopMargin=2                   # 整个直方图相对与顶边的边距
declare -i DEFAULT_MAX_VALUE                 # 默认最大的直方图最大值

# @brief 绘制垂直方向的直方图
# @param $1 实际值
#        $2 最大值
# @return
drawVertialHist()
{

}

# @brief 绘制水平方向的直方图,
#        这里最大值和实际值都是相对来说的, 对于直方图最大值是字符单位, 所以这里需要进行映射
# @param $1 实际值
#        $2 最大值
# @return
drawHorizontalHist()
{

}

# @brief 初始化直方图
#        这里最大值和实际值都是相对来说的, 对于直方图最大值是字符单位, 所以这里需要进行映射
# @param $1 控件距离左边的距离
#        $2 控件距离顶边的距离
# @return
initHistgram()
{
  histLeftMargin=$1
  histTopMargin=$2

  #1. 绘制柱子最大值,默认为水平方向
  drawHorizontalHist

  #2. 信号捕获代码, 其中有"<" ">"
}
