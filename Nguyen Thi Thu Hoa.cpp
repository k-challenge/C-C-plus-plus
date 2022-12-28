#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <fstream>
#define MAXN 1001
#define MAXX 999999999

using namespace std;

int A[MAXN][MAXN];
int MinPath[MAXN];
int From[MAXN];
bool Free[MAXN];

int M, N, S, E;


void init()
{
    ifstream fp("DIJKSTRA.txt", ios::in);
    fp >> N >> M >> S >> E;
    for (int i = 1; i <= M; i++)
    {
        int u, v, p;
        fp >> u >> v >> p;
        A[u][v] = A[v][u] = p;
    }

    for (int i = 1; i <= N; i++) MinPath[i] = MAXX;
    MinPath[S] = 0;
}


void DIJKSTRA()
{
    int g = S, minD;
    do
    {
        g = E;
        for (int i = 1; i <= N; i++)
            if (Free[i] == false && MinPath[g] > MinPath[i])
            {
                g = i;
            }
        Free[g] = true;

        if (MinPath[g] == MAXX || g == E) break;


        for (int v = 1; v <= N; v++)
        {
            if (A[g][v] > 0 && !Free[v])
            {
                if (A[g][v] + MinPath[g] < MinPath[v])
                {
                    MinPath[v] = A[g][v] + MinPath[g];
                    From[v] = g;
                }
            }
        }

    } while (true);
}


void TruyVet(int end)
{
    int u = end;
    vector<int> vet;
    while (u != S)
    {
        vet.push_back(u);
        u = From[u];
    }
    vet.push_back(S);
    printf("\nVet tim duoc: ");
    for (int i = vet.size() - 1; i >= 0; i--) printf("%3d", vet[i]);
    printf("\n");
}


void print()
{
    if (MinPath[E] == MAXX)
        printf("Khong co duong di!");
    else
        printf("Duong di ngan nhat la: %d", MinPath[E]);
}

int main()
{
    init();
    DIJKSTRA();
    print();
    TruyVet(E);
}

/*Input Test:

6 7 1 4
1 2 1
1 6 20
2 3 2
3 6 3
3 4 20
5 4 5
6 5 4
*/