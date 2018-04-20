#ifndef KEYPOINTS_HPP
#define KEYPOINTS_HPP

#include "tako/common_include.hpp"
#include "DBoW3/DBoW3.h"
// build ORB feature and descriptor and BoW3 dictionary
namespace tako
{
    class KeyPoints
    {
        public:
            cv::Ptr< cv::Feature2D > detect = ORB::create(); // orb feature detect
            std::vector<cv::Mat> images_; // 接收 image vector
            std::vector<cv::Mat> descriptors_; // 讀取 descriptor
            
            // dictionary
            DBoW3::Vocabulary vocab_;
            

        public:
            KeyPoints(std::vector<cv::Mat> &images);
            void create_dictionary(); // create and save
            double compare();
            ~KeyPoints();

    };
}
#endif //KEYPOINTS_HPP