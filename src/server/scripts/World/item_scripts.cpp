/*
 * Copyright (C) 2016+     AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE-GPL2
 * Copyright (C) 2008-2016 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
 */

/* ScriptData
SDName: Item_Scripts
SD%Complete: 100
SDComment: Items for a range of different items. See content below (in script)
SDCategory: Items
EndScriptData */

/* ContentData
item_nether_wraith_beacon(i31742)   Summons creatures for quest Becoming a Spellfire Tailor (q10832)
item_flying_machine(i34060, i34061)  Engineering crafted flying machines
item_gor_dreks_ointment(i30175)     Protecting Our Own(q10488)
item_only_for_flight                Items which should only useable while flying
EndContentData */

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "Spell.h"
#include "Player.h"
#include "AccountMgr.h"
#include "ScriptMgr.h"
#include "ScriptedGossip.h"
#include "Common.h"
#include "Chat.h"
#include "ObjectAccessor.h"
#include "ObjectMgr.h"
#include "SharedDefines.h"
#include "World.h"
#include "WorldSession.h"
#include "config.h"
#include "group.h"
#include "../Custom/CommonFunc/CommonFunc.h"
#include "Guild.h"

using namespace std;


/*#####
# item_only_for_flight
#####*/

enum OnlyForFlight
{
    SPELL_ARCANE_CHARGES    = 45072
};

class item_only_for_flight : public ItemScript
{
public:
    item_only_for_flight() : ItemScript("item_only_for_flight") { }

    bool OnUse(Player* player, Item* item, SpellCastTargets const& /*targets*/)
    {
        uint32 itemId = item->GetEntry();
        bool disabled = false;

        //for special scripts
        switch (itemId)
        {
           case 24538:
                if (player->GetAreaId() != 3628)
                    disabled = true;
                break;
           case 34489:
                if (player->GetZoneId() != 4080)
                    disabled = true;
                break;
           case 34475:
                if (const SpellInfo* spellInfo = sSpellMgr->GetSpellInfo(SPELL_ARCANE_CHARGES))
                    Spell::SendCastResult(player, spellInfo, 1, SPELL_FAILED_NOT_ON_GROUND);
                break;
        }

        // allow use in flight only
        if (player->IsInFlight() && !disabled)
            return false;

        // error
        player->SendEquipError(EQUIP_ERR_CANT_DO_RIGHT_NOW, item, nullptr);
        return true;
    }
};

/*#####
# item_nether_wraith_beacon
#####*/

class item_nether_wraith_beacon : public ItemScript
{
public:
    item_nether_wraith_beacon() : ItemScript("item_nether_wraith_beacon") { }

    bool OnUse(Player* player, Item* /*item*/, SpellCastTargets const& /*targets*/)
    {
        if (player->GetQuestStatus(10832) == QUEST_STATUS_INCOMPLETE)
        {
            if (Creature* nether = player->SummonCreature(22408, player->GetPositionX(), player->GetPositionY()+20, player->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN, 180000))
                nether->AI()->AttackStart(player);

            if (Creature* nether = player->SummonCreature(22408, player->GetPositionX(), player->GetPositionY()-20, player->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN, 180000))
                nether->AI()->AttackStart(player);
        }
        return false;
    }
};

/*#####
# item_gor_dreks_ointment
#####*/

class item_gor_dreks_ointment : public ItemScript
{
public:
    item_gor_dreks_ointment() : ItemScript("item_gor_dreks_ointment") { }

    bool OnUse(Player* player, Item* item, SpellCastTargets const& targets)
    {
        if (targets.GetUnitTarget() && targets.GetUnitTarget()->GetTypeId() == TYPEID_UNIT &&
            targets.GetUnitTarget()->GetEntry() == 20748 && !targets.GetUnitTarget()->HasAura(32578))
            return false;

        player->SendEquipError(EQUIP_ERR_CANT_DO_RIGHT_NOW, item, nullptr);
        return true;
    }
};

/*#####
# item_incendiary_explosives
#####*/

class item_incendiary_explosives : public ItemScript
{
public:
    item_incendiary_explosives() : ItemScript("item_incendiary_explosives") { }

    bool OnUse(Player* player, Item* item, SpellCastTargets const & /*targets*/)
    {
        if (player->FindNearestCreature(26248, 15) || player->FindNearestCreature(26249, 15))
            return false;
        else
        {
            player->SendEquipError(EQUIP_ERR_OUT_OF_RANGE, item, nullptr);
            return true;
        }
    }
};

