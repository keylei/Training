#!/usr/bin/env bash
#=========================================================================
# @usage
# @brief 绘制靶状图
# @author 斗牛组/麒麟组 (该脚本主要由grace负责完成)
# @version 1.00 2017/08/24 note:rime create it
#=========================================================================

declare -i bulletChartLeftMargin=2                  # 整个直方图相对与左边的边距
declare -i bulletChartTopMargin=2                   # 整个直方图相对与顶边的边距
declare -i DEFAULT_X_MAX_VALUE                   # 默认X方向最大的直方图最大值
declare -i DEFAULT_Y_MAX_VALUE                   # 默认Y方向最大的直方图最大值

# @brief 初始化靶状图
# @param $1 控件距离左边的距离
#        $2 控件距离顶边的距离
# @return
initBulletChart()
{
  bulletChartLeftMargin=$1
  bulletChartTopMargin=$2
  
  # 1.绘制坐标轴
}

# @brief 更新BarChart
#        注意:
#        1.每个点的坐标用"X"表示
#        2.如果点数太多, 造成界面过于密集的话, 需要进行插值处理
# @param $1 数组参数
#        $2 X轴的最大值
#        $3 Y轴的最大值
# @return
updateBulletChart()
{
  #1. 更新坐标轴最大值的label显示
  #2. 更新靶状图的坐标(用x表示)
}
