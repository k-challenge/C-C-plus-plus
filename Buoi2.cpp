#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "conio.h"
#include "stdlib.h"

#define vmax 20
//định nghĩa cấu trúc đồ thị
struct dothi
{
	int flag; //loại đồ thị: 0 là vô hướng, 1 là có hướng
	int n; //số đỉnh của đồ thị
	int w[vmax][vmax]; //ma trận kề hoặc ma trận trọng số
};
//đọc dữ liệu từ file lưu vào cấu trúc đồ thị
void docfile(dothi& g)
{
	FILE* f = fopen("data.txt", "r");
	if (f == NULL)
		printf("\nKhong tim thay file");
	else
	{
		fscanf(f, "%d", &g.flag);
		fscanf(f, "%d", &g.n);
		for (int i = 1; i <= g.n; i++)
			for (int j = 1; j <= g.n; j++)
				fscanf(f, "%d", &g.w[i][j]);

	}
}
//xuất thông tin đồ thị
void xuatdothi(dothi g)
{
	if (g.flag == 0)
		printf("\nDo thi vo huong");
	else
		printf("\nDo thi co huong");
	printf("\nMa tran ke hoac ma tran trong so cua do thi:");
	for (int i = 1; i <= g.n; i++)
	{
		printf("\n");
		for (int j = 1; j <= g.n; j++)
			printf("%5d", g.w[i][j]);

	}
}

//Phần tạo cây khung
//Định nghĩa cấu trúc cạnh
struct canh
{
	int u, v;
};
int chuaxet[100]; //đánh dấu các đỉnh đã xét hay chưa, đầu tiên khởi tạo các đỉnh chưa
//xuất các cạnh của cây khung
void xuatcaykhung(canh T[], int socanh)
{
	printf("\nCay khung nhỏ nhat \n");
	for (int i = 1; i <= socanh; i++)
		printf("\t(%d, %d)", T[i].u, T[i].v);

}
//xây dựng cây khung theo thuật toán DFS
void xaydungcaykhung_DFS(dothi g, canh T[], int& socanh, int u)
{
	chuaxet[u] = 1;
	for (int v = 1; v <= g.n; v++)
	{
		if (g.w[u][v] != 0 && chuaxet[v] == 0)
		{
			socanh++;
			T[socanh].u = u;
			T[socanh].v = v;
			if (socanh == g.n - 1)
			{
				xuatcaykhung(T, socanh);
				return;
			}
			else
				xaydungcaykhung_DFS(g, T, socanh, v);

		}
	}
}
//xây dựng cây khung theo thuật toán BFS
void xaydungcaykhung_BFS(dothi g, canh T[], int& socanh)
{
	for (int u = 1; u <= g.n; u++)
	{
		for (int v = 1; v <= g.n; v++)
		{
			if (g.w[u][v] != 0 && chuaxet[v] == 0)
			{
				socanh++;
				T[socanh].u = u;
				T[socanh].v = v;
				chuaxet[v] = 1;
				chuaxet[u] = 1;
				printf("\n===============(%d,%d)", T[socanh].u, T[socanh].v);
				if (socanh == g.n - 1)
				{
					xuatcaykhung(T, socanh);
					return;
				}
			}
		}

	}
}
int main()
{
	dothi g;
	docfile(g);
	xuatdothi(g);
	canh T[100];
	int socanh = 0;
	for (int i = 1; i <= g.n; i++)
		chuaxet[i] = 0;
	xaydungcaykhung_BFS(g, T, socanh);
	//socanh = 0;
	//xaydungcaykhung_BFS(g, T, socanh);
}