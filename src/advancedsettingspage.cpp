/***************************************************************************
  advancedsettingspage.cpp
  ------------------------
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

#include "advancedsettingspage.h"

#include <QDebug>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QPushButton>

#include "dlproject.h"
#include "ecproject.h"
#include "advmenudelegate.h"
#include "advoutputoptions.h"
#include "advprocessingoptions.h"
#include "advsettingscontainer.h"
#include "advspectraloptions.h"
#include "advstatisticaloptions.h"
#include "planarfitsettingsdialog.h"
#include "timelagsettingsdialog.h"
#include "smartfluxbar.h"
#include "widget_utils.h"

const QString AdvancedSettingsPage::PAGE_TITLE_0 = QObject::tr("Processing Options");
const QString AdvancedSettingsPage::PAGE_TITLE_1 = QObject::tr("Statistical Analysis");
const QString AdvancedSettingsPage::PAGE_TITLE_2 = QObject::tr("Output Files");
const QString AdvancedSettingsPage::PAGE_TITLE_3 = QObject::tr("Computation Options");
const QString AdvancedSettingsPage::PAGE_TITLE_4 = QObject::tr("Spectral Analysis and Corrections");

AdvancedSettingsPage::AdvancedSettingsPage(QWidget* parent,
                                           DlProject* dlProject,
                                           EcProject* ecProject,
                                           ConfigState* config) :
    QWidget(parent),
    dlProject_(dlProject),
    ecProject_(ecProject),
    configState_(config)
{
    createMenu();
    createIcons();

    auto resetButtonContainer = new QWidget;
    resetButtonContainer->setProperty("buttonContainer", true);

    auto resetButton = new QPushButton;
    resetButton->setProperty("mdButton", true);
    resetButton->setText(tr("Restore Default Values"));
    resetButton->setToolTip(tr("<b>Restore Default Values</b>: "
                               "Resets all the Advanced Settings to the "
                               "default settings."));

    auto resetButtonContainerLayout = new QHBoxLayout;
    resetButtonContainerLayout->addWidget(resetButton, 1, Qt::AlignCenter);
    resetButtonContainer->setLayout(resetButtonContainerLayout);

    advancedSettingContainer = new AdvSettingsContainer(this,
                                                        dlProject_,
                                                        ecProject_,
                                                        configState_);
    menuWidget->setCurrentRow(0);

    smartfluxBar = new SmartFluxBar(ecProject_, configState_);

    auto mainLayout = new QGridLayout(this);
    mainLayout->addWidget(smartfluxBar, 0, 0, 1, -1);
    mainLayout->addWidget(menuWidget, 1, 0, 1, 1);
    mainLayout->addWidget(advancedSettingContainer, 1, 1, 2, 1);
    mainLayout->addWidget(resetButtonContainer, 2, 0, 1, 1);
    mainLayout->setRowStretch(1, 1);
    mainLayout->setColumnStretch(1, 1);
    mainLayout->setSizeConstraint(QLayout::SetNoConstraint);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    setLayout(mainLayout);

    connect(resetButton, &QPushButton::clicked, this,
            &AdvancedSettingsPage::resetButtonCLicked);

    // TODO: understand why the new qt5 syntax trigger errors in the
    // following cases
    connect(smartfluxBar, SIGNAL(showSmartfluxBarRequest(bool)),
            parent, SIGNAL(showSmartfluxBarRequest(bool)));
//    connect(smartfluxBar_, &SmartFluxBar::showSmartfluxBarRequest,
//            parent, &SmartFluxBar::showSmartfluxBarRequest);

    connect(smartfluxBar, SIGNAL(saveSilentlyRequest()),
            parent, SIGNAL(saveSilentlyRequest()));
//    connect(smartfluxBar_, &SmartFluxBar::saveSilentlyRequest,
//            parent, &SmartFluxBar::saveSilentlyRequest);

    connect(smartfluxBar, SIGNAL(saveRequest()),
            parent, SIGNAL(saveRequest()));
//    connect(smartfluxBar_, &SmartFluxBar::saveRequest,
//            parent, &SmartFluxBar::saveRequest);
}

void AdvancedSettingsPage::createMenu()
{
    menuWidget = new QListWidget;
    menuWidget->setSelectionRectVisible(false);
    // to reduce the select decoration
    menuWidget->setObjectName(QStringLiteral("advSettingsMenu"));
    menuWidget->setIconSize(QSize(42, 42));
    menuWidget->setSpacing(0);
    menuWidget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    connect(menuWidget, SIGNAL(currentRowChanged(int)),
            this, SLOT(changePage(int)));
}

void AdvancedSettingsPage::createIcons()
{
    menuWidget->setItemDelegate(new AdvMenuDelegate(menuWidget));

    auto processingItem = new QListWidgetItem;
    processingItem->setData(AdvMenuDelegate::TextRole, PAGE_TITLE_0);
    processingItem->setData(AdvMenuDelegate::IconRole, QIcon(QStringLiteral(":/icons/adv-menu-processing")));
    menuWidget->addItem(processingItem);

    auto statisticItem = new QListWidgetItem;
    statisticItem->setData(AdvMenuDelegate::TextRole, PAGE_TITLE_1);
    statisticItem->setData(AdvMenuDelegate::IconRole, QIcon(QStringLiteral(":/icons/adv-menu-statistic")));
    menuWidget->addItem(statisticItem);

    auto spectraItem = new QListWidgetItem;
    spectraItem->setData(AdvMenuDelegate::TextRole, PAGE_TITLE_4);
    spectraItem->setData(AdvMenuDelegate::IconRole, QIcon(QStringLiteral(":/icons/adv-menu-spectra")));
    menuWidget->addItem(spectraItem);

    auto outputItem = new QListWidgetItem;
    outputItem->setData(AdvMenuDelegate::TextRole, PAGE_TITLE_2);
    outputItem->setData(AdvMenuDelegate::IconRole, QIcon(QStringLiteral(":/icons/adv-menu-output")));
    menuWidget->addItem(outputItem);
}

void AdvancedSettingsPage::changePage(int index)
{
    advancedSettingContainer->setCurrentPage(index);
}

bool AdvancedSettingsPage::requestSettingsReset()
{
    return WidgetUtils::yesNoQuestion(this,
                tr("Reset Advanced Settings"),
                tr("<p>Do you want to reset all the "
                   "Advanced Settings to the default settings?</p>"),
                tr("<p>You cannot undo this action.</p>"));
}

void AdvancedSettingsPage::resetButtonCLicked()
{
    if (requestSettingsReset())
    {
        advancedSettingContainer->processingOptions()->reset();
        advancedSettingContainer->statisticalOptions()->reset();
        advancedSettingContainer->spectralOptions()->reset();
        advancedSettingContainer->outputOptions()->reset();
        ecProject_->setModified(true);
    }
}

void AdvancedSettingsPage::updateSmartfluxBar()
{
    smartfluxBar->setVisible(configState_->project.smartfluxMode);

    advancedSettingContainer->processingOptions()->getPlanarFitSettingsDialog()
            ->setSmartfluxUI();
    advancedSettingContainer->processingOptions()->getTimeLagSettingsDialog()
            ->setSmartfluxUI();

    advancedSettingContainer->spectralOptions()->setSmartfluxUI();
    advancedSettingContainer->outputOptions()->setSmartfluxUI();
}
