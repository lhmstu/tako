set (tako_files SHARED
    config.cpp
    database.cpp
)

add_library(tako ${tako_files})

#target_link_libraries( tako ${LIBRARIES_TAKO})
