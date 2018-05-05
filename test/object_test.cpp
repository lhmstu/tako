#include "tako/common_include.hpp"
#include "tako/node.hpp"
#include "tako/object_detect.hpp"
#include "tako/database.hpp"
#include "tako/config.hpp"
#include "tako/object.hpp"
#include <stdlib.h>
int main(int argc, char** argv)
{
    tako::Config::setParameterFile(argv[1]);
    std::vector<tako::Node> nodes;
    std::string dbPath = tako::Config::get<std::string> ("database_path");
    std::cout << "database_path : " <<dbPath <<std::endl;
    char* sql;

    sql = "SELECT * FROM Data";
    tako::SQLiteDatabase database(dbPath, sql);
    database.setDatabaseImage(nodes);
    std::cout<<"start dnn network....."<<std::endl;
    tako::ObjectDetect objectDetect;
    std::cout<<"start create file : object_test.txt"<<std::endl;
    std::ofstream file;
    file.open("object_test.txt", std::ios::out|std::ios::trunc);
    if(!file)
    {
        std::cout<< " file doesn't exist." <<std::endl;
    }
    else
    {
        for(tako::Node& node:nodes)
        {
            node.node_object_ = objectDetect.object_detect(node);
            for(tako::Object& object:node.node_object_)
            {    std::cout<< "node id : " << node.id_ <<std::endl;
                 std::cout<< "node descritpor : " << node.getDescriptor() << std::endl;
                 std::cout<< "node_object : " <<object<<std::endl;
            }
        }
        objectDetect.getWeights();
    }
    return 0;
}