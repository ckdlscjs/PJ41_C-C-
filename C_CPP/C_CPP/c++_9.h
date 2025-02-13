#pragma once
#include "std.h"
namespace ch9
{
	template<typename T> //Ŭ�������ø��� ���ڸ� �����ؼ� ���� �ڵ带 �����ϴ°�, Ŭ�������ø��ν��Ͻ�ȭ, ���� ��ü�� �������� ������ �ڵ�� ��ȯ�����ʴ´�.
	class Vector
	{
	private:
		T* data;
		int capacity;
		int length;
		
	public:
		Vector(int _size = 1) : data(new T[_size]), capacity(_size), length(0) {}
		~Vector()
		{
			if(data)
				delete[] data;
		}
		void Push_Back(T t) 
		{
			if (capacity <= length)
			{
				capacity *= 2;//����2��Ȯ��
				T* temp = new T[capacity];
				for (int i = 0; i < length; i++) temp[i] = data[i];
				delete[] data;
				data = temp;
			}
			data[length] = t;
			length++;
		}

		T& operator[](int i)
		{
			return data[i];
		}
		void Remove(int i)
		{
			for (int idx = i + 1; idx < length; idx++) data[idx - 1] = data[idx];
			length--;
		}
		int Size()
		{
			return length;
		}
		void Swap(int i, int j)
		{
			T temp = data[i];
			data[i] = data[j];
			data[j] = temp;
		}
	};
	
	//Ư�� Ÿ�Կ� ���ؼ� ���� ó���� ���ִ°��� ���ø�Ư��ȭ ��� �Ѵ�, ���޵Ǵ� ���ø� ���ڰ� ���� ���� ���ø����� �Ͻ��ϱ����� template<> ���ʼ�
	//bool�� int��(32��)�� ǥ���Ͽ� 1��Ʈ���� ǥ���ϱ����� 1���� int�������� 32��¥�� ũ��� �����Ѵ�. �� 32���� ��Ʈ �ȿ� ���° ��Ʈ�� ����ϰ� �̸� ���.
	class BoolRef //bool�� ��ȯ���ֱ����� Proxy����(�븮��ü)
	{
	private:
		unsigned int& ref;
		int pos;
	public:
		BoolRef(unsigned int& _ref, int _pos) : ref(_ref), pos(_pos) {}
		operator bool()
		{
			return (ref & (1 << pos)) ? true : false;
		}
		BoolRef& operator=(bool tf)
		{
			if (tf)
				ref |= (1 << pos);
			else
				ref &= ~(1 << pos);
			return *this;
		}
		friend class Vector<bool>;
	};
	template<>
	class Vector<bool>
	{
	private:
		unsigned int* data;
		int capacity;
		int length;

	public:
		Vector(int _size = 1) : data(new unsigned int[_size/32 + 1]), capacity(_size/32 + 1), length(0) 
		{
			//length�� ���� �� ��Ʈ�� ������ ��Ͻ�Ų��.
			for (int i = 0; i < capacity; i++) data[i] = 0; //������/32 ��ŭ 0�����ʱ�ȭ, 32������ 1����unsigned int
		}
		~Vector()
		{
			if (data)
				delete[] data;
		}
		void Push_Back(bool b)
		{
			if (capacity*32 <= length)
			{
				unsigned int*  temp = new unsigned int[capacity*2];
				for (int i = 0; i < capacity; i++) temp[i] = data[i];
				for (int i = capacity; i < capacity * 2; i++) temp[i] = 0;
				delete[] data;
				data = temp;
				capacity *= 2;
			}
			if (b)
				data[length / 32] |= (1 << (length % 32));
			length++;
		}
		BoolRef operator[](int i)
		{
			return BoolRef(data[i / 32], i % 32);
		}
		void Remove(int pos)
		{
			for (int i = pos + 1; i < length; i++)
			{
				int prev = i - 1;
				int cur = i;
				
				//�����Ʈ�� 1�̶��
				if (data[cur / 32] & (1 << (cur % 32)))
					data[prev / 32] |= (1 << (prev % 32));
				else
					data[prev / 32] &= ~(1 << (prev % 32));
			}
			length--;
		}
		int Size() { return length; }

	};
	

