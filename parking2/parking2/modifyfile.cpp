#include<iostream>
#include<fstream>
using namespace std;

void modifyPorrt()
{
  fstream file("test.txt",ios::in|ios::out);
  int a=0,b=0;
  file.ignore(5,EOF);//file.ignore(1000,'\n');也可
  file>>a;
  file.ignore(1,EOF);
  file>>b;
  cout<<"原值："<<a<<":"<<b<<endl;
  cout<<"输入修改值：";
  cin>>a>>b;
  file.seekp(5,ios::beg);
  file<<endl<<a<<":"<<b<<endl;
  file.close();
}
