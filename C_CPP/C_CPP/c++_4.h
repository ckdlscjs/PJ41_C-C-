
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
	int Marine::midx = 1;
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
}

