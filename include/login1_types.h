#pragma once

#include "namespace.h"
#include <qdbusargument.h>
#include <qdbusextratypes.h>
#include <qdbusmetatype.h>
#include <qmetatype.h>
#include <qglobal.h>
#include <qlist.h>
#include <qnamespace.h>

LOGIN1_BEGIN_NAMESPACE
struct ScheduledShutdownValue
{
    QString type;
    quint64 usec;
    static void registerMetaType();
};

struct SessionProperty
{
    QString name;
    QDBusVariant var;
    static void registerMetaType();
};

struct Inhibitor
{
    QString what;
    QString who;
    QString why;
    QString mode;
    uint    uid;
    uint    pid;
    static void registerMetaType();
};

struct Seat
{
    QString seat_id;
    QDBusObjectPath path;
    static void registerMetaType();
};

struct Session
{
    QString session_id;
    uint user_id;
    QString user_name;
    QString seat_id;
    QDBusObjectPath path;
    static void registerMetaType();
};

struct User
{
    uint user_id;
    QString user_name;
    QDBusObjectPath path;
    static void registerMetaType();
};

struct SeatPath
{
    QString seat_id;
    QDBusObjectPath path;
    static void registerMetaType();
};

struct SessionPath
{
    QString session_id;
    QDBusObjectPath path;
    static void registerMetaType();
};

struct UserPath
{
    uint user_id;
    QDBusObjectPath path;
    static void registerMetaType();
};

QDBusArgument &operator<<(QDBusArgument &arg, const ScheduledShutdownValue &value);
const QDBusArgument &operator>>(const QDBusArgument &arg, ScheduledShutdownValue &value);
QDBusArgument &operator<<(QDBusArgument &arg, const SessionProperty &property);
const QDBusArgument &operator>>(const QDBusArgument &arg, SessionProperty &property);
QDBusArgument &operator<<(QDBusArgument &arg, const Inhibitor &inhibitor);
const QDBusArgument &operator>>(const QDBusArgument &arg, Inhibitor &inhibitor);
QDBusArgument &operator<<(QDBusArgument &arg, const Seat &seat);
const QDBusArgument &operator>>(const QDBusArgument &arg, Seat &seat);
QDBusArgument &operator<<(QDBusArgument &arg, const Session &session);
const QDBusArgument &operator>>(const QDBusArgument &arg, Session &session);
QDBusArgument &operator<<(QDBusArgument &arg, const User &user);
const QDBusArgument &operator>>(const QDBusArgument &arg, User &user);
QDBusArgument &operator<<(QDBusArgument &arg, const SeatPath &path);
const QDBusArgument &operator>>(const QDBusArgument &arg, SeatPath &path);
QDBusArgument &operator<<(QDBusArgument &arg, const SessionPath &path);
const QDBusArgument &operator>>(const QDBusArgument &arg, SessionPath &path);
QDBusArgument &operator<<(QDBusArgument &arg, const UserPath &path);
const QDBusArgument &operator>>(const QDBusArgument &arg, UserPath &path);

LOGIN1_END_NAMESPACE
Q_DECLARE_METATYPE(LOGIN1_NAMESPACE::ScheduledShutdownValue)
Q_DECLARE_METATYPE(LOGIN1_NAMESPACE::SessionProperty)
Q_DECLARE_METATYPE(LOGIN1_NAMESPACE::Inhibitor)
Q_DECLARE_METATYPE(LOGIN1_NAMESPACE::Seat)
Q_DECLARE_METATYPE(LOGIN1_NAMESPACE::Session)
Q_DECLARE_METATYPE(LOGIN1_NAMESPACE::User)
Q_DECLARE_METATYPE(LOGIN1_NAMESPACE::SeatPath)
Q_DECLARE_METATYPE(LOGIN1_NAMESPACE::SessionPath)
Q_DECLARE_METATYPE(LOGIN1_NAMESPACE::UserPath)

