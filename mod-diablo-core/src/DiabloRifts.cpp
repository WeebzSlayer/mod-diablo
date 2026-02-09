#include "ScriptMgr.h"
#include "ScriptedGossip.h"
#include "Player.h"
#include "Creature.h"

class npc_persephone : public CreatureScript {
public:
    npc_persephone() : CreatureScript("npc_persephone") {}

    bool OnGossipHello(Player* player, Creature* creature) override {
        AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Open a Nephalem Rift (Endgame)", GOSSIP_SENDER_MAIN, 1);
        AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "I need supplies.", GOSSIP_SENDER_MAIN, 2);
        SendGossipMenuFor(player, 1, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action) override {
        CloseGossipMenuFor(player);

        if (action == 1) { // Start Rift
            player->CastSpell(player, 41232, true); // Portal Visual
            // Teleport to a designated "Rift Zone" (e.g., Map 1 Instance)
            player->TeleportTo(1, 16227.0f, 16252.0f, 13.0f, 0.0f); 
            
            // Spawn Rift Guardian at destination after delay
            player->SummonCreature(99001, 16220.0f, 16250.0f, 13.0f, 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 60000);
            ChatHandler(player->GetSession()).SendSysMessage("The Rift Guardian approaches...");
        }
        if (action == 2) {
            player->GetSession()->SendListInventory(creature->GetGUID());
        }
        return true;
    }
};