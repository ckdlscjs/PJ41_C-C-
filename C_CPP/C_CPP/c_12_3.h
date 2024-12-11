#pragma once
#include "std.h"

void func12_3()
{
	int arr[] = { 100, 98, 97, 95, 89, 76, 92, 96, 100, 99 };
	int* parr = &arr[0]; //same parr = arr;
	while (parr - arr <= 9)
		std::cout << *(parr++) << ' ';

	std::cout << '\n';
	//�迭������
	int(*parr2)[10] = &arr; //ũ�Ⱑ 10�� int�� �迭�� ����Ű�� ������(�迭������)
	std::cout << arr+1 << ' ' << parr2+1; //move to +4, +40(4*10)
	int arr2[2][3] = { 1,2,3,4,5,6};
	std::cout << '\n';
	std::cout << arr2[0] << ' ' << arr2[1] << '\n'; //same arr2[0][0], arr2[1][0], + 1 move 4byte
	std::cout << sizeof(arr2) << ' ' << sizeof(arr2[0]) << ' ' << sizeof(arr2[0][0]) << '\n';

	int(*parr3)[3] = arr2; 
	//arr[a][b] �� int arr[b]¥�� �迭�� �ΰ� �޸𸮻� �������� ��ġ�ϴ°� ���
	//�׷��Ƿ� arr[y][0]�� �ּҰ��� y��° int arr[b]¥�� �迭�̴�, �׷��⶧���� arr + 4*b*y�̴�, �������� x�ǰ�����ŭ ���ϸ� arr+4*b*y+4*x�� �ּҰ��̵ȴ�
	//�׷��⶧���� [3]�̶�� b�������� �������� �˷���� �ش� �迭�����Ͱ� �ּҸ� ��Ȯ�� ��� �� �� �ִ�.
	std::cout << parr3[0][0] << '\n';
	
	//int arr2[2][3] = { 1,2,3,4,5,6 };
	int(*parr4)[2] = NULL;
	parr4 = (int(*)[2])arr2; //cast to [2][3] -> [3][2] ������ �ϳ� ���������ʴ´�(UB���ʷ�)
	std::cout << parr4[1][0] << '\n';

	int* parr5[2];
	parr5[0] = arr2[0];
	parr5[1] = arr2[1];
	int** pparr = parr5; //���������ͷ� ó���� �Ϸ��� �������ǹ迭�� �̿��� ��ġó���� �� �� �ִ�.
	std::cout << pparr[0][0];
}
#include <bits/stdc++.h>
using namespace std;
const int dy[] = { 0, 0, 1, -1 };
const int dx[] = { 1, -1, 0, 0 };
std::string arr[12];
bool visited[14][8];
int DFS(int cy, int cx, char ch)
{
    int ret = 1;
    visited[cy][cx] = true;
    for (int dir = 0; dir < 4; dir++)
    {
        int ny = cy + dy[dir];
        int nx = cx + dx[dir];
        if (ny < 0 || nx < 0 || ny >= 12 || nx >= 6 || arr[ny][nx] != ch || visited[ny][nx]) continue;
        ret += DFS(ny, nx, ch);
    }
    return ret;
}
int baek()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);
    for (int i = 0; i < 12; i++) std::cin >> arr[i];
    int cnt = 0;
    while (1)
    {
        bool chk = false;
        for (int j = 0; j < 6; j++)
        {
            for (int i = 11; i >= 0; i--)
            {
                if (arr[i][j] == '.' || visited[i][j]) continue;
                if (DFS(i, j, arr[i][j]) >= 4)
                {
                    chk = true;
                    std::queue<std::pair<int, int>> q;
                    q.push({ i, j });
                    while (q.size())
                    {
                        int cy = q.front().first;
                        int cx = q.front().second;
                        q.pop();
                        char ch = arr[cy][cx];
                        arr[cy][cx] = '.';
                        for (int dir = 0; dir < 4; dir++)
                        {
                            int ny = cy + dy[dir];
                            int nx = cx + dx[dir];
                            if (ny < 0 || nx < 0 || ny >= 12 || nx >= 6 || arr[ny][nx] != ch) continue;
                            q.push({ ny, nx });
                        }
                    }
                }
            }
        }
        for (int i = 0; i < 12; i++)
        {
            std::cout << arr[i];
            std::cout << '\n';
        }
        std::cout << '\n';
        if (!chk) break;
        cnt++;
        for (int j = 0; j < 6; j++)
        {
            for (int i = 11; i >= 0; i--)
            {
                if (arr[i][j] != '.') continue;
                for (int ii = i - 1; ii >= 0; ii--)
                {
                    if (arr[ii][j] == '.') continue;
                    arr[i][j] = arr[ii][j];
                    arr[ii][j] = '.';
                    break;
                }
            }
        }
        std::memset(visited, false, sizeof(visited));
    }
    std::cout << cnt;
    return 0;
}