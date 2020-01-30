// Copyright 2005-2020 The Mumble Developers. All rights reserved.
// Use of this source code is governed by a BSD-style license
// that can be found in the LICENSE file at the root of the
// Mumble source tree or at <https://www.mumble.info/LICENSE>.

#include "GlobalShortcut_noop.h"

#include "Settings.h"

#include <QtCore/QFileSystemWatcher>
#include <QtCore/QSocketNotifier>


#ifdef Q_OS_LINUX
# include <linux/input.h>
# include <fcntl.h>
#endif

// We define a global macro called 'g'. This can lead to issues when included code uses 'g' as a type or parameter name (like protobuf 3.7 does). As such, for now, we have to make this our last incl
#include "Global.h"

// We have to use a global 'diagnostic ignored' pragmas because
// we still support old versions of GCC. (FreeBSD 9.3 ships with GCC 4.2)
#if defined (__GNUC__)
// ScreenCount(...) and so on are macros that access the private structure and
// cast their return value using old-style-casts. Hence we suppress these warnings
// for this section of code.
# pragma GCC diagnostic ignored "-Wold-style-cast"
// XKeycodeToKeysym is deprecated.
// For backwards compatibility reasons we want to keep using the
// old function as long as possible. The replacement function
// XkbKeycodeToKeysym requires the XKB extension which isn't
// guaranteed to be present.
# pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif

/**
 * Returns a platform specific GlobalShortcutEngine object.
 *
 * @see GlobalShortcutX
 * @see GlobalShortcutMac
 * @see GlobalShortcutWin
 */
GlobalShortcutEngine *GlobalShortcutEngine::platformInit() {
        return new GlobalShortcutNoop();
}

GlobalShortcutNoop::GlobalShortcutNoop() {

}

GlobalShortcutNoop::~GlobalShortcutNoop() {

}

// Tight loop polling
void GlobalShortcutNoop::run() {

}

// Find XI2 master devices so they can be ignored.
void GlobalShortcutNoop::queryXIMasterList() {

}

QString GlobalShortcutNoop::buttonName(const QVariant &v) {
    return QString();
}
