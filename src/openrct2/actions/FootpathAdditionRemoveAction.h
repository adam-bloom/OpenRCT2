/*****************************************************************************
 * Copyright (c) 2014-2020 OpenRCT2 developers
 *
 * For a complete list of all authors, please refer to contributors.md
 * Interested in contributing? Visit https://github.com/OpenRCT2/OpenRCT2
 *
 * OpenRCT2 is licensed under the GNU General Public License version 3.
 *****************************************************************************/

#pragma once

#include "GameAction.h"

DEFINE_GAME_ACTION(FootpathAdditionRemoveAction, GAME_COMMAND_REMOVE_FOOTPATH_ADDITION, GameActions::Result)
{
private:
    CoordsXYZ _loc;

public:
    FootpathAdditionRemoveAction() = default;

    FootpathAdditionRemoveAction(const CoordsXYZ& loc)
        : _loc(loc)
    {
    }
    void AcceptParameters(GameActionParameterVisitor & visitor) override;

    uint16_t GetActionFlags() const override
    {
        return GameAction::GetActionFlags();
    }

    void Serialise(DataSerialiser & stream) override;

    GameActions::Result::Ptr Query() const override;

    GameActions::Result::Ptr Execute() const override;
};