/*
Задача A. BFS на очереди
Имя входного файла: стандартный ввод
Имя выходного файла: стандартный вывод
Вам дан граф неориентированный невзвешенный G на n вершин и m ребер и вершина s.
Найдите расстояния от вершины s до всех остальных вершин.
Формат входных данных:
В первой строке вводятся три числа n, m, s — количество вершин, количество ребер
и стартовая вершина соответсвенно.
В следующих m строках вводится по два числа ai, bi — ребра графа G.
Формат выходных данных:
В единственной строке выведите n числе, где i-е равно расстоянию от вершины s до i,
если путь от s до i существует, и −1 иначе.
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main()
{
    int n, m, s;
    cin >> n >> m >> s;
    vector<vector<int>> adj(n + 1);
    
    for (int i = 0; i < m; ++i)
    {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    
    vector<int> dist(n + 1, -1);
    queue<int> q;
    dist[s] = 0;
    q.push(s);

    while (!q.empty())
    {
        int v = q.front(); q.pop();
        for (int u : adj[v])
        {
            if (dist[u] == -1)
            {
                dist[u] = dist[v] + 1;
                q.push(u);
            }
        }
    }
    for (int i = 1; i <= n; ++i)
    {
        cout << dist[i];
        if (i < n) cout << ' ';
    }

    cout << '\n';
    return 0;
}