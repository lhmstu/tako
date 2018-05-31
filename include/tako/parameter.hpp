#pragma once
#include "tako/common_include.hpp"

namespace tako
{
    class Parameter
    {
        public:
            int init = 0; 
            //threshold
            double* thr_start_ = nullptr;
            double* thr_inter_ = nullptr;
            double* thr_end_ = nullptr;
            //weight
            float* weight_ = nullptr;
            float weight_inter_ ;//0.1
            float weight_end_; // 0.9
        public:
            //Parameter(double, double, double, float, float, float);
            Parameter(double thr[], double thr_inter[], double thr_end[], float weight[], float weight_inter, float weight_end);
            ~Parameter();
            //double* update_threshold(double thr[], double inter[]);
            float update_weight(float weight[], float weight_inter);
            //void reset();
            bool check_weight(float alpha, float beta, float gamma);
            bool is_thr_end(double thr[]);

    };
}