# Red-Black-Tree

This repository contains implementation of [Red-Black Tree](https://en.wikipedia.org/wiki/Red%E2%80%93black_tree) as described in [Introduction to Algorithms](http://www.amazon.com/Introduction-Algorithms-Thomas-H-Cormen/dp/8120340078/ref=la_B000AQ24AS_1_1/278-5160862-2398836?s=books&ie=UTF8&qid=1449314670&sr=1-1).

## Operations
- **Making a tree object**:
    To make a tree:
      > ```RBTree<KeyType, DataType> tree-name;```

- **Insertion**:
    Insertion follows the algorithm which is same as described in CLRS
    To insert an element with a key use following methods,
      > `tree-name.insert(key, data)`
    
- **Deletion**:
    Deletion is same as descirbed in CLRS except that 
      - A node nil[T] may be made during deletion. This is required for proper deletion
      - Instead of copying the data from the node, node is relinked to proper position
      - To delete an element with a key (key), use this method: 
        `tree-name.erase(key)`
      - To delete all elements in range [start, end), use this method `tree-name.erase(start, end)`
      where start and end are iterators
