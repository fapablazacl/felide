
set(target "Felide.Core")

set(sources 
    "Felide/FileUtil.cpp"
	"Felide/FileUtil.hpp"
)

source_group("\\Felide" FILES ${sources})

add_library(${target} ${sources})
