
#pragma once
#include "std.h"
void func4Print(int x)
{
	std::cout << "int : " << x << '\n';
}
void func4Print(char x)
{
	std::cout << "char : " << x << '\n';
}
void func4Print(double x)
{
	std::cout << "double : " << x << '\n';
}

class Func4Check
{
public:
	Func4Check()
	{
		std::cout << "Func4������" << '\n';
	}
};
namespace PointGeo
{
	double GetDistance(int x1, int y1, int x2, int y2)
	{
		return std::sqrt(std::pow(x1 - y1, 2) + std::pow(x2 - y2, 2));
	}
	class Point {
		friend class Geometry;
		int x, y;

	public:
		Point(int pos_x, int pos_y);
		Point(const Point& point);
	};
	PointGeo::Point::Point(int pos_x, int pos_y)
	{
		x = pos_x;
		y = pos_y;
	}
	PointGeo::Point::Point(const Point& point)
	{
		x = point.x;
		y = point.y;
	}


	class Geometry {
	private:
		// �� 100 ���� �����ϴ� �迭.
		Point* pa[100];
		int num_points = 0;
	public:
		Geometry() {
			std::memset(pa, NULL, sizeof(pa));
			num_points = 0;
		}
		~Geometry()
		{
			for (int i = 0; i < num_points; i++)
				delete pa[i];
		}
		void AddPoint(const Point& point) {
			pa[num_points++] = new Point(point.x, point.y);
		}

		// ��� ���� ���� �Ÿ��� ����ϴ� �Լ� �Դϴ�.
		/*
		std::cout << arr[0]->x << std::endl;            // ���� ������ ǥ��
		std::cout << (*arr[0]).x << std::endl;          // ->�� ������� ����
		std::cout << (*(*(arr + 0))).x << std::endl;    // ������ Ǯ�� �� ����
		*/
		void PrintDistance()
		{
			std::cout << "-----printDist-----\n";
			for (int i = 0; i < num_points; i++)
			{
				for (int j = i + 1; j < num_points; j++)
				{
					std::cout << pa[i]->x << ", " << (*(*(pa + i))).y << " to " << pa[j]->x << ", " << pa[j]->y << " : " << GetDistance(pa[i]->x, pa[i]->y, pa[j]->x, pa[j]->y) << '\n';
				}
			}
			std::cout << "-------------------\n";
		}

		// ��� ������ �մ� ������ ���� ������ ���� ������ִ� �Լ� �Դϴ�.
		// ���������� ������ �� ���� �մ� ������ �������� f(x,y) = ax+by+c = 0
		// �̶�� �� �� ������ �ٸ� �� �� (x1, y1) �� (x2, y2) �� f(x,y)=0 �� ��������
		// ���� �ٸ� �κп� ���� ������ f(x1, y1) * f(x2, y2) <= 0 �̸� �˴ϴ�.
		
		/*
		* �����ǹ�����1,�����ǹ�����2 �ΰ��� ������ �������� �� ������ ������ ������ ������1�����Ѵ�
		*/
		void PrintNumMeets() {
			int meet_count = 0; // ������ ����
			std::set<std::pair<int, int>> unique_intersections;

			for (int i = 0; i < num_points; ++i) {
				for (int j = i + 1; j < num_points; ++j) {
					// ù ��° ���� ���� (�� i, �� j)
					int a1 = pa[j]->y - pa[i]->y;
					int b1 = pa[i]->x - pa[j]->x;
					int c1 = pa[i]->y * (pa[j]->x - pa[i]->x) - pa[i]->x * (pa[j]->y - pa[i]->y);

					for (int k = 0; k < num_points; ++k) {
						for (int l = k + 1; l < num_points; ++l) {
							if (i == k && j == l) continue; // ���� ������ �ǳʶ�

							// �� ��° ���� ���� (�� k, �� l)
							int a2 = pa[l]->y - pa[k]->y;
							int b2 = pa[k]->x - pa[l]->x;
							int c2 = pa[k]->y * (pa[l]->x - pa[k]->x) - pa[k]->x * (pa[l]->y - pa[k]->y);

							// �� ������ determinant�� ���� ���� Ȯ��
							int determinant = a1 * b2 - a2 * b1; // ad - bc ��Ľ�
							if (determinant != 0) { // ���� ����
								// ������ ���
								int x_intersection = (b1 * c2 - b2 * c1) / determinant;
								int y_intersection = (a2 * c1 - a1 * c2) / determinant;

								// �������� set�� �߰��Ͽ� �ߺ� ����
								unique_intersections.insert({ x_intersection, y_intersection });
							}
						}
					}
				}
			}

			std::cout << "Number of unique intersection points: " << unique_intersections.size() << std::endl;
		}
	};
}

