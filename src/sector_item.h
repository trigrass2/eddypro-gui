/***************************************************************************
  sectoritem.h
  ------------
  Copyright © 2019, LI-COR Biosciences, Inc. All Rights Reserved.
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
#ifndef SECTORITEM_H
#define SECTORITEM_H

#include <QColor>

struct SectorItem
{
    SectorItem(double startAngle = 0.0,
               double endAngle = 10.0,
               QColor color = QColor(170, 230, 255)) // #aae6ff
        : startAngle_(startAngle),
          endAngle_(endAngle),
          color_(std::move(color))
    {
    }

    double startAngle_;
    double endAngle_;
    QColor color_;
};

#endif // SECTORITEM_H
