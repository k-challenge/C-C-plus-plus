#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;

struct edge {
    int u, v;
    float w;
};

bool cmp(const edge& a, const edge& b) {
    return a.w > b.w;
}
bool cmp1(const edge& a, const edge& b) {
    return a.w < b.w;
}
#define N 10005

int cha[N], hang[N];

int find(int u) {
    if (cha[u] != u) cha[u] = find(cha[u]);
    return cha[u];
}
void outGraph(vector<edge> edges) {
    for (edge& e : edges) cout<< e.u <<" "<< e.v<<" " << e.w<<endl;
}
void out(edge edges[], int size) {
    for(int i = 1; i < size; i++)
        cout << "(" << edges[i].u << ", " << edges[i].v << ") ";

}
bool join(int u, int v) {
    u = find(u); v = find(v);
    if (u == v) return false;
    if (hang[u] == hang[v]) hang[u]++;
    if (hang[u] < hang[v]) cha[u] = v;
    else cha[v] = u;
    return true;
}
void karuskal(vector<edge>& edges) {
    edge result[N];
    int count = 1;
    float sum = 0;
    for (edge& e : edges) {
        if (join(e.u, e.v)) {
            result[count].u = e.u;
            result[count].v = e.v;
            sum += e.w;
            count++;
        }
    }
    out(result, count);
    cout << "\ntong gia tri cua cay khung: "<<sum;
}
void bai4();
void bai5();

int main() {
    bai4();
    cout << "\n";
    bai5();
    return 0;
}

void bai4() {
    int n = 0, m = 0;
    ifstream fp("data.txt", ios::in);
    if (fp.is_open()) {
        fp >> n >> m;
        vector<edge> edges(m);
        for (edge& e : edges) fp >> e.u >> e.v >> e.w;
        sort(edges.begin(), edges.end(), cmp);
        for (int i = 1; i <= n; i++) {
            cha[i] = i;
            hang[i] = 0;
        }
        cout << "danh sach mang luoi va do tin cay " << endl;
        outGraph(edges);
        cout << "cay khung H co do tin cay lon nhat: " << endl;
        karuskal(edges);
    }
    fp.close();
}
void bai5() {
    int n = 0, m = 0;
    ifstream fp("data5.txt", ios::in);
    if (fp.is_open()) {
        fp >> n >> m;
        vector<edge> edges(m);
        for (edge& e : edges) fp >> e.u >> e.v >> e.w;
        sort(edges.begin(), edges.end(), cmp1);
        for (int i = 1; i <= n; i++) {
            cha[i] = i;
            hang[i] = 0;
        }
        cout << "danh sach mang duong: " << endl;
        outGraph(edges);
        cout << "cay khung nho nhat: " << endl;
        karuskal(edges);
    }
    fp.close();
}