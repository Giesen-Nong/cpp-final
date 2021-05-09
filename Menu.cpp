#include <iostream>
#include <Windows.h>
#include "loginsystem.h"
using namespace std;
void LoginMenu(AVLTree<string>& a);//��½���
void RegisterMunu(AVLTree<string>& a);//ע�����
void loginsystem(Node<string>*& cur, AVLTree<string>& a);//��½�����
void admin(AVLTree<string>& a);//���������
//���˵�
void MainMenu(AVLTree<string>& a) {
	int flag;
	bool m_exit = 0;
	do {
		system("cls");
		cout << "=======================================\n";
		cout << "     1.��½ϵͳ                        \n";
		cout << "     2.ע���û�                        \n";
		cout << "     3.��ʾ�û���������������ģʽ��    \n";
		cout << "     0.�˳�ϵͳ                        \n";
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
//��½���
void LoginMenu(AVLTree<string>& a) {
	string username, password;
	while(1){
		system("cls");
		cout << "=======================================\n";
		cout << "�û���½ϵͳ                     - �� X|\n";
		cout << "=======================================\n";
		cout << "   �û�����";
		cin >> username;
		cout << "\n   ���룺  ";
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
//ע�����
void RegisterMunu(AVLTree<string>& a) {
	string username, password,c_password;
	while (1) {
		system("cls");
		cout << "=======================================\n";
		cout << "�û�ע��ϵͳ                     - �� X|\n";
		cout << "=======================================\n";
		cout << "����ܰ��ʾ��\n";
		cout << "   ���û������������4λ��С��21λ��\n";
		cout << "   �����볤�������5λ��С��19λ��\n\n";
		cout << "   �û�����";
		cin >> username;
		cout << "\n   ���룺  ";
		cin >> password;
		cout << "\n ȷ�����룺";
		cin >> c_password;
		cout << "\n";
		cout << "=======================================\n";
		if (c_password != password) {
			cout << "������������벻һ��\n";
			system("pause");
		}
		else if (username.length()<5|| username.length()>20) {
			cout << "�û������������4��С��21\n";
			system("pause");
			MainMenu(a);
		}
		else if (password.length() < 6|| password.length()>18) {
			cout << "���볤�������5��С��19\n";
			system("pause");
			MainMenu(a);
		}
		else {
			for (int i = 0; i < username.length(); i++) {
				if (username[i] < 33 || username[i]>125) {
					cout << "�û������ڷǷ��ַ���������һ�㡣" << endl;
					system("pause");
					MainMenu(a);
				}
			}
			for (int i = 0; i < password.length(); i++) {
				if (password[i] < 33 || password[i]>125) {
					cout << "������ڷǷ��ַ���������һ�㡣" << endl;
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
//��½�����
void loginsystem(Node<string>*& cur,AVLTree<string>& a) {
	int flag;
	bool m_exit = 0;
	do {
		system("cls");
		cout << "=======================================\n";
		cout << "     1.�޸�����                        \n";
		cout << "     2.ע���û�                        \n";
		cout << "     0.�˳���½                        \n";
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
//���������
void admin(AVLTree<string>& a) {
	a.Print();
	system("pause");
	MainMenu(a);
}
