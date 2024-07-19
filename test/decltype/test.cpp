#include <vector>
#include <iostream>
using namespace std;


  struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  
  };

class Solution {
public:
    void FindRoutine(TreeNode* root, TreeNode* node, vector<TreeNode*>& routine, bool& is_find){
        if(root == nullptr){ 
            routine.push_back(nullptr);
            return;
        }

        if(root == node){
            routine.push_back(node);
            is_find = true;
            return;
        }
        
        routine.push_back(root);
        FindRoutine(root->left, node, routine, is_find);
        if(is_find) return;
        routine.pop_back();
        FindRoutine(root->right, node, routine, is_find);
        if(is_find) return;
        routine.pop_back();
    }

    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        vector<TreeNode*> p_vector, q_vector;
        bool is_find = false;
        bool is_find2 = false;
        FindRoutine(root, p, p_vector, is_find);
        FindRoutine(root, q, q_vector, is_find2);
        for(const auto& e : p_vector){
            cout << e->val << " ";
        }
        cout << endl;
        for(const auto& e : q_vector){
            cout << e->val << " ";
        }
        cout << endl;
        size_t p_sz = p_vector.size(), q_sz = q_vector.size();
        int i = 1;
        while(i < p_sz && i < q_sz){
            if(p_vector[i] != q_vector[i]) return p_vector[i-1];
            else i++;
        }
        return root;
    }
};

int main(){
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(5); root->right = new TreeNode(1);
    root->left->left = new TreeNode(6); root->left->right = new TreeNode(2);
    root->left->right->left = new TreeNode(7); root->left->right->right = new TreeNode(4);
    root->right->left = new TreeNode(0); root->right->right = new TreeNode(8);
    Solution s; s.lowestCommonAncestor(root, root->left, root->right);
    return 0;
}
