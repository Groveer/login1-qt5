#pragma once

#include "include/namespace.h"
#include <qobject.h>

class DBusInterface;
LOGIN1_BEGIN_NAMESPACE
class Login1Seat;

class Login1SeatPrivate : public QObject
{
    Q_OBJECT
public:
    explicit Login1SeatPrivate(Login1Seat *parent = nullptr) : q_ptr(parent) {}

    QString m_errorMessage;
    DBusInterface *m_inter;
    Login1Seat *q_ptr;
    Q_DECLARE_PUBLIC(Login1Seat)
};

LOGIN1_END_NAMESPACE
