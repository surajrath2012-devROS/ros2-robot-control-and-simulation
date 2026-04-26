import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    package_name = 'autonomous_robot_core'
    urdf_file = os.path.join(get_package_share_directory(package_name), 'urdf', 'robot.urdf')

    with open(urdf_file, 'r') as infp:
        robot_description = infp.read()

    # 1. Robot State Publisher (The Body)
    node_robot_state_publisher = Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        output='screen',
        parameters=[{'robot_description': robot_description}]
    )

    # 2. Joint State Publisher (The Hinges) - ADD THIS
    node_joint_state_publisher = Node(
        package='joint_state_publisher',
        executable='joint_state_publisher',
        output='screen'
    )

    return LaunchDescription([
        node_robot_state_publisher,
        node_joint_state_publisher
    ])