	void Exam()
	{
		Vector<int> int_vec;
		int_vec.Push_Back(3);
		int_vec.Push_Back(2);

		std::cout << "-------- int vector ----------" << std::endl;
		std::cout << "ù��° ���� : " << int_vec[0] << std::endl;
		std::cout << "�ι�° ���� : " << int_vec[1] << std::endl;

		Vector<std::string> str_vec;
		str_vec.Push_Back("hello");
		str_vec.Push_Back("world");
		std::cout << "-------- std::string vector -------" << std::endl;
		std::cout << "ù��° ���� : " << str_vec[0] << std::endl;
		std::cout << "�ι�° ���� : " << str_vec[1] << std::endl;

		Vector<bool> bool_vec;
		bool_vec.Push_Back(true);
		bool_vec.Push_Back(true);
		bool_vec.Push_Back(false);
		bool_vec.Push_Back(false);
		bool_vec.Push_Back(false);
		bool_vec.Push_Back(true);
		bool_vec.Push_Back(false);
		bool_vec.Push_Back(true);
		bool_vec.Push_Back(false);
		bool_vec.Push_Back(true);
		bool_vec.Push_Back(false);
		bool_vec.Push_Back(true);
		bool_vec.Push_Back(false);
		bool_vec.Push_Back(true);
		bool_vec.Push_Back(false);
		bool_vec.Push_Back(true);
		bool_vec.Push_Back(false);

		bool_vec[0] = 0; //�븮��ü�̿��� Ư����Ʈ On/Off����
		bool_vec[1] = 0;
		std::cout << "-------- bool vector ---------" << std::endl;
		for (int i = 0; i < bool_vec.Size(); i++) {
			std::cout << bool_vec[i];
		}
		std::cout << std::endl;
		
	}

	//�Լ����ø�
	template<typename T>
	T Max(const T& a, const T& b) //const �� ����� ���� �� ���� rvalue
	{
		return a > b ? a : b;
	}

	//�Լ���ü(Functor, FuntionObject)
	template <typename Cont, typename Comp>
	void bubble_sort(Cont& cont, Comp comp)
	{
		for (int i = 0; i < cont.Size(); i++)
		{
			for (int j = i + 1; j < cont.Size(); j++)
			{
				if (!comp(cont[i], cont[j]))
				{
					cont.Swap(i, j);
				}
			}
		}
	}
	struct Comp1 //������������
	{
		bool operator()(int a, int b) { return a < b; }
	};

	//Ÿ���� �ƴ� ���ø�����(nonType template arguments)
	//typename���� ���ø����ڰ� �ƴ� ����Ÿ��, ������Ÿ��, enumŸ��, nullptr�� ���ڷ� ����ó�� ���� �� �ִ�
	//������ ����Ʈ��ó�� ���ø�����, �ƱԸ�Ʈ�� �⺻���� ���� �� �� �ִ�
	template <typename T>
	struct Compare 
	{
		bool operator()(const T& a, const T& b) const { return a < b; }
	};

	template <typename T, typename Comp = Compare<T>> //�⺻���ø� ���ڸ� Compare<T>�� ����
	T Min(T a, T b) {
		Comp comp;
		if (comp(a, b)) {
			return a;
		}
		return b;
	}
	void Exam2()
	{
		int a = 10, b = 20;
		std::cout << Max(10, 20) << '\n'; //same Max<int>(a, b), Ư�����ø��� ����Ҷ� �ش� ���ø����ڿ� �������Լ����� ���ǵǾ����� �ʴٸ� �����Ͽ������߻��Ѵ�.

		Vector<int> int_vec;
		int_vec.Push_Back(3);
		int_vec.Push_Back(1);
		int_vec.Push_Back(2);
		int_vec.Push_Back(8);
		int_vec.Push_Back(5);
		int_vec.Push_Back(3);
		bubble_sort(int_vec, Comp1());
		for (int i = 0; i < int_vec.Size(); i++)
			std::cout << int_vec[i] << ' ';
	}
}

