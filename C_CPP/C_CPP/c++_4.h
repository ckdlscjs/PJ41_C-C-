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
namespace funcPointGeo
{
	class Point {
		int x, y;

	public:
		Point(int pos_x, int pos_y);
		Point(const Point& point);
	};
	funcPointGeo::Point::Point(int pos_x, int pos_y)
	{
		x = pos_x;
		y = pos_y;
	}
	funcPointGeo::Point::Point(const Point& point)
	{
		x = point.x;
		y = point.y;
	}


	class Geometry {
	public:
		Geometry() {
			num_points = 0;
		}

		void AddPoint(const Point& point) {
			point_array[num_points++] = new Point(point);
		}

		// ��� ���� ���� �Ÿ��� ����ϴ� �Լ� �Դϴ�.
		void PrintDistance();

		// ��� ������ �մ� ������ ���� ������ ���� ������ִ� �Լ� �Դϴ�.
		// ���������� ������ �� ���� �մ� ������ �������� f(x,y) = ax+by+c = 0
		// �̶�� �� �� ������ �ٸ� �� �� (x1, y1) �� (x2, y2) �� f(x,y)=0 �� ��������
		// ���� �ٸ� �κп� ���� ������ f(x1, y1) * f(x2, y2) <= 0 �̸� �˴ϴ�.
		void PrintNumMeets();

	private:
		// �� 100 ���� �����ϴ� �迭.
		Point* point_array[100];
		int num_points;
	};
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
}

