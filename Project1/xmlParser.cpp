#include "xmlParser.h"

void XmlNode::coutNode(int depth)
{
}



void XmlNode::setTagName(string tagName)
{
	this->tagName = tagName;
}

string XmlNode::getTagName()
{
	return this->tagName;
}

void XmlNode::setTagValue(string tagValue)
{
	this->tagValue = tagValue;
}

string XmlNode::getTagValue()
{
	return this->tagValue;
}

void XmlNode::setTagAttrs(XmlAttribute tagAttrs) // ������ � ������ ��������� ���� 
{
	this->tagAttrs.push_back(tagAttrs);
}

vector< XmlAttribute> XmlNode::getTagAttrs()  // ������� ������ ������� ������ ���������   
{
	return this->tagAttrs;
}

XmlAttribute::XmlAttribute(string stringAttributeWithValue)// ����������� �������� ������ � ��������� �� �� ������� � ������� 
{
	string attributeName, attributeValue;

	bool isFindAttributeName = false;

	for (size_t currentElementNumber = 0; currentElementNumber < stringAttributeWithValue.length(); currentElementNumber++)
	{
		if (stringAttributeWithValue[currentElementNumber] == '=')// ���� ����� �� ����� ������ ��� ������� �� �������� 
		{
			isFindAttributeName = true;

		}

		if (!isFindAttributeName)
		{
			attributeName += stringAttributeWithValue[currentElementNumber];
		}
		
		if (isFindAttributeName && stringAttributeWithValue[currentElementNumber] != '=')
		{
			attributeValue += stringAttributeWithValue[currentElementNumber];
		}
		
	}

	this->setAttributeName(attributeName);// � ������� ������� ������� ���� ������ � XmlAttribute
	this->setAttributeValue(attributeValue);

}

void XmlAttribute::setAttributeName(string attributeName)
{
	this->attributeName = attributeName;

}

string XmlAttribute::getAttributeName()
{
	return this->attributeName;
}

void XmlAttribute::setAttributeValue(string attributeValue)
{
	this->attributeValue = attributeValue;
}

string XmlAttribute::getAttributeValue()
{
	return this->attributeValue;
}

XmlNode::XmlNode()
{
	
}

string XmlParser::getFullWord()// � ������� �������� ������ ������ ������ � ��� ���������� ��� ����� ������� �� ������� ������� 
{
	string stringByReturn;
	
	for (this->currentElementInStringNumber; this->currentElementInStringNumber < this->docString.length(); this->currentElementInStringNumber++)
	{
		if (this->docString[this->currentElementInStringNumber] != ' ' && this->docString[this->currentElementInStringNumber] != '>'  && this->docString[this->currentElementInStringNumber] != '<')// ���� ��������� �� ������� ������� �� ���������� �����  
		{
			stringByReturn += this->docString[this->currentElementInStringNumber];
		}
		else
		{
			if (this->docString[this->currentElementInStringNumber] == '<')
			{
				this->currentElementInStringNumber--;
			}

			return  stringByReturn;
		}
	}

	return stringByReturn;
}

void XmlParser::parseNode(XmlInstruction * node)
{
	bool isParseInstructionName = false;

	for (this->currentElementInStringNumber; this->currentElementInStringNumber < this->docString.length(); this->currentElementInStringNumber++)
	{
		if (this->docString[this->currentElementInStringNumber] == '?' && isParseInstructionName == false)// �������� ��� ��������� ������� ���� ��� �� ����� ��� ����������
		{
			isParseInstructionName = true;

			string instructionName = this->getFullWord();// �������� �������� ���������� 

			node->setTagName(instructionName);
		}

		if (this->docString[this->currentElementInStringNumber] != ' ' && this->docString[this->currentElementInStringNumber] != '?')
		{
			string tagWithValue = this->findTagWithValue();// ���� ��� � ��������� ��������� 

			XmlAttribute attributeByWriteInTag(tagWithValue);// ������� ������� �� ����� �������� � ��� ���

			node->setTagAttrs(attributeByWriteInTag);
		}

		if (this->docString[this->currentElementInStringNumber] == '?')
		{
			this->currentElementInStringNumber++;

			return;
		}
	}
}

