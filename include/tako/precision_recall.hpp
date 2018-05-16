#ifndef PRECISION_RECALL_HPP
#define PRECISION_RECALL_HPP
#include "tako/common_include.hpp"
#include "tako/config.hpp"
#include <fstream>
namespace tako
{
    class Verification
    {
      public:
        // compute values
        double precision_;
        double recall_;
        // define loop
        int total_image_; // 需要直接定義完成
        int total_loop_; // 需要直接定義完成
        int true_positive_; // 發生正確 loop closure 
        int false_positive_; // 發生錯誤 loop closure
        int false_negative_; // 沒有偵測到的 loop closure 現實 loop - TP

        // threshold
        float* thr = nullptr; // keypoint 1, object 2, spatial 3 
        // 1 float keypoint_threshold_;
        // 2 float object_threshold_;
        // 3 float spatial_threshold_;

      public:
        Verification(float* thr, int total_loop, int true_positive, int false_positive, int false_negative);
        void getPrecision(){return precision_;};
        void savefile();
        void getRecall(){return recall_;};
        
    };
} // namespace tako

#endif //PRECISION_REALL_HPP