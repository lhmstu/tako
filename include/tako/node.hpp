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
            // object descriptor
            cv::Mat Objdescriptor_;

            // spatial
            cv::Mat position_ = cv::Mat::zeros(cv::Size(4,3), CV_32FC1);

        public:
            Node ();
            int getId(){return this->id_;};
            cv::Mat getImage(){return this->image_;};
            cv::Mat getPose(){return this->position_;};
            float get_x(){return this->position_.at<float>(0,3);};
            float get_y(){return this->position_.at<float>(1,3);};
            cv::Mat getDescriptor(){return this->Objdescriptor_;};
            ~Node (){}
    };
}
#endif // NODE_HPP