void XmlParser::parseNode(XmlComment * node)
{
	string comment;

	int dashCounter = 0;  // 

	for (this->currentElementInStringNumber; this->currentElementInStringNumber < this->docString.length(); this->currentElementInStringNumber++)
	{
		//comment += this->docString[this->currentElementInStringNumber] == '-';

		if (this->docString[this->currentElementInStringNumber] == '!')  // ���� ����� ����� ���� �� ������� 2 �������� ��� ��� ��� ����� ���������� 
		{
			this->currentElementInStringNumber++;
			this->currentElementInStringNumber++;
			this->currentElementInStringNumber++;
		}

		if (this->docString[this->currentElementInStringNumber] == '-')  // ���� ����� - ���� �� ������� 2 �������� ��� ��� ��� ����� ��������� � ������ > 
		{
			this->currentElementInStringNumber++;
			this->currentElementInStringNumber++;

			node->setTagValue(comment); // �������� �������� �������� � ����� �� �������

			return;
		}

		comment += this->docString[this->currentElementInStringNumber];
	}
	return;
}

string XmlParser::findTagWithValue() // ������� ���� ������� �� ��������� �������  ��� �������� 
{
	string temp;
	
	int quoteCounter=0;

	for (this->currentElementInStringNumber; this->currentElementInStringNumber < this->docString.length(); this->currentElementInStringNumber++)
	{
		temp += this->docString[this->currentElementInStringNumber];
		
		if (this->docString[this->currentElementInStringNumber] == '"')
		{
			quoteCounter++;
		}

		if (this->docString[this->currentElementInStringNumber] == '"' && quoteCounter==2) // ���� ����� ������� 2 ���������� ������ 
		{
			return temp;
		}

		try
		{
			if (this->docString[this->currentElementInStringNumber] == '>') // ���� �� ��� � �� ����� ������� �� ������� ���������� 
			{
				throw exception("������� ������������� � ������� �������� �������� ");
			}
		}
		catch (const exception &ex)
		{
			cout << "\n" << "----------------ERORR--------------------" << endl;
			cout << ex.what() << endl;
			cout << "----------------------------------------" << endl;
			system("pause");
		}
	}



	return  temp;
}

bool XmlParser::parseNode(XmlTag * node)
{
	bool isFindTagName = false;

	string tagName;

	for (this->currentElementInStringNumber; this->currentElementInStringNumber < this->docString.length(); this->currentElementInStringNumber++)
	{
		if (this->docString[this->currentElementInStringNumber] != ' ' && isFindTagName == false)  // ������� ������ ����� �������� ����
		{
			tagName = this->getFullWord();// ���������� ����� �� ������� ������� 

			node->setTagName(tagName);

			isFindTagName = true;
		}

		if (isFindTagName == true && this->docString[this->currentElementInStringNumber] != ' ' && this->docString[this->currentElementInStringNumber] != '/' &&
			this->docString[this->currentElementInStringNumber] != '>') // ���� �� ���� ��� ���� � ������� ������� �� ������ � ��� �� ������ 
		{
			// ������� ����� ������� �� ��������� ����� ���������� ��� ������� ���� ����������� XmlAttribute � ����� ���������� ���������� ��������� � ��� ���� ������ xml 

			string tagWithValue = this->findTagWithValue();

			XmlAttribute attributeByWriteInTag(tagWithValue);// ������� ������� �� ����� �������� � ��� ���

			node->setTagAttrs(attributeByWriteInTag);
		}

		if (this->docString[this->currentElementInStringNumber] == '/' && this->docString[this->currentElementInStringNumber + 1] == '>')  // tru ������� ��� ������ ������������ � ���� ������� ��� ��� ������ 
		{
			// �������� � ��� ���� �������� ��� ��� ������ ����� ������ �� ����������� � ������ 

			node->setTagValue(node->getTagValue() + " /");  // �� ������� ������������� ��������  ���� ����� �� ������ ���������  ���� '/' � �����

			this->currentElementInStringNumber++;

			return false;
		}
		else
		{
			if (this->docString[this->currentElementInStringNumber] == '>')
			{
				return true;
			}
		}

		//return  tagName;// ���������� ������ �� ���� ������� �������� �� ��������� ������� ������� � ���� ���������� ������
	}

	return true;
}

