/*
Задача C. «0-1» BFS
Имя входного файла: стандартный ввод
Имя выходного файла: стандартный вывод
Вам дан неориентированный взвешенный граф G на n вершин и m ребер и вершина s.
Известно, что вес любого ребра равен либо единице, либо нулю.
Найдите расстояния от вершины s до всех остальных вершин.
Формат входных данных:
В первой строке вводятся три числа n, m, s — количество вершин,
количество ребер и стартовая вершина соответсвенно.
В следующих m строках вводится по два числа ai, bi, c — ребра графа G.
Формат выходных данных:
В единственной строке выведите n числе, где i-е равно расстоянию от вершины s до i,
если путь от s до i существует, и −1 иначе.
*/

#include <iostream>
#include <vector>
#include <deque>

using namespace std;

int main()
{
    int n, m, s;
    cin >> n >> m >> s;
    vector<vector<pair<int,int>>> adj(n + 1);

    for (int i = 0; i < m; ++i)
    {
        int a, b, c;
        cin >> a >> b >> c;
        adj[a].push_back({b, c});
        adj[b].push_back({a, c});
    }

    const int INF = 1e9;
    vector<int> dist(n + 1, INF);
    deque<int> dq;

    dist[s] = 0;
    dq.push_back(s);
    while (!dq.empty())
    {
        int v = dq.front(); dq.pop_front();
        for (auto [u, w] : adj[v])
        {
            if (dist[v] + w < dist[u])
            {
                dist[u] = dist[v] + w;
                if (w == 0) dq.push_front(u);
                else dq.push_back(u);
            }
        }
    }
    for (int i = 1; i <= n; ++i)
    {
        cout << (dist[i] == INF ? -1 : dist[i]);
        if (i < n) cout << ' ';
    }

    cout << '\n';
    return 0;
}