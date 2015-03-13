#include "ScriptPCH.h"
#include "Chat.h"
#include <stdarg.h>
#include "GameObject.h"
#include "PoolMgr.h"
#include "ObjectAccessor.h"
#include "Transport.h"
#include "Language.h"

using namespace std;

class misc : public CommandScript
{
public:
	misc() : CommandScript("anim") { }

	ChatCommand * GetCommands() const
	{

		static ChatCommand misccommandTable[] =
		{
			{ "fly", SEC_PLAYER, false, &HandleFlyCommand, "", NULL },
		};
		return misccommandTable;
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
		{
			if (target->HasUnitMovementFlag(MOVEMENTFLAG_CAN_FLY))
			{
				return false;
			}
			target->AddUnitMovementFlag(MOVEMENTFLAG_CAN_FLY);
			target->RemoveUnitMovementFlag(MOVEMENTFLAG_SWIMMING | MOVEMENTFLAG_SPLINE_ELEVATION);
			target->SetFall(false);
		}
		else if (strncmp(args, "off", 4) == 0)
		{
			if (!target->HasUnitMovementFlag(MOVEMENTFLAG_CAN_FLY))
			{
				return false;
			}
			target->RemoveUnitMovementFlag(MOVEMENTFLAG_CAN_FLY | MOVEMENTFLAG_MASK_MOVING_FLY);
			if (!target->IsLevitating())
			{
				target->SetFall(true);
			}
		}
		else
		{
			handler->SendSysMessage(LANG_USE_BOL);
			return false;
		}
		handler->PSendSysMessage(LANG_COMMAND_FLYMODE_STATUS, handler->GetNameLink(target).c_str(), args);
		return true;
	}

};

void AddSC_misc()
{
	new misc;
}