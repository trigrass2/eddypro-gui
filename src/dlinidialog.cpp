/***************************************************************************
  dlinidialog.cpp
  ---------------
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
 ***************************************************************************/

#include "dlinidialog.h"

#include <QApplication>
#include <QDebug>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTabWidget>
#include <QVBoxLayout>

#include "dlinstrtab.h"
#include "dlproject.h"
#include "dlrawfiledesctab.h"
#include "dlsitetab.h"
#include "fileutils.h"
#include "widget_utils.h"

DlIniDialog::DlIniDialog(QWidget *parent, DlProject *dlProject, ConfigState* config) :
    QDialog(parent),
    filename_(QString()),
    newFlag_(true),
    dlProject_(dlProject),
    configState_(config)
{
    // tab widget
    tabwidget_ = new QTabWidget(this);

    // pages
    site_tab = new DlSiteTab(this, dlProject_);
    site_tab->setToolTip(tr("<b>Station:</b> Enter information that describes the flux station."));
    tabwidget_->addTab(site_tab, tr("Station"));
    instruments_tab = new DlInstrTab(this, dlProject_);
    instruments_tab->setToolTip(tr("<b>Instruments:</b> Enter information that describes all anemometer(s) and gas analyzer(s) used at the flux station to collect raw data you want to process."));
    tabwidget_->addTab(instruments_tab, tr("Instruments"));
    rawfile_tab = new DlRawfileDescTab(this, dlProject_);
    rawfile_tab->setToolTip(tr("<b>Raw file description:</b> Here you specify the order of variables in the raw files, scaling or converting values, flag thresholds for individual samples, and time lags."));
    tabwidget_->addTab(rawfile_tab, tr("Raw File Description"));

    // buttons
    saveAsButton = new QPushButton(tr("Save Metadata As..."));
    saveAsButton->setProperty("mdDialogButton", true);
    saveAsButton->setToolTip(tr("<b>Save as...:</b> Saves the metadata file with a new file name."));
    saveAsButton->setMaximumWidth(saveAsButton->sizeHint().width());

    resetButton = new QPushButton(tr("Reset Metadata"));
    resetButton->setProperty("mdDialogButton", true);
    resetButton->setToolTip(tr("<b>Reset:</b> Reset the default settings in the <i><b>Metadata File Editor</i></b>."));
    resetButton->setEnabled(false);
    resetButton->setMaximumWidth(resetButton->sizeHint().width());

    connect(resetButton, &QPushButton::clicked,
            this, &DlIniDialog::defaults);
    connect(saveAsButton, &QPushButton::clicked,
            this, &DlIniDialog::saveAsButtonClicked);

    connect(dlProject_, &DlProject::projectNew,
            this, &DlIniDialog::reset);
    connect(dlProject_, &DlProject::projectChanged,
            this, &DlIniDialog::refresh);

    // NOTE: queued connection prevents double call to saveAvailable()
    // which triggers a crash when changing input unit on a unsaved
    // metadata. to further investigate
    connect(dlProject_, SIGNAL(projectModified()),
            this, SLOT(saveAvailable()), Qt::QueuedConnection);

    auto buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(resetButton);
    buttonLayout->addWidget(saveAsButton);
    buttonLayout->addStretch();

    auto mainlayout = new QVBoxLayout;
    mainlayout->addWidget(tabwidget_);
    mainlayout->addLayout(buttonLayout);
    mainlayout->setSpacing(0);
    mainlayout->setSizeConstraint(QLayout::SetNoConstraint);
    setLayout(mainlayout);
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    dlProject_->newProject(configState_->project);
}

// flush/reset the entire view
void DlIniDialog::refresh()
{
    // save the modified flag to prevent side effects of setting widgets
    bool oldmod = dlProject_->modified();
    dlProject_->blockSignals(true);

    // reset tab views
    site_tab->refresh();
    instruments_tab->refresh();
    rawfile_tab->refresh();

    // restore modified flag
    dlProject_->setModified(oldmod);
    dlProject_->blockSignals(false);
}

// reset the entire view
void DlIniDialog::reset()
{
    // save the modified flag to prevent side effects of setting widgets
    bool oldmod = dlProject_->modified();
    dlProject_->blockSignals(true);

    // reset tab views
    site_tab->reset();
    instruments_tab->reset();
    rawfile_tab->reset();

    // restore modified flag
    dlProject_->setModified(oldmod);
    dlProject_->blockSignals(false);
}

void DlIniDialog::saveAsButtonClicked()
{
    newFlag_ = true;
    apply();
}

// OK button was pressed
void DlIniDialog::accept()
{
    apply();
}

