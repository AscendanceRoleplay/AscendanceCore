/* ScriptData
Name: toggle_commandscript
%Complete: 100
Comment: All toggle related commands
Category: commandscripts
EndScriptData */

#include "ScriptMgr.h"
#include "ObjectMgr.h"
#include "Chat.h"

class toggle_commandscript : public CommandScript
{
public:
	toggle_commandscript() : CommandScript("toggle_commandscript") { }

	ChatCommand* GetCommands() const
	{

		static ChatCommand toggleCommandTable[] =
		{
			{ "appear", SEC_PLAYER, false, &HandleToggleAppearCommand, "", NULL },
			{ "summon", SEC_PLAYER, false, &HandleToggleSummonCommand, "", NULL },
			{ "chat", SEC_PLAYER, false, &HandleToggleChatCommand, "", NULL },
			{ NULL, 0, false, NULL, "", NULL }
		};

		static ChatCommand commandTable[] =
		{
			{ "toggle", SEC_PLAYER, false, NULL, "", toggleCommandTable },
			{ NULL, 0, false, NULL, "", NULL }
		};
		return commandTable;
	}

	static bool HandleToggleAppearCommand(ChatHandler* handler, const char* args)
	{
		if (!handler->GetSession() && !handler->GetSession()->GetPlayer())
			return false;

		std::string argstr = (char*)args;

		Player* _player = handler->GetSession()->GetPlayer();

		if (!*args)
			argstr = (handler->GetSession()->GetPlayer()->GetCommandStatus(TOGGLE_APPEAR)) ? "off" : "on";

		if (argstr == "on")
		{
			_player->SetCommandStatusOn(TOGGLE_APPEAR);
			handler->SendSysMessage("Appear is ON. Players can appear to you.");
			return true;
		}
		else if (argstr == "off")
		{
			_player->SetCommandStatusOff(TOGGLE_APPEAR);
			handler->SendSysMessage("Appear is OFF. Players can't appear to you.");
			return true;
		}

		return false;
	}

	static bool HandleToggleSummonCommand(ChatHandler* handler, const char* args)
	{
		if (!handler->GetSession() && !handler->GetSession()->GetPlayer())
			return false;

		std::string argstr = (char*)args;

		Player* _player = handler->GetSession()->GetPlayer();

		if (!*args)
			argstr = (handler->GetSession()->GetPlayer()->GetCommandStatus(TOGGLE_SUMMON)) ? "off" : "on";

		if (argstr == "on")
		{
			_player->SetCommandStatusOn(TOGGLE_SUMMON);
			handler->SendSysMessage("Summon is ON. Players can summon you.");
			return true;
		}
		else if (argstr == "off")
		{
			_player->SetCommandStatusOff(TOGGLE_SUMMON);
			handler->SendSysMessage("Summon is OFF. Players can't summon you.");
			return true;
		}

		return false;
	}

	static bool HandleToggleChatCommand(ChatHandler* handler, const char* args)
	{
		if (!handler->GetSession() && !handler->GetSession()->GetPlayer())
			return false;

		std::string argstr = (char*)args;

		Player* _player = handler->GetSession()->GetPlayer();

		if (!*args)
			argstr = (handler->GetSession()->GetPlayer()->GetCommandStatus(TOGGLE_WORLD_CHAT)) ? "off" : "on";

		if (argstr == "on")
		{
			_player->SetCommandStatusOn(TOGGLE_WORLD_CHAT);
			handler->SendSysMessage("Appear is ON. Players can appear to you.");
			return true;
		}
		else if (argstr == "off")
		{
			_player->SetCommandStatusOff(TOGGLE_WORLD_CHAT);
			handler->SendSysMessage("Appear is OFF. Players can't appear to you.");
			return true;
		}

		return false;
	}
};

void AddSC_toggle_commandscript()
{
	new toggle_commandscript();
}