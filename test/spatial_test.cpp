#include <stdlib.h>
#include "tako/common_include.hpp"
#include "tako/config.hpp"
#include "tako/database.hpp"
#include "tako/node.hpp"
#include "tako/keypoints.hpp"
#include "tako/object.hpp"

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

    std::ofstream file;
    file.open("spatial.txt", std::ios::out|std::ios::trunc);
    if(!file)
    {
        std::cout << " file doesn't exist. " <<std::endl;
    }
    else
    {   
        for(tako::Node& node:nodes)
        {
            file << " image id : " << node.id_ << " position : " << std::endl;
            file << node.position_ << std::endl;
        }
    }
    file.close();
    std::cout<<"finish!"<<std::endl;

    return 0;
}