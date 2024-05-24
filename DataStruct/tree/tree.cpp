#include<iostream>
#include<vector>
#include<queue>
using namespace std;

typedef struct BTNode
{   
    struct BTNode* left;
    struct BTNode* right;
    int _val;
    explicit BTNode(int val):
        left(nullptr), right(nullptr), _val(val){}
}BTNode;

//通过前序历遍来创建二叉树，如果节点为nullptr用#来表示
//m是用来干嘛的：用来记录右子树对应的下标在哪里
BTNode* BinaryTreeCreate(const string& arr, int& m){
    if(m >= arr.size() || arr[m] == '#') {
        m++;
        return nullptr;
    }
    BTNode* root = new BTNode(arr[m]);
    m++;
    root->left = BinaryTreeCreate(arr, m);
    root->right = BinaryTreeCreate(arr, m);
    return root;
}

BTNode* CreateBTree(){
    BTNode* n1 = new BTNode(1);
    BTNode* n2 = new BTNode(2);
    BTNode* n3 = new BTNode(3);
    BTNode* n4 = new BTNode(4);
    BTNode* n5 = new BTNode(5);
    BTNode* n6 = new BTNode(6);
    BTNode* n7 = new BTNode(7);
    BTNode* n8 = new BTNode(8);

    n1->left = n2;
	n1->right = n4;
	n2->left = n3;
	n4->left = n5;
	n4->right = n6;
    n2->right = n7;
    n3->left = n8;
	return n1;
}

void PrevOrder(BTNode* root){
    if(root == nullptr) return;

    cout << root->_val << " ";
    PrevOrder(root->left);
    PrevOrder(root->right);
}

int BTSize(BTNode* root){
    //有几种方法来进行实现 1.使用staic来定义局部静态变量，这样会带来一个问题
    //因为静态变量只可以初始化一次，所以只有第一次计算size是正确的其余都是错误的，还可以使用全局变量
    //但是全局变量会带俩线程不安全的问题，然后还有一个方法就是创建一个变量，然后项函数中传递这个变量的指针

    //最后最好的就是使用分支的思想来解决问题
    // if(root == nullptr) return 0;
    // int left = BTSize(root->left);
    // int right = BTSize(root->right);
    // //最后再执行 + 1操作是加上当前的节点
    // return left + right + 1;

    //还可但是注意如果是需要进行比较的话就要递归产生的结果记录下来，否则会造成效率很低的情况 
    return root == nullptr ? 0 : BTSize(root->left) + BTSize(root->right) + 1;
}

int BinaryTreeLeafSize(BTNode* root){
    if(root->left == nullptr && root->right == nullptr) return 1;
    int left = 0;
    if(root->left) {
        left = BinaryTreeLeafSize(root->left);
    }
    int right = 0;
    if(root->right){
        right = BinaryTreeLeafSize(root->right);
    }
    return left + right;
}

//处理这个问题的两种思路：1.使用层序遍历，遍历到第k层然后查看该层一共有多少个节点
//2.分解子问题第k层 = 第1层的向下第 k - 1层 等于第2层的向下第k - 2层
int BinaryTreeLevelKSize(BTNode* root, int k){
    if(k == 1 && root) return 1;
    if(!root) return 0;
    int left = BinaryTreeLevelKSize(root->left, k - 1);
    int right = BinaryTreeLevelKSize(root->right, k - 1);
    return left + right;
}

//如果要进行二叉树的销毁，为了不让节点成为野指针，应该使用后续遍历

//层序遍历的思想是在遍历完这一层之后直接对下一层进行遍历，那么我们要做的就是将节点存储下来
void LevelOrder(BTNode* root){
	queue<BTNode*> q;
	if(root == nullptr) return;
	q.emplace(root);
	while(!q.empty()){
		BTNode* Node = q.front();
		q.pop();
		cout << Node->_val;
		if(Node->left) q.emplace(Node->left);
		if(Node->right) q.emplace(Node->right);

	}
	cout << endl;
}

//判断是不是完全二叉树应该使用队列，因为队列是一层一层的遍历的
//如果出现空了那么之后的元素就不可以再出现元素了只可以是空，如果出现的元素，那么就不是完全二叉树
bool isComopleteTree(BTNode* root){
	queue<BTNode*> q;
	q.emplace(root);
	while(!q.empty()){
		BTNode* Front = q.front();
		q.pop();
		if(Front == nullptr) break;
		q.emplace(Front->left);
		q.emplace(Front->right);

	}
	//如果在这里就证明已经有nullptr出现了，那么后面所有的元素只能是nullptr
	while(!q.empty()){
		BTNode* Front = q.front();
		q.pop();
		if(Front != nullptr) return false;
	}
	return true;
}

int main(){
    BTNode* root = CreateBTree();
    //PrevOrder(root);
    //cout << endl;
    // string str = "ABD##E#H##CF##G##";
    // int x = 0;
    // BTNode* root = BinaryTreeCreate(str, x);
    ///PrevOrder(root);
    //cout << BinaryTreeLeafSize(root) << endl;
    // cout << BinaryTreeLevelKSize(root, 1);
    // cout << BinaryTreeLevelKSize(root, 2);
    // cout << BinaryTreeLevelKSize(root, 3);
    // cout << BinaryTreeLevelKSize(root, 4);
    // cout << BinaryTreeLevelKSize(root, 5);
    //LevelOrder(root);
		cout << isComopleteTree(root) << endl;
    return 0;
}
