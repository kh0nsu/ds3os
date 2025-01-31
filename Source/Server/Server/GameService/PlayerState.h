/*
 * Dark Souls 3 - Open Server
 * Copyright (C) 2021 Tim Leonard
 *
 * This program is free software; licensed under the MIT license.
 * You should have received a copy of the license along with this program.
 * If not, see <https://opensource.org/licenses/MIT>.
 */

#pragma once

#include <string>

#include "Protobuf/Protobufs.h"

#include "Server/GameService/Utils/GameIds.h"

// Represents the in-game state of a player. Each game client owns an instance of this class.

#define DEFINE_FIELD(type, name, default_value)                             \
    private: type name = default_value;                                     \
    public:                                                                 \
        const type& Get##name() const { return name; }                      \
        type& Get##name##_Mutable() { return name; }                        \
        void Set##name(const type& input) { name = input; Mutated(); }   

struct PlayerState
{
private:
    size_t Generation;

public:
    size_t GetGeneration() { return Generation; }
    void Mutated() { Generation++; }

    // Steam ID of logged in user as a hex string.
    DEFINE_FIELD(std::string, SteamId, "")    
    
    // Unique ID of the player account. Used for identifying the 
    // player in most packets past initial login, steam id is not used.
    DEFINE_FIELD(uint32_t, PlayerId, 0)
    
    // What character id they are currently playing.
    DEFINE_FIELD(uint32_t, CharacterId, 0)
    
    // The name of the character the player is currently playing with. Will be empty
    // until the first RequestUpdatePlayerStatus is invoked.
    DEFINE_FIELD(std::string, CharacterName, "")    
    
    // Current online matching area the player is in.
    DEFINE_FIELD(OnlineAreaId, CurrentArea, OnlineAreaId::None)
    
    // If the player is currently in a state they can be invaded in.
    DEFINE_FIELD(bool, IsInvadable, false)
    
    // Players current soul level.
    DEFINE_FIELD(int, SoulLevel, 0)
    
    // Players maximum weapon level. 
    DEFINE_FIELD(int, MaxWeaponLevel, 0)
    
    // What type of visitor the player can currently be summoned as.
    DEFINE_FIELD(Frpg2RequestMessage::VisitorPool, VisitorPool, Frpg2RequestMessage::VisitorPool::VisitorPool_None)
    
    // Information the player sends and periodically patches with 
    // RequestUpdatePlayerStatus requests.
    DEFINE_FIELD(Frpg2PlayerData::AllStatus, PlayerStatus, Frpg2PlayerData::AllStatus())
};

#undef DEFINE_FIELD