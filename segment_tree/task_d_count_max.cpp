/*
Задача D. Количество максимумов на отрезке
Имя входного файла: стандартный ввод
Имя выходного файла: стандартный вывод
Дан массив из N элементов, нужно научиться находить количество элементов на отрезке [l, r], равных максимуму на этом отрезке.
Формат входных данных:
В первой строке вводится одно натуральное число N — количество чисел в массиве.
Во второй строке вводятся N чисел от 1 до 109 — элементы массива.
В третьей строке вводится одно натуральное число K — количество запросов.
Следующие K строк содержат следующие запросы:
1. A i x — присвоить i-му элементу массива значение x;
2. Q l r — найти количество максимумов на позициях от l до r.
Формат выходных данных:
На каждый запрос вида Q l r нужно вывести единственное число — количество чисел на позициях от l до r,
равных максимуму из чисел этого отрезка.
*/

#include <iostream>
#include <vector>

using namespace std;

int n;
vector<long long> a;
vector<pair<long long, int>> tree;

pair<long long, int> combine(const pair<long long, int>& x, const pair<long long, int>& y) 
{
    if (x.first > y.first) return x;
    if (y.first > x.first) return y;
    return {x.first, x.second + y.second};
}

void build(int node, int l, int r)
{
    if (l == r) 
    { 
        tree[node] = {a[l], 1}; 
        return; 
    }

    int mid = (l + r) / 2;
    build(2 * node, l, mid);
    build(2 * node + 1, mid + 1, r);
    tree[node] = combine(tree[2 * node], tree[2 * node + 1]);
}

void update(int node, int l, int r, int pos, long long val)
{
    if (l == r)
    { 
        tree[node] = {val, 1}; 
        return; 
    }

    int mid = (l + r) / 2;
    if (pos <= mid) update(2 * node, l, mid, pos, val);
    else update(2 * node + 1, mid + 1, r, pos, val);
    tree[node] = combine(tree[2 * node], tree[2 * node + 1]);
}

pair<long long, int> query(int node, int l, int r, int ql, int qr)
{
    if (ql <= l && r <= qr) return tree[node];
    int mid = (l + r) / 2;
    if (qr <= mid) return query(2 * node, l, mid, ql, qr);
    if (ql > mid) return query(2 * node + 1, mid + 1, r, ql, qr);
    return combine(query(2 * node, l, mid, ql, qr), query(2 * node + 1, mid + 1, r, ql, qr));
}

int main() 
{
    cin >> n;
    a.assign(n + 1, 0);
    for (int i = 1; i <= n; ++i) cin >> a[i];
    tree.assign(4 * n, {0, 0});
    build(1, 1, n);

    int k;
    cin >> k;
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
            cout << query(1, 1, n, l, r).second << '\n';
        }
    }

    return 0;
}