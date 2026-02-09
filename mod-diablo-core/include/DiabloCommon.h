#ifndef DIABLO_COMMON_H
#define DIABLO_COMMON_H

#include "Common.h"
#include "Config.h"
#include "ScriptMgr.h"
#include "Player.h"
#include "Creature.h"
#include "Chat.h"

// Entry IDs for Custom NPCs
enum DiabloEntries
{
    NPC_PERSEPHONE    = 99000,
    NPC_RIFT_GUARDIAN = 99001
};

// Configuration helper namespace to keep code clean
namespace DiabloConfig
{
    inline bool Enabled() { return sConfigMgr->GetOption<bool>("Diablo.Enable", true); }
    
    // Density & Champions
    inline float DensityChance() { return sConfigMgr->GetOption<float>("Diablo.Density.Chance", 25.0f); }
    inline float ChampChance()   { return sConfigMgr->GetOption<float>("Diablo.Champion.Chance", 5.0f); }
    
    // Combat
    inline float CleaveChance()  { return sConfigMgr->GetOption<float>("Diablo.Cleave.Chance", 30.0f); }
    inline float CleaveRadius()  { return sConfigMgr->GetOption<float>("Diablo.Cleave.Radius", 8.0f); }
    
    // Healing
    inline float PotionPercent() { return sConfigMgr->GetOption<float>("Diablo.Potion.HealPercent", 35.0f); }
    inline float GlobeChance()   { return sConfigMgr->GetOption<float>("Diablo.HealthGlobe.Chance", 5.0f); }
}

#endif