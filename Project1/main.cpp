#include<iostream>
#include "xmlParser.h"


class Parent
{
public:
	
	 virtual void foo()
	{
		cout << "i'm parent"<<endl;
	}

	 

};

class Child  : public Parent
{
public:

	void foo() override
	{
		cout << "I'm child"<<endl;
	}
	
};



int main()
{
	setlocale(LC_ALL, "ru");
	
	
	vector < Parent> set;

	Child child;

	set.push_back(child);

	(&set)->push_back(child);

	



	XmlParser a("xml-example.xml") ;

	

	

	//XmlAttribute d(ss);
	
	system("pause");
	return 0;
}