
#include <stdlib.h>
#include "tako/common_include.hpp"
#include "tako/config.hpp"
#include "tako/database.hpp"
#include "tako/node.hpp"
#include "tako/keypoints.hpp"
#include "tako/object.hpp"
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

    // keypoint
    tako::KeyPoints keypoints;
    keypoints.setVocabulary(nodes);
    std::cout<< "setting Database " <<std::endl;
    DBoW3::Database db = keypoints.setDatabase();
    std::cout <<"database info : " << db << std::endl;
    //tako::Node temp; 
    /*for(std::vector<tako::Node>::iterator iter = nodes.begin(); iter!= nodes.end();++iter)
    {
        if(iter == nodes.begin())
        {
            temp = (*iter);
        }
        else
        {
           std::cout<<"simuliarity about "
                    <<temp.id_
                    <<" vs "
                    <<iter->id_
                    <<" score : "
                    <<keypoints.compare_Image2Image(temp, *iter)
                    <<std::endl;
        }
        temp = (*iter);
    }*/
    // keypoint
    std::ofstream file_keypoint;
    file_keypoint.open("keypoint.txt", std::ios::out|std::ios::trunc);

    // spatial
    tako::Spatial spatial(nodes);
    std::ofstream file_spatial;
    file_spatial.open("spatial.txt", std::ios::out|std::ios::trunc);
    std::list<tako::Node> cluster_test;
    int spatial_loop = 0;
    
    if(!file_keypoint)
    {
        std::cout<<"file doesn't exist." <<std::endl;
    }
    else
    {
        // threshold
        double BoW_Threshold = tako::Config::get<double> ("BoW_threshold");
        file_keypoint << "database info : " <<std::endl;
        file_keypoint << db << std::endl;
        std::cout<<"compare image with database..." <<std::endl;
        int total_loop = 0;
        for(tako::Node& node:nodes)
        {
            // keypoint test
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
            //spatial
            if(keypoint_score >= BoW_Threshold)
            {
                if(loopId != 0)
                {
                    total_loop ++;
                }
                file_keypoint <<" image id : " << node.id_
                       << " simularity image : " << loopId
                       << " keypoint_score : " << keypoint_score <<std::endl;
            }
            else
            {
                file_keypoint << " image id : " << node.id_
                       << " not simularity image !" << std::endl;
            }

            if(node.id_ ==1 || node.id_ == 2  && keypoint_score >= BoW_Threshold)
            {
                cluster_test.push_back(node);
                std::vector<tako::Node> cluster_aims = spatial.getSpatial_node(loopId); // 比對方
                std::cout <<"node id : " << node.id_ <<" ---- " << std::endl;
                double spatial_Score = keypoints.compare_spatial2spatial(cluster_test, cluster_aims);
                file_spatial << "the node : " << node.id_ << " similarity node : " << loopId 
                           << " spatial_Scoring : " << spatial_Score <<std::endl;
                continue;
            }

            cluster_test.push_back(node);
            if(node.id_ !=1 && node.id_ != 2 && keypoint_score >= BoW_Threshold)            
            {
                //keypoint
                // spatial test
                //std::cout << cluster_test.size()<< std::endl;
                std::vector<tako::Node> cluster_aims = spatial.getSpatial_node(loopId); // 比對方
                std::cout <<"node id : "<< node.id_ <<" ---- " << std::endl;
                double spatial_Score = keypoints.compare_spatial2spatial(cluster_test, cluster_aims);
                file_spatial << "the node : " << node.id_ << " similarity node : " << loopId 
                           << " spatial_Scoring : " << spatial_Score <<std::endl;
            }
            cluster_test.pop_front();
        }
        file_keypoint << " keypoint total_loop : " << total_loop<<std::endl;
        std::cout << " threshold : " << BoW_Threshold <<std::endl;
    }
    file_spatial.close();

    file_keypoint.close();
    return 0;
}