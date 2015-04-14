#include "ScriptPCH.h"

class customskills : public PlayerScript
{
public:

	customskills() : PlayerScript("newskills") { }
	void OnLogin(Player * player, bool)
	{
		player->GetSession()->SendNotification("|cffFFFF00Welcome to Ascendance!");
		player->SetCommandStatusOn(TOGGLE_WORLD_CHAT);
		player->SetSkill(293, 1, 1, 1); // Plate Mail
		player->SetSkill(413, 1, 1, 1); // Mail
		player->SetSkill(414, 1, 1, 1); // Leather
		player->SetSkill(415, 1, 1, 1);	// Cloth
		player->SetSkill(118, 1, 1, 1);	// Dual Wield
		player->SetSkill(43, 1, 1, 1); // One-Handed Swords
		player->SetSkill(55, 1, 1, 1); // Two-Handed Swords
		player->SetSkill(54, 1, 1, 1); // Maces
		player->SetSkill(160, 1, 1, 1); // Two-Handed Maces
		player->SetSkill(44, 1, 1, 1); // Axes
		player->SetSkill(172, 1, 1, 1); // Two-Handed Axes
		player->SetSkill(229, 1, 1, 1); // Polearms
		player->SetSkill(176, 1, 1, 1); // Thrown
		player->SetSkill(226, 1, 1, 1); // Crossbows
		player->SetSkill(46, 1, 1, 1); // Bows
		player->SetSkill(47, 1, 1, 1); // Guns
		player->SetSkill(136, 1, 1, 1); // Staves
		player->SetSkill(173, 1, 1, 1); // Daggers
		player->SetSkill(228, 1, 1, 1); // Wands
		player->SetSkill(433, 1, 1, 1); // Shields
		player->UpdateSkill(433, 1); // Shields
	}
};

void AddSC_customskills()
{
	new customskills;
}