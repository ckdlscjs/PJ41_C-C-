#pragma once
#include "std.h"
//���(Inheritance)
namespace Inheritance1
{
	class A
	{
	protected:
		static int idxs;
		int idx;
		std::string s;
	public:
		A() : s("�θ�") { idx = idxs++; std::cout << "�θ�Ŭ����������\n"; };
		virtual void What() { std::cout << s << '\n'; }
		virtual ostream& Print(std::ostream& out) const
		{
			return out << "AŬ����:" << idx;
		}
		friend ostream& operator<<(std::ostream& out, const A& _a)
		{
			return _a.Print(out);
		}
	};
	class B : public A
	{
	public:
		B()
		{ 
			idx = idxs++;
			s = "�ڽ�";
			std::cout << "�ڽ�Ŭ����������\n"; 
		}
		virtual void What()
		{
			std::cout << "�����ǵ��Լ� " << s << '\n';
		}
		virtual ostream& Print(std::ostream& out) const
		{
			return out << "BŬ����:" << idx;
		}
	};
	
	class PDLists
	{
		int maximumsizes;
		int cnts;
		A** cntLists;
	public:
		PDLists(int _sizes) : maximumsizes(_sizes)
		{
			cntLists = new A * [maximumsizes];
			cnts = 0;
		}
		~PDLists()
		{
			for (int i = 0; i < cnts; i++)
				delete cntLists[i];
			delete[] cntLists;
		}
		void AddLists(A* instanceA)
		{
			cntLists[cnts++] = instanceA;
		}
		void PrintLists()
		{
			for (int i = 0; i < cnts; i++)
			{
				std::cout << *cntLists[i] << ' ';
			}
		}
	};
	int A::idxs = 0;

	void Exam()
	{
		PDLists lists(10);
		lists.AddLists(new A);
		lists.AddLists(new B);
		lists.AddLists(new A);
		lists.AddLists(new B);
		lists.AddLists(new A);
		lists.PrintLists();
	}
}
void Exam()
{
	std::string a = "abc";
	std::cout << a.length();
	if (a._Equal("abc"))
	{
		std::cout << "isequal";
	}
}