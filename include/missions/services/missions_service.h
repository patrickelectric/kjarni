#ifndef MISSIONS_SERVICE_H
#define MISSIONS_SERVICE_H

#include "i_mission_items_repository.h"
#include "i_missions_repository.h"
#include "i_missions_service.h"

#include <QMutex>

namespace md::domain
{
class MissionsService : public IMissionsService
{
    Q_OBJECT

public:
    MissionsService(IMissionsRepository* missionsRepo, IMissionItemsRepository* itemsRepo,
                    QObject* parent = nullptr);

    Mission* mission(const QVariant& id) const override;
    Mission* missionForVehicle(const QVariant& vehicleId) const override;
    QVariantList missionIds() const override;
    QList<Mission*> missions() const override;
    MissionOperation* operationForMission(Mission* mission) const override;
    const MissionType* missionType(const QString& id) const override;
    QList<const MissionType*> missionTypes() const override;

    RoutePattern* createRoutePattern(const QString& routePatternId) override;

    void startOperation(Mission* mission, MissionOperation::Type type) override;
    void endOperation(MissionOperation* operation, MissionOperation::State state) override;

    void registerMissionType(const MissionType* type) override;
    void unregisterMissionType(const MissionType* type) override;

    void registerRoutePatternFactory(const QString& routePatternId,
                                     IRoutePatternFactory* factory) override;
    void unregisterRoutePatternFactory(const QString& routePatternId) override;

    // For tests
    void addMission(Mission* mission);

public slots:
    void readAll() override;
    void removeMission(Mission* mission) override;
    void restoreMission(Mission* mission) override;
    void saveMission(Mission* mission) override;
    void saveItem(MissionRoute* route, MissionRouteItem* item) override;
    void restoreItem(MissionRoute* route, MissionRouteItem* item) override;

private:
    Mission* readMission(const QVariant& id);
    MissionRouteItem* readItem(const QVariant& id);
    void saveItemImpl(MissionRouteItem* item, const QVariant& parentId, const QVariantList& itemIds);
    void restoreItemImpl(MissionRouteItem* item);
    void removeItems(const QVariantList& itemsIds);

    IMissionsRepository* const m_missionsRepo;
    IMissionItemsRepository* const m_itemsRepo;

    QMap<QString, const MissionType*> m_missionTypes;
    QMap<QVariant, Mission*> m_missions;
    QMap<Mission*, MissionOperation*> m_operations;
    QMap<QString, IRoutePatternFactory*> m_patternFactories;

    mutable QMutex m_mutex;
};
} // namespace md::domain

#endif // MISSIONS_SERVICE_H
