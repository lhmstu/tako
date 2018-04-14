
#include <stdlib.h>
#include "tako/common_include.hpp"
#include "tako/config.hpp"
#include "tako/database.hpp"


int main(int argc, char** argv)
{
    tako::Config::setParameterFile(argv[1]);
    std::vector<cv::Mat> images;
    std::string dbPath = tako::Config::get<std::string> ("database_path");
    std::cout<<"database_path : " <<dbPath <<std::endl;
    
    char* sql;
    //sqlite3 *db;
    
    sql = "SELECT * FROM Data";
    tako::SQLiteDatabase database(dbPath, sql);
    images = database.setDatabaseImage();

    int i = 0;
    for(std::vector<cv::Mat>::iterator iter = images.begin(); iter!=images.end(); ++iter)
    {
        i++;
        cv::namedWindow("Display windows");
        cv::imshow("Display windows", *iter);
        std::cout<<"picture number : " <<i << std::endl;
        cv::waitKey(0);
    }
    //sqlite3_close(db);
    return 0;
}