set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/submodules/tinyxml)
aux_source_directory(. SRC_LIST)
# add_library(tinyxml SHARED ${SRC_LIST}) # .so库
add_library(tinyxml STATIC ${SRC_LIST}) # 静态库