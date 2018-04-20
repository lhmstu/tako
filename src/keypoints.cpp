#include "tako/keypoints.hpp"

namespace tako
{
    KeyPoints::KeyPoints(std::vector<cv::Mat> &images) : images_(images)
    {
        for(Mat& image:images_)
        {
            vector<KeyPoint> keypoints;
            cv::Mat descriptor;
            detector->detectAndCompute(image, Mat(), keypoints, descriptor);
            descriptors_.push_back( descriptor );
        }
    }

    void create_dictionary()
    {
        std::cout<< "create Vocabulary..." <<std::endl;
        vocab_.create(descriptors_);

        vocab_.save("vocabulary.yml.gz");

        std::cout<< "save dictionary to file : vocabulary.yml.gz " <<std::endl;
    }
}