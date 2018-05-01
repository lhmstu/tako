
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
    file.open("test.txt", std::ios::out|std::ios::trunc);
    if(!file)
    {
        std::cout<<"file doesn't exist." <<std::endl;
    }
    else
    {
        file << "database info : " <<std::endl;
        file << db << std::endl;
        std::cout<<"compare image with database..." <<std::endl;
        for(tako::Node& node:nodes)
        {
            DBoW3::QueryResults ret ;
            keypoints.compare_Image2Database(node, db, ret);
            for(DBoW3::QueryResults::iterator iter = ret.begin(); iter != ret.end(); iter++)
            {
                if(true)
                {
                    file <<"image id : " << node.id_
                           << " simularity image : " << iter->Id
                           << " score : " << iter->Score ;
                }
                else{
                    continue;
                }
                file<<std::endl;
            }
            file<<std::endl;
        }
    }
    file.close();
    return 0;
}