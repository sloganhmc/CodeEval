"""
Author: Sheldon Logan

Robot Movements
Description:

A robot is located at the top-left corner of a 4x4 grid. The robot can move either up,
down, left, or right, but can not visit the same spot twice. The robot is trying to
reach the bottom-right corner of the grid.

Input sample:

There is no input for this program.

Output sample:

Print out the unique number of ways the robot can reach its destination. (The number should
be printed as an integer whole number eg. if the answer is 10 (its not !!), print out 10,
not 10.0 or 10.00 etc)

"""

"""
Maps the input matrix to a graph
"""
def create_graph(in_matrix, num_rows, num_cols):
    return_graph = {}
    for row_idx in range(0,num_rows):
        for col_idx in range(0,num_cols):
            adj_nodes = []
            if(row_idx>0):
                adj_nodes.append(in_matrix[row_idx-1][col_idx])
            if(row_idx<num_rows-1):
                adj_nodes.append(in_matrix[row_idx+1][col_idx])
            if(col_idx>0):
                adj_nodes.append(in_matrix[row_idx][col_idx-1])
            if(col_idx<num_cols-1):
                adj_nodes.append(in_matrix[row_idx][col_idx+1])
            adj_nodes.sort()
            return_graph[in_matrix[row_idx][col_idx]] = adj_nodes
    return(return_graph)

"""
Find all the paths between a start node and an end node using
a breadth first search
"""
def find_all_paths(in_graph, s_node, e_node):
    pseudo_stack = [s_node]
    count = 0
    
    while(len(pseudo_stack)):
        curr_path = pseudo_stack.pop(0)
        last_node = curr_path[-1]
        if last_node == e_node:
            count+=1
        for node in in_graph[last_node]:
            if node not in curr_path:
                new_path = curr_path + node
                pseudo_stack.append(new_path)
    print(count)
    
input_matrix = [['a','b','c','d'],['e','f','g','h'],['i','j','k','l'],['m','n','o','p']]
input_graph = create_graph(input_matrix, 4, 4)
find_all_paths(input_graph, 'a', 'p')


