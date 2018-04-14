#ifndef NODE_HPP
#define NODE_HPP

#include "tako/common_include.hpp"

namespace tako
{
    class SQLiteDatabase;
    class node
    {
        public:
            std::shared_ptr<SQLiteDatabase> ptr_;
            int id_;
            cv::Mat image_;


        public:
            node ();
            int getId();
            cv::Mat getImage();
            ~node ();
    };
}
#endif // NODE_HPP