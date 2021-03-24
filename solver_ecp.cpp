#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

class ecp
{
    int n = 16;
    int root_n = 4;
    int rows = n * n * n;
    int cols = n * n * 4;
    int nodes = rows * cols;

    int row_num(int r, int x)
    {
        return n * n * 0 + r * n + x;
    };
    int col_num(int c, int x)
    {
        return n * n * 1 + c * n + x;
    };
    int box_num(int box, int x)
    {
        return n * n * 2 + box * n + x;
    };
    int cell_num(int r, int c)
    {
        return n * n * 3 + r * n + c;
    };

    class node
    {
    public:
        int rw, cl, num;
        node *l, *r, *u, *d;
        void unlink_l_r()
        {
            this->l->r = this->r;
            this->r->l = this->l;
        };
        void unlink_u_d()
        {
            this->u->d = this->d;
            this->d->u = this->u;
        };
        void relink_l_r()
        {
            this->l->r = this;
            this->r->l = this;
        };
        void relink_u_d()
        {
            this->u->d = this;
            this->d->u = this;
        };
    };
    node head;
    vector<node> row_node;
    vector<node> col_node;
    vector<node> ecp_node;
    int ecp_c = 0;
    vector<int> count;
    vector<int> solution;
    vector<vector<int>> input;

    void init()
    {
        root_n = pow(n, 0.5);
        rows = n * n * n;
        cols = n * n * 4;
        nodes = rows * cols;
        head.rw = 0;
        head.cl = 0;
        head.l = head.r = head.u = head.d = &head;
        for (int i = 0; i <= rows; i++)
        {
            node p;
            row_node.push_back(p);
            solution.push_back(0);
        }
        for (int i = 0; i <= cols; i++)
        {
            node p;
            col_node.push_back(p);
            count.push_back(0);
        }

        for (int i = 0; i <= cols * rows; i++)
        {
            node p;
            ecp_node.push_back(p);
        }

        for (int i = 0; i < rows; i++)
        {
            row_node[i].u = head.u;
            head.u = &row_node[i];
            row_node[i].rw = i;
            row_node[i].d = &head;
            row_node[i].l = &row_node[i];
            row_node[i].r = &row_node[i];
            row_node[i].u->d = &row_node[i];
            row_node[i].d->u = &row_node[i];
        }
        for (int i = 0; i < cols; i++)
        {
            col_node[i].l = head.l;
            head.l = &col_node[i];
            col_node[i].r = &head;
            col_node[i].num = 0;
            col_node[i].cl = i;
            col_node[i].u = &col_node[i];
            col_node[i].d = &col_node[i];
            col_node[i].l->r = &col_node[i];
            col_node[i].r->l = &col_node[i];
        }
    };
    void link(int r, int c, int num, int cl_cnt)
    {
        int rw_cnt = r * n * n + c * n + num;
        count[cl_cnt]++;
        node tmp;
        int ecp_place = rw_cnt * cols + cl_cnt;
        ecp_node[ecp_place].rw = rw_cnt;
        ecp_node[ecp_place].cl = cl_cnt;

        ecp_node[ecp_place].u = &col_node[cl_cnt];
        ecp_node[ecp_place].d = col_node[cl_cnt].d;
        col_node[cl_cnt].d->u = &ecp_node[ecp_place];
        col_node[cl_cnt].d = &ecp_node[ecp_place];

        ecp_node[ecp_place].l = &row_node[rw_cnt];
        ecp_node[ecp_place].r = row_node[rw_cnt].r;
        row_node[rw_cnt].r->l = &ecp_node[ecp_place];
        row_node[rw_cnt].r = &ecp_node[ecp_place];
    };
    void make_link(int r, int c, int num)
    {
        int box = r / root_n * root_n + c / root_n;
        link(r, c, num, row_num(r, num));
        link(r, c, num, col_num(c, num));
        link(r, c, num, box_num(box, num));
        link(r, c, num, cell_num(r, c));
    };
    void cover(int cl_cnt)
    {
        //col_node[cl_cnt].unlink_l_r();
        col_node[cl_cnt].l->r = col_node[cl_cnt].r;
        col_node[cl_cnt].r->l = col_node[cl_cnt].l;

        for (node *p = col_node[cl_cnt].d; p != &col_node[cl_cnt]; p = p->d)
        {
            for (node *q = p->r; q != p; q = q->r)
            {
                count[q->cl]--;
                //q->unlink_u_d();
                q->u->d = q->d;
                q->d->u = q->u;
            }
            //p->unlink_l_r();
            p->l->r = p->r;
            p->r->l = p->l;
        }
    };
    void uncover(int cl_cnt)
    {
        for (node *p = col_node[cl_cnt].d; p != &col_node[cl_cnt]; p = p->d)
        {
            //p->relink_l_r();
            p->l->r = p;
            p->r->l = p;
            for (node *q = p->r; q != p; q = q->r)
            {
                //q->relink_u_d();
                q->u->d = q;
                q->d->u = q;
                count[q->cl]++;
            }
        }
        //col_node[cl_cnt].relink_l_r();
        col_node[cl_cnt].l->r = &col_node[cl_cnt];
        col_node[cl_cnt].r->l = &col_node[cl_cnt];
    };

