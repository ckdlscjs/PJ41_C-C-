#pragma once
#include "std.h"
namespace ExcelProject
{
	class Cell;
	class Table;
	class Vector
	{
		int capacity;
		int length;
		std::string* datas;
	public:
		// ������
		Vector(int n = 1) : capacity(n), length(0), datas(new std::string[n]) {}
		virtual ~Vector()
		{
			if(datas)
				delete[] datas;
		}
		// �� �ڿ� ���ο� ���Ҹ� �߰��Ѵ�.
		void push_back(std::string s)
		{
			if (length >= capacity)
			{
				std::string* copys = new std::string[capacity * 2];
				for (int idx = 0; idx < length; idx++) copys[idx] = datas[idx];
				delete[] datas;
				datas = copys;
				capacity *= 2;
			}
			datas[length++] = s;
		}

		// ������ ��ġ�� ���ҿ� �����Ѵ�.
		std::string operator[](int i)
		{
			if (i < 0 || i >= length) return "";
			return datas[i];
		}

		// x ��° ��ġ�� ���Ҹ� �����Ѵ�.
		void remove(int x)
		{
			if (x < 0 || x >= length) return;
			for (int i = x + 1; i < length; i++)
			{
				datas[i - 1] = datas[i];
			}
			length--;
		}

		// ���� ������ ũ�⸦ ���Ѵ�.
		int size()
		{
			return length;
		}
	};
	class Stack
	{
		struct Node
		{
			std::string str;
			Node* prev;
			Node(std::string _s, Node* _prev = NULL) : str(_s), prev(_prev){}
		};
		Node* topNode;
	public:
		Stack() : topNode(NULL) {}
		virtual ~Stack()
		{
			while (topNode)
			{
				Node* delNode = topNode;
				topNode = delNode->prev;
				delete delNode;
			}
		}
		// �ֻ�ܿ� ���ο� ���Ҹ� �߰��Ѵ�.
		void push(std::string str)
		{
			Node* newNode = new Node(str);
			if (topNode == NULL)
			{
				topNode = newNode;
			}
			else
			{
				newNode->prev = topNode;
				topNode = newNode;
			}
		}
		// �ֻ���� ���Ҹ� ��ȯ�Ѵ�.
		std::string top()
		{
			return topNode ? topNode->str : NULL;
		}

		// �ֻ���� ���Ҹ� �����ϰ� ��ȯ�Ѵ�.
		std::string pop()
		{
			Node* delNode = topNode;
			std::string ret = delNode->str;
			topNode = delNode->prev;
			delete delNode;
			return ret;
		}

		// ������ ����ִ����� ������ ��ȯ�Ѵ�.
		bool is_empty()
		{
			return topNode ? false : true;
		}
	};
	class Cell
	{
	protected:
		std::string data;
		int y, x;
		Table* table;
	public:
		Cell(std::string _str, int _y, int _x, Table* _tableinfo) : data(_str), y(_y), x(_x), table(_tableinfo) {}
		virtual std::string numtostr();
		virtual int strtonum();
	};

	class Table
	{
	protected:
		int row, col;
		Cell*** cells;

	};
}