/*#####
# item_mysterious_egg
#####*/

class item_mysterious_egg : public ItemScript
{
public:
    item_mysterious_egg() : ItemScript("item_mysterious_egg") { }

    bool OnExpire(Player* player, ItemTemplate const* /*pItemProto*/)
    {
        ItemPosCountVec dest;
        uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, 39883, 1); // Cracked Egg
        if (msg == EQUIP_ERR_OK)
            player->StoreNewItem(dest, 39883, true);

        return true;
    }
};

/*#####
# item_disgusting_jar
#####*/

class item_disgusting_jar : public ItemScript
{
public:
    item_disgusting_jar() : ItemScript("item_disgusting_jar") { }

    bool OnExpire(Player* player, ItemTemplate const* /*pItemProto*/)
    {
        ItemPosCountVec dest;
        uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, 44718, 1); // Ripe Disgusting Jar
        if (msg == EQUIP_ERR_OK)
            player->StoreNewItem(dest, 44718, true);

        return true;
    }
};

/*#####
# item_petrov_cluster_bombs
#####*/

enum PetrovClusterBombs
{
    SPELL_PETROV_BOMB           = 42406,
    AREA_ID_SHATTERED_STRAITS   = 4064,
    ZONE_ID_HOWLING             = 495
};

class item_petrov_cluster_bombs : public ItemScript
{
public:
    item_petrov_cluster_bombs() : ItemScript("item_petrov_cluster_bombs") { }

    bool OnUse(Player* player, Item* item, const SpellCastTargets & /*targets*/)
    {
        if (player->GetZoneId() != ZONE_ID_HOWLING)
            return false;

        if (!player->GetTransport() || player->GetAreaId() != AREA_ID_SHATTERED_STRAITS)
        {
            player->SendEquipError(EQUIP_ERR_NONE, item, nullptr);

            if (const SpellInfo* spellInfo = sSpellMgr->GetSpellInfo(SPELL_PETROV_BOMB))
                Spell::SendCastResult(player, spellInfo, 1, SPELL_FAILED_NOT_HERE);

            return true;
        }

        return false;
    }
};

enum CapturedFrog
{
    QUEST_THE_PERFECT_SPIES      = 25444,
    NPC_VANIRAS_SENTRY_TOTEM     = 40187
};

class item_captured_frog : public ItemScript
{
public:
    item_captured_frog() : ItemScript("item_captured_frog") { }

    bool OnUse(Player* player, Item* item, SpellCastTargets const& /*targets*/)
    {
        if (player->GetQuestStatus(QUEST_THE_PERFECT_SPIES) == QUEST_STATUS_INCOMPLETE)
        {
            if (player->FindNearestCreature(NPC_VANIRAS_SENTRY_TOTEM, 10.0f))
                return false;
            else
                player->SendEquipError(EQUIP_ERR_OUT_OF_RANGE, item, nullptr);
        }
        else
            player->SendEquipError(EQUIP_ERR_CANT_DO_RIGHT_NOW, item, nullptr);
        return true;
    }
};

// Only used currently for
// 19169: Nightfall
class item_generic_limit_chance_above_60 : public ItemScript
{
public:
    item_generic_limit_chance_above_60() : ItemScript("item_generic_limit_chance_above_60") { }

    bool OnCastItemCombatSpell(Player* /*player*/, Unit* victim, SpellInfo const* /*spellInfo*/, Item* /*item*/) override
    {
        // spell proc chance gets severely reduced on victims > 60 (formula unknown)
        if (victim->getLevel() > 60)
        {
            // gives ~0.1% proc chance at lvl 70
            float const lvlPenaltyFactor = 9.93f;
            float const failureChance = (victim->getLevel() - 60) * lvlPenaltyFactor;

            // base ppm chance was already rolled, only roll success chance
            return !roll_chance_f(failureChance);
        }

        return true;
    }
};

class item_add_spell : public ItemScript
{
public:
    item_add_spell() : ItemScript("item_add_spell") { }

