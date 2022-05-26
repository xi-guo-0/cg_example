add_library(ray_tracing image.cpp ray.cpp camera.cpp light.cpp material.cpp hittable.cpp mesh.cpp)
target_include_directories(ray_tracing PUBLIC ${CgExample_SOURCE_DIR}/include)
target_link_libraries(ray_tracing png Eigen3::Eigen)
