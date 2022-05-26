add_executable(app app.cpp)
target_link_libraries(app PRIVATE ray_tracing)

add_executable(rasterization rasterization.cpp)
target_link_libraries(rasterization PRIVATE ray_tracing)
