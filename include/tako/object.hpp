#ifndef OBJECT_HPP
#define OBJECT_HPP
#include "tako/common_include.hpp"
namespace tako
{
    class Object
    {
        public:
            cv::String className_;
            float confidence_;
            float width_;
            float height_;

        public:
            Object(){}
            void storeVarious(cv::String &className,float &confidence, float &width, float &height);
            friend std::ostream &operator<<(std::ostream &s, tako::Object object);
            ~Object(){}
    };
}
#endif //OBJECT_HPP