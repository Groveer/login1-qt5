// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-only

#pragma once

#include "include/namespace.h"
#include <qobject.h>

class DBusInterface;
LOGIN1_BEGIN_NAMESPACE
class Login1Session;

class Login1SessionPrivate : public QObject
{
    Q_OBJECT
public:
    explicit Login1SessionPrivate(Login1Session *parent = nullptr)
        : q_ptr(parent)
    {
    }

    QString m_errorMessage;
    DBusInterface *m_inter;
    Login1Session *q_ptr;
    Q_DECLARE_PUBLIC(Login1Session)
};

LOGIN1_END_NAMESPACE
