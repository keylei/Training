#ifndef DATAGENERATOR_HPP
#define DATAGENERATOR_HPP


#include <time.h>

#include "../sdk/FormatConvertor.hpp"
#include "../sdk/NumRandom.hpp"
#include "../sdk/Shape.hpp"
#include "../job/Board.hpp"
#include "../job/MeasuredObj.hpp"
#include "../sdk/CustomException.hpp"


using namespace std;

using namespace Job;
using namespace SSDK;


namespace App
{
/**
 *  @brief  DataGenerator
 *          生成所有数据
 *
 *  @author grace
 *  @version 1.00 2017-11-30 grace
 *                note:create it
 */
class DataGenerator
{
public:
    //>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    //constructor & destructor

    DataGenerator();
    virtual ~DataGenerator();

    //<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    //>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    //member function

    /**
     * @brief generateBoard 生成基板数据
     * @param board 基板
     * @param fiducialMarkCnt 基准点数量
     * @param padCnt 焊盘数量
     */
    static void generateBoard(Job::Board& board,int fiducialMarkCnt,int padCnt);

    //<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
};
}//End of namespace App


#endif // DATAGENERATOR_HPP
