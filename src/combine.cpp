#include "tako/combine.hpp"
namespace tako
{
    Combine::Combine(float alpha = 0, float beta = 0, float gamma = 0, float Wth = 0): alpha(alpha), beta(beta),gamma(gamma), Wth(Wth)
    {

    }

    void Combine::setProb(std::vector<int> loop[])
    {
        /*  loop[0] keypoint number
            loop[1] object number 
            loop[2] spatial number
        */
        //int keypointLoop_ = loop[0].size();
        //int objectSame_ = loop[1].size();
        //int spatialLoop_ = loop[2].size();
        //prob_key = (double)(keypointLoop_) / (double)(total_image);
        //prob_obj = (double)(objectSame_) / (double)(total_image);
        //prob_spatial = prob_key * (double)(spatialLoop_ * 2) / (double)(total_image * 2);

        int keyspatial_obj_ = 0;
        int keyspatial_nobj_ = 0;
        int keyspatial_ = 0;
        for(std::vector<int>::iterator iter_key = loop[0].begin(); iter_key!= loop[0].end(); iter_key++)
        {
            std::vector<int>::iterator iter_spa = std::find(loop[2].begin(), loop[2].end(), *iter_key);
            if(iter_spa != loop[2].end())
            {
                std::vector<int>::iterator iter_obj = std::find(loop[1].begin(), loop[1].end(), *iter_key);
                if(iter_obj != loop[1].end())
                {
                    keyspatial_obj_ ++;
                }
                else
                {
                    keyspatial_nobj_ ++;
                }
                keyspatial_ ++;
            }
        }
        condition_keyspatial_nobj = (double)keyspatial_nobj_/(double)keyspatial_;
        condition_keyspatial_obj = (double)keyspatial_obj_/(double)keyspatial_;
        std::cout << " --keyspatial : " << keyspatial_ << std::endl;
        std::cout << " --keyspatial_nobj : " << keyspatial_nobj_ << std::endl;
        std::cout << " --keyspatial_obj : " << keyspatial_obj_ << std::endl;
        std::cout << " --condition_nobj : " << condition_keyspatial_nobj << std::endl;
        std::cout << " --condition_obj : " << condition_keyspatial_obj << std::endl;
    }

    void Combine::resetProb()
    {
        //prob_key = 0 ;
        //prob_obj = 0 ;
        //prob_spatial = 0;
        condition_keyspatial_nobj = 0 ;
        condition_keyspatial_obj = 0;
    }
    // main run 
    bool Combine::run(double keypoint_score, bool object_score, double spatial_score)
    {
        if(alpha && beta && gamma && Wth)
        {
            //std::cerr<<"Combint init correct...." <<std::endl;
        }
        else
        {
            std::cerr<<"Init error !! Check three parameters is set " <<std::endl;
        }

        //std::cerr<<" setting Threshold..." <<std::endl;

        double threshold = this->setThreshold();
        double score = this->compute_scoring(keypoint_score, object_score, spatial_score);
        //bool check  = this->checkLoop(score, threshold);

        return this->checkLoop(score, threshold);
    }

    // need setThreshold compute
    double Combine::setThreshold()
    {
        double threshold = 0;
        threshold = (1 - Wth) * condition_keyspatial_nobj + Wth * condition_keyspatial_obj;
        std::cout << " -combine threshold : " << threshold << std::endl;

        
        return threshold;
    }

    double Combine::compute_scoring(double keypoint, bool object, double spatial )
    {
       double score = 0 ;
       if(object)
       {
            score = (alpha*keypoint) + (beta*spatial) + (gamma*object) ;
            std::cout << " -obj combine score : " << score << std::endl;
       }
       else
       {
            score = (alpha / (alpha + beta)) * keypoint + (beta / (alpha + beta))* spatial;
            std::cout << " -nobj combine score : " << score << std::endl;
       }

       return score ;
    }

    bool Combine::checkLoop(double score, double threshold)
    {
        if(score > threshold)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    
    Combine::~Combine()
    {

    }


}