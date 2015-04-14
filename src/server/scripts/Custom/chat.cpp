#include "ScriptPCH.h"
#include "Chat.h"
#include <stdarg.h>
#include "GameObject.h"
#include "PoolMgr.h"
#include "ObjectAccessor.h"
#include "Transport.h"
#include "Language.h"
#include "Config.h"

std::string PLAYER_H_ICON;
std::string PLAYER_H_PREFIX;
std::string PLAYER_H_SUFFIX;
std::string PLAYER_A_ICON;
std::string PLAYER_A_PREFIX;
std::string PLAYER_A_SUFFIX;
std::string BUILDER_ICON;
std::string BUILDER_PREFIX;
std::string BUILDER_SUFFIX;
std::string ARCHITECT_ICON;
std::string ARCHITECT_PREFIX;
std::string ARCHITECT_SUFFIX;
std::string DUNGEONMASTER_ICON;
std::string DUNGEONMASTER_PREFIX;
std::string DUNGEONMASTER_SUFFIX;
std::string EVENTMASTER_ICON;
std::string EVENTMASTER_PREFIX;
std::string EVENTMASTER_SUFFIX;
std::string LOREMASTER_ICON;
std::string LOREMASTER_PREFIX;
std::string LOREMASTER_SUFFIX;
std::string COMMUNITYREPRESENTATIVE_ICON;
std::string COMMUNITYREPRESENTATIVE_PREFIX;
std::string COMMUNITYREPRESENTATIVE_SUFFIX;
std::string COMMUNITYMANAGER_ICON;
std::string COMMUNITYMANAGER_PREFIX;
std::string COMMUNITYMANAGER_SUFFIX;
std::string COUNCILMEMBER_ICON;
std::string COUNCILMEMBER_PREFIX;
std::string COUNCILMEMBER_SUFFIX;
std::string HEADDEVELOPER_ICON;
std::string HEADDEVELOPER_PREFIX;
std::string HEADDEVELOPER_SUFFIX;

std::string GetNameLink(Player* player)
{
	std::string name = player->GetName();
	std::string color;
	switch (player->getClass())
	{
	case CLASS_DEATH_KNIGHT:
		color = "|cffC41F3B";
		break;
	case CLASS_DRUID:
		color = "|cffFF7D0A";
		break;
	case CLASS_HUNTER:
		color = "|cffABD473";
		break;
	case CLASS_MAGE:
		color = "|cff69CCF0";
		break;
	case CLASS_PALADIN:
		color = "|cffF58CBA";
		break;
	case CLASS_PRIEST:
		color = "|cffFFFFFF";
		break;
	case CLASS_ROGUE:
		color = "|cffFFF569";
		break;
	case CLASS_SHAMAN:
		color = "|cff0070DE";
		break;
	case CLASS_WARLOCK:
		color = "|cff9482C9";
		break;
	case CLASS_WARRIOR:
		color = "|cffC79C6E";
		break;
	}
	return "|Hplayer:" + name + "|h|cffFFFFFF[" + color + name + "|cffFFFFFF]|h|r";
}

class chat : public CommandScript
{
public:
	chat() : CommandScript("chat"){}

	ChatCommand * GetCommands() const
	{
		static ChatCommand ChatCmdTable[] =
		{
			{ "mute", SEC_EVENTMASTER, true, &HandleMuteCommand, "", NULL },
			{ "unmute", SEC_EVENTMASTER, true, &HandleUnmuteCommand, "", NULL },
			{ "", SEC_PLAYER, true, &HandleChatCommand, "", NULL },
			{ NULL, 0, false, NULL, "", NULL }
		};

		static ChatCommand ChatCommandTable[] =
		{
			{ "chat", SEC_PLAYER, true, NULL, "", ChatCmdTable },
			{ NULL, 0, false, NULL, "", NULL }
		};

		return ChatCommandTable;
	}

