#include <iostream>
#include "loginsystem.h"
using namespace std;
void MainMenu(AVLTree<string> &a);
int main() {
	AVLTree<string> a;
	a.read();
	MainMenu(a);
}