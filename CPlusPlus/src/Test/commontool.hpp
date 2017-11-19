#ifndef COMMONTOOL_H
#define COMMONTOOL_H

#include <vector>

/**
 *  @brief comment
 *
 *  @author rime
 *  @version 1.00 2017-05-31 rime
 *                note:create it
*/
class CommonTool
{
public:
    CommonTool();
    virtual ~CommonTool();

    /**
     * @brief isEqual
     *             判断两个Vector是否相等
     * @param vec1
     * @param vec2
     * @return
     *              只有当Vector的长度相同, 每个元素相同的时候, 返回true, 其余返回false
     */
    template<typename T>
    static bool isEqual(std::vector<T> vec1, std::vector<T> vec2);
};

template<typename T>
bool CommonTool::isEqual(std::vector<T> vec1, std::vector<T> vec2)
{
    if(vec1.size()!=vec2.size())
    {
        return false;
    }
    else
    {
        for(auto i = 0; i < vec1.size(); ++i)
        {
            if(vec1[i] != vec2[i])
            {
                return false;
            }
        }

        return true;
    }
}

#endif//COMMONTOOL_H


