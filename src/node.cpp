#include "tako/node.hpp"

namespace tako
{
    Node::Node()
    {
        Objdescriptor_ = cv::Mat::zeros(cv::Size(80,1), CV_32FC1);
    }

}