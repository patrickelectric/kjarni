#ifndef PROPERTY_TREE_H
#define PROPERTY_TREE_H

#include "i_property_tree.h"

#include <QMap>

namespace md::domain
{
class PropertyTree : public IPropertyTree
{
    Q_OBJECT

public:
    PropertyTree(QObject* parent = nullptr);

    QStringList rootNodes() const override;
    QJsonObject properties(const QString& path) const override;

    void setProperties(const QString& path, const QJsonObject& properties) override;
    void appendProperties(const QString& path, const QJsonObject& properties) override;
    void removeNode(const QString& path) override;

private:
    QMap<QString, QJsonObject> m_properties;
};
} // namespace md::domain

#endif // PROPERTY_TREE_H
