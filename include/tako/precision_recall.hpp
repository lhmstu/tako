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
        // define loop
        int total_image_ ;//= tako::Config::get<int>("total_image"); // 需要直接定義完成
        //int real_loop_ = tako::Config::get<int>("total_real_loop"); // 需要直接定義完成
        int compute_loop_ ;
        //int tp = tako::Config::get<int>("TP"); // 發生正確 loop closure 
        //int fp; // 發生錯誤 loop closure
        //int fn; // 沒有偵測到的 loop closure 現實 loop - TP

        //final threshold
        float alpha_ = 0;
        float beta_ = 0;
        float gamma_ = 0;
        float Wth_ = 0;

        // threshold
        double* thr = nullptr; // keypoint 1, object 2, spatial 3 
        // 1 float keypoint_threshold_;
        // 2 float object_threshold_;
        // 3 float spatial_threshold_;

      public:
        Verification(int total_image, int compute_loop);
        ~Vertification();
        void main(cv::Mat loop);
        double getPrecision(int tp, int fp);
        double getRecall(int tp, int fn);
        int getTP(cv::Mat correct, cv::Mat loop);
        cv::Mat correctLoop();
        void savefile(double precision, double recall);
        void savefile(float alpha, float beta, float gamma, float Wth, double precision, double recall);
    };
} // namespace tako

#endif //PRECISION_REALL_HPP