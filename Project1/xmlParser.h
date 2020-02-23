#include<iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class XmlAttribute // ����� �������� , �������� ������� � ��� �������� 
{
public:

	XmlAttribute(string stringAttributeWithValue); // ����������� ������� ��� ��������� ������ �� ������  �������� �������� 
	
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

	vector <XmlAttribute> getTagAttrs(); // ������� ���������� ������ ��������� 
	
	vector <XmlNode*>  nodes; // ������ �������� �����
	
	XmlNode *parent; // ��������� �� ��������

	XmlNode(); // ���������� ��� �������� �������� 

private:

	string tagName; // �������� ���� 

	string tagValue; // ������ ���� // ������ � ������ ���� ������ 

	vector <XmlAttribute> tagAttrs; //  ������ ������ ��������� 
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

	

	

	size_t currentElementInStringNumber; //  ���������� ���������� �� ����� �������� �������� 

	string getFullWord();

	bool parseNode(XmlTag *node);

	void parseNode(XmlText *node);

	void parseNode(XmlInstruction *node);

	void parseNode(XmlComment *node);


	string findTagWithValue();

	void read(XmlNode *parent);

	string docString; 

	
};

