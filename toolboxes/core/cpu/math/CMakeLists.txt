if (WIN32)
    add_definitions(-D__BUILD_GADGETRON_CPUCORE_MATH__)
elseif(WIN32)
    set(CMAKE_CXX_FLAGS -fpermissive)
endif (WIN32)


set(cpucore_math_header_files
    cpucore_math_export.h
    hoNDArray_math.h
    hoNDImage_util.h
    hoNDImage_util.hxx
    hoNDArray_linalg.h )

set(cpucore_math_src_files 
    hoNDArray_linalg.cpp )


    set(cpucore_math_header_files 
        ${cpucore_math_header_files}
        hoNDArray_reductions.h
        hoNDArray_reductions.hxx
        hoArmadillo.h
        hoNDArray_elemwise.h
        cpp_blas.h
         )

    set(cpucore_math_src_files 
        ${cpucore_math_src_files} 
        hoNDArray_reductions.cpp
        hoNDArray_elemwise.cpp
        cpp_blas.cpp)

set_source_files_properties(cpp_blas.cpp PROPERTIES COMPILE_FLAGS -fpermissive)
add_library(gadgetron_toolbox_cpucore_math SHARED  ${cpucore_math_src_files} ${cpucore_math_header_files})
set_target_properties(gadgetron_toolbox_cpucore_math PROPERTIES VERSION ${GADGETRON_VERSION_STRING} SOVERSION ${GADGETRON_SOVERSION})
    target_link_libraries(gadgetron_toolbox_cpucore_math
        gadgetron_toolbox_cpucore
        gadgetron_toolbox_log
        armadillo
        BLAS
		${LAPACK_LIBRARIES}
            )

install(TARGETS gadgetron_toolbox_cpucore_math
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
	RUNTIME DESTINATION bin
	COMPONENT main
)


install(FILES 
    ${cpucore_math_header_files}
    DESTINATION ${GADGETRON_INSTALL_INCLUDE_PATH} COMPONENT main)
