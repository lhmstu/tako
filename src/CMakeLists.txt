set (tako_files 
    config.cpp
    object.cpp
    node.cpp
    database.cpp
    keypoints.cpp
    object_detect.cpp
    spatial.cpp
    combine.cpp
    precision_recall.cpp
   # parameter.cpp

    sqlite3.c
)

add_library(tako ${tako_files})

target_link_libraries( tako ${LIBRARIES_TAKO})
