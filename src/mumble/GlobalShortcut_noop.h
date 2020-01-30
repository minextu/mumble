// Copyright 2005-2020 The Mumble Developers. All rights reserved.
// Use of this source code is governed by a BSD-style license
// that can be found in the LICENSE file at the root of the
// Mumble source tree or at <https://www.mumble.info/LICENSE>.

#ifndef MUMBLE_MUMBLE_GLOBALSHORTCUT_NOOP_H_
#define MUMBLE_MUMBLE_GLOBALSHORTCUT_NOOP_H_

#include "GlobalShortcut.h"
#include "ConfigDialog.h"
#include "Global.h"
#define NUM_BUTTONS 0x2ff

class GlobalShortcutNoop : public GlobalShortcutEngine {
	private:
		Q_OBJECT
        Q_DISABLE_COPY(GlobalShortcutNoop)
	public:
                int *display;
                QSet<int> qsRootWindows;
		int iXIopcode;
		QSet<int> qsMasterDevices;

		volatile bool bRunning;
		QSet<QString> qsKeyboards;
		QMap<QString, QFile *> qmInputDevices;

                GlobalShortcutNoop();
                ~GlobalShortcutNoop() Q_DECL_OVERRIDE;
		void run() Q_DECL_OVERRIDE;
		QString buttonName(const QVariant &) Q_DECL_OVERRIDE;

		void queryXIMasterList();
};

#endif
