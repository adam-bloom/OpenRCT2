/*****************************************************************************
 * Copyright (c) 2014-2020 OpenRCT2 developers
 *
 * For a complete list of all authors, please refer to contributors.md
 * Interested in contributing? Visit https://github.com/OpenRCT2/OpenRCT2
 *
 * OpenRCT2 is licensed under the GNU General Public License version 3.
 *****************************************************************************/

#include "WallSetColourAction.h"

#include "../OpenRCT2.h"
#include "../management/Finance.h"
#include "../ride/Track.h"
#include "../ride/TrackData.h"
#include "../world/Banner.h"
#include "../world/LargeScenery.h"
#include "../world/MapAnimation.h"
#include "../world/Scenery.h"
#include "../world/SmallScenery.h"
#include "../world/Surface.h"

void WallSetColourAction::Serialise(DataSerialiser& stream)
{
    GameAction::Serialise(stream);

    stream << DS_TAG(_loc) << DS_TAG(_primaryColour) << DS_TAG(_secondaryColour) << DS_TAG(_tertiaryColour);
}

GameActions::Result::Ptr WallSetColourAction::Query() const
{
    auto res = MakeResult();
    res->ErrorTitle = STR_CANT_REPAINT_THIS;
    res->Position.x = _loc.x + 16;
    res->Position.y = _loc.y + 16;
    res->Position.z = _loc.z;

    res->Expenditure = ExpenditureType::Landscaping;

    if (!LocationValid(_loc))
    {
        return MakeResult(GameActions::Status::NotOwned, STR_CANT_REPAINT_THIS, STR_LAND_NOT_OWNED_BY_PARK);
    }

    if (!(gScreenFlags & SCREEN_FLAGS_SCENARIO_EDITOR) && !map_is_location_in_park(_loc) && !gCheatsSandboxMode)
    {
        return MakeResult(GameActions::Status::NotOwned, STR_CANT_REPAINT_THIS, STR_LAND_NOT_OWNED_BY_PARK);
    }

    auto wallElement = map_get_wall_element_at(_loc);
    if (wallElement == nullptr)
    {
        log_error(
            "Could not find wall element at: x = %d, y = %d, z = %d, direction = %u", _loc.x, _loc.y, _loc.z, _loc.direction);
        return MakeResult(GameActions::Status::InvalidParameters, STR_CANT_REPAINT_THIS);
    }

    if ((GetFlags() & GAME_COMMAND_FLAG_GHOST) && !(wallElement->IsGhost()))
    {
        return res;
    }

    rct_scenery_entry* sceneryEntry = wallElement->GetEntry();
    if (sceneryEntry == nullptr)
    {
        log_error("Could not find wall object");
        return MakeResult(GameActions::Status::Unknown, STR_CANT_REPAINT_THIS);
    }

    if (_primaryColour > 31)
    {
        log_error("Primary colour invalid: colour = %d", _primaryColour);
        return MakeResult(GameActions::Status::InvalidParameters, STR_CANT_REPAINT_THIS);
    }

    if (_secondaryColour > 31)
    {
        log_error("Secondary colour invalid: colour = %d", _secondaryColour);
        return MakeResult(GameActions::Status::InvalidParameters, STR_CANT_REPAINT_THIS);
    }

    if (sceneryEntry->wall.flags & WALL_SCENERY_HAS_TERNARY_COLOUR)
    {
        if (_tertiaryColour > 31)
        {
            log_error("Tertiary colour invalid: colour = %d", _tertiaryColour);
            return MakeResult(GameActions::Status::InvalidParameters, STR_CANT_REPAINT_THIS);
        }
    }
    return res;
}

GameActions::Result::Ptr WallSetColourAction::Execute() const
{
    auto res = MakeResult();
    res->ErrorTitle = STR_CANT_REPAINT_THIS;
    res->Position.x = _loc.x + 16;
    res->Position.y = _loc.y + 16;
    res->Position.z = _loc.z;
    res->Expenditure = ExpenditureType::Landscaping;

    auto wallElement = map_get_wall_element_at(_loc);
    if (wallElement == nullptr)
    {
        log_error(
            "Could not find wall element at: x = %d, y = %d, z = %d, direction = %u", _loc.x, _loc.y, _loc.z, _loc.direction);
        return MakeResult(GameActions::Status::InvalidParameters, STR_CANT_REPAINT_THIS);
    }

    if ((GetFlags() & GAME_COMMAND_FLAG_GHOST) && !(wallElement->IsGhost()))
    {
        return res;
    }

    rct_scenery_entry* sceneryEntry = wallElement->GetEntry();
    if (sceneryEntry == nullptr)
    {
        log_error("Could not find wall object");
        return MakeResult(GameActions::Status::Unknown, STR_CANT_REPAINT_THIS);
    }

    wallElement->SetPrimaryColour(_primaryColour);
    wallElement->SetSecondaryColour(_secondaryColour);

    if (sceneryEntry->wall.flags & WALL_SCENERY_HAS_TERNARY_COLOUR)
    {
        wallElement->SetTertiaryColour(_tertiaryColour);
    }
    map_invalidate_tile_zoom1({ _loc, _loc.z, _loc.z + 72 });

    return res;
}
