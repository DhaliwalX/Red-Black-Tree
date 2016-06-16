#ifndef RBTREE_H_
#define RBTREE_H_

#include <string>
#include <utility>

#define THROW(str) std::string(str)
#define __ inline

enum Color { RED, BLACK };

template <typename KeyType, typename DataType>
class RBTree;
template <typename KeyType, typename DataType>
class _const_Tree_Iterator;
template <typename KeyType, typename DataType>
class _Tree_Iterator;

template <typename KeyType, typename DataType>
class RBNode {
  friend class RBTree<KeyType, DataType>;
  friend class _const_Tree_Iterator<KeyType, DataType>;
  friend class _Tree_Iterator<KeyType, DataType>;
public:

	RBNode(const KeyType key, const DataType data) :
		key_(key), data_(data), parent_{ nullptr },
		left_(nullptr), right_(nullptr), color_(RED)
	{ }

	RBNode(const KeyType key, const DataType data,
		RBNode *left, RBNode *right, RBNode *parent) :
		key_(key), data_(data), left_(left),
		right_(right), parent_(parent), color_(RED)
	{ }

	RBNode(const RBNode& node) :
		key_(node.key_), data_(node.data_), left_(node.left_),
		right_(node.right_), parent_(node.parent_), color_(RED)
	{ }

	RBNode & operator=(const RBNode &node) {
		key_ = node.key_;
		data_ = node.data_;
		left_ = node.left_;
		right_ = node.right_;
		parent_ = node.parent_;
		color_ = node.color_;
		return *this;
	}

	RBNode() :
		key_(), data_(), left_(nullptr),
    right_(nullptr), parent_(nullptr)
	{ }

	~RBNode()
	{ }

  KeyType &Key() {
    return key_;
  }

  KeyType Key() const {
    return key_;
  }

private:
	RBNode *parent_;
	RBNode *left_;
	RBNode *right_;
	KeyType key_;
	DataType data_;
	Color color_;
};
 
template <typename KeyType, typename DataType>
class _const_Tree_Iterator {
public:
  using pointer = typename RBNode<KeyType, DataType>*;
  using NodeType = typename RBNode<KeyType, DataType>;

  _const_Tree_Iterator(RBNode<KeyType, DataType> *ptr) :
    ptr_(ptr)
  { }

  _const_Tree_Iterator(const _const_Tree_Iterator &rhs) :
    ptr_(rhs.ptr_)
  { }

  _const_Tree_Iterator() :
    ptr_(nullptr)
  { }

  _const_Tree_Iterator<KeyType, DataType>
    operator=(const _const_Tree_Iterator<KeyType, DataType> &rhs)
  {
    ptr_ = rhs.ptr_;
    return *this;
  }

  const pointer operator->()
  {
    return this->ptr_;
  }

  const RBNode<KeyType, DataType> &operator*()
  {
    return *(this->ptr_);
  }

  _const_Tree_Iterator<KeyType, DataType> operator++()
  { // increments the iterator
    pointer parent = nullptr;
    if (IsNil(ptr_))
      ;
    else if (!IsNil(Right(ptr_))) {
      RBNode<KeyType, DataType> *min = _Min(Right(ptr_));
      ptr_ = min;
    }
    else if (!IsNil(parent = Parent(ptr_)))
    { // go up to find left subtree
      while (!IsNil(parent = Parent(ptr_))
        && (ptr_ == Right(parent)))
        ptr_ = parent;
      ptr_ = parent;
    }
    else
      ptr_ = nullptr;// throw THROW("iterator out of range");
    return *this;
  }

  _const_Tree_Iterator operator++(int)
  { // post-increment
    pointer Old = (*this).ptr_;
    ++(*this);
    return _const_Tree_Iterator<KeyType, DataType>(Old);
  }

