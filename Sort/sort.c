/**
 * @file Sort.c
 * @author huazaiki (dqihua03@126.com)
 * @brief 数据结构排序篇代码
 * @version 0.1
 * @date 2024-04-21
 * 
 * @(c) 2024 huazaiki
 * 
 */

#include <stdio.h>
#define ELemType int

/**
 * @brief 直接插入排序
 * 
 * @param A 目标数组
 * @param n 数组长度
 */
void InsertSort(ELemType A[], int n) {
    int i, j;   // i: 指向当前元素, j: 用来遍历前面有序数组
    for (i = 2; i <= n; i++)    // A[0]设置为 "哨兵"
    {
        if (A[i] < A[i-1])  // 比较当前元素和前面有序数组最后一位(因为有序，最后一位为最大值)
        {
            A[0] = A[i];    // 将当前元素放到哨兵位
            for(j = i - 1; A[0] < A[j]; --j)    // 将所有比当前元素大的元素后移
                A[j+1] = A[j];
            A[j+1] = A[0];  // 空出来的位置就是当前元素应该在的位置
        }
    }
}

/**
 * @brief 折半插入排序
 * 
 * @param A 目标数组
 * @param n 数组长度
 */
void InsertSort_2(ELemType A[], int n) {
    int i, j, low, high, mid;
    for (i = 2; i <= n; i++)
    {
        A[0] = A[i];    // "哨兵"
        low = 1, high = i - 1;  // 指向前面有序数组的头和尾
        while (low <= high)
        {
            mid = (low + high) / 2;
            if(A[mid] > A[0]){  
                high = mid - 1;
            } else {    // 保证算法稳定性
                low = mid + 1;
            }
        }
        for (j = i - 1; j >= high + 1; i++) // 让需要移动的元素后移
            A[j + 1] = A[j];
        A[high + 1] = A[0];
    }
}

/**
 * @brief 希尔排序
 * 
 * @param A 目标数组
 * @param n 数组长度
 */
void ShellSort(int A[], int n) {
    int d, i, j;    // d: 增量
    for(d = n / 2; d >= 1; d = d / 2) { // 开始设置分块大小
        for(i = d + 1; i <= n; i++) {   // 从 d + 1 的位置开始向后遍历，每次遍历切换分块
            if(A[i] < A[i - d]) {   // 如果当前元素比分块里前一个元素小，就前移
                A[0] = A[i];
                for(j = i - d; j > 0 && A[0] < A[j]; j -= d)    // j设置在分块里前一个元素的位置
                    A[j + d] = A[j];                            // 比较哨兵和这个位置的大小，小就后移
                A[j + d] = A[0];
            }
        }
    }
}

/**********************************************
 * 
 *                  快速排序
 * 
 **********************************************/

/**
 * @brief 划分操作
 * 
 * @param A 操作的数组(子数组)
 * @param low 
 * @param high 
 * @return int 划分元素的下表，根据这个下标递归
 */
int Partition(ELemType A[], int low, int high) {
    ELemType pivot = A[low];
    while (low < high)  // pivot成为分界点，pivot左边的元素 < pivot; pivot右边的元素 >= pivot
    {
        while(A[high] >= pivot && low < high) --high;   // 从右向左遍历，找到第一个小于pivot的元素
        A[low] = A[high];
        while(A[low] < pivot && low < high) ++low;  // 从左向右遍历，找到第一个大于等于pivot的元素
        A[high] = A[low];
    }
    A[low] = pivot; // 将此次划分的基准元素放到low指向的地方
    return low;
}

void QuickSort(ELemType A[], int low, int high) {
    if (low < high)
    {
        int pivotpos = Partition(A, low, high);
        QuickSort(A, low, pivotpos - 1);
        QuickSort(A, pivotpos + 1, high);
    }
}