#ifndef _CAY_DO_DEN_SINH_VIEN_
#define _CAY_DO_DEN_SINH_VIEN_
#include <stdio.h>
#include "SinhVien.h"
#include <Windows.h>
using namespace std;
typedef SinhVien ItemType;
enum EColor { RED, BLACK };
struct Node
{
	ItemType Info;
	EColor Color;
	Node* Left, * Right, * Parent;
};
void showBRTNode(Node* p);
void initBRTree(Node*& brt);
void showBRTree_InOrder(Node* root);
void insert(Node*& root, ItemType Info);
Node* search(Node* root, char x_ma[]);
void deleteByInfo(Node*& root, char x_ma[]);
#endif
