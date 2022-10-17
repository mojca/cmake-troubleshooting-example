if (MYAWESOMELIB_USE_SOURCE_BOOST)
    include(FetchContent)

    set(OLD_FETCHCONTENT_QUIET ${FETCHCONTENT_QUIET})
    set(FETCHCONTENT_QUIET OFF)

    FetchContent_Declare(boost
        GIT_REPOSITORY https://github.com/boostorg/boost.git
        GIT_TAG boost-1.80.0
        GIT_SUBMODULES_RECURSE ON
        GIT_SUBMODULES tools/cmake
                       libs/align
                       libs/assert
                       libs/atomic
                       libs/concept_check
                       libs/config
                       libs/container_hash
                       libs/conversion
                       libs/core
                       libs/detail
                       libs/filesystem
                       libs/function_types
                       libs/fusion
                       libs/integer
                       libs/io
                       libs/iterator
                       libs/move
                       libs/mp11
                       libs/mpl
                       libs/optional
                       libs/predef
                       libs/preprocessor
                       libs/smart_ptr
                       libs/static_assert
                       libs/system
                       libs/throw_exception
                       libs/tuple
                       libs/type_traits
                       libs/typeof
                       libs/utility
                       libs/variant2
                       libs/winapi
        GIT_PROGRESS ON
        GIT_SHALLOW ON
        GIT_REMOTE_UPDATE_STRATEGY CHECKOUT
    )

    set(BUILD_SHARED_LIBS OFF)
    set(BOOST_RUNTIME_LINK static)
    message(STATUS "Linking Boost statically (lib)")

    FetchContent_MakeAvailable(boost)

    set(FETCHCONTENT_QUIET ${OLD_FETCHCONTENT_QUIET})

else()
    set(Boost_USE_STATIC_LIBS ON CACHE BOOL "")
    set(Boost_USE_MULTITHREADED ON)
    set(Boost_USE_STATIC_RUNTIME ON)
    set(Boost_NO_WARN_NEW_VERSIONS ON)

    find_package(Boost 1.71.0 REQUIRED COMPONENTS filesystem)
    if (Boost_FOUND)
        message(STATUS "Boost ${Boost_VERSION} at: ${Boost_INCLUDE_DIRS} | ${Boost_LIBRARY_DIRS}")
        set(Boost_INCLUDE_DIRS ${Boost_INCLUDE_DIRS} CACHE INTERNAL "Boost include directories.")
        set(Boost_LIBRARY_DIRS ${Boost_LIBRARY_DIRS} CACHE INTERNAL "Link directories for Boost libraries.")
        set(Boost_LIBRARIES ${Boost_LIBRARIES} CACHE INTERNAL "Boost_LIBRARIES")

        if (Boost_LIBRARIES MATCHES "::")
            message(STATUS "USING boost cmake")

            foreach(BOOST_COMPONENT IN LISTS Boost_LIBRARIES)
                set_target_properties(${BOOST_COMPONENT} PROPERTIES IMPORTED_GLOBAL TRUE)
            endforeach()
        else()
            message(STATUS "NOT using boost CMake")
            set(BOOST_COMPONENTS filesystem)

            foreach(BOOST_COMPONENT ${BOOST_COMPONENTS})
                set(FULL_TARGET_NAME "Boost::${BOOST_COMPONENT}")
                if(TARGET ${FULL_TARGET_NAME})
                    set_target_properties(${FULL_TARGET_NAME} PROPERTIES IMPORTED_GLOBAL TRUE)
                endif()
            endforeach()
        endif()
    else()
        message(FATAL_ERROR "Boost 1.71.0 or newer is needed.")
    endif()
endif()
