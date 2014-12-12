#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

inline void Swap(int &a, int &b)
{
    int c = a;
    a = b;
    b = c;
}

void QuickSort(int num[], int l, int r)
{
    if (l < r)
    {
        int i = l, j = r, x = num[r];
        while (i<j)
        {
            while (i<j && num[i] <= x)
                i++;
            if (i<j)
                num[j--] = num[i];
            while (i<j && num[j] > x)
                j--;
            if (i<j)
                num[i++] = num[j];
        }
        num[j] = x;
        QuickSort(num, l, j-1);
        QuickSort(num, j+1, r);
    }
}
////////////////////////////////////////////////////////////////////////
void BubbleSort(int num[], int n)
{
    int sortPos = n;
    int j, k;
    while (sortPos > 0)
    {
        k = sortPos;
        sortPos = 0;
        for (j=1; j<k; j++)
        {
            if (num[j-1] > num[j])
            {
                Swap(num[j-1], num[j]);
                sortPos = j;
            }
        }
    }
}
////////////////////////////////////////////////////////////////////////////
void InsertSort(int num[], int n)
{
    int i,j;
    for ( i=0; i<n-1; i++)
    {
        for (j=i; j>=0 && num[j] > num[j+1]; j--)
        {
            Swap(num[j], num[j+1]);
        }
    }
}
//////////////////////////////////////////////////////////////////////////
void ShellSort(int num[], int n)
{
    int gap, i, j;
    for (gap = n/2; gap > 0; gap/=2)
    {
        for (i = gap; i<n; i++)
            for (j = i; j>=gap && num[j]<num[j-gap]; j-=gap)
            {
                Swap(num[j], num[j-gap]);
            }
    }
}
///////////////////////////////////////////////////////////////////////////
void SelectSort(int num[], int n)
{
    int smallPos;
    for (int i=0; i<n-1; i++)
    {
        smallPos = i;
        for (int j=i+1; j<n; j++)
            if (num[smallPos] > num[j])
            {
                smallPos = j;
            }
        Swap(num[i], num[smallPos]);
    }

}
/////////////////////////////////////////////////////////////////////////

void mergearray(int num[], int head, int mid, int tail, int tempArea[])
{
    int i=head, j=mid+1;
    int m=mid, n=tail;
    int k=0;
    while (i<=m && j<=n)
    {
        if (num[i] > num[j])
        {
            tempArea[k++] = num[j++];
        }
        else
        {
            tempArea[k++] = num[i++];
        }
    }
    while (i<=m)
    {
        tempArea[k++] = num[i++];
    }
    while (j<=n)
    {
        tempArea[k++] = num[j++];
    }
    for (i=0; i<k; i++)
        num[head+i] = tempArea[i];
}

bool mergesort(int num[], int head, int tail, int tempArea[])
{
    if (head < tail)
    {
        int mid = (head + tail) / 2;
        mergesort(num, head, mid, tempArea);
        mergesort(num, mid+1, tail, tempArea);
        mergearray(num, head, mid, tail, tempArea);
    }
    return true;
}


void MergeSort(int num[], int n)
{
    int *tempArea = new int[n];
    if (tempArea == nullptr)
        return;
    mergesort(num, 0, n-1, tempArea);
    delete[] tempArea;
}
//////////////////////////////////////////////////////////////////////////

class MinHeap
{
public:
    MinHeap();
    MinHeap(int input[], int n);
    ~MinHeap();
    void push(int nNum);
    int pop();
    void MinHeapSort();
private:
    int *num;
    int lastPos;
    void MinHeapDelete();
    void MakeMinHeap();
    void MinHeapFixUp(int fixPos);
    void MinHeapFixDown(int fixPos);
};

MinHeap::MinHeap():lastPos(-1)
{
    num = new int[100000];
}

MinHeap::MinHeap(int input[], int length):lastPos(length-1)
{
    num = new int[100000];
    for (int i=0; i<length; i++)
    {
        num[i] = input[i];
    }
    MakeMinHeap();
}

MinHeap::~MinHeap()
{
    delete[] num;
}

void MinHeap::MinHeapFixUp(int fixPos)
{
    if (0 >= lastPos)
        return;
    int j = fixPos;
    for (int i=(j-1)/2; i>=0 && j!=0 && num[i]>num[j]; j=i, i=(i-1)/2)
    {
        Swap(num[i], num[j]);
    }
}

void MinHeap::MinHeapFixDown(int fixPos)
{
    if (0 >= lastPos)
        return;
    int i = fixPos;
    int temp = num[i], j = i*2+1;

    while (j<=lastPos)
    {
        if (j+1<=lastPos && num[j+1] < num[j])
        {
            j++;
        }
        if (num[j] >= temp)
            break;
        num[i] = num[j];
        i = j;
        j = i * 2 + 1;
    }
    num[i] = temp;

}

void MinHeap::MakeMinHeap()
{
    for (int i=(lastPos-1)/2; i>=0; i--)
    {
        MinHeapFixDown(i);
    }
}

void MinHeap::push(int nNum)
{
    lastPos++;
    num[lastPos] = nNum;
    MinHeapFixUp(lastPos);
}

int MinHeap::pop()
{
    int minNum = num[0];
    MinHeapDelete();
    return minNum;
}

void MinHeap::MinHeapDelete()
{
    num[0] = num[lastPos];
    lastPos--;
    MinHeapFixDown(0);
}

void MinHeap::MinHeapSort()
{
    for (int i=lastPos; i>0; i--)
    {
        Swap(num[i], num[0]);
        MinHeapFixDown(0);
    }
}

///////////////////////////////////////////////////////////////////////////
void output(int num[], int n)
{
    for (int i=0; i<n; i++)
    {
        cout << num[i] << " ";
        if (i % 10 == 0 && i != 0)
            cout << endl;
    }
    cout << endl;
}

int main()
{
    srand(time(nullptr));
    int length;
    cin >> length;
    int num[100000] {};
    int result[100000] {};
    for (int i=0; i<length; i++)
    {
        num[i] = rand();
    }

    //BubbleSort(num, length);
    //InsertSort(num, length);
    //ShellSort(num, length);
    //SelectSort(num, length);
    //MergeSort(num, length);
    MinHeap *minHeap = new MinHeap(num, length);
    for (int i=0; i<length; i++)
    {
        result[i] = minHeap->pop();
    }
    delete minHeap;
    //output(result, length);
    QuickSort(num, 0, length-1);

    for (int i=0; i<length; i++)
    {
        if (result[i] != num[i])
        {
            cout << "Something Wrong!!!" << endl;
            exit(0);
        }
    }
    cout << "You Make It!" << endl;

    return 0;
}

