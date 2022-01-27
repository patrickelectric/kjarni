#ifndef TEST_MISSION_TRAITS_H
#define TEST_MISSION_TRAITS_H

#include "mission_traits.h"

namespace md::domain::test_mission
{
// Prameters
const ParameterType radius = { "radius", "Radius", ParameterType::Real, 100, 0, route::maxRadius };
const ParameterType altitude = { "altitude", "Altitude",         ParameterType::Real,
                                 0.0,        route::minAltitude, route::maxAltitude };
const ParameterType airspeed = { "airspeed", "Airspeed", ParameterType::Int, 10, 0, 100 };
const ParameterType passthrough = { "passthrough", "Passthrough", true };

// Route Items
const RouteItemType changeSpeed{
    "ch_speed", "Change speed", "CH SPD", Positioned::Optional, { &airspeed }
};
const RouteItemType changeAltitude{
    "ch_speed", "Change alt", "CH ALT", Positioned::Optional, { &altitude }
};
const RouteItemType takePhoto{
    "take_photo", "Take photo", "PHOTO", Positioned::No, {}
};

const RouteItemType waypoint = {
    "waypoint", "Waypoint", "WPT", Positioned::Required, { &passthrough }
};
const RouteItemType circle = {
    "circle", "Circle", "CRL", Positioned::Required, { &radius }
};
const RouteItemType loop = {
    "circle", "Circle", "CRL", Positioned::Required, { &radius }
};

// Routes
const RouteType routeType = { "test_route",
                              "Test Route",
                              { &waypoint, &circle, &loop, &changeSpeed, &changeAltitude,
                                &takePhoto },
                              {} };

// Mission
const MissionType missionType = { "test_mission", "Test Mission", &routeType, &waypoint, &waypoint };

} // namespace md::domain::test_mission

#endif // TEST_MISSION_TRAITS_H
