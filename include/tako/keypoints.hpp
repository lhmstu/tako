#ifndef KEYPOINTS_HPP
#define KEYPOINTS_HPP

#include "tako/common_include.hpp"
#include "DBoW3/DBoW3.h"
#include "tako/node.hpp"
#include "tako/config.hpp"
// build ORB feature and descriptor and BoW3 dictionary
namespace tako
{
    class Node;
    class KeyPoints
    {

        public:
            KeyPoints (){}
            KeyPoints(DBoW3::Vocabulary &vocab);
            KeyPoints(DBoW3::Vocabulary &vocab, DBoW3::Database &db); //constructor descriptors

            void create_database(std::vector<tako::Node> &nodes); // create and save
            double compare_Image2Image(tako::Node node1, tako::Node node2);
            //spatial compare
            double compare_spatial2spatial(cv::Mat descriptor1, cv::Mat descritpor2);
            DBoW3::Database setDatabase();
            //void setDatabase();
            void setVocabulary(std::vector<tako::Node> &nodes);
            void compare_Image2Database(tako::Node &node, DBoW3::Database &db, DBoW3::QueryResults &ret);
            //void compare_Image2Database(tako::Node &node, DBoW3::Database &db)
            ~KeyPoints(){};

        public:
            cv::Ptr< cv::Feature2D > detector_ = cv::ORB::create(); // orb feature detect
            //std::vector<cv::Mat> images_; // 接收 image vector
            std::vector<cv::Mat> descriptors_; // 讀取 descriptor
            // dictionary
            DBoW3::Vocabulary vocab_;
    };
}
#endif //KEYPOINTS_HPP