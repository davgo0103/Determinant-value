#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;
double det = 1;
void swap(double** p, int* tx, int* ty, int* m, int* n) {
    double tmp;
    int tmpx = *tx, tmpy = *ty;
    for (int i = tmpy; i < *m; i++) {
        if (p[i][tmpx] != 0) {
            for (int s = tmpx; s < *n; s++) {
                tmp = p[i][s];
                p[i][s] = p[*ty][s];
                p[*ty][s] = tmp;
            }
            det = det * -1;
            return;
        }
    }
    det = 0;
}
void down(double** p, int* tx, int* ty, int* m, int* n) {
    int tmpx = *tx, tmpy = *ty;
    double num;
    for (int i = tmpy + 1; i < *m; i++) {
        num = p[i][tmpx];
        if (num != 0) {
            for (int j = tmpx; j < *n; j++) {
                p[i][j] = p[i][j] + (p[tmpy][j] * -1 * num);
            }
        }
    }
}
void operation(double** p, int* tx, int* ty, int* m, int* n) {
    int tmpy = *ty;
    int tmpx = *tx;
    double leader = p[tmpy][tmpx];
    if (leader != 0) {
        for (int i = tmpx; i < *n; i++) { //取得前導1
            if (leader != 1) {
                p[tmpy][i] = p[tmpy][i] / leader;
            }
            else {
                break;
            }
        }
        det = det * leader;
        down(p, tx, ty, m, n);
    }
    *ty = *ty + 1; *tx = *tx + 1;
}

void openfile(int* m, int* n) {
    ifstream ifs;
    string buffer;
    string space_delimiter = " ";
    size_t pos = 0;
    ifs.open("D:\input.txt");
    if (!ifs.is_open()) {
        cout << "Failed to open file.\n";
    }
    else {
        while (getline(ifs, buffer)) {
            *m = *m + 1;
        }
        while ((pos = buffer.find(space_delimiter)) != string::npos) { //計算n
            buffer.erase(0, pos + space_delimiter.length());
            *n = *n + 1;
        }

        ifs.close();
    }
}

int main()
{
    ifstream ifs;
    string buffer;
    string space_delimiter = " ";
    size_t pos = 0;
    int m = 0, n = 1, x = 0, y = 0;
    double** matrix = NULL;

    openfile(&m, &n);

    ifs.open("D:\input.txt");
    if (!ifs.is_open()) {
        cout << "Failed to open file.\n";
    }
    else {
        matrix = (double**)malloc(m * sizeof(double*));
        int i = 0;
        while (getline(ifs, buffer)) {
            matrix[i] = (double*)malloc(n * sizeof(double));
            int j = 0;
            while ((pos = buffer.find(space_delimiter)) != string::npos) { //計算n
                matrix[i][j] = stof(buffer.substr(0, pos));
                buffer.erase(0, pos + space_delimiter.length());
                j++;
            }
            matrix[i][j] = stof(buffer.substr(0, pos));
            i++;
        }
        ifs.close();
    }


    while (true)
    {
        if (matrix[y][x] == 0 && x < n && y < m) { //找出非零整數
            swap(*&matrix, &x, &y, &m, &n);
        }
        operation(*&matrix, &x, &y, &m, &n);
        if (x + 1 > n || y + 1 > m || det == 0) {
            break;
        }
    }

    cout << "det = " << det;
}