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


## Quick Example

```cpp
BinaryTree tree({
    {8,  100},
    {3,  200},
    {10, 300},
    {1,  400},
    {6,  500},
    {14, 600}
});

tree.insert(4, 700);
tree.remove(3);

if (int* value = tree.find(6))
    std::cout << "Found: " << *value << std::endl;

std::cout << "Min key: " << tree.min() << std::endl;
std::cout << "Max key: " << tree.max() << std::endl;

std::cout << "Tree size: " << tree.size() << std::endl;

tree.printTree();
```
