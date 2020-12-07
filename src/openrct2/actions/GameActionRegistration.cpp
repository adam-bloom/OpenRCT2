/*****************************************************************************
 * Copyright (c) 2014-2020 OpenRCT2 developers
 *
 * For a complete list of all authors, please refer to contributors.md
 * Interested in contributing? Visit https://github.com/OpenRCT2/OpenRCT2
 *
 * OpenRCT2 is licensed under the GNU General Public License version 3.
 *****************************************************************************/

#include "BalloonPressAction.h"
#include "BannerPlaceAction.h"
#include "BannerRemoveAction.h"
#include "BannerSetColourAction.h"
#include "BannerSetNameAction.h"
#include "BannerSetStyleAction.h"
#include "ClearAction.h"
#include "ClimateSetAction.h"
#include "CustomAction.h"
#include "FootpathAdditionPlaceAction.h"
#include "FootpathAdditionRemoveAction.h"
#include "FootpathPlaceAction.h"
#include "FootpathPlaceFromTrackAction.h"
#include "FootpathRemoveAction.h"
#include "GameAction.h"
#include "GuestSetFlagsAction.h"
#include "GuestSetNameAction.h"
#include "LandBuyRightsAction.h"
#include "LandLowerAction.h"
#include "LandRaiseAction.h"
#include "LandSetHeightAction.h"
#include "LandSetRightsAction.h"
#include "LandSmoothAction.h"
#include "LargeSceneryPlaceAction.h"
#include "LargeSceneryRemoveAction.h"
#include "LargeScenerySetColourAction.h"
#include "LoadOrQuitAction.hpp"
#include "MazePlaceTrackAction.hpp"
#include "MazeSetTrackAction.hpp"
#include "NetworkModifyGroupAction.hpp"
#include "ParkEntranceRemoveAction.hpp"
#include "ParkMarketingAction.hpp"
#include "ParkSetDateAction.hpp"
#include "ParkSetLoanAction.hpp"
#include "ParkSetNameAction.hpp"
#include "ParkSetParameterAction.hpp"
#include "ParkSetResearchFundingAction.hpp"
#include "PauseToggleAction.hpp"
#include "PeepPickupAction.hpp"
#include "PlaceParkEntranceAction.hpp"
#include "PlacePeepSpawnAction.hpp"
#include "PlayerKickAction.hpp"
#include "PlayerSetGroupAction.hpp"
#include "RideCreateAction.hpp"
#include "RideDemolishAction.hpp"
#include "RideEntranceExitPlaceAction.hpp"
#include "RideEntranceExitRemoveAction.hpp"
#include "RideSetAppearanceAction.hpp"
#include "RideSetColourScheme.hpp"
#include "RideSetName.hpp"
#include "RideSetPriceAction.hpp"
#include "RideSetSetting.hpp"
#include "RideSetStatus.hpp"
#include "RideSetVehiclesAction.hpp"
#include "ScenarioSetSettingAction.hpp"
#include "SetCheatAction.hpp"
#include "SetParkEntranceFeeAction.hpp"
#include "SignSetNameAction.hpp"
#include "SignSetStyleAction.hpp"
#include "SmallSceneryPlaceAction.h"
#include "SmallSceneryRemoveAction.h"
#include "SmallScenerySetColourAction.hpp"
#include "StaffFireAction.hpp"
#include "StaffHireNewAction.hpp"
#include "StaffSetColourAction.hpp"
#include "StaffSetCostumeAction.hpp"
#include "StaffSetNameAction.hpp"
#include "StaffSetOrdersAction.hpp"
#include "StaffSetPatrolAreaAction.hpp"
#include "SurfaceSetStyleAction.hpp"
#include "TileModifyAction.hpp"
#include "TrackDesignAction.h"
#include "TrackPlaceAction.hpp"
#include "TrackRemoveAction.hpp"
#include "TrackSetBrakeSpeedAction.hpp"
#include "WallPlaceAction.hpp"
#include "WallRemoveAction.hpp"
#include "WallSetColourAction.hpp"
#include "WaterLowerAction.hpp"
#include "WaterRaiseAction.hpp"
#include "WaterSetHeightAction.hpp"

namespace GameActions
{
    void Register()
    {
        Register<BalloonPressAction>();
        Register<BannerPlaceAction>();
        Register<BannerRemoveAction>();
        Register<BannerSetColourAction>();
        Register<BannerSetNameAction>();
        Register<BannerSetStyleAction>();
        Register<ClimateSetAction>();
        Register<FootpathPlaceAction>();
        Register<FootpathPlaceFromTrackAction>();
        Register<FootpathRemoveAction>();
        Register<FootpathAdditionPlaceAction>();
        Register<FootpathAdditionRemoveAction>();
        Register<GuestSetNameAction>();
        Register<MazePlaceTrackAction>();
        Register<MazeSetTrackAction>();
        Register<NetworkModifyGroupAction>();
        Register<ParkMarketingAction>();
        Register<ParkEntranceRemoveAction>();
        Register<ParkSetLoanAction>();
        Register<ParkSetNameAction>();
        Register<ParkSetParameterAction>();
        Register<ParkSetResearchFundingAction>();
        Register<PeepPickupAction>();
        Register<PlaceParkEntranceAction>();
        Register<PlacePeepSpawnAction>();
        Register<PlayerKickAction>();
        Register<PlayerSetGroupAction>();
        Register<RideCreateAction>();
        Register<RideDemolishAction>();
        Register<RideEntranceExitPlaceAction>();
        Register<RideEntranceExitRemoveAction>();
        Register<RideSetColourSchemeAction>();
        Register<RideSetNameAction>();
        Register<RideSetPriceAction>();
        Register<RideSetStatusAction>();
        Register<RideSetAppearanceAction>();
        Register<RideSetVehicleAction>();
        Register<RideSetSettingAction>();
        Register<ScenarioSetSettingAction>();
        Register<SetParkEntranceFeeAction>();
        Register<SignSetNameAction>();
        Register<SignSetStyleAction>();
        Register<StaffFireAction>();
        Register<StaffHireNewAction>();
        Register<StaffSetColourAction>();
        Register<StaffSetNameAction>();
        Register<StaffSetOrdersAction>();
        Register<StaffSetCostumeAction>();
        Register<StaffSetPatrolAreaAction>();
        Register<SurfaceSetStyleAction>();
        Register<WallPlaceAction>();
        Register<WallRemoveAction>();
        Register<WallSetColourAction>();
        Register<SmallSceneryPlaceAction>();
        Register<SmallSceneryRemoveAction>();
        Register<SmallScenerySetColourAction>();
        Register<LargeSceneryPlaceAction>();
        Register<LargeSceneryRemoveAction>();
        Register<LargeScenerySetColourAction>();
        Register<LandBuyRightsAction>();
        Register<LandLowerAction>();
        Register<LandRaiseAction>();
        Register<LandSetHeightAction>();
        Register<LandSetRightsAction>();
        Register<LandSmoothAction>();
        Register<TileModifyAction>();
        Register<TrackDesignAction>();
        Register<TrackPlaceAction>();
        Register<TrackRemoveAction>();
        Register<TrackSetBrakeSpeedAction>();
        Register<ClearAction>();
        Register<PauseToggleAction>();
        Register<LoadOrQuitAction>();
        Register<WaterSetHeightAction>();
        Register<WaterLowerAction>();
        Register<WaterRaiseAction>();
        Register<GuestSetFlagsAction>();
        Register<ParkSetDateAction>();
        Register<SetCheatAction>();
#ifdef ENABLE_SCRIPTING
        Register<CustomAction>();
#endif
    }
} // namespace GameActions
