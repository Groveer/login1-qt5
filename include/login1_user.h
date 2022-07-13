#pragma once

#include <qobject.h>

#include "namespace.h"
#include "login1_types.h"

LOGIN1_BEGIN_NAMESPACE

class Login1UserPrivate;

class Login1User : public QObject
{
    Q_OBJECT
public:
    explicit Login1User(const QString &path, QObject *parent = nullptr);
    virtual ~Login1User();

private:
    QScopedPointer<Login1UserPrivate> d_ptr;
    Q_DECLARE_PRIVATE(Login1User)
};
LOGIN1_END_NAMESPACE
