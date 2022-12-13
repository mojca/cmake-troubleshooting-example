if (MYAWESOMELIB_USE_SOURCE_BOOST)
    include(FetchContent)

    set(OLD_FETCHCONTENT_QUIET ${FETCHCONTENT_QUIET})
    set(FETCHCONTENT_QUIET OFF)

    set(BOOST_VERSION_SOURCE 1.81.0.beta1)

    FetchContent_Declare(boost
                         URL      https://github.com/boostorg/boost/releases/download/boost-${BOOST_VERSION_SOURCE}/boost-${BOOST_VERSION_SOURCE}.zip
                         URL_HASH SHA256=e0d4abdfc99c7a57d6d35f090ff32197e89ed83bf49cd9ac8e72babb94b8587f
                         ${FC_PARAMS}
    )

    set(BUILD_SHARED_LIBS OFF)
    set(BOOST_RUNTIME_LINK static)
    message(STATUS "Linking Boost statically (lib)")

    set(NEEDED_LIBRARIES
        filesystem
    )

    set(BOOST_INCLUDE_LIBRARIES "${NEEDED_LIBRARIES}"
        CACHE STRING
        "List of libraries to build (default: all but excluded and incompatible)"
        FORCE
    )

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
