#pragma once
#include "std.h"
void changeVal(int* p)
{
	*p = 3;
}
void changeVal(int& p)
{
	p = 7;
}
int& retVal(int& ref)
{
	return ref;
}
//�����ڷ� ��������ͷ��� ����
const int& retConstval() 
{
	int constVal = 456;
	return constVal;
}
void func2_1()
{
	int num = 5; //int������ num
	std::cout << num << '\n';

	changeVal(&num); //int������ num�� int* p�� �ּҸ� �Ѱܼ� changeVal�Լ��� �̿��� ���� ������
	std::cout << num << '\n'; //num�ǰ��� ������� Ȯ��

	int& ref_num = num; //int�� ������ ref_num�� num�� ����
	ref_num = 6;
	std::cout << num << '\n';

	changeVal(ref_num); //int�� ������ p�� ref_num(num)�� ����
	std::cout << num << '\n';

	const int& ref = 123;
	std::cout << ref << '\n'; //������ͷ� ref

	int arr[] = { 1, 4, 3 };
	int& refarr = *arr;
	int(&refarr2)[3] = arr;
	std::cout << &refarr << ' ' << refarr2+1 << ' ' << arr+1 << '\n'; //arr[0]���ּ�, �迭arr�� �ּ�+1, �迭arr���ּ�+1
	std::cout << refarr2 + 1 << ' ' << &arr + 1 << '\n'; //arr���ּ�+1, �迭arr��ü���ּ�+1(+4*3)
	std::cout << refarr + 1 << ' ' << refarr2[1] << ' ' << *(arr + 1) << '\n'; //�迭arr[0]�ǰ�+1, arr[1], arr[1]

	int& reffunc = retVal(arr[0]); //�����ڷ� arr[0]�� �ǳ���, reffunc�� ��ȯ�Ǵ� �������� ������ ���� reffunc�����ڰ� arr[0]�� ����Ŵ
	reffunc = 5; //arr[0]�ǰ�������
	std::cout << arr[0] << '\n';

	const int& constVal = retConstval(); //����� ������ ���ͷ��� ����� �����ڷ� ����, �����Ұ�
	std::cout << constVal;
}