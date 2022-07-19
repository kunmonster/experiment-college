# 基于交换的排序

## 原理:

- 通过交换序列内部元素实现的排序

## 冒泡排序

### 原理

- 每一趟有一个关键字位于其最终位置
- 相邻元素比较,然后如果满足要求就交换,一趟完成后,就能确定一个元素的最终位置
- 可以设立一个交换标志位,如果某一趟没有发生交换,那么显然序列已经有序

### 代码

```langague c++
/**
 * @brief 冒泡排序
 * @tparam T
 * @param arr
 * @param len
 */
template <typename T>
void bubble_sort(Element<T>* arr, int len) {
  if (len <= 1) return;
  bool switch_flag;
  int i, j;
  for (i = 0; i < len; i++) {
    //判断某一趟是否发生交换,如果未发生交换,显然已经有序,此时不需要再继续了
    switch_flag = false;
    for (j = 0; j < (len - i - 1); j++) {
      if (arr[j] > arr[j + 1]) {
        //发生交换
        auto temp = arr[j + 1];
        arr[j + 1] = arr[j];
        arr[j] = temp;
        switch_flag = true;
      }
    }
    if (switch_flag == false) return;
  }
}
```

### 效率分析

#### 时间效率
1. 最好情况
    

2. 最坏情况
