#include <bits/stdc++.h>
using namespace std;

struct Point
{
    double x, y;
    int index;
    int rank;
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
};
bool cmpX(const Point A, const Point B)
{
    return A.x < B.x;
}
bool cmpY(const Point A, const Point B)
{
    return A.y < B.y;
}
bool cmpIndex(const Point A, const Point B)
{
    return A.index < B.index;
}
void heapify(vector<Point> &arr, int n, int root)
{
    int largest = root;
    int l = 2 * root + 1;
    int r = 2 * root + 2;
    if (l < n && arr[l].x > arr[largest].x)
        largest = l;
    if (r < n && arr[r].x > arr[largest].x)
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
void heapifyY(vector<Point> &arr, int n, int root)
{
    int largest = root;
    int l = 2 * root + 1;
    int r = 2 * root + 2;
    if (l < n && arr[l].y > arr[largest].y)
        largest = l;
    if (r < n && arr[r].y > arr[largest].y)
        largest = r;
    if (largest != root)
    {
        swap(arr[root], arr[largest]);
        heapifyY(arr, n, largest);
    }
}
void heapSortY(vector<Point> &arr, int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        heapifyY(arr, n, i);
    }
    for (int i = n - 1; i >= 0; i--)
    {
        swap(arr[0], arr[i]);
        heapifyY(arr, i, 0);
    }
}
vector<Point> findRanks(vector<Point> arr)
{
    int n = arr.size();
    if (n <= 1) // end case is sooooo IMPORTANT
    {
        arr[0].rank = 0;
        return arr;
    }
    int mid = n / 2;
    vector<Point> A(arr.begin(), arr.begin() + mid);
    vector<Point> B(arr.begin() + mid, arr.end());
    A = findRanks(A);
    B = findRanks(B);

    sort(A.begin(), A.end(), cmpY);
    sort(B.begin(), B.end(), cmpY);
    // heapSortY(A, (int)A.size());
    // heapSortY(B, (int)B.size());
    for (int i = 0; i < B.size(); i++)
    {
        int cnt = 0;
        for (int j = 0; j < A.size(); j++)
        {
            if (A[j].y < B[i].y && A[j].x < B[j].x)
                cnt++;
            else
                break;
        }
        B[i].rank += cnt;
    }
    vector<Point> new_arr(A.size() + B.size());
    copy(A.begin(), A.end(), new_arr.begin());
    copy(B.begin(), B.end(), new_arr.begin() + A.size());
    return new_arr;
}

int main()
{
    int n = 0;
    ifstream inStream;
    inStream.open("test5.txt");
    double a, b;
    vector<Point> points;
    while (inStream >> a >> b)
    {
        Point tmp;
        tmp.x = a;
        tmp.y = b;
        tmp.index = n;
        tmp.rank = 0;
        n++;
        points.push_back(tmp);
    }
    // heapSort(points, n); // unstable sort may cause false so if we use the quicksort(in algorithm library) would have different result
    sort(points.begin(), points.end(), cmpX);
    points = findRanks(points);
    sort(points.begin(), points.end(), cmpIndex);
    int maxRank = -1;
    int minRank = n + 1;
    double meanRank = 0.0;
    for (int i = 0; i < n; ++i)
    {
        cout << "points " << i + 1 << ": (" << points[i].x << "," << points[i].y << "):" << points[i].rank << '\n';
        maxRank = max(maxRank, points[i].rank);
        minRank = min(minRank, points[i].rank);
        meanRank += (double)points[i].rank;
    }
    meanRank /= (double)n;
    cout << "Number of points: " << n << endl;
    cout << "The max rank: " << maxRank << endl;
    cout << "The min rank: " << minRank << endl;
    cout << "The mean rank: " << setprecision(2) << fixed << meanRank << endl;
    inStream.close();
}