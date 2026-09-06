#include "library/template.hpp"
#include <cassert>
using namespace std;
using namespace vectorial;

signed main() {
    int N;
    read(N);

    vector<long long> X(N), Y(N);

    for (int i = 0; i < N; ++i) {
        long long A, B;
        read(A, B);
        X[i] = A + B;
        Y[i] = A - B;
    }

    vector<int> px(N), py(N);
    iota(px.begin(), px.end(), 0);
    iota(py.begin(), py.end(), 0);

    sort(px.begin(), px.end(), [&](int i, int j) {
        if (X[i] != X[j]) return X[i] < X[j];
        return i < j;
    });

    sort(py.begin(), py.end(), [&](int i, int j) {
        if (Y[i] != Y[j]) return Y[i] < Y[j];
        return i < j;
    });

    vector<int> sx(N), sy(N);

    for (int k = N / 2; k < N; ++k) {
        sx[px[k]] = 1;
        sy[py[k]] = 1;
    }

    vector<int> g[4];

    for (int i = 0; i < N; ++i) {
        g[sx[i] * 2 + sy[i]].push_back(i);
    }

    assert(g[0].size() == g[3].size());
    assert(g[1].size() == g[2].size());

    for (int k = 0; k < (int)g[0].size(); ++k) {
        cout << g[0][k] + 1 << ' ' << g[3][k] + 1 << '\n';
    }

    for (int k = 0; k < (int)g[1].size(); ++k) {
        cout << g[1][k] + 1 << ' ' << g[2][k] + 1 << '\n';
    }
}