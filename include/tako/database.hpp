#ifndef DATABASE_HPP
#define DATABASE_HPP

extern "C"
{
 #include "sqlite3/sqlite3.h"   
}
#include "tako/common_include.hpp"
#include "tako/node.hpp"

namespace tako
{
    class Node;
    class SQLiteDatabase 
    {
        //parameter
        public:
            static std::shared_ptr<SQLiteDatabase> ptr_; // 一次開啟一個 database 就好
            //std::vector<cv::Mat> images_;
            //std::vector<int> ids_;

            //std::vector<tako::node> nodes_;

            std::string dbPath_;
            sqlite3 *db_;
            char* sql_ ;

        // function
        public:
            SQLiteDatabase(std::string& dbPath, char* sql);
            //std::vector<cv::Mat> setDatabaseImage();
            void setDatabaseImage(std::vector<tako::Node> &nodes);
            ~SQLiteDatabase();
            
    };
}
#endif