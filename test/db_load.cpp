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
    int check;
    char* sql;

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
    sql = "SELECT * from COMPANY";
    // execute SQL statement
    check = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
    if(check != SQLITE_OK)
    {
        cout << "SQL error " << zErrMsg <<endl;
        sqlite3_free(zErrMsg);
    }
    else
    {
        cout<< " operation done successfully" <<endl;
    }
    sqlite3_close(db);
    return 0;
}