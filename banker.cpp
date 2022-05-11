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
	// int temp = 0;
	int failness = 0; //自上一个满足的进程起，接下来的进程不满足的次数
	while (allFinish != ProcessNum) //当进程还没全部结束时
	{
		j = 0;
		if (Finish[i] != true)
		{
			for (j = 0; j < ResourceNum; j++)
			{
				if (need[i][j] > work[j])
				{
					failness++; //不满足次数加1
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
			failness = 0; //当前进程满足，归0
		}
		i++;
		if (i >= ProcessNum)
		{
			i = i % ProcessNum;
			// if (temp == allFinish)
			if (failness == ProcessNum - allFinish) //剩余进程都不满足，系统不安全，退出
				break;
		}
		// temp = allFinish;
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
