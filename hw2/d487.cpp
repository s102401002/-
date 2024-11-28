#include <bits/stdc++.h>
using namespace std;

int ranks[10000];
struct Point
{
    int x, y, index;

    bool operator<(const Point &other) const
    {
        if (this->x != other.x)
            return this->x < other.x;
        return this->y > other.y;
    }
    bool operator>(const Point &other) const
    {
        return this->x > other.x || (this->x == other.x && this->y > other.y);
    }
} buffer[10000];
vector<Point> points;
void heapify(vector<Point> &arr, int n, int root)
{
    int largest = root;
    int l = 2 * root + 1;
    int r = 2 * root + 2;
    if (l < n && arr[l] > arr[largest])
        largest = l;
    if (r < n && arr[r] > arr[largest])
        largest = r;
    if (largest != root)
    {
        swap(arr[root], arr[largest]);
        heapify(arr, n, largest);
    }
}
void heapSort(vector<Point> &arr, int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        heapify(arr, n, i);
    }
    for (int i = n - 1; i >= 0; i--)
    {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

void Rank2D(int lower, int upper)
{
    if (upper - lower <= 1)
        return;
    int middle = (lower + upper) >> 1, medianX = points[middle].x;
    Rank2D(lower, middle);
    Rank2D(middle, upper);
    int cnt = 0, i = lower, j = middle, k = lower;
    while (i < middle || j < upper)
    {
        if (i == middle)
        {
            buffer[k] = points[j];
            ranks[buffer[k].index] += cnt;
            ++j;
            ++k;
        }
        else if (j == upper)
        {
            buffer[k] = points[i];
            ++i;
            ++k;
        }
        else if (points[i].y < points[j].y)
        {
            buffer[k] = points[i];
            ++cnt;
            ++i;
            ++k;
        }
        else
        {
            buffer[k] = points[j];
            ranks[buffer[k].index] += cnt;
            ++j;
            ++k;
        }
    }
    for (i = lower; i < upper; ++i)
        points[i] = buffer[i];
}

int main()
{
    int n;
    while (cin >> n)
    {
        points = vector<Point>(n);
        memset(ranks, 0, sizeof(ranks));
        for (int i = 0; i < n; ++i)
        {
            cin >> points[i].x >> points[i].y;
            points[i].index = i;
        }
        heapSort(points, n);
        // for (int i = 0; i < n; ++i)
        // {
        //     cout << points[i].x << " " << points[i].y << endl;
        // }
        Rank2D(0, n);
        for (int i = 0; i < n; ++i)
            cout << ranks[i] << '\n';
    }
}