namespace Starcraft
{

	class Marine
	{
	private:
		static int midx;
		char* name;
		int idx;
		int hp;
		int y;
		int x;
		int damage;
		bool is_dead;
	public:
		//�ʱ�ȭ����Ʈ�� ����ؾ� ���(const)�� ���۷�������(&)�� �ʱ�ȭ �����ϴ�, ���������ÿ��ʱ�ȭ�Ǵ°�
		Marine() : hp(50), y(0), x(0), damage(5), is_dead(false) { idx = midx++; }
		Marine(int _y, int _x) : hp(50), y(_y), x(_x), damage(5), is_dead(false) { idx = midx++; }
		Marine(const char* _name, int _y, int _x) : hp(50), y(_y), x(_x), damage(5), is_dead(false)
		{
			name = new char[std::strlen(_name) + 1]; //������\0�� ���̴� ���⶧���� �߰��������
			strcpy(name, _name);
			idx = midx++;
		}
		//const�� �޾����Ƿ� ������ü�� �ǵ� �� ����
		Marine(const Marine& _marine)
		{
			std::cout << "CopyConstructor\n";
			if (_marine.name)
			{
				name = new char[std::strlen(_marine.name)+1]; //deepcopy
				strcpy(name, _marine.name);
			}
			hp = _marine.hp;
			y = _marine.y;
			x = _marine.x;
			damage = _marine.damage;
			idx = midx++;
		}
		~Marine()
		{
			std::cout << "Destruct " << idx << '\n';
			if (name)
			{
				std::cout << idx << " have name\n";
				delete[] name; //�Ҹ��ڿ��� �����Ҵ��� name�� �ִٸ� ������Ų��.
			}
				
		}
		void Move(int _y, int _x)
		{
			y = _y;
			x = _x;
		}
		void Dead()
		{
			is_dead = true;
			std::cout << "Marine " << idx << " is dead! \n";
		}
		void Damaged(int _damage)
		{
			hp -= _damage;
			if (hp <= 0)
				Dead();
		}
		void Attack(Marine& target)
		{
			target.Damaged(damage);
		}
		void Show()
		{
			if(name != nullptr)
				std::cout << "Marine " << idx << ", " << name << '\n';
			else
				std::cout << "Marine " << idx << '\n';
			std::cout << y << ", " << x << '\n';
			std::cout << hp << '\n';
			std::cout << "-----------------\n";
		}
	};
	int Marine::midx = 1; //static ���������� �ۿ��� �ʱ�ȭ������Ѵ�.
}

namespace CopyConstructExam
{
	class A {
		int x;

	public:
		A(int c) : x(c) { std::cout << "construct A\n"; }
		A(const A& a) {
			x = a.x;
			std::cout << "���� ����" << std::endl;
		}
		A& operator=(const A& a)
		{
			std::cout << "�������\n";
			return *this;
		}
	};


	class B {
		A a; 

	public:
		B(int c) : a(c) { std::cout << "construct B\n"; } 
		B(const B& b) : a(b.a) {}
		A get_A() {
			A temp(a);
			return temp; 
		}
	};

	void funcExam()
	{
		B b(10); //construc1

		std::cout << "---------" << std::endl;
		A a1 = b.get_A(); //RVO, ��������ڰ��ѹ���ȣ���
	}
}

namespace MyString
{
	class MyString
	{
	private:
		char* str;
		int len;
	public:
		//�����ϳ��κ��ͻ���
		MyString(const char c);
		//���ڿ��κ��ͻ���
		MyString(const char* _str);
		//���������
		MyString(const MyString& _str);
		//�Ҹ���
		~MyString();
		
