/***************************************************************************
  timelagsettingsdialog.h
  -----------------------
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

#ifndef TIMELAGSETTINGSDIALOG_H
#define TIMELAGSETTINGSDIALOG_H

#include <QDateTime>
#include <QDialog>

#include "fileutils.h"

////////////////////////////////////////////////////////////////////////////////
/// \file src/timelagsettingsdialog.h
/// \brief
/// \version
/// \date
/// \author      Antonio Forgione
/// \note
/// \sa
/// \bug
/// \deprecated
/// \test
/// \todo
////////////////////////////////////////////////////////////////////////////////

class QButtonGroup;
class QCheckBox;
class QDate;
class QDateEdit;
class QDoubleSpinBox;
class QLabel;
class QRadioButton;
class QSpinBox;
class QTimeEdit;

class AncillaryFileTest;
class ClickLabel;
struct ConfigState;
class EcProject;
class FileBrowseWidget;

class TimeLagSettingsDialog : public QDialog
{
    Q_OBJECT
public:
    TimeLagSettingsDialog(QWidget *parent, EcProject *ecProject, ConfigState* config);

    void setSmartfluxUI();
signals:
    void saveRequest();

public slots:
    void close();
    void reset();
    void refresh();
    void partialRefresh();
    void setDateRange(FileUtils::DateRange dates);

private slots:
    void updateTlMode(int radioButton);
    void radioClicked(int radioButton);
    void testSelectedFile(const QString &fp);

    void onStartDateLabelClicked();
    void onEndDateLabelClicked();
    void updateStartDate(const QDate &d);
    void updateEndDate(const QDate &d);
    void updateStartTime(const QTime &t);
    void updateEndTime(const QTime &t);

    void onRhClassClicked();
    void updateRhClass(int n);

    void onCo2MinFluxClicked();
    void updateCo2MinFlux(double d);
    void onCh4MinFluxClicked();
    void updateCh4MinFlux(double d);
    void onGas4MinFluxClicked();
    void updateGas4MinFlux(double d);
    void onLeMinFluxClicked();
    void updateLeMinFlux(double d);
    void onPgRangeLabelClicked();
    void updatePgRange(double d);

    void onCo2LabelClicked();
    void updateMinCo2Tl(double d);
    void updateMaxCo2Tl(double d);
    void onH2oLabelClicked();
    void updateMinH2oTl(double d);
    void updateMaxH2oTl(double d);
    void onCh4LabelClicked();
    void updateMinCh4Tl(double d);
    void updateMaxCh4Tl(double d);
    void onGas4LabelClicked();
    void updateMinGas4Tl(double d);
    void updateMaxGas4Tl(double d);

    void updateSubsetSelection(bool b);

private:
    void updateFile(const QString& fp);
    void forceEndDatePolicy();
    void forceEndTimePolicy();

    QRadioButton* existingRadio;
    QRadioButton* nonExistingRadio;
    QButtonGroup* radioGroup;
    FileBrowseWidget * fileBrowse;
    QCheckBox* subsetCheckBox;
    ClickLabel* startDateLabel;
    QDateEdit* startDateEdit;
    QTimeEdit* startTimeEdit;
    QLabel* lockedIcon;
    ClickLabel* endDateLabel;
    QDateEdit* endDateEdit;
    QTimeEdit* endTimeEdit;
    ClickLabel* pgRangeLabel;
    QLabel* pgRangeLabel_2;
    QDoubleSpinBox* pgRangeSpin;

    QLabel* h2oTitleLabel;
    ClickLabel* rhClassLabel;
    QSpinBox* rhClassSpin;
    ClickLabel* leMinFluxLabel;
    QDoubleSpinBox* leMinFluxSpin;

    QLabel* gasTitleLabel;
    ClickLabel* co2MinFluxLabel;
    QDoubleSpinBox* co2MinFluxSpin;
    ClickLabel* ch4MinFluxLabel;
    QDoubleSpinBox* ch4MinFluxSpin;
    ClickLabel* gas4MinFluxLabel;
    QDoubleSpinBox* gas4MinFluxSpin;

    QLabel* searchWindowLabel;
    QLabel* minLabel;
    QLabel* maxLabel;
    ClickLabel* co2Label;
    ClickLabel* h2oLabel;
    ClickLabel* ch4Label;
    ClickLabel* gas4Label;
    QDoubleSpinBox* minCo2TlSpin;
    QDoubleSpinBox* maxCo2TlSpin;
    QDoubleSpinBox* minH2oTlSpin;
    QDoubleSpinBox* maxH2oTlSpin;
    QDoubleSpinBox* minCh4TlSpin;
    QDoubleSpinBox* maxCh4TlSpin;
    QDoubleSpinBox* minGas4TlSpin;
    QDoubleSpinBox* maxGas4TlSpin;

    EcProject *ecProject_;
    ConfigState* configState_;
};

#endif // TIMELAGSETTINGSDIALOG_H
