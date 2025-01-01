#pragma once
#include "std.h"
namespace MyString5
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
		bool operator==(const MyString& _str);
		char& operator[](const int idx) const;
		friend ostream& operator<<(std::ostream& out, const MyString& _str)
		{
			return out << _str.str;
		}
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
		std::cout << str << " �� �Ҹ���ȣ��\n";
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
	bool MyString::MyString::operator==(const MyString& _str)
	{
		if (len != _str.Size()) return false;
		for (int i = 0; i < len; i++)
			if (str[i] != _str.At(i)) return false;
		return true;
	}
	char& MyString::MyString::operator[](const int idx) const
	{
		return str[idx];
	}
	void Exam()
	{
		MyString str1("Check1");
		MyString str2 = str1;
		str2.Assign("Check2");
		std::cout << (str1 == str2 ? 1 : 0) << '\n';
		MyString str3("abcdef");
		str3[3] = 'c';
		std::cout << str3 << '\n';
	}
}

namespace Complex
{
	//��� Ŭ���� z = a + bi;
	class Complex
	{
	private:
		double real, img; //�Ǽ���, �����

	private:
		double GetNumber(const char* _str, int begin, int end)
		{
			double ret = 0.0f;
			double decimal_after = 1.0f;
			int minus = 1;
			bool is_int = true;
			for (begin; begin <= end; begin++)
			{
				if (_str[begin] == ' ' || _str[begin] == '+')
					continue;
				else if (_str[begin] == '-')
				{
					minus = -1;
					continue;
				}
				else if (_str[begin] == '.')
				{
					is_int = false;
					continue;
				}
				else if (is_int)
				{
					ret *= 10.0f;
					ret += (_str[begin] - '0');
				}
				else
				{
					decimal_after *= 0.1f;
					ret += (_str[begin] - '0') * decimal_after;
				}
			}
			return ret * minus;
		}
	public:
		Complex(double _real, double _img) : real(_real), img(_img) {}
		Complex(const char* _str)
		{
			//_str -> ��ȣ, �Ǽ���, ��ȣ, ����� i
			int begin = 0, end = std::strlen(_str), pos_oper = -1;
			bool is_i = _str[end - 1] == 'i';
			for (int i = end - 1; i >= begin; i--)
			{
				if (_str[i] == '+' || _str[i] == '-')
				{
					pos_oper = i;
					break;
				}
			}
			if (!is_i)
			{
				real = GetNumber(_str, begin, end - 1);
			}
			else
			{
				if (pos_oper > 0)
				{
					real = GetNumber(_str, begin, pos_oper - 1);
					img = GetNumber(_str, pos_oper, end - 2);
				}
				else
				{
					img = GetNumber(_str, pos_oper, end - 2);
				}
			}
		}
		Complex(const Complex& c) : real(c.real), img(c.img) {} //���������
		//������ ���� ������ �ʿ� ���� ���ο� �ǿ����ڸ� ������ �����ϹǷ� const�� �����Ѵ�
		/*
		* �ڱ��ڽ��� ��ȯ�ϴ� ���״��԰��õ� �����ڵ��� ����Լ���, �Ϲ� �����ڴ� friend�� �̿��Ѵ�.
		Complex operator+(const Complex& c) const
		{
			return Complex(real + c.real, img + c.img);
		}
		Complex operator-(const Complex& c) const
		{
			return Complex(real - c.real, img - c.img);
		}
		Complex operator*(const Complex& c) const
		{
			return Complex(real*c.real - img*c.img, real * c.img + img * c.real); // (a1a2 - b1b2) + (a1b2 + a2b1)i
		}
		Complex operator/(const Complex& c) const // ((a1a2 + b1b2) + (b1a2 - a1b2)i)  / (a2^2 + b2^2)
		{
			return Complex((real * c.real + img * c.img)  / (c.real*c.real + c.img * c.img), (img * c.real- real * c.img) / (c.real * c.real + c.img * c.img));
		}
		*/
		Complex& operator=(const Complex& c)
		{
			real = c.real;
			img = c.img;
			return *this;
		}
		Complex& operator+=(const Complex& c) 
		{
			*this = *this + c;
			return *this;
		}
		Complex& operator-=(const Complex& c) 
		{
			*this = *this - c;
			return *this;
		}
		Complex& operator*=(const Complex& c)
		{
			*this = *this * c;
			return *this;
		}
		Complex& operator/=(const Complex& c)
		{
			*this = *this / c;
			return *this;
		}
		/*
		* //�����Ϸ����� �����ڸ� �̿��ؼ� �˾Ƽ� ����ȯ���ش� ��
		* a = a.operator+(Complex("-1.1 + 3.923i")); �� ó���ȴ�
		Complex operator+(const char* _str)
		{
			return *this + Complex(_str);
		}
		Complex operator-(const char* _str)
		{
			return *this - Complex(_str);
		}
		Complex operator*(const char* _str)
		{
			return *this * Complex(_str);
		}
		Complex operator/(const char* _str)
		{
			return *this / Complex(_str);
		}
		*/
		friend ostream& operator<<(std::ostream& out, const Complex& c) //��¿����� �����ε�
		{
			out << '(' << c.real << ", " << c.img << ')';
			return out;
		}
		friend Complex operator+(const Complex& a, const Complex& b)
		{
			return Complex(a.real + b.real, a.img + b.img);
		}
		friend Complex operator-(const Complex& a, const Complex& b)
		{
			return Complex(a.real - b.real, a.img - b.img);
		}
		friend Complex operator*(const Complex& a, const Complex& b)
		{
			return Complex(a.real * b.real - a.img * b.img, a.real * b.img + a.img * b.real); // (a1a2 - b1b2) + (a1b2 + a2b1)i
		}
		friend Complex operator/(const Complex& a, const Complex& b)
		{
			return Complex((a.real * b.real + a.img * b.img) / (b.real * b.real + b.img * b.img), (a.img * b.real - a.real * b.img) / (b.real * b.real + b.img * b.img));
		}
	};
	/*
	Complex operator+(const Complex& a, const Complex& b)
	{
		
	}
	Complex operator+(const Complex& a, const Complex& b)
	{
		return Complex(a.real + b.real, a.img + b.img);
	}
	Complex operator+(const Complex& a, const Complex& b)
	{
		return Complex(a.real + b.real, a.img + b.img);
	}
	Complex operator+(const Complex& a, const Complex& b)
	{
		return Complex(a.real + b.real, a.img + b.img);
	}
	*/
	class A
	{
	private:
		void private_func() {}
		int private_num;

