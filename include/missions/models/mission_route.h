#ifndef MISSION_ROUTE_H
#define MISSION_ROUTE_H

#include "mission_route_item.h"
#include "visible_mixin.hpp"

namespace md::domain
{
class MissionRoute : public NamedMixin<VisibleMixin<Entity>>
{
    Q_OBJECT

public:
    explicit MissionRoute(const QString& name = QString(), bool visible = true,
                          const QVariant& id = utils::generateId(), QObject* parent = nullptr);
    explicit MissionRoute(const QVariantMap& map, QObject* parent = nullptr);

    bool isEmpty() const;
    int count() const;
    int index(MissionRouteItem* item) const;
    int currentIndex() const;
    MissionRouteItem* firstItem() const;
    MissionRouteItem* lastItem() const;
    MissionRouteItem* currentItem() const;
    const QList<MissionRouteItem*>& items() const;
    MissionRouteItem* item(int index) const;

public slots:
    void setItems(const QList<MissionRouteItem*>& items);
    void addItem(MissionRouteItem* item);
    void removeItem(MissionRouteItem* item);
    void clear();

    void setReached(int index);
    void setCurrent(int index);

signals:
    void itemAdded(int index, MissionRouteItem* item);
    void itemChanged(int index, MissionRouteItem* item);
    void itemRemoved(int index, MissionRouteItem* item);

    void currentChanged(int index);
    void itemReached(int index);

    void goTo(int index);

private:
    QList<MissionRouteItem*> m_items;
    int m_currentIndex = -1;
};
} // namespace md::domain

#endif // MISSION_ROUTE_H
