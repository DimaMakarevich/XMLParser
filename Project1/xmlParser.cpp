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

void XmlNode::setTagAttrs(XmlAttribute tagAttrs) // пушает в вектор атрибутов тега 
{
	this->tagAttrs.push_back(tagAttrs);
}

vector< XmlAttribute> XmlNode::getTagAttrs()  // функция должна вернуть вектор атрибутов   
{
	return this->tagAttrs;
}

XmlAttribute::XmlAttribute(string stringAttributeWithValue)// конструктор получает строку и разбивает ее на атрибут и элемент 
{
	string attributeName, attributeValue;

	bool isFindAttributeName = false;

	for (size_t currentElementNumber = 0; currentElementNumber < stringAttributeWithValue.length(); currentElementNumber++)
	{
		if (stringAttributeWithValue[currentElementNumber] == '=')// если дошли до равно значит имя трибута мы записали 
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

	this->setAttributeName(attributeName);// с помощью сетеров заносим наши данные в XmlAttribute
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

string XmlParser::getFullWord()// в функцию получаем первое символ строки и она возвращает все слово целиком до первого пробела 
{
	string stringByReturn;
	
	for (this->currentElementInStringNumber; this->currentElementInStringNumber < this->docString.length(); this->currentElementInStringNumber++)
	{
		if (this->docString[this->currentElementInStringNumber] != ' ' && this->docString[this->currentElementInStringNumber] != '>'  && this->docString[this->currentElementInStringNumber] != '<')// если добрались до первого пробела то возвращаем слово  
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
		if (this->docString[this->currentElementInStringNumber] == '?' && isParseInstructionName == false)// хаписали имя интрукции заходим если еще не нашли имя инструкции
		{
			isParseInstructionName = true;

			string instructionName = this->getFullWord();// получили название инструкции 

			node->setTagName(instructionName);
		}

		if (this->docString[this->currentElementInStringNumber] != ' ' && this->docString[this->currentElementInStringNumber] != '?')
		{
			string tagWithValue = this->findTagWithValue();// ищем тег в интрукции обработки 

			XmlAttribute attributeByWriteInTag(tagWithValue);// атрибут который мы дожны записать в наш тег

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

		if (this->docString[this->currentElementInStringNumber] == '!')  // если нашли воскл знак то скипаем 2 элемента так как они будут черточками 
		{
			this->currentElementInStringNumber++;
			this->currentElementInStringNumber++;
			this->currentElementInStringNumber++;
		}

		if (this->docString[this->currentElementInStringNumber] == '-')  // если нашли - знак то скипаем 2 элемента так как они будут черточкой и знаком > 
		{
			this->currentElementInStringNumber++;
			this->currentElementInStringNumber++;

			node->setTagValue(comment); // записали значение коммента и вышли из функции

			return;
		}

		comment += this->docString[this->currentElementInStringNumber];
	}
	return;
}

string XmlParser::findTagWithValue() // функция ищет атрибут до последней кавычки  его значения 
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

		if (this->docString[this->currentElementInStringNumber] == '"' && quoteCounter==2) // если число кавычек 2 возвращаем строку 
		{
			return temp;
		}

		try
		{
			if (this->docString[this->currentElementInStringNumber] == '>') // если мы так и не нашли кавычку то бросаем исключение 
			{
				throw exception("Имеется незаключенное в кавычки значение атрибута ");
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
		if (this->docString[this->currentElementInStringNumber] != ' ' && isFindTagName == false)  // находим первое слово название тега
		{
			tagName = this->getFullWord();// вовзращает слово до первого пробела 

			node->setTagName(tagName);

			isFindTagName = true;
		}

		if (isFindTagName == true && this->docString[this->currentElementInStringNumber] != ' ' && this->docString[this->currentElementInStringNumber] != '/' &&
			this->docString[this->currentElementInStringNumber] != '>') // если мы нашл имя тега и текущий элемент не пробел и тег не пустой 
		{
			// сначала нашли атрибут со значением потом распарсили это атрибут черз констркутор XmlAttribute и потом установили содержимое атрибутов в наш узел дерева xml 

			string tagWithValue = this->findTagWithValue();

			XmlAttribute attributeByWriteInTag(tagWithValue);// атрибут который мы дожны записать в наш тег

			node->setTagAttrs(attributeByWriteInTag);
		}

		if (this->docString[this->currentElementInStringNumber] == '/' && this->docString[this->currentElementInStringNumber + 1] == '>')  // tru говорит что дерево продолжается а фалс говорит что тег пустой 
		{
			// возможно у нам надо сообщить что тег пустой чтобы дальше не углубляться в дерево 

			node->setTagValue(node->getTagValue() + " /");  // мы сетером устанавливаем значение  тоже самое но только добавляем  знак '/' в конце

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

		//return  tagName;// возвращать ничего не надо функцию получает по указателю элемент массива и сама записывает данные
	}

	return true;
}

void XmlParser::parseNode(XmlText * node)
{
	string tagValue;

	for (this->currentElementInStringNumber; this->currentElementInStringNumber < this->docString.length(); this->currentElementInStringNumber++)
	{
		if (this->docString[this->currentElementInStringNumber] == '<') // когда дошли до конца и нашли < то делаем ретрунь 
		{
			node->setTagValue(tagValue);
			return;
		}

		if (this->docString[this->currentElementInStringNumber] != ' ') // добавляем слово и пробел после него 
		{
			tagValue += this->getFullWord() + ' ';

		}
	}

	return;
}

void XmlParser::read(XmlNode *parent)
{
	//XmlNode *parent = &(this->docyment); // правилно ли передаю всякие там ссылки и указатели 

	for (this->currentElementInStringNumber ; this->currentElementInStringNumber < this->docString.length(); this->currentElementInStringNumber++)
	{
		try
		{
			if (this->docString[this->currentElementInStringNumber] == '>')
			{
				throw exception("Имеется  лишний символ завершения тега '>' ");
			}
		}
		catch (const exception &ex)
		{
			cout << "\n" << "----------------ERORR--------------------" << endl;
			cout << ex.what() << endl;
			cout << "----------------------------------------" << endl;
			system("pause");
		}
		
		if (this->docString[this->currentElementInStringNumber] == '/')// если нашли табуляцию то переходим к след символы после /t
		{
			this->currentElementInStringNumber++;

			this->currentElementInStringNumber++;
		}
		
		if (this->docString[this->currentElementInStringNumber] != '<' && this->docString[this->currentElementInStringNumber] != ' '  && 
			this->docString[this->currentElementInStringNumber] != '\t') // если элемент не скобка и пробел то значит это текст тега 
		{
			XmlText *node= new XmlText;

			node->parent = parent; // новый элемент связываем с родителем

			this->parseNode(node);// перегрузка метода 

			parent->nodes.push_back(node);// добавляем в векор новый элемнт
		}
		
		if (this->docString[this->currentElementInStringNumber] == '<')// условие парса различных тегов надо добавить занесение обыного текста в значене тега
		{
			//XmlNode *node = new XmlNode;

			this->currentElementInStringNumber++;

			 // новый элемент связываем с родителем
			
			switch (this->docString[this->currentElementInStringNumber])
			{

			case '!': 
			{
				if (this->docString[this->currentElementInStringNumber + 1] == '[')// если мы нашли CDATA  то п олнстью игнорируем его обработку парсером 
				{
					this->skipCDATAFragment();

					break;
				}
				
				XmlComment *node = new XmlComment;

				node->parent = parent;

				this->parseNode(node);

				parent->nodes.push_back(node); // сначала запоняем вершину а после заносим в вектор обратный порядок нельзя делать 

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

			case '/': // найти конец завершающегося тега 
			{
				this->findTagEnd();
				
				return ;
			}

			case '<':
			{
				try
				{
						throw exception("Имеется  лишний символ начала тега '< '");	
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

			default:// это значит что нашли  обычный тег и будем его парсить 
			{
				XmlTag *node = new XmlTag;
				
				node->parent = parent;
				
				
				
				if (this->parseNode(node)) //передаем созданный тег в нашу функцию и если при возврате он говорит что он не пустой то еще раз рекурсивно вызываем функцию считывания  
				{
					this->currentElementInStringNumber++;
					
					this->read(node);

					parent->nodes.push_back(node); //  поменял порядок сначала считыванием а потом заносим 
				}
				else
				{
					parent->nodes.push_back(node);
				}
				
				break;
			}

			}
			// здесь надо рекурсивнно еще раз вызывать функцию считывания 		
		}
	}
	return ;
}


void XmlNode::printXml(int depth) // фнкуциия выводит дерево xml
{
	//XmlNode tempTag;
	
	for (size_t tagCounter=0; tagCounter < this->nodes.size(); tagCounter++)// так как мы передаем родиельский элементы и дальше надо производить рабор дочерних 
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
	fin.exceptions(ifstream::badbit | ifstream::failbit); // убираем стандартнеы исключания 

	try
	{
		fin.open(path);	
	}
	catch (const std::exception&)
	{
		cout << "Файл не был открыт!" << endl;
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

void XmlNode::coutAllAttribute(vector<XmlAttribute> tagAttrs)// функция выводит все атрибуты тега 
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

	this->coutAllAttribute(this->getTagAttrs());// вызываем функцию вывода атрибутов и передаем в нее вектор атрибутов 

	cout << "?>" << endl;
}



void XmlText::coutNode(int depth)
{
	cout << this->getTagValue() << endl;
}



void XmlTag::coutNode(int depth)
{
	cout << "<" << this->getTagName();

	this->coutAllAttribute(this->getTagAttrs());// вызываем функцию вывода атрибутов и передаем в нее вектор атрибутов 

	if (this->nodes.size() == 0) // если вектор елементов пуст то то выводим конец тега так как тег пстой 
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


