#pragma once
#include <iostream>
using namespace std;

template<typename K, typename V>
struct AVLNode{
    AVLNode(pair<K, V> kv = {K(), V()})
    :_kv(kv),
    _bt(0), _left(nullptr),
    _right(nullptr),_parent(nullptr)
    {}

   pair<K, V> _kv;
   int _bt; //balance factor
   AVLNode<K, V>* _left; 
   AVLNode<K, V>* _right; 
   AVLNode<K, V>* _parent; 
};


namespace spigcoder{
    template<typename K, typename V>
    class AVLTree{
    private:
        using Node = AVLNode<K, V>;
        void _Inorder(Node* node);
        bool _IsBalance(Node* root);
        void RotateL(Node* parent);
        void RotateR(Node* parent);
        void RotateLR(Node* parent);
        void RotateRL(Node* parent);       
        int _Height(Node* root);
    public:
        AVLTree() = default;
        bool insert(const pair<K, V>& kv);
        Node* find(const pair<K, V>& kv);
        void Inorder() { _Inorder(_root); }
        bool IsBalance() { return _IsBalance(_root); }
        int Height() { return _Height(_root); }
    private:
        Node* _root = nullptr;
    };

    template<typename K, typename V>
    int AVLTree<K, V>::_Height(Node* root){
        if(root == nullptr) return 0;

        int left_height = _Height(root->_left);
        int right_height = _Height(root->_right);

        return left_height > right_height ? left_height+1 : right_height+1;
    }

    template<typename K, typename V>
    bool AVLTree<K, V>::_IsBalance(Node* root){
        if(root == nullptr) return true;

        int left_height = _Height(root->_left);
        int right_height = _Height(root->_right); 

        //这里是判断错误的情况，如果正确，还要递归判断其左右子树
        if(abs(left_height - right_height) >= 2 || abs(root->_bt) >= 2)
            return false;

        bool left_is_balance = _IsBalance(root->_left);
        bool right_is_balance = _IsBalance(root->_right);

        return left_is_balance && right_is_balance;
    }

    template<typename K, typename V>
    void AVLTree<K, V>::_Inorder(Node* node){
        if(node == nullptr) return;
        _Inorder(node->_left);
        cout << node->_kv.first << ": " << node->_kv.second << endl;
        _Inorder(node->_right);
    }

    template<typename K, typename V>
    typename AVLTree<K, V>::Node* AVLTree<K, V>::find(const pair<K, V>& kv){
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
    bool AVLTree<K, V>::insert(const pair<K, V>& kv){
        if(_root == nullptr){
            _root = new Node(kv);
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

        while(parent){
            //renewal balance factor
            if(node == parent->_left) parent->_bt--;
            else parent->_bt++;
            if(parent->_bt == 0) break;

            if(parent->_bt == 2 || parent->_bt == -2){
                if(parent->_bt == 2 && node->_bt == 1){
                    RotateL(parent);
                }else if(parent->_bt == -2 && node->_bt == -1){
                    RotateR(parent);
                }else if(parent->_bt == 2 && node->_bt == -1){
                    Node* SubR = parent->_right; 
                    Node* SubRL = SubR->_left;
                    int bt = SubRL->_bt;
                    RotateRL(parent);
                    //renewal balance factor
                    if(bt == 0){
                        SubR->_bt = parent->_bt = 0;
                    }else if(bt == 1){
                        parent->_bt = -1;
                        SubR->_bt = SubRL->_bt = 0;
                    }else if(bt == -1){
                        SubRL->_bt = parent->_bt = 0;
                        SubR->_bt = 1;
                    }

                }else if(parent->_bt == -2 && node->_bt == 1){
                    Node* SubL = parent->_left;
                    Node* SubLR = SubL->_right;
                    int bt = SubLR->_bt;
                    RotateLR(parent);
                    //renewal balance factor
                    if(bt == 0){
                        SubL->_bt = parent->_bt = 0;
                    }else if(bt == 1){
                        SubL->_bt = -1;
                        SubLR->_bt = parent->_bt = 0;
                    }else if(bt == -1){
                        SubL->_bt = SubLR->_bt = 0;
                        parent->_bt = 1;
                    }
                }
                break;
            }
            node = parent;
            parent = parent->_parent;
        }
    }

    template<typename K, typename V>
    void AVLTree<K, V>::RotateL(Node* parent){
        Node* SubR = parent->_right;
        Node* SubRL = SubR->_left;
        Node* Parent_parent = parent->_parent;

        //link
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

        //renewal balance factor
        parent->_bt = SubR->_bt = 0;
    }

    template<typename K, typename V>
    void AVLTree<K, V>::RotateR(Node* parent){
        Node* SubL = parent->_left;
        Node* SubLR = SubL->_right;
        Node* Parent_parent = parent->_parent;

        //link
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

        //renewal balance factor
        parent->_bt = SubL->_bt = 0;
    }

    template<typename K, typename V>
    void AVLTree<K, V>::RotateRL(Node* parent){
        Node* SubR = parent->_right;
        Node* SubRL = SubR->_left;
        
        RotateR(SubR);
        RotateL(parent);
    }

    template<typename K, typename V>
    void AVLTree<K, V>::RotateLR(Node* parent){
        Node* SubL = parent->_left;
        Node* SubLR = SubL->_right;
        
        RotateL(SubL);
        RotateR(parent);
    }

};













