	static bool HandleChatCommand(ChatHandler * handler, const char * args)
	{
		if (!handler->GetSession()->GetPlayer()->CanSpeak())
		{
			handler->PSendSysMessage("|cffFF0000You have been barred from the world chat!|r");
			handler->SetSentErrorMessage(true);
			return false;
		}

		std::string temp = args;

		if (!args || temp.find_first_not_of(' ') == std::string::npos)
		{
			handler->PSendSysMessage("|cffFF0000You can not send blank messages!|r");
			handler->SetSentErrorMessage(true);
			return false;
		}

		std::string msg = "";
		Player * player = handler->GetSession()->GetPlayer();

		if (!player->GetCommandStatus(TOGGLE_WORLD_CHAT)){
			handler->PSendSysMessage("|cffFF0000Chat is disabled, use .toggle chat on!|r");
			handler->SetSentErrorMessage(true);
			return false;
		}

		QueryResult worldMute = LoginDatabase.PQuery("SELECT is_muted FROM world_mute WHERE guid='%u'", player->GetSession()->GetAccountId());

		uint32 isMuted;

		if (!worldMute)
		{
			isMuted = 0;
		}

		if (worldMute)
		{
			Field * m_fields = worldMute->Fetch();
			isMuted = m_fields[0].GetUInt32();
		}

		if (isMuted == 1)
		{
			handler->PSendSysMessage("|cffFF0000You have been barred from the world chat!|r");
			handler->SetSentErrorMessage(true);
			return false;
		}

		switch (player->GetSession()->GetSecurity())
		{
		case SEC_PLAYER:
			if (player->GetTeam() == ALLIANCE)
			{
				msg += PLAYER_H_ICON;
				msg += PLAYER_H_PREFIX;
				msg += GetNameLink(player);
				msg += PLAYER_H_SUFFIX;
			}
			else
			{
				msg += PLAYER_A_ICON;
				msg += PLAYER_A_PREFIX;
				msg += GetNameLink(player);
				msg += PLAYER_A_SUFFIX;
			}
			break;
		case SEC_MODERATOR:
			msg += COMMUNITYMANAGER_ICON;
			msg += COMMUNITYMANAGER_PREFIX;
			msg += GetNameLink(player);
			msg += COMMUNITYMANAGER_SUFFIX;
			break;
		case SEC_GAMEMASTER:
			msg += BUILDER_ICON;
			msg += BUILDER_PREFIX;
			msg += GetNameLink(player);
			msg += BUILDER_SUFFIX;
			break;
		case SEC_ADMINISTRATOR:
			msg += DUNGEONMASTER_ICON;
			msg += DUNGEONMASTER_PREFIX;
			msg += GetNameLink(player);
			msg += DUNGEONMASTER_SUFFIX;
			break;
		case SEC_STAFFMEMBER:
			msg += ARCHITECT_ICON;
			msg += ARCHITECT_PREFIX;
			msg += GetNameLink(player);
			msg += ARCHITECT_SUFFIX;
			break;
		case SEC_EVENTMASTER:
			msg += EVENTMASTER_ICON;
			msg += EVENTMASTER_PREFIX;
			msg += GetNameLink(player);
			msg += EVENTMASTER_SUFFIX;
			break;
		case SEC_LOREMASTER:
			msg += LOREMASTER_ICON;
			msg += LOREMASTER_PREFIX;
			msg += GetNameLink(player);
			msg += LOREMASTER_SUFFIX;
			break;
		case SEC_COMMUNITYREPRESENTATIVE:
			msg += COMMUNITYREPRESENTATIVE_ICON;
			msg += COMMUNITYREPRESENTATIVE_PREFIX;
			msg += GetNameLink(player);
			msg += COMMUNITYREPRESENTATIVE_SUFFIX;
			break;
		case SEC_COUNCILMEMBER:
			msg += COUNCILMEMBER_ICON;
			msg += COUNCILMEMBER_PREFIX;
			msg += GetNameLink(player);
			msg += COUNCILMEMBER_SUFFIX;
			break;
		case SEC_HEADDEVELOPER:
			msg += HEADDEVELOPER_ICON;
			msg += HEADDEVELOPER_PREFIX;
			msg += GetNameLink(player);
			msg += HEADDEVELOPER_SUFFIX;
			break;
		case SEC_CONSOLE:
			msg += "|cfffa9900[ROOT] ";
			msg += GetNameLink(player);
			msg += " |cFFFFFFF0 : |cFF66FFFF";
			break;

		}

		sWorld->SendWorldChat(LANG_CHAT_COLOR, msg.c_str(), args);

		return true;
	}

