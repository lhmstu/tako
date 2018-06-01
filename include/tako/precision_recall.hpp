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
        //file name
        std::string filename_; 
        int tip = 1;
        //type of modules
        // module 
        //  1 : bow keypoint  
        //  2 : object keypoint
        //  3 : spatial 
        //  4 : combine total
        int module_ = 0;
        // compute values
        // define loop
        int total_image_ ;//= tako::Config::get<int>("total_image"); // 需要直接定義完成
        int real_loop_ ;//= tako::Config::get<int>("total_real_loop"); // 需要直接定義完成
        int compute_loop_ ;
        int tp_ ; // 發生正確 loop closure 
        //int fp; // 發生錯誤 loop closure
        //int fn; // 沒有偵測到的 loop closure 現實 loop - TP
        
        //ROC
        double tpr = 0;
        double fpr = 0; 

        //final threshold
        //float alpha_ = 0;
        //float beta_ = 0;
        //float gamma_ = 0;
        float* weight_ = nullptr;
        //float Wth_ = 0;

        // threshold
        double* thr_ = nullptr; // keypoint 1, object 2, spatial 3 
        // 1 float keypoint_threshold_;
        // 2 float object_threshold_;
        // 3 float spatial_threshold_;

      public:
        Verification(){}
        void init(double* thr, int total_image, int compute_loop, int real_loop);
        void init(double* thr, float* weight, int total_image, int compute_loop, int real_loop);
        //Verification(double* thr, int total_image, int compute_loop, int real_loop, float alpha, float beta, float gamma, float Wth);
        //Verification(double* thr, int total_image, int compute_loop, int real_loop,float alpha, float beta, float gamma);
        ~Verification();
        void setFilename(std::string filename);
        void run(int module, cv::Mat loop);
        double getPrecision(int tp, int fp);
        double getRecall(int tp, int fn);
        int getTP(cv::Mat correct, cv::Mat loop);
        cv::Mat correctLoop();
        void savefile(double precision, double recall);
        //void savefile(float alpha, float beta, float gamma, float Wth, double precision, double recall);
        void savefile(float alpha, float beta, float gamma, double precision, double recall);
    };
} // namespace tako

#endif //PRECISION_REALL_HPP