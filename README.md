

[TOC]

# 进程死锁：银行家算法

## 问题描述

​        设计程序模拟避免进程死锁的银行家算法的工作过程。假设有系统中有n个进程P~1~, … ,P~n~，有m类可分配的资源R~1~, … ,R~m~，在T~0~时刻，进程Pi分配到的j类资源为Allocation~i~~j~个，它还需要j类资源Need~i~~j~个，系统目前剩余j类资源Work~j~个，现采用银行家算法进行资源分配避免死锁的发生。

1）判断当前状态T~0~是否安全，如果安全，给出安全序列；如果不安全给出理由。

2）对于下一个时刻T~1~，某个进程P~k~会提出请求Request(R~1~, … ,R~m~)，判断是否可以分配给P~k~进程请求的资源。

3）输入以下信息，或者将这些信息存入文件，并读入该文件。

- 进程个数n，资源种类m，以及各类资源的实例个数，例如：

> The number of processes: 5
>
> The number of resource types: 3
>
> The numbers of the resources for each resource type : 10, 5, 7

- T~0~时刻各个进程的资源分配情况、最大资源需求、剩余所需资源、以及剩余的资源情况，例如：

![image-20220506154508999](https://s2.loli.net/2022/05/06/7phYaRNWtZerPx8.png)

- T~1~时刻，发出请求的进程编号，以及请求的资源情况，例如：

> Who makes a further request (the number of the process): 1
>
> The request : 1, 0, 2

4）输出：

- 判断T~0~时刻是否安全的详细信息，如果安全，则输出安全的进程序列，否则提示不安全信息。例如：

![image-20220506154859918](https://s2.loli.net/2022/05/06/r35kuj6RfgEZP7p.png)

> security sequence : P~1~，P~3~，P~4~，P~2~，P~0~

- 判断T~1~时刻满足进程请求后系统是否安全的详细信息，最后给出是否可以满足该进程请求的结论信息。例如：

![image-20220506155107234](https://s2.loli.net/2022/05/06/bdQqkrTMmcfo849.png)

> Conclusion : Requests of p~1~ is able to be granted.

## 实验环境

- Windows 11
- Visual Studio Code
- GCC version 8.1.0

## 输入

- 输入所需的信息和系统的当前状态。
- 输出状态的判断，如果状态是安全的，则输出进程的安全顺序。
- 在T1时间内输入请求。


## 输出

- 显示T~0~时间内系统的状态。
- 调用安全算法以查看当前状态是否安全，并显示详细结果。
- 输出状态判断和请求能否被批准的结论。如果状态是安全的，则输出进程的安全序列。如果不安全或者无新请求则退出。

## 测试数据

- 进程和资源的数据如**问题描述**所示
- 发起请求的进程：P~1~
- 请求的资源数量：1 0 2
- 测试系统不安全和请求资源超出剩余资源的情况

## 实验设计

### 数据结构

```cpp
//剩余的可使用资源
int available[ResourceNum] = {3, 3, 2};
//进程的最大需求
int MAX[ProcessNum][ResourceNum] = {{7, 5, 3}, {3, 2, 2}, {9, 0, 2}, {2, 2, 2}, {4, 3, 3}};
//进程以及占有的资源
int allocation[ProcessNum][ResourceNum] = {{0, 1, 0}, {2, 0, 0}, {3, 0, 2}, {2, 1, 1}, {0, 0, 2}};
//进程还需要的资源
int need[ProcessNum][ResourceNum] = {{7, 4, 3}, {1, 2, 2}, {6, 0, 0}, {0, 1, 1}, {4, 3, 1}};
//判断是否安全
bool Finish[ProcessNum];
//安全序列号
int safeSeries[ProcessNum] = {0};
//进程请求资源数
int request[ResourceNum];
```

### 主要函数功能和参数

`void print()`

- 功能：打印系统信息
- 参数：无

`void safePrint(int work[ResourceNum], int i)`

- 功能：打印安全检查信息
- 参数：工作向量、进程的索引

`void safePrint(int work[ResourceNum], int i)`

- 功能：打印安全检查信息
- 参数：工作向量、进程的索引

`bool is_safe()`

- 功能：安全性检查
- 参数：无


### 系统框架图

![img](https://s2.loli.net/2022/05/06/pBSAIRWgza85qxn.png)

### 流程图

![image-20220506182220519](C:/Users/%E9%AB%98%E6%B6%A6/AppData/Roaming/Typora/typora-user-images/image-20220506182220519.png)

## 实验结果与分析

### 结果展示与描述

- 初始信息

![image-20220506183240454](https://s2.loli.net/2022/05/06/SC23k9aNiEjHXvV.png)

- 进程1请求资源1 0 2

![image-20220506183256745](https://s2.loli.net/2022/05/06/CgYArbiQcdUV78z.png)

- 不安全和请求资源超出剩余资源的情况

![image-20220506183753995](https://s2.loli.net/2022/05/06/rBfFiTbQMGczJDC.png)

### 结果分析

- 剩余资源满足P~1~需求，首先分配给P~1~
- P~1~完成后，释放资源，此时剩余资源满足P~3~需求
- 以此类推，每次有进程完成释放资源后，都存在满足条件的进程
- 以此得到安全序列并打印
- P~1~申请资源后，对调整后的资源再进行安全性检查
- 能够得到安全序列
- 若P~4~再申请资源0 3 0，则无法得到安全序列
- 若申请的资源超出剩余资源，则报错并退出程序

### 总结

- 银行家算法是一种最有代表性的避免死锁的算法。在避免死锁方法中允许进程动态地申请资源，但系统在进行资源分配之前，应先计算此次分配资源的安全性，若分配不会导致系统进入不安全状态，则分配，否则等待。
- 在避免死锁的方法中，所施加的限制条件较弱，有可能获得令人满意的系统性能。在该方法中把系统的状态分为安全状态和不安全状态，只要能使系统始终都处于安全状态，便可以避免发生死锁。
- 理解了进程死锁相关概念，包括资源的请求、资源持有、安全状态等等。掌握了判断进程是否处于安全状态的过程。掌握了死锁避免方法中的银行家算法。

## 源代码

```cpp
#include <iostream>
using namespace std;
#define ProcessNum 5  //进程总数
#define ResourceNum 3 //资源种类
#define TRUE 1
#define FALSE 0
//剩余的可使用资源
int available[ResourceNum] = {3, 3, 2};
//进程的最大需求
int MAX[ProcessNum][ResourceNum] = {{7, 5, 3}, {3, 2, 2}, {9, 0, 2}, {2, 2, 2}, {4, 3, 3}};
//进程以及占有的资源
int allocation[ProcessNum][ResourceNum] = {{0, 1, 0}, {2, 0, 0}, {3, 0, 2}, {2, 1, 1}, {0, 0, 2}};
//进程还需要的资源
int need[ProcessNum][ResourceNum] = {{7, 4, 3}, {1, 2, 2}, {6, 0, 0}, {0, 1, 1}, {4, 3, 1}};
//判断是否安全
bool Finish[ProcessNum];
//安全序列号
int safeSeries[ProcessNum] = {0};
//进程请求资源数
int request[ResourceNum];

//打印系统信息
void print()
{
	cout << "-------------------------------------------- " << endl;
	cout << "当前系统各类资源剩余：";
	for (int i = 0; i < ResourceNum; i++)
	{
		cout << available[i] << " ";
	}
	cout << endl;
	cout << "当前系统资源情况：" << endl;
	cout << "PID" << '\t' << "MAX" << '\t' << "Allocation" << '\t' << "Need" << endl;
	for (int i = 0; i < ProcessNum; i++)
	{
		cout << i << '\t';
		for (int j = 0; j < ResourceNum; j++)
		{
			cout << MAX[i][j] << " ";
		}
		cout << '\t';
		for (int j = 0; j < ResourceNum; j++)
		{
			cout << allocation[i][j] << " ";
		}
		cout << '\t' << '\t';
		for (int j = 0; j < ResourceNum; j++)
		{
			cout << need[i][j] << " ";
		}
		cout << endl;
	}
	cout << "---------------------------------------------------------" << endl;
	// cout << endl;
}

//打印安全检查信息
void safePrint(int work[ResourceNum], int i)
{
	cout << "PID" << '\t' << "Work" << '\t' << "Need" << '\t' << "Allocation" << '\t' << "Work+Allocation" << endl;
	cout << i << '\t';
	for (int j = 0; j < ResourceNum; j++)
	{
		cout << work[j] << " ";
	}
	cout << '\t';
	for (int j = 0; j < ResourceNum; j++)
	{
		cout << need[i][j] << " ";
	}
	cout << '\t';
	for (int j = 0; j < ResourceNum; j++)
	{
		cout << allocation[i][j] << " ";
	}
	cout << '\t' << '\t';
	for (int j = 0; j < ResourceNum; j++)
	{
		cout << allocation[i][j] + work[j] << " ";
	}
	cout << endl;
}

//安全性检查
bool is_safe()
{
	int allFinish = 0;					  //完成的进程数
	int safeIndex = 0;					  //安全序列下标
	int work[ResourceNum];				  //工作向量
	for (int i = 0; i < ResourceNum; i++) //初始work=available
	{
		work[i] = available[i];
	}
	for (int i = 0; i < ProcessNum; i++) //初始Finish全为FALSE，有足够资源分配给进程时为TRUE
	{
		Finish[i] = FALSE;
	}
	int i = 0, j = 0, k = 0;
	int temp = 0;
	while (allFinish != ProcessNum) //当进程还没全部结束时
	{
		j = 0;
		if (Finish[i] != true)
		{
			for (j = 0; j < ResourceNum; j++)
			{
				if (need[i][j] > work[j])
				{
					break;
				}
			}
		}
		if (j == ResourceNum)
		{
			Finish[i] = true;
			safePrint(work, i);
			for (k = 0; k < ResourceNum; k++)
			{
				work[k] += allocation[i][k];
			}
			safeSeries[allFinish++] = i;
		}
		i++;
		if (i >= ProcessNum)
		{
			i = i % ProcessNum;
			if (temp == allFinish)
				break;
		}
		temp = allFinish;
	}

	if (allFinish == ProcessNum)
	{
		cout << "系统安全！安全序列号为：";
		for (i = 0; i < ProcessNum; i++)
		{
			cout << safeSeries[i] << " ";
		}
		cout << endl;
		return true;
	}
	cout << "系统不安全！";
	return false;
}

int main()
{
	int curProcess = 0;
	print(); //打印资源情况
	// cout << "---------------------------------------------------------" << endl;
	cout << "系统安全性分析：" << endl;
	is_safe();
	cout << "---------------------------------------------------------" << endl;
	while (TRUE)
	{
		cout << "输入要分配的PID : ";
		cin >> curProcess;
		cout << "输入要分配给进程的资源 : ";
		for (int i = 0; i < ResourceNum; i++)
		{
			cin >> request[i];
		}
		int j;
		for (j = 0; j < ResourceNum; j++)
		{
			if (request[j] > need[curProcess][j])
			{
				cout << "所需资源超过最大值, ERROR ! " << endl;
				cout << "---------------------------------------------------------" << endl;
				return 0;
			}
		}
		for (j = 0; j < ResourceNum; j++)
		{
			if (request[j] <= available[j])
				continue;
			else
			{
				cout << "资源不足，等待中 ! " << endl;
				break;
			}
		}
		if (j == ResourceNum)
		{
			for (j = 0; j < ResourceNum; j++)
			{
				available[j] -= request[j];
				allocation[curProcess][j] += request[j];
				need[curProcess][j] -= request[j];
			}
			cout << "系统安全情况分析 : " << endl;
			if (is_safe())
			{
				cout << "分配成功 ! " << endl;
				print(); //打印信息
			}
			else //分配失败，恢复原来的状态
			{
				available[j] += request[j];
				allocation[curProcess][j] -= request[j];
				need[curProcess][j] += request[j];
				cout << "分配失败 ! " << endl;
				cout << "进程" << curProcess << "等待 ! " << endl;
			}
		}
	}
	system("pause");
	return 0;
}

```



