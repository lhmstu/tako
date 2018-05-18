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
    tako::Config::setParameterFile(argv[1]);
    std::vector<tako::Node> nodes;
    std::string dbPath = tako::Config::get<std::string>("database_path");
    std::cout<<"database_path : " << dbPath <<std::endl;
    char* sql;

    //load database image;
    sql = "SELECT * FROM Data";
    tako::SQLiteDatabase database(dbPath, sql);
    database.setDatabaseImage(nodes);
    sql = "SELECT * FROM Node";
    database.changeSql(sql);
    database.setDatabasePosition(nodes);

    // keypoint 
    tako::KeyPoints keypoints;
    keypoints.setVocabulary(nodes);
    std::cout << "Setting Database "<< std::endl;
    DBoW3::Database db = keypoints.setDatabase();
    std::cout<< "database info : " << std::endl;
    // spatial kmeans
    tako::Spatial spatial(nodes);
    //spatial.KMeans(nodes);

    std::ofstream file;
    file.open("spatial_test.txt", std::ios::out|std::ios::trunc);
    if(!file)
    {
        std::cout << " file doesn't exist. " <<std::endl;
    }
    else
    {   
        std::cout << " now load spaital.txt and insert ! " << std::endl;
        std::list<tako::Node> cluster_test;
        cv::Mat test;
        for(tako::Node &node:nodes)
        {
            if(node.id_ == 1 )
            {
                test = node.descriptor_.clone() ;
            }
            else
            {
                test = test + node.descriptor_;
            }
            std::cout << test << std::endl;
            
            if(node.id_ == 1 || node.id_ == 2)
            {
                cluster_test.push_back(node);
            }
            else
            {
                cluster_test.push_back(node);
                std::cout << cluster_test.size()<< std::endl;
                std::vector<tako::Node> cluster_aims = spatial.getSpatial_node(node.id_); // 比對方
                double spatial_Score = keypoints.compare_spatial2spatial(cluster_test, cluster_aims);
                std::cout << "the node : " << node.id_ << " similarity node : " << cluster_aims[0].id_
                           << " Scoring : " << spatial_Score <<std::endl;
                cluster_test.pop_front();
            }
        }
    }
    file.close();
    std::cout<<" spatial file finish!"<<std::endl;

    return 0;
}