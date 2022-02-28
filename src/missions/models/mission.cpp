#include "mission.h"

#include <QDebug>

#include "mission_traits.h"

using namespace md::domain;

Mission::Mission(const MissionType* type, const QString& name, const QVariant& vehicleId,
                 const QVariant& id, QObject* parent) :
    NamedMixin<Entity>(name, id, parent),
    type(type),
    vehicleId(vehicleId),
    route(new MissionRoute(name, id, this))
{
}

Mission::Mission(const MissionType* type, const QVariantMap& map, QObject* parent) :
    Mission(type, map.value(props::name).toString(), map.value(props::vehicle),
            map.value(props::id), parent)
{
}

QVariantMap Mission::toVariantMap() const
{
    QVariantMap map = NamedMixin<Entity>::toVariantMap();

    map.insert(props::type, this->type()->id);
    map.insert(props::vehicle, this->vehicleId());
    map.insert(props::route, this->route()->toVariantMap());

    return map;
}

void Mission::fromVariantMap(const QVariantMap& map)
{
    NamedMixin<Entity>::fromVariantMap(map);
    this->route()->fromVariantMap(map.value(props::route).toMap());
}

void Mission::clear()
{
    this->route()->clear();
}
