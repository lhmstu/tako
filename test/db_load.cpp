#include "tako/common_include.hpp"
#include <stdlib.h>

using namespace std;

static int callback(void *data, int argc, char **argv, char **azColName)
{
    int i;
    cout<< (const char*)data << endl;
    for (i = 0; i < argc; i++)
    {
        auto lambda = [](char* text, int i)
                {
                    return text?text:"NULL";
                }(argv[i],i);
        cout << azColName[i] << " = " << lambda << endl;
    }
    cout << endl;

    return 0;
}

int main(int argc, char **argv)
{
    sqlite3 *db;
    char *zErrMsg = 0;
    std::vector<cv::Mat> images;
    std::vector<int> ids;



    int check;
    check = sqlite3_open(argv[1], &db);
    if (check)
    {
        cout << " false to load database " << endl;
        exit(0);
    }
    else
    {
        cout << "Opened database successfully" << endl;
    }

    // create SQL statement 
    /*sql =   "CREATE TABLE COMPANY( " \
            "ID INT PRIMARY KEY     NOT NULL,"\
            "NAME           TEXT    NOT NULL,"\
            "AGE            INT     NOT NULL,"\
            "ADDRESS        CHAR(50),"\
            "SALARY         REAL);";
    */
   // insert
   /*
    sql =   "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
            "VALUES (1, 'Paul0', 32, 'Calif0', 1000.00);" \ 
            "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
            "VALUES (2, 'Paul1', 22, 'Calif1', 2000.00);" \ 
            "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
            "VALUES (3, 'Paul2', 12, 'Calif2', 3000.00);" \ 
            "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
            "VALUES (4, 'Paul3', 25, 'Calif3', 4000.00);";
    */

    //image load
    const char* sql = "SELECT * FROM Data";
    // execute SQL statement
    //check = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
    sqlite3_stmt *statement;
    if (sqlite3_prepare_v2(db, sql, strlen(sql), &statement, 0) != SQLITE_OK)
    {
        std::cout<<"false to open database " <<std::endl;
        return 0;
    }


    int result = 0;
        while(true)
        {
            result = sqlite3_step(statement);
            if(result == SQLITE_ROW)
            {
                int id = sqlite3_column_int(statement, 0 );
                ids.push_back(id);
                int size = sqlite3_column_bytes(statement, 1); // Get the size of the vector
                uchar* p = (uchar*)sqlite3_column_blob(statement, 1); // Get the pointer to data
                std::vector<uchar> data(p, p + size); // Initialize the vector with the data 
                images.push_back(cv::imdecode(data, CV_LOAD_IMAGE_COLOR));
            }
            else
            {
                break;
            }
        }
    if(check != SQLITE_OK)
    {
        cout << "SQL error " << zErrMsg <<endl;
        sqlite3_free(zErrMsg);
    }
    else
    {
        cout<< " operation done successfully" <<endl;
    }
    sqlite3_finalize(statement);
    sqlite3_close(db);
    int i =0 ;
    for(vector<cv::Mat>::iterator iter = images.begin(); iter!=images.end(); ++iter)
    {
        i++   ;
        cv::namedWindow("Display windows");
        cv::imshow("Display windows", *iter);
        std::cout<<"picture number : " << i << std::endl;
        cv::waitKey(0);
    }
    return 0;
}