	public:
		//const��ȣ��
		int Size() const;
		void Print() const;
		MyString& Assign(const char* _str);
		MyString& Assign(const MyString& _str);
		char At(int idx) const;
		MyString& Insert(int loc, const MyString& _str);
		MyString& Insert(int loc, const char* _str);
		MyString& Insert(int loc, char c);
		MyString& Erase(int loc, int num);
		int Find(const MyString& _str) const;
		int Find(const char* _str) const;
		int Find(char _c) const;
	};
	MyString::MyString::MyString(const char c)
	{
		str = new char[2];
		str[0] = c;
		str[1] = '\0';
		len = 1;
	}
	MyString::MyString::MyString(const char* _str)
	{
		len = 0;
		while (*(_str + len) != '\0') len++;
		str = new char[len + 1];
		for (int i = 0; i < len; i++)
			str[i] = _str[i];
		str[len] = '\0';
	}
	MyString::MyString::MyString(const MyString& _str)
	{
		len = _str.Size();
		str = new char[len + 1];
		for (int i = 0; i < len; i++)
			str[i] = _str.str[i];
		str[len] = '\0';
	}
	MyString::MyString::~MyString()
	{
		std::cout << "�Ҹ���ȣ��\n";
		delete[] str;
	}
	int MyString::MyString::Size() const
	{
		return len;
	}
	void MyString::MyString::Print() const
	{
		std::cout << str << '\n';
	}
	MyString& MyString::MyString::Assign(const char* _str)
	{
		delete[] str;
		len = 0;
		while (_str[len] != '\0') len++;
		str = new char[len + 1];
		for (int i = 0; i < len; i++)
			str[i] = _str[i];
		str[len] = '\0';
		return *this;
	}
	MyString& MyString::MyString::Assign(const MyString& _str)
	{
		delete[] str;
		len = _str.Size();
		str = new char[len + 1];
		for (int i = 0; i < len; i++)
			str[i] = _str.str[i];
		str[len] = '\0';
		return *this;
	}
	char MyString::MyString::At(int idx) const
	{
		if (idx < 0 || idx >= len) return NULL;
		return str[idx];
	}
	MyString& MyString::MyString::Insert(int loc, const MyString& _str)
	{
		if (loc < 0) return *this;
		if (len < loc) loc = len;
		int _len = len + _str.Size();
		char* temp = new char[_len + 1];
		int idx = 0;
		for (idx = 0; idx < loc; idx++)
			temp[idx] = str[idx];
		for (int i = 0; i < _str.Size(); i++)
			temp[idx++] = _str.str[i];
		for (int i = loc; i < len; i++)
			temp[idx++] = str[i];
		temp[_len] = '\0';
		delete[] str;
		str = temp;
		len = _len;
		return *this;
	}
	MyString& MyString::MyString::Insert(int loc, const char* _str)
	{
		return this->Insert(loc, MyString(_str));
	}
	MyString& MyString::MyString::Insert(int loc, char c)
	{
		return this->Insert(loc, MyString(c));
	}
	MyString& MyString::MyString::Erase(int loc, int num)
	{
		if (num < 0 || loc < 0 || loc > len || num > len) return *this;
		for (int i = loc + num; i < len; i++)
			str[i - num] = str[i];
		len -= num;
		str[len] = '\0';
		return *this;
	}
	int MyString::MyString::Find(const MyString& _str) const
	{
		if (_str.Size() <= 0) return -1;
		if (_str.Size() > len) return -1;
		for (int i = 0; i <= len - _str.Size(); i++)
		{
			int j;
			for (j = 0; j < _str.Size(); j++)
				if (str[i + j] != _str.str[j]) break;
			if (j == _str.Size()) return i;
		}
		return -1;
	}
	int MyString::MyString::Find(const char* _str) const
	{
		return Find(MyString(_str));
	}
	int MyString::MyString::Find(char _c) const
	{
		return Find(MyString(_c));
	}

