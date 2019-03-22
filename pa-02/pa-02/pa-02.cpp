#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

int x[20], y[20], visited[20];			// x, y좌표값, 방문했는지 여부 (1이면 방문)
double distance[20][20], cost = 0;		// 좌표 사이의 거리, 최종 비용

int least(int city, int num)			// 한 도시에서 다른도시까지 최소거리
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

void mincost(int city, int num)		// 순환함수를 이용하여 최소비용 경로를 구함
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
		// 데이터 읽기 실패의 경우, 파일 경로의 재설정 필요
	if (fp == NULL)
	{
		printf("데이터 읽기 실패\n");
		return 1;
	}
	printf("도시의 수 : ");
	fscanf(fp, "%d", &city);
	printf("%d\n\n", city);
	printf("각 도시의 좌표\n");
	for (i = 0; i < city; i++)
	{
		fscanf(fp, "%d", &x[i]);
		printf("%d ", x[i]);
		fscanf(fp, "%d", &y[i]);
		printf("%d\n", y[i]);
		visited[i] = 0;
	}
	printf("\n한 도시로 부터 다른 도시까지의 거리 (0, 0)~(%d, %d)\n\n", city-1, city-1);
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

	printf("\n\n경로 :");

	mincost(0, city);		// 0번 city부터 시작

	printf("\n\n최소 비용 : %f\n", cost);
	return 0;
}