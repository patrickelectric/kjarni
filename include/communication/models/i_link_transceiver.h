#ifndef I_LINK_TRANSCEIVER_H
#define I_LINK_TRANSCEIVER_H

#include <QByteArray>
#include <QObject>

namespace md::domain
{
class ILinkTransceiver : public QObject
{
    Q_OBJECT

public:
    ILinkTransceiver(QObject* parent) : QObject(parent)
    {
    }
    virtual ~ILinkTransceiver() = default;

public slots:
    virtual void start() = 0;
    virtual void stop() = 0;
    //    virtual void send(const QByteArray& data) = 0;

signals:
    void finished();
    //    void receivedData(QByteArray data);
};
} // namespace md::domain

#endif // I_LINK_TRANSCEIVER_H
