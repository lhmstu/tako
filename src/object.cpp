#include "tako/object.hpp"
namespace tako
{
    void Object::storeVarious(cv::String &className, float &confidence, float &width, float &height)
    {
        className_ = className;
        confidence_ = confidence;
        width_ = width;
        height_ = height;
    }

    std::ostream &operator<<(std::ostream &s, tako::Object object)
    {
        s << "( classname : " << object.className_ << " , " 
            << "confidence : " << object.confidence_ << " , "
            << "width : " << object.width_ << " , " 
            << "height : " << object.height_ << " )" ;

        return s ;
    }
}