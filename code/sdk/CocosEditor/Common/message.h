#ifndef _LocalMessage_h_
#define _LocalMessage_h_


#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <map>
#include <list>
#include <deque>
using namespace std;

enum
{
	enum_MessageType_begin = 0,
	//-------------------------------
	
	enum_MessageType_test,
	enum_MessageType_NewCreateMap,	//新创建地图
	enum_MessageType_DragMode,		//拖拽模式
	enum_MessageType_EditStopData,	//编辑阻挡数据
	enum_MessageType_EditEventArea, //编辑事件区域
	enum_MessageType_DeleteEventArea,	//删除事件区域
	enum_MessageType_SelectedEventArea,	//查询事件区域
	enum_MessageType_ShowQMessageBox,	//显示消息弹框
	//-------------------------------
	enum_MessageType_end
};




class MessageData;
class LocalMessage
{
public:
	LocalMessage(){}
	~LocalMessage(){}

	virtual void ReceiveMessage(int messageType, MessageData * data) = 0;
};

class InterfaceData{
};
template<typename T>
class TemplateData : public InterfaceData
{
public:
	TemplateData(){}
	~TemplateData(){}
	T t;
};

class MessageData
{
public:
	MessageData(){}
	~MessageData(){
		while (!dequeData.empty())
		{
			InterfaceData * data = dequeData.front();
			dequeData.pop_front();
			if (!data)
				continue;
			delete data;
		}
	}

	template<typename T>
	void push(T t)
	{
		TemplateData<T> * data = new TemplateData<T>;
		data->t = t;

		dequeData.push_back(data);
	}

	template<typename T>
	T pop()
	{
		T re;
		InterfaceData * data = dequeData.front();
		re = ((TemplateData<T> *)data)->t;
		delete data;

		dequeData.pop_front();
		return re;
	}

private:
	deque<InterfaceData *> dequeData;
};


class MessageDataSet
{
public:
	MessageDataSet(){}
	~MessageDataSet(){}

	LocalMessage * obj;
	int priority;
};


class LocalMessageManage
{
private:
	LocalMessageManage(){
		this->initData();
	}
	~LocalMessageManage(){
		this->deleteAllMessage();
	}

public:
	static LocalMessageManage * getObject()
	{
		static LocalMessageManage mess;
		return &mess;
	}

	void initData()
	{
		for (int i = enum_MessageType_begin + 1; i < enum_MessageType_end; i++)
		{
			std::list<MessageDataSet *> _list;
			map_message.insert(std::map<int, std::list<MessageDataSet *>>::value_type(i, _list));
		}
	}

	int registerMessage(LocalMessage * obj, int messageType, int priority = 0)
	{
		std::map<int, std::list<MessageDataSet *>>::iterator it = map_message.find(messageType);
		if (it == map_message.end())
		{
			return -1;
		}

		MessageDataSet * dataSet = new MessageDataSet();
		dataSet->obj = obj;
		dataSet->priority = priority;

		std::list<MessageDataSet *> * _list = &map_message[messageType];

		std::list<MessageDataSet *>::iterator itP = (*_list).begin();

		for (; itP != (*_list).end(); itP++)
		{
			if (!(*itP))
				continue;

			if ((*itP)->obj == obj)
				return -1;
		}

		for (itP = (*_list).begin(); itP != (*_list).end(); itP++)
		{
			if (priority > (*itP)->priority)
			{
				(*_list).insert(itP, dataSet);
				return 0;
			}
		}
		
		if (itP != (*_list).begin())
			itP--;

		(*_list).insert(itP, dataSet);

		return 0;
	}

	int sendMessage(int messageType, MessageData * messageData, bool share = true)
	{
		std::map<int, std::list<MessageDataSet *>>::iterator it = map_message.find(messageType);
		if (it == map_message.end())
		{
			return -1;
		}

		std::list<MessageDataSet *> * _list = &map_message[messageType];
		std::list<MessageDataSet *>::iterator itP = (*_list).begin();
		for (; itP != (*_list).end(); itP++)
		{
			if (!(*itP)->obj)
				continue;
			(*itP)->obj->ReceiveMessage(messageType, messageData);
			if (!share)
				break;
		}

	}

	int deleteMessage(LocalMessage * obj, int messageType)
	{
		std::map<int, std::list<MessageDataSet *>>::iterator it = map_message.find(messageType);
		if (it == map_message.end())
		{
			return -1;
		}

		std::list<MessageDataSet *> * _list = &map_message[messageType];
		std::list<MessageDataSet *>::iterator itP = (*_list).begin();
		for (; itP != (*_list).end(); itP++)
		{
			if (!(*itP))
				continue;

			if ((*itP)->obj == obj)
			{
				delete *itP;

				(*_list).erase(itP);
				return 0;
			}
		}

		return -2;
	}

	void deleteAllMessage()
	{
		for (int i = enum_MessageType_begin + 1; i < enum_MessageType_end; i++)
		{
			std::list<MessageDataSet *> * _list = &map_message[i];
			if (_list)
				continue;

			for (std::list<MessageDataSet *>::iterator it = (*_list).begin(); it != (*_list).end(); it++)
			{
				if (*it)
					delete *it;
			}

			(*_list).clear();
		}
	}

private:
	std::map<int, std::list<MessageDataSet *>> map_message;
};

#endif
///

//////////////////////////////////test/////////////////////////////

//示例：

/*

class Test
{
public:

	int x;
};
class A : public LocalMessage
{
public:
	A()
	{
		LocalMessageManage::getObject()->registerMessage(this, enum_MessageType_test);
	}
	~A()
	{
		LocalMessageManage::getObject()->deleteMessage(this, enum_MessageType_test);
	}
	virtual void ReceiveMessage(int messageType, MessageData * data)
	{
		switch (messageType)
		{
		case enum_MessageType_test:
			testMessage(data);
			break;
		default:
			break;
		}
	}

	void testMessage(MessageData * data)
	{
		int x = data->pop<int>();
		float y = data->pop<float>();
		char * c = data->pop<char *>();
		Test t = data->pop<Test>();

		printf("int x:%d\n",x);
		printf("float y:%f\n",y);
		printf("char * c:%s\n",c);
		printf("obj :%d\n",t.x);
	}
};
class B
{
public:
	void send()
	{
		MessageData mess;
		mess.push<int>(1314);
		mess.push<float>(12.2222);
		mess.push<char *>("nihaowohaodajiahao");

		Test t;
		t.x = 123321;
		mess.push<Test>(t);
		LocalMessageManage::getObject()->sendMessage(enum_MessageType_test,&mess);
	}
};

*/