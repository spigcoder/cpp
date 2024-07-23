#pragma once
#include <cassert>
#include <iostream>
using namespace std;

enum Colour{
    RED,
    BLACK
};

template<typename V>
struct RBNode{
    RBNode(V kv =  V())
    :_data(kv),
    _col(RED),
    _left(nullptr),
    _right(nullptr),
    _parent(nullptr)
    {}

   V _data;
   Colour _col;
   RBNode<V>* _left; 
   RBNode<V>* _right; 
   RBNode<V>* _parent; 
};

template<typename V, typename Ref, typename Ptr>
class Iterator{
    using Node = RBNode<V>;

public:
    Iterator(Node* node, Node* root)
    :_node(node),
    _root(root)
    {}

    using self = Iterator<V, Ref, Ptr>;
    using iterator = Iterator<V, V&, V*>;

    Ref operator*() const{
        return _node->_data;
    }

    Ptr operator->() const{
        return &(operator*());
    }

    //对于二叉树而言，operator++就是采用中序进行历遍操作
    self& operator++(){
        assert(_node != nullptr);
        //如果有右孩子，那么下一个就是右孩子的最左节点
        if(_node->_right){
            Node* left_most = _node->_right;
            while(left_most->_left){
                left_most = left_most->_left;
            }
            _node = left_most;
        }else{
            //如果没有右节点表示以_node为根的子树已经全部走完了，那就看他的父亲
            //如果它是他的父亲的左树，那么下一个就是它的父亲，否则以他的父亲为根的子树也走完了，接着寻找
            Node* parent = _node->_parent;
            while(parent && _node == parent->_right){
                _node = parent;
                parent = _node->_parent; 
            }
            _node = parent;
        }
        return *this;
    }

    self& operator--(){
        if(_node == nullptr){
            //返回最右节点
            assert(_root != nullptr);
            Node* most_right_node = _root;
            while(most_right_node->_right){
                most_right_node = most_right_node->_right;
            }
            _node = most_right_node;
        }else{
            //这里是一个反中序遍历，就是右节点，根，左节点
            if(_node->_left){
                //返回最节点的最有节点
                Node* most_right_node = _node->_left;
                while(most_right_node->_right){
                    most_right_node = most_right_node->_right;
                }
                _node = most_right_node;
            }else{
                Node* parent = _node->_parent;
                while(parent && _node == parent->_left){
                    _node = parent;
                    parent = _node->_parent; 
                }
                _node = parent;
            }
        }
        return *this;
    }

    bool operator!=(const self& it){
        return it._node != _node;
    }

    bool operator==(const self& it){
        return it._node == _node;
    }

private:
//这样写只是一个简洁版的set迭代器，如果RBTree出现翻转的化，就会有迭代器失效的问题，因为root变了
    Node* _node = nullptr;
    Node* _root = nullptr;
};


//为什么需要KeyOfValue -> 因为map和set是需要不同的value的map是pair，set是k，这时候就有人有些疑问
//既然不用K，为什么还要将K传进来呢，有的api要用比如find -> find只知道K不知道value
template<typename K, typename V, typename KeyOfValue>
class RBTree{
private:
    using Node = RBNode<V>;
    bool _IsBalance(Node* root, const int& black_num, int cur_black_num);
    void RotateL(Node* parent);
    void RotateR(Node* parent);
    void RotateLR(Node* parent);
    void RotateRL(Node* parent);       
    int _Height(Node* root);
private:

public:
    using iterator = Iterator<V, V&, V*>;
    using const_iterator = Iterator<V, const V&, const V*>;

    iterator begin(){
        //返回最左节点
        Node* left_most = _root;
        while(left_most->_left){
            left_most = left_most->_left;
        }
        return iterator(left_most, _root);
    }

    iterator end(){
        //返回最左节点
        return iterator(nullptr, _root);
    }

    RBTree() = default;
    bool insert(const V& kv);
    Node* find(const K& key);
    bool IsBalance() { 
        if(_root == nullptr) return true;
        if(_root->_col == RED) return false;
        int black_num = 0;
        Node* cur = _root;
        while(cur){
            if(cur->_col == BLACK) black_num++;
            cur = cur->_left;
        }
        _IsBalance(_root, black_num, 0);
    }
    int Height() { return _Height(_root); }
private:
    Node* _root = nullptr;
};

template<typename K, typename V, typename KeyOfValue>
int RBTree<K, V, KeyOfValue>::_Height(Node* root){
    if(root == nullptr) return 0;

    int left_height = _Height(root->_left);
    int right_height = _Height(root->_right);

    return left_height > right_height ? left_height+1 : right_height+1;
}

