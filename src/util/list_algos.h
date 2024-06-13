#ifndef _Util_List_Algos_h_
#define _Util_List_Algos_h_

#include <util/list.h>

/**
 * 附加题：
 * 1. 创建单元测试来比较这两个算法的性能。你需要man 3 time来查询基本的时间函数，并且需要运行足够的迭代次数，至少以几秒钟作为样本。
 * 2. 改变需要排序的链表中的数据总量，看看耗时如何变化。
 * 3. 寻找方法来创建不同长度的随机链表，并且测量需要多少时间，之后将它可视化并与算法的描述对比。
 * 4. 尝试解释为什么对链表排序十分麻烦。
 * 5. 实现List_insert_sorted（有序链表），它使用List_compare，接收一个值，将其插入到正确的位置，使链表有序。它与创建链表后再进行排序相比怎么样？
 * 5. 尝试实现维基百科上“自底向上”的归并排序。上面的代码已经是C写的了，所以很容易重新创建，但是要试着理解它的工作原理，并与这里的低效版本对比。
 * 
 */

typedef int (*List_compare)(const void *a, const void *b);

int List_bubble_sort(List *list, List_compare cmp);

List *List_merge_sort(List *list, List_compare cmp);

#endif