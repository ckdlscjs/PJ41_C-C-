#pragma once
#include "std.h"
/*
* c++ stl�� �����̳ʴ� �ΰ��� �������ִ�, ���Ҹ� ���������� �����ϴ� �����������̳�(SequenceContainer), key������ �����ϴ� ���������̳�(AssociateContainer) 
* �����������̳ʵ� ���Ҹ� �� �ڿ� �߰��ϴ� �۾��� amortized O(1) �̶� �Ѵ�, ���Ұ� �� ���ԵǴ� ��� �� ū ������ ���Ҵ��ϰ� ���������� ���縦 �����ؾ��ϹǷ� ����O(1)���ٴ� ũ���� ������ΰ��ΰ�
*/

namespace stl_vec
{
	
	void Exam()
	{
		void (*pf)(const std::vector<int>&) = [](const std::vector<int>& vec) 
			{
			for (std::vector<int>::const_iterator iter = vec.begin(); iter != vec.end(); iter++)
				std::cout << *iter << ' ';
			std::cout << '\n'; 
			};
		std::vector<int> vec;
		vec.push_back(0);
		vec.push_back(10); //�ڿ�����
		vec.push_back(20);
		vec.push_back(30);
		//�ݺ���(iterator)
		/*
		* begin() ù����
		* end() ����������+1
		* 
		*/
		
		std::cout << *(vec.begin() + 2) << '\n';//0, 1, 2(vec[2] ->20)
		
		pf(vec);

		vec.insert(vec.begin() + 2, 15); //20�ڸ��� 15����
		pf(vec);
		
		*(vec.begin() + 3) = 25; //����20�� 25�κ���

		//iterator�� �̿��� erase�� �����Ҷ� �ݺ��������� iterator�� ��ġ������ �̿��� ����� ��ȯ���� iterator�� �����Ͽ� iterator�� �������������
		for (std::vector<int>::const_iterator iter = vec.begin(); iter != vec.end();)
		{
			if (*iter == 25)
				iter = vec.erase(iter);
			iter++;
		}
		pf(vec);
		//begin()0������Ŵ end()��+1������Ŵ
		//rend()ù��°���Һ��� ��ĭ��������Ŵ(end�͵���), rbegin() ���������Ҹ�����Ŵ
	}
}

namespace stl_list
{
	/*
	* ���Ḯ��Ʈ, vector�� �޸� ���Ḯ��Ʈ������ �Ǿ��ֱ⿡ ������ ���������� �Ұ��ϴ�, 
	* ++, -- ���� ����, ���� ���길 �����ϰ� begin() + 5�� ���������� �Ұ��ϴ�(�������޸𸮰� �ƴϱ⶧��)
	*/
	void Exam()
	{
		std::list<int> lst;
		lst.push_back(0);
		lst.push_back(10); //�ڿ�����
		lst.push_back(20);
		lst.push_back(30);
		for (std::list<int>::const_iterator iter = lst.begin(); iter != lst.end();)
		{
			if (*iter == 20)
			{
				iter = lst.erase(iter);
				continue;
			}
			std::cout << *iter++ << ' ';
		}
	}
}

namespace stl_deque
{
	/*
	* ���� ������ ��κ��� ������ �����ϸ� �ӵ����� ������ �����ϳ� ������ ��ġ�� ����ϱ����� �߰��޸𸮰����� ��ƸԱ⶧���� �޸𸮰����� �Һ������� �ð����⵵������ �̵��� ��������
	* �޸𸮻� �������� ���������ʰ� ���Ḯ��Ʈ�� �̿��Ͽ� ������ġ�� ����Ű�� �����ͷ� �����Ͽ� ������ ������Ų��
	* ������·� ���������� ������Ű�⶧���� ����ó�� �������� �Ҵ��ϸ鼭 ������ ���ҵ��� ������ �ʿ伺�� ���⶧���� ���ͺ��� ������ ���� �� ���ִ�
	*/
	void Exam()
	{
		
	}
}

/*
* 10_2
* ���������̳�(AssociateContainer)�� ���ؼ� �ٷ��
* key<->value ���� �����̳�
* �����Ͱ� ������ ���θ�üũ set, unordered_set
* �����ͽ��� üũ map, unordered_map
* set, map�� �����Ʈ������� �ڰ���������Ʈ���� �̿�
* unordered�迭�� �ؽø� �̿�
* multi�迭�� �ߺ��Ǵ� key���� ����Ѵ�, ������ �����ǰ��� ������ �ش� Ű�� �����ϴ�
* ������ ��Բ� �� �� �ִ� �̸� ���� var.equal_range(����)�� ����Ѵ�
* set, map�� ��� < Ȥ�� > ������ �񱳸� �ϴ� operator�� �������Ͽ� ��������Ŭ������
* ���� �����ϴ�, unordered�迭�� hash�� ��������ؾ� �ϹǷ� ��ȿ����
* 
*/

/*
* 10_3
* sort�� �����ݺ������ڿ����� ��밡���ϴ�, vector, deque(�������������̰�����), list���� ���������� �����ؾ��ϴ� �����̳ʿ����� ����̺Ұ���
* �Ϲ������� algorithm�� �Լ����� Pred�� �����ڿ� �Լ���ü�� ����־� ����Ѵ�(���� bool)
* erase�ǰ�� erase(iter)�ǰ�� �ϳ��ǿ��Ҹ� ����� erase(iter first, iter last)�� ���� first~last�����ǿ��Ҹ������
* Ư���� ������ ������Ű�� ������ ����Ұ�� remove, Ȥ�� remove_if�� �̿��Ѵ�
* 
* �����Լ�
* [ĸó��] (����) -> ����Ÿ�� {�Լ���ü}
* ����Ÿ���̾����� ->�������� [ĸ����] (����) {�Լ���ü}, ����Ÿ���� �����Ϸ����߷�, Ŭ�������ο��� ���ڸ� üũ���� ���� ĸ������ this�����
* [&]�����ΰ�����
* [=]����ΰ�����
* [this] ��ü������
* 
* transform(���۹ݺ���, ���ݺ���, ����������������̳��ǽ��۹ݺ���, ������(Pred))-> ����~�� ���� ���۹ݺ����ʿ� �ش簹����ŭ����, �� ����������̳ʰ� �̸� ������ŭũ�Ⱑ�Ǿ���
*/
namespace ch10_3
{
	struct is_odd
	{
		bool operator()(const int& i) { return i % 2 == 1; };
	};
	struct is_odd2
	{
		int* num_delete;
		is_odd2(int* num_del_ptr) : num_delete(num_del_ptr) {} //�ܺκ����� ���, ��ü�Լ��� �ν��Ͻ������� ��ü���ٴٸ��Ƿ�,
		bool operator()(const int& i) 
		{ 
			if (*num_delete < 2)
			{
				if (i % 2 == 1)
				{
					(*num_delete)++;
					return true;
				}
			}
			return false;
		};
	};
	void Exam()
	{
		int del_cnt = 0;
		std::vector<int> vec = { 5, 3, 1, 2, 3, 4 };
		/*
		auto iterator = std::remove_if(vec.begin(), vec.end(), is_odd2(&del_cnt)); // 2, 4, 1, 2, 3, 4, is_odd�� �ش��ϴ� Ȧ������ �ڷκ�����
		for (const auto& iter : vec)
			std::cout << iter << ' ';
		std::cout << '\n';
		*/
		vec.erase(std::remove_if(vec.begin(), vec.end(), is_odd2(&del_cnt)), vec.end());
		for (const auto& iter : vec)
			std::cout << iter << ' ';
	}
}