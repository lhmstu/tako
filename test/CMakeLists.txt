set( DBoW3_INCLUDE_DIRS "/usr/local/include")
set( DBoW3_LIBS "/usr/local/lib/libDBoW3.so")

add_executable( tako_test tako_test.cpp)
TARGET_LINK_LIBRARIES(tako_test 
       # rtabmap_core 
       # rtabmap_utilite 
        ${LIBRARIES_TAKO}
        tako
        )

add_executable( db_load db_load.cpp)
TARGET_LINK_LIBRARIES(db_load 
       # rtabmap_core 
       # rtabmap_utilite 
        ${LIBRARIES_TAKO}
        tako
        )

add_executable( keyframe_test keyframe_test.cpp)
TARGET_LINK_LIBRARIES( keyframe_test
       # rtabmap_core
       # rtabmap_utilite 
        ${LIBRARIES_TAKO}
        tako
        ${DBoW3_LIBS}
        )

add_executable( feature_test feature_training.cpp)
TARGET_LINK_LIBRARIES( feature_test 
	${LIBRARIES_TAKO} 
	${DBoW3_LIBS} 
        tako
)
#TARGET_LINK_LIBRARIES( feature_test
#        rtabmap_core
#        rtabmap_utilite 
#        ${LIBRARIES_TAKO}
#        tako
#        ${DBoW3_LIBS}
#        )
#SET_TARGET_PROPERTIES(take_test 
#	PROPERTIES OUTPUT_NAME ${PROJECT_PREFIX}-tako)
