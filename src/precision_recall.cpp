#include "tako/precision_recall.hpp"

namespace tako
{
    Vertification::Vertification(float* thr , int total_loop, int true_positive, int false_positive)
        : thr(thr), total_loop_(total_loop), true_positive_(true_positive), false_positive_(false_positive)
    {
        
        false_negative_ = total_loop_ - true_positive_ ;
        precision_ = (double)true_positive_ / (double)(true_positive_ + false_positive_);
        recall_ = (double)true_positive_ / (double)(true_positive_ + false_negative_);
        this->savefile();
    }
    void Vertification::savefile()
    {
        file_.open("precision.txt", std::ios::out|std::ios::app);
        if(!file)
        {
            std::cerr << " the file doesn't exist!!" << std::endl;
        }
        else
        {
            file << "Loop closure test ..." << std::endl;
            file << "threshold " << std::endl;
            file << " -keypoint_threshold : " << (thr)* <<std::endl;
            file << " -object_threshold : " << (thr + 1)* << std::endl;
            file << " -spatial_threshold : " << (thr + 2)* << std::endl;

            file << "output values ..." << std::endl;
            file << " precision : " << precision_ << std::endl;
            file << " recall : " << recall_ << std::endl;
        }

        file_.close();

    }

}