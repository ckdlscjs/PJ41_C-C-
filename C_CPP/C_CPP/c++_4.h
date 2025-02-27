
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
		std::cout << "Func4생성자" << '\n';
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
		// 점 100 개를 보관하는 배열.
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

		// 모든 점들 간의 거리를 출력하는 함수 입니다.
		/*
		std::cout << arr[0]->x << std::endl;            // 가장 간단한 표현
		std::cout << (*arr[0]).x << std::endl;          // ->를 사용하지 않음
		std::cout << (*(*(arr + 0))).x << std::endl;    // 완전히 풀어 쓴 형태
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

		// 모든 점들을 잇는 직선들 간의 교점의 수를 출력해주는 함수 입니다.
		// 참고적으로 임의의 두 점을 잇는 직선의 방정식을 f(x,y) = ax+by+c = 0
		// 이라고 할 때 임의의 다른 두 점 (x1, y1) 과 (x2, y2) 가 f(x,y)=0 을 기준으로
		// 서로 다른 부분에 있을 조건은 f(x1, y1) * f(x2, y2) <= 0 이면 됩니다.
		
		/*
		* 직선의방정식1,직선의방정식2 두가지 직선을 기준으로 두 직선이 접점이 있으면 갯수를1증가한다
		*/
		void PrintNumMeets() {
			int meet_count = 0; // 교점의 개수
			std::set<std::pair<int, int>> unique_intersections;

			for (int i = 0; i < num_points; ++i) {
				for (int j = i + 1; j < num_points; ++j) {
					// 첫 번째 직선 정의 (점 i, 점 j)
					int a1 = pa[j]->y - pa[i]->y;
					int b1 = pa[i]->x - pa[j]->x;
					int c1 = pa[i]->y * (pa[j]->x - pa[i]->x) - pa[i]->x * (pa[j]->y - pa[i]->y);

					for (int k = 0; k < num_points; ++k) {
						for (int l = k + 1; l < num_points; ++l) {
							if (i == k && j == l) continue; // 같은 직선은 건너뜀

							// 두 번째 직선 정의 (점 k, 점 l)
							int a2 = pa[l]->y - pa[k]->y;
							int b2 = pa[k]->x - pa[l]->x;
							int c2 = pa[k]->y * (pa[l]->x - pa[k]->x) - pa[k]->x * (pa[l]->y - pa[k]->y);

							// 두 직선의 determinant로 교차 여부 확인
							int determinant = a1 * b2 - a2 * b1; // ad - bc 행렬식
							if (determinant != 0) { // 교점 존재
								// 교차점 계산
								int x_intersection = (b1 * c2 - b2 * c1) / determinant;
								int y_intersection = (a2 * c1 - a1 * c2) / determinant;

								// 교차점을 set에 추가하여 중복 제거
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
		//초기화리스트를 사용해야 상수(const)나 레퍼런스변수(&)를 초기화 가능하다, 생성과동시에초기화되는것
		Marine() : hp(50), y(0), x(0), damage(5), is_dead(false) { idx = midx++; }
		Marine(int _y, int _x) : hp(50), y(_y), x(_x), damage(5), is_dead(false) { idx = midx++; }
		Marine(const char* _name, int _y, int _x) : hp(50), y(_y), x(_x), damage(5), is_dead(false)
		{
			name = new char[std::strlen(_name) + 1]; //마지막\0의 길이는 빼기때문에 추가해줘야함
			strcpy(name, _name);
			idx = midx++;
		}
		//const로 받았으므로 원본객체를 건들 수 없다
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
				delete[] name; //소멸자에서 동적할당한 name이 있다면 삭제시킨다.
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
	int Marine::midx = 1; //static 정적변수는 밖에서 초기화해줘야한다.
}

namespace CopyConstructExam
{
	class A {
		int x;

	public:
		A(int c) : x(c) { std::cout << "construct A\n"; }
		A(const A& a) {
			x = a.x;
			std::cout << "복사 생성" << std::endl;
		}
		A& operator=(const A& a)
		{
			std::cout << "복사대입\n";
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
		A a1 = b.get_A(); //RVO, 복사생성자가한번만호출됨
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
		//문자하나로부터생성
		MyString(const char c);
		//문자열로부터생성
		MyString(const char* _str);
		//복사생성자
		MyString(const MyString& _str);
		//소멸자
		~MyString();
		
	public:
		//const로호출
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
		std::cout << "소멸자호출\n";
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

		str3.Insert(0, 'Z'); //임시객체 소멸자가호출
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

		/*explict 키워드 -> 묵시적 형변환을 막는다, 복사생성자등 컴파일러가 임의로 해석해 맞는 함수호출하는것을 방지*/
		/*mutable 키워드 -> 변수앞에 선언되면 const함수내부에서 해당 변수는 변환이가능하다, const로 선언해야하는 함수내부에서 변경해야할 유연함을 제공*/
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
	* 오버로딩의 형변환 과정
	* 1.적합한 인자가 맞는 함수를 찾는다
	* 
	* 2.정확히 일치하는 타입이 없을경우 형변환을 통해 일치하는 함수를 찾는다
	* 2_1. char unsigned char, short 는 int로변환된다
	* 2_2. unsigned short 는 int의 크기에 따라 int 혹은 unsigned int로 변환된다
	* 2_3. float는 double로 변환된다
	* 2_4. Enum은 int로 변환된다
	* 
	* 3.해당사항이 없다면 추가로 좀더 포괄적인 형변환을 통해 일치하는 함수를 찾는다
	* 3_1. 임의의숫자(Numeric)타입은 다른 숫자타입으로 변환된다 (ex. float -> int)
	* 3_2. Enum또한 임의의 숫자 타입으로 변환된다 (ex. Enum -> double)
	* 3_3. 0은 포인터타입<->숫자타입 양측을 오가며 체크
	* 3_4. 포인터는 void포인터로 변환된다
	* 
	* 4.직접 정의한 타입변환으로 일치하는것을 찾는다.
	* 
	* 위의과정들을 통해서 일치하는 함수를 찾을 수 없거나 같은단계에서 두개이상 겹치는 경우 모호(ambiguous)에러를 발생시킨다
	*/

	Func4Check func; //생성자호출, ()->함수호출이되버림, 모호한구문을 함수선언으로 우석 해석하는 좌측우선파싱(left-to-right parsing)때문, 함수선언(정의)가되어버림
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
	std::cout << "마린1이 마린2를 공격\n";
	marine1.Attack(marine2);
	marine1.Show();
	marine2.Show();

	Starcraft::Marine marine3 = marine2; //복사생성자
	
	marine3.Show();
	//marine3 = marine1; //복사, marine3이 marine1을 가리키게끔한다.
	marine3.Show();

	CopyConstructExam::funcExam();
	*/
	MyString::funcExam();
}

