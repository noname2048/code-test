#include <iostream>
#include <vector>

#define ABS(x) (x>0?x:-x)

using namespace std;


enum Name { A = 0, C, F, J, M, N, R, T };
int global_n = -1;
vector<string> global_data;
int global_cnt = 0;

int person_serial[8] = { -1, -1, -1, -1, -1, -1, -1, -1 };
int person_position[8] = { -1, -1, -1, -1, -1, -1, -1, -1 };
bool used[8] = { false, };
int table[256];

void pre_char2idx() {
    char names[9] = "ACFJMNRT";
    for (int i=0; i<8; i++) {
        table[names[i]] = i;
    }
}

// char2idx('A') => 0
int char2idx(char c) {
    return table[int(c)];
}

/**
 * verify condition
 * 
 * A~F=3
 * A, F have to used (true)
 * called by prun
 */
bool verify(int cond_idx) {
    int a = char2idx(global_data[cond_idx][0]);
    int b = char2idx(global_data[cond_idx][2]);
    int c = global_data[cond_idx][3];
    int distance = ABS(person_position[a] - person_position[b]);
    int between_friends = distance - 1;
    int target = int(global_data[cond_idx][4]) - int('0');
    switch(c) {
    case '=':
        return (between_friends == target);
        break;
    case '<':
        return (between_friends < target);
        break;
    case '>':
        return (between_friends > target);
        break;
    default:
        printf("error\n");
        exit(0);
    }
}

/**
 * can be prun?
 * true => yes (not search anymore)
 * false => no (more search)
 */
bool prun() {
    for (int i = 0; i < global_n; i++) {
        int first = char2idx(global_data[i][0]);
        int second = char2idx(global_data[i][2]);
        if (used[first] == true && used[second] == true) {
            if (verify(i) == false) {
                // printf("case %02d\n", i);
                return true;
            }
        }
    }
    return false;
}


int recur(int idx) {
    if (idx == 8) {
        if (prun() == false){
            printf("%2d %2d %2d %2d %2d %2d %2d %2d\n",
                    person_serial[0], person_serial[1], person_serial[2], person_serial[3],
                    person_serial[4], person_serial[5], person_serial[6], person_serial[7]);
            global_cnt += 1;
        }
    }
    else {
        for (int i=0; i<8; i++) {
            if (used[i] == false) {
                used[i] = true;
                person_serial[idx] = i;
                person_position[i] = idx;

                if (prun() == false) {
                    recur(idx + 1);
                }
                else {
                    // printf("%2d %2d %2d %2d %2d %2d %2d %2d\n",
                    // person_serial[0], person_serial[1], person_serial[2], person_serial[3],
                    // person_serial[4], person_serial[5], person_serial[6], person_serial[7]);
                }

                person_serial[idx] = -1;
                person_position[i] = -1;
                used[i] = false;
            }
        }
    }
}

int solution(int n, vector<string> data) {
    pre_char2idx();
    
    global_data = data;
    global_n = n;
    global_cnt = 0;

    recur(0);
    return global_cnt;
}

int main() {
    vector<string> q1 = { "N~F=0", "R~T>2" };
    vector<string> q2 = { "M~C<2", "C~M>1" };

    int ans = solution(q2.size(), q2);
    printf("%d\n", ans);
    return 0;
}