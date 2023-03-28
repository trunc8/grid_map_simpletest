#include<grid_map_core/grid_map_core.hpp>
#include<iostream>
#include<cmath>

int main() {
    std::cout << "Hello grid_map world!" << std::endl;
    grid_map::GridMap map( {"elevation"} );
    map.setFrameId( "map" );
    std::cout << "Frame Id: " << map.getFrameId() << std::endl;
    map.setGeometry( grid_map::Length(2,5), 0.3 ); // By default centered at (0,0)
    std::cout << "Y length: " << map.getLength().y() << std::endl;

    for( grid_map::GridMapIterator it(map); !it.isPastEnd(); ++it ) {
        grid_map::Position position;
        map.getPosition( *it, position );
        map.at( "elevation", *it ) = sin(position.x()) + exp(position.y());
        // std::cout << map.at( "elevation", *it ) << std::endl;
    }

    grid_map::Position p1(0.5,1.5), p2(0.1,0.3);
    grid_map::Index idx1, idx2;
    map.getIndex( p1, idx1 );
    map.getIndex( p2, idx2 );
    std::cout << idx1 << std::endl;
    std::cout << map.at( "elevation", idx1 ) << std::endl;
    std::cout << map.at( "elevation", idx2 ) << std::endl;
    std::cout << map.atPosition( "elevation", p1 ) << std::endl;
    std::cout << map.atPosition( "elevation", p2 ) << std::endl;
    std::cout << "Height difference between (0.5,1.5) and (0.1,0.3): " << 
        map.atPosition( "elevation", p1 ) - map.atPosition( "elevation", p2 ) << 
        std::endl;
    return 0;
}