import sys

"""
    This program takes an input of a number of rooms, the money they hold,
    and the rooms they lead to and outputs the greatest amount of money
    collected of all the singular traversable paths.
    
    This solution is only possible when given rooms that do not loop upon themselves.
"""

class Room:
    def __init__( this, input_cash, input_doors ):
        this.money = input_cash
        this.doors = input_doors

    def path_finding( this ):
    # This method takes a input of a dictionary describing a room, stores the greatest total
    # from following the paths though it's 'doors' and returns that total.
    # This method works recursively.
        cash_picked_up = 0
    
        for path in this.doors: # each of the doors from the room
            if path != 'E': # if the door is not an exit
                return_cash = building_layout[ path ].path_finding() # recursive call
            
                if cash_picked_up < return_cash: # keep the largest sum of cash
                    cash_picked_up = return_cash

        if cash_picked_up: # if a total has been computed, store it
            this.money += cash_picked_up # future searches will find the same total here
            this.doors = { 'E' } # total is stored, no need to keep its connections
    
        return this.money

building_layout = {}

for count in range( int( input() ) ): # room input
    room_input = input().split() # the numbers are still as strings but most don't need to be changed
    building_layout.update( { room_input[ 0 ]: Room( int( room_input[ 1 ] ), set( room_input[ 2: ] ) ) } )

print( building_layout['0'].path_finding() )