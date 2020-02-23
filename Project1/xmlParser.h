#include<iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class XmlAttribute // класс атрибута , содежрит атрибут и его значение 
{
public:

	XmlAttribute(string stringAttributeWithValue); // конструктор который сам разбивает строку на атрбут  значение атрибута 
	
	void setAttributeName(string  attributeName);

	string getAttributeName();

	void setAttributeValue(string attributeValue);

	string getAttributeValue();

private:

	string attributeName;

	string attributeValue;
};

class XmlNode 
{
public:

	void coutTab(int depth);

	void printXml(int depth);

	void coutAllAttribute(vector <XmlAttribute> tagAttrs);

	virtual void coutNode(int depth);

	

	void setTagName(string nameTag);

	string getTagName();

	void setTagValue(string tagValue);

	string getTagValue();

	void setTagAttrs(XmlAttribute tagAttrs);

	vector <XmlAttribute> getTagAttrs(); // функция возвращает вектор атрибутов 
	
	vector <XmlNode*>  nodes; // вектор дочерних тегов
	
	XmlNode *parent; // указатель на родителя

	XmlNode(); // контруктор для создания элемента 

private:

	string tagName; // название тега 

	string tagValue; // данные тега // только у листоы есть данные 

	vector <XmlAttribute> tagAttrs; //  вектор сторок атрибутов 
};

class XmlInstruction : public XmlNode
{
public:
	
	void coutNode(int depth) override;
};

class XmlComment : public XmlNode
{
public:

	void coutNode(int depth) override;
};

class XmlTag : public XmlNode
{
public:

	void coutNode(int depth) override;
};

class XmlText : public XmlNode
{
public:

	void coutNode(int depth) override;
};

class XmlParser 
{
public:
	
	XmlParser(string path);

private:

	void skipCDATAFragment();

	void findTagEnd();

	

	

	size_t currentElementInStringNumber; //  переменная отвечающая за номер текущего элемента 

	string getFullWord();

	bool parseNode(XmlTag *node);

	void parseNode(XmlText *node);

	void parseNode(XmlInstruction *node);

	void parseNode(XmlComment *node);


	string findTagWithValue();

	void read(XmlNode *parent);

	string docString; 

	
};

