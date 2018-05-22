#include "tako/combine.hpp"
namespace tako
{
    Combine::Combine(float alpha = 0, float beta = 0, float gamma = 0, float Wth = 0): alpha(alpha), beta(beta),gamma(gamma), Wth(Wth)
    {

    }

    void Combine::setProb(int total_image, std::vector<int> loop[])
    {
        /*  loop[0] keypoint number
            loop[1] object number 
            loop[2] spatial number
        */
        int keypointLoop = loop[0].size();
        int objectSame = loop[1].size();
        int spatialLoop = loop[2].size();
        prob_key = (double)(keypointLoop) / (double)(total_image);
        prob_obj = (double)(objectSame) / (double)(total_image);
        prob_spatial = prob_key * (double)(spatialLoop * 2) / (double)(total_image * 2);

        int keyspatial_obj = 0;
        for(std::vector<int>::iterator iter_key = loop[0].begin(); iter_key!= loop[0].end(); iter_key++)
        {
            for(std::vector<int>::iterator iter_spa = loop[2].begin(); iter_spa!= loop[2].end(); iter_spa++)
            {
                if( *iter_key == *iter_spa)
                {
                    std::vector<int>::iterator iter_obj = std::find(loop[1].begin(), loop[1].end(), *iter_key);
                    if(iter_obj != loop[1].end())
                    {
                        keyspatial_obj ++;
                    }
                }
            }
        }

        condition_keyspatial_nobj = 0;
        condition_keyspatial_obj = 0;
    }

    void Combine::resetProb()
    {
        prob_key = 0 ;
        prob_obj = 0 ;
        prob_spatial = 0;
        condition_keyspatial_nobj = 0 ;
        condition_keyspatial_obj = 0;
    }
    bool Combine::run(double keypoint_score, bool object_score, float spatial_score)
    {
        if(alpha && beta && gamma && Wth)
        {
            std::cerr<<"Combint init correct!" <<std::endl;
        }
        else
        {
            std::cerr<<"Init error !! Check three parameters is set " <<std::endl;
            exit -1 ;
        }

        std::cerr<<"setting Threshold..." <<std::endl;

        double threshold = this->setThreshold();
        double score = this->compute_scoring(keypoint_score, object_score, spatial_score)

        return this->checkLoop(score, threshold);
    }

    // need setThreshold compute
    double Combine::setThreshold()
    {
        double threshold = 0;
        threshold = (1 - Wth) * condition_keyspatial_nobj + Wth * condition_keyspatial_obj;

        
        return threshold;
    }

    double Combine::compute_scoring(double keypoint, bool object, double spatial )
    {
       double score = 0 ;
       if(object)
       {
         score = (alpha*keypoint) + (beta*spatial) + (gamma*object) ;
       }
       else
       {
           score = (1 - gamma) * keypoint + gamma * spatial;
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
    
    Comine::~Combine()
    {

    }


}