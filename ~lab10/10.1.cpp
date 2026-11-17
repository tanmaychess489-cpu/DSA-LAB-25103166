#include <iostream>
#include <vector>
using namespace std;

void helper(vector<int>& a, int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if(left < n && a[left] > a[largest])
        largest = left;

    if(right < n && a[right] > a[largest])
        largest = right;

    if(largest != i)
    {
        swap(a[i], a[largest]);
        helper(a, n, largest);
    }
}

void heapSort(vector<int>& a, int n)
{
    for(int i = n / 2 - 1; i >= 0; i--)
        helper(a, n, i);

    for(int i = n - 1; i > 0; i--)
    {
        swap(a[0], a[i]);
        helper(a, i, 0);
    }
}

int main()
{
    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> a(n);

    cout << "Enter elements: ";
    for(int i = 0; i < n; i++)
        cin >> a[i];

    heapSort(a, n);

    cout << "Sorted elements: ";
    for(int i = 0; i < n; i++)
        cout << a[i] << " ";

    return 0;
}