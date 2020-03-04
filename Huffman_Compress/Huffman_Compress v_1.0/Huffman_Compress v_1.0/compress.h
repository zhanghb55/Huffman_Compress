#pragma once
#include "Huffman_Tree.h"

using namespace std;
//Ƶ������
int res[256];
//�洢���ֵ��ֽڵĹ���������
string code[256];
//�洢���е��ֽ�
//vector<char> all_alpha;
//�����ļ��ĳ���
int _file_length;

//����get_code �����ݴ��ַ���
string temp;

//��ȡÿ���ֽڼ�����ֵ�Ƶ��
void get_frequency(char* source_file_name) {
	ifstream in;
	in.open(source_file_name, ios::binary);
	char buffer;
	in.read(&buffer, sizeof(char));
	while (!in.eof()) {
		res[(unsigned char)(buffer)]++;
		//all_alpha.push_back(buffer);
		in.read(&buffer, sizeof(char));
	}
	in.close();
}
//��ȡ�����ļ����ֽڳ���
void file_length() {
	for (int i = 0; i < 256; i++) {
		_file_length += res[i];
	}
}

//���������õ�����
void get_code(node* head) {
	if (head->left == nullptr && head->right == nullptr) {
		int value = head->value;
		code[value] = temp;
		return;
	}
	temp.push_back('0');
	get_code(head->left);
	temp.pop_back();
	temp.push_back('1');
	get_code(head->right);
	temp.pop_back();
}

//��Ƶ����������������밴λ�Ͷ������ļ��ķ�ʽд���ļ�
void write_out(char* source_file_name) {
	ifstream in;
	in.open(source_file_name, ios::binary);
	char buffer;
	string temp;
	char* output = new char[_file_length];
	memset(output, 0, sizeof(char) * _file_length);
	//���¶��ļ�����Ϊ��������е��ֽ�ֱ�Ӷ��������vector�ڴ���ܻ�ը
	in.read(&buffer, sizeof(char));
	int count = 0;
	long long int buffer_ptr = 0;
	string total;
	while (!in.eof()) {
		//�������潫ԭ�ֽ�ת��Ϊ���������벢ѹ���µ��ֽ�
		string temp = code[(unsigned char)buffer];
		total += temp;
		for (int i = 0; i < temp.size(); i++) {
			int x = temp[i] - '0';
			x = x << (7 - count);
			output[buffer_ptr] = output[buffer_ptr] | x;
			count++;
			if (count == 8) {
				count = 0;
				buffer_ptr++;
			}
		}
		in.read(&buffer, sizeof(char));
	}
	in.close();
	//��ʼ���
	ofstream out;
	string out_name = source_file_name;
	out_name += ".zhbzqyzip";//���Ϻ�׺��
	out.open(out_name, ios::out | ios::binary);
	//ͳ�Ƴ��ֶ������ֽ�
	int total_num = 0;
	for (int i = 0; i < 256; i++) {
		if (res[i])total_num++;
	}
	//�������ֽ��������ļ����ڶ�ȡ��ʱ��Ϳ�����forѭ����λ
	out.write((char*)& total_num, sizeof(int));
	for (int i = 0; i < 256; i++) {
		//�����ļ����ֹ����ֽڼ����Ӧ�Ĺ������������ļ����ڽ����ʱ���ٹ�������ȡ
		if (res[i]) {
			buffer = i;
			int num = res[i];
			out.write(&buffer, sizeof(char));
			out.write((char*)& num, sizeof(int));
		}
	}

	out.write((char*)& buffer_ptr, sizeof(int));
	out.write((char*)& count, sizeof(int));
	for (int i = 0; i <= buffer_ptr; i++) {
		char temp = output[i];
		int x = (unsigned char)output[i];
		out.write(&temp, sizeof(char));
	}
	out.write((char*)& _file_length, sizeof(int));
	out.close();
	delete[]output;
}

void compress(char* file) {
	get_frequency(file);
	file_length();
	priority_queue<node> queue = get_queue(res);
	node* head = Huffman_Tree(queue);
	get_code(head);
	write_out(file);
}

