# BinaryTree

**Binary search tree implementation in C++**

## Features

- `min` – returns the minimum key in the tree  
- `max` – returns the maximum key in the tree  
- `empty` – checks whether the tree is empty  
- `size` – returns the total number of elements in the tree  
- `insert` – inserts a key-value pair into the tree  
- `remove` – removes a node by key  
- `clear` – clears the entire tree  
- `find` – finds a value by key and returns a pointer to it  

## Tree Traversals

The tree supports 4 types of traversal with a user-defined callback:

- **In-order**: left → root → right  

- **Pre-order**: root → left → right  

- **Post-order**: left → right → root  

- **Level-order**: level by level from top to bottom, left to right  
