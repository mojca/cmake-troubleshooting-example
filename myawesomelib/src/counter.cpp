#include "myawesomelib/counter.h"

#include <algorithm>
#include <boost/filesystem.hpp>

size_t Counter::getNumberOfFiles()
{
    using namespace boost::filesystem;

    const path the_path(".");
    const size_t cnt = std::count_if(
        directory_iterator(the_path),
        directory_iterator(),
        static_cast<bool(*)(const path&)>(is_regular_file));

	return cnt;
}
