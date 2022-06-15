#include <iostream>
#include <vector>
#include <algorithm>

void    solve(std::vector<int> &vi_set, int n, int L);
int     find_lower_bound(std::vector<int> &vi_set, int n, int left, int right);
int     find_upper_bound(std::vector<int> &vi_set, int n, int left, int right);
int     get_lower_bound(std::vector<int> &vi_set, int n, int L);
int     get_upper_bound(std::vector<int> &vi_set, int n, int L);
int     comb_2(int n);

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::vector<int>    vi_set;
    int                 i;
    int                 L;
    int                 num;
    int                 n;

    i = 0;
    std::cin >> L;
    while (++i <= L)
    {
        std::cin >> num;
        vi_set.emplace_back(num);
    }
    std::cin >> n;
    std::sort(vi_set.begin(), vi_set.end());

    solve(vi_set, n, L);
    return (0);
}

void    solve(std::vector<int> &vi_set, int n, int L)
{
    const int   lower_bound = get_lower_bound(vi_set, n, L);
    const int   upper_bound = get_upper_bound(vi_set, n, L);
    const int   entire_sections = comb_2(upper_bound - lower_bound - 1);
    const int   no_n_lower_sections = comb_2(n - lower_bound - 1);
    const int   no_n_upper_sections = comb_2(upper_bound - n - 1);

    std::cout << (entire_sections - no_n_lower_sections - no_n_upper_sections);
}

int     find_lower_bound(std::vector<int> &vi_set, int n, int left, int right)
{
    int mid;

    if (left == right)
        return (vi_set.at(left));

    mid = (left + right) / 2 + 1;

    if (vi_set.at(mid) == n)
        return (vi_set.at(mid));
    else if (n < vi_set.at(mid))
        return (find_lower_bound(vi_set, n, left, mid - 1));
    else
        return (find_lower_bound(vi_set, n, mid, right));
}

int     find_upper_bound(std::vector<int> &vi_set, int n, int left, int right)
{
    int mid;

    if (left == right)
        return (vi_set.at(left));

    mid = (left + right) / 2;
    
    if (vi_set.at(mid) == n)
        return (vi_set.at(mid));
    else if (n < vi_set.at(mid))
        return (find_upper_bound(vi_set, n, left, mid));
    else
        return (find_upper_bound(vi_set, n, mid + 1, right));
}

int     get_lower_bound(std::vector<int> &vi_set, int n, int L)
{
    if (n < *(vi_set.begin()))
        return (0);
    else
        return (find_lower_bound(vi_set, n, 0, L - 1));
}

int     get_upper_bound(std::vector<int> &vi_set, int n, int L)
{
    if (n < *(vi_set.begin()))
        return (*vi_set.begin());
    else
        return (find_upper_bound(vi_set, n, 0, L - 1));
}

int     comb_2(int n)
{
    if (n <= 1)
        return (0);
    else
        return (n * (n - 1) / 2);
}