#pragma once

#include "include/namespace.h"
#include <qobject.h>

class DBusInterface;
LOGIN1_BEGIN_NAMESPACE
class Login1User;

class Login1UserPrivate : public QObject
{
    Q_OBJECT
public:
    explicit Login1UserPrivate(Login1User *parent = nullptr) : q_ptr(parent) {}

    QString m_errorMessage;
    DBusInterface *m_inter;
    Login1User *q_ptr;
    Q_DECLARE_PUBLIC(Login1User)
};

LOGIN1_END_NAMESPACE
