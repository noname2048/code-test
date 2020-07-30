#include <cassert>
#include <iostream>
#include <string>
#include <vector>

#define N 8
using namespace std;

bool used[N];
int position[N];

int record_for_activate = 0;
int record_prun_effectiveness = 0;

class ClassFactorial {
   public:
    ClassFactorial();
    static vector<long> cache;
    static int last_called_i;
    static int limits_of_i;
    static long f(int i) {
        assert(last_called_i > 0);
        assert(0 < i);
        assert(i < limits_of_i);

        long& ret = cache[i];
        if (ret > 0)
            return ret;
        else {
            while (last_called_i == i) {
                last_called_i++;
                if (last_called_i > 1) {
                    cache[last_called_i] =
                        cache[last_called_i - 1] * last_called_i;
                    assert(cache[last_called_i] > 0);
                } else if (last_called_i == 0)
                    cache[last_called_i] = 0;
                else if (last_called_i == 1)
                    cache[last_called_i] = 1;
            }
            return ret;
        }
    }
};
vector<long> ClassFactorial::cache = vector<long>(20, -1);
int ClassFactorial::last_called_i = -1;

int abs(int number) {
    if (number < 0)
        return -number;
    else
        return number;
}

int a_k(int number) {
    assert(number <= N);

    static vector<int> cache;
    if (cache.size() < 0) {
        cache = vector<int>(N, -1);
        cache[0] = 1;
    }
    if (cache[number] < 0) {
        cache[number] = cache[number] * (N - number + 1);
    }

    return ClassFactorial::f(N) / ClassFactorial::f(N - number);
}

void solve(int& n, vector<string>& condition) { ClassFactorial::f(0); };

void recur(int depth) {
    if (depth >= N)
        return;
    else {
        for (int i = 0; i < N; i++) {
            if (used[i] == false) {
                used[i] = true;
                position[depth] = i;

                recur(depth + 1);

                used[i] = false;
                position[depth] = -1;
            }
            record_for_activate += 1;
        }
    }
}

int main() {
    fill_n(used, N, false);
    fill_n(position, N, -1);
    fill_n(&Factorial::cache[2], 18, -1);

    printf("%d", A.a);
    Factorial::cache[0] = 0;
    vector<string> a;
    solve(N, a);
    return 0;
}