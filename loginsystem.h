#pragma once
#include <iostream>
#include <fstream>
#include<queue>
using namespace std;
template <class T>
struct Node{
	T username;//用户名
	T password;//密码
	int height;//树的高度
	Node<T>* leftchild;//左子树
	Node<T>* rightchild;//右子树
	Node<T>():username(NULL),password(NULL),height(0),leftchild(NULL),rightchild(NULL){}
	Node<T>(T a,T b,Node<T>* l=NULL,Node<T>* r=NULL):username(a),password(b),height(0),leftchild(l),rightchild(r){}
};
template <class T>
class AVLTree {
public:
	AVLTree() :root(NULL) {}//构造空树
	AVLTree(AVLTree& a){}//复制构造树
	~AVLTree() { save(); Destroy(root); }//析构函数
	int Height() { return Height(root); }//获取树的总高度
	void inOrder() { inOrder(root); }//中序遍历
	bool Register(T name, T passwd);//添加用户
	bool Del(Node<T>* cur);//删除用户
	Node<T>* Search(T name) { return Search(root, name); }//搜索用户
	void Print() { Print(root); }//打印用户AVL树
	bool login_check(T name, T passwd);//用户登陆账号密码检查
	bool changepw(Node<T>*& cur);//修改用户密码
	void save();//将数据保存到文件中
	void read();//将用户数据插入树中
private:
	Node<T>* root;//根结点
	int Height(Node<T>* cur)const;//获取当前树的高度
	Node<T>* leftRotation(Node<T>* cur);//左旋
	Node<T>* rightRotation(Node<T>* cur);//右旋
	Node<T>* leftRightRotation(Node<T>* cur);//先左旋后右旋
	Node<T>* rightLeftRotation(Node<T>* cur);//先右旋后左旋
	Node<T>* Insert(Node<T>*& cur, T name, T passwd);//插入新结点
	Node<T>* maximum(Node<T>* cur);//返回该子树的最大结点
	Node<T>* minimum(Node<T>* cur);//返回该子树的最小结点
	Node<T>* Remove(Node<T>* cur,Node<T>* a);//删除结点
	Node<T>* Search(Node<T>* cur, T name)const;//查找结点（非递归）
	void Destroy(Node<T>*& cur);//销毁AVL树
	void Print(Node<T>* cur);
};
//获取当前树的高度
template <class T>
int AVLTree<T>::Height(Node<T>* cur)const {
	if (cur == NULL) return 0;
	if (cur->leftchild == NULL && cur->rightchild == NULL) {
		return 1;
	}
	return max(Height(cur->leftchild),Height(cur->rightchild))+1 ;
}
//左旋
template <class T>
Node<T>* AVLTree<T>::leftRotation(Node<T>* cur) {
	Node<T>* prchild = cur->rightchild;
	cur->rightchild = prchild->leftchild;
	prchild->leftchild = cur;
	//重新获取子树高度
	cur->height = max(Height(cur->leftchild), Height(cur->rightchild)) + 1;
	prchild->height= max(Height(prchild->leftchild), Height(prchild->rightchild)) + 1;
	return prchild;
}
//右旋
template <class T>
Node<T>* AVLTree<T>::rightRotation(Node<T>* cur) {
	Node<T>* prchild = cur->leftchild;
	cur->leftchild = prchild->rightchild;
	prchild->rightchild = cur;
	//重新获取子树高度
	cur->height = max(Height(cur->leftchild), Height(cur->rightchild)) + 1;
	prchild->height = max(Height(prchild->leftchild), Height(prchild->rightchild)) + 1;
	return prchild;
}
//先左旋后右旋
template <class T>
Node<T>* AVLTree<T>::leftRightRotation(Node<T>* cur) {
	cur->leftchild = leftRotation(cur->leftchild);
	return rightRotation(cur);
}
//先右旋后左旋
template <class T>
Node<T>* AVLTree<T>::rightLeftRotation(Node<T>* cur) {
	cur->rightchild = rightRotation(cur->rightchild);
	return leftRotation(cur);
}
//插入新结点
template <class T>
Node<T>* AVLTree<T>::Insert(Node<T>*& cur, T name, T passwd) {
	if (cur == NULL) {//插入空结点位置
		cur = new Node<T>(name, passwd);
	}
	else if (name > cur->username) {//比较值的大小，如果大往右子树插入
		cur->rightchild = Insert(cur->rightchild, name, passwd);
		if (Height(cur->rightchild) - Height(cur->leftchild) == 2) {//插入后失去平衡
			if (name > cur->username) {//双右结点子树，执行左旋操作
				cur = leftRotation(cur);
			}
			else if (name < cur->username) {//先右后左子树，先右旋再左旋
				cur = rightLeftRotation(cur);
			}
		}
	}
	else if (name < cur->username) {//值小往左子树插入
		cur->leftchild = Insert(cur->leftchild, name, passwd);
		if (Height(cur->leftchild) - Height(cur->rightchild) == 2) {//插入后失去平衡
			if (name < cur->username) {//双左结点子树，执行左旋操作
				cur = rightRotation(cur);
			}
			else if (name < cur->username) {//先左后右子树，先左旋再右旋
				cur = leftRightRotation(cur);
			}
		}
	}
	cur->height = max(Height(cur->leftchild), Height(cur->rightchild)) + 1;//更新树的高度
	return cur;
}
//返回该子树的最大结点
template <class T>
Node<T>* AVLTree<T>::maximum(Node<T>* cur) {
	if (cur != NULL) {
		while (cur->rightchild != NULL) {
			cur = cur->rightchild;
		}
		return cur;
	}
	return NULL;
}
//返回该子树的最小结点
template <class T>
Node<T>* AVLTree<T>::minimum(Node<T>* cur) {
	if (cur != NULL) {
		while (cur->leftchild != NULL) {
			cur = cur->leftchild;
		}
		return cur;
	}
	return NULL;
}
//删除结点
template <class T>
Node<T>* AVLTree<T>::Remove(Node<T>* cur, Node<T>* a) {
	if (cur != NULL) {
		if (a->username == cur->username && a->password == cur->password) {//找到需要删除的结点
			if (cur->leftchild != NULL && cur->rightchild != NULL) {//删除结点处有2个子树
				if (Height(cur->leftchild) > Height(cur->rightchild)) {//左子树高度大于右子树，找到左子树最右结点提起再删除结点
					Node<T>* maxNode = maximum(cur->leftchild);
					cur->username = maxNode->username;
					cur->password = maxNode->password;
					cur->leftchild = Remove(cur->leftchild, maxNode);
				}
				else {//右子树高度大于左子树反之
					Node<T>* minNode = minimum(cur->rightchild);
					cur->username = minNode->username;
					cur->password = minNode->password;
					cur->rightchild = Remove(cur->rightchild, minNode);
				}
			}
			else {//只有一个子树或没有子树
				Node<T>* temp = cur;
				if (cur->leftchild != NULL) {
					cur= cur->leftchild;
				}
				else if (cur->rightchild != NULL) {
					cur = cur->rightchild;
				}
				else { return NULL; }
				delete temp;
			}
		}
		else if (a->username > cur->username) {//需要删除的结点比当前值大，往右子树查找删除
			cur->rightchild = Remove(cur->rightchild,a);
			if (Height(cur->leftchild) - Height(cur->rightchild) == 2) {//判断删除后树是否平衡
				if (Height(cur->leftchild->rightchild) > Height(cur->leftchild->leftchild)) {
					cur = leftRightRotation(cur);
				}
				else {
					cur = rightRotation(cur);
				}
			}
		}
		else if (a->username < cur->username) {//需要删除的结点比当前值小，往左子树查找删除
			cur->leftchild = Remove(cur->leftchild,a);
			if (Height(cur->rightchild) - Height(cur->leftchild) == 2) {
				if (Height(cur->rightchild->leftchild) > Height(cur->rightchild->rightchild)) {
					cur = rightLeftRotation(cur);
				}
				else {
					cur = leftRotation(cur);
				}
			}
		}
		return cur;
	}
	return NULL;
}
//删除用户
template <class T>
bool AVLTree<T>::Del(Node<T>* cur) {
	char flag;
	cout << "您当前删除的用户为" << cur->username << endl;
	cout << "是否确认注销该用户？Y/N"<<endl;
	cin >> flag;
	if(flag=='Y'||flag=='y'){
	if (Search(cur->username) != NULL) {
		root = Remove(root, cur);
		cout << "用户注销成功，退出登陆\n";
		save();
		return 1;
	}
	}
	return 0;
}
//查找结点（非递归）
template <class T>
Node<T>* AVLTree<T>::Search(Node<T>* cur, T name)const {
	while (cur != NULL) {
		if (name == cur->username) {
			return cur;
		}
		else if (name > cur->username) {
			cur = cur->rightchild;
		}
		else {
			cur = cur->leftchild;
		}
	}
	return NULL;
}
//销毁AVL树
template <class T>
void AVLTree<T>::Destroy(Node<T>*& cur) {
	if (cur != NULL) {
		Destroy(cur->leftchild);
		Destroy(cur->rightchild);
		delete cur;
		cur = NULL;
	}
}
//注册用户
template <class T>
bool AVLTree<T>::Register(T name, T passwd) {
	if (Search(root, name) == NULL) {
		Insert(root, name, passwd);
		cout << "注册成功！\n";
		save();
		return 1;
	}
	else {
		cout << "用户名已存在\n";
		return 0;
	}
}
//用户登陆账号密码检查
template <class T>
bool AVLTree<T>::login_check(T name, T passwd) {
	if(Search(root, name)!=NULL){
	Node<T>* check = Search(root,name);
	if (passwd == check->password) {
		cout << "登陆成功\n";
		return 1;
	}
	else if (passwd != check->password) {
		cout << "账号或密码错误！\n";
		return 0;
	}
	}
	else {
		cout << "用户名不存在,自动返回上一层\n";
		return 0;
	}
}
//修改用户密码
template <class T>
bool AVLTree<T>::changepw(Node<T>*& cur) {
	string o_pw,pw, c_pw;
	cout << "请输入旧密码：";
	cin >> o_pw;
	if (o_pw == cur->password) {
		cout << "请输入修改后的密码：";
		cin >> pw;
		cout << "请再次确认密码：";
		cin >> c_pw;
		if (pw != c_pw) {
			cout << "两次输入的密码不一致，返回上一层。\n";
			return 1;
		}
		else {
			cur->password = pw;
			cout << "密码修改成功！请记牢您的新密码，自动退出登陆\n";
			save();
			return 0;
		}
	}
	else { cout << "旧密码输入错误，返回上一层\n"; return 1; }
}
//将数据保存到文件中
template <class T>
void AVLTree<T>::save() {
	//用队列实现层序遍历
	queue<Node<T>*> q;
	fstream f("userdata.txt", ios::out);
	Node<T>* temp;
	temp = root;
	q.push(temp);
	while (!q.empty()) {
		Node<T>* front = q.front();
		f << front->username << ' ' << front->password << '\n';
		if (front->leftchild != NULL)
			q.push(front->leftchild);
		if (front->rightchild != NULL)
			q.push(front->rightchild);
		q.pop();
	}
	f.close();
}
// 将用户数据插入树中
template <class T>
void AVLTree<T>::read() {
	fstream f("userdata.txt", ios::_Nocreate);
	if (f) {//判断文件是否存在，存在则读取
		f.close();
		T name, passwd;
		f.open("userdata.txt", ios::in);
		while (!f.eof()) {
			f >> name >> passwd;
			Insert(root, name, passwd);
		}
	}
	f.close();
}
//打印二叉树
template <class T>
void AVLTree<T>::Print(Node<T>* cur) {
	static int level = -1; //记录是第几层次
	int i;
	if (cur){
	level++;
	Print(cur->rightchild);
	level--;
	level++;
	for (i = 0; i < level; i++)
		cout << '\t';
	cout << cur->username << endl;
	Print(cur->leftchild);
	level--;
	}
}