  _const_Tree_Iterator<KeyType, DataType> operator--()
  { // pre-decrement
    pointer parent = nullptr;
    if (IsNil(ptr_))
    { // if ptr_ is end()
 
    }
    else if (!IsNil(Left(ptr_))) 
    { // set ptr to left-subtree of ptr
      ptr_ = _Max(Left(ptr_));
    }
    else if (!IsNil(Parent(ptr_)))
    { // go up to find right subtree
      while (!IsNil(Left(parent = Parent(ptr_)))
        && (ptr_ == Left(parent)))
        ptr_ = parent;
    }
    else
      ;// throw THROW("iterator out of range");
  }

  _const_Tree_Iterator<KeyType, DataType> operator--(int)
  { // post-decrement
    pointer Old = (*this).ptr_;
    --(*this);
    return _const_Tree_Iterator<KeyType, DataType>(Old);
  }

  bool operator==(const _const_Tree_Iterator<KeyType, DataType> &rhs)
  {
    return this->ptr_ == rhs.ptr_;
  }

  bool operator!=(const _const_Tree_Iterator<KeyType, DataType> &rhs)
  {
    return this->ptr_ != rhs.ptr_;
  }

private:
  __ pointer _Min(pointer node) const
  { // returns minimum of the tree
    pointer parent = nullptr;

    // go to leftmost leaf or child
    while (!IsNil(node)) {
      parent = node;
      node = Left(node);
    }
    return parent;
  }

  __ pointer _Max(pointer node) const
  { // returns maximum key element
    pointer parent = nullptr;

    while (!IsNil(node))
    { // go to the rightmost subtree
      parent = node;
      node = Right(node);
    }
    return parent;
  }

  __ pointer& Parent(pointer &node) const
  { // get the parent of the node
    return node->parent_;
  }

  __ pointer& Left(pointer &node) const
  { // get the left child of the node
    return node->left_;
  }

  __ pointer& Right(pointer &node)
  { // get the roght child of the node
    return node->right_;
  }

  // as described in CLRS, we consider the null nodes
  // as nil[T] and color of these nodes is black
  __ Color _Color(pointer &node)
  { // get the color of the node
    return !IsNil(node) ? node->color_ : Color::BLACK;
  }

  __ KeyType &Key(pointer &node) const
  { // return the key of the node
    return node->key_;
  }

  __ bool IsNil(pointer &node) const
  { // returns true if node is nullptr
    return node == nullptr;
  }
  RBNode<KeyType, DataType> *ptr_;
};

template <typename KeyType, typename DataType>
class _Tree_Iterator {
  using pointer =  typename RBNode<KeyType, DataType>*;
  using NodeType = typename RBNode<KeyType, DataType>;
public:
  _Tree_Iterator(RBNode<KeyType, DataType> *ptr) :
    ptr_(ptr)
  { }

  _Tree_Iterator(const _Tree_Iterator &rhs) :
    ptr_(rhs.ptr_)
  { }

  _Tree_Iterator() :
    ptr_(nullptr)
  { }

  _Tree_Iterator<KeyType, DataType>
    operator=(const _Tree_Iterator<KeyType, DataType> &rhs)
  {
    ptr_ = rhs.ptr_;
    return *this;
  }

  pointer *operator->()
  {
    return this->ptr_;
  }

  RBNode<KeyType, DataType> &operator*()
  {
    return *(this->ptr_);
  }

  _Tree_Iterator<KeyType, DataType> operator++()
  { // increments the iterator
    pointer parent = nullptr;
    if (IsNil(ptr_))
      ;
    else if (!IsNil(Right(ptr_))) {
      RBNode<KeyType, DataType> *min = _Min(Right(ptr_));
      ptr_ = min;
    }
    else if (!IsNil(parent = Parent(ptr_)))
    { // go up to find left subtree
      while (!IsNil(parent = Parent(ptr_))
        && (ptr_ == Right(parent)))
        ptr_ = parent;
      ptr_ = parent;
    }
    else
      ptr_ = nullptr;
    return *this;
  }

  _Tree_Iterator operator++(int)
  { // post-increment
    pointer Old = (*this).ptr_;
    ++(*this);
    return _Tree_Iterator<KeyType, DataType>(Old);
  }