		friend class B; //B -> A������ ����, A -> B �Ұ���
		friend void func(); //�ܺ��Լ� func���� AŬ������ ���ڿ� ������ ����Ѵ�
	};
	class B
	{
	public:
		void b()
		{
			A a;
			a.private_func();
			a.private_num = 2;
		}
	};
	void func()
	{
		A a;
		a.private_func();
		a.private_num = 3;
	}
	void Exam()
	{
		/*
		Complex a(1.0f, 2.0f);
		Complex b(3.0f, -2.0f);
		
		Complex c(0.0f, 0.0f); //c = �ÿ� ��������ڰ� ȣ���
		c = a * b + a / b + a + b; //���Կ����ڰ� ȣ���
		
		a += b;
		std::cout << a << '\n';
		std::cout << b << '\n';
		std::cout << b + "-4-3.2i" << '\n';
		Complex c(0, 0);
		std::cout << Complex("-0.5-3.7i") << '\n';
		std::cout << c + "-1.1 + 3.923i";
		*/
		Complex a(0, 0);
		a = "-1.1 + 3.923i" + a;
		a = a + a;
		std::cout << a;
	}
}

namespace Wrapper
{
	class Int
	{
		int data;
		// some other data

	public:
		Int(int data) : data(data) {} //�⺻������
		Int(const Int& i) : data(i.data) {} //���������
		operator int() //int�� ����ȯ, 
		{ 
			return data; 
		} 
	};
	class Test
	{
		int data;
		// some other data

	public:
		Test(int data) : data(data) {} //�⺻������
		Test(const Test& i) : data(i.data) {} //���������
		Test& operator++() //�������������ڴ� ���ڰ� ����
		{
			data++;
			std::cout << "��������������!\n";
			return *this;
		}
		Test& operator++(int) //�������������ڴ� ���ڰ� ����
		{
			data++;
			std::cout << "��������������!\n";
			return *this;
		}
	};
	void Exam()
	{
		Int x = 3;
		Int x2 = x + 4;
		x2 = x * 2 + x + 4;
		std::cout << x2;
		Test tes = 3;
		++tes;
	}
}

namespace NDimension
{
	class Array
	{
		struct Address
		{
			//0����~n-1����, n-1������ ���� �����͹迭�� ����Ų��
			int level;
			//���������� �����ּҸ� ����Ű�� ������, �Ǹ������� ���� �����͸� ����Ų��
			void* next;
		};
		//��� ���� �����°�
		const int dim;
		//�ش� ���� ��� �迭�� �����ϴ°�
		int* size;
		//top�ּҸ� ����Ű�� ������(��Ʈ)
		Address* root;
	public:
		Array(int _dim, int* _sizes) : dim(_dim)
		{
			size = new int[dim];
			std::memcpy(size, _sizes, sizeof(size));
		}
	};
}