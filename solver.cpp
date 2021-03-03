#include <vector>
#include <iostream>
#include <string>
using namespace std;

class grid
{
private:
    vector<vector<int>> g;
    bool is_placeable(int i, int j, int val)
    {
        int cnt = (i / 3) * 3 + j / 3;
        if (!h_done[i][val] && !v_done[j][val] && !box_done[cnt][val])
        {
            return true;
        }
        else
        {
            return false;
        }
    }

public:
    vector<vector<bool>> h_done, v_done, box_done;
    bool insert_cell(int i, int j, int val)
    {
        if (is_placeable(i, j, val))
        {
            int cnt = (i / 3) * 3 + j / 3;
            h_done[i][val] = true;
            v_done[j][val] = true;
            box_done[cnt][val] = true;

            g[i][j] = val;
            return true;
        }
        else
        {
            return false;
        }
    }
    void remove_cell(int i, int j)
    {
        int cnt = (i / 3) * 3 + j / 3;

        int val = g[i][j];
        h_done[i][val] = false;
        v_done[j][val] = false;
        box_done[cnt][val] = false;
        g[i][j] = 0;
    }

    bool is_empty(int i, int j)
    {
        if (g[i][j] == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    void get_grid()
    {
        for (int i = 0; i <= 10; i++)
        {
            h_done.push_back(vector<bool>(10, false));
            v_done.push_back(vector<bool>(10, false));
            box_done.push_back(vector<bool>(10, false));
        }
        string x;
        cin >> x;
        for (int i = 0; i < 9; i++)
        {
            g.push_back(vector<int>(9));
            for (int j = 0; j < 9; j++)
            {
                int cnt = (i / 3) * 3 + j / 3;
                g[i][j] = x[i * 9 + j] - '0';
                if (g[i][j] != 0)
                {
                    h_done[i][g[i][j]] = true;
                    v_done[j][g[i][j]] = true;
                    box_done[cnt][g[i][j]] = true;
                }
            }
        }
    }
    void print_grid()
    {
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                cout << g[i][j];
            }
        }
        cout << endl;
    }
};

class solver
{
private:
    grid start, current, ans;

public:
    void input_start()
    {
        start.get_grid();
        current = start;
    }
    void show_ans()
    {
        if (solve(0, 0))
        {
            ans.print_grid();
        }
        else
        {
            cout << "failed..." << endl;
        }
    }
    bool solve(int i, int j)
    {
        if (i == 9)
        {
            ans = current;
            return true;
        }
        int nexti = i + (j == 8 ? 1 : 0);
        int nextj = (j == 8 ? 0 : j + 1);
        if (current.is_empty(i, j))
        {
            for (int k = 1; k <= 9; k++)
            {
                if (current.insert_cell(i, j, k))
                {
                    if (solve(nexti, nextj))
                    {
                        return true;
                    }
                    else
                    {
                        current.remove_cell(i, j);
                    }
                }
            }
            return false;
        }
        else
        {
            return solve(nexti, nextj);
        }
    }
};

int main()
{
    solver s;
    s.input_start();
    s.show_ans();
    return 0;
}