  _Tree_Iterator<KeyType, DataType> operator--()
  { // pre-decrement
    pointer parent = nullptr;
    if (IsNil(ptr_))
    { // if ptr_ is end()

    }
    else if (!IsNil(Left(ptr_)))
    { // set ptr to left-subtree of ptr
      ptr_ = _Max(Left(ptr_));
    }
    else if (!IsNil(Parent(ptr_)))
    { // go up to find right subtree
      while (!IsNil(Left(parent = Parent(ptr_)))
        && (ptr_ == Left(parent)))
        ptr_ = parent;
    }
    else
      throw THROW("iterator out of range");
  }

  _Tree_Iterator<KeyType, DataType> operator--(int)
  { // post-decrement
    pointer Old = (*this).ptr_;
    --(*this);
    return _Tree_Iterator<KeyType, DataType>(Old);
  }

  _Tree_Iterator operator+(size_t Off)
  { // move the iterator by Off
    while (Off-- > 0)
      ++(*this);
  }

  bool operator==(const _Tree_Iterator<KeyType, DataType> &rhs)
  {
    return this->ptr_ == rhs.ptr_;
  }

  bool operator!=(const _Tree_Iterator<KeyType, DataType> &rhs)
  {
    return this->ptr_ != rhs.ptr_;
  }


  RBNode<KeyType, DataType> * _Ptr()
  {
    return this->ptr_;
  }
private:
  __ pointer _Min(pointer node) const
  { // returns minimum of the tree
    pointer parent = nullptr;

    // go to leftmost leaf or child
    while (!IsNil(node)) {
      parent = node;
      node = Left(node);
    }
    return parent;
  }

  __ pointer _Max(pointer node) const
  { // returns maximum key element
    pointer parent = nullptr;

    while (!IsNil(node))
    { // go to the rightmost subtree
      parent = node;
      node = Right(node);
    }
    return parent;
  }

  __ pointer& Parent(pointer &node) const
  { // get the parent of the node
    return node->parent_;
  }

  __ pointer& Left(pointer &node) const
  { // get the left child of the node
    return node->left_;
  }

  __ pointer& Right(pointer &node)
  { // get the roght child of the node
    return node->right_;
  }

  // as described in CLRS, we consider the null nodes
  // as nil[T] and color of these nodes is black
  __ Color _Color(pointer &node)
  { // get the color of the node
    return !IsNil(node) ? node->color_ : Color::BLACK;
  }

  __ KeyType &Key(pointer &node) const
  { // return the key of the node
    return node->key_;
  }

  __ bool IsNil(pointer &node) const
  { // returns true if node is nullptr
    return node == nullptr;
  }

  RBNode<KeyType, DataType> *ptr_;
};

template <typename KeyType, typename DataType>
class RBTree {
public:
  using pointer = RBNode<KeyType, DataType>*;
  using pair = std::pair<KeyType, DataType>&;
  using NodeType = typename RBNode<KeyType, DataType>;
  using size_type = unsigned int;
  using const_iterator =
    typename _const_Tree_Iterator<KeyType, DataType>;
  using iterator =
    typename _Tree_Iterator<KeyType, DataType>;

public:
  RBTree() :
    root_(nullptr), size_(0)
  { }

  RBTree(const RBTree<KeyType, DataType> &rhs) :
    size_(0), root_(nullptr)
  { // copy from another tree
    if (!empty())
      clear();
    _Clone(rhs.cbegin(), rhs.cend());
    
  }

  RBTree& operator=(const RBTree<KeyType, DataType> &rhs)
  { // assigns one tree to another
    if ((*this) != rhs) {
      if (!empty())
        clear();
      _Clone(rhs.cbegin(), rhs.cend())
    }
  }

  ~RBTree()
  { // destructor
    if (!empty())
      clear();
  }

  // true if empty
  bool empty()
  { return !size(); }

  // returns the number of nodes
  size_type size() 
  { return size_; }

