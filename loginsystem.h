#pragma once
#include <iostream>
#include <fstream>
#include<queue>
using namespace std;
template <class T>
struct Node{
	T username;//�û���
	T password;//����
	int height;//���ĸ߶�
	Node<T>* leftchild;//������
	Node<T>* rightchild;//������
	Node<T>():username(NULL),password(NULL),height(0),leftchild(NULL),rightchild(NULL){}
	Node<T>(T a,T b,Node<T>* l=NULL,Node<T>* r=NULL):username(a),password(b),height(0),leftchild(l),rightchild(r){}
};
template <class T>
class AVLTree {
public:
	AVLTree() :root(NULL) {}//�������
	AVLTree(AVLTree& a){}//���ƹ�����
	~AVLTree() { save(); Destroy(root); }//��������
	int Height() { return Height(root); }//��ȡ�����ܸ߶�
	void inOrder() { inOrder(root); }//�������
	bool Register(T name, T passwd);//����û�
	bool Del(Node<T>* cur);//ɾ���û�
	Node<T>* Search(T name) { return Search(root, name); }//�����û�
	void Print() { Print(root); }//��ӡ�û�AVL��
	bool login_check(T name, T passwd);//�û���½�˺�������
	bool changepw(Node<T>*& cur);//�޸��û�����
	void save();//�����ݱ��浽�ļ���
	void read();//���û����ݲ�������
private:
	Node<T>* root;//�����
	int Height(Node<T>* cur)const;//��ȡ��ǰ���ĸ߶�
	Node<T>* leftRotation(Node<T>* cur);//����
	Node<T>* rightRotation(Node<T>* cur);//����
	Node<T>* leftRightRotation(Node<T>* cur);//������������
	Node<T>* rightLeftRotation(Node<T>* cur);//������������
	Node<T>* Insert(Node<T>*& cur, T name, T passwd);//�����½��
	Node<T>* maximum(Node<T>* cur);//���ظ������������
	Node<T>* minimum(Node<T>* cur);//���ظ���������С���
	Node<T>* Remove(Node<T>* cur,Node<T>* a);//ɾ�����
	Node<T>* Search(Node<T>* cur, T name)const;//���ҽ�㣨�ǵݹ飩
	void Destroy(Node<T>*& cur);//����AVL��
	void Print(Node<T>* cur);
};
//��ȡ��ǰ���ĸ߶�
template <class T>
int AVLTree<T>::Height(Node<T>* cur)const {
	if (cur == NULL) return 0;
	if (cur->leftchild == NULL && cur->rightchild == NULL) {
		return 1;
	}
	return max(Height(cur->leftchild),Height(cur->rightchild))+1 ;
}
//����
template <class T>
Node<T>* AVLTree<T>::leftRotation(Node<T>* cur) {
	Node<T>* prchild = cur->rightchild;
	cur->rightchild = prchild->leftchild;
	prchild->leftchild = cur;
	//���»�ȡ�����߶�
	cur->height = max(Height(cur->leftchild), Height(cur->rightchild)) + 1;
	prchild->height= max(Height(prchild->leftchild), Height(prchild->rightchild)) + 1;
	return prchild;
}
//����
template <class T>
Node<T>* AVLTree<T>::rightRotation(Node<T>* cur) {
	Node<T>* prchild = cur->leftchild;
	cur->leftchild = prchild->rightchild;
	prchild->rightchild = cur;
	//���»�ȡ�����߶�
	cur->height = max(Height(cur->leftchild), Height(cur->rightchild)) + 1;
	prchild->height = max(Height(prchild->leftchild), Height(prchild->rightchild)) + 1;
	return prchild;
}
//������������
template <class T>
Node<T>* AVLTree<T>::leftRightRotation(Node<T>* cur) {
	cur->leftchild = leftRotation(cur->leftchild);
	return rightRotation(cur);
}
//������������
template <class T>
Node<T>* AVLTree<T>::rightLeftRotation(Node<T>* cur) {
	cur->rightchild = rightRotation(cur->rightchild);
	return leftRotation(cur);
}
//�����½��
template <class T>
Node<T>* AVLTree<T>::Insert(Node<T>*& cur, T name, T passwd) {
	if (cur == NULL) {//����ս��λ��
		cur = new Node<T>(name, passwd);
	}
	else if (name > cur->username) {//�Ƚ�ֵ�Ĵ�С�������������������
		cur->rightchild = Insert(cur->rightchild, name, passwd);
		if (Height(cur->rightchild) - Height(cur->leftchild) == 2) {//�����ʧȥƽ��
			if (name > cur->username) {//˫�ҽ��������ִ����������
				cur = leftRotation(cur);
			}
			else if (name < cur->username) {//���Һ���������������������
				cur = rightLeftRotation(cur);
			}
		}
	}
	else if (name < cur->username) {//ֵС������������
		cur->leftchild = Insert(cur->leftchild, name, passwd);
		if (Height(cur->leftchild) - Height(cur->rightchild) == 2) {//�����ʧȥƽ��
			if (name < cur->username) {//˫����������ִ����������
				cur = rightRotation(cur);
			}
			else if (name < cur->username) {//�������������������������
				cur = leftRightRotation(cur);
			}
		}
	}
	cur->height = max(Height(cur->leftchild), Height(cur->rightchild)) + 1;//�������ĸ߶�
	return cur;
}
//���ظ������������
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
//���ظ���������С���
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
//ɾ�����
template <class T>
Node<T>* AVLTree<T>::Remove(Node<T>* cur, Node<T>* a) {
	if (cur != NULL) {
		if (a->username == cur->username && a->password == cur->password) {//�ҵ���Ҫɾ���Ľ��
			if (cur->leftchild != NULL && cur->rightchild != NULL) {//ɾ����㴦��2������
				if (Height(cur->leftchild) > Height(cur->rightchild)) {//�������߶ȴ������������ҵ����������ҽ��������ɾ�����
					Node<T>* maxNode = maximum(cur->leftchild);
					cur->username = maxNode->username;
					cur->password = maxNode->password;
					cur->leftchild = Remove(cur->leftchild, maxNode);
				}
				else {//�������߶ȴ�����������֮
					Node<T>* minNode = minimum(cur->rightchild);
					cur->username = minNode->username;
					cur->password = minNode->password;
					cur->rightchild = Remove(cur->rightchild, minNode);
				}
			}
			else {//ֻ��һ��������û������
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
		else if (a->username > cur->username) {//��Ҫɾ���Ľ��ȵ�ǰֵ��������������ɾ��
			cur->rightchild = Remove(cur->rightchild,a);
			if (Height(cur->leftchild) - Height(cur->rightchild) == 2) {//�ж�ɾ�������Ƿ�ƽ��
				if (Height(cur->leftchild->rightchild) > Height(cur->leftchild->leftchild)) {
					cur = leftRightRotation(cur);
				}
				else {
					cur = rightRotation(cur);
				}
			}
		}
		else if (a->username < cur->username) {//��Ҫɾ���Ľ��ȵ�ǰֵС��������������ɾ��
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
//ɾ���û�
template <class T>
bool AVLTree<T>::Del(Node<T>* cur) {
	char flag;
	cout << "����ǰɾ�����û�Ϊ" << cur->username << endl;
	cout << "�Ƿ�ȷ��ע�����û���Y/N"<<endl;
	cin >> flag;
	if(flag=='Y'||flag=='y'){
	if (Search(cur->username) != NULL) {
		root = Remove(root, cur);
		cout << "�û�ע���ɹ����˳���½\n";
		save();
		return 1;
	}
	}
	return 0;
}
//���ҽ�㣨�ǵݹ飩
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
//����AVL��
template <class T>
void AVLTree<T>::Destroy(Node<T>*& cur) {
	if (cur != NULL) {
		Destroy(cur->leftchild);
		Destroy(cur->rightchild);
		delete cur;
		cur = NULL;
	}
}
//ע���û�
template <class T>
bool AVLTree<T>::Register(T name, T passwd) {
	if (Search(root, name) == NULL) {
		Insert(root, name, passwd);
		cout << "ע��ɹ���\n";
		save();
		return 1;
	}
	else {
		cout << "�û����Ѵ���\n";
		return 0;
	}
}
//�û���½�˺�������
template <class T>
bool AVLTree<T>::login_check(T name, T passwd) {
	if(Search(root, name)!=NULL){
	Node<T>* check = Search(root,name);
	if (passwd == check->password) {
		cout << "��½�ɹ�\n";
		return 1;
	}
	else if (passwd != check->password) {
		cout << "�˺Ż��������\n";
		return 0;
	}
	}
	else {
		cout << "�û���������,�Զ�������һ��\n";
		return 0;
	}
}
//�޸��û�����
template <class T>
bool AVLTree<T>::changepw(Node<T>*& cur) {
	string o_pw,pw, c_pw;
	cout << "����������룺";
	cin >> o_pw;
	if (o_pw == cur->password) {
		cout << "�������޸ĺ�����룺";
		cin >> pw;
		cout << "���ٴ�ȷ�����룺";
		cin >> c_pw;
		if (pw != c_pw) {
			cout << "������������벻һ�£�������һ�㡣\n";
			return 1;
		}
		else {
			cur->password = pw;
			cout << "�����޸ĳɹ�����������������룬�Զ��˳���½\n";
			save();
			return 0;
		}
	}
	else { cout << "������������󣬷�����һ��\n"; return 1; }
}
//�����ݱ��浽�ļ���
template <class T>
void AVLTree<T>::save() {
	//�ö���ʵ�ֲ������
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
// ���û����ݲ�������
template <class T>
void AVLTree<T>::read() {
	fstream f("userdata.txt", ios::_Nocreate);
	if (f) {//�ж��ļ��Ƿ���ڣ��������ȡ
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
//��ӡ������
template <class T>
void AVLTree<T>::Print(Node<T>* cur) {
	static int level = -1; //��¼�ǵڼ����
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