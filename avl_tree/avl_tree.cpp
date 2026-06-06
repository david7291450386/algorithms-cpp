/*
Задание по АВЛ-деревьям.
Создать свой класс (бинарное сбалансированное дерево),
в котором реализованы методы создания дерева по массиву данных,
поиска, добавления, удаления элемента.
Разумеется, при этом должно гарантироваться, что дерево останется АВЛ-деревом.
Продемонстрируйте работоспособность вашего класса на примере.
Хотелось бы, чтоб теоретические данные про асимптотику были бы подтверждены на практике.
Для этого можно создавать файлы со случайными данными разного объёма
и запускать на них тесты для созданного класса.
Результаты удобно представить в виде таблицы или графика.
Особых требований к оформлению не имею.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <random>
#include <chrono>
#include <iomanip>
#include <cmath>
#include <Windows.h>

using namespace std;

struct Node 
{
    int key;
    int height;
    Node* left;
    Node* right;
    Node(int k) : key(k), height(1), left(nullptr), right(nullptr) {}
};

class AVLTree 
{
    Node* root;

    int height(Node* n) 
    {
        return n ? n->height : 0;
    }

    int balanceFactor(Node* n) 
    {
        return n ? height(n->left) - height(n->right) : 0;
    }

    void updateHeight(Node* n) 
    {
        n->height = 1 + max(height(n->left), height(n->right));
    }

    Node* rotateRight(Node* y) 
    {
        Node* x = y->left;
        Node* T2 = x->right;
        x->right = y;
        y->left = T2;
        updateHeight(y);
        updateHeight(x);
        return x;
    }

    Node* rotateLeft(Node* x)
    {
        Node* y = x->right;
        Node* T2 = y->left;
        y->left = x;
        x->right = T2;
        updateHeight(x);
        updateHeight(y);
        return y;
    }

    Node* balance(Node* n) 
    {
        updateHeight(n);
        int bf = balanceFactor(n);

        if (bf > 1) 
        {
            if (balanceFactor(n->left) < 0)
                n->left = rotateLeft(n->left);
            return rotateRight(n);
        }

        if (bf < -1)
        {
            if (balanceFactor(n->right) > 0)
                n->right = rotateRight(n->right);
            return rotateLeft(n);
        }
        return n;
    }

    Node* insert(Node* n, int key) 
    {
        if (!n) return new Node(key);
        if (key < n->key)
            n->left = insert(n->left, key);
        else if (key > n->key)
            n->right = insert(n->right, key);
        else
            return n;
        return balance(n);
    }

    Node* findMin(Node* n) 
    {
        return n->left ? findMin(n->left) : n;
    }

    Node* remove(Node* n, int key) 
    {
        if (!n) return nullptr;

        if (key < n->key)
        {
            n->left = remove(n->left, key);
        }
        else if (key > n->key)
        {
            n->right = remove(n->right, key);
        }
        else
        {
            if (!n->left || !n->right)
            {
                Node* child = n->left ? n->left : n->right;
                delete n;
                return child;
            }
            else
            {
                Node* m = findMin(n->right);
                n->key = m->key;
                n->right = remove(n->right, m->key);
            }
        }
        return balance(n);
    }

    bool search(Node* n, int key)
    {
        if (!n) return false;
        if (key == n->key) return true;
        return key < n->key ? search(n->left, key) : search(n->right, key);
    }

    void inorder(Node* n)
    {
        if (!n) return;
        inorder(n->left);
        cout << n->key << " ";
        inorder(n->right);
    }

    void destroy(Node* n)
    {
        if (!n) return;
        destroy(n->left);
        destroy(n->right);
        delete n;
    }

public:
    AVLTree() : root(nullptr) {}
    ~AVLTree()
    { 
        destroy(root);
    }

    void insert(int key)  
    {
        root = insert(root, key);
    }
    void remove(int key)
    {
        root = remove(root, key);
    }
    bool search(int key)
    {
        return search(root, key);
    }

    void buildFromArray(const vector<int>& a)
    {
        for (int x : a) insert(x);
    }

    void print()
    {
        inorder(root); cout << endl;
    }
    int  treeHeight()
    {
        return height(root);
    }
};

// тестовый main для демонстрации работы АВЛ дерева:
int main()
{
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    cout << "--------------------------------------\n";
    cout << "----Демонстрация работы АВЛ-дерева----\n";
    cout << "--------------------------------------\n";
    vector<int> vec = {10, 20, 30, 40, 50, 25};

    AVLTree tree;
    tree.buildFromArray(vec);

    cout << "Массив:  ";
    for (int x : vec) cout << x << " ";
    cout << "\nОбход по возрастанию:  ";
    tree.print();
    cout << "Высота дерева:  " << tree.treeHeight() << "\n" << endl;

    cout << "Поиск 25:  " << (tree.search(25) ? "найден" : "не найден") << "\n";
    cout << "Поиск 99:  " << (tree.search(99) ? "найден" : "не найден") << "\n";

    tree.remove(30);
    cout << "После удаления 30:     ";
    tree.print();

    cout << "\n----Проверка асимптотики O(log N)----\n";
    cout << left
         << setw(12) << "N"
         << setw(12) << "Высота"
         << setw(12) << "log2(N)"
         << setw(20) << "Построение (мс)"
         << "Поиск 100000 (мс)\n";
    cout << string(70, '-') << "\n";

    mt19937 gen(42);
    vector<int> sizes = {1000, 10000, 100000, 1000000};

    for (int N : sizes) 
    {
        uniform_int_distribution<int> dist(0, 10 * N);

        vector<int> vals(N);
        for (int i = 0; i < N; i++) vals[i] = dist(gen);

        AVLTree t;
        auto t1 = chrono::high_resolution_clock::now();
        t.buildFromArray(vals);
        auto t2 = chrono::high_resolution_clock::now();

        for (int i = 0; i < 100000; i++)
        {
            t.search(dist(gen));
        }
        auto t3 = chrono::high_resolution_clock::now();

        double buildMs  = chrono::duration<double, milli>(t2 - t1).count();
        double searchMs = chrono::duration<double, milli>(t3 - t2).count();

        cout << left
             << setw(12) << N
             << setw(12) << t.treeHeight()
             << setw(12) << fixed << setprecision(1) << log2((double)N)
             << setw(20) << setprecision(2) << buildMs
             << searchMs << endl;
    }

    cout << "\nВидно что при росте N в 10 раз высота растёт всего на ~3 уровня,\n"
         << "а время 100000 поисков почти не меняется — это и есть O(log N).\n";

    return 0;
}