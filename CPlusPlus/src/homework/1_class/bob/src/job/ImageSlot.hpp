#ifndef IMAGESLOT_HPP
#define IMAGESLOT_HPP

#include "../sdk/customexception.hpp"

namespace Job
{

    /**
     *  @brief ImageSlot
     *         单个FOV图片的容器
     *  @author bob
     *  @version 1.00 2017-12-13 bob
     *                note:create it
     */
    class ImageSlot
    {
    public:
        //>>>----------------------------------------------------------------------------------------------------------------------------
        //constructor & destructor

        ImageSlot();

        /*
        *  @brief ImageSlot
        *           1.开辟指定大小的空间,存放单个FOV的图片
        *           2.获取图片的width,height,及单个fov图片的数量 //rime 顺序都不对，你应该是先获取到大小和张数，再开辟空间
        *  @param  imgWidth: 图片的宽度(单张图片)
        *          imgHeight:图片的高度(单张图片)
        *          imgCnt : 单个FOV内存放图片的数量
        *  @return N/A
        */
        ImageSlot(unsigned int imgWidth,unsigned int imgHeight,unsigned int imgCnt);

        /*
        *  @brief ImageSlot
        *         深复制ImageSlot对象中所有数据,具体如下:
        *             1.图片容器中图片的数量,图片的width,height
        *             2.图片容器中所有图片数据的灰度值
        *  @param imgSlot:为内存中已经存在的图片容器对象
        *                 (此对象数据深复制给 图片容器 对象)
        *  @return  N/A
        */
        ImageSlot(ImageSlot &imgSlot);

        /*p
        *  @brief  ImageSlot
        *           释放ImageSlot的储存空间
        *  @param   N/A
        *  @return  N/A
        */
        ~ImageSlot();
        //>>>----------------------------------------------------------------------------------------------------------------------------

        //>>>----------------------------------------------------------------------------------------------------------------------------
        // get & set functions

        int imgCnt(){return this->m_imgCnt;}
        void setImgCnt(unsigned int imgCnt){ this->m_imgCnt = imgCnt;}

        int imgWidth(){return this->m_imgWidth;}
        void setImgWidth(unsigned int imgWidth){this->m_imgWidth = imgWidth;}

        int imgHeight(){return this->m_imgHeight;}
        void setImgHeight(unsigned int imgHeight){this->m_imgHeight = imgHeight;}

        //rime 函数注释还是用编译器自动生成的好了
        /*
        *  @brief  setImgData
        *           给图片容器中每张图片中每个像素点的灰度值赋值
        *  @param  pImgData:传入图片数据的头指针
        *  @return N/A
        */
        //rime 这是个访存函数，不能出现在源文件中，再说如果涉及到深复制已经不能用访存函数了，因为人家
        //从函数名上已经无法分辨你是深复制还是浅复制了
        void setImgData(unsigned char * pImgData)
        {
            try
            {
                //获取单张图片的总长度
                int imgLen = this->m_imgWidth * this->m_imgHeight;

                if(0 == this->m_imgCnt ||
                   0 == this->m_imgHeight ||
                   0 == this->m_imgWidth) //如果imageslot成员变量为0,(即没有开辟空间)对象中
                {
                    THROW_EXCEPTION("没有初始化ImageSlot对象!");
                }
                else    //如果初始化成员变量,则开辟存储空间,给图片容器中图片数据赋值
                {
                    create();
                    //给图片容器中每张图片每个像素点的灰度值赋值
                    for (unsigned int i = 0; i < this->m_imgCnt; ++i)
                    {
                        for (int j = 0; j < imgLen; ++j)
                        {
                            this->m_pImageData[i][j] = pImgData[i * imgLen + j];
                        }
                    }
                }
            }
            catch(...)
            {
                destory();
                throw;
            }
        }
        unsigned char ** pImgData(){return this->m_pImageData;}
        //>>>----------------------------------------------------------------------------------------------------------------------------

        //>>>----------------------------------------------------------------------------------------------------------------------------
        //member functions

        /*
        *  @brief  initialize
        *          初始化图片容器类对象中所有成员变量
        *  @param  imgCnt:图片容器中的图片数量
        *          imgWidth:图片容器中每张图片的宽度
        *          imgHeight:图片容器中每张图片的高度
        *  @return N/A
        */
        void initialize(unsigned int imgCnt,unsigned int imgWidth,unsigned int imgHeight);

        /*
        *  @brief  create
        *          创建图片容器存储图片数据的空间
        *  @param  N/A
        *  @return N/A
        */
        void create();

        /*
        *  @brief  destory
        *          销毁图片容器储存图片数据空间
        *  @param  N/A
        *  @return N/A
        */
        void destory();
        //<<<---------------------------------------------------------------------------------------------------------------------------

    private:
        //>>>---------------------------------------------------------------------------------------------------------------------------

        unsigned int m_imgCnt{0};                             //单个fov图片的数量
        unsigned int m_imgWidth{0};                           //图片的宽度
        unsigned int m_imgHeight{0};                          //单个图片的高度
        unsigned char ** m_pImageData{nullptr};      //指定图片容器中图片数据的指针
        //<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    };

} //End of namespace Job

#endif // IMAGESLOT_HPP
