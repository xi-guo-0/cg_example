add_executable(main main.cpp image.cpp ray.cpp camera.cpp)
target_link_libraries(main png Eigen3::Eigen)