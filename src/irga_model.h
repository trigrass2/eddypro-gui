/***************************************************************************
  irga_model.h
  ------------
  Copyright © 2007-2011, Eco2s team, Antonio Forgione
  Copyright © 2011-2019, LI-COR Biosciences, Inc. All Rights Reserved.
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

#ifndef IRGA_MODEL_H
#define IRGA_MODEL_H

#include <QAbstractTableModel>
#include <QModelIndex>
#include <QVariant>

#include "irga_desc.h" // NOTE: for IrgaDescList

class IrgaModel : public QAbstractTableModel {
    Q_OBJECT
public:
    // model columns
    enum IrgaItem
    {
        MANUFACTURER,
        MODEL,
        SWVERSION,
        ID,
        TUBELENGTH,
        TUBEDIAMETER,
        TUBEFLOWRATE,
        TUBENSEPARATION,
        TUBEESEPARATION,
        TUBEVSEPARATION,
        VPATHLENGTH,
        HPATHLENGTH,
        TAU,
        KWATER,
        KOXYGEN,
        IRGANUMCOLS
    };

    IrgaModel(QObject *parent, IrgaDescList *list);

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex& index,
                 const QVariant& value,
                 int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;
    QVariant headerData(int section,
                        Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;
    bool insertColumns(int column,
                       int count,
                       const QModelIndex& parent = QModelIndex()) override;
    bool removeColumns(int column,
                       int count,
                       const QModelIndex& parent = QModelIndex()) override;
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    void flush();

signals:
    void modified();

private:
    IrgaDescList *list_;
};

#endif // IRGA_MODEL_H
