'''
Author: Sheldon Logan

Grid Walk
Description:

There is a monkey which can walk around on a planar grid. The monkey can move one
space at a time left, right, up or down. That is, from (x, y) the monkey can go
to (x+1, y), (x-1, y), (x, y+1), and (x, y-1). Points where the sum of the digits
of the absolute value of the x coordinate plus the sum of the digits of the absolute
value of the y coordinate are lesser than or equal to 19 are accessible to the monkey.
For example, the point (59, 79) is inaccessible because 5 + 9 + 7 + 9 = 30, which is
greater than 19. Another example: the point (-5, -7) is accessible because abs(-5) +
abs(-7) = 5 + 7 = 12, which is less than 19. How many points can the monkey access
if it starts at (0, 0), including (0, 0) itself?

Input sample:

There is no input for this program.

Output sample:

Print the number of points the monkey can access. It should be printed as an
integer, for example, if the number of points is 10, print "10", not "10.0" or
"10.00", etc.
'''

"""
determine if a new coordianate is valid or not
"""
def check_new_coordinate(in_coor, max_val):
    xval = str(abs(in_coor[0]));
    yval = str(abs(in_coor[1]));

    count = 0
    for char in xval:
        count+=int(char)
    for char in yval:
        count+=int(char)

    if(count<=max_val):
        return(True)
    else:
        return(False)

"""
Return all the nearby coordinates of a given coordinate if accessible
"""
def find_close_by_coors(in_coor, max_val):
    return_arr = []

    if check_new_coordinate((in_coor[0]+1,in_coor[1]), max_val):
        return_arr.append((in_coor[0]+1,in_coor[1]))
    if check_new_coordinate((in_coor[0],in_coor[1]+1), max_val):
        return_arr.append((in_coor[0],in_coor[1]+1))
    if check_new_coordinate((in_coor[0]-1,in_coor[1]), max_val):
        return_arr.append((in_coor[0]-1,in_coor[1]))
    if check_new_coordinate((in_coor[0],in_coor[1]-1), max_val):
        return_arr.append((in_coor[0],in_coor[1]-1))

    return(return_arr)

"""
Main function
Calculates the number of points accessible by doing a breadth first search
through the solution space
"""
def grid_walk(start_coor, max_sum_val):
    #Create dictionary that stores all the points already visited index by coordinate
    point_already_visited = {}
    point_already_visited[start_coor] = True

    #create "pseudo stack" for breadth first search
    pseudo_stack = [start_coor]
    count = 1
    
    while(len(pseudo_stack)):
        new_coor = pseudo_stack.pop(0)
        close_by_coors = find_close_by_coors(new_coor, max_sum_val)

        #if not visited add to stack and mark as visited
        for coor in close_by_coors:
            try:
                is_in_dict = point_already_visited[coor]
            except KeyError:
                #item not in dictionary add to dictionary and add to stack
                point_already_visited[coor] = True
                pseudo_stack.append(coor)
                count+=1

    print(count)

s_coor = (0,0)
max_s_val = 19
all_points_accessible = grid_walk(s_coor, max_s_val)


    
