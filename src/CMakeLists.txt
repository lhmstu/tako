set (tako_files 
    config.cpp
    database.cpp
    node.cpp
    sqlite3.c
)

add_library(tako ${tako_files})

#target_link_libraries( tako ${LIBRARIES_TAKO})
