#include <bits/stdc++.h>
using namespace std;

struct Cycle
{
    vector<int> order;
    int weight;
    Cycle()
    {
        weight = 0;
    }
    bool operator<(const Cycle other) const
    {
        return weight < other.weight;
    }
};

class Solve
{
private:
    int nodeNum;
    int edgeNum;
    int target;
    bool can_be_added(vector<Cycle> &currBasis, Cycle candidate)
    {
        if (currBasis.empty())
        {
            return true;
        }
        vector<int> candidateCycle(this->nodeNum * this->nodeNum, 0);
        int n = candidate.order.size();
        for (int i = 0; i < n; i++)
        {
            int from = candidate.order[i];
            int to = candidate.order[(i + 1) % n];
            candidateCycle[from * this->nodeNum + to] = 1;
            candidateCycle[to * this->nodeNum + from] = 1;
        }
        // cout << candidateCycle.size() << endl;
        //  將現有循環轉換為矩陣
        vector<vector<int>> basisMatrix;
        for (const auto &cycle : currBasis)
        {
            vector<int> baseCycle(this->nodeNum * this->nodeNum, 0);
            int m = cycle.order.size();
            for (int i = 0; i < m; i++)
            {
                int from = cycle.order[i];
                int to = cycle.order[(i + 1) % m];
                baseCycle[from * this->nodeNum + to] = 1;
                baseCycle[to * this->nodeNum + from] = 1;
            }
            basisMatrix.push_back(baseCycle);
        }
        // cout << "Candidite";
        // for (int i = 0; i < candidateCycle.size(); i++)
        // {
        //     cout << ", " << candidateCycle[i];
        // }
        // cout << endl;
        // cout << "Basis";
        // for (const auto &basis : basisMatrix)
        // {
        //     for (int i = 0; i < basis.size(); i++)
        //     {
        //         cout << ", " << basis[i];
        //     }
        //     cout << endl;
        // }
        // 用高斯消去法判斷線性無關性
        vector<int> temp = candidateCycle;
        for (const auto &basis : basisMatrix)
        {
            // 對每個基本循環進行XOR
            for (int i = 0; i < temp.size(); i++)
            {
                temp[i] ^= basis[i];
            }

            bool isZero = true;
            for (int val : temp)
            {
                if (val != 0)
                {
                    isZero = false;
                    break;
                }
            }
            if (isZero)
            {
                cout << "drop\n";
                return false;
            }
        }

        return true;
    }

public:
    vector<Cycle> solve(vector<Cycle> allCycle, int nodeNum, int edgeNum)
    {
        this->nodeNum = nodeNum;
        this->edgeNum = edgeNum;
        this->target = (edgeNum - nodeNum + 1);

        vector<Cycle> basis;
        stable_sort(allCycle.begin(), allCycle.end());

        for (const Cycle &cycle : allCycle)
        {
            //
            // target = 3;
            // test
            if (basis.size() == target)
            {
                break;
            }
            if (can_be_added(basis, cycle))
            {
                basis.push_back(cycle);
            }
        }

        return basis;
    }
};

