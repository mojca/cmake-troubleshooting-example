include(FetchContent)

FetchContent_Declare(pybind11
    GIT_REPOSITORY https://github.com/pybind/pybind11
    GIT_TAG v2.10.0
    GIT_PROGRESS ON
    GIT_SHALLOW ON
    GIT_REMOTE_UPDATE_STRATEGY CHECKOUT
)
FetchContent_MakeAvailable(pybind11)
