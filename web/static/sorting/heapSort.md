# 堆排序

## 算法原理
将数组构建出完全二叉树，从最后一个内结点向上调整，若为大根堆，则从最后一个内结点往上，每次将此根节点与左右子节点中的较大者作为根节点，直到最后完全二叉树的根节点就确定为最大数，记录到数组中。再将数组中最后一个元素覆盖到根节点位置，再次从最后一个内结点开始向上调整堆，直到堆中所有元素均已被记录

## 算法实现
```cpp
int heapSort(vector<Book> v){
    vector<int> ret;
    for(int n =v.size(); n > 0; n--){
        for(int i = (n-1-1)/2; i>=0; i--){
            找到左右子节点的最大者
            if(最大者大于根节点){
                交换最大者与根节点
            }
        }
    	ret.push_back(v[0]);//记录最大元素到返回数组
    	v[0] = v[n-1];//用尾元素覆盖根节点
    }
    return ret;
}
```
## 实现要点
- n-1为尾元素，(index - 1)/2为index的父节点，父节点*2为左孩子，*2+1为右孩子
- 从最后一个内结点（尾结点的父节点开始向上调整）