int main()
{
    int i, j;
    int nodenum, edgenum, cost, begin, end;

    ifstream inStream;
    inStream.open("cost239");
    inStream >> nodenum >> edgenum;

    int A[nodenum][nodenum]; // 儲存連線的點
    for (i = 0; i < nodenum; i++)
        for (j = 0; j < nodenum; j++)
            A[i][j] = 0;
    while (inStream >> begin >> end >> cost)
    {
        A[begin][end] = cost;
        A[end][begin] = cost;
    }
    inStream.close();
    int r, f;
    int k, c, pre, no; // 第no格
    int b = 0;         // 有b個temp(多出來的排列組合)
    int s = 0, e = nodenum, cycle = 0;
    int temp[nodenum];
    int order[20000][nodenum]; // 預設值-1
    int check_re[20000];
    int check_cycle[nodenum];
    for (i = 0; i < 20000; i++)
        for (j = 0; j < nodenum; j++)
            order[i][j] = -1;
    for (i = 0; i < nodenum; i++)
        order[i][0] = i;
    int adde;
    int t; // 比大小時的temp
    int smallest, compare;
    int m, n;
    vector<Cycle> allCycle;
    for (no = 1; no < nodenum; no++) // 設定no
    {

        adde = 0;
        s = 0;
        for (k = 0; k < e; k++) // 做e次加長連線(e預設為nodenum)
        {
            s = s + b;
            b = 0;
            pre = order[s][no - 1];                       // pre是前一個頂點
            for ((i = order[s][0] + 1); i < nodenum; i++) // i=pre+1修改修改修改修改修改修改修改修改修改修改修改
            {
                if (A[pre][i] == 1)
                {
                    for (j = 1; j < (no - 1); j++) // for迴圈 檢查有沒有重複的頂點
                    {
                        if (order[s][j] == i)
                        {
                            j = -1;
                            break;
                        }
                    }
                    if (j != -1)
                        temp[b++] = i; // b計算多出來的排列組合
                }
            }
            c = 0;

            if (b > 0)
            {
                adde = adde + b - 1;
                for (i = e + adde; i > s; i--) // 往後移 (更改:e->e+adde)
                {
                    for (j = 0; j < no; j++)
                        order[i + b - 1][j] = order[i][j];
                }
                for (i = s; i < (s + b); i++) // 補上&新連線
                {
                    order[i][no] = temp[c++];
                    for (j = 0; j < no; j++)
                        order[i][j] = order[s][j];

                    // 檢查cycle
                    if (no > 1 && A[order[i][no]][order[i][0]] == 1)
                    {

                        for (m = 0; m <= no; m++)
                            check_cycle[m] = order[i][m];

                        compare = 0; // 檢查是否為反序

                        for (m = 1; m <= no; m++)
                            compare = compare * 10 + check_cycle[m];
                        compare = compare * 10 + check_cycle[0];

                        check_re[i] = 0;
                        for (m = no; m >= 0; m--)
                            check_re[i] = check_re[i] * 10 + check_cycle[m];

                        for (m = 0; m < i; m++)
                        {
                            if (check_re[m] == compare)
                            {
                                m = -1;
                                break;
                            }
                        }
                        if (m != -1)
                        {
                            vector<int> nodes;
                            int weight = 0;
                            for (j = 0; j <= no; j++)
                            {
                                nodes.push_back(order[i][j]);
                                if (j > 0)
                                {
                                    weight += A[order[i][j - 1]][order[i][j]];
                                }
                            }
                            weight += A[order[i][no]][order[i][0]];
                            Cycle tmp;
                            tmp.order = nodes;
                            tmp.weight = weight;
                            allCycle.push_back(tmp);
                            cycle++;
                        }
                    }
                }
            }
            else // b==0
            {
                for (i = s; i < e + adde; i++) // 往前移1格
                {
                    for (j = 0; j <= no; j++)
                        order[i][j] = order[i + 1][j];
                }
                adde--;
            }
        }
        e = e + adde;
    }
    // cout << allCycle.size();
    Solve solver;
    vector<Cycle> minCycleBasis = solver.solve(allCycle, nodenum, edgenum);

    // Output the minimum cycle basis
    int totalCost = 0;
    for (const auto &cycle : minCycleBasis)
    {
        cout << "Cycle Weight: " << cycle.weight << ", Nodes: ";
        totalCost += cycle.weight;
        for (int node : cycle.order)
            cout << node << " ";
        cout << endl;
    }
    cout << "All Cycle Number: " << allCycle.size() << endl;
    cout << "Node Number:" << nodenum << ", Edge Number:" << edgenum << endl;
    cout << "Minimum Cycle Basis Cost: " << totalCost << endl;
    cout << "Minimum Cycle Basis Size: " << minCycleBasis.size() << endl;
    return 0;
}