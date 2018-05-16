
#include <stdlib.h>
#include "tako/common_include.hpp"
#include "tako/config.hpp"
#include "tako/database.hpp"
#include "tako/node.hpp"
#include "tako/keypoints.hpp"
#include "tako/object.hpp"


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
    //finish
    /*for(std::vector<cv::Mat>::iterator iter = images.begin(); iter!=images.end(); ++iter)
    {
        i++;
        cv::namedWindow("Display windows");
        cv::imshow("Display windows", *iter);
        std::cout<<"picture number : " <<i << std::endl;
        cv::waitKey(0);
    }
    */
   //finish
   /*for(std::vector<tako::Node>::iterator iter = nodes.begin(); iter!=nodes.end(); ++iter)
   {
       cv::namedWindow("Display windows");
       cv::imshow("Display windows", iter->getImage());
       std::cout<<"picture number : " << iter->getId() <<std::endl;
       cv::waitKey(0);
   }
   */
   // DBoW3::Vocabulary vocab;//("./vocabulary.yml.gz");
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
    std::ofstream file;
    file.open("keypoint.txt", std::ios::out|std::ios::trunc);
    if(!file)
    {
        std::cout<<"file doesn't exist." <<std::endl;
    }
    else
    {
        // threshold
        double BoW_Threshold = tako::Config::get<double> ("BoW_threshold");
        file << "database info : " <<std::endl;
        file << db << std::endl;
        std::cout<<"compare image with database..." <<std::endl;
        int total_loop = 0;
        for(tako::Node& node:nodes)
        {
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
            if(keypoint_score >= BoW_Threshold)
            {
                if(loopId != 0)
                {
                    total_loop ++;
                }
                file <<" image id : " << node.id_
                       << " simularity image : " << loopId
                       << " score : " << keypoint_score <<std::endl;
            }
            else{
                file << " image id : " << node.id_
                        << " not simularity image !" << std::endl;
            }
        }
        file << " total_loop : " << total_loop<<std::endl;
        std::cout << " threshold : " << BoW_Threshold <<std::endl;
    }
    file.close();
    return 0;
}