namespace Variadic
{
	//c++���� ���ø��� �̿��� �����ǰ����� �޴� �Լ��� ���� �� �� �ִ�

	//������ȣ��� ���ڰ� �Ѱ� �� �̹Ƿ� (5) �� �޾�����
	template<typename T>
	void Print(T t)
	{
		std::cout << t << '\n';
	}
	//ù ȣ��� (1, (2,3,4,5))
	//���� (2, (3,4,5))...�����ȣ��
	template<typename T, typename... Types>
	void Print(T t, Types... args)
	{
		std::cout << t << ", ";
		Print(args...);
	}
	void Exam1()
	{
		Print(1, 2, 3, 4, 5); //�������ڸ� ���� �޴´�
	}

	//������ ������ ���ڿ��� ��ġ���Լ�
	//std::string str = s1 + s2 + s3.. �� s1�� s2�� ���϶� �޸��Ҵ�, ���� s3�����϶��� �޸��Ҵ�, �޸��� �Ҵ�/������ ����� ũ�⶧���� �ѹ��� �Ҵ����� ó���ϴ°� ȿ�����̴�
	//���ڸ� ��ĥ �������� ���ڿ��� �������ڸ� ���ؼ� �ް� �޸��Ҵ��� �ѹ����� �ذ� �� �� ������ �̹Ƿ� ȿ�������� �ذᰡ���ϴ�
	template <typename String>
	std::string Strcat(const String& str)
	{
		return std::string(str);
	}
	//�Ҵ���ü�� +�����ڸ� �̿��ؼ� �߰��� �ӽð�ü������� �ϱ⶧���� �Ҵ�Ƚ����ü�� ������ const char* ���� �޴°� �����ϴ�
	template<typename String, typename... Strings>
	std::string Strcat(const String& str, Strings... args)
	{
		return std::string(str) + Strcat(args...);
	}
	void Exam2()
	{
		std::cout << Strcat("This", " ", "is", " ", std::string("a"), " ", std::string("sentence"));
	}

	//���Ҵ�Ǵ� ������ �ѹ����� �ذ��ϱ����� �̸� ũ�⸦ �� ����ؼ� �ٿ��ش�

	//ũ�⸦ ����ϴ� �Լ�, �����������ø��� �̿��� ��������� ���
	size_t GetStringSize(const char* _str) { return std::strlen(_str); }
	size_t GetStringSize(const std::string& _str) { return _str.size(); }
	template<typename String, typename... Strings>
	size_t GetStringSize(String _str, Strings... strs)
	{
		return GetStringSize(_str) + GetStringSize(strs...);
	}

	//����string�� �������ڷ� �޴� append_str�� �ϳ��� �����ش�, dest_str�� strcat���� reserve���� ũ�⸦ �÷�������.
	void AppendString(std::string& dest_str) { return; }
	template<typename String, typename... Strings>
	void AppendString(std::string& dest_str, const String& append_str, Strings... strs)
	{
		dest_str.append(append_str);
		AppendString(dest_str, strs...);
	}

	template<typename String, typename... Strings>
	std::string Strcat2(String _str, Strings... strs)
	{
		//ũ�⸦ �̸� üũ�س��� ����� ����
		std::string concat_str;
		concat_str.reserve(GetStringSize(_str, strs...));
		
		//�÷����� �� ������ ù ������ �ް� �ش繮����� �̾������
		concat_str = _str;
		AppendString(concat_str, strs...);
		return concat_str;
	}

	void Exam3()
	{
		std::cout << Strcat2(std::string("this"), " ", "is", " ", std::string("a"), " ", std::string("sentence"));
	}
	
	//�������������� �μ�0�϶��� �Լ�
	int SumAll() { return 0; }
	template<typename... Ints>
	int SumAll(int num, Ints... nums)
	{
		return num + SumAll(nums...);
	}

	template<typename... Ints>
	double average(Ints... nums)
	{
		return static_cast<double>(SumAll(nums...)) / sizeof...(nums); //sizeof... ���ø� �������ڸ� �̿��� ������ ������ ����
	}
	
