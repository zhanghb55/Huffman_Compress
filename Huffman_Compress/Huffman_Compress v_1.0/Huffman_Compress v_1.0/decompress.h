#pragma once
#include "Huffman_Tree.h"
#include "compress.h"

//�����洢����������ӳ�䵽�ַ��Ĺ�ϵ
map<string, int> key;
//�����洢���ɵĹ������ļ��������ֽ�
char* file;
//��λ�����ʱ��������ʾfile�ĵڼ���char����
int buffer_ptr;
//������ʾfile�ĵ�buffer_ptr�ĵڼ���λ
int count_bit;
//�����洢ת��Ϊ������ʽ�ı���������ֽ�
char* reduction;
//��ȡ���ɵĹ������ļ�
void read(char* source_file_name) {
	ifstream in;
	in.open(source_file_name, ios::binary);
	int n;
	in.read((char*)& n, sizeof(int));
	for (int i = 0; i < n; i++) {
		char buffer;
		in.read(&buffer, sizeof(char));
		int x = (unsigned int)buffer;
		int temp;
		in.read((char*)& temp, sizeof(int));
		res[(unsigned char)buffer] = temp;
	}
	in.read((char*)& buffer_ptr, sizeof(int));
	in.read((char*)& count_bit, sizeof(int));
	file = new char[buffer_ptr + 1];
	for (int i = 0; i <= buffer_ptr; i++) {
		char buffer;
		in.read(&buffer, sizeof(char));
		file[i] = buffer;
		int x = (unsigned char)buffer;
	}
	in.read((char*)& _file_length, sizeof(int));
}
void get_string_map() {
	for (int i = 0; i < 256; i++) {
		if (!code[i].empty()) {
			key.insert(pair<string, int>(code[i], i));
		}
	}
}
void convert() {
	reduction = new char[_file_length];
	string temp;
	int ptr = 0;//�����ַ�λ
	int i = 0;//����bit
	int m = 0;//������������ַ���������
	while (1) {
		if (m == _file_length)break;
		int x = (unsigned char)file[ptr];
		x = x & (1 << (7 - i));
		i++;
		if (i == 8) {
			ptr++;
			i = 0;
		}
		if (x) {
			temp.push_back('1');
		}
		else temp.push_back('0');
		if (key.count(temp)) {
			reduction[m++] = key[temp];
			temp.clear();
		}
	}
}
void reduction_file(char* filename) {
	string temp = filename;
	for (int i = 0; i < 10; i++) {
		temp.pop_back();
	}
	ofstream out;
	out.open(temp, ios::out | ios::binary);
	for (int i = 0; i < _file_length; i++) {
		char tmp = reduction[i];
		out.write(&tmp, sizeof(char));
	}
	out.close();
}
void decompress(char* file_name) {
	read(file_name);
	priority_queue<node> queue = get_queue(res);
	node* head = Huffman_Tree(queue);
	get_code(head);
	get_string_map();
	convert();
	reduction_file(file_name);
}