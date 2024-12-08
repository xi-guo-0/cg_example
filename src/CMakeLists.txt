add_library(ray_tracing image.cpp ray.cpp camera.cpp light.cpp material.cpp hittable.cpp)
target_include_directories(ray_tracing PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(ray_tracing webp Eigen3::Eigen)
