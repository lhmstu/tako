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
            cv::dnn::Net net_; 
            std::vector<cv::String> classNamesVec_;
            
            // object vector weights 
            cv::Mat weights_ = cv::Mat::zeros(cv::Size(80,1), CV_32FC1);

            // object mapping
            cv::Mat tfIdf_;
            typedef std::multimap<int, std::pair<int, cv::Mat> > objDatabase;
            objDatabase objDatabase_;
            //std::vector<std::pair<int,cv::Mat> > scores_;

            //input
        public:
            ObjectDetect();
            std::vector<tako::Object> object_detect(tako::Node &node);
            void getWeights();
            void gettf_idf(); // return TF*IDF
            void objscoring(tako::Node &node, std::vector<std::pair<int, float> > &scores_);
            double compare_Object2Object(tako::Node &node1, tako::Node &node2);
            //std::multimap<int, cv::String> getMultimap();
            ~ObjectDetect();
    };
}
#endif // OBJECT_DETECT_HPP