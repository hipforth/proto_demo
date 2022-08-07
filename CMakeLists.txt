cmake_minimum_required(VERSION 3.2)

project(proto_demo)

find_package(Eigen3 REQUIRED)
set(BOOST_COMPONENTS iostreams)
find_package(Boost REQUIRED COMPONENTS ${BOOST_COMPONENTS})

include_directories(include
										build
                    ${EIGEN3_INCLUDE_DIR}
										${Boost_INCLUDE_DIRS})

add_subdirectory(proto)
add_library(${PROJECT_NAME} src/grid_2d.cc 
                            src/submap_2d.cc
														src/proto_io.cc
														)
target_link_libraries(${PROJECT_NAME} proto ${Boost_LIBRARIES})
# add_executable(demo app/demo.cc)
# target_link_libraries(demo ${PROJECT_NAME})

add_executable(test_rigid app/test_rigid.cc)
target_link_libraries(test_rigid ${PROJECT_NAME})