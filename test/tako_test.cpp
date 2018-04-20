
#include <stdlib.h>
#include "tako/common_include.hpp"
#include "tako/config.hpp"
#include "tako/database.hpp"
#include "tako/node.hpp"


int main(int argc, char** argv)
{
    // set parameter 
    tako::Config::setParameterFile(argv[1]);
    //std::vector<cv::Mat> images;
    std::vector<tako::node> nodes;
    std::string dbPath = tako::Config::get<std::string> ("database_path");
    std::cout<<"database_path : " <<dbPath <<std::endl;
    char* sql;
    //sqlite3 *db;

    // load database images
    sql = "SELECT * FROM Data";
    tako::SQLiteDatabase database(dbPath, sql);
    database.setDatabaseImage(nodes);

    int i = 0;
    /*for(std::vector<cv::Mat>::iterator iter = images.begin(); iter!=images.end(); ++iter)
    {
        i++;
        cv::namedWindow("Display windows");
        cv::imshow("Display windows", *iter);
        std::cout<<"picture number : " <<i << std::endl;
        cv::waitKey(0);
    }
    */
   for(std::vector<tako::node>::iterator iter = nodes.begin(); iter!=nodes.end(); ++iter)
   {
       cv::namedWindow("Display windows");
       cv::imshow("Display windows", iter->getImage());
       std::cout<<"picture number : " << iter->getId() <<std::endl;
       cv::waitKey(0);
   }
    //sqlite3_close(db);
    return 0;
}