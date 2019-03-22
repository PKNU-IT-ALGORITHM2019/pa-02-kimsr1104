#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

int x[20], y[20], visited[20];			// x, y��ǥ��, �湮�ߴ��� ���� (1�̸� �湮)
double distance[20][20], cost = 0;		// ��ǥ ������ �Ÿ�, ���� ���

int least(int city, int num)			// �� ���ÿ��� �ٸ����ñ��� �ּҰŸ�
{
	int i, nc = 999;
	int min = 999;
	double kmin;

	for (i = 0; i < num; i++)
	{
		if ((distance[city][i] != 0) && (visited[i] == 0))
			if (distance[city][i] + distance[i][city] < min)
			{
				min = distance[i][0] + distance[city][i];
				kmin = distance[city][i];
				nc = i;
			}
	}
	if (min != 999)
		cost += kmin;

	return nc;
}

void mincost(int city, int num)		// ��ȯ�Լ��� �̿��Ͽ� �ּҺ�� ��θ� ����
{
	int i, ncity;

	visited[city] = 1;

	printf("%d-->", city);
	ncity = least(city, num);

	if (ncity == 999)
	{
		ncity = 0;
		printf("%d", ncity);
		cost += distance[city][ncity];

		return;
	}
	mincost(ncity, num);
}

int main()
{
	int city;
	int x_cost, y_cost;
	int i = 0, j = 0;
	FILE *fp;

	fp = fopen("C:\\GitHub2019\\pa-02-kimsr1104\\pa-02\\input0.txt", "rt");
		// ������ �б� ������ ���, ���� ����� �缳�� �ʿ�
	if (fp == NULL)
	{
		printf("������ �б� ����\n");
		return 1;
	}
	printf("������ �� : ");
	fscanf(fp, "%d", &city);
	printf("%d\n\n", city);
	printf("�� ������ ��ǥ\n");
	for (i = 0; i < city; i++)
	{
		fscanf(fp, "%d", &x[i]);
		printf("%d ", x[i]);
		fscanf(fp, "%d", &y[i]);
		printf("%d\n", y[i]);
		visited[i] = 0;
	}
	printf("\n�� ���÷� ���� �ٸ� ���ñ����� �Ÿ� (0, 0)~(%d, %d)\n\n", city-1, city-1);
	for (i = 0; i < city; i++)
	{
		for (j = 0; j < city; j++)
		{
			x_cost = abs(x[i] - x[j]);
			y_cost = abs(y[i] - y[j]);
			distance[i][j] = sqrt((x_cost * x_cost) + (y_cost * y_cost));
			printf("%.2f\t", distance[i][j]);
		}
		printf("\n");
	}

	printf("\n\n��� :");

	mincost(0, city);		// 0�� city���� ����

	printf("\n\n�ּ� ��� : %f\n", cost);
	return 0;
}