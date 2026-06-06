/*
Задача A. Сумма на отрезке
Имя входного файла: стандартный ввод
Имя выходного файла: стандартный вывод
Дан массив из N элементов, нужно научиться находить сумму чисел на отрезке.
Формат входных данных:
Первая строка входного файла содержит два целых числа N и K — количество чисел в массиве и
количество запросов. Следующие K строк содержат следующие запросы:
1. A i x — присвоить i-му элементу массива значение x;
2. Q l r — найти сумму чисел в массиве на позициях от l до r. Изначально в массиве живут нули.
Формат выходных данных:
На каждый запрос вида Q l r нужно вывести единственное число — сумму на отрезке.
*/

#include <iostream>
#include <vector>

using namespace std;

int n, k;
vector<long long> tree;

void update(int node, int l, int r, int pos, long long val)
{
    if (l == r)
    {
        tree[node] = val; return;
    }

    int mid = (l + r) / 2;
    if (pos <= mid) update(2 * node, l, mid, pos, val);
    else update(2 * node + 1, mid + 1, r, pos, val);
    tree[node] = tree[2 * node] + tree[2 * node + 1];
}

long long query(int node, int l, int r, int ql, int qr)
{
    if (qr < l || r < ql) return 0;
    if (ql <= l && r <= qr) return tree[node];
    int mid = (l + r) / 2;
    return query(2 * node, l, mid, ql, qr) + query(2 * node + 1, mid + 1, r, ql, qr);
}

int main()
{
    cin >> n >> k;
    tree.assign(4 * n, 0);

    while (k--)
    {
        char c;
        cin >> c;
        if (c == 'A')
        {
            int i;
            long long x;
            cin >> i >> x;
            update(1, 1, n, i, x);
        } 
        else
        {
            int l, r;
            cin >> l >> r;
            cout << query(1, 1, n, l, r) << '\n';
        }
    }
    return 0;
}