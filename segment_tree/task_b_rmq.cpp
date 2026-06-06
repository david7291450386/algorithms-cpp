/*
Задача B. RMQ
Имя входного файла: стандартный ввод
Имя выходного файла: стандартный вывод
Реализуйте структуру данных, которая на данном массиве из N целых чисел позволяет узнать
максимальное значение на этом массиве и индекс элемента, на котором достигается это максимальное значение.
Формат входных данных:
В первой строке вводится натуральное число N – количество элементов в массиве.
В следующей строке содержатся N целых чисел, не превосходящих по модулю 10^9 – элементы массиваб гарантируется,
что в массиве нет одинаковых элементов. Далее идет число K – количество запросов к структуре данных.
Каждая из следующих K строк содержит два целых числа l и r – левую и правую границы отрезка в массиве для данного запроса.
Формат выходных данных:
Для каждого из запросов выведите два числа: наибольшее значение среди элементов массива
на отрезке от l до r и индекс одного из элементов массива, принадлежащий отрезку от l до r,
на котором достигается этот максимум.
*/

#include <iostream>
#include <vector>
#include <climits>

using namespace std;

int n;
vector<long long> a;
vector<pair<long long, int>> tree;

pair<long long, int> combine(const pair<long long, int>& x, const pair<long long, int>& y)
{
    return (x.first >= y.first) ? x : y;
}

void build(int node, int l, int r)
{
    if (l == r)
    {
        tree[node] = {a[l], l}; 
        return;
    }

    int mid = (l + r) / 2;
    build(2 * node, l, mid);
    build(2 * node + 1, mid + 1, r);
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
    tree.assign(4 * n, {LLONG_MIN, -1});
    build(1, 1, n);

    int q;
    cin >> q;
    while (q--)
    {
        int l, r;
        cin >> l >> r;
        auto res = query(1, 1, n, l, r);
        cout << res.first << ' ' << res.second << '\n';
    }

    return 0;
}