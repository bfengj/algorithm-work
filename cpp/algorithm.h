#include <unistd.h>
#include <queue>
#include <vector>
#include <iostream>
#include<stack>
#include<algorithm>
#include <stdio.h>

#ifndef ALGORITHM_ALGORITHM_H
#define ALGORITHM_ALGORITHM_H
#endif //ALGORITHM_ALGORITHM_H
using namespace std;
typedef struct Book {
    char bookId[8];    //书号
    char bookName[10];  //书名
    char author[10];    //作者
    unsigned int monthTicket;  //月票数量
XPACK(O(bookId, bookName, author, monthTicket));
} Book, *PBook;


//重载运算符
bool operator<(Book book1, Book book2) {
    return book1.monthTicket < book2.monthTicket;
}

//重载运算符
bool operator>(Book book1, Book book2) {
    return book1.monthTicket > book2.monthTicket;
}

//重载运算符
bool operator<=(Book book1, Book book2) {
    return book1.monthTicket <= book2.monthTicket;
}

//重载运算符
bool operator>=(Book book1, Book book2) {
    return book1.monthTicket >= book2.monthTicket;
}

//重载运算符
bool operator==(Book book1, Book book2) {
    return book1.monthTicket >= book2.monthTicket;
}

int operator+(Book book1, Book book2) {
    return book1.monthTicket + book2.monthTicket;
}
int cnt =0;
vector<Book> findMedian(vector<Book> &books) {
    //大顶堆
    priority_queue<Book, vector<Book>, less<Book> > largeTopHeap;
    //小顶堆
    priority_queue<Book, vector<Book>, greater<Book> > smallTopHeap;
    //largeTopHeap存储小于等于中位数的
    //smallTopHeap存储大于中位数的
    //要么二者数量相同，要么largeTopHeap比smallTopHeap的数量多一个
    //遍历books
    int n = books.size();
    for (int i = 0; i < n; ++i) {
        Book book = books[i];
        if (largeTopHeap.size() > smallTopHeap.size()) {
            largeTopHeap.push(book);
            smallTopHeap.push(largeTopHeap.top());
            largeTopHeap.pop();
        } else {
            smallTopHeap.push(book);
            largeTopHeap.push(smallTopHeap.top());
            smallTopHeap.pop();
        }
    }
    vector<Book> res;
    res.push_back(largeTopHeap.top());
    //下中位数
    return res;
}

int Partion(vector<Book> &a, int l, int r) {
    Book pivot = a[l];
    while (l < r) {
        while (a[r] <= pivot && r > l) r--;
        a[l] = a[r];
        while (a[l] >= pivot && l < r) l++;
        a[r] = a[l];
    }
    //最后一定l==r
    a[l] = pivot;
    return l;
}

//快速排序
void QuickSort(vector<Book> &a, int l, int r) {
    if (l < r) {
        int k = Partion(a, l, r);
        QuickSort(a, l, k - 1);
        QuickSort(a, k + 1, r);
    }
}

int Partion(vector<Book> &a, int l, int r, int pos) {
    Book pivot = a[pos];
    swap(a[pos], a[l]);
    while (l < r) {
        while (a[r] <= pivot && r > l) {
            r--;
            cnt++;
        }
        a[l] = a[r];
        while (a[l] >= pivot && l < r) {
            l++;
            cnt++;
        }
        a[r] = a[l];
    }
    //最后一定l==r
    a[l] = pivot;
    return l;
}

//从大到小排序
//插入排序
void InsertSort(vector<Book> &a, int l, int r) {
    for (int i = l + 1; i <= r && i < a.size(); ++i) {
        Book temp = a[i];
        int j;
        for (j = i - 1; j >= l; --j) {
            if (a[j] <= temp) {
                a[j + 1] = a[j];
                continue;
            }
            break;
        }
        a[j + 1] = temp;
    }
}

