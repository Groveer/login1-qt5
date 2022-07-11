#include "include/login1_types.h"

LOGIN1_BEGIN_NAMESPACE

QDBusArgument &operator<< (QDBusArgument &arg, const ScheduledShutdownValue &value)
{
    arg.beginStructure();
    arg << value.type;
    arg << value.usec;
    arg.endStructure();
    return arg;
}

const QDBusArgument &operator>> (const QDBusArgument &arg, ScheduledShutdownValue &value)
{
    arg.beginStructure();
    arg >> value.type;
    arg >> value.usec;
    arg.endStructure();
    return arg;
}

QDBusArgument &operator<< (QDBusArgument &arg, const SessionProperty &property)
{
    arg.beginStructure();
    arg << property.name;
    arg << property.var;
    arg.endStructure();
    return arg;
}

const QDBusArgument &operator>> (const QDBusArgument &arg, SessionProperty &property)
{
    arg.beginStructure();
    arg >> property.name;
    arg >> property.var;
    arg.endStructure();
    return arg;
}

QDBusArgument &operator<< (QDBusArgument &arg, const Inhibitor &inhibitor)
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

const QDBusArgument &operator>> (const QDBusArgument &arg, Inhibitor &inhibitor)
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

QDBusArgument &operator<< (QDBusArgument &arg, const Seat &seat)
{
    arg.beginStructure();
    arg << seat.seat_id;
    arg << seat.path;
    arg.endStructure();
    return arg;
}

const QDBusArgument &operator>> (const QDBusArgument &arg, Seat &seat)
{
    arg.beginStructure();
    arg >> seat.seat_id;
    arg >> seat.path;
    arg.endStructure();
    return arg;
}

QDBusArgument &operator<< (QDBusArgument &arg, const Session &session)
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

const QDBusArgument &operator>> (const QDBusArgument &arg, Session &session)
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

QDBusArgument &operator<< (QDBusArgument &arg, const User &user)
{
    arg.beginStructure();
    arg << user.user_id;
    arg << user.user_name;
    arg << user.path;
    arg.endStructure();
    return arg;
}

const QDBusArgument &operator>> (const QDBusArgument &arg, User &user)
{
    arg.beginStructure();
    arg >> user.user_id;
    arg >> user.user_name;
    arg >> user.path;
    arg.endStructure();
    return arg;
}

void login1::ScheduledShutdownValue::registerMetaType()
{
    qRegisterMetaType<ScheduledShutdownValue>("ScheduledShutdownValue");
    qDBusRegisterMetaType<ScheduledShutdownValue>();
}

void login1::SessionProperty::registerMetaType()
{
    qRegisterMetaType<SessionProperty>("SessionProperty");
    qDBusRegisterMetaType<SessionProperty>();
}

void login1::Inhibitor::registerMetaType()
{
    qRegisterMetaType<Inhibitor>("Inhibitor");
    qDBusRegisterMetaType<Inhibitor>();
}

void login1::Seat::registerMetaType()
{
    qRegisterMetaType<Seat>("Seat");
    qDBusRegisterMetaType<Seat>();
}

void login1::Session::registerMetaType()
{
    qRegisterMetaType<Session>("Session");
    qDBusRegisterMetaType<Session>();
}

void login1::User::registerMetaType()
{
    qRegisterMetaType<User>("User");
    qDBusRegisterMetaType<User>();
}

LOGIN1_END_NAMESPACE
