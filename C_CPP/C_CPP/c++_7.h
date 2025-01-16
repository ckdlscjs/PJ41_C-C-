#pragma once
#include "std.h"
/*
* c++�� ����� Ŭ�������� ios_base�� ���Ŭ������ �Ѵ�, ios_base�� ��Ʈ����������İ��� �����͸� ó���Ѵ�(�Ǽ���, ������, 10����, 16���� �ڷ���������ó��)
* 
* iosŬ������ iosbase�� ������� �Ͽ� ��Ʈ�����۸� �ʱ�ȭ�Ѵ�, �����͸� �������ų� �޾Ƶ��̱� ���� �ӽ÷� �����ϴ°�, �����͸� �ѹ��� �о� ��Ʈ�����ۿ� ������
* �ʿ�ÿ� ���� ���ϴ� ũ�⸸ŭ ������, �����͸� �о���� �۾��� �ſ� ������ ������ �̸� ûũ������ �о�� �ʿ��Ѹ�ŭ ����Ѵ�
* ������۾��� ����ó������ ó���Ѵ�, ������ �дٰ� ���� �����ߴ°��� Ȯ���ϱ����� eof�Լ��� ȣ��, ������۾��� �������θ� üũ�ϴ� good�Լ����� ó��
* 
* istream �� �Է��� �����ϴ� Ŭ�����̴�, istream��ü cin������ �����ε� ������ operator>>�� �̿��ؼ� �Է��� �޴°�
* std::stringŬ������ ��ü���� xstring���� istream�� �����Լ��� string��ü�� ���� �����ε��ؼ� �����Ͽ��⶧��
* operator>>�� ���鹮��(����, ����, ��)�� ���� �� ����, ���������ڷ� ��޵ȴ�
* iosŬ������ ��Ʈ���� ���¸� �����ϴµ� �̶� 4���� �÷��׸� �̿��� ���� ��Ʈ���� ��� �������� ������ �����Ѵ�
* goodbit -> ��Ʈ���� ����� �۾��� ������
* badbit -> ��Ʈ���� ���� �Ұ����� ������ �߻�
* failbit -> ��Ʈ���� ���� ������ ������ �߻�
* eofbit -> �Է��۾��� eof����(��)
* 
* std::cin�� operator>>�� �̿��ؼ� �Է��� ������ ��Ʈ���� ���¿� ���� ��ü������ �÷��׸� �̿��� ���¸� �����Ű�µ�
* �ùٸ��� ���� �Է°��� ���´ٸ� operator�Լ��� cin��ü�� failbit���� Ű�Եȴ�, ���� cin��ü�� ���¿����� ���ϰ�(cin��ü)�� ���¿� ����
* �����Էµ��� ������ �ִ°� ���°������� ���ΰ� ��������
* 
* std::cin.setf(std::ios_base::hex, std::ios_base::basefield); �� �̿��ؼ� ��Ʈ���� ����� ������ 16������(std::ios_base::hex)�� �ٲܼ� �ִ�
* setf�� �Լ����ڰ� ��ó�� 2���ϰ�� ù��° �÷��� ���ڸ� �����Ű�� �ι�° ������ ������ �ʱ�ȭ��Ű�°�
* 
* �ι�° ����º��������δ� std::cin >> std::hex �� ���Ͽ� ���� �� �� �ִ�, ���� setf�ǰ�� ���ڷ� �÷��׸�(std::ios_base::hex)�����ϴ� �� ������
* std::cin >> std::hex�� ��� std::ios_base�� �����ϴ� std::ios_base& hex(std::ios_base& str) �Լ��� �̿��Ͽ� ���ڷ� ���� cin(istream)�� ���� �����Ͽ� ����� �ϴ°����� �����Ѵ�
* ��� std::cin �� �������� operator>>�� ���� ios_base�� ���ϵǴ� std::hex�Լ��� �̿��Ͽ� operator>>�� ���ڷ� ���ϵǴ� ios_base�� �޾� cin�� �÷��װ��� �����Ű�°�
* �̶� �Լ��� ���ڴ� istream& operator>>(ios_base& (*pf)(ios_base&))�� �Ǵµ� �̶� ������ ios_base& (*pf)(ios_base&)�� �Լ������͸� �ǹ��Ѵ� ��� std::hex�� �Լ��̱� �����̴�
* ���� �ΰ��� ���ó�� Ư�� �÷��׸� �̿��� ��Ʈ���ǻ��¸� �ٲٴ°͵��� ������ ��� �Ѵ�(endl, left, right, boolalpha��)
* 
* ��� ����� ��ü���� �����Ǵ� ��Ʈ����ü�� ������, ����¿� �ش��ϴ� ��Ʈ������ Ŭ������ streambufŬ�����̴�.
* ���ڵ��� �������� ������ stream�̶�� �� �� �ִµ� c++������ std::stringstream �� ���� ���ڿ��� ��Ʈ��ó�� �̿� �� ���� �ְ� �Ѵ�
* 
* 
*/
namespace stream
{
	void Exam()
	{
		/*
		int t = -1;
		while (true) {
			std::cin >> t;
			if (std::cin.fail()) //cin��ü�� MyState, flag�� &�����Ͽ� ����� ����
			{
				std::cout << "������Է¹ٶ�"<< '\n';
				std::cin.clear();
				std::cin.ignore(100, '\n');
			}
			else
			{
				std::cout << "�Է� :: " << t << '\n';
			}
			
			if (t == 0) 
				break;
		}
		*/

		/*
		char first, last;

		cout << "Enter your first and last names: ";

		first = cin.get();
		cin.ignore(256, ' ');  // ��Ʈ������ 256��, ' '���� �����Ѵ�

		last = cin.get();

		cout << "Your initials are " << first << last;
		*/

		std::string s;
		std::cin >> s;

		// ��ġ �����ڸ� �� ĭ �ű��, �� ���� ���ڸ� ���ĺ��� (�� ���� �������� ����)
		/*
		* std::cin >> s �� �̿��� hello world\n�� �Է¹�����
		* ���⸦ ���� ��Ʈ�����۴� o�� w�� ��� ������ �����ϰ��ִ�
		* rdbuf�� �̿��� ���� ��Ʈ�������� �����͸� �������� snextc�� ��Ʈ���� ��ġ�����ڸ� ��ĭ �ڷ� ������ ������, ���ο� �Է��� ���ö� ������
		* ��ġ�� �д°��� �ƴϱ⶧���� ����Ű�� ������ w�� �����ϰԵǰ� ���� std::cin>>s�� ���Է�(world\n)�� ������ �Ǹ� �׶� w�� �о�´�
		*/
		char peek = std::cin.rdbuf()->snextc();
		if (std::cin.fail()) std::cout << "Failed";
		std::cout << "�� ��° �ܾ� �� �ձ��� : " << peek << std::endl;
		//std::cin >> s;
		//std::cout << "�ٽ� ������ : " << s << std::endl;
	}
}
namespace fileio
{
//#define __str__
	void Exam()
	{
		std::ifstream in("test.txt"); //���ϸ� ������ vs���� ����� �ҽ����ϰ��������, �̿ܿ� �������ϰ� �������, ��ü�� ���ο� ������ �б����ؼ� close�� �ʿ��ϴ�, ifstream��ü�� �Ҹ�� �ڵ����� close���Ѵ�
		std::string s;
		if (in.is_open())
		{
			in >> s;
			std::cout << s << '\n';
		}
		else
			std::cout << "������ ���о��\n";
	}
	void Exam2()
	{
		std::ifstream in("test2.txt", std::ios::binary); //�Է��� ����·� ������������ �÷���, or�������� �߰� �ɼǰ���
		std::string s;
		int x;
		if (in.is_open())
		{
			in.read((char*)(&x), 4);
			std::cout << std::hex << x << '\n';
		}
		else
		{
			std::cout << "������ ã�� �� �����ϴ�\n";
		}
	}
	void Exam3()
	{
		std::ifstream in("test3.txt");
		std::string s;
		if (in.is_open())
		{
			//�����Ǹ��������� �������̵�
			in.seekg(0, std::ios::end);
			//������ġ�� �������� ũ�⸦ ����, �ѱ��� 2����Ʈ����
			int size = in.tellg();
			//���ڿ��� ũ�⸦ �����ŭ����
			s.resize(size);
			//�����͸�ó�����θ���
			in.seekg(0, std::ios::beg);
			//������ ó������ �����ŭ �������д´�
			in.read(&s[0], size);
			std::cout << s << '\n';//���
		}
		else
		{
			std::cout << "������ ã�� �� �����ϴ�\n";
		}
	}
	void Exam4()
	{
		std::ifstream in("test3.txt");
		char buf[105];
		if (!in.is_open())
		{
			std::cout << "������ ���� �� �����ϴ�\n";
			return;
		}

#ifdef __str__
		while (in) //�ڽ��� bool�� ĳ���� �ϴ� operator bool()�� �����ε� �Ǿ��־� bool�� ĳ���� �ϴ� operator bool�� ȣ��Ǿ� ����üũ�� ���δ�, �����÷��׸� �������� ����boolean����������
		{ 
			in.getline(buf, 100); //'\n'�� ������ ���� 100�� ������ �о�´�, ������'\n'�� ������ �ִ� 99����
			std::cout << buf << std::endl;
			/*
			* getline�Լ��� ���๮�� Ȥ�� ��������(����° �з����� delim)�� ������ ���� ������ ũ�Ⱑ �� ����(����� �ѱ��) failbit�� �ѹǷ� ������������ �� üũ�ؾ��Ѵ�
			* �̸� �ذ��ϱ����� ifstream�� getline�� �ƴ� std::getline(ifstream��ü, std::string)�� �̿��Ͽ� ������ ����� �Ű澲�� �ʾƵ� �ȴ�
			*/
		}
#endif
#ifndef  __str__
		std::string str;
		while (in) //�ڽ��� bool�� ĳ���� �ϴ� operator bool()�� �����ε� �Ǿ��־� bool�� ĳ���� �ϴ� operator bool�� ȣ��Ǿ� ����üũ�� ���δ�, �����÷��׸� �������� ����boolean����������
		{
			std::getline(in, str);
			std::cout << str << std::endl;

		}
#endif // ! __str__
	}

