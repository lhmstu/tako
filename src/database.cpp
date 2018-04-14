#include "tako/database.hpp"

namespace tako
{
    SQLiteDatabase::SQLiteDatabase(std::string& dbPath,char* sql)
    {
        dbPath_ = dbPath;
        sql_ = sql;
        if(sqlite3_open(dbPath_.c_str(), &db_) == SQLITE_OK )
        {
            std::cout<<"Opened database Successfully\n"<<std::endl;
        }
        else
        {
            std::cout<<"false to open database construct" <<std::endl;
            sqlite3_close(db_);
        }
    }

    // put image from database to vector
    std::vector<cv::Mat> SQLiteDatabase::setDatabaseImage()
    {
        sqlite3_stmt* statement;
        if (sqlite3_prepare_v2(db_, sql_, strlen(sql_), &statement, 0) != SQLITE_OK)
        {
            std::cout<<"false to open database Image" <<std::endl;
        }
        int result = 0;
        int i = 0;
        while(true)
        {
            i++;
            result = sqlite3_step(statement);
            if(result == SQLITE_ROW)
            {
                int id = sqlite3_column_int(statement, 0 );
                ids_.push_back(id);
                int size = sqlite3_column_bytes(statement, 1); // Get the size of the vector
                uchar* p = (uchar*)sqlite3_column_blob(statement, 1); // Get the pointer to data
                std::vector<uchar> data(p, p + size); // Initialize the vector with the data 
                images_.push_back(cv::imdecode(data, CV_LOAD_IMAGE_COLOR));
            }
            else
            {
                break;
            }
        }
        sqlite3_finalize(statement);
        std::cout<<"load total " << i << "images"<<std::endl;
        return images_;
    }

    SQLiteDatabase::~SQLiteDatabase()
    {
        sqlite3_close(db_);
    }


}