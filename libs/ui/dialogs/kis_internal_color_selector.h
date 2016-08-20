/*
 * Copyright (C) Wolthera van Hovell tot Westerflier <griffinvalley@gmail.com>, (C) 2016
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

#ifndef KISINTERNALCOLORSELECTOR_H
#define KISINTERNALCOLORSELECTOR_H

#include "kritaui_export.h"
#include "KoColor.h"
#include "KoColorSpace.h"
#include "KoColorDisplayRendererInterface.h"

#include <QScopedPointer>

#include "ui_wdgdlginternalcolorselector.h"

/**
 * @brief The KisInternalColorSelector class
 *
 * A non-modal color selector dialog that is not a plugin and can thus be used for filters.
 */
class KRITAUI_EXPORT KisInternalColorSelector : public QDialog
{
    Q_OBJECT
public:
    KisInternalColorSelector(QWidget* parent, KoColor color, bool modal, const QString &caption, const KoColorDisplayRendererInterface *displayRenderer = KoDumbColorDisplayRenderer::instance());
    ~KisInternalColorSelector();

    /**
     * @brief slotColorSpaceChanged
     * Color space has changed, use this dialog to change the colorspace.
     */
    void colorSpaceChanged(const KoColorSpace *cs);

    /**
     * @brief setDisplayRenderer
     * Set the display renderer. This is necessary for HDR color manage support.
     * @param displayRenderer
     */
    void setDisplayRenderer(const KoColorDisplayRendererInterface *displayRenderer);

    /**
     * @brief getModalColorDialog
     * Excecute this dialog modally. The function returns
     * the KoColor you want.
     * @param color - The current color. Make sure this is in the color space you want your
     * end color to be in.
     * @param chooseAlpha - Whether or not the alpha-choosing functionality should be used.
     */
    static KoColor getModalColorDialog(const KoColor color, bool chooseAlpha = false, QWidget* parent = Q_NULLPTR, QString caption = QString());

    /**
     * @brief getCurrentColor
     * @return gives currently active color;
     */
    KoColor getCurrentColor();

    void chooseAlpha(bool chooseAlpha);

Q_SIGNALS:
    /**
     * @brief signalForegroundColorChosen
     * The most important signal. This will sent out when a color has been picked from the selector.
     * There will be a small delay to make sure that the selector causes too many updates.
     *
     * Do not connect this to slotColorUpdated.
     * @param color The new color chosen
     */

    void signalForegroundColorChosen(KoColor color);
public Q_SLOTS:
    /**
     * @brief slotColorUpdated
     * Very important slot. Is connected to krita's resources to make sure it has
     * the currently active color. It's very important that this function is able to understand
     * when the signal came from itself.
     * @param newColor This is the new color.
     */
    void slotColorUpdated(KoColor newColor);
private Q_SLOTS:

    /**
     * @brief slotLockSelector
     * This slot will prevent the color from being updated.
     */
    void slotLockSelector();

    /**
     * @brief slotConfigurationChanged
     * Wrapper slot for changes to the colorspace.
     */
    void slotConfigurationChanged();

    void endUpdateWithNewColor();

    /**
     * @brief setPreviousColor
     * triggered when the dialog is either accepted or hidden.
     */
    void setPreviousColor();

    void slotSetColorFromPatch(KoColorPatch* patch);


private:
    Ui_WdgDlgInternalColorSelector *m_ui; //the UI
    struct Private; //The private struct
    const QScopedPointer<Private> m_d; //the private pointer

    /**
     * @brief updateAllElements
     * Updates each widget with the new element, and if it's responsible for the update sents
     * a signal out that there's a new color.
     */
    void updateAllElements(QObject *source);

    virtual void focusInEvent(QFocusEvent *e);
};

#endif // KISINTERNALCOLORSELECTOR_H
