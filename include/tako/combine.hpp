#ifndef COMBINE_HPP
#define COMBINE_HPP
#include "tako/common_include.hpp"
#include "tako/config.hpp"
namespace tako
{
    class Combine 
    {
        public:
            float alpha;
            float beta;
            float gamma;
            float Wth;

            //double prob_key = 0; // keypoint method loop number
            //double prob_obj = 0; // same object number
            //double prob_spatial  = 0; // same spatial number
            double condition_keyspatial_obj = 0;
            double condition_keyspatial_nobj = 0;
        

        public:
            //set parameter
            Combine(float alpha, float beta, float gamma, float Wth);
            void setProb(std::vector<int> loop[]);
            void resetProb();
            
            double setThreshold();
            //run
            bool run(double keypoint_score, bool object_score, double spatial_score);
            double compute_scoring(double keypoint, bool object, double spatial);
            bool checkLoop(double score, double threshold);
            ~Combine();
    };
}
#endif // COMBINE_HPP