// Set dialog to default values
void DlIniDialog::defaults()
{
    if (!newFlag_)
    {
        if (requestMetadataReset())
        {
            defaults_2();
        }
    }
}

// Set dialog to default values
void DlIniDialog::defaults_2()
{
    dlProject_->newProject(configState_->project);
    newFlag_ = true;
    disableResetButton(newFlag_);
    emit mdFileEditClearRequest();
}

bool DlIniDialog::openFile(const QString &fileName, bool embedded)
{
    if (!fileName.isEmpty())
    {
        if (QFile::exists(fileName))
        {
            if (dlProject_->nativeFormat(fileName))
            {
                bool modified = false;
                if (dlProject_->loadProject(fileName, !embedded, &modified, true))
                {
                    filename_ = fileName;
                    newFlag_ = false;
                    disableResetButton(newFlag_);

                    if (modified && !embedded)
                    {
                        // load was successful
                        WidgetUtils::information(
                            nullptr,
                            tr("Load Metadata"),
                            tr("The metadata file was successfully imported "
                               "and updated."));
                    }
                    return true;
                }
                // load was unsuccessful
                WidgetUtils::warning(this,
                    tr("Load Metadata Error"),
                    tr("Unable to load the project <p>%1</p>")
                    .arg(QFileInfo(filename_).fileName()));

                // close the current open project to prevent partial loading
                // of ec project settings (currently there is no roll-back
                // of the loadProject() function)
                defaults_2();

                return false;
            }
            // file not in native format
            return false;
        }
        // file does not exist
        filename_.clear();
    }
    // empty file name
    return false;
}

// Apply values
void DlIniDialog::apply()
{
    if (newFlag_)
    {
        fileSaveAs();
    }
    else
    {
        if (!saveFile(filename_))
        {
            // error in saving file
            WidgetUtils::warning(this,
                                 tr("Save Metadata Error"),
                                 tr("%1 was unable to save <b>%2</b>")
                                 .arg(Defs::APP_NAME, filename_));
        }
    }
}

bool DlIniDialog::saveFile(const QString& filename)
{
    bool status = true;

    if (!filename.isEmpty())
    {
        status = dlProject_->saveProject(filename);
    }
    return status;
}

void DlIniDialog::fileSaveAs()
{
    QString fname;

    auto searchPath = WidgetUtils::getSearchPathHint();

    auto filenameHint = QString();
    if (dlProject_->filename().isEmpty())
    {
        filenameHint = searchPath;
    }
    else if (FileUtils::existsPath(QFileInfo(dlProject_->filename()).canonicalPath()))
    {
        filenameHint = dlProject_->filename();
    }
    else
    {
        filenameHint = searchPath;
    }

    fname = QFileDialog::getSaveFileName(this,
                                         tr("Save the Metadata File As..."),
                                         filenameHint,
                                         tr("%1 Metadata Files (*.metadata);;All files (*)").arg(Defs::APP_NAME),
                                         nullptr,
                                         QFileDialog::DontConfirmOverwrite);

    // we got a filename
    if (!fname.isEmpty())
    {
        // add suffix if there is none
        QString mdExt = QStringLiteral(".") + Defs::METADATA_FILE_EXT;
        if (fname.indexOf(mdExt) == -1)
        {
            fname += mdExt;
        }

        // overwrite?
        if (QFile::exists(fname))
        {
            if (!WidgetUtils::okToOverwrite(this, fname)) { return; }
        }

        if (saveFile(fname))
        {
            // successfully saved
            newFlag_ = false;
            disableResetButton(newFlag_);
            filename_ = fname;
            emit metadataFileSaved(filename_);
        }
        else
        {
            // error in saving
            WidgetUtils::warning(this,
                                 tr("Save Metadata Error"),
                                 tr("Unable to save <b>%1</b>")
                                 .arg(QFileInfo(filename_).fileName()));
        }
    }
}

void DlIniDialog::saveAvailable()
{
    if (newFlag_)
    {
        WidgetUtils::information(QApplication::activeWindow(),
                 tr("Save Metadata"),
                 tr("Please save the Metadata file before editing."),
                 tr("Subsequent edits will be saved automatically."));
    }
    apply();
}

// available only when the file has some change
void DlIniDialog::disableResetButton(bool ok)
{
    resetButton->setDisabled(ok);
}

bool DlIniDialog::requestMetadataReset()
{
    return WidgetUtils::yesNoQuestion(this,
                tr("Reset Metadata"),
                tr("<p>Do you want to reset the current metadata values?</p>"),
                tr("<p>You cannot undo this action.</p>"));
}