    bool OnUse(Player* player, Item* item, SpellCastTargets const& targets)
    {
        Item* tar = targets.GetItemTarget();

        if (!tar || !item)
            return false;
        uint32 idd = tar->GetEntry();
        if (idd < 920000 && idd > 920018)
        {
            ChatHandler(player->GetSession()).SendSysMessage("这件装备没有符文槽.");
            return false;
        }

        ItemTemplate const* it = item->GetTemplate();

        uint32 ok = 0;
        bool okk = true;
        uint32 sl = 0;
        if (it->Spells[1].SpellId)
        {
            if (SpellItemEnchantmentEntry const* enchantEntry = sSpellItemEnchantmentStore.LookupEntry(it->Spells[1].SpellId))
                for (uint8 slot = PERM_ENCHANTMENT_SLOT; slot < MAX_ENCHANTMENT_SLOT; slot++)
                {
                    if (slot > 1 && slot < 7)
                        continue;

                    if (tar->GetEnchantmentId((EnchantmentSlot)slot))
                    {
                        sl++;
                        continue;
                    }

                    if (okk)
                    {
                        okk = false;
                        ok = slot;
                    }
                }
        }


        ItemTemplate const* its = tar->GetTemplate();
        if (sl >= its->ItemLevel)
        {
            ChatHandler(player->GetSession()).SendSysMessage("符文槽已经镶满了.");
            return true;
        }



        tar->SetEnchantment((EnchantmentSlot)ok, it->Spells[1].SpellId, 0, 0);
        player->DestroyItemCount(item->GetEntry(), 1, true);
        //	ChatHandler(player->GetSession()).PSendSysMessage("=%u =%u. sl=%u", ok, it->Spells[1].SpellId, sl);


        ChatHandler(player->GetSession()).SendSysMessage("符文已经插如成功了.");
        return true;
    }
};
using namespace std;

//--------------------秒专------by 泡面------------------------
class Max_skill : public ItemScript
{
public:
    Max_skill() :ItemScript("max_skill") {}

    int MaxSkillValue;
    int Expansion = sConfigMgr->GetIntDefault("Expansion", 1);


    bool OnUse(Player* player, Item* item, SpellCastTargets const& targets)
    {
        //-------根据config表控制的版本计算最大技能点数
        if (Expansion == 0) {
            MaxSkillValue = 300;
        }
        else if (Expansion == 1) {
            MaxSkillValue = 375;
        }
        else
            MaxSkillValue = 450;


        player->PlayerTalkClass->ClearMenus();
        if (player->HasSkill(171) && player->GetSkillValue(171) < MaxSkillValue)//炼金
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|TInterface/ICONS/Trade_Alchemy:30:30:0:0|t炼金", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
        }

