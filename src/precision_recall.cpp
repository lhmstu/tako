#include "tako/precision_recall.hpp"

namespace tako
{
    Vertification::Vertification(int total_image, int compute_loop, float alpha = 0, float beta = 0,float gamma = 0, float Wth = 0)
    {
        total_image_ = total_image;
        compute_loop_ = compute_loop;
        alpha_ = alpha;
        beta_ = beta;
        gamma_ = gamma;
        Wth_ = Wth ;
    }
    void Vertification::main(cv::Mat loop)
    {
        int tp = this->getTP(this->correctLoop(), loop);
        fp = compute_loop_ - tp ; 
        fn = real_loop_ - tp ;
        double precision =  this->getPrecision(tp, fp);
        double recall = this->getRecall(tp, fn);
        if(alpha_ != 0 || beta_ != 0 || Wth_ != 0)
        {
            this->savefile(alpha_, beta_, gamma_, Wth_, precision, recall);
        }
        else
        {
            this->savefile(precision, recall);
        }
    }

    double Vertification::getPrecision(int tp, int fp)
    {
        double precision ; 
        precision = (double)tp /(double)(tp + fp);
        return precision ; 
    }

    double Vertification::getRecall(int tp, int fn)
    {
        double recall;
        recall = (double)tp / (double) (tp + fn);
        return recall ; 
    }

    void Vertification::savefile(float alpha, float beta, float gamma, float Wth, double precision, double recall)
    {
        std::ofstream file;
        file_.open("precision_recall.txt", std::ios::out|std::ios::app);
        if(!file)
        {
            std::cerr << " the file doesn't exist!!" << std::endl;
        }
        else
        {
            file << "Loop closure test ..." << std::endl;
            file << "threshold " << std::endl;
            file << " -keypoint_threshold : " << *thr <<std::endl;
            file << " -object_threshold : " << *(thr + 1) << std::endl;
            file << " -spatial_threshold : " << *(thr + 2) << std::endl;

            file << "final threshold parameter : " << std::endl;
            file << " -alpha:" << alpha <<", "<<"beta:"<<beta <<", "
                <<"gamma:"<<gamma<< "Wth:" << Wth << std::endl;

            file << "Total image : " << total_image_ << std::endl;
            file << "output values ..." << std::endl;
            file << "precision" << "," << "recall" << std::endl;
            file << precision <<","<< recall << std::endl;
        }

        file_.close();

    }

    void Vertification::savefile(double precision, double recall)
    {
        std::ofstream file;
        file_.open("precision_recall.txt", std::ios::out|std::ios::app);
        if(!file)
        {
            std::cerr << " the file doesn't exist!!" << std::endl;
        }
        else
        {
            file << "Loop closure test ..." << std::endl;
            file << "threshold " << std::endl;
            file << " -keypoint_threshold : " << *thr <<std::endl;
            file << " -object_threshold : " << *(thr + 1) << std::endl;
            file << " -spatial_threshold : " << *(thr + 2) << std::endl;

            file << "Total image : " << total_image_ << std::endl;
            file << "output values ..." << std::endl;
            file << "precision" << "," << "recall" << std::endl;
            file << precision <<","<< recall << std::endl;
        }

        file_.close();

    }

    int Vertification::getTP(cv::Mat correct, cv::Mat loop)
    {
        return (int)correct.dot(loop);
        
    }
    // need true positive
    // correct loop 
    cv::Mat Vertification::correctLoop()
    {

    }

    Vertification::~Vertification()
    {

    }

}