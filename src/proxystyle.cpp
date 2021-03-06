/***************************************************************************
  proxystyle.cpp
  --------------
  Copyright © 2013-2019, LI-COR Biosciences, Inc. All Rights Reserved.
  Author: Antonio Forgione

  This file is part of EddyPro®.

  NON-COMMERCIAL RESEARCH PURPOSES ONLY - EDDYPRO® is licensed for
  non-commercial academic and government research purposes only,
  as provided in the EDDYPRO® End User License Agreement.
  EDDYPRO® may only be used as provided in the End User License Agreement
  and may not be used or accessed for any commercial purposes.
  You may view a copy of the End User License Agreement in the file
  EULA_NON_COMMERCIAL.rtf.

  Commercial companies that are LI-COR flux system customers are
  encouraged to contact LI-COR directly for our commercial EDDYPRO®
  End User License Agreement.

  EDDYPRO® contains Open Source Components (as defined in the
  End User License Agreement). The licenses and/or notices for the
  Open Source Components can be found in the file LIBRARIES.txt.

  EddyPro® is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#include "proxystyle.h"

#include <QStyleFactory>

ProxyStyle::ProxyStyle(const QString& style)
    : style_(QStyleFactory::create(style))
{
}

ProxyStyle::~ProxyStyle()
{
    delete style_;
}

void ProxyStyle::drawComplexControl(ComplexControl control, const QStyleOptionComplex* option, QPainter* painter, const QWidget* widget) const
{
    style_->drawComplexControl(control, option, painter, widget);
}

void ProxyStyle::drawControl(ControlElement element, const QStyleOption* option, QPainter* painter, const QWidget* widget)  const
{
    style_->drawControl(element, option, painter, widget);
}

void ProxyStyle::drawItemPixmap(QPainter* painter, const QRect& rect, int alignment, const QPixmap& pixmap) const
{
    style_->drawItemPixmap(painter, rect, alignment, pixmap);
}

void ProxyStyle::drawItemText(QPainter* painter, const QRect& rect, int alignment, const QPalette& pal, bool enabled, const QString& text, QPalette::ColorRole textRole) const
{
    style_->drawItemText(painter, rect, alignment, pal, enabled, text, textRole);
}

void ProxyStyle::drawPrimitive(PrimitiveElement elem, const QStyleOption* option, QPainter* painter, const QWidget* widget) const
{
    style_->drawPrimitive(elem, option, painter, widget);
}

QPixmap ProxyStyle::generatedIconPixmap(QIcon::Mode iconMode, const QPixmap& pixmap, const QStyleOption* option) const
{
    return style_->generatedIconPixmap(iconMode, pixmap, option);
}

QStyle::SubControl ProxyStyle::hitTestComplexControl(ComplexControl control, const QStyleOptionComplex* option, const QPoint& pos, const QWidget* widget) const
{
    return style_->hitTestComplexControl(control, option, pos, widget);
}

QRect ProxyStyle::itemPixmapRect(const QRect& rect, int alignment, const QPixmap& pixmap) const
{
    return style_->itemPixmapRect(rect, alignment, pixmap);
}

QRect ProxyStyle::itemTextRect(const QFontMetrics& metrics, const QRect& rect, int alignment, bool enabled, const QString& text) const
{
    return style_->itemTextRect(metrics, rect, alignment, enabled, text);
}

int ProxyStyle::layoutSpacing(QSizePolicy::ControlType control1, QSizePolicy::ControlType control2, Qt::Orientation orientation, const QStyleOption *option, const QWidget *widget) const
{
    return style_->layoutSpacing(control1, control2, orientation, option, widget);
}

int ProxyStyle::pixelMetric(PixelMetric metric, const QStyleOption* option, const QWidget* widget) const
{
    return style_->pixelMetric(metric, option, widget);
}

void ProxyStyle::polish(QWidget* widget)
{
    style_->polish(widget);
}

void ProxyStyle::polish(QApplication* app)
{
    style_->polish(app);
}

void ProxyStyle::polish(QPalette& pal)
{
    style_->polish(pal);
}

QSize ProxyStyle::sizeFromContents(ContentsType type, const QStyleOption* option, const QSize& contentsSize, const QWidget* widget) const
{
    return style_->sizeFromContents(type, option, contentsSize, widget);
}

QIcon ProxyStyle::standardIcon(StandardPixmap standardIcon, const QStyleOption* option, const QWidget* widget) const
{
    return style_->standardIcon(standardIcon, option, widget);
}

QPalette ProxyStyle::standardPalette() const
{
    return style_->standardPalette();
}

QPixmap ProxyStyle::standardPixmap(StandardPixmap standardPixmap, const QStyleOption* option, const QWidget* widget) const
{
    return style_->standardPixmap(standardPixmap, option, widget);
}

int ProxyStyle::styleHint(StyleHint hint, const QStyleOption* option, const QWidget* widget, QStyleHintReturn* returnData) const
{
    return style_->styleHint(hint, option, widget, returnData);
}

QRect ProxyStyle::subControlRect(ComplexControl control, const QStyleOptionComplex* option, SubControl subControl, const QWidget* widget) const
{
    return style_->subControlRect(control, option, subControl, widget);
}

QRect ProxyStyle::subElementRect(SubElement element, const QStyleOption* option, const QWidget* widget) const
{
    return style_->subElementRect(element, option, widget);
}

void ProxyStyle::unpolish(QWidget* widget)
{
    style_->unpolish(widget);
}

void ProxyStyle::unpolish(QApplication* app)
{
    style_->unpolish(app);
}
