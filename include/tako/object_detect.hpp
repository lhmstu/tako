#ifndef OBJECT_DETECT_HPP
#define OBJECT_DETECT_HPP
// tako 
#include "tako/common_include.hpp"
#include "tako/node.hpp"
#include "tako/config.hpp"

// opencv dnn module
namespace tako
{
    class Config;
    class Object;
    class ObjectDetect
    {
        public:
            //parameter
            cv::String cfg_;
            cv::String model_;
            float confidThr_;
            cv::dnn::Net net_; //?
            std::vector<cv::String> classNamesVec_;

            //input
        public:
            ObjectDetect();
            std::vector<tako::Object> object_detect(cv::Mat frame);
            ~ObjectDetect();
    };
}
#endif // OBJECT_DETECT_HPP