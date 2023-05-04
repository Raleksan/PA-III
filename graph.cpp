// Ryabov Aleksandr
// B22-DSAI-01
// a.ryabov@innpolis.university

#include <bits/stdc++.h>
#include <cmath>
#include <cstdio>
#include <sstream>

using namespace std;

#define GNUPLOT_NAME "gnuplot -persist"

int main()
{
    std::string rawString = R"(11
42
0.6
0.035
0.14
0.002
100
1000)";

    stringstream input(rawString);
    cin.rdbuf(input.rdbuf());

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

    FILE* pipe1 = popen(GNUPLOT_NAME, "w"); 
    fprintf(pipe1, "plot '-' title \"v(t)\" pt 3 ps 2 lc \"black\", '-' title \"k(t)\" pt 3 ps 2 lc \"grey\" \n");

    for (int i = 0; i < approx + 1; i++)
    {
        fprintf(pipe1, "%f\t%f\n", ts[i], vs[i]);
    }

    fprintf(pipe1, "e\n");

    for (int i = 0; i < approx + 1; i++)
    {
        fprintf(pipe1, "%f\t%f\n", ts[i], ks[i]);
    }

    fprintf(pipe1, "e\n");

    fflush(pipe1);

    pclose(pipe1);


    FILE* pipe2 = popen(GNUPLOT_NAME, "w");

    fprintf(pipe2, "reset\n");
    fprintf(pipe2, "plot '-' title \"v(k)\" pt 3 ps 2 lc \"black\" \n");

    for (int i = 0; i < approx + 1; i++)
    {
        fprintf(pipe2, "%f\t%f\n", ks[i], vs[i]);
    }

    fprintf(pipe2, "e\n");

    pclose(pipe2);

    return 0;
}   