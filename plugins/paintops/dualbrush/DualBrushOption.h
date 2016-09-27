/*
 *  Copyright (c) 2016 Boudewijn Rempt <boud@valdyas.org>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */
#ifndef KIS_DUALBRUSHOP_OPTION_H
#define KIS_DUALBRUSHOP_OPTION_H

#include <QWidget>

#include <kis_paintop_option.h>
#include "ui_WdgDualBrushOptions.h"

#include "StackedPreset.h"

class QListWidgetItem;

class DualBrushOpOptionsWidget: public QWidget, public Ui::WdgDualBrushOptions
{
    Q_OBJECT
public:
    DualBrushOpOptionsWidget(QWidget *parent = 0);
    virtual ~DualBrushOpOptionsWidget();

    void setPresetStack(const QVector<StackedPreset> &presetStack);
    QVector<StackedPreset> presetStack() const;

Q_SIGNALS:

    void configurationChanged();

private Q_SLOTS:

    void updatePreset();
    void addPreset();
    void removePreset();
    void movePresetUp();
    void movePresetDown();
    void itemSelected(QListWidgetItem *current, QListWidgetItem *previous);

};

class DualBrushOpOption : public KisPaintOpOption
{
    Q_OBJECT
public:
    DualBrushOpOption();
    ~DualBrushOpOption();

    void writeOptionSetting(KisPropertiesConfigurationSP setting) const;
    void readOptionSetting(const KisPropertiesConfigurationSP setting);
    QVector<StackedPreset> presetStack() const;

private:
    DualBrushOpOptionsWidget *m_dualBrushOptionsWidget;

};

#endif