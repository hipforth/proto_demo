# 查找 protobuf
find_package(Protobuf REQUIRED)

# 编译 proto 为 .cpp 和 .h
FILE(GLOB PROTO_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.proto")
message(STATUS ${PROTO_FILES})

PROTOBUF_GENERATE_CPP(PROTO_SRCS PROTO_HDRS ${PROTO_FILES})
message("PROTO_SRCS = ${PROTO_SRCS}")
message("PROTO_HDRS = ${PROTO_HDRS}")

add_library(proto STATIC ${PROTO_SRCS} ${PROTO_HDRS})

target_link_libraries(proto ${Protobuf_LIBRARIES}) 

target_include_directories(proto
        PUBLIC ${CMAKE_CURRENT_BINARY_DIR}
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
        PUBLIC ${PROTOBUF_INCLUDE_DIRS})
