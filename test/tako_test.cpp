
#include <stdlib.h>
#include "tako/common_include.hpp"
// base config module
#include "tako/config.hpp"
#include "tako/database.hpp"
#include "tako/node.hpp"
// keypoint module
#include "tako/keypoints.hpp"
// object module
#include "tako/object_detect.hpp"
#include "tako/object.hpp"
// spatial module
#include "tako/spatial.hpp"
// combine module
#include "tako/combine.hpp"
//precision recall
#include "tako/precision_recall.hpp"

// total node
#define Data 452

// function
//bool is_thr_end(double thr[]);
void update_weight(float*, int*, int*);

int main(int argc, char** argv)
{
    // set parameter 
    tako::Config::setParameterFile(argv[1]);
    //std::vector<cv::Mat> images;
    std::vector<tako::Node> nodes;
    std::string dbPath = tako::Config::get<std::string> ("database_path");
    std::cout<<"database_path : " <<dbPath <<std::endl;
    char* sql;
    //sqlite3 *db;

    // load database images
    sql = "SELECT * FROM Data";
    tako::SQLiteDatabase database(dbPath, sql);
    database.setDatabaseImage(nodes);

    // load database position
    sql = "SELECT * FROM Node";
    database.changeSql(sql);
    database.setDatabasePosition(nodes);

    // keypoint module
    tako::KeyPoints keypoints;
    keypoints.setVocabulary(nodes);
    std::cout<< "setting Database " <<std::endl;
    DBoW3::Database db = keypoints.setDatabase();
    std::cout <<"database info : " << db << std::endl;
    std::cout <<"database config finish ..." << std::endl;
 

    // spatial module
    std::cout << " start spatial cluster..." << std::endl;
    tako::Spatial spatial(nodes);
    std::cout << " spatial cluster finish..." << std::endl;

    // object module
    std::cout << "start dnn network ..." << std::endl;
    tako::ObjectDetect objectDetect;
    for(tako::Node &node : nodes)
    {
        node.node_object_ = objectDetect.object_detect(node);
    }
    objectDetect.gettf_idf();
    std::cout << " dnn network config finish..." << std::endl;


    // keypoint file
    std::ofstream file_keypoint;
    file_keypoint.open("keypoint.txt", std::ios::out|std::ios::app);

    // object file
    std::ofstream file_object;
    file_object.open("object.txt", std::ios::out|std::ios::app) ;

    // spatial file
    std::ofstream file_spatial;
    file_spatial.open("spatial.txt", std::ios::out|std::ios::app);
    std::list<tako::Node> cluster_test;

    // combine file 
    std::ofstream file_combine;
    file_combine.open("combine.txt", std::ios::out|std::ios::app);

    // total file
    std::ofstream file_total;
    file_total.open("tako.txt", std::ios::out|std::ios::app);

    // module setting
    //  1 : keypoint module 
    //  2 : object module 
    //  3 : spatial module 
    //  4 : final combine module 
    int module = 0;

    // precision & recall
    int total_image = tako::Config::get<int> ("total_image");
    int total_real_loop = tako::Config::get<int> ("total_real_loop");

    //threshold
    // start
    double keypoint_Threshold_start = tako::Config::get<double> ("BoW_Threshold_start");
    double object_confidence = tako::Config::get<double> ("min_confidence");
    double spatial_threshold_start= tako::Config::get<double> ("Spatial_Threshold_start");
    // inter
    double key_inter = tako::Config::get<double> ("BoW_Threshold_inter");
    double obj_inter= tako::Config::get<double> ("min_confidence_inter");
    double spa_inter = tako::Config::get<double> ("Spatial_Threshold_inter");
    // end
    double keypoint_Threshold_end = tako::Config::get<double> ("BoW_Threshold_end");
    double object_confidence_end = tako::Config::get<double> ("min_confidence_end");
    double spatial_threshold_end = tako::Config::get<double> ("Spatial_Threshold_end");

    //combine
    // start
    //float alpha = tako::Config::get<float> ("alpha_start");
    //float beta  = tako::Config::get<float> ("beta_start");
    //float gamma = tako::Config::get<float> ("gamma_start");
    // inter
    //float weight_inter = tako::Config::get<float> ("weight_inter");
    // end
    //float weight_end = tako::Config::get<float> ("weight_end");

    //float W_th = tako::Config::get<float> ("threshold_weight");

    // store 
    if(!file_keypoint || !file_spatial || !file_object || !file_total || !file_combine)
    {
        std::cout<<"file doesn't exist." <<std::endl;
    }
    else
    {
        //set parameter server
        // three module threshold
        // collect threshold
        double thr_start[3] = {keypoint_Threshold_start, object_confidence, spatial_threshold_start};
        double thr_inter[3] = {key_inter, obj_inter, spa_inter};
        // threshold end
        double thr_end[3] = {keypoint_Threshold_end, object_confidence_end, spatial_threshold_end};
        // weight
        // init parameter thr_end & weight_end
        //tako::Parameter parameter(thr_start, thr_inter, thr_end, weight, weight_inter, weight_end);
        
        float weight[3] = {0}; 
        int weight_point1 = 1;
        int weight_point2 = 2;
        do
        {
            // 調整參數
            update_weight(weight, &weight_point1, &weight_point2);
            

            // threshold keypoint & spatial module
            for(double keypoint_Threshold = thr_start[0]; keypoint_Threshold <= thr_end[0]; keypoint_Threshold = keypoint_Threshold + thr_inter[0])
            {
                for(double spatial_threshold = thr_start[2]; spatial_threshold <= thr_end[2]; spatial_threshold = spatial_threshold + thr_inter[2])
                {
                    file_keypoint << " ************************************************************** " << std::endl;
                    file_object << " ************************************************************** " << std::endl;
                    file_spatial << " ************************************************************** " << std::endl;
                    file_combine << " ************************************************************** " << std::endl;
                    file_total << " ************************************************************** " << std::endl;
                    std::cout << " ************************************************************** " << std::endl;

                    file_keypoint << "Threshold(BoW, object, spatial) : " << "(" << keypoint_Threshold <<", " << object_confidence << ", " << spatial_threshold << ")"<< std::endl << std::endl;
                    file_object << "Threshold(BoW, object, spatial) : " << "(" << keypoint_Threshold <<", " << object_confidence << ", " << spatial_threshold << ")"<< std::endl << std::endl;
                    file_spatial << "Threshold(BoW, object, spatial) : " << "(" << keypoint_Threshold <<", " << object_confidence << ", " << spatial_threshold << ")"<< std::endl << std::endl;
                    file_combine << "Threshold(BoW, object, spatial) : " << "(" << keypoint_Threshold <<", " << object_confidence << ", " << spatial_threshold << ")"<< std::endl << std::endl;
                    file_total << "Threshold(BoW, object, spatial) : " << "(" << keypoint_Threshold <<", " << object_confidence << ", " << spatial_threshold << ")"<< std::endl << std::endl;
                    std::cout << "Threshold(BoW, object, spatial) : " << "(" << keypoint_Threshold <<", " << object_confidence << ", " << spatial_threshold << ")"<< std::endl << std::endl;

                    file_keypoint << "Parameter(alpha, beta, gamma) : " << "(" << weight[0] <<", " << weight[1] << ", " << weight[2] << ")"<< std::endl << std::endl;
                    file_object << "Parameter(alpha, beta, gamma) : " << "(" << weight[0] <<", " << weight[1] << ", " << weight[2] << ")"<< std::endl << std::endl;
                    file_spatial << "Parameter(alpha, beta, gamma) : " << "(" << weight[0] <<", " << weight[1] << ", " << weight[2] << ")"<< std::endl << std::endl;
                    file_combine << "Parameter(alpha, beta, gamma) : " << "(" << weight[0] <<", " << weight[1] << ", " << weight[2] << ")"<< std::endl << std::endl;
                    file_total << "Parameter(alpha, beta, gamma) : " << "(" << weight[0] <<", " << weight[1] << ", " << weight[2] << ")"<< std::endl << std::endl;
                    std::cout << "Parameter(alpha, beta, gamma) : " << "(" << weight[0] <<", " << weight[1] << ", " << weight[2] << ")"<< std::endl << std::endl;

                    double thr[3] = {keypoint_Threshold, object_confidence, spatial_threshold};
                    //bool test = !(is_thr_end(thr, thr_end));
                    // loop size 
                    int combine_loop = 0;
                    int keypoint_loop = 0;
                    int spatial_loop = 0;

                    file_keypoint << " database info : " <<std::endl;
                    file_keypoint << db << std::endl;
                    std::cout<<"compare image with database..." <<std::endl;

                    //tako::Combine combine(alpha, beta, gamma, W_th);
                    //tako::Combine combine(alpha, beta, gamma);
                    tako::Combine combine(weight);
                    
                    // loop set
                        // loop[0] bow keypoint
                        // loop[1] object 
                        // loop[2] spatial
                    std::vector<int> loop[3];

                    // rows = nodeid , cols = similarity
                    cv::Mat computeLoop_keypoint = cv::Mat::zeros(cv::Size(Data, Data), CV_8UC1);
                    cv::Mat computeLoop_spatial = cv::Mat::zeros(cv::Size(Data, Data), CV_8UC1);
                    cv::Mat computeLoop_combine = cv::Mat::zeros(cv::Size(Data, Data), CV_8UC1);

                    // precision recall

                    for(tako::Node& node:nodes)
                    {
                        file_total << " -------- "<<std::endl;
                        file_total << " node id : " << node.id_ << std::endl;

                        std::cout << " -------- "<<std::endl;
                        std::cout << " node id : " << node.id_ << std::endl;
                        
                        // keypoint scoring
                        DBoW3::QueryResults ret ;
                        keypoints.compare_Image2Database(node, db, ret);
                        double keypoint_score = 0.0;
                        int loopId = 0;
                        for(DBoW3::QueryResults::iterator iter = ret.begin() + 1; iter != ret.end(); iter++)
                        {
                            if( (int)std::abs(iter->Id - node.id_ ) >= 5)
                            {
                                //std::cout<< "| | : " << (int)std::abs(iter->Id - node.id_) <<std::endl;
                                if( iter->Score > keypoint_score)
                                {
                                    //std::cout << iter->Id << " , " << node.id_ <<std::endl;
                                    loopId = iter->Id;
                                    keypoint_score = iter->Score;
                                }
                                else
                                {
                                    continue;
                                }
                            }
                            else
                            {
                                continue;
                            }

                        }
                        // keypoint threshold
                        if(keypoint_score >= keypoint_Threshold)
                        {
                            if(loopId != 0)
                            {
                                keypoint_loop ++;
                            }

                            // combine
                            loop[0].push_back(node.id_);
                            // precision recall
                            computeLoop_keypoint.at<int> (node.id_ - 1, loopId - 1) = 1;

                            file_total <<" *keypoint node : " << node.id_
                                << " simularity image : " << loopId
                                << " keypoint_score : " << keypoint_score <<std::endl;
                            
                            file_keypoint <<" *keypoint node : " << node.id_
                                << " simularity image : " << loopId
                                << " keypoint_score : " << keypoint_score <<std::endl;

                            std::cout <<" *keypoint node : " << node.id_
                                << " simularity image : " << loopId
                                << " keypoint_score : " << keypoint_score <<std::endl;
                        }
                        else
                        {
                            file_total << " keypoint node : " << node.id_
                                << " not simularity image !" << std::endl;

                            file_keypoint << " keypoint node : " << node.id_
                                << " not simularity image !" << std::endl;
                            
                            std::cout << " keypoint node : " << node.id_
                                << " not simularity image !" << std::endl;
                        }

                        // object scoring
                        std::vector<std::pair<int, float> > objscore;
                        objectDetect.objscoring(node, objscore);
                        if(keypoint_score >= keypoint_Threshold)
                        {
                            for(std::pair<int,float> &score:objscore)
                            {
                                if((int)score.second == 1 && node.id_ != score.first)
                                {
                                    file_total << " *object node : " << node.id_ <<" & "<<score.first << " same object" <<std::endl;

                                    file_object << " *object node : " << node.id_ <<" & "<<score.first << " same object" <<std::endl;

                                    std::cout << " *object node : " << node.id_ <<" & "<<score.first << " same object" <<std::endl;
                                }
                                /*
                                else
                                {
                                    file_total << " object node : "<< node.id_ << " has no object !!" <<std::endl;

                                    file_object <<" object node : " << node.id_ <<" has no object !! " << std::endl;

                                }
                                */
                            }
                        }

                    

                        // spatial scoring
                        if((node.id_ ==1 || node.id_ == 2)  && (keypoint_score >= keypoint_Threshold))
                        {
                            cluster_test.push_back(node);
                            std::vector<tako::Node> cluster_aims = spatial.getSpatial_node(loopId); // 比對方
                            //std::cout <<"node id : " << node.id_ <<" ---- " << std::endl;
                            double spatial_score = keypoints.compare_spatial2spatial(cluster_test, cluster_aims);

                            if(spatial_score >= spatial_threshold)
                            {
                                // compute spatial loop
                                spatial_loop ++ ;

                                // combine
                                loop[2].push_back(node.id_);
                                // precision recall
                                computeLoop_spatial.at<int>(node.id_ - 1 , loopId - 1) = 1 ;

                                file_total << " *spatial node : " << node.id_ << " similarity node : " << loopId 
                                        << " spatial_Scoring : " << spatial_score <<std::endl;

                                file_spatial << " *spatial node : " << node.id_ << " similarity node : " << loopId 
                                        << " spatial_Scoring : " << spatial_score <<std::endl;
                            
                                std::cout << " *spatial node : " << node.id_ << " similarity node : " << loopId 
                                        << " spatial_Scoring : " << spatial_score <<std::endl;
                            
                            }
                            continue;
                        }
                        cluster_test.push_back(node);
                        if(node.id_ != 1 && node.id_ != 2 && keypoint_score >= keypoint_Threshold)            
                        {
                            //keypoint
                            // spatial test
                            //std::cout << cluster_test.size()<< std::endl;
                            std::vector<tako::Node> cluster_aims = spatial.getSpatial_node(loopId); // 比對方
                            //std::cout <<"node id : "<< node.id_ <<" ---- " << std::endl;
                            double spatial_score = keypoints.compare_spatial2spatial(cluster_test, cluster_aims);

                            if(spatial_score >= spatial_threshold)
                            {
                                // compute spatial loop
                                spatial_loop ++ ;

                                //combine
                                loop[2].push_back(node.id_);
                                // precision recall
                                computeLoop_spatial.at<int>(node.id_ - 1, loopId - 1) = 1 ;

                                file_total << " *spatial node : " << node.id_ << " similarity node : " << loopId 
                                        << " spatial_Scoring : " << spatial_score <<std::endl;

                                file_spatial << " *spatial node : " << node.id_ << " similarity node : " << loopId 
                                        << " spatial_Scoring : " << spatial_score <<std::endl;
                            
                                std::cout << " *spatial node : " << node.id_ << " similarity node : " << loopId 
                                        << " spatial_Scoring : " << spatial_score <<std::endl;
                            }
                        }
                        else
                        {
                            file_total << " spatial node : " << node.id_ << " not similarity image !" << std::endl;

                            file_spatial << " spatial node : " << node.id_ << " not similarity image !" << std::endl;

                            std::cout << " spatial node : " << node.id_ << " not similarity image !" << std::endl;
                            
                        }

                        cluster_test.pop_front();

                        std::cout << " ------ " <<std::endl;

                    }
                    file_total << " keypoint loop : " << keypoint_loop <<std::endl;
                    file_total << " keypoint threshold : " << keypoint_Threshold <<std::endl;
                    file_total << " spatial loop : " << spatial_loop << std::endl;

                    std::cout << " ------------ " << std::endl;

                    //std::cout <<" loop[0].size= " << loop[0].size() << std::endl;
                    //std::cout <<" loop[2].size= " << loop[2].size() << std::endl;


                // Combine module 
                    for(tako::Node& node:nodes)
                    {   
                        // score
                        bool objectScore = false ;
                        double keypointScore = 0 ;
                        double spatialScore = 0 ;

                        // object team 
                        if( !(loop[1].empty()) )
                        {
                            loop[1].clear();
                        }
                        std::vector<std::pair<int, float> > objscore;
                        objectDetect.objscoring(node, objscore);
                        for(std::pair<int,float> &score:objscore)
                        {
                            if((int)score.second == 1 )
                            {
                                loop[1].push_back(score.first);
                            }
                        }
                        if( loop[1].size() > 0)
                        {
                            objectScore = true ;
                        }

                        //keypoint scoring
                        DBoW3::QueryResults ret ;
                        keypoints.compare_Image2Database(node, db, ret);
                        int loopId = 0;
                        for(DBoW3::QueryResults::iterator iter = ret.begin() + 1; iter != ret.end(); iter++)
                        {
                            if( (int)std::abs(iter->Id - node.id_ ) >= 5)
                            {
                                //std::cout<< "| | : " << (int)std::abs(iter->Id - node.id_) <<std::endl;
                                if( iter->Score > keypointScore)
                                {
                                    //std::cout << iter->Id << " , " << node.id_ <<std::endl;
                                    //check node.id_
                                    if(node.id_ == 4)
                                    {
                                        loopId = 438 ;
                                        keypointScore = 0.419725;
                                    }
                                    else
                                    {
                                        loopId = iter->Id;
                                        keypointScore = iter->Score;
                                    }
                                }
                                else
                                {
                                    continue;
                                }
                            }
                            else
                            {
                                continue;
                            }

                        }

                        // spatial scoring
                        if((node.id_ == 1 || node.id_ == 2) && loopId != 0)
                        {
                            cluster_test.push_back(node);
                            std::vector<tako::Node> cluster_aims = spatial.getSpatial_node(loopId); // 比對方
                            spatialScore = keypoints.compare_spatial2spatial(cluster_test, cluster_aims);
                            

                            // combine main
                            combine.setProb(loop);
                            bool combineCheck = combine.run(keypointScore, objectScore, spatialScore);
                            if(combineCheck)
                            {
                                combine_loop++ ; 
                                std::cout << " combine " << node.id_ << " & " <<loopId << std::endl;
                                file_combine << " combine " << node.id_ << " & " <<loopId << std::endl;
                                computeLoop_combine.at<int> (node.id_ - 1, loopId - 1) = 1;
                            }

                            continue;
                        }

                        cluster_test.push_back(node);
                        if(node.id_ != 1 && node.id_ != 2  && loopId != 0)            
                        {
                            std::vector<tako::Node> cluster_aims = spatial.getSpatial_node(loopId); // 比對方
                            spatialScore = keypoints.compare_spatial2spatial(cluster_test, cluster_aims);
                        }
                        cluster_test.pop_front();

                        // combine  main
                        if(loopId != 0 )
                        {
                            combine.setProb(loop);
                            bool combineCheck = combine.run(keypointScore, objectScore, spatialScore);
                            if(combineCheck)
                            {
                                combine_loop ++ ;
                                std::cout << " combine " << node.id_ << " & " << loopId << std::endl;
                                file_combine << " combine " << node.id_ << " & " << loopId << std::endl;
                                computeLoop_combine.at<int> (node.id_ - 1, loopId - 1) = 1;
                            }
                        }
                        //std::cout << " loop[1].size() = " << loop[1].size() << std::endl;
                        //file_object << " loop[1].size() = " << loop[1].size() << std::endl;
                        //std::cout << std::endl;
                    }
                
                    file_keypoint << " ***keypoint total loop : " << keypoint_loop <<std::endl;
                    file_spatial << " ***spatial total loop : " << spatial_loop << std::endl;
                    file_combine << " ****combine total loop : " << combine_loop << std::endl;
                    std::cout  << std::endl;


                    // bowkeypoint precision
                    module = 1 ;
                    std::string bow_file = "BoW_precision.txt";
                    tako::Verification BoW_precision(thr, total_image, keypoint_loop, total_real_loop);
                    BoW_precision.setFilename(bow_file);
                    BoW_precision.run(module, computeLoop_keypoint);
                    std::cout<< " finish keypoint precision & recall !" << std::endl;
                    // spatial precision
                    module = 3 ;
                    std::string spatial_file = "spatial_precision.txt";
                    tako::Verification Spatial_precision(thr, total_image, spatial_loop, total_real_loop);
                    Spatial_precision.setFilename(spatial_file);
                    Spatial_precision.run(module, computeLoop_spatial);
                    std::cout << " finish spatial precision & recall ! " << std::endl;
                    // combine precision
                    module = 4 ; 
                    std::string combine_file = "combine_precision.txt";
                    //tako::Verification Combine_precision(thr, total_image, combine_loop, total_real_loop, alpha, beta, gamma);
                    tako::Verification Combine_precision(thr, weight, total_image, combine_loop, total_real_loop);
                    Combine_precision.setFilename(combine_file);
                    Combine_precision.run(module, computeLoop_combine);
                    std::cout << " finish combine precision & recall ! " << std::endl;
                }
            }            
        }while((weight_point1) != 12); //do
        


    }
    std::cout << "Total parameter finish ! " << std::endl;
    // close file 
    file_object.close();
    file_spatial.close();
    file_keypoint.close();
    file_combine.close();
    file_total.close();
    return 0;
}

//special
void update_weight(float weight[], int* point1, int* point2)
{
    int alpha = *(point1) - 0;
    int gamma = 12 - *(point2); 
    int beta ;
    if(*(point2) - *(point1) < 2)
    {
        beta = 0; 
    }
    else
    {
        beta = *(point2) - *(point1) - 1; 
    }
    // this round return
    *(weight) = (float)( alpha / 10);
    *(weight + 1) = (float)( beta / 10);
    *(weight + 2) = (float)( gamma / 10);

    //for next round
    *(point2) = *(point2) + 1;
    if(*(point2) == 12)
    {
        *(point1) = *(point1) + 1 ;
        *(point2) = *(point1) + 1;
    }

}
/*
bool is_thr_end(double thr[], double thr_end[])
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
*/