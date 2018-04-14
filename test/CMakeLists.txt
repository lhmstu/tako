
add_executable( tako_test tako_test.cpp)
TARGET_LINK_LIBRARIES(tako_test 
        rtabmap_core 
        rtabmap_utilite 
        ${LIBRARIES_TAKO}
        tako
        )

add_executable( db_load db_load.cpp)
TARGET_LINK_LIBRARIES(db_load 
        rtabmap_core 
        rtabmap_utilite 
        ${LIBRARIES_TAKO}
        tako
        )
#SET_TARGET_PROPERTIES(take_test 
#	PROPERTIES OUTPUT_NAME ${PROJECT_PREFIX}-tako)
