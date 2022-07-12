#pragma once

#include "include/namespace.h"
#include <qobject.h>

class DBusInterface;
LOGIN1_BEGIN_NAMESPACE
class Login1Manager;

class Login1ManagerPrivate : public QObject
{
    Q_OBJECT
public:
    explicit Login1ManagerPrivate(Login1Manager *parent = nullptr) : q_ptr(parent) {}

    QString m_errorMessage;
    DBusInterface *m_inter;
    Login1Manager *q_ptr;
    Q_DECLARE_PUBLIC(Login1Manager)
};

LOGIN1_END_NAMESPACE
