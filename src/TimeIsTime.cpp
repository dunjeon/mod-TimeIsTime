/*
 * Azerothcore Module:     TimeIsTime
 * Author:                 Dunjeon
 * Contributing Author(s): lasyan3, vratam @ RegWorks
 * Version:                20210225
 * License:                GNU Affero General Public License v3.0.
 */

#include "ScriptMgr.h"
#include "Player.h"
#include "Config.h"
#include "Chat.h"

static bool timeistime_enable{};
static bool timeistime_announce{};
static float timeistime_speed_rate{};

class TimeIsTimeBeforeConfigLoad : public WorldScript {
public:

    TimeIsTimeBeforeConfigLoad() : WorldScript("TimeIsTimeBeforeConfigLoad") { }

    void OnBeforeConfigLoad(bool /*reload*/) override {
        timeistime_enable = sConfigMgr->GetBoolDefault("TimeIsTime.Enable", true);
        timeistime_announce = sConfigMgr->GetBoolDefault("TimeIsTime.Announce", true);
        timeistime_speed_rate = sConfigMgr->GetFloatDefault("TimeIsTime.SpeedRate", 1.0);
    }
};

class TimeIsTimeAnnounce : public PlayerScript
{
public:

    TimeIsTimeAnnounce() : PlayerScript("TimeIsTimeAnnounce") {}

    void OnLogin(Player* player) {
        // Announce Module
        if (timeistime_enable && timeistime_announce)
            ChatHandler(player->GetSession()).SendSysMessage("Server is running |cff4CFF00TimeIsTime |cffFFFF00 rmodule.");
    }
};

class TimeIsTime : public PlayerScript {
public:

    TimeIsTime() : PlayerScript("TimeIsTime") { }

    void OnSendInitialPacketsBeforeAddToMap(Player* player, WorldPacket& data) override {
        if (timeistime_enable) {
            uint32 speedtime = ((sWorld->GetGameTime() - sWorld->GetUptime()) + (sWorld->GetUptime() * timeistime_speed_rate));

            data.Initialize(SMSG_LOGIN_SETTIMESPEED, 4 + 4 + 4);
            data.AppendPackedTime(timeistime_speed_rate);
            data << float(0.01666667f) * timeistime_speed_rate;
            data << uint32(0);

            player->GetSession()->SendPacket(&data);
        }
    }
};

void AddTimeIsTimeScripts() {
    new TimeIsTimeBeforeConfigLoad();
    new TimeIsTimeAnnounce();
    new TimeIsTime();
}

