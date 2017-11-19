#ifndef IMAGESLOT_HPP
#define IMAGESLOT_HPP

namespace Job
{
    class ImageSlot
    {
    public:
        ImageSlot();
        ImageSlot(int width, int height, int imgCnt);
        ImageSlot(const ImageSlot& slot);
        ImageSlot& operator = (const ImageSlot &slot);
        virtual ~ImageSlot();

        void alloc();
        void transferCamBufToRawData( unsigned char** pRawImg, int imgCnt, int imgLen );
        void dealloc();

    private:
        int m_imgCnt {0};
        int m_width{0};
        int m_height{0};

        unsigned char** m_pRawImg{nullptr};
    };
}//End of namespace Job



#endif // IMAGESLOT_HPP
