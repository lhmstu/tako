#ifndef NODE_HPP
#define NODE_HPP

#include "tako/common_include.hpp"

namespace tako
{
    class Node
    {
        public:
            int id_;
            cv::Mat image_; // image color
            cv::Mat pose_; // pose

            cv::Mat descriptor_;
            

        public:
            Node (){}
            int getId(){return this->id_;};
            cv::Mat getImage(){return this->image_;};
            cv::Mat getPose(){return this->pose_;};
            ~Node (){}
    };
}
#endif // NODE_HPP