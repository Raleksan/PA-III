// Ryabov Aleksandr
// B22-DSAI-01
// a.ryabov@innpolis.university

#include <bits/stdc++.h>
#include <cmath>

using namespace std;

int main()
{
    long in_v, in_k;
    cin >> in_v >> in_k;

    double al1, al2, bt1, bt2;
    cin >> al1 >> bt1 >> al2 >> bt2;

    double v0 = in_v - al2 / bt2;
    double k0 = in_k - al1 / bt1;

    long time, approx;
    cin >> time >> approx;

    vector<double> ts (approx + 1);
    vector<double> vs (approx + 1);
    vector<double> ks (approx + 1);

    for (int i = 0; i < approx + 1; i++)
    {
        double timePnt = double(i) * time / approx;

        double v = v0 * cos( sqrt(al1 * al2) * timePnt ) - 
            (k0 * sqrt(al2) * bt1 * sin( sqrt(al1 * al2) * timePnt )) / 
            (bt2 * sqrt(al1)) + al2 / bt2;

        double k = k0 * cos( sqrt(al1 * al2) * timePnt ) +
            (v0 * sqrt(al1) * bt2 * sin( sqrt(al1 * al2) * timePnt )) / 
            (bt1 * sqrt(al2)) + al1 / bt1;

        ts[i] = timePnt;
        ks[i] = k;
        vs[i] = v;
    }

    cout << "t:\n";
    for (auto elem: ts) 
    {
        printf("%.2f ", elem);
    }
    cout << "\n";

    cout << "v:\n";
    for (auto elem: vs)
    {
        printf("%.2f ", elem);
    }
    cout << "\n";

    cout << "k:\n";
    for (auto elem: ks)
    {
        printf("%.2f ", elem);
    }
    cout << "\n";

    return 0;
}   