	void Exam4()
	{
		std::cout << average(1, 4, 2, 3, 10);
	}

	//fold�� c++17�̻�, 
	/*
	template<typename... Ints>
	int SumAll(Ints... nums)
	{
		return (... + nums);
	}

	void Exam5()
	{
		std::cout << SumAll(1, 4, 2, 3, 10);
	}
	*/
}

namespace ArrayTest
{
	template<typename T, unsigned int N>
	class Array
	{
	private:
		T data[N]; //���ø����� ���� N������ ���� T�Ͱ��� ������Ÿ�ӿ� �ڵ尡�����ȴ�, �� Array<int, 5> Array<int, 3>�� ���� �ٸ�Ŭ������ ����
	public:
		Array(T (&arr)[N]) //T (&temp)[N] = arr, �� int arr[N]�� ��ġ���ȴ�.
		{
			for (int i = 0; i < N; i++)
				data[i] = arr[i];
		}

		T* GetArray() { return data; }
		unsigned int Size() { return N; }
		void PrintAll()
		{
			for (int i = 0; i < N; i++)
				std::cout << data[i] << ", ";
			std::cout << '\n';
		}
	};
	void Exam()
	{
		int arr[] = { 1, 2, 3 };
		Array<int, 3> Arr(arr);
		Arr.PrintAll();
	}
}

namespace Int
{
	template <int N>
	struct Int 
	{
		static const int num = N; //������Ÿ�ӿ� ���� ���Ѵ�, static �� const
	};

	template <typename T, typename U>
	struct add
	{
		typedef Int<T::num + U::num> result;
	};

	void Exam()
	{
		typedef Int<2> two;
		typedef Int<5> five;
		std::cout << add<two, five>::result::num; //�̹� ���α׷� �������� �����Ͻÿ� 7�� ġȯ�Ǿ��ִ�, �� ������Ÿ�ӿ� �̹� ������ ���������� �ڵ���ü�� ���α׷��� �ϴ°��� ��Ÿ���α׷��� �̶��Ѵ�
	}
}

namespace TMP
{
	template<int N>
	struct Factorial
	{
		static const int result = N * Factorial<N - 1>::result;
	};
	template<>
	struct Factorial<1>
	{
		static const int result = 1;
	};
	void Exam()
	{
		std::cout << Factorial<5>::result; //�̹� �������ϸ鼭 ���� �������ִ�, �ٸ� ��Ÿ�ӿ��� ���� ���Ƿ� ���� �� ���� ����, �̹� ������Ÿ�ӿ� �����⶧��, ������Ÿ�ӻ��
	}

	//��͸� �̿��� ��Ŭ���� ȣ����
	int gcd(int a, int b)
	{
		if (b == 0) return a;
		return gcd(b, a % b);
	}

	//�̸� ��Ÿ���α׷������� ����
	template<int X, int Y>
	struct GCD
	{
		static const int ret = GCD<Y, X%Y>::ret;
	};

	template<int X>
	struct GCD<X, 0> //���ø�Ư��ȭ, ���ϴ� ���ø����� �����
	{
		static const int ret = X;
	};
	void Exam2()
	{
		std::cout << GCD<36, 24>::ret;
	}
	
	//�и�, ���ڸ� �޾� ǥ���ϴ� RatioŬ����
	//<N, D>�� ������Ÿ�ӿ� ǥ���� ������ n, d�� �������ȭ
	template<int N, int D = 1>
	struct Ratio
	{
		static const int num = N;
		static const int den = D;
	};
	//Ratio�� �̿��Ͽ� ������ �����ϴ� ���ø�
	template<typename R1, typename R2>
	struct _Ratio_Add
	{
		using type = Ratio<R1::num* R2::den + R2::num * R1::den, R1::den* R2::den>; //�������ȭ�� R1, R2�� NUM DEN���� ������� ���ο� RatioŬ����Ÿ�� +����� Ŭ������ ����, ���Ǽ������� using type = �� ����
	};
	//ǥ���� ���ϼ������� _Ratio_Add�� ��ӹ޾ƻ���Ѵ�
	template<typename R1, typename R2>
	struct Ratio_Add : _Ratio_Add<R1, R2>::type {}; //ǥ���� ���ϼ������� using���� ǥ���� type, �� RatioŬ������ ����Ͽ� ���ο�Ratio����(_Ratio_Add�ǻ���̾ƴ�, Ratio�ǻ��)

