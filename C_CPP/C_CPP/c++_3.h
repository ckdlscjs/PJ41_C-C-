#pragma once
#include "std.h"
struct Animal
{
	char name[30];
	int age;
};
void CreateAnimal(Animal* animal)
{
	std::cout << "�̸� : "; std::cin >> animal->name;
	std::cout << "���� : "; std::cin >> animal->age;
}
void ShowAnimal(Animal* animal)
{
	std::cout << "�̸� : " << animal->name << '\n';
	std::cout << "���� : " << animal->age << '\n';
}
void func3()
{
	int* p = new int; //int�������� p�� �����Ҵ�
	*p = 10;
	std::cout << *p << '\n';
	delete p; //�������� �����Ҵ�� int�� ����� ����Ű�� p�� �Ҵ��ϴ� �ּҸ� �����Ѵ�

	int arr_size;
	std::cin >> arr_size;
	int* arr = new int[arr_size]; //�����迭����(������)
	for (int i = 0; i < arr_size; i++) std::cin >> arr[i];
	for (int i = 0; i < arr_size; i++) std::cout << arr[i] << ' ';
	std::cout << '\n';
	delete[] arr; //����, new[]�� �迭 ��ü�� ���� ���� �޸� ����� �����ϴµ� delete�� ���ϰ�ü�� �����ϹǷ� UB�� �߱��Ų��
}
//Ȯ���� �ʿ��� �⺻���� ��ü�����ڵ�
void funcAnimal() 
{
	Animal* list[10];
	int idx = 0;
	int input = 0;
	while (input != -1)
	{
		std::cout << "1.�߰�" << '\n';
		std::cout << "2.����" << '\n';
		std::cin >> input;
		switch (input)
		{
		case 1 :
		{
			Animal* newAnimal = new Animal;
			CreateAnimal(newAnimal);
			list[idx++] = newAnimal;
		}break;
		case 2:
		{
			for (int i = 0; i < idx; i++)
				ShowAnimal(list[i]);
		}break;
		default:
		{
			std::cout << "����";
		}break;
		}
	}
	for (int i = 0; i < idx; i++)
		delete list[i];
}