	// World Mute Player
	static bool HandleMuteCommand(ChatHandler* handler, char const* args)
	{
		Player* target;
		ObjectGuid targetGuid;
		std::string targetName;
		if (!handler->extractPlayerTarget((char*)args, &target, &targetGuid, &targetName))
			return false;

		uint32 accountId = target ? target->GetSession()->GetAccountId() : sObjectMgr->GetPlayerAccountIdByGUID(targetGuid);

		if (handler->GetSession() && target == handler->GetSession()->GetPlayer())
		{
			handler->PSendSysMessage("|cffFF0000You cannot mute yourself!|r");
			handler->SetSentErrorMessage(true);
			return false;
		}

		QueryResult isMuted = LoginDatabase.PQuery("SELECT is_muted FROM world_mute WHERE guid='%u'", accountId);

		if (isMuted)
		{
			handler->PSendSysMessage("|cffFF0000%s is already muted!|r", (char*)args);
			handler->SetSentErrorMessage(true);
			return false;
		}

		handler->PSendSysMessage("|cffFF0000%s has been muted!|r", (char*)args);
		LoginDatabase.PExecute("INSERT INTO world_mute (guid, is_muted) VALUES ('%u', '1')", accountId);
		return true;
	}

	// Unmute Player
	static bool HandleUnmuteCommand(ChatHandler* handler, char const* args)
	{
		Player* target;
		ObjectGuid targetGuid;
		std::string targetName;
		if (!handler->extractPlayerTarget((char*)args, &target, &targetGuid, &targetName))
			return false;

		uint32 accountId = target ? target->GetSession()->GetAccountId() : sObjectMgr->GetPlayerAccountIdByGUID(targetGuid);

		if (handler->GetSession() && target == handler->GetSession()->GetPlayer())
		{
			handler->PSendSysMessage("|cffFF0000You cannot mute yourself!|r");
			handler->SetSentErrorMessage(true);
			return false;
		}

		QueryResult isMuted = LoginDatabase.PQuery("SELECT is_muted FROM world_mute WHERE guid='%u'", accountId);

		if (!isMuted)
		{
			handler->PSendSysMessage("|cffFF0000%s is not muted!|r", (char*)args);
			handler->SetSentErrorMessage(true);
			return false;
		}

		handler->PSendSysMessage("|cffFF0000%s has been unmuted!|r", (char*)args);
		LoginDatabase.PExecute("DELETE FROM world_mute WHERE guid='%u'", accountId);
		return true;
	}
};

class Script_chat_WorldScript : public WorldScript
{
public:
	Script_chat_WorldScript() : WorldScript("Script_chat_WorldScript") { }