Book findMiddle(vector<Book> a, int l, int r) {
    int n = l;
    for (int i = l; i <= r; i += 5) {
        InsertSort(a, i, i + 4);
        int right = ((i + 4) >= a.size() ? a.size() - 1 : i + 4);
        right = (right >= r ? r : right);
        swap(a[n++], a[(i + right) / 2]);
    }
    if (n - l > 1) {
        return findMiddle(a, l, n - 1);
    } else {
        return a[l];
    }
}

//求第k大，k从0开始
void BFPTR(vector<Book> &a, int l, int r, int k) {
    Book mid = findMiddle(a, l, r);
    int pos;
    for (int i = 0; i < a.size(); ++i) {
        cnt++;
        if (mid == a[i]) {
            pos = i;
            break;
        }
    }
    int kk = Partion(a, l, r, pos);
    if (kk == k - 1)return;
    else if (kk > k - 1) {
        BFPTR(a, l, kk - 1, k);
    } else {
        BFPTR(a, kk + 1, r, k);
    }
}


vector<Book> topKPercent(vector<Book> &a,int k){
    int n = a.size();
    k = n*k/100;
    BFPTR(a,0,n-1,k);
    QuickSort(a,0,k-1);
    vector<Book> res;
    for (int i = 0; i < k; ++i) {
        res.push_back(a[i]);
    }
    return res;
}








vector<Book> removeAbnormalData(vector<Book> &a, int m) {
    int n = a.size();
    int leftM = n * m / 100;
    int rightM = n * (100 - m) / 100;
    BFPTR(a, 0, n - 1, leftM);
    BFPTR(a, leftM + 1, n - 1, rightM);
    vector<Book> res;
    for (int i = leftM + 1; i < rightM; ++i) {
        res.push_back(a[i]);
    }
    return res;
}


//希尔排序
vector<Book> shellSort(vector<Book>& v){//type为1表示降序从大到小，为0表示升序
    int n = v.size();
    for(int gap = n/2; gap >=1; gap /= 2){
        for(int i = 0; i < gap; i++){
            for(int j = i+gap; j < n; j+=gap){
                Book temp = v[j];//记录待插入结点
                int k = j - gap;
                cnt++;
                if(temp.monthTicket > v[k].monthTicket){//结点大于降序序列的末尾，需要调整；如果小于则不需要调整
                    while(k >= 0 && temp.monthTicket > v[k].monthTicket){//循环找到插入位置，k不能越界
                        v[k + gap] = v[k];
                        k -= gap;
                        cnt++;
                    }
                    v[k + gap] = temp;
                }
            }
        }
    }
    return v;
}

//堆排序
//数组形式的堆
vector<Book> heapSort(vector<Book> v){
    vector<Book> ret;
    //n-1为尾元素，(index - 1)/2为index的父节点，父节点*2为左孩子，*2+1为右孩子
    //从最后一个内结点（尾结点的父节点开始向上调整）
    for(int n =v.size(); n > 1; n--){//最后只剩一个元素停止，将其直接加入ret返回
        for(int i = (n-1-1)/2; i>=0; i--){
            int maxintwo;
            if(2*i+2 >= n)//右子节点不能越界
                maxintwo = 2*i+1;
            else
                maxintwo = v[2*i+1].monthTicket>v[2*i+2].monthTicket? 2*i+1 : 2*i+2;
            if(v[maxintwo].monthTicket > v[i].monthTicket){
                swap(v[i], v[maxintwo]);
            }
        }
    ret.push_back(v[0]);
    v[0] = v[n-1];
    v.pop_back();
    }
    ret.push_back(v[0]);
    return ret;
}