    //Algorithm X
    bool algo_x(int depth)
    {
        if (head.r == &head)
        {
            return true;
        }

        int candidate_col;
        int min = 1 << 10;
        for (node *p = head.r; p != &head; p = p->r)
        {
            if (min > count[p->cl])
            {
                min = count[p->cl];
                candidate_col = p->cl;
                if (min <= 1)
                {
                    break;
                }
            }
        }

        if (min == 0)
        {
            return false;
        }
        cover(candidate_col);
        for (node *p = col_node[candidate_col].d; p != &col_node[candidate_col]; p = p->d)
        {
            solution[depth] = p->rw;

            p->l->r = p;
            for (node *q = p->r; p != q; q = q->r)
            {
                cover(q->cl);
            }
            p->l->r = p->r;

            if (algo_x(depth + 1))
            {
                return true;
            }

            p->r->l = p;
            for (node *q = p->l; p != q; q = q->l)
            {
                uncover(q->cl);
            }
            p->r->l = p->l;
        }
        uncover(candidate_col);
        return false;
    };

    void get_num()
    {
        for (int i = 0; i < n; ++i)
        {
            input.push_back(vector<int>(n));
        }
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                int x;
                cin >> x;
                x--;
                input[i][j] = x;
                if (x < 0)
                {
                    for (int k = 0; k < n; k++)
                    {
                        make_link(i, j, k);
                    }
                }
                else
                {
                    make_link(i, j, x);
                }
            }
        }
        for (int i = 0; i < rows; i++)
        {
            row_node[i].l->r = row_node[i].r;
            row_node[i].r->l = row_node[i].l;
            //row_node[i].relink_l_r();
        }
    };

public:
    void show_ans()
    {
        if (algo_x(0))
        {
            for (int i = 0; i < n * n; i++)
            {
                int r = solution[i] / (n * n);
                int c = solution[i] / n % n;
                input[r][c] = solution[i] % n;
            }
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    cout << input[i][j] + 1 << " ";
                }
                cout << endl;
            }
        }
        else
        {
            cout << "failed..." << endl;
        }
    };

    ecp(int x)
    {
        n = x;
        init();
        get_num();
    }
    ~ecp()
    {
        cout << "destructor called" << endl;
        col_node.clear();
        col_node.shrink_to_fit();

        row_node.clear();
        row_node.shrink_to_fit();

        ecp_node.clear();
        ecp_node.shrink_to_fit();

        count.clear();
        count.shrink_to_fit();

        solution.clear();
        solution.shrink_to_fit();

        for (int i = 0; i < input.size(); i++)
        {
            input[i].clear();
            input[i].shrink_to_fit();
        }
        input.clear();
        input.shrink_to_fit();
    }
};

int main()
{
    ecp solver(16);
    solver.show_ans();
    return 0;
}