/*
Задача E. Очередь с минимумом
Имя входного файла: стандартный ввод
Имя выходного файла: стандартный вывод
Вам дано q запросов трех типов:
• «1 x» — добавить число x в конец очереди.
• «2» — вывести на экран и удалить первое число из очереди.
Гарантируется, что очедерь в данный момент времени не пуста.
• «3 i» — вывести на экран i-е число очереди.
Гарантируется, что i, где len — это размер очереди в данный момент времени.
• «4» — вывести на экран минимальное число очереди.
Гарантируется, что очедерь в данный момент времени не пуста.
Формат входных данных:
В первой строке вводится одно число q — количество запросов.
В последующие q строках вводятся запросы в выше описанном формате.
Формат выходных данных:
Для каждого запроса второго, третьего и четвёртого типа выведите по одному числу.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int q;
    cin >> q;
    vector<long long> in_st, in_min, out_st, out_min;

    while (q--)
    {
        int t;
        cin >> t;

        if (t == 1)
        {
            long long x;
            cin >> x;
            in_st.push_back(x);
            in_min.push_back(in_min.empty() ? x : min(in_min.back(), x));
        }
        else if (t == 2)
        {
            if (out_st.empty())
            {
                while (!in_st.empty())
                {
                    long long v = in_st.back();
                    in_st.pop_back();
                    in_min.pop_back();
                    out_st.push_back(v);
                    out_min.push_back(out_min.empty() ? v : min(out_min.back(), v));
                }
            }

            cout << out_st.back() << '\n';
            out_st.pop_back();
            out_min.pop_back();
        }
        else if (t == 3)
        {
            int i;
            cin >> i;
            int os = (int)out_st.size();
            if (i <= os)
            {
                cout << out_st[os - i] << '\n';
            }
            else
            {
                cout << in_st[i - os - 1] << '\n';
            }
        }
        else
        {
            long long mn;
            if (out_min.empty()) mn = in_min.back();
            else if (in_min.empty()) mn = out_min.back();
            else mn = min(in_min.back(), out_min.back());

            cout << mn << '\n';
        }
    }
    
    return 0;
}