  iterator insert(const KeyType &key, const DataType &data)
  { // inserts key with data to the tree
    pointer node =
      new RBNode<KeyType, DataType>(key, data);
    root_ = _Insert(root_, node);
    return iterator(node);
  }  

  iterator insert(const std::pair<KeyType, DataType> &p)
  {
    pointer node = new RBNode<KeyType, DataType>(p.first, p.second);
    root_ = _Insert(root_, node);
    return iterator(node);
  }

  void insert_or_assign(const KeyType &key, const DataType &data)
  { // inserts if key doesn't exists, otherwise assigns data to the key
    pointer exists = _Search(root_, key);
    if (exists == nullptr)
      insert(key, data);
    else {
      exists->data_ = data;
    }
  }

  // void insert(iterator & it, const KeyType &key)
  //{ // unimplemented
  // since insertion at arbitrary place in red black tree is not
  // possible. Think of inserting 5 at position 1 in { 1, 2, 3, 4 }
  // }
  
  void erase(const KeyType &key)
  {
    pointer toDelete = _Search(root_, key);
    
    if (toDelete == nullptr) return;

    toDelete = _Delete(root_, toDelete);
    delete toDelete;
  }

  void erase(iterator &_start, iterator &_end)
  { // erases all the elements in range ==> [_start, _end)
    _Erase_range(_start, _end);
  }

  const_iterator cbegin() const 
  { // returns const_iterator to the minimum key
    return const_iterator(_Min(root_));
  }

  const_iterator cend() const
  { // returns const_iterator to the nil[T]
    return const_iterator();
  }

  iterator begin()
  { // returns iterator to the minimum element
    return iterator(_Min(root_));
  }

  iterator end()
  { // returns iterator to the nil[T]
    return iterator();
  }

  void erase(const iterator &it)
  {
    this->_Safe_remove(it);
  }

  void clear()
  {
    _Clear(root_);
  }

  const_iterator search(const KeyType &key) const
  {
    pointer searched = _Search(root_, key);
    return const_iterator(searched);
  }

  iterator search(const KeyType &key)
  {
    pointer searched = _Search(root_, key);
    return iterator(searched);
  }

  DataType operator[](const KeyType &_key) const
  { // returns data field corresponding to the key
    pointer searched = _Search(root_, _key);
    if (searched == nullptr)
      return DataType();
    else
      return searched->data_;
  }

  DataType& operator[](const KeyType &_key)
  { // returns data field corresponding to the key
    pointer searched = _Search(root_, _key);
    if (searched == nullptr) 
    { // inserts the key into the tree
      iterator inserted = insert(_key, DataType());
      return (*inserted).data_;
    }
    else
      return searched->data_;
  }


private:

  void _Assign(pointer &node)
  { // assigns one element to the tree, removing others
    _Clear(root_);
    root_ = _Insert(root_, node);
  }

  void _Clone(const_iterator &_start, const_iterator &_end)
  { // _Clones from tree into root tree
    for (const_iterator it = _start; it != _end; ++it)
    { // inserts every node pointed by iterator
      pointer node = _Create_node((*it).key_, (*it).data_);
      root_ = _Insert(root_, node);
    }
  }

  void _Clear(pointer &root)
  { // clears in post-order
    if (!empty())
      _Erase_range(begin(), end());
  }

  void _Safe_remove(pointer &node)
  { // safely removes the node, preserving RB properties
    pointer target = _Delete(root_, node);
    delete target;
  }

  void _Safe_remove(iterator node)
  { // safely removes the element preserving RB properties
    pointer target = (node)._Ptr();
    target = _Delete(root_, target);
    delete target;
  }

  void _Erase_range(const iterator &_start, const iterator &_end)
  { // erases range of elements from _start to _end
    iterator itr = _start, next = _start, prev = _start;
    if (itr != end())
      do {
        itr = next++;
        _Safe_remove(itr);
       // std::cout << (*next).key_;
      } while (next != _end);
  }

