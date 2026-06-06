/*
Задача E. Есть ли цикл?
Имя входного файла: стандартный ввод
Имя выходного файла: стандартный вывод
Дан ориентированный граф. Требуется определить, есть ли в нем цикл.
Формат входных данных:
В первой строке вводится число n - количество вершин и m - количество ребер.
Далее в m строках следует по 2 числа u, v - вершины графа, соединенные ребром.
Формат выходных данных:
Выведите 0, если в заданном графе нет цикла, и 1, если он есть.
*/

/*
Классический DFS с тремя цветами:
0 - не посещена (белый);
1 - в стеке текущего обхода (серый);
2 - обработана (чёрный).
Ребро в серую вершину = цикл.
Реализация итеративная, потому что n до 10^5 и рекурсия может переполнить стек.
*/

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n + 1);

    for (int i = 0; i < m; ++i)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }

    vector<int> color(n + 1, 0);
    bool hasCycle = false;

    for (int start = 1; start <= n && !hasCycle; ++start)
    {
        if (color[start] != 0) continue;
        stack<pair<int, int>> st;
        st.push({start, 0});
        color[start] = 1;
        while (!st.empty())
        {
            auto& [v, i] = st.top();
            if (i < (int)adj[v].size())
            {
                int u = adj[v][i];
                i++;
                if (color[u] == 0)
                {
                    color[u] = 1;
                    st.push({u, 0});
                }
                else if (color[u] == 1)
                {
                    hasCycle = true;
                    break;
                }
            }
            else
            {
                color[v] = 2;
                st.pop();
            }
        }
    }
    
    cout << (hasCycle ? 1 : 0) << endl;
    return 0;
}