	void Exam3()
	{
		using rat1 = Ratio<2, 3>;
		using rat2 = Ratio<3, 2>;
		using rat3 = Ratio_Add<rat1, rat2>;
		std::cout << rat3::num << '/' << rat3::den;
	}
}

//GCD(�ִ�����, ��Ŭ����ȣ����)�� �̿��� �������� ��Ģ������ �����ϴ� ���ø��� �̿��� ��Ÿ���α׷��� �ڵ�, ��Ģ���� ���� ���м��� ǥ�������� �ִ��������̿��Ѵ�
namespace TMP2
{
	//�̸� ��Ÿ���α׷������� ����
	template<int X, int Y>
	struct GCD
	{
		static const int value = GCD<Y, X% Y>::value;
	};

	template<int X>
	struct GCD<X, 0> //���ø�Ư��ȭ, ���ϴ� ���ø����� �����
	{
		static const int value = X;
	};

	//�и�, ���ڸ� �޾� ǥ���ϴ� RatioŬ����
	//<N, D>�� ������Ÿ�ӿ� ǥ���� ������ n, d�� �������ȭ
	template<int N, int D = 1>
	struct Ratio
	{
	private:
		static const int _gcd = GCD<N, D>::value; //�������� ��Ģ�������� ���м��� ǥ���� ���� �ִ�����
	public:
		static const int num = N / _gcd; //���м�ǥ�������س�����
		static const int den = D / _gcd; //���м�ǥ�������س�����
	};
	//Ratio�� �̿��Ͽ� ������ �����ϴ� ���ø�
	template<typename R1, typename R2>
	struct _Ratio_Add
	{
		using type = Ratio<R1::num* R2::den + R2::num * R1::den, R1::den* R2::den>; //�������ȭ�� R1, R2�� NUM DEN���� ������� ���ο� RatioŬ����Ÿ�� +����� Ŭ������ ����, ���Ǽ������� using type = �� ����
	};
	//ǥ���� ���ϼ������� _Ratio_Add�� ��ӹ޾ƻ���Ѵ�
	template<typename R1, typename R2>
	struct Ratio_Add : _Ratio_Add<R1, R2>::type {}; //ǥ���� ���ϼ������� using���� ǥ���� type, �� RatioŬ������ ����Ͽ� ���ο�Ratio����(_Ratio_Add�ǻ���̾ƴ�, Ratio�ǻ��)
	
	//����
	template<typename R1, typename R2>
	struct _Ratio_Subtract
	{
		using type = Ratio<R1::num* R2::den - R2::num * R1::den, R1::den* R2::den>;
	};
	template<typename R1, typename R2>
	struct Ratio_Subtract : _Ratio_Subtract<R1, R2>::type {};

	//����
	template<typename R1, typename R2>
	struct _Ratio_Multiply
	{
		using type = Ratio<R1::num * R2::num, R1::den* R2::den>;
	};
	template<typename R1, typename R2>
	struct Ratio_Multiply : _Ratio_Multiply<R1, R2>::type {};

	//������
	template<typename R1, typename R2>
	struct _Ratio_Divide
	{
		using type = Ratio<R1::num * R2::den, R1::den * R2::num>;
	};
	template<typename R1, typename R2>
	struct Ratio_Divide : _Ratio_Divide<R1, R2>::type {};

	void Exam()
	{
		using r1 = Ratio<2, 3>;
		using r2 = Ratio<3, 2>;

		using r3 = Ratio_Add<r1, r2>;
		std::cout << "2/3 + 3/2 = " << r3::num << " / " << r3::den << std::endl;

		using r4 = Ratio_Multiply<r1, r3>;
		std::cout << "13 / 6 * 2 /3 = " << r4::num << " / " << r4::den << std::endl;
	}
}