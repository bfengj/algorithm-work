# 基数排序

## 算法原理
待比较数字的拥有不同的位权，在相同的位权上可以进行排序，再逐渐升高位权，例如10, 22, 7，3, 54，按照个位上排序后为10， 22， 3， 54， 7，在此排序结果上再按照十位排序，结果为3， 7， 10， 22， 54，此时数组已有序。

## 算法实现

```cpp
vector<int> baseSort(vector<int> &v){
    vector<vector<int>> ctnr(10);//十位数每位范围为0-9
    int n, maxindex, maxnum = 0;//n记录最大数的位数
    for(int i =0; i < v.size(); i++){
        找到位数最长的数字
    }
    for(int f = 10, temp = v[maxindex]; temp > 0; n++){//确定最大数的位数，用n记录
        temp /= f;
    }

    for(int f = 1, times = 0; times < n; f *= 10, times++){
        for(int i =0; i < v.size(); i++){
            ctnr[v[i] /f %10].push_back(v[i]);//将数组中的数字按照位值，类似桶排序放入临时数组的对应下标，如个位模的结果为3，则放入临时数组3下标的位置
        }
        int cnt = 0;
        for(auto i = ctnr.begin(); i != ctnr.end(); i++){
            for(auto j = i->begin(); j != i->end(); ){
                v[cnt++] = *j;//将新排序的数组覆盖原数组
                j = i->erase(j);
            }
        }
    }
    return v;
}
```

## 实现要点
- 先要确定最大数有多少位
- 按位排序记录的数组大小为10
- 每次新的排序都以上次已经按位排好的结果为基础