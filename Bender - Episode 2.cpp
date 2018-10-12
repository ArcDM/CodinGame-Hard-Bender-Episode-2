#include <iostream>
#include <vector>
#include <unordered_map>
#include <sstream>

/**This program takes an input of a number of rooms, the money they hold,
 * and the rooms they lead to and outputs the greatest amount of money
 * collected of all the singular traversable paths.
 * 
 * This solution is only possible when given rooms that do not loop upon themselves.
 */

size_t path_finding( std::unordered_map<int, std::vector<int>> &floor_plan, std::vector<int> &room)
{ // This method takes a input describing a room, stores the greatest total
  // from following the paths though it's 'doors' and returns that total.
  // This method works recursively.
    size_t cash_picked_up = 0;
    
    for( std::vector<int>::iterator door = room.begin() + 1; door != room.end(); ++door )
    { // for each of the doors from the room, if any
        if( *door )
        { // if the door is not an exit
            size_t return_cash = path_finding( floor_plan, floor_plan[ *door ] ); // recursive call
            
            if( cash_picked_up < return_cash )
            { // keep the largest sum of cash
                cash_picked_up = return_cash;
            }
        }
    }

    if( cash_picked_up )
    { // if a total has been computed, store it
        room = { cash_picked_up + room[ 0 ] }; // future searches will find the total here
    } // total is stored, no need to keep its connections

    return room[ 0 ];
}

int main()
{
    size_t room_count;
    std::cin >> room_count; std::cin.ignore();
    std::unordered_map<int, std::vector<int>> building_layout( room_count );
    
    for( size_t count = room_count; count; --count )
    { // room input
        std::string input_string, parsed_element;        
        getline( std::cin, input_string );
        std::vector<int> room_input;
        std::stringstream streamed_data( input_string );
        
        while( getline( streamed_data, parsed_element, ' ' ) )
        { // parses input into integers
            if( parsed_element == "E" )
            { // not a number
                room_input.push_back( NULL );
            }
            else
            {
                room_input.push_back( atoi( parsed_element.c_str() ) );
            }
        }
                                // room number: {cash, doors...}
        building_layout.emplace( room_input[0], std::vector<int> ( room_input.begin() + 1, room_input.end() ) );
    }

    std::cout << path_finding( building_layout, building_layout[ 0 ] ) << std::endl;
}