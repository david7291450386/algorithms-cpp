/*
Задача C. НОД на подотрезках с изменением элемента
Имя входного файла: стандартный ввод
Имя выходного файла: стандартный вывод
Реализуйте эффективную структуру данных,
позволяющую изменять элементы массивы и вычислять НОД нескольких подряд идущих элементов.
Формат входных данных:
В первой строке вводится одно натуральное число N – количество чисел в массиве.
Во второй строке вводятся N чисел от 0 до 100000 – элементы массива.
В третьей строке вводится одно натуральное число M – количество запросов.
Каждая из следующих M строк представляет собой описание запроса.
Сначала вводится одна буква, кодирующая вид запроса (s – вычислить НОД, u – обновить значение элемента).
Следом за s вводятся два числа – номера левой и правой границы отрезка.
Следом за u вводятся два числа – номер элемента и его новое значение.
Формат выходных данных:
Для каждого запроса s выведите результат. Все числа выводите в одну строку через пробел.
*/

#include <iostream>
#include <vector>

using namespace std;

long long g(long long x, long long y) 
{
    while (y) 
    { 
        x %= y; 
        swap(x, y); 
    }

    return x;
}

int n;
vector<long long> a;
vector<long long> tree;

void build(int node, int l, int r)
{
    if (l == r) 
    { 
        tree[node] = a[l]; 
        return; 
    }
    int mid = (l + r) / 2;
    build(2 * node, l, mid);
    build(2 * node + 1, mid + 1, r);
    tree[node] = g(tree[2 * node], tree[2 * node + 1]);
}

void update(int node, int l, int r, int pos, long long val) 
{
    if (l == r) 
    { 
        tree[node] = val; return; 
    }

    int mid = (l + r) / 2;
    if (pos <= mid) update(2 * node, l, mid, pos, val);
    else update(2 * node + 1, mid + 1, r, pos, val);
    tree[node] = g(tree[2 * node], tree[2 * node + 1]);
}

long long query(int node, int l, int r, int ql, int qr) 
{
    if (qr < l || r < ql) return 0;
    if (ql <= l && r <= qr) return tree[node];
    int mid = (l + r) / 2;
    return g(query(2 * node, l, mid, ql, qr), query(2 * node + 1, mid + 1, r, ql, qr));
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
            int l, r;
            cin >> l >> r;
            if (!first) cout << ' ';
            cout << query(1, 1, n, l, r);
            first = false;
        } 
        else 
        {
            int i;
            long long x;
            cin >> i >> x;
            update(1, 1, n, i, x);
        }
    }

    cout << '\n';
    return 0;
}