void XmlParser::parseNode(XmlText * node)
{
	string tagValue;

	for (this->currentElementInStringNumber; this->currentElementInStringNumber < this->docString.length(); this->currentElementInStringNumber++)
	{
		if (this->docString[this->currentElementInStringNumber] == '<') // ����� ����� �� ����� � ����� < �� ������ ������� 
		{
			node->setTagValue(tagValue);
			return;
		}

		if (this->docString[this->currentElementInStringNumber] != ' ') // ��������� ����� � ������ ����� ���� 
		{
			tagValue += this->getFullWord() + ' ';

		}
	}

	return;
}

void XmlParser::read(XmlNode *parent)
{
	//XmlNode *parent = &(this->docyment); // �������� �� ������� ������ ��� ������ � ��������� 

	for (this->currentElementInStringNumber ; this->currentElementInStringNumber < this->docString.length(); this->currentElementInStringNumber++)
	{
		try
		{
			if (this->docString[this->currentElementInStringNumber] == '>')
			{
				throw exception("�������  ������ ������ ���������� ���� '>' ");
			}
		}
		catch (const exception &ex)
		{
			cout << "\n" << "----------------ERORR--------------------" << endl;
			cout << ex.what() << endl;
			cout << "----------------------------------------" << endl;
			system("pause");
		}
		
		if (this->docString[this->currentElementInStringNumber] == '/')// ���� ����� ��������� �� ��������� � ���� ������� ����� /t
		{
			this->currentElementInStringNumber++;

			this->currentElementInStringNumber++;
		}
		
		if (this->docString[this->currentElementInStringNumber] != '<' && this->docString[this->currentElementInStringNumber] != ' '  && 
			this->docString[this->currentElementInStringNumber] != '\t') // ���� ������� �� ������ � ������ �� ������ ��� ����� ���� 
		{
			XmlText *node= new XmlText;

			node->parent = parent; // ����� ������� ��������� � ���������

			this->parseNode(node);// ���������� ������ 

			parent->nodes.push_back(node);// ��������� � ����� ����� ������
		}
		
		if (this->docString[this->currentElementInStringNumber] == '<')// ������� ����� ��������� ����� ���� �������� ��������� ������� ������ � ������� ����
		{
			//XmlNode *node = new XmlNode;

			this->currentElementInStringNumber++;

			 // ����� ������� ��������� � ���������
			
			switch (this->docString[this->currentElementInStringNumber])
			{

			case '!': 
			{
				if (this->docString[this->currentElementInStringNumber + 1] == '[')// ���� �� ����� CDATA  �� � ������� ���������� ��� ��������� �������� 
				{
					this->skipCDATAFragment();

					break;
				}
				
				XmlComment *node = new XmlComment;

				node->parent = parent;

				this->parseNode(node);

				parent->nodes.push_back(node); // ������� �������� ������� � ����� ������� � ������ �������� ������� ������ ������ 

				break;
			}

			case '?':
			{
				XmlInstruction *node = new XmlInstruction;

				node->parent = parent;

				this->parseNode(node);
				parent->nodes.push_back(node); 
				break;
			}

			case '/': // ����� ����� �������������� ���� 
			{
				this->findTagEnd();
				
				return ;
			}

			case '<':
			{
				try
				{
						throw exception("�������  ������ ������ ������ ���� '< '");	
				}
				catch (const exception &ex)
				{

					cout << "\n" << "----------------ERORR--------------------" << endl;
					cout << ex.what() << endl;
					cout << "----------------------------------------" << endl;
					system("pause");
				}
				
				break;
			}

			default:// ��� ������ ��� �����  ������� ��� � ����� ��� ������� 
			{
				XmlTag *node = new XmlTag;
				
				node->parent = parent;
				
				
				
				if (this->parseNode(node)) //�������� ��������� ��� � ���� ������� � ���� ��� �������� �� ������� ��� �� �� ������ �� ��� ��� ���������� �������� ������� ����������  
				{
					this->currentElementInStringNumber++;
					
					this->read(node);

					parent->nodes.push_back(node); //  ������� ������� ������� ����������� � ����� ������� 
				}
				else
				{
					parent->nodes.push_back(node);
				}
				
				break;
			}

			}
			// ����� ���� ����������� ��� ��� �������� ������� ���������� 		
		}
	}
	return ;
}