  pointer _Search(pointer &root, const KeyType &key) const
  { // returns pointer to the node if found with key_ = key
    pointer ptr = root;
    while (!IsNil(ptr)) {
      if (key == ptr->key_)
        break;
      else if (key < ptr->key_)
        ptr = ptr->left_;
      else ptr = ptr->right_;
    }
    return ptr;
  }

  //////////////////////////////////////////////////////////////////
  //| 
  //|        |                                       |
  //|       (A)                                     (B)
  //|      /   \                                   /   \
  //|     /     \           -------->             /     \
  //|   {x}     (B)                             (A)     {z}
  //|          /   \                           /   \
  //|         /     \                         /     \
  //|        {y}    {z}                     {x}     {y}
  //|
  //| node == A & pivotEnd == B
  //////////////////////////////////////////////////////////////////
  pointer LeftRotate(pointer& root, pointer node)
  { // rotates towards the left pivoted at <node, Right[node]>
    
    // splice the right subtree of node
    pointer pivotEnd = Right(node);

    // splice the left child of pivotEnd
    // and join to the right child of node
    node->right_ = Left(pivotEnd);

    if (pivotEnd->left_ != nullptr)
      pivotEnd->left_->parent_ = node;

    // update the parent field of pivotEnd
    pivotEnd->parent_ = Parent(node);

    if (Parent(node) == nullptr) // node was root
      root = pivotEnd;
    else if (node == Left(Parent(node)))
      node->parent_->left_ = pivotEnd; // join to the left
    else node->parent_->right_ = pivotEnd; // else right
    
    // join node to the left of pivotEnd
    pivotEnd->left_ = node;
    node->parent_ = pivotEnd;

    // not required
    return pivotEnd;
  }


  
  //////////////////////////////////////////////////////////////////
  //| 
  //|           |                                       |
  //|          (A)                                     (B)
  //|         /   \                                   /   \
  //|        /     \           -------->             /     \
  //|      (B)     {z}                             {x}     (A)
  //|     /   \                                           /   \
  //|    /     \                                         /     \
  //|  {x}     {y}                                      {y}    {z}
  //|
  //| node == A & pivotEnd == B
  //////////////////////////////////////////////////////////////////
  pointer
    RightRotate(pointer& root, pointer node)
  { // right symmetry of LeftRotate
    pointer pivotEnd = Left(node);
    node->left_ = Right(pivotEnd);
    
    if (pivotEnd->right_ != nullptr)
      pivotEnd->right_->parent_ = node;
    pivotEnd->parent_ = Parent(node);

    if (Parent(node) == nullptr)
      root = pivotEnd;
    else if (node == Left(Parent(node)))
      node->parent_->left_ = pivotEnd;
    else node->parent_->right_ = pivotEnd;

    pivotEnd->right_ = node;
    node->parent_ = pivotEnd;
    return pivotEnd;
  }

  pointer
    _Insert(pointer &root, pointer node)
  { // primitive insert operation required by other members
    pointer parent = nullptr;
    pointer itr = root;

    // find the right place where node needs to be inserted
    while (itr != nullptr) {
      parent = itr;
      if (node->key_ < itr->key_)
        itr = itr->left_;
      else
        itr = itr->right_;
    }
    node->parent_ = parent;
    if (parent == nullptr)
      root = node;
    else if (Key(node) < Key(parent))
      parent->left_ = node;
    else parent->right_ = node;
    _FixInsert(root, node);
    size_++;
    return root;
  }

