/*
Задача E. Дейкстра с восстановлением пути
Имя входного файла: стандартный ввод
Имя выходного файла: стандартный вывод
Вам дан взвешенный неориентированный граф G на n вершин и m ребер и вершины s и t.
Найдите кратчайший путь от вершины s до t.
Формат входных данных:
В первой строке вводятся четыре числа числа n, m, s, t — количество вершин, количество ребер,
номер стартовой и конечной вершины. В следующих m строках вводятся по три числа ai, bi, ci — ребра графа.
Формат выходных данных:
Если пути из s в t не существует выведите единственное число −1.
Иначе выведите в первой строке число d, равное расстоянию от вершины s до t, и число k,
равное числу вершин в одном из кратчайших путей из s в t. Во второй строке выведите k чисел — вершины,
через которые проходит один из кратчайших путей из s в t.
*/

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int main()
{
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    vector<vector<pair<int,long long>>> adj(n + 1);

    for (int i = 0; i < m; ++i)
    {
        int a, b;
        long long c;
        cin >> a >> b >> c;
        adj[a].push_back({b, c});
        adj[b].push_back({a, c});
    }

    const long long INF = (long long)4e18;
    vector<long long> dist(n + 1, INF);
    vector<int> parent(n + 1, -1);
    priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<>> pq;
    dist[s] = 0;
    pq.push({0, s});
    
    while (!pq.empty())
    {
        auto [d, v] = pq.top(); pq.pop();
        if (d > dist[v]) continue;
        for (auto [u, w] : adj[v])
        {
            if (dist[v] + w < dist[u])
            {
                dist[u] = dist[v] + w;
                parent[u] = v;
                pq.push({dist[u], u});
            }
        }
    }
    if (dist[t] == INF)
    {
        cout << -1 << '\n';
        return 0;
    }
    vector<int> path;
    for (int v = t; v != -1; v = parent[v]) path.push_back(v);
    reverse(path.begin(), path.end());
    cout << dist[t] << ' ' << path.size() << '\n';
    for (size_t i = 0; i < path.size(); ++i)
    {
        cout << path[i];
        if (i + 1 < path.size()) cout << ' ';
    }

    cout << '\n';
    return 0;
}