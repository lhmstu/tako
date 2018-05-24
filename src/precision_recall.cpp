#include "tako/precision_recall.hpp"

namespace tako
{
    Verification::Verification(double* thr, int total_image, int compute_loop, int real_loop)
    {
        thr_ = thr ;
        total_image_ = total_image;
        compute_loop_ = compute_loop;
        real_loop_ = real_loop;
    }
    Verification::Verification(double* thr, int total_image, int compute_loop, int real_loop, float alpha = 0, float beta = 0,float gamma = 0, float Wth = 0)
    {
        thr_ = thr ;
        total_image_ = total_image;
        compute_loop_ = compute_loop;
        real_loop_ = real_loop;
        alpha_ = alpha;
        beta_ = beta;
        gamma_ = gamma;
        Wth_ = Wth ;
    }
    void Verification::run(int module, cv::Mat computeLoop)
    {
        std::cerr << " start module " << module << "precision & recall ! " << std::endl;
        module_ = module ;
        int tp = this->getTP(this->correctLoop(), computeLoop);
        std::cerr << " tp : " << tp << std::endl;
        int fp = compute_loop_ - tp ; 
        int fn = real_loop_ - tp ;
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

    double Verification::getPrecision(int tp, int fp)
    {
        double precision ; 
        precision = (double)tp /(double)(tp + fp);
        return precision ; 
    }

    double Verification::getRecall(int tp, int fn)
    {
        double recall;
        recall = (double)tp / (double) (tp + fn);
        return recall ; 
    }

    void Verification::savefile(float alpha, float beta, float gamma, float Wth, double precision, double recall)
    {
        std::ofstream file_;
        file_.open("precision_recall.txt", std::ios::out|std::ios::app);
        if(!file_)
        {
            std::cerr << " the file doesn't exist!!" << std::endl;
        }
        else
        {
            if(module_ == 4)
            {
                file_ << "module : Final combine " << std::endl;
            }
            file_ << "Loop closure test ..." << std::endl;
            file_ << "threshold " << std::endl;
            file_ << " -keypoint_threshold : " << *thr_ <<std::endl;
            file_ << " -object_threshold : " << *(thr_ + 1) << std::endl;
            file_ << " -spatial_threshold : " << *(thr_ + 2) << std::endl;

            file_ << "final threshold parameter : " << std::endl;
            file_ << " -alpha: " << alpha <<", "<<"beta: "<<beta <<", "
                <<"gamma: "<<gamma<< ", Wth: " << Wth << std::endl;
            file_ << std::endl;

            file_ << "Total image : " << total_image_ << std::endl;
            file_ << "output values ..." << std::endl;
            file_ << "precision" << "," << "recall" << std::endl;
            file_ << precision <<","<< recall << std::endl;
            file_ << std::endl;
        }

        file_.close();

    }

    void Verification::savefile(double precision, double recall)
    {
        std::ofstream file_;
        file_.open("precision_recall.txt", std::ios::out|std::ios::app);
        if(!file_)
        {
            std::cerr << " the file doesn't exist!!" << std::endl;
        }
        else
        {
            if(module_ == 1)
            {
                file_ << "module : BoW keypoint " << std::endl;
            }
            if(module_ == 3)
            {
                file_ << "module : Spatial descriptor " << std::endl;
            }
            file_ << "Loop closure test ..." << std::endl;
            file_ << "threshold " << std::endl;
            file_ << " -keypoint_threshold : " << *thr_ <<std::endl;
            file_ << " -object_threshold : " << *(thr_ + 1) << std::endl;
            file_ << " -spatial_threshold : " << *(thr_ + 2) << std::endl;
            file_ << std::endl;

            file_ << "Total image : " << total_image_ << std::endl;
            file_ << "output values ..." << std::endl;
            file_ << "precision" << "," << "recall" << std::endl;
            file_ << precision <<","<< recall << std::endl;
            file_ << std::endl;
        }

        file_.close();

    }

    int Verification::getTP(cv::Mat correct, cv::Mat loop)
    {
        cv::Mat dst;
        cv::multiply(correct, loop, dst);
        int sum = cv::sum(dst)[0];
        return sum;
        
    }
    // need true positive
    // correct loop 
    cv::Mat Verification::correctLoop()
    {
        // rows = nodeid , cols = similarity
        cv::Mat correctLoop = cv::Mat::zeros(cv::Size(Data, Data), CV_8UC1);
        for(int i = 0; i < correctLoop.rows; i++)
        {
            switch(i + 1)
            {
                case 1 :
                    correctLoop.at<int>(i, 8 - 1) = 1 ;
                    break;
                case 2 :
                    correctLoop.at<int>(i, 9 - 1) = 1 ;
                    break;
                case 3 :
                    correctLoop.at<int>(i, 11 - 1) = 1 ;
                    break;
                case 4 :
                    correctLoop.at<int>(i, 10 - 1) = 1 ;
                    break;
                case 5 :
                    correctLoop.at<int>(i, 11 - 1) = 1 ;
                    break;
                case 6 :
                    correctLoop.at<int>(i, 12 - 1) = 1 ;
                    break;
                case 7 :
                    correctLoop.at<int>(i, 12 - 1) = 1 ;
                    break;
                case 14 :
                    correctLoop.at<int>(i, 437 - 1) = 1 ;
                    break;
                case 19 :
                    correctLoop.at<int>(i, 26 - 1) = 1 ;
                    break;
                case 20 :
                    correctLoop.at<int>(i, 25 - 1) = 1 ;
                    break;
                case 21 :
                    correctLoop.at<int>(i, 27 - 1) = 1 ;
                    break;
                case 22 :
                    correctLoop.at<int>(i, 27 - 1) = 1 ;
                    break;
                case 23 :
                    correctLoop.at<int>(i, 28 - 1) = 1 ;
                    break;
                case 28 :
                    correctLoop.at<int>(i, 438 - 1) = 1 ;
                    break;
                case 29 :
                    correctLoop.at<int>(i, 416 - 1) = 1 ;
                    break;
                case 31 :
                    correctLoop.at<int>(i, 420 - 1) = 1 ;
                    break;
                case 126 :
                    correctLoop.at<int>(i, 131 - 1) = 1 ;
                    break;
                case 174 :
                    correctLoop.at<int>(i, 180 - 1) = 1 ;
                    break;
                case 175 :
                    correctLoop.at<int>(i, 180 - 1) = 1 ;
                    break;
                case 176 :
                    correctLoop.at<int>(i, 181 - 1) = 1 ;
                    break;
                case 177 :
                    correctLoop.at<int>(i, 182 - 1) = 1 ;
                    break;
                case 178 :
                    correctLoop.at<int>(i, 183 - 1) = 1 ;
                    break;
                case 179 :
                    correctLoop.at<int>(i, 184 - 1) = 1 ;
                    break;
                case 180 :
                    correctLoop.at<int>(i, 185 - 1) = 1 ;
                    break;
                case 181 :
                    correctLoop.at<int>(i, 186 - 1) = 1 ;
                    break;
                case 192 :
                    correctLoop.at<int>(i, 198 - 1) = 1 ;
                    break;
                case 193 :
                    correctLoop.at<int>(i, 200 - 1) = 1 ;
                    break;
                case 194 :
                    correctLoop.at<int>(i, 199 - 1) = 1 ;
                    break;
                case 195 :
                    correctLoop.at<int>(i, 200 - 1) = 1 ;
                    break;
                case 196 :
                    correctLoop.at<int>(i, 201 - 1) = 1 ;
                    break;
                case 197 :
                    correctLoop.at<int>(i, 202 - 1) = 1 ;
                    break;
                case 423 :
                    correctLoop.at<int>(i, 429 - 1) = 1 ;
                    break;
                case 424 :
                    correctLoop.at<int>(i, 429 - 1) = 1 ;
                    break;
                case 425 :
                    correctLoop.at<int>(i, 431 - 1) = 1 ;
                    break;
                case 426 :
                    correctLoop.at<int>(i, 431 - 1) = 1 ;
                    break;
                // 0.09
                case 24 :
                    correctLoop.at<int>(i, 438 - 1) = 1 ;
                    break;
                case 25 :
                    correctLoop.at<int>(i, 438 - 1) = 1 ;
                    break;
                case 26 :
                    correctLoop.at<int>(i, 438 - 1) = 1 ;
                    break;
                case 27 :
                    correctLoop.at<int>(i, 438 - 1) = 1 ;
                    break;
                case 41 :
                    correctLoop.at<int>(i, 46 - 1) = 1 ;
                    break;
                case 133 :
                    correctLoop.at<int>(i, 138 - 1) = 1 ;
                    break;
                case 134 :
                    correctLoop.at<int>(i, 139 - 1) = 1 ;
                    break;
                case 151 :
                    correctLoop.at<int>(i, 156 - 1) = 1 ;
                    break;
                case 154 :
                    correctLoop.at<int>(i, 159 - 1) = 1 ;
                    break;
                case 173 :
                    correctLoop.at<int>(i, 180 - 1) = 1 ;
                    break;
                case 182 :
                    correctLoop.at<int>(i, 187 - 1) = 1 ;
                    break;
                case 183 :
                    correctLoop.at<int>(i, 188 - 1) = 1 ;
                    break;
                case 237 :
                    correctLoop.at<int>(i, 242 - 1) = 1 ;
                    break;
                case 248 :
                    correctLoop.at<int>(i, 254 - 1) = 1 ;
                    break;
                case 418 :
                    correctLoop.at<int>(i, 434 - 1) = 1 ;
                    break;
                case 419 :
                    correctLoop.at<int>(i, 435 - 1) = 1 ;
                    break;
                case 433 :
                    correctLoop.at<int>(i, 439 - 1) = 1 ;
                    break;
                // 0.07
                case 10 :
                    correctLoop.at<int>(i, 418 - 1) = 1 ;
                    break;
                case 11 :
                    correctLoop.at<int>(i, 435 - 1) = 1 ;
                    break;
                case 18 :
                    correctLoop.at<int>(i, 433 - 1) = 1 ;
                    break;
                case 38 :
                    correctLoop.at<int>(i, 43 - 1) = 1 ;
                    break;
                case 40 :
                    correctLoop.at<int>(i, 45 - 1) = 1 ;
                    break;
                case 55 :
                    correctLoop.at<int>(i, 60 - 1) = 1 ;
                    break;
                case 56 :
                    correctLoop.at<int>(i, 61 - 1) = 1 ;
                    break;
                case 58 :
                    correctLoop.at<int>(i, 63 - 1) = 1 ;
                    break;
                case 61 :
                    correctLoop.at<int>(i, 66 - 1) = 1 ;
                    break;
                case 79 :
                    correctLoop.at<int>(i, 84 - 1) = 1 ;
                    break;
                case 81 :
                    correctLoop.at<int>(i, 86 - 1) = 1 ;
                    break;
                case 86 :
                    correctLoop.at<int>(i, 91 - 1) = 1 ;
                    break;
                case 124 :
                    correctLoop.at<int>(i, 129 - 1) = 1 ;
                    break;
                case 128 :
                    correctLoop.at<int>(i, 133 - 1) = 1 ;
                    break;
                case 136 :
                    correctLoop.at<int>(i, 141 - 1) = 1 ;
                    break;
                case 138 :
                    correctLoop.at<int>(i, 143 - 1) = 1 ;
                    break;
                case 139 :
                    correctLoop.at<int>(i, 144 - 1) = 1 ;
                    break;
                case 141 :
                    correctLoop.at<int>(i, 146 - 1) = 1 ;
                    break;
                case 143 :
                    correctLoop.at<int>(i, 150 - 1) = 1 ;
                    break;
                case 144 :
                    correctLoop.at<int>(i, 150 - 1) = 1 ;
                    break;
                case 145 :
                    correctLoop.at<int>(i, 150 - 1) = 1 ;
                    break;
                case 148 :
                    correctLoop.at<int>(i, 153 - 1) = 1 ;
                    break;
                case 150 :
                    correctLoop.at<int>(i, 156 - 1) = 1 ;
                    break;
                case 152 :
                    correctLoop.at<int>(i, 158 - 1) = 1 ;
                    break;
                case 153 :
                    correctLoop.at<int>(i, 159 - 1) = 1 ;
                    break;
                case 155 :
                    correctLoop.at<int>(i, 160 - 1) = 1 ;
                    break;
                case 190 :
                    correctLoop.at<int>(i, 197 - 1) = 1 ;
                    break;
                case 191 :
                    correctLoop.at<int>(i, 200 - 1) = 1 ;
                    break;
                case 198 :
                    correctLoop.at<int>(i, 203 - 1) = 1 ;
                    break;
                case 236 :
                    correctLoop.at<int>(i, 241 - 1) = 1 ;
                    break;
                case 238 :
                    correctLoop.at<int>(i, 243 - 1) = 1 ;
                    break;
                case 264 :
                    correctLoop.at<int>(i, 275 - 1) = 1 ;
                    break;
                case 269 :
                    correctLoop.at<int>(i, 274 - 1) = 1 ;
                    break;
                case 275 :
                    correctLoop.at<int>(i, 280 - 1) = 1 ;
                    break;
                case 277 :
                    correctLoop.at<int>(i, 282 - 1) = 1 ;
                    break;
                case 287 :
                    correctLoop.at<int>(i, 292 - 1) = 1 ;
                    break;
                case 290 :
                    correctLoop.at<int>(i, 295 - 1) = 1 ;
                    break;
                case 305 :
                    correctLoop.at<int>(i, 310 - 1) = 1 ;
                    break;
                case 327 :
                    correctLoop.at<int>(i, 332 - 1) = 1 ;
                    break;
                case 346 :
                    correctLoop.at<int>(i, 351 - 1) = 1 ;
                    break;
                case 352 :
                    correctLoop.at<int>(i, 357 - 1) = 1 ;
                    break;
                case 353 :
                    correctLoop.at<int>(i, 358 - 1) = 1 ;
                    break;
                case 365 :
                    correctLoop.at<int>(i, 370 - 1) = 1 ;
                    break;
                case 366 :
                    correctLoop.at<int>(i, 371 - 1) = 1 ;
                    break;
                case 367 :
                    correctLoop.at<int>(i, 372 - 1) = 1 ;
                    break;
                case 370 :
                    correctLoop.at<int>(i, 375 - 1) = 1 ;
                    break;
                case 379 :
                    correctLoop.at<int>(i, 384 - 1) = 1 ;
                    break;
                case 393 :
                    correctLoop.at<int>(i, 398 - 1) = 1 ;
                    break;
                case 414 :
                    correctLoop.at<int>(i, 438 - 1) = 1 ;
                    break;
                case 415 :
                    correctLoop.at<int>(i, 438 - 1) = 1 ;
                    break;
                case 416 :
                    correctLoop.at<int>(i, 438 - 1) = 1 ;
                    break;
                case 417 :
                    correctLoop.at<int>(i, 438 - 1) = 1 ;
                    break;
                // 0.05
                case 8 :
                    correctLoop.at<int>(i , 414 - 1) = 1 ;
                    break;
                case 9 :
                    correctLoop.at<int>(i , 435 - 1) = 1 ;
                    break;
                case 12 :
                    correctLoop.at<int>(i , 414 - 1) = 1 ;
                    break;
                case 13 :
                    correctLoop.at<int>(i , 435 - 1) = 1 ;
                    break;
                case 44 :
                    correctLoop.at<int>(i , 447 - 1) = 1 ;
                    break;
                case 94 :
                    correctLoop.at<int>(i , 99 - 1) = 1 ;
                    break;
                case 159 :
                    correctLoop.at<int>(i , 164 - 1) = 1 ;
                    break;
                case 161 :
                    correctLoop.at<int>(i , 166 - 1) = 1 ;
                    break;
                case 189 :
                    correctLoop.at<int>(i , 198 - 1) = 1 ;
                    break;
                case 199 :
                    correctLoop.at<int>(i , 204 - 1) = 1 ;
                    break;
                case 239 :
                    correctLoop.at<int>(i , 244 - 1) = 1 ;
                    break;
                case 278 :
                    correctLoop.at<int>(i , 283 - 1) = 1 ;
                    break;
                case 279 :
                    correctLoop.at<int>(i , 284 - 1) = 1 ;
                    break;
                case 295 :
                    correctLoop.at<int>(i , 300 - 1) = 1 ;
                    break;
                case 345 :
                    correctLoop.at<int>(i , 350 - 1) = 1 ;
                    break;
                case 368 :
                    correctLoop.at<int>(i , 368 - 1) = 1 ;
                    break;
                case 369 :
                    correctLoop.at<int>(i , 374 - 1) = 1 ;
                    break;
                case 391 :
                    correctLoop.at<int>(i , 396 - 1) = 1 ;
                    break;
                case 412 :
                    correctLoop.at<int>(i , 433 - 1) = 1 ;
                    break;
                case 413 :
                    correctLoop.at<int>(i , 438 - 1) = 1 ;
                    break;
                case 446 :
                    correctLoop.at<int>(i , 451 - 1) = 1 ;
                    break;
                case 32 :
                    correctLoop.at<int>(i , 445 - 1) = 1 ;
                    break;
                case 35 :
                    correctLoop.at<int>(i , 446 - 1) = 1 ;
                    break;
                case 42 :
                    correctLoop.at<int>(i , 447 - 1) = 1 ;
                    break;
                case 214 :
                    correctLoop.at<int>(i , 221 - 1) = 1 ;
                    break;
                case 226 :
                    correctLoop.at<int>(i , 251 - 1) = 1 ;
                    break;
                case 233 :
                    correctLoop.at<int>(i , 238 - 1) = 1 ;
                    break;
                case 258 :
                    correctLoop.at<int>(i , 263 - 1) = 1 ;
                    break;
                case 297 :
                    correctLoop.at<int>(i , 302 - 1) = 1 ;
                    break;
                case 298 :
                    correctLoop.at<int>(i , 303 - 1) = 1 ;
                    break;
                case 317 :
                    correctLoop.at<int>(i , 322 - 1) = 1 ;
                    break;
                case 318 :
                    correctLoop.at<int>(i , 323 - 1) = 1 ;
                    break;
                case 392 :
                    correctLoop.at<int>(i , 397 - 1) = 1 ;
                    break;
                case 410 :
                    correctLoop.at<int>(i , 415 - 1) = 1 ;
                    break;
                // 0.03
                case 33 :
                    correctLoop.at<int>(i, 447 - 1) = 1 ;
                    break;
                case 34 :
                    correctLoop.at<int>(i, 450 - 1) = 1 ;
                    break;
                case 74 :
                    correctLoop.at<int>(i, 79 - 1) = 1 ;
                    break;
                case 162 :
                    correctLoop.at<int>(i, 167 - 1) = 1 ;
                    break;
                case 163 :
                    correctLoop.at<int>(i, 168 - 1) = 1 ;
                    break;
                case 200 :
                    correctLoop.at<int>(i, 205 - 1) = 1 ;
                    break;
                case 204 :
                    correctLoop.at<int>(i, 209 - 1) = 1 ;
                    break;
                case 249 :
                    correctLoop.at<int>(i, 256 - 1) = 1 ;
                    break;
                case 294 :
                    correctLoop.at<int>(i, 299 - 1) = 1 ;
                    break;
                case 349 :
                    correctLoop.at<int>(i, 399 - 1) = 1 ;
                    break;
                case 445 :
                    correctLoop.at<int>(i, 451 - 1) = 1 ;
                    break;
                case 30 :
                    correctLoop.at<int>(i, 437 - 1) = 1 ;
                    break;
                case 201 :
                    correctLoop.at<int>(i, 206 - 1) = 1 ;
                    break;
                case 202 :
                    correctLoop.at<int>(i, 207 - 1) = 1 ;
                    break;
                case 203 :
                    correctLoop.at<int>(i, 209 - 1) = 1 ;
                    break;
                case 272 :
                    correctLoop.at<int>(i, 280 - 1) = 1 ;
                    break;
                case 409 :
                    correctLoop.at<int>(i, 433 - 1) = 1 ;
                    break;
                case 411 :
                    correctLoop.at<int>(i, 433 - 1) = 1 ;
                    break;
            }
        }
        return correctLoop ;
    }

    Verification::~Verification()
    {

    }

}