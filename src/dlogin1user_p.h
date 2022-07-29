// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-only

#pragma once

#include "include/namespace.h"
#include <qobject.h>

class DBusInterface;
DLOGIN1_BEGIN_NAMESPACE
class DLogin1User;

class DLogin1UserPrivate : public QObject
{
    Q_OBJECT
public:
    explicit DLogin1UserPrivate(DLogin1User *parent = nullptr) : q_ptr(parent) {}

    QString m_errorMessage;
    DBusInterface *m_inter;
    DLogin1User *q_ptr;
    Q_DECLARE_PUBLIC(DLogin1User)
};

DLOGIN1_END_NAMESPACE
