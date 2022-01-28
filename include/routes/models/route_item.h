#ifndef ROUTE_ITEM_H
#define ROUTE_ITEM_H

#include "geodetic.h"
#include "parametrised_mixin.hpp"
#include "route_item_type.h"

namespace md::domain
{
class RouteItem : public ParametrisedMixin<NamedMixin<Entity>>
{
    Q_OBJECT

public:
    explicit RouteItem(const RouteItemType* type, const QString& name = QString(),
                       const QVariant& id = utils::generateId(), QVariantMap params = {},
                       const Geodetic& position = Geodetic(), const QVariantMap& calcData = {},
                       bool current = false, bool reached = false, QObject* parent = nullptr);
    RouteItem(const RouteItemType* type, const QVariantMap& map, QObject* parent = nullptr);

    utils::Property<Geodetic> position;
    utils::Property<QVariantMap> calcData;
    utils::Property<bool> current;
    utils::Property<bool> reached;

    QVariantMap toVariantMap() const override;
    void fromVariantMap(const QVariantMap& map) override;

    const RouteItemType* type() const;

public slots:
    void setType(const RouteItemType* type);

    // TODO: to Parametrised or TypeParametrised
    void setAndCheckParameter(const QString& paramId, const QVariant& value);
    void resetParameter(const QString& paramId);
    void resetParameters();
    void syncParameters();

signals:
    void typeChanged();

    void goTo();

private:
    const RouteItemType* m_type;
};
} // namespace md::domain

#endif // ROUTE_ITEM_H
