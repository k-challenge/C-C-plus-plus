#include <iostream>
#include <string>
#include <fstream>
#define Max 100

using namespace std;

int chuaxet[Max];
class Graph{
public:
	class nhan{
	public:
		int dinh, chiphi;
	};
	int n;
	int flag;
	int arr[Max][Max];
	nhan bangchiphi[Max][Max];
	void fread(string file_name) {
		ifstream fp(file_name, ios::in);
		if (fp.is_open()) {
			fp >> n;
			fp >> flag;
			for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				fp >> arr[i][j];
		}
		fp.close();
	}

	void out() const {
		if (flag)
			cout << "do thi co huong" << endl;
		else
			cout << "Do thi vo huong\n" << endl;
		cout << "Ma tran ke hoac ma tran trong so cua do thi: " << endl;
		for (int i = 1; i <= n; i++){
			for (int j = 1; j <= n; j++)
				cout << arr[i][j] << "\t";
			cout << endl;
		}
	}

	void xuatBangChiPhi() {
		printf("\nBang mo ta thuat toan Prim tim cay khung nho nhat: \n");
		for (int i = 1; i <= n; i++)
			printf("%10d", i);
		for (int i = 1; i <= n; i++) {
			printf("%\n---------------------------------------------------------\n");
			for (int j = 1; j <= n; j++){
				printf("(%d, %d)\t", bangchiphi[i][j].dinh, bangchiphi[i][j].chiphi);
			}
		}
	}
	void init(int dinhkhoidau) {
		for (int i = 1; i <= n; i++) {
			chuaxet[i] = 0;
			bangchiphi[0][i].chiphi = Max;
			bangchiphi[0][i].dinh = 0;
		}

		bangchiphi[0][dinhkhoidau].chiphi = 0;
		bangchiphi[0][dinhkhoidau].dinh = 0;
	}
	void xuatcaykhung() {
		cout << "\nCac hanh trinh duong bay ngan nhat: " << endl;
		int i = 2;
		while (i <= n) {
			cout << "(" << bangchiphi[n - 1][i].dinh << ", " << i << ")";
			i++;
		}
	}
	void prim(int dinhkhoidau) {
		init(dinhkhoidau);
		int i = 0;
		while (i < n) {
			int dinh_min = 1;
			while (chuaxet[dinh_min] == 1) dinh_min++;
			for (int j = 1; j <= n; j++) {
				if (chuaxet[j] == 0 && (bangchiphi[i][j].chiphi < bangchiphi[i][dinh_min].chiphi))
					dinh_min = j;
			}

			chuaxet[dinh_min] = 1;
			i++;
			for (int j = 1; j <= n; j++) {
				if ((chuaxet[j] == 1 || arr[dinh_min][j] == Max))
					bangchiphi[i][j] = bangchiphi[i - 1][j];

				if (dinh_min != j && chuaxet[j] == 0 && arr[dinh_min][j] < Max){
					if (bangchiphi[i - 1][j].chiphi > arr[dinh_min][j]){
						bangchiphi[i][j].chiphi = arr[dinh_min][j];
						bangchiphi[i][j].dinh = dinh_min;
					}
					else {
						bangchiphi[i][j] = bangchiphi[i - 1][j];
					}
				}
			}
		}
	}

	int getLength() {
		int sum = 0;
		int i = 2;
		while (i <= n) {
			sum += bangchiphi[bangchiphi[n - 1][i].dinh][i].chiphi;
			i++;
		}
		return sum;
	}
};

void exercise_3(Graph& graph) {
	graph.prim(1);
	graph.xuatcaykhung();
}
int main() {
	Graph graph;
	graph.fread("data3.txt");
	graph.out();
	exercise_3(graph);
	cout << "\nTong chi phi gia ve la:  ";
	cout << graph.getLength()<<endl;
	system("pause");

	return 0;
}
