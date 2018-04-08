add_library(tako 
    config.cpp
    database.cpp
)

target_link_libraries( tako rtabmap_core rtabmap_utilite ${LIBRARIES_TAKO})
