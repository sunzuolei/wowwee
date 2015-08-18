
#OpenCV
find_package(OpenCV REQUIRED)

#set the include directories
include_directories (${CMAKE_SOURCE_DIR}/core/thirdpart/include)
#libraries
add_library(tld_utils ./src/tld_utils.cpp)
add_library(LKTracker ./src/LKTracker.cpp)
add_library(ferNN ./src/FerNNClassifier.cpp)
add_library(tld ./src/TLD.cpp)
#executables
#add_executable(run_tld run_tld.cpp)
#link the libraries
#target_link_libraries(run_tld tld LKTracker ferNN tld_utils ${OpenCV_LIBS})
#set optimization level 
#set(CMAKE_BUILD_TYPE Release)

