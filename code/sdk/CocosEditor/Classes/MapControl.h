#ifndef MapControl_h_
#define MapControl_h_

#include "cocos2d.h"
using namespace cocos2d;

#include "message.h"


enum caozuo
{
	enum_caozuo_dragMap = 0,		//�϶���ͼ
	enum_caozuo_editStopData,	//�༭�赲����
	enum_caozuo_editEventArea,	//�༭�¼�����
	enum_caozuo_deleteEventArea,	//ɾ���¼���
	enum_caozuo_selectedEventArea,	//��ѯ�¼���
};

class Map_Director;
class Map_Layer;
class MapControl : public Layer, public LocalMessage
{
public:
	MapControl();
	~MapControl();

	virtual bool init();
	virtual void onEnter();
	virtual void onExit();

	CREATE_FUNC(MapControl);

	//��д��Ϣ���պ���
	virtual void ReceiveMessage(int messageType, MessageData * data);

	void touchBegan(int tile_x, int tile_y);
	void touchMove(int tile_x, int tile_y);
	void touchEnd(int tile_x, int tile_y);

	void handleDrag(MessageData * data);
	void handleStopEdit(MessageData * data);
	void handleEventArea(MessageData * data);
	void handleDeleteEventArea(MessageData * data);
	void handleSelectedEventArea(MessageData * data);
private:
	void update(float dt);
private:
	Vec2 beginTilePoint;
	int editStopData;	//�༭�赲����,-1���༭
	int eventAreaType;  //�¼���������
	caozuo caoz;
	Map_Director * mapDirector;
};

#endif