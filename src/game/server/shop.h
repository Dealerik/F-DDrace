// made by fokkonaut

#ifndef GAME_SHOP_H
#define GAME_SHOP_H

#include <engine/shared/protocol.h>
#include "gamecontext.h"

enum Items
{
	PAGE_NONE = -1,
	PAGE_MAIN,

	ITEM_RAINBOW,
	ITEM_BLOODY,
	ITEM_POLICE,
	ITEM_SPOOKY_GHOST,
	ITEM_ROOM_KEY,
	ITEM_VIP,
	ITEM_SPAWN_SHOTGUN,
	ITEM_SPAWN_GRENADE,
	ITEM_SPAWN_RIFLE,
	ITEM_NINJAJETPACK,
	ITEM_TASER,
	NUM_ITEMS_LIST,

	POLICE_RANK_1 = NUM_ITEMS_LIST,
	POLICE_RANK_2,
	POLICE_RANK_3,
	POLICE_RANK_4,
	POLICE_RANK_5,

	TASER_LEVEL_1,
	TASER_LEVEL_2,
	TASER_LEVEL_3,
	TASER_LEVEL_4,
	TASER_LEVEL_5,
	TASER_LEVEL_6,
	TASER_LEVEL_7,
	NUM_ITEMS
};

enum Time
{
	TIME_DEATH,
	TIME_DISCONNECT,
	TIME_FOREVER
};

enum States
{
	STATE_NONE = 0,
	STATE_OPENED_WINDOW,
	STATE_CONFIRM
};


class CShop
{
private:
	class CGameContext *m_pGameServer;
	class IServer *m_pServer;

	struct ItemInfo
	{
		bool m_Used;
		const char *m_pName;
		int m_Level;
		int m_Price;
		int m_Time;
		const char *m_pDescription;
	} m_aItems[NUM_ITEMS];

	void AddItem(const char *pName, int Level, int Price, int Time, const char *pDescription);
	void ShopWindow(int ClientID, int Dir);

	const char *GetHeadline(int Item);
	const char *GetTimeMessage(int Time);
	const char *FormatMotd(const char *pMsg, int Item);

	void SendWindow(int ClientID, int Item);

	void BuyItem(int ClientID, int Item);
	void ConfirmPurchase(int ClientID);
	void EndPurchase(int ClientID, bool Cancelled);

	int m_WindowPage[MAX_CLIENTS];
	int m_PurchaseState[MAX_CLIENTS];

	bool m_InShop[MAX_CLIENTS];
	int m_AntiSpamTick[MAX_CLIENTS];
	int m_MotdTick[MAX_CLIENTS];

	int m_BackgroundItem[MAX_CLIENTS];

public:

	CShop(CGameContext *pGameServer);
	void Tick(int ClientID);

	void Reset(int ClientID);

	void OnShopEnter(int ClientID);
	void OnShopLeave(int ClientID);

	void OnKeyPress(int ClientID, int Dir);
	bool CanChangePage(int ClientID);

	void OnPageChange(int ClientID, int Dir) { ShopWindow(ClientID, Dir); };
	bool IsInShop(int ClientID) { return m_InShop[ClientID]; };
	void ResetMotdTick(int ClientID) { m_MotdTick[ClientID] = 0; };
};

#endif
