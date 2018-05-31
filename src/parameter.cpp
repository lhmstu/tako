#include "tako/parameter.hpp"

namespace tako
{
    /*
    Parameter::Parameter(double key_thr_end,
                        double obj_thr_end,
                        double spa_thr_end,
                        float alpha_end,
                        float beta_end,
                        float gamma_end) 
    {   
        key_thr_end_ = key_thr_end ;
        obj_thr_end_ = obj_thr_end ; 
        spa_thr_end_ = spa_thr_end ; 
        alpha_end_ = alpha_end;
        beta_end_ = beta_end;
        gamma_end_ = gamma_end;
    }
    */
    Parameter::Parameter(
                        double thr[],
                        double thr_inter[],
                        double thr_end[],
                        float weight[],
                        float weight_inter,
                        float weight_end)
    {
        thr_ = thr;
        thr_inter_ = thr_inter;
        thr_end_ = thr_end;
        weight_ = weight;
        weight_inter_ = weight_inter;
        weight_end_ = weight_end;
    }

    Parameter::~Parameter()
    {

    }
/*
    double* Parameter::change_threshold(double thr[])
    {
        switch(init)
        {
            case 1:
                if(thr[0] == thr_end_[0])
                {
                    init++;
                    thr[0] = thr_start_[0] ;
                }
                else
                {
                    *(thr) = *(thr) + *(thr_inter_);
                    return thr;
                }
            case 2:
                if(thr_start[2] == thr_end_[2])
                {
                    init++;
                    return thr;
                }
                else
                {
                    *(thr + 2) = *(thr + 2) + *(thr_inter_ + 2);
                    init = 1 ;
                    return thr;
                }
                break;
            default:
                init ++ ;
                return thr;
                break;
        }
    }

    void Parameter::reset(double thr_start[])
    {
        init = 0;
        *thr_start = *thr;
        *(thr_start + 1) = *(thr + 1);
        *(thr_start + 2) = *(thr + 2);
    }
*/
    float* Parameter::update_weight(float weight[], float weight_inter)
    {
        bool check = this->check_weight(weight[0], weight[1], weight[2]);
        if(check)
        {

        }
        else
        {
            
        }
    }
    bool Parameter::is_thr_end(double thr[])
    {
        if(thr[0] == thr_end[0] && thr[1] == thr_end[1] && thr[2] == thr_end[2])
        {
            return true ;
        }
        else
        {
            return false ;
        }
    }

    bool Parameter::check_weight(float alpha, float beta, float gamma)
    {
        int total = (int)(alpha + beta + gamma) ;
        if( total == 1 )
        {
            return true;
        }
        else
        {
            return false;
        }
    }

}