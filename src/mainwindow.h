/***************************************************************************
  mainwindow.h
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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "configstate.h"
#include "defs.h"
#include "fileutils.h"
#include "process.h"

class QPlainTextEdit;
class QDockWidget;
class QActionGroup;
class QLabel;

class AboutDialog;
class ClickLabel;
class CustomSplashScreen;
class DlProject;
class EcProject;
class InfoMessage;
class MainWidget;
class MdiChild;
class TooltipFilter;
class UpdateDialog;

/// \class MainWindow
/// \brief Class representing the main window of the application
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QString  filename = QString(),
               QString  appEnvPath = QString(),
               CustomSplashScreen* splashscreen = nullptr,
               QWidget* parent = nullptr,
               Qt::WindowFlags flags = Qt::WindowFlags());
    ~MainWindow() override;

    bool queryEcProjectImport(const QString &filename);
    bool queryDlProjectImport();

protected:
    void closeEvent(QCloseEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;
    bool eventFilter(QObject* o, QEvent* e) override;
    void wheelEvent(QWheelEvent* event) override;
    void changeEvent(QEvent* event) override;

private slots:
    void initialize();
    void fileNew();
    void fileOpen(const QString& fileName = QString());
    void fileRecent();
    bool fileSave(bool quiet = false);
    bool fileSaveAs(const QString& fileName = QString());
    void fileClose();

    void fileOpenRequest(const QString& file);
    void fileNewRequest();

    bool fileSaveSilently();

    // add a file to recent file menu
    void addRecent(const QString& filename);

    // Windows
    void updateMenuActionStatus(Defs::CurrPage page);

    // View
    void setFullScreen(bool on);
    void toggleStatusbar(bool on);
    void viewTooltipOutput(bool on);
    void viewConsoleOutput(bool on);
    void viewInfoOutput(bool on);

    // displays help contents
    void showHelp();
    void showPdfHelp();
    void showStarterPdfHelp();
    void setOfflineHelp(bool yes);
    void setSmartfluxMode(bool on);
    void about();

    void setEcProjectModified();
    void recentMenuShow();

    void updateHtmlDock(QPlainTextEdit* dock, const QString& htmlMsg);
    void changePage(Defs::CurrPage page, bool testCurrentPage = true);
    void setCurrentPage(Defs::CurrPage page);
    void windowTitleUpdate(Defs::CurrPage page);
    void updatePage(Defs::CurrPage page);
    void updateRunButtonsAvailability();

    void setCurrentStatus(Defs::CurrStatus state);
    void setCurrentRunStatus(Defs::CurrRunStatus state);

    void viewWelcomePage();
    void viewProjectPage();
    void viewBasicSettingsPage();
    void viewAdvancedSettingsPage();
    void viewRunPage();

    void getRunExpress();
    void getRunAdvanced();
    void getRunRetriever();
    void pauseResumeComputations(Defs::CurrRunStatus mode);
    bool pauseEngine(Defs::CurrRunStatus mode);
    bool resumeEngine(Defs::CurrRunStatus mode);
    void stopEngine();
    void stopEngineProcess();

    void updateSpectraPaths();

    void resetRunIcons();
    void setRunExpIcon2Resume();
    void setRunAdvIcon2Resume();
    void setRunRetIcon2Resume();
    void setRunExpIcon2Pause();
    void setRunAdvIcon2Pause();
    void setRunRetIcon2Pause();

    void displayExitDialog();
    void onlineHelpTrigger_1();

    void updateConsoleLine(QByteArray& data);
    void updateConsoleChar(QByteArray& data);
    void updateConsoleReceived();
    void updateConsoleError();

    void setMetadataRead(bool b);

    void showAutoUpdateDialog();
    void showAutoUpdateResults();
    void showUpdateDialog();

    void openLicorSite() const;

    void checkInternetConnection();
    void updateInfoMessages();
    void showGuidedModeMessages_1();
    void showGuidedModeMessages_2();
    void showGuidedModeMessages_3();

    // restore application state
    void restorePreviousStatus();

    void connectBinarySettingsDialog();
    void connectPlanarFitDialog();
    void connectTimeLagDialog();

    void updateDockBorder(Qt::DockWidgetArea);

    void scheduleMdCleanup();

    void closeMainWindow();

private:
    void runExpress();
    void runAdvancedStep_1();
    void runAdvancedStep_2();
    void runRetriever();
    void createEngineProcess();
    void createActions();
    void connectActions();
    void createMenus();
    void createToolBars();
    void createStatusBar();
    void createInfoDockWin();
    void createConsoleDockWin();
    bool continueBeforeClose();
    void saveEnvSettings(const QString& env);

    void setCurrentProjectFile(const QString& fileName, bool modified = false);
    const QString &currentProjectFile() const;

    // set window caption from file name
    void setFileCaption(const QString& filename, bool clearStar = true);
    void updateStatusBar();

    void readSettings();
    void writeSettings();

    // save application state
    bool openFile(const QString& filename);
    void newFile();
    void loadFile(const QString& fileName);
    bool saveFile(const QString& fileName);

    void displayExitMsg(Process::ExitStatus exitReason);
    void displayExitMsg2(Process::ExitStatus exitReason);
    bool okToStopRun();
    int testBeforeRunningPassed();
    bool alertChangesWhileRunning();
    void togglePageButton(Defs::CurrPage page);
    void changeViewToolbarSeparators(Defs::CurrPage page);

    void checkUpdate();

    void cleanOverdueMessageBox(const QString &messageBoxName);

    void requestSmartFluxMode(bool on);

    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *viewMenu;
    QMenu *toolsMenu;
    QMenu *optionsMenu;
    QMenu *helpMenu;
    QMenu *fileMenuOpenRecent;

    QToolBar *fileToolBar;
    QToolBar *viewToolBar;
    QToolBar *runToolBar;

    ClickLabel* sep1;
    ClickLabel* sep2;
    ClickLabel* sep3;
    ClickLabel* sep4;

    QAction *newAction;
    QAction *openAction;
    QAction *closeAction;
    QAction *recentOpenAction;
    QAction *saveAction;
    QAction *saveAsAction;
    QAction *smartfluxAction;
    QAction *quitAction;
    QActionGroup* viewActionGroup;
    QAction *viewWelcomeAction;
    QAction *viewProjectCreationAction;
    QAction *viewBasicSettingsAction;
    QAction *viewAdvancedAction;
    QAction *viewRunPageAction;
    QAction *runExpressAction;
    QAction *runAdvancedAction;
    QAction *runRetrieverAction;
    QAction *stopAction;
//#if !defined(Q_OS_MACOS)
    QAction *toggleFullScreenAction;
//#endif
    QAction *toggleStatusbarAct;
    QAction* toggleInfoOutputAct;
    QAction *toggleTooltipOutputAct;
    QAction *toggleConsoleOutputAct;
    QActionGroup *changeStyleAction;
    QAction *helpAction;
    QAction *pdfHelpAction;
    QAction *starterPdfHelpAction;
    QAction *toggleOfflineHelpAct;
    QAction* appWebpageAction;
    QAction* forumWebpageAction;
    QAction* checkUpdateAction;
    QAction *aboutAction;
    QAction *aboutQtAction;

    QDockWidget *infoDock;
    QPlainTextEdit *infoOutput;
    QDockWidget *consoleDock;
    QPlainTextEdit *consoleOutput;

    AboutDialog *aboutDialog;
    CustomSplashScreen *splash_screen_;

private:
    TooltipFilter *tooltipFilter_;
    MainWidget *mainWidget_;

    ConfigState configState_;
    DlProject *dlProject_;

    EcProject *ecProject_;
    QString currEcProjectFilename_;
    QString appEnvPath_;
    QLabel *currentProjectLabel;

    QTimer* notificationTimer_;

    // flags
    bool newFlag_;
    bool modifiedFlag_;
    bool openingFlag_;
    bool engineResumableFlag_;
    bool metadataReadFlag_;
    bool neededEngineStep2_;
    bool guidedModeOn_;
    bool basicSettingsPageAvailable_;
    bool runExpressAvailable_;
    bool runAdvancedAvailable_;
    bool newClicked_;

    Defs::CurrPage previousPage_;

    Defs::CurrPage currentPage_;
    Defs::CurrPage currentPage() const;

    Defs::CurrStatus currentStatus_;
    Defs::CurrStatus currentStatus() const;

    Defs::CurrRunStatus currentRunStatus_;
    Defs::CurrRunStatus currentRunStatus() const;

    bool expressClicked_;
    bool advancedClicked_;
    bool retrieverClicked_;

    void showStatusTip(const QString &text) const;

    Process* engineProcess_;

    UpdateDialog* updateDialog;
    void updateInfoDock(bool yes);

    bool argFilename_;

    void loadSmartfluxProjectCopy(const QString &filename);
    void cleanEnvTmpDir();
    void silentMdClenaup();

    bool scheduledSilentMdCleanup_;

    void closeOpenDialogs();

    bool getDatesRangeDialog(Defs::CurrRunMode mode);
    bool showDatesRangeDialog(Defs::CurrRunMode mode);
    FileUtils::DateRange getCurrentDateRange();

    void minimizeGui();
    void maximizeGui();

    void removeSplashScreen();

signals:
    void updateMetadataReadRequest();
    void updateCrossWindRequest();
    void checkMetadataOutputRequest();
    void recentUpdated();
};

#endif // MAINWINDOW_H
