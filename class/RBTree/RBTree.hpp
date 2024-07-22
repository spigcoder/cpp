#pragma once
#include <cassert>
#include <iostream>
using namespace std;

enum Colour{
    RED,
    BLACK
};

template<typename K, typename V>
struct RBNode{
    RBNode(pair<K, V> kv = {K(), V()})
    :_kv(kv),
    _col(RED),
     _left(nullptr),
    _right(nullptr),
    _parent(nullptr)
    {}

   pair<K, V> _kv;
   Colour _col;
   RBNode<K, V>* _left; 
   RBNode<K, V>* _right; 
   RBNode<K, V>* _parent; 
};


namespace spigcoder{
    template<typename K, typename V>
    class RBTree{
    private:
        using Node = RBNode<K, V>;
        void _Inorder(Node* node);
        bool _IsBalance(Node* root, const int& black_num, int cur_black_num);
        void RotateL(Node* parent);
        void RotateR(Node* parent);
        void RotateLR(Node* parent);
        void RotateRL(Node* parent);       
        int _Height(Node* root);
    public:
        RBTree() = default;
        bool insert(const pair<K, V>& kv);
        Node* find(const pair<K, V>& kv);
        void Inorder() { _Inorder(_root); }
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

    template<typename K, typename V>
    int RBTree<K, V>::_Height(Node* root){
        if(root == nullptr) return 0;

        int left_height = _Height(root->_left);
        int right_height = _Height(root->_right);

        return left_height > right_height ? left_height+1 : right_height+1;
    }

    template<typename K, typename V>
    bool RBTree<K, V>::_IsBalance(Node* root, const int& black_num, int cur_black_num){
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

    template<typename K, typename V>
    void RBTree<K, V>::_Inorder(Node* node){
        if(node == nullptr) return;
        _Inorder(node->_left);
        cout << node->_kv.first << ": " << node->_kv.second << endl;
        _Inorder(node->_right);
    }

    template<typename K, typename V>
    typename RBTree<K, V>::Node* RBTree<K, V>::find(const pair<K, V>& kv){
        Node *cur = _root, *parent = _root;
        while(cur){
            parent = cur;
            if(kv > cur->_kv.first){
                cur = cur->_right;
            }else if(kv < cur->_kv.first){
                cur = cur->_left;
            }else{
                return cur;
            }
        }
        return nullptr;
    }
    
    
    template<typename K, typename V>
    bool RBTree<K, V>::insert(const pair<K, V>& kv){
        if(_root == nullptr){
            _root = new Node(kv);
            _root->_col = BLACK;
            return true;
        }
        //find position to insert
        Node *cur = _root, *parent = _root;
        while(cur){
            parent = cur;
            if(kv.first > cur->_kv.first){
                cur = cur->_right;
            }else if(kv.first < cur->_kv.first){
                cur = cur->_left;
            }else{
                return false;
            }
        }

        //link
        Node* node = new Node(kv);
        if(kv.first > parent->_kv.first){
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

    template<typename K, typename V>
    void RBTree<K, V>::RotateL(Node* parent){
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

    template<typename K, typename V>
    void RBTree<K, V>::RotateR(Node* parent){
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

    template<typename K, typename V>
    void RBTree<K, V>::RotateRL(Node* parent){
        Node* SubR = parent->_right;
        Node* SubRL = SubR->_left;
        
        RotateR(SubR);
        RotateL(parent);
    }

    template<typename K, typename V>
    void RBTree<K, V>::RotateLR(Node* parent){
        Node* SubL = parent->_left;
        Node* SubLR = SubL->_right;
        
        RotateL(SubL);
        RotateR(parent);
    }

};