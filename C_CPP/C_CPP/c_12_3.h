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