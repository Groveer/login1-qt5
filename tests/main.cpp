// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-only

#include <qcoreapplication.h>
#include <qdebug.h>
#include <qglobal.h>

#include "include/login1manager.h"

int main (int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    DLogin1::Login1Manager manager;
    auto seats = manager.listSeats();
    if (seats.isEmpty()) {
        qDebug() << "error:" << manager.lastError();
        return -1;
    }
    qDebug() << "seat0's path:" << seats[0].path;

    QObject::connect(&manager, qOverload<const uint, const QString&>(&DLogin1::Login1Manager::UserNew), [](const uint uid, const QString &path) {
                         qDebug() << "user added:" << uid << path;
                     });
    return app.exec();
}
