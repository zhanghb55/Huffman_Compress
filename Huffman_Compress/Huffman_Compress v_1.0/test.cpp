/*
    测试程序
    功能：比较两个文件是否全同
    基本思想：严格按照顺序读取两个文件的字符
             若一个文件比另一个文件先结束或读取的两个字符不相等，则说明两个文件大小不匹配
             否则，则说明两个文件完全匹配
*/
#include <iostream>
#include <fstream>
using namespace std;

bool test( char * file_name_1, char *file_name_2 );

/*
    使用方法：假设main.cpp生成可执行文件main.exe
        1、在命令行中输入 "main.exe file_1_name.file_1_type file_2_name.file_2_type"
        2、修改main函数为你熟悉的文件输入方式
*/

int main( int argc, char *argv[] )
{
    // argv[1]为第一个文件, argv[2]为第二个文件
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
        //读取的字符不匹配
        if ( c1 != c2 ) {
            f1.close();
            f2.close();
            return false;
        }
        f1.read( &c1, sizeof(char) );
        f2.read( &c2, sizeof(char) );
    }

    if ( f1.eof() && f2.eof() ) ans = true; //两个文件完全匹配
    else ans = false; // 两个文件大小不相同

    f1.close();
    f2.close();
    return ans;
}