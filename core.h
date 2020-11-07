#ifndef CORE_H
#define CORE_H

#include <QObject>

#define VERSION "0.5.0"

class NetworkController;

class Core : public QObject
{
    Q_OBJECT
    Q_PROPERTY(NetworkController * networkController READ networkController CONSTANT)
    Q_PROPERTY(QString version READ version CONSTANT)

public:
    virtual ~Core();

    static Core *instance();

    NetworkController *networkController() const;
    QString version() const;

private:
    explicit Core(QObject *parent = nullptr);

    static Core *_instance;
    NetworkController *_networkController;
};

#endif // CORE_H
