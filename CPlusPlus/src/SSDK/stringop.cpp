#include "stringop.hpp"

void SSDK:: toUpper(char* src)
{
    if( nullptr != src)
    {
        size_t len = strlen(src);
        for (size_t i = 0; i < len; i++)
        {
            src[i] = std::toupper(src[i]);
        }
    }
}
