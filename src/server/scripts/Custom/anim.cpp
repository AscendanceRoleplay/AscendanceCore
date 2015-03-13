#include "ScriptPCH.h"
#include "Chat.h"
#include <stdarg.h>
#include "GameObject.h"
#include "PoolMgr.h"
#include "ObjectAccessor.h"
#include "Transport.h"
#include "Language.h"

using namespace std;

class anim : public CommandScript
{
public:
	anim() : CommandScript("anim") { }

	ChatCommand * GetCommands() const
	{

		static ChatCommand animcommandTable[] =
		{
			{ "anim", SEC_PLAYER, false, &HandleAnimCommand, "", NULL },
			{ "fly", SEC_PLAYER, false, &HandleFlyCommand, "", NULL },
		};
		return animcommandTable;
	}

	static bool HandleAnimCommand(ChatHandler* handler, const char* args)
	{
		if (!*args)
			return false;

		uint32 anim_id = atoi((char*)args);
		handler->GetSession()->GetPlayer()->SetUInt32Value(UNIT_NPC_EMOTESTATE, anim_id);

		return true;
	}

	static bool HandleFlyCommand(ChatHandler* handler, char const* args)
	{
		if (!*args)
			return false;

		Player* target = handler->getSelectedPlayer();
		if (!target)
			target = handler->GetSession()->GetPlayer();

		WorldPacket data;

		if (strncmp(args, "on", 3) == 0)
			target->SetCanFly(true);
		else if (strncmp(args, "off", 4) == 0)
			target->SetCanFly(false);
		else
		{
			handler->SendSysMessage(LANG_USE_BOL);
			return false;
		}
		handler->PSendSysMessage(LANG_COMMAND_FLYMODE_STATUS, handler->GetNameLink(target).c_str(), args);
		return true;
	}

};

void AddSC_anim()
{
	new anim;
}