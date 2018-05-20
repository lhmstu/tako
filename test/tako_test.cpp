
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
    file_keypoint.open("keypoint.txt", std::ios::out|std::ios::trunc);
    int keypoin_loop = 0;

    // object file
    std::ofstream file_object;
    file_object.open("object.txt", std::ios::out|std::ios::trunc) ;

    // spatial file
    std::ofstream file_spatial;
    file_spatial.open("spatial.txt", std::ios::out|std::ios::trunc);
    std::list<tako::Node> cluster_test;
    int spatial_loop = 0;

    // total file
    std::ofstream file_total;
    file_total.open("tako.txt", std::ios::out|std::ios::trunc);
    // store 

    
    
    if(!file_keypoint || !file_spatial || !file_object || !file_total)
    {
        std::cout<<"file doesn't exist." <<std::endl;
    }
    else
    {
        // keypoint threshold
        double keypoint_Threshold = tako::Config::get<double> ("BoW_threshold");
        file_keypoint << "database info : " <<std::endl;
        file_keypoint << db << std::endl;
        std::cout<<"compare image with database..." <<std::endl;

        // spatial threshold
        double spatial_threshold = tako::Config::get<double> ("Spatial_threshold");

        // object threshold
        double object_confidence = tako::Config::get<double> ("min_confidence");

        for(tako::Node& node:nodes)
        {
            file_total << " -------- "<<std::endl;
            file_total << "node id : " << node.id_ << std::endl;

            std::cout << " -------- "<<std::endl;
            std::cout << "node id : " << node.id_ << std::endl;
            
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
                    keypoin_loop ++;
                }
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
                    else
                    {
                        file_total << " object node : "<< node.id_ << " has no object !!" <<std::endl;

                        file_object <<" object node : " << node.id_ <<" has no object !! " << std::endl;

                    }
                }
            }

        

            // spatial scoring
            if((node.id_ ==1 || node.id_ == 2)  && (keypoint_score >= keypoint_Threshold))
            {
                cluster_test.push_back(node);
                std::vector<tako::Node> cluster_aims = spatial.getSpatial_node(loopId); // 比對方
                //std::cout <<"node id : " << node.id_ <<" ---- " << std::endl;
                double spatial_Score = keypoints.compare_spatial2spatial(cluster_test, cluster_aims);

                file_total << " *spatial node : " << node.id_ << " similarity node : " << loopId 
                           << " spatial_Scoring : " << spatial_Score <<std::endl;

                file_spatial << " *spatial node : " << node.id_ << " similarity node : " << loopId 
                           << " spatial_Scoring : " << spatial_Score <<std::endl;
                
                std::cout << " *spatial node : " << node.id_ << " similarity node : " << loopId 
                           << " spatial_Scoring : " << spatial_Score <<std::endl;
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
                double spatial_Score = keypoints.compare_spatial2spatial(cluster_test, cluster_aims);

                file_total << " *spatial node : " << node.id_ << " similarity node : " << loopId 
                           << " spatial_Scoring : " << spatial_Score <<std::endl;

                file_spatial << " *spatial node : " << node.id_ << " similarity node : " << loopId 
                           << " spatial_Scoring : " << spatial_Score <<std::endl;
                
                std::cout << " *spatial node : " << node.id_ << " similarity node : " << loopId 
                           << " spatial_Scoring : " << spatial_Score <<std::endl;
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
        file_total << " keypoint loop : " << keypoin_loop <<std::endl;
        file_total << " keypoint threshold : " << keypoint_Threshold <<std::endl;

        file_keypoint << " keypoint loop : " << keypoin_loop <<std::endl;
        std::cout << " keypoint loop : " << keypoin_loop <<std::endl;
        std::cout << " keypoint threshold : " << keypoint_Threshold <<std::endl;
    }
    // close file 
    file_object.close();
    file_spatial.close();
    file_keypoint.close();
    file_total.close();
    return 0;
}