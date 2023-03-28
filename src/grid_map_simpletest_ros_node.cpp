#include "ros/ros.h"
#include "grid_map_core/grid_map_core.hpp"
#include "grid_map_ros/grid_map_ros.hpp"
#include "grid_map_msgs/GridMap.h"

int main(int argc, char **argv) {
    std::cout << "Hello grid_map_ros world!" << std::endl;
    grid_map::GridMap map( {"elevation"} );

    ros::init(argc, argv, "grid_map_node");
    ros::NodeHandle nh;
    ros::Publisher map_pub = nh.advertise<grid_map_msgs::GridMap>("mapper", 1000);
    ros::Rate loop_rate(10);

    map.setFrameId( "map" );
    map.setGeometry( grid_map::Length(2,5), 0.3 );
    for( grid_map::GridMapIterator it(map); !it.isPastEnd(); ++it ) {
        grid_map::Position position;
        map.getPosition( *it, position );
        map.at( "elevation", *it ) = sin(position.x()) + exp(position.y());
        // std::cout << map.at( "elevation", *it ) << std::endl;
    }

    while( ros::ok() ) {
        grid_map_msgs::GridMap map_msg;
        grid_map::GridMapRosConverter::toMessage( map, map_msg );
        map_pub.publish( map_msg );
        ros::spinOnce();
        loop_rate.sleep();
    }

}