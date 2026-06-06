/*
Задача E. Количество различных на отрезке
Имя входного файла: стандартный ввод
Имя выходного файла: стандартный вывод
Дан массив a, состоящий из небольших целых чисел. Нужно научиться находить количество различных элементов на отрезке.
Формат входных данных:
В первой строке вводится одно натуральное число N — количество чисел в массиве.
Во второй строке вводятся N чисел от 1 до 40 — элементы массива.
В третьей строке вводится одно натуральное число K — количество запросов.
Следующие K строк содержат следующие запросы:
1. A i x — присвоить i-му элементу массива значение x;
2. Q l r — найти количество различных чисел на позициях от l до r.
Формат выходных данных:
На каждый запрос вида Q l r нужно вывести единственное число — количество различных чисел на позициях от l до r.
*/

#include <iostream>
#include <vector>

using namespace std;

int n;
vector<int> a;
vector<long long> tree;

void build(int node, int l, int r) 
{
    if (l == r) 
    { 
        tree[node] = 1LL << (a[l] - 1); 
        return; 
    }

    int mid = (l + r) / 2;
    build(2 * node, l, mid);
    build(2 * node + 1, mid + 1, r);
    tree[node] = tree[2 * node] | tree[2 * node + 1];
}

void update(int node, int l, int r, int pos, int val) 
{
    if (l == r) 
    { 
        tree[node] = 1LL << (val - 1); 
        return; 
    }

    int mid = (l + r) / 2;
    if (pos <= mid) update(2 * node, l, mid, pos, val);
    else update(2 * node + 1, mid + 1, r, pos, val);
    tree[node] = tree[2 * node] | tree[2 * node + 1];
}

long long query(int node, int l, int r, int ql, int qr)
{
    if (qr < l || r < ql) return 0;
    if (ql <= l && r <= qr) return tree[node];
    int mid = (l + r) / 2;
    return query(2 * node, l, mid, ql, qr) | query(2 * node + 1, mid + 1, r, ql, qr);
}

int main() 
{
    cin >> n;
    a.assign(n + 1, 0);
    for (int i = 1; i <= n; ++i) cin >> a[i];
    tree.assign(4 * n, 0);
    build(1, 1, n);

    int k;
    cin >> k;
    while (k--) 
    {
        char c;
        cin >> c;
        if (c == 'A') 
        {
            int i, x;
            cin >> i >> x;
            update(1, 1, n, i, x);
        } 
        else 
        {
            int l, r;
            cin >> l >> r;
            cout << __builtin_popcountll(query(1, 1, n, l, r)) << '\n';
        }
    }

    return 0;
}