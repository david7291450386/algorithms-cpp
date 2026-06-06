/*
Задача F. Шарики
Имя входного файла: стандартный ввод
Имя выходного файла: стандартный вывод
В одной компьютерной игре игрок выставляет в линию шарики разных цветов.
Когда образуется непрерывная цепочка из трех и более шариков одного цвета,
она удаляется из линии. Все шарики при этом сдвигаются друг к другу,
и ситуация может повториться. Напишите программу,
которая по данной ситуации определяет, сколько шариков будет «уничтожено».
Естественно, непрерывных цепочек из трех и более одноцветных шаров
в начальный момент может быть не более одной.
Формат входных данных:
Сначала вводится количество шариков в цепочке n, а затем цвета шариков ci.
Формат выходных данных:
Требуется вывести количество шариков, которое будет «уничтожено».
*/

#include <iostream>
#include <list>

using namespace std;

int main()
{
    int n;
    cin >> n;
    list<pair<int,int>> lst;

    for (int i = 0; i < n; ++i)
    {
        int c;
        cin >> c;
        if (!lst.empty() && lst.back().first == c) lst.back().second++;
        else lst.push_back({c, 1});
    }

    long long removed = 0;
    auto chain_it = lst.end();
    for (auto it = lst.begin(); it != lst.end(); ++it)
    {
        if (it->second >= 3)
        {
            chain_it = it;
            break;
        }
    }

    while (chain_it != lst.end())
    {
        removed += chain_it->second;
        bool has_prev = (chain_it != lst.begin());
        auto prev_it = has_prev ? prev(chain_it) : lst.end();
        auto next_it = next(chain_it);

        lst.erase(chain_it);

        if (has_prev && next_it != lst.end() && prev_it->first == next_it->first)
        {
            prev_it->second += next_it->second;
            lst.erase(next_it);
            chain_it = (prev_it->second >= 3) ? prev_it : lst.end();
        }
        else
        {
            chain_it = lst.end();
        }
    }

    cout << removed << endl;
    return 0;
}