        if (player->HasSkill(164) && player->GetSkillValue(164) < MaxSkillValue)//锻造
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|TInterface/ICONS/Trade_BlackSmithing:30:30:0:0|t锻造", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
        }

        if (player->HasSkill(333) && player->GetSkillValue(333) < MaxSkillValue)//附魔
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|TInterface/ICONS/Trade_Engraving:30:30:0:0|t附魔", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
        }

        if (player->HasSkill(202) & player->GetSkillValue(202) < MaxSkillValue)//工程
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|TInterface/ICONS/Trade_Engineering:30:30:0:0|t工程", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
        }

        if (player->HasSkill(182) && player->GetSkillValue(182) < MaxSkillValue)//草药
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|TInterface/ICONS/Trade_Herbalism:30:30:0:0|t草药", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
        }

        if (player->HasSkill(773) && player->GetSkillValue(773) < MaxSkillValue)//铭文
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|TInterface/ICONS/INV_Inscription_Tradeskill01:30:30:0:0|t铭文", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
        }

        if (player->HasSkill(755) & player->GetSkillValue(755) < MaxSkillValue)//珠宝
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|TInterface/ICONS/INV_Jewelcrafting_DragonsEye02:30:30:0:0|t珠宝", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
        }

        if (player->HasSkill(165) && player->GetSkillValue(165) < MaxSkillValue)//制皮
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|TInterface/ICONS/Trade_LeatherWorking:30:30:0:0|t制皮", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
        }

        if (player->HasSkill(186) && player->GetSkillValue(186) < MaxSkillValue)//采矿
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|TInterface/ICONS/Trade_Mining:30:30:0:0|t采矿", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9);
        }

        if (player->HasSkill(393) && player->GetSkillValue(393) < MaxSkillValue)//剥皮
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|TInterface/ICONS/INV_Misc_LeatherScrap_10:30:30:0:0|t剥皮", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 10);
        }

        if (player->HasSkill(197) && player->GetSkillValue(197) < MaxSkillValue)//裁缝
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|TInterface/ICONS/Trade_Tailoring:30:30:0:0|t裁缝", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11);
        }

        if (player->HasSkill(185) && player->GetSkillValue(185) < MaxSkillValue)//烹饪
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|TInterface/ICONS/INV_Misc_Food_64:30:30:0:0|t烹饪", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 12);
        }

        if (player->HasSkill(129) && player->GetSkillValue(129) < MaxSkillValue)//急救
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|TInterface/ICONS/Spell_Holy_SealOfSacrifice:30:30:0:0|t急救", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 13);
        }

        if (player->HasSkill(356) && player->GetSkillValue(356) < MaxSkillValue)//钓鱼
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|TInterface/ICONS/Trade_Fishing:30:30:0:0|t钓鱼", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 14);
        }

        player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, item->GetGUID());

        return true;
    }





    void OnGossipSelect(Player* player, Item* item, uint32 /*sender*/, uint32 action) override
    {
        switch (action)
        {
        case GOSSIP_ACTION_INFO_DEF + 1:
            player->SetSkill(171, player->GetSkillStep(171), MaxSkillValue, MaxSkillValue);
            player->DestroyItemCount((item->GetEntry()), 1, true);
            player->CastSpell(player, 47292, true);
            break;

        case GOSSIP_ACTION_INFO_DEF + 2:
            player->SetSkill(164, player->GetSkillStep(164), MaxSkillValue, MaxSkillValue);
            player->DestroyItemCount((item->GetEntry()), 1, true);
            player->CastSpell(player, 47292, true);
            break;

        case GOSSIP_ACTION_INFO_DEF + 3:
            player->SetSkill(333, player->GetSkillStep(333), MaxSkillValue, MaxSkillValue);
            player->DestroyItemCount((item->GetEntry()), 1, true);
            player->CastSpell(player, 47292, true);
            break;

        case GOSSIP_ACTION_INFO_DEF + 4:
            player->SetSkill(202, player->GetSkillStep(202), MaxSkillValue, MaxSkillValue);
            player->DestroyItemCount((item->GetEntry()), 1, true);
            player->CastSpell(player, 47292, true);
            break;


        case GOSSIP_ACTION_INFO_DEF + 5:
            player->SetSkill(182, player->GetSkillStep(182), MaxSkillValue, MaxSkillValue);
            player->DestroyItemCount((item->GetEntry()), 1, true);
            player->CastSpell(player, 47292, true);
            break;

        case GOSSIP_ACTION_INFO_DEF + 6:
            player->SetSkill(773, player->GetSkillStep(773), MaxSkillValue, MaxSkillValue);
            player->DestroyItemCount((item->GetEntry()), 1, true);
            player->CastSpell(player, 47292, true);
            break;

        case GOSSIP_ACTION_INFO_DEF + 7:
            player->SetSkill(755, player->GetSkillStep(755), MaxSkillValue, MaxSkillValue);
            player->DestroyItemCount((item->GetEntry()), 1, true);
            player->CastSpell(player, 47292, true);
            break;

        case GOSSIP_ACTION_INFO_DEF + 8:
            player->SetSkill(165, player->GetSkillStep(165), MaxSkillValue, MaxSkillValue);
            player->DestroyItemCount((item->GetEntry()), 1, true);
            player->CastSpell(player, 47292, true);
            break;

        case GOSSIP_ACTION_INFO_DEF + 9:
            player->SetSkill(186, player->GetSkillStep(186), MaxSkillValue, MaxSkillValue);
            player->DestroyItemCount((item->GetEntry()), 1, true);
            player->CastSpell(player, 47292, true);
            break;

        case GOSSIP_ACTION_INFO_DEF + 10:
            player->SetSkill(393, player->GetSkillStep(393), MaxSkillValue, MaxSkillValue);
            player->DestroyItemCount((item->GetEntry()), 1, true);
            player->CastSpell(player, 47292, true);
            break;

        case GOSSIP_ACTION_INFO_DEF + 11:
            player->SetSkill(197, player->GetSkillStep(197), MaxSkillValue, MaxSkillValue);
            player->DestroyItemCount((item->GetEntry()), 1, true);
            player->CastSpell(player, 47292, true);
            break;

        case GOSSIP_ACTION_INFO_DEF + 12:
            player->SetSkill(185, player->GetSkillStep(185), MaxSkillValue, MaxSkillValue);
            player->DestroyItemCount((item->GetEntry()), 1, true);
            player->CastSpell(player, 47292, true);
            break;

        case GOSSIP_ACTION_INFO_DEF + 13:
            player->SetSkill(129, player->GetSkillStep(129), MaxSkillValue, MaxSkillValue);
            player->DestroyItemCount((item->GetEntry()), 1, true);
            player->CastSpell(player, 47292, true);
            break;

        case GOSSIP_ACTION_INFO_DEF + 14:
            player->SetSkill(356, player->GetSkillStep(356), MaxSkillValue, MaxSkillValue);
            player->DestroyItemCount((item->GetEntry()), 1, true);
            player->CastSpell(player, 47292, true);
            break;

        }
        player->CLOSE_GOSSIP_MENU();
    }
};


