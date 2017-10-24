#include <iostream>
#include <sys/time.h>
using namespace std;

void foo(char *ch)
{
    cout<<"calll foo(char*)"<<endl;
}

void foo(int i)
{
    cout<<"called foo(int i)"<<endl;
    cout<<"文件:"<<__FILE__<<endl<<"函数:"<<__func__<<endl<<"第"<<__LINE__<<"行"<<endl;
}


int main()
{
    class test {
        // test(istream &is);
        public:
            const string hello();
            inline test world() { cout<<"women"<<endl; a = 'a'; women = "测试" ; return *this;}
            test() { cout<<"你好，我是构造函数"<<endl;}
            ~test() { cout<<"我是析构函数"<<endl;}
        private :
            char a = '2';
            string women = "women";
    };

    const string test::hello()
    {
        return this->women;
    }


    // test::test(istream &is)
    // {
    //
    // }

    // struct test *b = new test;
    test b,c;
    cout<< b.hello() <<endl;
    // cout<< b.women<<endl;

    c = b.world();
    cout<< c.hello() <<endl;
    // cout<< c.women<<endl;

    // void *p = b.world();
    // delete b;
    return 0;
}

