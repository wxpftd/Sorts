#include <ctime>
#include <iostream>
#include <cstdlib>

using namespace std;

inline void Swap(int &a, int &b)
{
	int c = a;
	a = b;
	b = c;
}

////////////////////////////////////////////////////////////////////////////////
void QuickSort(int num[], int l, int r)
{
	if (l < r)
	{
		int x = num[r];
		int i = l, j = r;
		while (i < j)
		{
			while (i < j && num[i] < x)
				i++;
			if (i < j)
				num[j--] = num[i];
			while (i < j && num[j] > x)
				j--;
			if (i < j)
				num[i++] = num[j];
		}
		num[j] = x;
		QuickSort(num, l, j - 1);
		QuickSort(num, j + 1, r);
	}
}
////////////////////////////////////////////////////////////////////////////////

void BubbleSort(int num[], int length)
{
	int sortPos = length;
	int k = sortPos;
	while (sortPos > 0)
	{
		k =	sortPos;
		sortPos = 0;
		for (int i = 1; i < k; i++)	
		{
			if (num[i] < num[i-1])	
			{
				sortPos = i;
				Swap(num[i], num[i-1]);
			}
		}
	}
}
////////////////////////////////////////////////////////////////////////////////

void InsertSort(int num[], int length)
{
	for (int i = 1; i < length; i++)	
	{
		for (int j = i; j > 0 && num[j] < num[j-1]; j--)	
			Swap(num[j], num[j-1]);
	}
}
////////////////////////////////////////////////////////////////////////////////

void ShellSort(int num[], int length)
{
	for (int gap = length/2; gap > 0; gap/=2)	
	{
		for (int i = gap; i < length; i++)
		{
			for (int j = i; j >= gap && num[j] < num[j-gap]; j-=gap)
				Swap(num[j], num[j-gap]);
		}
	}
}
////////////////////////////////////////////////////////////////////////////////

void SelectSort(int num[], int length)
{
	int minPos;
	for (int i = 0; i < length - 1; i++)
	{
		minPos = i;
		for (int j = i; j < length; j++)
		{
			if (num[j] < num[minPos])	
			{
				minPos = j;
			}
		}
		Swap(num[i], num[minPos]);
	}
}
////////////////////////////////////////////////////////////////////////////////
void mergeArray(int num[], int head, int mid, int tail, int temp[])
{
	int i = head, j = mid + 1;
	int m = mid, n = tail;
	int k = 0;
	while (i <= m && j <= n)
	{
		if (num[i] < num[j])	
			temp[k++] = num[i++];
		else
			temp[k++] = num[j++];
	}
	while (i <= m)
		temp[k++] = num[i++];
	while (j <= n)
		temp[k++] = num[j++];
	for (i = 0; i < k; i++)
		num[i + head] = temp[i];

}

void mergeSort(int num[], int head, int tail, int temp[])
{
	if (head < tail)	
	{
		int mid = (head + tail) / 2;
		mergeSort(num, head, mid, temp);	
		mergeSort(num, mid+1, tail, temp);
		mergeArray(num, head, mid, tail, temp);
	}
}

void MergeSort(int num[], int length)
{
	int *temp = new int[100000];
	if (temp == nullptr)
		return;
	mergeSort(num, 0, length-1, temp);
	delete[] temp; 
}
////////////////////////////////////////////////////////////////////////////////

class MinHeap
{
public:
	MinHeap();
	MinHeap(int input[], int length);
	~MinHeap();
	void push(int);
	int pop();

private:
	int *num;
	int lastPos;
	void minHeapFixDown(int fixPos);
	void minHeapFixUp(int fixPos);
	void makeMinHeap();

};

MinHeap::MinHeap():lastPos(-1)
{
	num = new int[100000];
}

MinHeap::MinHeap(int input[], int length):lastPos(length - 1)
{
	num = new int[100000];
	for (int i = 0; i < length; i++)
		num[i] = input[i];
	makeMinHeap();
}

MinHeap::~MinHeap()
{
	delete[] num;
}

void MinHeap::push(int nNum)
{	
	num[++lastPos] = nNum;
	minHeapFixUp(lastPos);
}

int MinHeap::pop()
{
	int minNum = num[0];
	num[0] = num[lastPos--];
	minHeapFixDown(0);
	return minNum;
}

void MinHeap::makeMinHeap()
{
	for (int i = (lastPos-1)/2; i >= 0; i--)	
	{
		minHeapFixDown(i);	
	}
}

void MinHeap::minHeapFixUp(int fixPos)
{
	int j = fixPos;
	for (int i = (j-1)/2; i >= 0 && j != 0 && num[i] > num[j]; j = i, i=(i-1)/2)
		Swap(num[i], num[j]);
}

void MinHeap::minHeapFixDown(int fixPos)
{
	int i = fixPos;
	int j = 2 * i + 1, temp = num[i];
	while (j <= lastPos)
	{
		if (j+1 <= lastPos && num[j+1] < num[j])	
			j++;
		if (num[j] >= temp)
			break;
		num[i] = num[j];
		i = j;
		j = i * 2 + 1;
	}
	num[i] = temp;
}


////////////////////////////////////////////////////////////////////////////////
void output(int num[], int length)
{
	for (int i=0; i<length; i++)
	{
		cout << num[i] << " ";	
		if (i%10==0 && i!=0)
		{
			cout << endl;	
		}
	}
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
    MergeSort(num, length);
    //MinHeap *minHeap = new MinHeap(num, length);
	//for (int i=0; i<20; i++)
	//{
	//	minHeap->push(rand()/100000000);
	//	length++;	
	//}
    for (int i=0; i<length; i++)
    {
		 result[i] = num[i]; 
    }
	
    //delete minHeap;
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
