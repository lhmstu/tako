#include <stdlib.h>
#include "tako/common_include.hpp"
#include "tako/config.hpp"
#include "tako/database.hpp"
#include "tako/node.hpp"
#include "tako/keypoints.hpp"
#include "tako/object.hpp"
#include "tako/spatial.hpp"

cv::Mat getDescriptor(tako::Node &node, tako::Node &node_early, tako::Node &node_after)
{
    cv::Mat descriptor = node.descriptor_ + node_early.descriptor_ + node_after.descriptor_;
    cv::divide(descriptor, 3, descriptor);
    return descriptor;
}

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
    file.open("spatial.txt", std::ios::out|std::ios::trunc);
    if(!file)
    {
        std::cout << " file doesn't exist. " <<std::endl;
    }
    else
    {   
        int check = 1; // 計算數量
        std::vector<tako::Node>::iterator iter = nodes.begin(); // after node;
        tako::Node node_early1 ; 
        for(tako::Node &node:nodes)
        {
            if(check == 1)
            {
                node_early1 = node;
                iter = iter + 1;
            }
            else
            {
                cv::Mat descriptor_1 = getDescriptor(node, node_early1, *iter); // 1 2 3 
                cv::Mat descriptor_2 = spatial.getDescriptor(node); // spatial 123
            }
            iter = iter + 1;
            check ++ ;
        }
    }
    file.close();
    std::cout<<" spatial file finish!"<<std::endl;

    return 0;
}