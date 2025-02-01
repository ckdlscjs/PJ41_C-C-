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
	public:
		std::string data;
		int y, x;
		Table* table;
	public:
		Cell(std::string _str, int _y, int _x, Table* _tableinfo) : data(_str), y(_y), x(_x), table(_tableinfo) {}
		virtual std::string numtostr()
		{
			return data;
		}
		virtual int strtonum()
		{
			return 0;
		}
	};

	/*
	* cell* ptr = new cell->cell�� ����Ű�� ������
	* cell* ptrs = new cell[size] -> size��ŭ ���������� cell�迭�� �����ּҸ� ����Ű�� ������
	* cell** dptrs = new cell*[size] -> cell*�� ����Ű�� �����͸� size������ŭ �����Ҵ��ϰ� �� �迭�� �����ּҸ� �Ҵ� ....
	*/

	class Table
	{
	protected:
		int size_row, size_col;
		Cell*** cells;
	public:
		Table(int _rsize, int _csize) : size_row(_rsize), size_col(_csize)
		{
			cells = new Cell**[size_row]; //cells**�� �����͸� size������ŭ ������ �迭�� �����ּҸ� cells�� �Ҵ�, row�ุŭ
			for (int r = 0; r < size_row; r++)
			{
				cells[r] = new Cell * [size_col]; //cells* �����͸� size������ŭ ������ �迭�� �����ּҸ� cells[r](��) �� �Ҵ�
				//std::memset(cells[r], NULL, sizeof(Cell*) * size_col);
				for (int c = 0; c < size_col; c++)
				{
					cells[r][c] = NULL;
				}
			}
		}
		~Table()
		{
			//����(cell�� ����Ű�� �����Ҵ�) ���� ����
			for (int r = 0; r < size_row; r++)
				for (int c = 0; c < size_col; c++)
					if (cells[r][c]) delete cells[r][c];
			//��(cell*�� ����Ű�� r���� cell**�� ������, cell**�� size_col���� �������)
			for (int r = 0; r < size_row; r++)
				delete[] cells[r];
			//��ü(cell**�� ����Ű�� cell***�� ������ cells, size_row���� �������)
			delete[] cells;
		}
		// ���ο� ���� row �� col ���� ����Ѵ�.
		void reg_cell(Cell* cell)
		{
			if (!cell) return;
			int r = cell->y;
			int c = cell->x;
			if (!(0 <= r && r < size_row)) return;
			if (!(0 <= c && c < size_col)) return;
			if (cells[r][c]) delete cells[r][c];
			cells[r][c] = cell;
		}

		// �ش� ���� �������� ��ȯ�Ѵ�.
		// s : �� �̸� (Ex. A3, B6 �� ����)
		int to_numeric(const std::string& s)
		{
			int r = std::atoi(s.c_str()+1);
			int c = s[0] - 'A';
			return to_numeric(r, c);
		}

		// �� �� �� ��ȣ�� ���� ȣ���Ѵ�.
		int to_numeric(int r, int c)
		{
			if (!(0 <= r && r < size_row)) return -1;
			if (!(0 <= c && c < size_col)) return -1;
			if (!cells[r][c]) return -1;
			return cells[r][c]->strtonum();
		}

		// �ش� ���� ���ڿ��� ��ȯ�Ѵ�.
		std::string stringify(const std::string& s)
		{
			int r = std::atoi(s.c_str() + 1);
			int c = s[0] - 'A';
			return stringify(r, c);
		}
		std::string stringify(int r, int c)
		{
			if (!(0 <= r && r < size_row)) return "";
			if (!(0 <= c && c < size_col)) return "";
			if (!cells[r][c]) return "";
			return cells[r][c]->numtostr();
		}

		virtual std::string print_table() const = 0; //const�� �Լ������ؾ� �����Լ� operator���� const�� ȣ�� ����, ���������Լ�, �ڽ�Ŭ�������� �������̵��ؾ���
	};
	class TextTable : public Table
	{
	private:
		std::string repeat_char(int n, char c) const
		{
			std::string str = "";
			for (int i = 0; i < n; i++) str += c;
			return str;
		}
		// ���ڷ� �� �� ��ȣ�� A, B, .... Z, AA, AB, ...  �̷� ������ �Ű��ش�.
		std::string col_num_to_str(int n) const
		{
			std::string str = "";
			if (n < 26)
			{
				str += ('A' + n);
			}
			else
			{
				char first = 'A' + n / 26 - 1;
				char second = 'A' + n % 26;

				str.push_back(first);
				str.push_back(second);
			}
			return str;
		}
	public:
		//�θ�����ڿ� �������� �� ����
		TextTable(int row, int col) : Table(row, col) {}

		// �ؽ�Ʈ�� ǥ�� �����ϰ� ������ش�.
		virtual std::string print_table() const
		{
			//���� ���̸� ���߱����� ���Ǳ���������ȸ
			int* col_max_lengths = new int[size_col];
			for (int j = 0; j < size_col; j++)
			{
				unsigned int col_length = 2;
				for (int i = 0; i < size_row; i++)
				{
					if (cells[i][j] && cells[i][j]->numtostr().size() > col_length)
						col_length = cells[i][j]->numtostr().size();
				}
				col_max_lengths[j] = col_length;
			}
			
			//������(������)
			int table_width = 4;
			std::string total_table = "    "; //4ĭ
			for (int j = 0; j < size_col; j++)
			{
				if (col_max_lengths[j])
				{
					int length = std::max(2, col_max_lengths[j]);
					total_table += " | " + col_num_to_str(j);
					total_table += repeat_char(length - col_num_to_str(j).size(), ' ');
					table_width += (length + 3);
				}
			}
			total_table += "\n";

			//��, �� ������ǥ��
			for (int i = 0; i < size_row; i++) {
				total_table += repeat_char(table_width, '-'); //����+���̸�ŭ - ǥ��
				total_table += "\n"; //�ٰ���
				total_table += to_string(i + 1) + repeat_char(4 - to_string(i + 1).length(), ' '); //�� ǥ��

				for (int j = 0; j < size_col; j++) {
					if (col_max_lengths[j]) {
						int max_len = std::max(2, col_max_lengths[j]); //Ư��������

						string s = "";
						if (cells[i][j]) {
							s = cells[i][j]->numtostr(); //����ǥ��
						}
						total_table += " | " + s;
						total_table += repeat_char(max_len - s.size(), ' '); //����ǥ�ù� ���� �ٸ���
					}
				}
				total_table += "\n"; //�� ���� ��� ������ ����
			}

			return total_table;
		}
	};
	std::ostream& operator<<(std::ostream& out, const Table& table)
	{
		out << table.print_table();
		return out;
	}
	void Exam()
	{
		TextTable table(5, 6);
		std::ofstream out("test.txt");

		table.reg_cell(new Cell("Hello~", 0, 0, &table));
		table.reg_cell(new Cell("C++", 0, 1, &table));

		table.reg_cell(new Cell("Programming", 1, 1, &table));
		std::cout << std::endl << table;
		out << table;
	}
}