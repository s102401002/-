#include <bits/stdc++.h>
using namespace std;

void quickSort(vector<double> &v, int l, int r) //(l,r)
{
    if (l >= r)
        return;
    int pivot = l;
    int i = l, j = r + 1;
    while (i < j)
    {
        while (v[++i] < v[pivot])
            ;
        while (v[--j] > v[pivot])
            ;
        if (i >= j)
            break;
        double tmp = v[i];
        v[i] = v[j];
        v[j] = tmp;
    }
    double tmp = v[j];
    v[j] = v[l];
    v[l] = tmp;
    quickSort(v, l, j - 1);
    quickSort(v, j + 1, r);
}

void insertionSort(vector<double> &v)
{
    for (int i = 1; i < v.size(); i++)
    {
        double insert = v[i];
        int j = i - 1;
        while (j >= 0 && v[j] > insert)
        {
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = insert;
    }
}

int main()
{
    ifstream inStream;
    inStream.open("test1.txt");
    double tmp;
    vector<double> v;
    while (inStream >> tmp)
    {
        v.push_back(tmp);
    }
    int mode;
    do
    {
        cout << "Entering mode:(1)quick sort (2)insertion sort (3)exit\n";
        cin >> mode;
        if (mode == 1)
        {
            vector<double> v1 = v;
            quickSort(v1, 0, v1.size() - 1);
            for (auto num : v1)
            {
                cout << num << "\t";
            }
            cout << endl;
            cout << "Size of array: " << v1.size() << endl;
            cout << "The max element: " << v1[v1.size() - 1] << endl;
            cout << "The min element: " << v1[0] << endl;
        }
        else if (mode == 2)
        {
            vector<double> v2 = v;
            insertionSort(v2);
            for (auto num : v2)
            {
                cout << num << "\t";
            }
            cout << endl;
            cout << "Size of array: " << v2.size() << endl;
            cout << "The max element: " << v2[v2.size() - 1] << endl;
            cout << "The min element: " << v2[0] << endl;
        }
        else if (mode == 3)
        {
            cout << "Close\n";
        }
        else
        {
            cout << "Wrong input!\n";
        }
    } while (mode != 3);

    inStream.close();
    return 0;
}