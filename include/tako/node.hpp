#ifndef NODE_HPP
#define NODE_HPP

#include "tako/common_include.hpp"
#include "tako/object.hpp"
namespace tako
{
    class Node
    {
        public:
            int id_;
            // keypoint
            cv::Mat image_; // image color
            cv::Mat descriptor_;

            // object detect
            std::vector<tako::Object> node_object_;

            // sequence
            cv::Mat pose_; // pose

        public:
            Node (){}
            int getId(){return this->id_;};
            cv::Mat getImage(){return this->image_;};
            cv::Mat getPose(){return this->pose_;};
            ~Node (){}
    };
}
#endif // NODE_HPP