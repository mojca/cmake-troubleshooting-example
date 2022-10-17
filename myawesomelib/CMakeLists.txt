set(LIB_NAME myawesome)

add_library(${LIB_NAME}
    src/counter.cpp
    include/myawesomelib/counter.h
)

target_include_directories(${LIB_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(${LIB_NAME}
    PRIVATE
        Boost::filesystem
)
