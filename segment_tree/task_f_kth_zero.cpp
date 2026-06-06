/*
Задача F. Катый ноль
Имя входного файла: стандартный ввод
Имя выходного файла: стандартный вывод
Реализуйте эффективную структуру данных, позволяющую изменять элементы массива
и вычислять индекс k-го слева нуля на данном отрезке в массиве.
Формат входных данных:
В первой строке вводится одно натуральное число N — количество чисел в массиве.
Во второй строке вводятся N чисел от 0 до 100 000 — элементы массива.
В третьей строке вводится одно натуральное число M — количество запросов.
Каждая из следующих M строк представляет собой описание запроса.
Сначала вводится одна буква, кодирующая вид запроса (s — вычислить индекс k-го нуля, u — обновить значение элемента).
Следом за s вводится три числа — левый и правый концы отрезка и число k.
Следом за u вводятся два числа — номер элемента и его новое значение.
Формат выходных данных:
Для каждого запроса s выведите результат. Все числа выводите в одну строку через пробел.
Если нужного числа нулей на запрашиваемом отрезке нет, выводите −1 для данного запроса.
*/

#include <iostream>
#include <vector>

using namespace std;

int n;
vector<int> a;
vector<int> tree;

void build(int node, int l, int r)
{
    if (l == r)
    {
        tree[node] = (a[l] == 0) ? 1 : 0;
        return;
    }
    int mid = (l + r) / 2;
    build(2 * node, l, mid);
    build(2 * node + 1, mid + 1, r);
    tree[node] = tree[2 * node] + tree[2 * node + 1];
}

void update(int node, int l, int r, int pos, int val)
{
    if (l == r)
    {
        tree[node] = (val == 0) ? 1 : 0;
        return;
    }
    int mid = (l + r) / 2;
    if (pos <= mid) update(2 * node, l, mid, pos, val);
    else update(2 * node + 1, mid + 1, r, pos, val);
    tree[node] = tree[2 * node] + tree[2 * node + 1];
}

int descend(int node, int l, int r, int k)
{
    while (l < r)
    {
        int mid = (l + r) / 2;
        if (tree[2 * node] >= k)
        { 
            node = 2 * node; 
            r = mid; 
        }
        else 
        { 
            k -= tree[2 * node]; 
            node = 2 * node + 1; 
            l = mid + 1; 
        }
    }

    return l;
}

int findKth(int node, int l, int r, int ql, int qr, int &k)
{
    if (qr < l || r < ql) return -1;
    if (ql <= l && r <= qr)
    {
        if (tree[node] < k)
        { 
            k -= tree[node];
            return -1;
        }

        return descend(node, l, r, k);
    }
    int mid = (l + r) / 2;
    int res = findKth(2 * node, l, mid, ql, qr, k);
    if (res != -1) return res;
    return findKth(2 * node + 1, mid + 1, r, ql, qr, k);
}

int main() 
{
    cin >> n;
    a.assign(n + 1, 0);
    for (int i = 1; i <= n; ++i) cin >> a[i];
    tree.assign(4 * n, 0);
    build(1, 1, n);

    int m;
    cin >> m;
    bool first = true;
    while (m--) 
    {
        char c;
        cin >> c;
        if (c == 's') 
        {
            int l, r, k;
            cin >> l >> r >> k;
            int kk = k;
            int ans = findKth(1, 1, n, l, r, kk);
            if (!first) cout << ' ';
            cout << ans;
            first = false;
        } 
        else 
        {
            int i, x;
            cin >> i >> x;
            update(1, 1, n, i, x);
        }
    }

    cout << '\n';
    return 0;
}