cmake_minimum_required(VERSION 3.8)
project(autonomous_robot_core)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

add_executable(brain_node src/simple_brain.cpp)
ament_target_dependencies(brain_node rclcpp std_msgs)

add_executable(sensor_node src/sensor_node.cpp)
ament_target_dependencies(sensor_node rclcpp std_msgs)

install(TARGETS
  brain_node
  sensor_node
  DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY urdf DESTINATION share/${PROJECT_NAME})

install(DIRECTORY urdf launch DESTINATION share/${PROJECT_NAME})

ament_package()
