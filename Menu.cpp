#include <iostream>
#include <Windows.h>
#include "loginsystem.h"
using namespace std;
void LoginMenu(AVLTree<string>& a);//登陆面板
void RegisterMunu(AVLTree<string>& a);//注册面板
void loginsystem(Node<string>*& cur, AVLTree<string>& a);//登陆后界面
void admin(AVLTree<string>& a);//开发者面板
//主菜单
void MainMenu(AVLTree<string>& a) {
	int flag;
	bool m_exit = 0;
	do {
		system("cls");
		cout << "=======================================\n";
		cout << "     1.登陆系统                        \n";
		cout << "     2.注册用户                        \n";
		cout << "     3.显示用户二叉树（开发者模式）    \n";
		cout << "     0.退出系统                        \n";
		cout << "=======================================\n";
		cin >> flag;
		switch (flag)
		{
			case 1:LoginMenu(a);
			case 2:RegisterMunu(a);
			case 3:admin(a);
			case 0: a.~AVLTree(); exit(0);
			default:continue;
		}
	} while (m_exit == 0);
}
//登陆面板
void LoginMenu(AVLTree<string>& a) {
	string username, password;
	while(1){
		system("cls");
		cout << "=======================================\n";
		cout << "用户登陆系统                     - 口 X|\n";
		cout << "=======================================\n";
		cout << "   用户名：";
		cin >> username;
		cout << "\n   密码：  ";
		cin >> password;
		cout << "\n";
		cout << "=======================================\n";
		if (a.login_check(username, password) == 0) {
			system("pause");
			MainMenu(a);
		}
		else {
			system("pause");
			Node<string>* cur = a.Search(username);
			loginsystem(cur, a);
		}
	}
}
//注册面板
void RegisterMunu(AVLTree<string>& a) {
	string username, password,c_password;
	while (1) {
		system("cls");
		cout << "=======================================\n";
		cout << "用户注册系统                     - 口 X|\n";
		cout << "=======================================\n";
		cout << "※温馨提示：\n";
		cout << "   ①用户名长度需大于4位且小于21位；\n";
		cout << "   ①密码长度需大于5位且小于19位；\n\n";
		cout << "   用户名：";
		cin >> username;
		cout << "\n   密码：  ";
		cin >> password;
		cout << "\n 确认密码：";
		cin >> c_password;
		cout << "\n";
		cout << "=======================================\n";
		if (c_password != password) {
			cout << "两次输入的密码不一致\n";
			system("pause");
		}
		else if (username.length()<5|| username.length()>20) {
			cout << "用户名长度需大于4且小于21\n";
			system("pause");
			MainMenu(a);
		}
		else if (password.length() < 6|| password.length()>18) {
			cout << "密码长度需大于5且小于19\n";
			system("pause");
			MainMenu(a);
		}
		else {
			for (int i = 0; i < username.length(); i++) {
				if (username[i] < 33 || username[i]>125) {
					cout << "用户名存在非法字符，返回上一层。" << endl;
					system("pause");
					MainMenu(a);
				}
			}
			for (int i = 0; i < password.length(); i++) {
				if (password[i] < 33 || password[i]>125) {
					cout << "密码存在非法字符，返回上一层。" << endl;
					system("pause");
					MainMenu(a);
				}
			}
			a.Register(username, password);
			system("pause");
			MainMenu(a);
		}
	}
}
//登陆后界面
void loginsystem(Node<string>*& cur,AVLTree<string>& a) {
	int flag;
	bool m_exit = 0;
	do {
		system("cls");
		cout << "=======================================\n";
		cout << "     1.修改密码                        \n";
		cout << "     2.注销用户                        \n";
		cout << "     0.退出登陆                        \n";
		cout << "=======================================\n";
		cin >> flag;
		system("cls");
		switch (flag)
		{
		case 1: if (a.changepw(cur) == 1) { system("pause"); continue; }; system("pause"); MainMenu(a);
		case 2:if (a.Del(cur) == 0) { system("pause"); continue; }; system("pause");  MainMenu(a);
		case 0:MainMenu(a);
		default:continue;
		}
	} while (m_exit == 0);
}
//开发者面板
void admin(AVLTree<string>& a) {
	a.Print();
	system("pause");
	MainMenu(a);
}