void XmlNode::printXml(int depth) // �������� ������� ������ xml
{
	//XmlNode tempTag;
	
	for (size_t tagCounter=0; tagCounter < this->nodes.size(); tagCounter++)// ��� ��� �� �������� ����������� �������� � ������ ���� ����������� ����� �������� 
	{
		this->coutTab(depth);

		this->nodes[tagCounter]->coutNode(depth);
	}

	if (this->parent != NULL && this->nodes.size() != 0)
	{
		this->coutTab(depth-1);

		cout << "</" << this->getTagName() << ">" << endl;
	}
}
XmlParser::XmlParser(string path)
{
	ifstream fin;
	fin.exceptions(ifstream::badbit | ifstream::failbit); // ������� ����������� ���������� 

	try
	{
		fin.open(path);	
	}
	catch (const std::exception&)
	{
		cout << "���� �� ��� ������!" << endl;
	}

	string temp;

	cout << "--------------------------------XML FILE BEFORE PARSING IN TREE-----------------------------------------------------" << endl;

	while (!fin.eof())
	{
		getline(fin, temp);
		
		this->docString += temp;

		cout << temp << endl;
	}

	//cout << this->docString;

	XmlNode *element=new XmlNode;

	this->currentElementInStringNumber = 0;

	this->read(element);

	cout << "---------------------------------XML FILE AFTER PARSING IN TREE---------------------------------------------------- " << endl;

	element->printXml(0);

	cout << "-------------------------------------------------------------------------------------------------------------------" << endl;

	//this->printXml(element, 0);
}

void XmlParser::skipCDATAFragment()
{
	for (this->currentElementInStringNumber; this->currentElementInStringNumber < this->docString.size(); this->currentElementInStringNumber++)
	{
		if (this->docString[this->currentElementInStringNumber] == ']' &&this->docString[this->currentElementInStringNumber+1] == ']' && this->docString[this->currentElementInStringNumber+2] == '>')
		{
			this->currentElementInStringNumber++;
			this->currentElementInStringNumber++;
			return;
		}
	}
}

void XmlParser::findTagEnd()
{
	for (this->currentElementInStringNumber; this->currentElementInStringNumber < this->docString.size(); this->currentElementInStringNumber++)
	{
		if (this->docString[this->currentElementInStringNumber] == '>')
		{
			return;
		}
	}
}

void XmlNode::coutAllAttribute(vector<XmlAttribute> tagAttrs)// ������� ������� ��� �������� ���� 
{
	for (size_t attributeCounter = 0; attributeCounter < tagAttrs.size(); attributeCounter++)
	{
		cout <<" " <<tagAttrs[attributeCounter].getAttributeName() << "=" << tagAttrs[attributeCounter].getAttributeValue();
	}
}

void XmlNode::coutTab(int depth)
{
	for (int tabCounter = 0; tabCounter < depth; tabCounter++)
	{
		cout << "\t";
	}
}

void XmlInstruction::coutNode(int depth)
{
	cout << "<" << this->getTagName();

	this->coutAllAttribute(this->getTagAttrs());// �������� ������� ������ ��������� � �������� � ��� ������ ��������� 

	cout << "?>" << endl;
}



void XmlText::coutNode(int depth)
{
	cout << this->getTagValue() << endl;
}



void XmlTag::coutNode(int depth)
{
	cout << "<" << this->getTagName();

	this->coutAllAttribute(this->getTagAttrs());// �������� ������� ������ ��������� � �������� � ��� ������ ��������� 

	if (this->nodes.size() == 0) // ���� ������ ��������� ���� �� �� ������� ����� ���� ��� ��� ��� ����� 
	{
		cout << " />" << endl;
	}
	else
	{
		cout << ">" << endl;

		this->printXml(depth + 1);
	}

}



void XmlComment::coutNode(int depth)
{
	cout << "<!--" << this->getTagValue() << "-->" << endl;
}