template<typename K, typename V, typename KeyOfValue>
bool RBTree<K, V, KeyOfValue>::_IsBalance(Node* root, const int& black_num, int cur_black_num){
    if(root == nullptr){
        if(cur_black_num == black_num) return true;
        else{
            cout << "路径上黑节点数量不相同" <<endl;
            return false;
        } 
    } 
    if(root->_col == BLACK) cur_black_num++;

    if(root->_col == RED) {
        if(root->_parent->_col == RED){ 
            cout << root->_kv.first << " " << root->_parent->_kv.first << endl;
            assert(false);
            return false;
        }
    }

    bool is_balance_left = _IsBalance(root->_left, black_num, cur_black_num);
    bool is_balance_right = _IsBalance(root->_right, black_num, cur_black_num);
    return is_balance_left && is_balance_right;
}


template<typename K, typename V, typename KeyOfValue>
typename RBTree<K, V, KeyOfValue>::Node* RBTree<K, V, KeyOfValue>::find(const K& key){
    Node *cur = _root, *parent = _root;
    KeyOfValue kov;
    while(cur){
        parent = cur;
        if(key > kov(cur->_data)){
            cur = cur->_right;
        }else if(key < kov(cur->_data)){
            cur = cur->_left;
        }else{
            return cur;
        }
    }
    return nullptr;
}


template<typename K, typename V, typename KeyOfValue>
bool RBTree<K, V, KeyOfValue>::insert(const V& kv){
    if(_root == nullptr){
        _root = new Node(kv);
        _root->_col = BLACK;
        return true;
    }
    KeyOfValue kov;
    //find position to insert
    Node *cur = _root, *parent = _root;
    while(cur){
        parent = cur;
        if(kov(kv) > kov(cur->_data)){
            cur = cur->_right;
        }else if(kov(kv) < kov(cur->_data)){
            cur = cur->_left;
        }else{
            return false;
        }
    }

    //link
    Node* node = new Node(kv);
    if(kov(kv) > kov(parent->_data)){
        parent->_right = node;
    }else{
        parent->_left = node;
    }
    node->_parent = parent;

    while(parent && parent->_col == RED){
        Node* grandfather = parent->_parent;
        //      g
        //    p   u 
        if(parent == grandfather->_left){
            Node* uncle = grandfather->_right;
            //uncle 存在且是红色
            if(uncle && uncle->_col == RED){
                //更改颜色
                parent->_col = uncle->_col = BLACK;
                grandfather->_col = RED;
                //向上更新
                node = grandfather;
                parent = node->_parent;
            }else if(uncle == nullptr || uncle->_col == BLACK){
                //需要进行旋转
                if(node == parent->_left){
                    //          g
                    //      p       u
                    // n -> 进行右单旋
                    RotateR(grandfather);
                    parent->_col = BLACK;
                    grandfather->_col = RED;
                    break;
                }else if(node == parent->_right){
                    //          g
                    //      p       u
                    //          n -> 进行左右双旋
                    RotateL(parent);
                    RotateR(grandfather);
                    node->_col = BLACK;
                    grandfather->_col = RED;
                    break;
                }else{
                    assert(false);
                }
            }else{
                assert(false);
            }
        }else{
            Node* uncle = grandfather->_left;
            if(uncle && uncle->_col == RED){
                uncle->_col = parent->_col = BLACK;
                grandfather->_col = RED;
                node = grandfather;
                parent = node->_parent;
            }else if(uncle == nullptr || uncle->_col == BLACK){
                if(node == parent->_right){
                    //          g
                    //      u       p
                    //                  n -> 进行左单旋
                    RotateL(grandfather);
                    parent->_col = BLACK;
                    grandfather->_col = RED;
                    break;
                }else if(node == parent->_left){
                    //          g
                    //      u       p
                    //           n -> 进行右左单旋
                    RotateR(parent);
                    RotateL(grandfather);
                    node->_col = BLACK;
                    grandfather->_col = RED;
                    break;
                }else {
                    assert(false);
                }
            }else{
                assert(false);
            }
        }
    }

    _root->_col = BLACK;
}

template<typename K, typename V, typename KeyOfValue>
void RBTree<K, V, KeyOfValue>::RotateL(Node* parent){
    Node* SubR = parent->_right;
    Node* SubRL = SubR->_left;
    Node* Parent_parent = parent->_parent;

    SubR->_left = parent;
    parent->_parent = SubR;
    parent->_right = SubRL;
    if(SubRL) SubRL->_parent = parent; 
    if(Parent_parent == nullptr){
        _root = SubR;
    }else{
        if(parent == Parent_parent->_left){
            Parent_parent->_left = SubR;
        }else{
            Parent_parent->_right = SubR;
        }
    }
    SubR->_parent = Parent_parent;

}

template<typename K, typename V, typename KeyOfValue>
void RBTree<K, V, KeyOfValue>::RotateR(Node* parent){
    Node* SubL = parent->_left;
    Node* SubLR = SubL->_right;
    Node* Parent_parent = parent->_parent;

    SubL->_right = parent;
    parent->_parent = SubL;
    parent->_left = SubLR;
    if(SubLR) SubLR->_parent = parent;
    if(Parent_parent == nullptr){
        _root = SubL;
    }else{
        if(Parent_parent->_left == parent){
            Parent_parent->_left = SubL;
        }else{
            Parent_parent->_right = SubL;
        }
    }
    SubL->_parent = Parent_parent;

}

