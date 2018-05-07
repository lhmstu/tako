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
            float x_; // pose
            float y_; // pose

        public:
            Node ();
            int getId(){return this->id_;};
            cv::Mat getImage(){return this->image_;};
            float get_x(){return this->x_;};
            float get_y(){return this->y_;};
            cv::Mat getDescriptor(){return this->Objdescriptor_;};
            ~Node (){}
    };
}
#endif // NODE_HPP