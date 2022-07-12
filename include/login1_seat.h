#pragma once

#include <qobject.h>

#include "namespace.h"
#include "login1_types.h"

LOGIN1_BEGIN_NAMESPACE

class Login1SeatPrivate;

class Login1Seat : public QObject
{
    Q_OBJECT
public:
    explicit Login1Seat(const QString &path, QObject *parent = nullptr);
    virtual ~Login1Seat();

private:
    QScopedPointer<Login1SeatPrivate> d_ptr;
    Q_DECLARE_PRIVATE(Login1Seat)
};
LOGIN1_END_NAMESPACE
