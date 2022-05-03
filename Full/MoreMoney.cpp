#include "StateList.h"
#include <vector>
#include <string>
#include <iostream>
using namespace std;

template<class A>
PairList<List<A>, A> select(List<A> lst)
{
    if (lst.isEmpty())
        return PairList<List<A>, A>();

    A       x  = lst.front();
    List<A> xs = lst.popped_front();

    auto result = List<pair<A, List<A>>>();
    forEach(select(xs), [x, &result](pair<A, List<A>> const & p)
    {
        A       y = p.first;
        List<A> ys = p.second;
        auto y_xys = make_pair(y, ys.pushed_front(x));
        result = result.pushed_front(y_xys);
    });

    return result.pushed_front(make_pair(x, xs));
}

int asNumber(vector<int> const & v)
{
    int acc = 0;
    for (auto i : v)
    {
        acc = 10 * acc + i;
    }
    return acc;
}

StateList<List<int>, tuple<int, int, int>> solve()
{
    StateList<List<int>, int> sel = &select<int>;

    return mbind(sel, [=](int s) {
    return mbind(sel, [=](int e) {
    return mbind(sel, [=](int n) {
    return mbind(sel, [=](int d) {
    return mbind(sel, [=](int m) {
    return mbind(sel, [=](int o) {
    return mbind(sel, [=](int r) {
    return mbind(sel, [=](int y) {
    return mthen(guard<List<int>>(s != 0 && m != 0), [=]() {
        int send  = asNumber(vector<int>{s, e, n, d});
        int more  = asNumber(vector<int>{m, o, r, e});
        int money = asNumber(vector<int>{m, o, n, e, y});
        return mthen(guard<List<int>>(send + more == money), [=]() {
            return mreturn<List<int>>(make_tuple(send, more, money));
        });
    }); }); }); }); }); }); }); }); });
}

namespace std {
template<typename T, typename U>
ostream& operator<<(ostream& os, const pair<T,U> & p)
{
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}
    template<class T>
    ostream& operator<<(ostream& os, const tuple<T,T,T> & t)
{
    os << "(" << get<0>(t) << ", " << get<1>(t) << ", " << get<2>(t) << ")";
    return os;
}
}

void testMonad()
{
    List<int>    lst1{ 1, 2, 3,};
    List<string> lst2{ "one", "two", "three" };

    List<pair<int, string>> pairs =
    for_each(lst1, [=](int i) { return
    for_each(lst2, [=](string s) { return
            yield(make_pair(i, s));
    }); });
    cout << pairs << endl;
}

StateList<List<int>, pair<int, int>> mk_pairs() {
    StateList<List<int>, int> sel = &select<int>;

    return mbind(sel, [=](int i) {
        return mbind(sel, [=](int j) {
            return mreturn<List<int>>(
                    make_pair(i, j));
        }); 
    });
}

int main()
{
    testMonad();
    List<int> test{ 4, 3, 2, 1 };
    auto out = fmap([](int v) { return v*2;}, test );
    cout << out << endl;
    cout << select(List<int>{1, 2}) << endl;
    cout << select(List<int>{1, 2, 3}) << endl;
    cout << runStateList(mk_pairs(), List<int>{1, 2, 3}) << endl;
    // List<int> lst{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    // cout << evalStateList(solve(), lst));
    // cout << endl;
    return 0;
}
