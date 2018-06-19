
# setup borc-core
include_directories("../borc-core/")

set (target "borc-tdd")
set (sources 
	"MainTDD.cpp"
)

include_directories(${Boost_INCLUDE_DIRS})

source_group("\\" FILES ${sources})

add_executable (
	${target} 
	${sources}
)

target_link_libraries (
    ${target} 
    borc-core
    fmt
)

install(TARGETS ${target} DESTINATION "bin")
