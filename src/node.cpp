#include "tako/node.hpp"

namespace tako
{

cv::Mat node::getImage()
{
    return this->image_;
}

int node::getId()
{
    return this->id_;
}
}