	void OnConfigLoad(bool /*reload*/)
	{
		PLAYER_H_ICON = sConfigMgr->GetStringDefault("PLAYER_H_ICON", "");
		PLAYER_H_PREFIX = sConfigMgr->GetStringDefault("PLAYER_H_PREFIX", "");
		PLAYER_H_SUFFIX = sConfigMgr->GetStringDefault("PLAYER_H_SUFFIX", "");

		PLAYER_A_ICON = sConfigMgr->GetStringDefault("PLAYER_A_ICON", "");
		PLAYER_A_PREFIX = sConfigMgr->GetStringDefault("PLAYER_A_PREFIX", "");
		PLAYER_A_SUFFIX = sConfigMgr->GetStringDefault("PLAYER_A_SUFFIX", "");

		BUILDER_ICON = sConfigMgr->GetStringDefault("BUILDER_ICON", "");
		BUILDER_PREFIX = sConfigMgr->GetStringDefault("BUILDER_PREFIX", "");
		BUILDER_SUFFIX = sConfigMgr->GetStringDefault("BUILDER_SUFFIX", "");

		DUNGEONMASTER_ICON = sConfigMgr->GetStringDefault("DUNGEONMASTER_ICON", "");
		DUNGEONMASTER_PREFIX = sConfigMgr->GetStringDefault("DUNGEONMASTER_PREFIX", "");
		DUNGEONMASTER_SUFFIX = sConfigMgr->GetStringDefault("DUNGEONMASTER_SUFFIX", "");

		ARCHITECT_ICON = sConfigMgr->GetStringDefault("ARCHITECT_ICON", "");
		ARCHITECT_PREFIX = sConfigMgr->GetStringDefault("ARCHITECT_PREFIX", "");
		ARCHITECT_SUFFIX = sConfigMgr->GetStringDefault("ARCHITECT_SUFFIX", "");

		EVENTMASTER_ICON = sConfigMgr->GetStringDefault("EVENTMASTER_ICON", "");
		EVENTMASTER_PREFIX = sConfigMgr->GetStringDefault("EVENTMASTER_PREFIX", "");
		EVENTMASTER_SUFFIX = sConfigMgr->GetStringDefault("EVENTMASTER_SUFFIX", "");

		LOREMASTER_ICON = sConfigMgr->GetStringDefault("LOREMASTER_ICON", "");
		LOREMASTER_PREFIX = sConfigMgr->GetStringDefault("LOREMASTER_PREFIX", "");
		LOREMASTER_SUFFIX = sConfigMgr->GetStringDefault("LOREMASTER_SUFFIX", "");

		COMMUNITYREPRESENTATIVE_ICON = sConfigMgr->GetStringDefault("COMMUNITYREPRESENTATIVE_ICON", "");
		COMMUNITYREPRESENTATIVE_PREFIX = sConfigMgr->GetStringDefault("COMMUNITYREPRESENTATIVE_PREFIX", "");
		COMMUNITYREPRESENTATIVE_SUFFIX = sConfigMgr->GetStringDefault("COMMUNITYREPRESENTATIVE_SUFFIX", "");

		COMMUNITYMANAGER_ICON = sConfigMgr->GetStringDefault("COMMUNITYMANAGER_ICON", "");
		COMMUNITYMANAGER_PREFIX = sConfigMgr->GetStringDefault("COMMUNITYMANAGER_PREFIX", "");
		COMMUNITYMANAGER_SUFFIX = sConfigMgr->GetStringDefault("COMMUNITYMANAGER_SUFFIX", "");

		COUNCILMEMBER_ICON = sConfigMgr->GetStringDefault("COUNCILMEMBER_ICON", "");
		COUNCILMEMBER_PREFIX = sConfigMgr->GetStringDefault("COUNCILMEMBER_PREFIX", "");
		COUNCILMEMBER_SUFFIX = sConfigMgr->GetStringDefault("COUNCILMEMBER_SUFFIX", "");

		HEADDEVELOPER_ICON = sConfigMgr->GetStringDefault("HEADDEVELOPER_ICON", "");
		HEADDEVELOPER_PREFIX = sConfigMgr->GetStringDefault("HEADDEVELOPER_PREFIX", "");
		HEADDEVELOPER_SUFFIX = sConfigMgr->GetStringDefault("HEADDEVELOPER_SUFFIX", "");

	}
};

void AddSC_chat()
{
	new chat();
	new Script_chat_WorldScript;
}

