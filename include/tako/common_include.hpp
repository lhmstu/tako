#ifndef COMMON_INCLUDE_HPP
#define COMMON_INCLUDE_HPP

// define the commomly included file to avoid a long include list
// SQLite3 library
extern "C"
{
#include "sqlite3/sqlite3.h"
}
// Opencv 
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>
//#include <opencv2/flann/flann.hpp>

// std
#include <vector>
#include <list>
#include <memory>
#include <string>
#include <iostream>
#include <set>
#include <map>
#include <unordered_map>
#include <algorithm>


#endif //COMMON_INCLUDE_H