  void _FixInsert(pointer &root, pointer node)
  { // fixes the red-black properties disturbed due to insertion
    pointer uncle = nullptr;
    while (_Color(Parent(node)) == RED) {
      if (Parent(node) == Left(Parent(Parent(node)))) {
        uncle = Right(Parent(Parent(node))); // get the uncle

        // case 1: node's uncle is RED
        if (_Color(uncle) == RED) {
          node->parent_->color_ = BLACK;
          uncle->color_ = BLACK;
          node->parent_->parent_->color_ = RED;
          node = node->parent_->parent_;
        }
        // case 2 & 3: node's uncle is BLACK
        else {
          // node is right child
          if (node == Right(Parent(node))) {
            node = Parent(node);
            LeftRotate(root, node);
          }

          // node is right or left child
          node->parent_->color_ = BLACK;
          node->parent_->parent_->color_ = RED;
          RightRotate(root, node->parent_->parent_);
        }
      }
      // right symmetry
      else {
        uncle = Left(Parent(Parent(node)));

        if (_Color(uncle) == RED) {
          node->parent_->color_ = BLACK;
          uncle->color_ = BLACK;
          node->parent_->parent_->color_ = RED;
          node = node->parent_->parent_;
        }
        else {
          if (node == Left(Parent(node))) {
            node = Parent(node);
            RightRotate(root, node);
          }

          node->parent_->color_ = BLACK;
          node->parent_->parent_->color_ = RED;
          LeftRotate(root, node->parent_->parent_);
        }
      }
    } // while 
    root->color_ = BLACK;
  }

  void 
    _Transplant_satellite_data(pointer &from, pointer &to)
  { // swaps the links of the to nodes from and to
    pointer left = Left(from), right = Right(from), parent = Parent(from);
    Color c = _Color(from);
    from->parent_ = Parent(to);
    from->left_ = Left(to);
    if (!IsNil(from->left_))
      from->left_->parent_ = from;
    from->right_ = Right(to);
    if (!IsNil(Right(from)))
      from->right_->parent_ = from;
    if (IsNil(Parent(to)))
      root = from;
    else if (to == Left(Parent(to)))
      to->parent_->left_ = from;
    else
      to->parent_->right_ = from;
    from->color_ = _Color(to);
    to->parent_ = parent;
    to->left_ = left;
    to->right_ = right;
    to->color_ = c;
  }

  // deletion algorithm as described in CLRS except that 
  // 1) A special node nil[T] may be made for deletion to
  //    be accurate, rest is same
  // 2) Instead of copying data from the node, node is linked
  //    where it was needed to be copied
  pointer
    _Delete(pointer &root, pointer node)
  { // will delete the node from the tree root[T]
    pointer toDelete = nullptr;
    Color c = RED;
    bool nil = false;

    // get the accurate node that needs to be deleted
    if (!IsNil(Left(node)) && !IsNil(Right(node))) // if both child exists
      toDelete = _Min(Right(node)); // then get the next successor of the node
    else
      toDelete = node;

    pointer toFix = nullptr;
    
    // get the child of the toDelete, that may be needed to be fix
    if (!IsNil(Left(toDelete)))
      toFix = Left(toDelete); // split the left subtree
    else
      toFix = Right(toDelete); // split the right subtree

    // if toFix was nullptr, then create a new node
    // nil[T] whose color is black, and set nil = true
    if (IsNil(toFix)) {
      toFix = new NodeType();
      toFix->color_ = BLACK;
      nil = true;
    }

    toFix->parent_ = toDelete->parent_;

    if (IsNil(Parent(toDelete)))  // if toDelete was root
      root = toFix;
    else if (toDelete == Left(Parent(toDelete))) 
      toDelete->parent_->left_ = toFix; // join the subtree
    else
      toDelete->parent_->right_ = toFix;

    c = _Color(toDelete);

    if (toDelete != node)  // if toDelete has atmost one child
    { // link the toDelete here
      _Transplant_satellite_data(toDelete, node);
      std::swap(toDelete, node);
    }

    if (c == BLACK)
      _Delete_Fixup(root, toFix);

    // if nil node was created then we have to remove it
    // otherwise memory would be wasted 
    if (nil == true) {
      // check the position of the toFix node
      if (IsNil(Parent(toFix)))
        root = nullptr;
      else if (toFix == Left(Parent(toFix)))
        toFix->parent_->left_ = nullptr;
      else
        toFix->parent_->right_ = nullptr;

      // free the memory
      delete toFix;
    }
    size_--;
    return toDelete;
  }

