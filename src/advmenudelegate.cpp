/***************************************************************************
  advmenudelegate.cpp
  -------------------
  Copyright © 2014-2019, LI-COR Biosciences, Inc. All Rights Reserved.
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

#include "advmenudelegate.h"

#include <QApplication>
#include <QPainter>

AdvMenuDelegate::AdvMenuDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{
}

QSize AdvMenuDelegate::sizeHint(const QStyleOptionViewItem& option,
                          const QModelIndex& index) const
{
    Q_UNUSED(option)
    Q_UNUSED(index)
    return QSize{195, 68};
}
void AdvMenuDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                       const QModelIndex &index) const
{
    QStyledItemDelegate::paint(painter, option, index);

    painter->save();

    QRect r = option.rect;

    if (option.state & QStyle::State_Selected)
    {
        QPen fontSelectedPen(Qt::white, 1, Qt::SolidLine);
        painter->setPen(fontSelectedPen);
    }

    auto icon = qvariant_cast<QIcon>(index.data(IconRole));

//#if defined(Q_OS_MACOS)
//    auto pixmap = icon.pixmap(icon.actualSize(QSize(42, 42)));
//    auto pixmap = icon.pixmap(QSize(42, 42));
//    pixmap.setDevicePixelRatio(2.0);
//#endif
//    icon.addPixmap(pixmap, QIcon::Normal, QIcon::On);

    if (!icon.isNull())
    {
        icon.paint(painter, r.adjusted(8, 0, 8, 0), Qt::AlignVCenter | Qt::AlignLeft);
    }

#if defined(Q_OS_MACOS)
    auto fontSize = 13;
#elif defined(Q_OS_WIN) || defined(Q_OS_LINUX)
    auto fontSize = 10;
#endif

    auto font = QFont(QStringLiteral("Open Sans"), fontSize, QFont::Normal);
    QFontMetrics fm(font);
    auto text = qvariant_cast<QString>(index.data(TextRole));

    painter->setFont(font);

    auto text_width = fm.width(text);

    // manage text wrapping, centering the item text
    if (text_width <= 185)
    {
        painter->drawText(r.adjusted(54,
                                     (r.height() - fm.height()) / 2,
                                     44,
                                     (r.height() - fm.height()) / 2), text);
    }
    else
    {
        painter->drawText(r.adjusted(54,
                                     (r.height() - fm.height()*2 - fm.leading()) / 2,
                                     44,
                                     (r.height() - fm.height()*2 - fm.leading()) / 2), text);
    }

    painter->restore();
}