	void Exam5()
	{
		/*std::ofstream out("testout.txt"); //������ ����� ���� ������ ���, ������ ������ ���
		if (out.is_open())
		{
			out << "WriteThis!";
		}
		*/
		
		std::ofstream out("testout.txt", std::ios::app); //std::ios::app�� �ɼ����� �߰��� append�̾������.
		if (out.is_open())
		{
			out << "appendThis!";
		}
		/*
		* ios::binary, app���� �������� �ɼ��� �����Ѵ�
		* ios::ate -> �ڵ����� ���� ������ ���� �б�, ���⸦ �ǽ��Ѵ�(������ ���� ��ġ�����ڰ� ���� ���� ����Ű���ִ�), ate�ǰ�� ��ġ�����ڸ� ������ �ű�����ִ�, app�� ������ �ǳ�
		* ios::trunc -> ���� ��Ʈ���� ���� ���� ������ �����������, �⺻���� ofstream��ü �������� �ʱ�ɼ�
		* ios::in, ios::out -> ���Ͽ� �Է�/ Ȥ�� ��� ���θ� �����Ѵ�, ifstream, ofstream���� �⺻�ɼǵ�
		*/
	}
	class EX6Class
	{
	private:
		std::string name;
		int age;
	public:
		EX6Class(const std::string _name, const int _age) : name(_name), age(_age) {}
		friend ofstream& operator<<(std::ofstream& out, EX6Class& ex) //�����Լ��� �����ε�
		{
			out << ex.name + ", " + std::to_string(ex.age) << '\n';
			return out;
		}
	};
	void Exam6()
	{
		std::ofstream out("test6.txt");
		EX6Class ex("�����", 60);
		out << ex;
	}
}
