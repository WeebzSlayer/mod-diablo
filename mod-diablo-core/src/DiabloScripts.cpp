#include "ScriptMgr.h"
#include "Player.h"
#include "Config.h"
#include "Chat.h"
#include "Unit.h"
#include "SpellInfo.h"

class DiabloSystem : public PlayerScript, public AllCreatureScript {
public:
    DiabloSystem() : PlayerScript("DiabloSystem"), AllCreatureScript("DiabloSystem") {}

    // --- MOVEMENT SPEED ---
    void OnLogin(Player* player) override {
        if (sConfigMgr->GetOption<bool>("Diablo.Enable", true)) {
            player->SetSpeed(MOVE_RUN, sConfigMgr->GetOption<float>("Diablo.MovementSpeed.Boost", 1.2f));
            ChatHandler(player->GetSession()).SendSysMessage("Diablo Mechanics Active: Movement Speed Increased.");
        }
    }

    // --- MONSTER DENSITY & CHAMPIONS ---
    void OnCreatureAdd(Creature* creature) override {
        if (!sConfigMgr->GetOption<bool>("Diablo.Enable", true) || creature->IsSummon())
            return;

        // Density Logic
        float densityChance = sConfigMgr->GetOption<float>("Diablo.Density.Chance", 25.0f);
        if (roll_chance_f(densityChance)) {
            // Summon a non-recursive clone
            TempSummon* summon = creature->SummonCreature(creature->GetEntry(), creature->GetPosition(), TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000);
        }

        // Champion Logic
        float champChance = sConfigMgr->GetOption<float>("Diablo.Champion.Chance", 5.0f);
        if (roll_chance_f(champChance)) {
            creature->SetObjectScale(1.3f);
            creature->SetMaxHealth(creature->GetMaxHealth() * sConfigMgr->GetOption<float>("Diablo.Champion.HealthMod", 3.0f));
            creature->SetHealth(creature->GetMaxHealth());
            creature->SetDisplayId(creature->GetNativeDisplayId()); // Reset display if needed
            creature->setFaction(14); // Hostile to all
            // Visual glow (Example: Blue Fire)
            creature->CastSpell(creature, 38330, true); 
        }
    }

    // --- HEALTH GLOBES & CLEAVE ---
    void OnPlayerKillCreature(Player* player, Creature* victim) override {
        float globeChance = sConfigMgr->GetOption<float>("Diablo.HealthGlobe.Chance", 5.0f);
        if (roll_chance_f(globeChance)) {
            uint32 healAmt = player->GetMaxHealth() * (sConfigMgr->GetOption<float>("Diablo.HealthGlobe.Percent", 10.0f) / 100.0f);
            player->HealBySpell(player, 20267, healAmt); // Visual heal
            ChatHandler(player->GetSession()).SendSysMessage("Health Globe consumed!");
        }
    }

    void OnPVPKill(Player* killer, Player* killed) override { /* Optional: PVP Rifts */ }
};

// --- CLEAVE & POTION OVERHAUL ---
class DiabloCombat : public UnitScript {
public:
    DiabloCombat() : UnitScript("DiabloCombat") {}

    void OnUnitDealDamage(Unit* attacker, Unit* victim, uint32& damage, DamageInfo& damageInfo) override {
        if (!attacker || !victim || !attacker->ToPlayer()) return;
        
        Player* player = attacker->ToPlayer();

        // Cleave Logic
        if (roll_chance_f(sConfigMgr->GetOption<float>("Diablo.Cleave.Chance", 30.0f))) {
            float radius = sConfigMgr->GetOption<float>("Diablo.Cleave.Radius", 8.0f);
            uint32 cleaveDamage = damage * (sConfigMgr->GetOption<float>("Diablo.Cleave.DamagePercent", 50.0f) / 100.0f);

            std::list<Creature*> targets;
            attacker->GetCreaturesWithDistanceInRange(targets, radius, true);
            for (auto target : targets) {
                if (target == victim || !target->IsAlive() || target->IsFriendlyTo(attacker)) continue;
                attacker->DealDamage(target, cleaveDamage);
                attacker->CastSpell(target, 31256, true); // Visual Cleave
            }
        }
    }
};

class DiabloPotions : public PlayerScript {
public:
    DiabloPotions() : PlayerScript("DiabloPotions") {}

    void OnSpellCast(Player* player, Spell* spell, bool skipCheck) override {
        uint32 spellId = spell->GetSpellInfo()->Id;
        
        // Example: Super Healing Potion ID is 27230
        if (spellId == 27230) { 
            float pct = sConfigMgr->GetOption<float>("Diablo.Potion.HealPercent", 35.0f);
            uint32 healAmt = player->GetMaxHealth() * (pct / 100.0f);
            player->HealBySpell(player, spellId, healAmt);
            // Mana too?
            uint32 manaAmt = player->GetMaxPower(POWER_MANA) * (pct / 100.0f);
            player->SetPower(POWER_MANA, player->GetPower(POWER_MANA) + manaAmt);
        }
    }
};