//----------增加专业--by泡面

//专业GOSS表
struct SkillDataii
{
    uint32 Menu;
    uint32 Submenu;
    uint32 Icon;
    uint32 Id;
    string Name;
    uint32 spellid;
    uint32 skillid;
};

SkillDataii sData[] =
{
    { 1, 0, GOSSIP_ICON_BATTLE, 33630, "|TInterface/ICONS/Trade_Alchemy:30:30:0:0|t炼金", 2259, 171 },
    { 1, 0, GOSSIP_ICON_BATTLE, 28694, "|TInterface/ICONS/Trade_BlackSmithing:30:30:0:0|t锻造", 2018, 164 },
    { 1, 0, GOSSIP_ICON_BATTLE, 33633, "|TInterface/ICONS/Trade_Engraving:30:30:0:0|t附魔", 7411, 333 },
    { 1, 0, GOSSIP_ICON_BATTLE, 28697, "|TInterface/ICONS/Trade_Engineering:30:30:0:0|t工程", 4036, 202 },
    { 1, 0, GOSSIP_ICON_BATTLE, 28704, "|TInterface/ICONS/Trade_Herbalism:30:30:0:0|t草药", 2366, 182 },
    { 1, 0, GOSSIP_ICON_BATTLE, 28702, "|TInterface/ICONS/INV_Inscription_Tradeskill01:30:30:0:0|t铭文", 45357, 773 },
    { 1, 0, GOSSIP_ICON_BATTLE, 28701, "|TInterface/ICONS/INV_Jewelcrafting_DragonsEye02:30:30:0:0|t珠宝", 25229, 755 },
    { 1, 0, GOSSIP_ICON_BATTLE, 28700, "|TInterface/ICONS/Trade_LeatherWorking:30:30:0:0|t制皮", 2108, 165 },
    { 1, 0, GOSSIP_ICON_BATTLE, 28698, "|TInterface/ICONS/Trade_Mining:30:30:0:0|t采矿", 2575, 186 },
    { 1, 0, GOSSIP_ICON_BATTLE, 28696, "|TInterface/ICONS/INV_Misc_LeatherScrap_10:30:30:0:0|t剥皮", 8613, 393 },
    { 1, 0, GOSSIP_ICON_BATTLE, 28699, "|TInterface/ICONS/Trade_Tailoring:30:30:0:0|t裁缝", 3908, 197 },
    { 1, 0, GOSSIP_ICON_BATTLE, 28705, "|TInterface/ICONS/INV_Misc_Food_64:30:30:0:0|t烹饪", 2550, 185 },
    { 1, 0, GOSSIP_ICON_BATTLE, 28706, "|TInterface/ICONS/Spell_Holy_SealOfSacrifice:30:30:0:0|t急救", 3273, 129 },
    { 1, 0, GOSSIP_ICON_BATTLE, 28742, "|TInterface/ICONS/Trade_Fishing:30:30:0:0|t钓鱼", 7620, 356 },


};



class Add_skill : public ItemScript
{

public:
    Add_skill() : ItemScript("add_skill") {}

    bool OnUse(Player* player, Item* item, SpellCastTargets const& targets)
    {
        player->PlayerTalkClass->ClearMenus();

        for (uint8 i = 0; i < (sizeof(sData) / sizeof(*sData)); i++)
        {
            if (!(player->HasSkill(sData[i].skillid)))
                player->ADD_GOSSIP_ITEM(sData[i].Icon, sData[i].Name, GOSSIP_SENDER_MAIN, i);
        }
        player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, item->GetGUID());
        return true;
    }


    void OnGossipSelect(Player* player, Item* item, uint32 /*sender*/, uint32 action) override
    {
        uint32 freeProfs = player->GetFreePrimaryProfessionPoints();
        int skillid = sData[action].skillid;
        int spellid = sData[action].spellid;
        player->SetSkill(skillid, player->GetSkillStep(skillid), 1, 75);
        player->learnSpell(spellid);
        player->DestroyItemCount((item->GetEntry()), 1, true);
        player->CastSpell(player, 47292, true);

        /*检测使用前空余技能点数，如不为0，则增加专业后恢复*/
        if (freeProfs)
            player->SetFreePrimaryProfessions(freeProfs);

        player->CLOSE_GOSSIP_MENU();
    }

};
//----------------群拉