	void funcExam()
	{
		/*
		MyString str1('A');
		str1.Print();

		MyString str2("Hello World!");
		str2.Print();

		MyString str3 = str2.Assign("New World!!");;
		str3.Print();
		
		str2.Assign(" Change");
		str2.Print();

		str3.Insert(3, str2); 
		str3.Print();

		str3.Insert(0, 'Z'); //�ӽð�ü �Ҹ��ڰ�ȣ��
		str3.Print();
		
		MyString str4("abc");
		str4.Insert(1, 'd');
		str4.Print();
		*/
		MyString str1("very long string");
		MyString str2("<some string inserted between>");
		std::cout << str1.Size() << '\n';
		str1.Print();
		std::cout << str1.Find("long") << '\n';
		str1.Insert(5, str2);
		str1.Print();

		str1.Erase(2, 2);
		str1.Print();

		str1.Erase(0, 33);
		str1.Print();
		std::cout << str1.Find("str") << '\n';
	}
}

void func4()
{
	int a = 1;
	char b = 'c';
	double c = 3.2f;
	func4Print(a);
	func4Print(b);
	func4Print(c);
	/*
	* �����ε��� ����ȯ ����
	* 1.������ ���ڰ� �´� �Լ��� ã�´�
	* 
	* 2.��Ȯ�� ��ġ�ϴ� Ÿ���� ������� ����ȯ�� ���� ��ġ�ϴ� �Լ��� ã�´�
	* 2_1. char unsigned char, short �� int�κ�ȯ�ȴ�
	* 2_2. unsigned short �� int�� ũ�⿡ ���� int Ȥ�� unsigned int�� ��ȯ�ȴ�
	* 2_3. float�� double�� ��ȯ�ȴ�
	* 2_4. Enum�� int�� ��ȯ�ȴ�
	* 
	* 3.�ش������ ���ٸ� �߰��� ���� �������� ����ȯ�� ���� ��ġ�ϴ� �Լ��� ã�´�
	* 3_1. �����Ǽ���(Numeric)Ÿ���� �ٸ� ����Ÿ������ ��ȯ�ȴ� (ex. float -> int)
	* 3_2. Enum���� ������ ���� Ÿ������ ��ȯ�ȴ� (ex. Enum -> double)
	* 3_3. 0�� ������Ÿ��<->����Ÿ�� ������ ������ üũ
	* 3_4. �����ʹ� void�����ͷ� ��ȯ�ȴ�
	* 
	* 4.���� ������ Ÿ�Ժ�ȯ���� ��ġ�ϴ°��� ã�´�.
	* 
	* ���ǰ������� ���ؼ� ��ġ�ϴ� �Լ��� ã�� �� ���ų� �����ܰ迡�� �ΰ��̻� ��ġ�� ��� ��ȣ(ambiguous)������ �߻���Ų��
	*/

	Func4Check func; //������ȣ��, ()->�Լ�ȣ���̵ǹ���, ��ȣ�ѱ����� �Լ��������� �켮 �ؼ��ϴ� �����켱�Ľ�(left-to-right parsing)����, �Լ�����(����)���Ǿ����
	Func4Check func2 = Func4Check();

	/*
	PointGeo::Geometry geometry;
	geometry.AddPoint(PointGeo::Point(0, 0));
	geometry.AddPoint(PointGeo::Point(0, 1));
	geometry.AddPoint(PointGeo::Point(0, 2));
	geometry.AddPoint(PointGeo::Point(1, 2));
	geometry.PrintDistance();
	geometry.PrintNumMeets();

	std::cout << "\n4_3----------------------------\n";

	Starcraft::Marine marine1(2, 3);
	Starcraft::Marine marine2("nameMarine2", 3, 5);

	marine1.Show();
	marine2.Show();
	std::cout << "����1�� ����2�� ����\n";
	marine1.Attack(marine2);
	marine1.Show();
	marine2.Show();

	Starcraft::Marine marine3 = marine2; //���������
	
	marine3.Show();
	//marine3 = marine1; //����, marine3�� marine1�� ����Ű�Բ��Ѵ�.
	marine3.Show();

	CopyConstructExam::funcExam();
	*/
	MyString::funcExam();
}

