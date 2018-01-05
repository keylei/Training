//#ifndef IMAGESLOT_HPP
//#define IMAGESLOT_HPP

//#include <cstring>
//#include <chrono>

//#include "sdk/customexception.hpp"

//namespace Job
//{
//    /**
//     *  @brief ImageSlot
//     *              图像槽
//     *              1.具有成员变量: 图像的张数(32张), 图像的长和宽, 图像数据的指针
//     *              2.在Job的命名空间下, 具有参数构造函数,默认构造函数和析构函数
//     *              3.ImageSlot能够被复制,请考虑到底使用深复制还是浅复制
//     *              4.具有开辟内存,销毁内存以及传输数据的成员函数
//     *              5.考虑好ImageSlot的异常处理
//     *              6.在main函数中调用，创建数组（10个），图像数据随机生成（byte类型）0-255
//     *
//     *  @author plato
//     *  @version 1.00 2017-12-13 plato
//     *                note:create it
//     */
//    class ImageSlot
//    {
//    public:
//        //>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//        //constructor & destructor

//        /**
//         * @brief ImageSlot
//         */
//        ImageSlot();

//        /**
//         * @brief ImageSlot
//         * @param imgCnt
//         * @param imgWidth
//         * @param imgHeight
//         */
//        ImageSlot(const int imgCnt, const int imgWidth, const int imgHeight);

//        /**
//         * @brief ImageSlot
//         * @param imageSlot
//         */
//        ImageSlot(const ImageSlot& imageSlot);

//        /**
//         * @brief ~ImageSlot
//         */
//        virtual ~ImageSlot();

//        //<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


//        //>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//        //get & set functions

//        int imgCnt() const { return this->m_imgCnt; }

//        int imgWidth() const { return this->m_imgWidth; }

//        int imgHeight() const { return this->m_imgHeight; }

//        unsigned char *pImgData() const { return this->m_pImgData; }

//        //<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


//        //>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//        //member functions

//        /**
//         * @brief create
//         */
//        void create();

//        /**
//         * @brief destroy
//         */
//        void destroy();

//        /**
//         * @brief transmit
//         */
//        void transmit(unsigned char *pImgData);

//        //<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//    private:
//        int m_imgCnt{0};                      // 图像张数
//        int m_imgWidth{0};                    // 图像宽度
//        int m_imgHeight{0};                   // 图像高度
//        unsigned char *m_pImgData{nullptr};  // 图像数据
//    };

//}//End of namespace Job

//#endif // IMAGESLOT_HPP
