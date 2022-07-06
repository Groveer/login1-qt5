#pragma once

#include "namespace.h"
#include <qdbusargument.h>
#include <qdbusextratypes.h>
#include <qlist.h>
#include <qnamespace.h>

LOGIN1_BEGIN_NAMESPACE
struct Property
{
    QString name;
    QDBusVariant var;
    friend QDBusArgument &operator<< (QDBusArgument &arg, const Property &property)
    {
        arg.beginStructure();
        arg << property.name;
        arg << property.var;
        arg.endStructure();
        return arg;
    }
    friend const QDBusArgument &operator>> (QDBusArgument &arg, Property &property)
    {
        arg.beginStructure();
        arg >> property.name;
        arg >> property.var;
        arg.endStructure();
        return arg;
    }
};

struct Inhibitor
{
    QString what;
    QString who;
    QString why;
    QString mode;
    uint    uid;
    uint    pid;
    friend QDBusArgument &operator<< (QDBusArgument &arg, const Inhibitor &inhibitor)
    {
        arg.beginStructure();
        arg << inhibitor.what;
        arg << inhibitor.who;
        arg << inhibitor.why;
        arg << inhibitor.mode;
        arg << inhibitor.uid;
        arg << inhibitor.pid;
        arg.endStructure();
        return arg;
    }
    friend const QDBusArgument &operator>> (QDBusArgument &arg, Inhibitor &inhibitor)
    {
        arg.beginStructure();
        arg >> inhibitor.what;
        arg >> inhibitor.who;
        arg >> inhibitor.why;
        arg >> inhibitor.mode;
        arg >> inhibitor.uid;
        arg >> inhibitor.pid;
        arg.endStructure();
        return arg;
    }
};

struct Seat
{
    QString seat_id;
    QDBusObjectPath path;
    friend QDBusArgument &operator<< (QDBusArgument &arg, const Seat &seat)
    {
        arg.beginStructure();
        arg << seat.seat_id;
        arg << seat.path;
        arg.endStructure();
        return arg;
    }
    friend const QDBusArgument &operator>> (QDBusArgument &arg, Seat &seat)
    {
        arg.beginStructure();
        arg >> seat.seat_id;
        arg >> seat.path;
        arg.endStructure();
        return arg;
    }
};

struct Session
{
    QString session_id;
    uint user_id;
    QString user_name;
    QString seat_id;
    QDBusObjectPath path;
    friend QDBusArgument &operator<< (QDBusArgument &arg, const Session &session)
    {
        arg.beginStructure();
        arg << session.session_id;
        arg << session.user_id;
        arg << session.user_name;
        arg << session.seat_id;
        arg << session.path;
        arg.endStructure();
        return arg;
    }
    friend const QDBusArgument &operator>> (QDBusArgument &arg, Session &session)
    {
        arg.beginStructure();
        arg >> session.session_id;
        arg >> session.user_id;
        arg >> session.user_name;
        arg >> session.seat_id;
        arg >> session.path;
        arg.endStructure();
        return arg;
    }
};

struct User
{
    uint user_id;
    QString user_name;
    QDBusObjectPath path;
    friend QDBusArgument &operator<< (QDBusArgument &arg, const User &user)
    {
        arg.beginStructure();
        arg << user.user_id;
        arg << user.user_name;
        arg << user.path;
        arg.endStructure();
        return arg;
    }
    friend const QDBusArgument &operator>> (QDBusArgument &arg, User &user)
    {
        arg.beginStructure();
        arg >> user.user_id;
        arg >> user.user_name;
        arg >> user.path;
        arg.endStructure();
        return arg;
    }
};
LOGIN1_END_NAMESPACE
Q_DECLARE_METATYPE(LOGIN1_NAMESPACE::Property)
Q_DECLARE_METATYPE(LOGIN1_NAMESPACE::Inhibitor)
Q_DECLARE_METATYPE(LOGIN1_NAMESPACE::Seat)
Q_DECLARE_METATYPE(LOGIN1_NAMESPACE::Session)
Q_DECLARE_METATYPE(LOGIN1_NAMESPACE::User)
