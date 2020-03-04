/*
    ���Գ���
    ���ܣ��Ƚ������ļ��Ƿ�ȫͬ
    ����˼�룺�ϸ���˳���ȡ�����ļ����ַ�
             ��һ���ļ�����һ���ļ��Ƚ������ȡ�������ַ�����ȣ���˵�������ļ���С��ƥ��
             ������˵�������ļ���ȫƥ��
*/
#include <iostream>
#include <fstream>
using namespace std;

bool test( char * file_name_1, char *file_name_2 );

/*
    ʹ�÷���������main.cpp���ɿ�ִ���ļ�main.exe
        1���������������� "main.exe file_1_name.file_1_type file_2_name.file_2_type"
        2���޸�main����Ϊ����Ϥ���ļ����뷽ʽ
*/

int main( int argc, char *argv[] )
{
    // argv[1]Ϊ��һ���ļ�, argv[2]Ϊ�ڶ����ļ�
    if ( test( argv[1], argv[2] ) ) {
        cout << "matched" << endl;
    }
    else {
        cout << "not matched" << endl;
    }
}

bool test( char * file_name_1, char *file_name_2 )
{
    ifstream f1, f2;
    char c1, c2;
    bool ans;

    f1.open( file_name_1, ios::in );
    f2.open( file_name_2, ios::in );

    if ( !f1.is_open() || !f2.is_open() ) exit( -1 );
    
    f1.read( &c1, sizeof(char) );
    f2.read( &c2, sizeof(char) );
    while ( !f1.eof() || !f2.eof() ) {
        //��ȡ���ַ���ƥ��
        if ( c1 != c2 ) {
            f1.close();
            f2.close();
            return false;
        }
        f1.read( &c1, sizeof(char) );
        f2.read( &c2, sizeof(char) );
    }

    if ( f1.eof() && f2.eof() ) ans = true; //�����ļ���ȫƥ��
    else ans = false; // �����ļ���С����ͬ

    f1.close();
    f2.close();
    return ans;
}