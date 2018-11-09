// XMLPublisher.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>
#include "Files.h"

#include "tinyxml2.h"

using namespace std;


//./xmlpublisher.exe
//./entity1/entity1.xml
//./entity2/entity2.xml
//整合所有entity的xml配置文件为一个

int main()
{
	std::vector<std::string> files;
	auto all_files = path::walk(path::curdir(), 2);
	for (auto filename : all_files)
	{
		if (path::splitext(filename)[1] == ".xml")
		{
			files.push_back(filename);
		}
	}

	std::string filename = "entity.xml";
	tinyxml2::XMLDocument *pDoc = new tinyxml2::XMLDocument();
	tinyxml2::XMLDeclaration *pDel = pDoc->NewDeclaration("xml version=\"1.0\" encoding=\"UTF-8\"");
	pDoc->LinkEndChild(pDel);

	tinyxml2::XMLElement *root = pDoc->NewElement("animationBox");
	pDoc->LinkEndChild(root);

	for (int i = 0; i < files.size(); i++)
	{
		tinyxml2::XMLDocument doc;
		doc.LoadFile(files[i].c_str());

		tinyxml2::XMLElement* animationBoxElement = doc.RootElement();
		tinyxml2::XMLElement* animationElement = animationBoxElement->FirstChildElement();
		tinyxml2::XMLElement* next = animationElement;

		while (animationElement)
		{
			next = animationElement->NextSiblingElement();
//			animationBoxElement->Unlink(animationElement);
			auto temp = animationElement->DeepClone(pDoc);
			root->LinkEndChild(temp);
			animationElement = next;
		}
	}

	pDoc->SaveFile(filename.c_str());
	//	pDoc->Print();
	delete pDoc;

	return 0;
}