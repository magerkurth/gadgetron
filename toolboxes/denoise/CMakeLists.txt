


add_library(gadgetron_toolbox_denoise SHARED 
        denoise_export.h
        non_local_means.cpp
        non_local_means.h
        non_local_bayes.cpp non_local_bayes.h)

set_target_properties(gadgetron_toolbox_denoise PROPERTIES VERSION ${GADGETRON_VERSION_STRING} SOVERSION ${GADGETRON_SOVERSION})

target_link_libraries(gadgetron_toolbox_denoise
        gadgetron_toolbox_log
        gadgetron_toolbox_cpucore
        gadgetron_toolbox_cpucore_math
        armadillo
        ${Boost_LIBRARIES}
        )
target_include_directories(gadgetron_toolbox_denoise
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        )

install(TARGETS gadgetron_toolbox_denoise
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
	RUNTIME DESTINATION bin
	COMPONENT main
)


install(FILES
        denoise_export.h
        non_local_means.h
        non_local_bayes.h
        DESTINATION ${GADGETRON_INSTALL_INCLUDE_PATH} COMPONENT main)
