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
};

void AddSC_anim()
{
	new anim;
}