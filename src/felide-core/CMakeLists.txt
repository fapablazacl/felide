
set(target "felide-core")

set(sources 
    "felide/FileUtil.cpp"
	"felide/FileUtil.hpp"
)

source_group("\\felide" FILES ${sources})

add_library(${target} ${sources})
