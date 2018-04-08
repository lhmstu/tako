add_executable( tako_test tako_test.cpp)
target_link_libraries(tako_test rtabmap_core rtabmap_utilite ${LIBRARIES_TAKO})

add_executable( db_load db_load.cpp)
target_link_libraries(db_load rtabmap_core rtabmap_utilite ${LIBRARIES_TAKO})
#SET_TARGET_PROPERTIES(take_test 
#	PROPERTIES OUTPUT_NAME ${PROJECT_PREFIX}-tako)
