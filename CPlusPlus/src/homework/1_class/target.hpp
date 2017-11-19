#ifndef TARGET_HPP
#define TARGET_HPP

#include <string>

namespace Job
{
    class Target
    {
    public:
        Target();

    private:

        int m_id;

        double m_x;
        double m_y;
        double m_angle;

        std::string m_name;
    };
}//End of namespace Job

#endif // TARGET_HPP