class Team_Call : public ItemScript
{
public:
    Team_Call() :ItemScript("team_call") {}

    bool OnUse(Player* player, Item* item, SpellCastTargets const& targets)
    {
        if (player->GetMap()->IsDungeon())
        {
            ChatHandler(player->GetSession()).PSendSysMessage("不允许在副本中使用群拉！！！，请到副本外使用");
            return false;
        }
        if (player->GetMap()->IsBattlegroundOrArena())
        {
            ChatHandler(player->GetSession()).PSendSysMessage("不允许在战场或竞技场使用群拉！！！");
            return false;
        }
        if (player->IsInCombat())
        {
            ChatHandler(player->GetSession()).PSendSysMessage("不允许在战斗中使用！！！");
            return false;
        }
        Group* grp = player->GetGroup();
        if (!grp)
        {
            ChatHandler(player->GetSession()).PSendSysMessage("你必须在一个队伍或团队中才能使用！");
            return false;
        }
        for (GroupReference* itr = grp->GetFirstMember(); itr != NULL; itr = itr->next())
        {

            Player* plGroup = itr->GetSource();

            if (!plGroup || plGroup == player || !plGroup->IsAlive() || !plGroup->IsInWorld())
            {
                continue;
            }
            sCF->SendLeaderSummon(player, plGroup);

        }

        return true;

    };


};


class Char_Rename : public ItemScript
{

public:
    Char_Rename() : ItemScript("item_rename") {}

    bool OnUse(Player* player, Item* item, SpellCastTargets const& targets)
    {
        player->SetAtLoginFlag(AT_LOGIN_RENAME);
        player->GetSession()->SendAreaTriggerMessage("重新上线以更改[名字]");
        ChatHandler(player->GetSession()).PSendSysMessage("重新上线以更改[名字]");
        player->DestroyItemCount((item->GetEntry()), 1, true);
        player->CastSpell(player, 47292, true);
        return true;
    }

};

class Char_Changerace : public ItemScript
{
public:
    Char_Changerace() :ItemScript("item_changerace") {}
    bool OnUse(Player* player, Item* item, SpellCastTargets const& targets)
    {
        player->SetAtLoginFlag(AT_LOGIN_CHANGE_RACE);
        player->GetSession()->SendAreaTriggerMessage("重新上线以更改[种族]");
        ChatHandler(player->GetSession()).PSendSysMessage("重新上线以更改[种族]");
        player->DestroyItemCount((item->GetEntry()), 1, true);
        player->CastSpell(player, 47292, true);
        if (Guild* guild = player->GetGuild())
            guild->HandleLeaveMember(player->GetSession());
        return true;
    }

};

class Char_Changerfacion : public ItemScript
{
public:
    Char_Changerfacion() :ItemScript("item_changefaction") {}
    bool OnUse(Player* player, Item* item, SpellCastTargets const& targets)
    {
        player->SetAtLoginFlag(AT_LOGIN_CHANGE_FACTION);
        player->GetSession()->SendAreaTriggerMessage("重新上线以更改[阵营]");
        ChatHandler(player->GetSession()).PSendSysMessage("重新上线以更改[阵营]");
        player->DestroyItemCount((item->GetEntry()), 1, true);
        player->CastSpell(player, 47292, true);
        if (Guild* guild = player->GetGuild())
            guild->HandleLeaveMember(player->GetSession());
        return true;
    }
};


void AddSC_item_scripts()
{
    new item_only_for_flight();
    new item_nether_wraith_beacon();
    new item_gor_dreks_ointment();
    new item_incendiary_explosives();
    new item_mysterious_egg();
    new item_disgusting_jar();
    new item_petrov_cluster_bombs();
    new item_captured_frog();
    new item_generic_limit_chance_above_60();
    new item_add_spell();
    new Max_skill();
    new Add_skill();
    new Team_Call();
    new Char_Changerfacion;
    new Char_Changerace;
    new Char_Rename;
}
