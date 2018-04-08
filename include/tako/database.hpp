#ifndef DATABASE_HPP
#define DATABASE_HPP

#include "tako/common_include.hpp"

namespace tako
{
    class SQLiteDatabase 
    {
        //parameter
        public:
            static std::shared_ptr<SQLiteDatabase> ptr_; // 一次開啟一個 database 就好
            int id_; // number of picture
            std::map<int, cv::Mat> imageMap_; //picture
            std::map<int, double> seq_; //sequence
        
        private:
            sqlite3 *db_;

        // function
        public:
            SQLiteDatabase();
            bool loadDatabase(const std::string& dbPath);
            cv::Mat getImage();
            double getSeq();
            ~SQLiteDatabase();
    };
}
#endif