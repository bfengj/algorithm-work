# 快速排序

## 算法原理
采用分治法，整个数组排序的实现建立在递归子区间均已排序构成的合集。
每轮递归确定一个基准元素的位置，再以基准元素为中心将数组分为基准元素左右两个区间继续递归。
设置一个基准元素pivot（一般选首个元素或末尾元素），和两个分别指向区间的首部指针low和尾部指针high，！当选取首个元素为pivot时，先移动右指针high，右指针向左移动直到遇到比基准元素pivot小的元素然后停下，再向右移动左指针low直到遇到第一个比pivot大的元素上，交换左右指针对应的元素。重复直到左指针等于右指针，将pivot与low对应的元素交换，此时在整个数组中pivot基准元素就确定好了自己的最终位置。以基准元素二分区间继续递归

## 算法实现
```cpp
int oneSort(vector<Book> &v, int low, int high){
    int pivot = low;//pivot等于区间最左点low
    while(low < high){
            while(low < high && v[high].monthTicket >= v[pivot].monthTicket)//pivot为首元素，则high指针先移动
                high--;
            while (low < high && v[low].monthTicket <= v[pivot].monthTicket)//枢纽选的第一个数，low从0开始，包含=
                low++;
            if(low < high)
                swap(v[high], v[low]);
        }
    swap(v[low], v[pivot]);
    return low;//low是枢纽确定后的位置
}


void quickSort(vector<Book> &v){
    stack<pair<int, int>> s;
    s.push({0, v.size()-1});
    while(!s.empty()){
        弹出左右指针
        int mid = oneSort(v, low, high);//oneSort返回pivot的下标
        if(mid-1 > low)
            左右指针入栈
        if(mid+1 < high)
            左右指针入栈
    }
}
```

## 算法要点
- 由于数据量大，不采用递归实现，而使用栈数据结构模拟递归
- 左右指针那个先移动与pivot选取有关，pivot为首元素，则右指针先移动
- 左右指针相等时，即为pivot元素的最终位置
- 非递归方法将区间的左右端点，即左右指针作为pair压入栈中，注意左右指针不能越界