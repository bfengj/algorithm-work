# 归并排序

## 算法原理
将多个有序的子区间合并成有序的整个数组，初始将数组分成多个长度为2的子区间，子区间内排序；逐渐增大子区间的长度并排序，直到子区间的长度为整个数组的长度。

## 算法实现
```cpp
void merge(vector<int> &v, int low, int middle, int high){
    int i = low, j = middle+1, k =0;
    vector<int> temp;
    while (i <= middle && j <= high){
		将i与j对应元素中的较小者放入temp数组
	}
	while (i <= middle)//将middle左区间剩余元素加入temp
		temp.push_back(v[i++]);
	while (j <= high)//将middle右区间剩余元素加入temp
		temp.push_back(v[j++]);
	// 将排好序的存回v中low到high该区间内 
	for (i = low, k = 0; i <= high; i++, k++)
		v[i] = temp[k];
}

vector<int> mergeSort(vector<int> &v){
    int n = v.size();
    int size = 1, low, middle, high;//size为区间长度
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
}
```
## 实现要点
- middle = low + size - 1，high = middle + size;即middle可与low重合
- high不能越界
- 下一个区间从上一个区间的右边界high的下一个位置开始