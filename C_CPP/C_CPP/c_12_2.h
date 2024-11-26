#pragma once
#include "std.h"
void func12_2(void)
{
	int a = 1, b = 0;
	const int* pa = &a; //int�� ������ pa�� ����Ű�� �ּҿ� ����� ���� pa�� ���ؼ��� ���� �� �� ����
	a = 2;
	int* const pb = &b; //int�� ������ pb�� ����Ű�� ��(����)�� ���� �Ұ��ϴ�, ����Ű�� �ּҿ� �ش��ϴ� ������ ������ ������ �����ϴ�
	*pb = 3;
	const int* const pc = &a; //����Ű�� �ּҰ��� ������ �� �Ѵ� ������ �Ұ��ϴ�
	std::cout << *pa << *pb << *pc << '\n';
	
	int add_a;
	int* add_pa = &add_a;
	//std::cout���� �������� �ּҰ��� %p�������� ����ϱ����� std::showbase, std::hex, reinterpret_cast�� �̿��Ѵ�, (�ڷ���)�� c��� Ÿ�� ĳ����
	std::cout << std::showbase << std::hex << reinterpret_cast<uintptr_t>(add_pa + 1) << ", " << (uintptr_t)&add_a << '\n'; //�� ���� ���� �ּҸ� ����Ų��, add_pa�� add_a���ּҸ� ����Ű�� +1�ϸ� 4����Ʈ����, &add_a+1�� �ּ�+4����Ʈ

	char add_b = 'a';
	char* add_pb = &add_b;
	std::cout << std::showbase << std::hex<< (uintptr_t)add_pb + 1 << ", " << (uintptr_t)&add_b << '\n';

	double add_c = 0.0f;
	double* add_pc = &add_c;
	std::cout << std::showbase << std::hex << (uintptr_t)add_pc + 1 << ", " << (uintptr_t)&add_c << '\n';
	
	int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	int* parr = &arr[0];
	//������ �� ���� �ּҸ� ����Ų�� �ᱹ &arr[0]�� arr�ǽ����ּ��ε� �̴� arr�� ���� �迭 arr�� ������ arr�迭�� �����ּҸ� ����Ų�ٴ°� �� �� �ִ�.
	std::cout << std::showbase << std::hex << (uintptr_t)parr << ", " << (uintptr_t)arr << ", " << (uintptr_t)&arr[0] <<'\n'; //������ �� ���� �ּҸ� ����Ų��
	std::cout << std::dec << arr[3] << ", " << *(arr + 3) << '\n';
}