//快速排序
int oneSort(vector<Book> &v, int low, int high){
    int pivot = low;//pivot等于区间最左点low
    while(low < high){
        while(low < high && v[high].monthTicket <= v[pivot].monthTicket){
            cnt++;
            high--;
        }
        while (low < high && v[low].monthTicket >= v[pivot].monthTicket){//枢纽选的第一个数，low从0开始，包含=
            cnt++;
            low++;
        }
        if(low < high)
            swap(v[high], v[low]);
    }
    swap(v[low], v[pivot]);//low是枢纽确定后的位置
    return low;
}

vector<Book> quickSort(vector<Book> &v){
    stack<pair<int, int> > s;
    s.push({0, v.size()-1});
    while(!s.empty()){
        int low = s.top().first, high = s.top().second;
        s.pop();
        int mid = oneSort(v, low, high);
        if(mid-1 > low)
            s.push({low, mid-1});
        if(mid+1 < high)
            s.push({mid+1, high});
    }
    return v;
}

//基数排序
//从个位到十位等等排序，每次排序新结果是新的子串。数组0到9
vector<Book> baseSort(vector<Book> &v){
    vector<vector<Book>> ctnr(10);
    int n, maxindex, maxnum = 0;//n记录最大数的位数
    for(int i =0; i < v.size(); i++){
        if(v[i].monthTicket > maxnum){
            maxindex = i;
            maxnum = v[i].monthTicket;
        }
    }
    for(int f = 10, temp = v[maxindex].monthTicket; temp > 0; n++){//确定最大数的位数
        temp /= f;
    }

    for(int f = 1, times = 0; times < n; f *= 10, times++){
        for(int i =0; i < v.size(); i++){
            ctnr[v[i].monthTicket /f %10].push_back(v[i]);
        }
        int cnt = 0;
        for(auto i = ctnr.begin(); i != ctnr.end(); i++){
            for(auto j = i->begin(); j != i->end(); ){
                v[cnt++] = *j;
                j = i->erase(j);
            }
        }
    }
    reverse(v.begin(), v.end());
    return v;
}

//归并排序
void merge(vector<Book> &v, int low, int middle, int high){
    int i = low, j = middle+1, k =0;
    vector<Book> temp;
    while (i <= middle && j <= high){
		if (v[i].monthTicket < v[j].monthTicket)
			temp.push_back(v[i++]);
		else
			temp.push_back(v[j++]);
	}
	while (i <= middle)
		temp.push_back(v[i++]);
	while (j <= high)
		temp.push_back(v[j++]);
	// 将排好序的存回arr中low到high该区间内 
	for (i = low, k = 0; i <= high; i++, k++)
		v[i] = temp[k];
 
}

vector<Book> mergeSort(vector<Book> &v)
{
    int n = v.size();
    int size = 1, low, middle, high;
    while (size <= n){
        low = 0;//low每轮循环初值为0
        while (low + size <= n){
            middle = low + size - 1;
            high = middle + size;
            if(high >= n)//注意单独元素越界问题！！！
                high = n-1;
            merge(v,low,middle,high);
            low = high + 1;
        }
        size *= 2;
    }
    reverse(v.begin(), v.end());
    return v;
}

int search1(vector<Book>& nums, int target) {
    int start = 0;
    int end = nums.size();
    while (start<end) {
        int mid = start + (end-start)/2;
        if(nums[mid].monthTicket <= target){
            end = mid;
        }else{
            start = mid+1;
        }
    }
    return end;
}
int search2(vector<Book>& nums, int target) {
    int start = 0;
    int end = nums.size()-1;
    while (start<end) {
        int mid = end - (end-start)/2;
        if(nums[mid].monthTicket < target){
            end = mid-1;
        }else{
            start = mid;
        }
    }
    return end;
}

void findCountProportion(vector<Book> &a,int value1,int value2){
    int n = a.size();
    if(value2>value1) swap(value1,value2);
    QuickSort(a,0,n-1);
    int left = search1(a,value1);
    int right = search2(a,value2);
    //printf("%d %d",left,right);
    double res = ((double)(right-left+1))/n;
    printf("%.8f\n",res);
}
