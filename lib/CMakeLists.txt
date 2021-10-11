aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} ALL_SOURCE)
add_library(nethelp SHARED ${ALL_SOURCE})

install(FILES help.h DESTINATION include)
install(TARGETS nethelp DESTINATION lib)
