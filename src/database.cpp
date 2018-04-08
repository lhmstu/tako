#include "tako/database.hpp"

namespace tako
{
    bool SQLiteDatabase::loadDatabase( const std::string& dbPath)
    {
        int check = sqlite3_open(dbPath.c_str(), &db_);
        if(check)
        {
            std::cout<<"false to open database " <<std::endl;
            sqlite3_close(db_);
            return 0;
        }
        else{
            std::cout<<"Opened database Successfully\n"<<std::endl;
        }
    }

    SQLiteDatabase::~SQLiteDatabase()
    {
            sqlite3_close(db_);
    }
}