  void _Delete_Fixup(pointer &root, pointer node)
  { // it fixes the RB properties if changed due to deletion
    pointer sibling = nullptr;
    while (node != root && _Color(node) == BLACK) {
      if (node == Left(Parent(node))) {
        sibling = Right(Parent(node));
        // case 1: node's sibling is RED
        if (_Color(sibling) == RED) {
          sibling->color_ = BLACK;
          node->parent_->color_ = RED;
          LeftRotate(root, Parent(node));
          sibling = Right(Parent(node));
        } // now case 1 will be reduced to case 2, 3, or 4

        // case 2: node's sibling is BLACK,
        // both of sibling's children are BLACK,
        if (_Color(Left(sibling)) == BLACK &&
          _Color(Right(sibling)) == BLACK) {
          sibling->color_ = RED;
          node = node->parent_;
        }
        else {
          // case3 : sibling is BLACK, 
          // sibling's left child is RED, 
          // sibling's right child is BLACK
          if (_Color(Right(sibling)) == BLACK) {
            sibling->left_->color_ = BLACK;
            sibling->color_ = RED;
            RightRotate(root, sibling);
            sibling = Right(Parent(node));
          }

          // case 4 : sibling is BLACK, 
          // sibling's right child is RED
          sibling->color_ = _Color(Parent(node));
          node->parent_->color_ = BLACK;
          sibling->right_->color_ = BLACK;
          LeftRotate(root, Parent(node));
          node = root;
        }
      }
      else 
      { // case 5, 6, 7, and 8 are symmetrically 
        // opposite to case 1, 2, 3 and 4 resp.
        sibling = Left(Parent(node));

        // case 5
        if (_Color(sibling) == RED) {
          sibling->color_ = BLACK;
          node->parent_->color_ = RED;
          RightRotate(root, Parent(node));
          sibling = Left(Parent(node));
        }

        // case 6
        if (_Color(Right(sibling)) == BLACK
          && _Color(Left(sibling)) == BLACK) {
          sibling->color_ = RED;
          node = node->parent_;
        }
        else {

          // case 7
          if (_Color(Left(sibling)) == BLACK) {
            sibling->right_->color_ = BLACK;
            sibling->color_ = RED;
            LeftRotate(root, sibling);
            sibling = Left(Parent(node));
          }

          // case 8
          sibling->color_ = _Color(Parent(node));
          node->parent_->color_ = BLACK;
          sibling->left_->color_ = BLACK;
          RightRotate(root, Parent(node));
          node = root;
        }
      }
    }

    if (!IsNil(node))
      node->color_ = BLACK;
  }

  __ pointer _Min(pointer node) const
  { // returns minimum of the tree
    pointer parent = nullptr;

    // go to leftmost leaf or child
    while (!IsNil(node)) {
      parent = node;
      node = Left(node);
    }
    return parent;
  }

  __ pointer _Max(pointer node) const
  { // returns maximum key element
    pointer parent = nullptr;

    while (!IsNil(node))
    { // go to the rightmost subtree
      parent = node;
      node = Right(node);
    }
    return parent;
  }

  __ pointer& Parent(pointer &node) const
  { // get the parent of the node
    return node->parent_;
  }

  __ pointer& Left(pointer &node) const
  { // get the left child of the node
    return node->left_;
  }

  __ pointer& Right(pointer &node)
  { // get the roght child of the node
    return node->right_;
  }

  // as described in CLRS, we consider the null nodes
  // as nil[T] and color of these nodes is black
  __ Color _Color(pointer &node)
  { // get the color of the node
    return !IsNil(node) ? node->color_ : Color::BLACK;
  }

  __ KeyType &Key(pointer &node) const 
  { // return the key of the node
    return node->key_;
  }

  __ bool IsNil(pointer &node) const
  { // returns true if node is nullptr
    return node == nullptr;
  }

  __ pointer _Create_node(const KeyType &key, const DataType &data)
  { // allocates memory for new node
    return new NodeType(key, data);
  }
private:
	RBNode<KeyType, DataType> *root_;
  size_type size_;
};

#endif
