#define _CRT_SECURE_NO_WARNINGS
#include "RBTree.h"
#include <string>
bool inputFromFile(Node*& root, char file[])
{
	FILE* fp = fopen(file, "rt");
	if (fp == NULL) return false;
	else
	{
		int n;
		fscanf(fp, "%d\n", &n);
		SinhVien x;
		for (int i = 0; i < n; i++)
		{
			docSV(fp, x);
			//xuatSV(x);
			insert(root, x);
		}
		fclose(fp);
		return true;
	}
}
void main()
{
	Node* root;
	initBRTree(root);
	char x[] = "input.txt";
	inputFromFile(root, x);
	showBRTree_InOrder(root);
	//tim kiem
	printf("\nTra cuu ma: ");
	char ma[10];
	scanf("%s", ma);
	Node* p = search(root, ma);
	if (p != NULL) {
		printf("Tim thay sinh vien voi ma %s: \n", ma);
		xuatSV(p->Info);
	}
	else
		printf("Khong tim thay sinh vien voi ma %s:", ma);
	printf("\nXoa sinh vien ma: ");
	scanf("%s", ma);
	deleteByInfo(root, ma);
	showBRTree_InOrder(root);
	system("pause");
}