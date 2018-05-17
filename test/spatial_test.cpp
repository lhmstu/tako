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
    file.open("spatial.txt", std::ios::out|std::ios::trunc);
    if(!file)
    {
        std::cout << " file doesn't exist. " <<std::endl;
    }
    else
    {   
       /* tako::Node *kp1 = nullptr;
        tako::Node *kp2 = nullptr;
        for(std::vector<tako::Node>::iter iter = nodes.begin(); iter!= nodes.end(); iter++)
        {
            if(iter == nodes.begin())
            {
               kp1 = iter ;
               kp2 = iter + 1 ;
            }
            else
            {
                kp1 = iter - 1; 
                kp2 = iter + 1;
            }
            cv::Mat now_descriptor = kp1->descriptor_ + iter->descriptor_ + kp2->descriptor_
            cv::divide(now_descriptor, 3, now_descriptor);
            cv::Mat descriptor = spatial.MeanDescriptor(node);
            


        }
        */
    }
    file.close();
    std::cout<<" spatial file finish!"<<std::endl;

    return 0;
}