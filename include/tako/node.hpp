#ifndef NODE_HPP
#define NODE_HPP

#include "tako/common_include.hpp"

namespace tako
{
    class node
    {
        public:
            int id_;
            cv::Mat image_; // image color
            cv::Mat pose_; // pose


        public:
            node (){}
            int getId(){return this->id_;};
            cv::Mat getImage(){return this->image_;};
            cv::Mat getPose(){return this->pose_;};
            ~node (){}
    };
}
#endif // NODE_HPP