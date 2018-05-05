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
            
            // object vector weights 
            cv::Mat weights_ = cv::Mat::zeros(cv::Size(80,1), CV_32FC1);

            //input
        public:
            ObjectDetect();
            std::vector<tako::Object> object_detect(tako::Node &node);
            void getWeights();
            ~ObjectDetect();
    };
}
#endif // OBJECT_DETECT_HPP