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

#include "DualBrushPaintopSettingsWidget.h"

#include "DualBrushOption.h"
#include "DualBrushPaintopSettings.h"

#include <kis_curve_option_widget.h>
#include <kis_pressure_opacity_option.h>
#include <kis_paintop_settings_widget.h>
#include <kis_paint_action_type_option.h>

DualBrushPaintOpSettingsWidget:: DualBrushPaintOpSettingsWidget(QWidget* parent)
    : KisPaintOpSettingsWidget(parent)
{
    setObjectName("dual brush option widget");

    addPaintOpOption(new DualBrushOpOption(), i18n("Brush Stack"));
    addPaintOpOption(new KisCurveOptionWidget(new KisPressureOpacityOption(), i18n("Transparent"), i18n("Opaque")), i18n("Opacity"));
    addPaintOpOption(new KisPaintActionTypeOption(), i18n("Painting Mode"));
}

DualBrushPaintOpSettingsWidget::~ DualBrushPaintOpSettingsWidget()
{
}

KisPropertiesConfigurationSP DualBrushPaintOpSettingsWidget::configuration() const
{
    DualBrushPaintOpSettings *config = new DualBrushPaintOpSettings();
    config->setOptionsWidget(const_cast<DualBrushPaintOpSettingsWidget*>(this));
    config->setProperty("paintop", "DualBrush");
    writeConfiguration(config);
    return config;
}