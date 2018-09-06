BeagleboneCanInterface.h                                                                            0000664 0001750 0001750 00000000335 13343710512 015423  0                                                                                                    ustar   matthew                         matthew                                                                                                                                                                                                                #ifndef BEAGLEBONECANPROVIDER_H
#define BEAGLEBONECANPROVIDER_H

#include "CanInterface.h"

class BeagleboneCanInterface : public CanInterface
{
public:
    BeagleboneCanInterface();
};

#endif // BEAGLEBONECANPROVIDER_H
                                                                                                                                                                                                                                                                                                   CanInterface.cpp                                                                                    0000664 0001750 0001750 00000000603 13343711233 014011  0                                                                                                    ustar   matthew                         matthew                                                                                                                                                                                                                #include "CanInterface.h"

CanInterface::CanInterface()
{

}


void CanInterface::SetCallbacks(CanInterfaceCallbacks_t* callbacks) 
{   
    this->_callbacks = callbacks;
}

void CanInterface::OnFrameReceived(can_frame_t frame)
{
    if (nullptr != this->_callbacks
        && nullptr != this->_callbacks->OnFrameReceived)
    {
        this->_callbacks->OnFrameReceived(frame);
    }
}
                                                                                                                             CanInterface.h                                                                                      0000664 0001750 0001750 00000001066 13343711262 013464  0                                                                                                    ustar   matthew                         matthew                                                                                                                                                                                                                #ifndef CanInterface_H
#define CanInterface_H

#include <cstdint>

typedef struct can_frame_e
{
    uint16_t id;
    uint8_t length;
    uint8_t data[8];
} can_frame_t;

typedef struct CanInterfaceCallbacks
{
    void (*OnFrameReceived)(can_frame_t frame);
} CanInterfaceCallbacks_t;

class CanInterface
{
private:
    CanInterfaceCallbacks_t* _callbacks = nullptr;
protected:
    virtual void OnFrameReceived(can_frame_t frame) final;
public:
    CanInterface();
    virtual void SetCallbacks(CanInterfaceCallbacks_t* callbacks) final;
};

#endif // CanInterface_H
                                                                                                                                                                                                                                                                                                                                                                                                                                                                          main.cpp                                                                                            0000664 0001750 0001750 00000000254 13343705274 012425  0                                                                                                    ustar   matthew                         matthew                                                                                                                                                                                                                #include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
                                                                                                                                                                                                                                                                                                                                                    mainwindow.cpp                                                                                      0000664 0001750 0001750 00000000333 13343705274 013653  0                                                                                                    ustar   matthew                         matthew                                                                                                                                                                                                                #include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
                                                                                                                                                                                                                                                                                                     mainwindow.h                                                                                        0000664 0001750 0001750 00000000443 13343705274 013322  0                                                                                                    ustar   matthew                         matthew                                                                                                                                                                                                                #ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
                                                                                                                                                                                                                             mainwindow.ui                                                                                       0000664 0001750 0001750 00000001574 13343705534 013515  0                                                                                                    ustar   matthew                         matthew                                                                                                                                                                                                                <?xml version="1.0" encoding="UTF-8"?>
<ui version="4.0">
 <class>MainWindow</class>
 <widget class="QMainWindow" name="MainWindow">
  <property name="geometry">
   <rect>
    <x>0</x>
    <y>0</y>
    <width>800</width>
    <height>480</height>
   </rect>
  </property>
  <property name="sizePolicy">
   <sizepolicy hsizetype="Fixed" vsizetype="Fixed">
    <horstretch>0</horstretch>
    <verstretch>0</verstretch>
   </sizepolicy>
  </property>
  <property name="minimumSize">
   <size>
    <width>800</width>
    <height>480</height>
   </size>
  </property>
  <property name="maximumSize">
   <size>
    <width>800</width>
    <height>480</height>
   </size>
  </property>
  <property name="windowTitle">
   <string>MainWindow</string>
  </property>
  <widget class="QWidget" name="centralWidget"/>
 </widget>
 <layoutdefault spacing="6" margin="11"/>
 <resources/>
 <connections/>
</ui>
                                                                                                                                    qtdash.pro                                                                                          0000664 0001750 0001750 00000000744 13343710764 013007  0                                                                                                    ustar   matthew                         matthew                                                                                                                                                                                                                #-------------------------------------------------
#
# Project created by QtCreator 2018-09-05T03:50:14
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qtdash
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    BeagleboneCanInterface.cpp \
    CanInterface.cpp

HEADERS  += mainwindow.h \
    BeagleboneCanInterface.h \
    CanInterface.h

FORMS    += mainwindow.ui

CONFIG += c++11
                            qtdash.pro.user                                                                                     0000664 0001750 0001750 00000043250 13343711274 013760  0                                                                                                    ustar   matthew                         matthew                                                                                                                                                                                                                <?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE QtCreatorProject>
<!-- Written by QtCreator 3.0.1, 2018-09-05T04:24:28. -->
<qtcreator>
 <data>
  <variable>ProjectExplorer.Project.ActiveTarget</variable>
  <value type="int">0</value>
 </data>
 <data>
  <variable>ProjectExplorer.Project.EditorSettings</variable>
  <valuemap type="QVariantMap">
   <value type="bool" key="EditorConfiguration.AutoIndent">true</value>
   <value type="bool" key="EditorConfiguration.AutoSpacesForTabs">false</value>
   <value type="bool" key="EditorConfiguration.CamelCaseNavigation">true</value>
   <valuemap type="QVariantMap" key="EditorConfiguration.CodeStyle.0">
    <value type="QString" key="language">Cpp</value>
    <valuemap type="QVariantMap" key="value">
     <value type="QByteArray" key="CurrentPreferences">CppGlobal</value>
    </valuemap>
   </valuemap>
   <valuemap type="QVariantMap" key="EditorConfiguration.CodeStyle.1">
    <value type="QString" key="language">QmlJS</value>
    <valuemap type="QVariantMap" key="value">
     <value type="QByteArray" key="CurrentPreferences">QmlJSGlobal</value>
    </valuemap>
   </valuemap>
   <value type="int" key="EditorConfiguration.CodeStyle.Count">2</value>
   <value type="QByteArray" key="EditorConfiguration.Codec">UTF-8</value>
   <value type="bool" key="EditorConfiguration.ConstrainTooltips">false</value>
   <value type="int" key="EditorConfiguration.IndentSize">4</value>
   <value type="bool" key="EditorConfiguration.KeyboardTooltips">false</value>
   <value type="bool" key="EditorConfiguration.MouseNavigation">true</value>
   <value type="int" key="EditorConfiguration.PaddingMode">1</value>
   <value type="bool" key="EditorConfiguration.ScrollWheelZooming">true</value>
   <value type="int" key="EditorConfiguration.SmartBackspaceBehavior">0</value>
   <value type="bool" key="EditorConfiguration.SpacesForTabs">true</value>
   <value type="int" key="EditorConfiguration.TabKeyBehavior">0</value>
   <value type="int" key="EditorConfiguration.TabSize">8</value>
   <value type="bool" key="EditorConfiguration.UseGlobal">true</value>
   <value type="int" key="EditorConfiguration.Utf8BomBehavior">1</value>
   <value type="bool" key="EditorConfiguration.addFinalNewLine">true</value>
   <value type="bool" key="EditorConfiguration.cleanIndentation">true</value>
   <value type="bool" key="EditorConfiguration.cleanWhitespace">true</value>
   <value type="bool" key="EditorConfiguration.inEntireDocument">false</value>
  </valuemap>
 </data>
 <data>
  <variable>ProjectExplorer.Project.PluginSettings</variable>
  <valuemap type="QVariantMap"/>
 </data>
 <data>
  <variable>ProjectExplorer.Project.Target.0</variable>
  <valuemap type="QVariantMap">
   <value type="QString" key="ProjectExplorer.ProjectConfiguration.DefaultDisplayName">Desktop</value>
   <value type="QString" key="ProjectExplorer.ProjectConfiguration.DisplayName">Desktop</value>
   <value type="QString" key="ProjectExplorer.ProjectConfiguration.Id">{7cd5e3e5-bd2a-4ed7-92b9-ee5bf10bd1cb}</value>
   <value type="int" key="ProjectExplorer.Target.ActiveBuildConfiguration">0</value>
   <value type="int" key="ProjectExplorer.Target.ActiveDeployConfiguration">0</value>
   <value type="int" key="ProjectExplorer.Target.ActiveRunConfiguration">0</value>
   <valuemap type="QVariantMap" key="ProjectExplorer.Target.BuildConfiguration.0">
    <value type="QString" key="ProjectExplorer.BuildConfiguration.BuildDirectory">/home/matthew/Desktop/qt/build-qtdash-Desktop-Debug</value>
    <valuemap type="QVariantMap" key="ProjectExplorer.BuildConfiguration.BuildStepList.0">
     <valuemap type="QVariantMap" key="ProjectExplorer.BuildStepList.Step.0">
      <value type="bool" key="ProjectExplorer.BuildStep.Enabled">true</value>
      <value type="QString" key="ProjectExplorer.ProjectConfiguration.DefaultDisplayName">qmake</value>
      <value type="QString" key="ProjectExplorer.ProjectConfiguration.DisplayName"></value>
      <value type="QString" key="ProjectExplorer.ProjectConfiguration.Id">QtProjectManager.QMakeBuildStep</value>
      <value type="bool" key="QtProjectManager.QMakeBuildStep.LinkQmlDebuggingLibrary">false</value>
      <value type="bool" key="QtProjectManager.QMakeBuildStep.LinkQmlDebuggingLibraryAuto">true</value>
      <value type="QString" key="QtProjectManager.QMakeBuildStep.QMakeArguments"></value>
      <value type="bool" key="QtProjectManager.QMakeBuildStep.QMakeForced">false</value>
     </valuemap>
     <valuemap type="QVariantMap" key="ProjectExplorer.BuildStepList.Step.1">
      <value type="bool" key="ProjectExplorer.BuildStep.Enabled">true</value>
      <value type="QString" key="ProjectExplorer.ProjectConfiguration.DefaultDisplayName">Make</value>
      <value type="QString" key="ProjectExplorer.ProjectConfiguration.DisplayName"></value>
      <value type="QString" key="ProjectExplorer.ProjectConfiguration.Id">Qt4ProjectManager.MakeStep</value>
      <valuelist type="QVariantList" key="Qt4ProjectManager.MakeStep.AutomaticallyAddedMakeArguments">
       <value type="QString">-w</value>
       <value type="QString">-r</value>
      </valuelist>
      <value type="bool" key="Qt4ProjectManager.MakeStep.Clean">false</value>
      <value type="QString" key="Qt4ProjectManager.MakeStep.MakeArguments"></value>
      <value type="QString" key="Qt4ProjectManager.MakeStep.MakeCommand"></value>
     </valuemap>
     <value type="int" key="ProjectExplorer.BuildStepList.StepsCount">2</value>
     <value type="QString" key="ProjectExplorer.ProjectConfiguration.DefaultDisplayName">Build</value>
     <value type="QString" key="ProjectExplorer.ProjectConfiguration.DisplayName"></value>
     <value type="QString" key="ProjectExplorer.ProjectConfiguration.Id">ProjectExplorer.BuildSteps.Build</value>
    </valuemap>
    <valuemap type="QVariantMap" key="ProjectExplorer.BuildConfiguration.BuildStepList.1">
     <valuemap type="QVariantMap" key="ProjectExplorer.BuildStepList.Step.0">
      <value type="bool" key="ProjectExplorer.BuildStep.Enabled">true</value>
      <value type="QString" key="ProjectExplorer.ProjectConfiguration.DefaultDisplayName">Make</value>
      <value type="QString" key="ProjectExplorer.ProjectConfiguration.DisplayName"></value>
      <value type="QString" key="ProjectExplorer.ProjectConfiguration.Id">Qt4ProjectManager.MakeStep</value>
      <valuelist type="QVariantList" key="Qt4ProjectManager.MakeStep.AutomaticallyAddedMakeArguments">
       <value type="QString">-w</value>
       <value type="QString">-r</value>
      </valuelist>
      <value type="bool" key="Qt4ProjectManager.MakeStep.Clean">true</value>
      <value type="QString" key="Qt4ProjectManager.MakeStep.MakeArguments">clean</value>
      <value type="QString" key="Qt4ProjectManager.MakeStep.MakeCommand"></value>
     </valuemap>
     <value type="int" key="ProjectExplorer.BuildStepList.StepsCount">1</value>
     <value type="QString" key="ProjectExplorer.ProjectConfiguration.DefaultDisplayName">Clean</value>
     <value type="QString" key="ProjectExplorer.ProjectConfiguration.DisplayName"></value>
     <value type="QString" key="ProjectExplorer.ProjectConfiguration.Id">ProjectExplorer.BuildSteps.Clean</value>
    </valuemap>
    <value type="int" key="ProjectExplorer.BuildConfiguration.BuildStepListCount">2</value>
    <value type="bool" key="ProjectExplorer.BuildConfiguration.ClearSystemEnvironment">false</value>
    <valuelist type="QVariantList" key="ProjectExplorer.BuildConfiguration.UserEnvironmentChanges"/>
    <value type="QString" key="ProjectExplorer.ProjectConfiguration.DefaultDisplayName">Debug</value>
    <value type="QString" key="ProjectExplorer.ProjectConfiguration.DisplayName"></value>
    <value type="QString" key="ProjectExplorer.ProjectConfiguration.Id">Qt4ProjectManager.Qt4BuildConfiguration</value>
    <value type="int" key="Qt4ProjectManager.Qt4BuildConfiguration.BuildConfiguration">2</value>
    <value type="bool" key="Qt4ProjectManager.Qt4BuildConfiguration.UseShadowBuild">true</value>
   </valuemap>
   <valuemap type="QVariantMap" key="ProjectExplorer.Target.BuildConfiguration.1">
    <value type="QString" key="ProjectExplorer.BuildConfiguration.BuildDirectory">/home/matthew/Desktop/qt/build-qtdash-Desktop-Release</value>
    <valuemap type="QVariantMap" key="ProjectExplorer.BuildConfiguration.BuildStepList.0">
     <valuemap type="QVariantMap" key="ProjectExplorer.BuildStepList.Step.0">
      <value type="bool" key="ProjectExplorer.BuildStep.Enabled">true</value>
      <value type="QString" key="ProjectExplorer.ProjectConfiguration.DefaultDisplayName">qmake</value>
      <value type="QString" key="ProjectExplorer.ProjectConfiguration.DisplayName"></value>
      <value type="QString" key="ProjectExplorer.ProjectConfiguration.Id">QtProjectManager.QMakeBuildStep</value>
      <value type="bool" key="QtProjectManager.QMakeBuildStep.LinkQmlDebuggingLibrary">false</value>
      <value type="bool" key="QtProjectManager.QMakeBuildStep.LinkQmlDebuggingLibraryAuto">true</value>
      <value type="QString" key="QtProjectManager.QMakeBuildStep.QMakeArguments"></value>
      <value type="bool" key="QtProjectManager.QMakeBuildStep.QMakeForced">false</value>
     </valuemap>
     <valuemap type="QVariantMap" key="ProjectExplorer.BuildStepList.Step.1">
      <value type="bool" key="ProjectExplorer.BuildStep.Enabled">true</value>
      <value type="QString" key="ProjectExplorer.ProjectConfiguration.DefaultDisplayName">Make</value>
      <value type="QString" key="ProjectExplorer.ProjectConfiguration.DisplayName"></value>
      <value type="QString" key="ProjectExplorer.ProjectConfiguration.Id">Qt4ProjectManager.MakeStep</value>
      <valuelist type="QVariantList" key="Qt4ProjectManager.MakeStep.AutomaticallyAddedMakeArguments">
       <value type="QString">-w</value>
       <value type="QString">-r</value>
      </valuelist>
      <value type="bool" key="Qt4ProjectManager.MakeStep.Clean">false</value>
      <value type="QString" key="Qt4ProjectManager.MakeStep.MakeArguments"></value>
      <value type="QString" key="Qt4ProjectManager.MakeStep.MakeCommand"></value>
     </valuemap>
     <value type="int" key="ProjectExplorer.BuildStepList.StepsCount">2</value>
     <value type="QString" key="ProjectExplorer.ProjectConfiguration.DefaultDisplayName">Build</value>
     <value type="QString" key="ProjectExplorer.ProjectConfiguration.DisplayName"></value>
     <value type="QString" key="ProjectExplorer.ProjectConfiguration.Id">ProjectExplorer.BuildSteps.Build</value>
    </valuemap>
    <valuemap type="QVariantMap" key="ProjectExplorer.BuildConfiguration.BuildStepList.1">
     <valuemap type="QVariantMap" key="ProjectExplorer.BuildStepList.Step.0">
      <value type="bool" key="ProjectExplorer.BuildStep.Enabled">true</value>
      <value type="QString" key="ProjectExplorer.ProjectConfiguration.DefaultDisplayName">Make</value>
      <value type="QString" key="ProjectExplorer.ProjectConfiguration.DisplayName"></value>
      <value type="QString" key="ProjectExplorer.ProjectConfiguration.Id">Qt4ProjectManager.MakeStep</value>
      <valuelist type="QVariantList" key="Qt4ProjectManager.MakeStep.AutomaticallyAddedMakeArguments">
       <value type="QString">-w</value>
       <value type="QString">-r</value>
      </valuelist>
      <value type="bool" key="Qt4ProjectManager.MakeStep.Clean">true</value>
      <value type="QString" key="Qt4ProjectManager.MakeStep.MakeArguments">clean</value>
      <value type="QString" key="Qt4ProjectManager.MakeStep.MakeCommand"></value>
     </valuemap>
     <value type="int" key="ProjectExplorer.BuildStepList.StepsCount">1</value>
     <value type="QString" key="ProjectExplorer.ProjectConfiguration.DefaultDisplayName">Clean</value>
     <value type="QString" key="ProjectExplorer.ProjectConfiguration.DisplayName"></value>
     <value type="QString" key="ProjectExplorer.ProjectConfiguration.Id">ProjectExplorer.BuildSteps.Clean</value>
    </valuemap>
    <value type="int" key="ProjectExplorer.BuildConfiguration.BuildStepListCount">2</value>
    <value type="bool" key="ProjectExplorer.BuildConfiguration.ClearSystemEnvironment">false</value>
    <valuelist type="QVariantList" key="ProjectExplorer.BuildConfiguration.UserEnvironmentChanges"/>
    <value type="QString" key="ProjectExplorer.ProjectConfiguration.DefaultDisplayName">Release</value>
    <value type="QString" key="ProjectExplorer.ProjectConfiguration.DisplayName"></value>
    <value type="QString" key="ProjectExplorer.ProjectConfiguration.Id">Qt4ProjectManager.Qt4BuildConfiguration</value>
    <value type="int" key="Qt4ProjectManager.Qt4BuildConfiguration.BuildConfiguration">0</value>
    <value type="bool" key="Qt4ProjectManager.Qt4BuildConfiguration.UseShadowBuild">true</value>
   </valuemap>
   <value type="int" key="ProjectExplorer.Target.BuildConfigurationCount">2</value>
   <valuemap type="QVariantMap" key="ProjectExplorer.Target.DeployConfiguration.0">
    <valuemap type="QVariantMap" key="ProjectExplorer.BuildConfiguration.BuildStepList.0">
     <value type="int" key="ProjectExplorer.BuildStepList.StepsCount">0</value>
     <value type="QString" key="ProjectExplorer.ProjectConfiguration.DefaultDisplayName">Deploy</value>
     <value type="QString" key="ProjectExplorer.ProjectConfiguration.DisplayName"></value>
     <value type="QString" key="ProjectExplorer.ProjectConfiguration.Id">ProjectExplorer.BuildSteps.Deploy</value>
    </valuemap>
    <value type="int" key="ProjectExplorer.BuildConfiguration.BuildStepListCount">1</value>
    <value type="QString" key="ProjectExplorer.ProjectConfiguration.DefaultDisplayName">Deploy locally</value>
    <value type="QString" key="ProjectExplorer.ProjectConfiguration.DisplayName"></value>
    <value type="QString" key="ProjectExplorer.ProjectConfiguration.Id">ProjectExplorer.DefaultDeployConfiguration</value>
   </valuemap>
   <value type="int" key="ProjectExplorer.Target.DeployConfigurationCount">1</value>
   <valuemap type="QVariantMap" key="ProjectExplorer.Target.PluginSettings"/>
   <valuemap type="QVariantMap" key="ProjectExplorer.Target.RunConfiguration.0">
    <valuelist type="QVariantList" key="Analyzer.Valgrind.AddedSuppressionFiles"/>
    <value type="bool" key="Analyzer.Valgrind.Callgrind.CollectBusEvents">false</value>
    <value type="bool" key="Analyzer.Valgrind.Callgrind.CollectSystime">false</value>
    <value type="bool" key="Analyzer.Valgrind.Callgrind.EnableBranchSim">false</value>
    <value type="bool" key="Analyzer.Valgrind.Callgrind.EnableCacheSim">false</value>
    <value type="bool" key="Analyzer.Valgrind.Callgrind.EnableEventToolTips">true</value>
    <value type="double" key="Analyzer.Valgrind.Callgrind.MinimumCostRatio">0.01</value>
    <value type="double" key="Analyzer.Valgrind.Callgrind.VisualisationMinimumCostRatio">10</value>
    <value type="bool" key="Analyzer.Valgrind.FilterExternalIssues">true</value>
    <value type="int" key="Analyzer.Valgrind.LeakCheckOnFinish">1</value>
    <value type="int" key="Analyzer.Valgrind.NumCallers">25</value>
    <valuelist type="QVariantList" key="Analyzer.Valgrind.RemovedSuppressionFiles"/>
    <value type="int" key="Analyzer.Valgrind.SelfModifyingCodeDetection">1</value>
    <value type="bool" key="Analyzer.Valgrind.Settings.UseGlobalSettings">true</value>
    <value type="bool" key="Analyzer.Valgrind.ShowReachable">false</value>
    <value type="bool" key="Analyzer.Valgrind.TrackOrigins">true</value>
    <value type="QString" key="Analyzer.Valgrind.ValgrindExecutable">valgrind</value>
    <valuelist type="QVariantList" key="Analyzer.Valgrind.VisibleErrorKinds">
     <value type="int">0</value>
     <value type="int">1</value>
     <value type="int">2</value>
     <value type="int">3</value>
     <value type="int">4</value>
     <value type="int">5</value>
     <value type="int">6</value>
     <value type="int">7</value>
     <value type="int">8</value>
     <value type="int">9</value>
     <value type="int">10</value>
     <value type="int">11</value>
     <value type="int">12</value>
     <value type="int">13</value>
     <value type="int">14</value>
    </valuelist>
    <value type="int" key="PE.EnvironmentAspect.Base">2</value>
    <valuelist type="QVariantList" key="PE.EnvironmentAspect.Changes"/>
    <value type="QString" key="ProjectExplorer.ProjectConfiguration.DefaultDisplayName">qtdash</value>
    <value type="QString" key="ProjectExplorer.ProjectConfiguration.DisplayName"></value>
    <value type="QString" key="ProjectExplorer.ProjectConfiguration.Id">Qt4ProjectManager.Qt4RunConfiguration:/home/matthew/Desktop/qt/qtdash/qtdash.pro</value>
    <value type="QString" key="Qt4ProjectManager.Qt4RunConfiguration.CommandLineArguments"></value>
    <value type="QString" key="Qt4ProjectManager.Qt4RunConfiguration.ProFile">qtdash.pro</value>
    <value type="bool" key="Qt4ProjectManager.Qt4RunConfiguration.UseDyldImageSuffix">false</value>
    <value type="bool" key="Qt4ProjectManager.Qt4RunConfiguration.UseTerminal">false</value>
    <value type="QString" key="Qt4ProjectManager.Qt4RunConfiguration.UserWorkingDirectory"></value>
    <value type="uint" key="RunConfiguration.QmlDebugServerPort">3768</value>
    <value type="bool" key="RunConfiguration.UseCppDebugger">true</value>
    <value type="bool" key="RunConfiguration.UseCppDebuggerAuto">false</value>
    <value type="bool" key="RunConfiguration.UseMultiProcess">false</value>
    <value type="bool" key="RunConfiguration.UseQmlDebugger">false</value>
    <value type="bool" key="RunConfiguration.UseQmlDebuggerAuto">true</value>
   </valuemap>
   <value type="int" key="ProjectExplorer.Target.RunConfigurationCount">1</value>
  </valuemap>
 </data>
 <data>
  <variable>ProjectExplorer.Project.TargetCount</variable>
  <value type="int">1</value>
 </data>
 <data>
  <variable>ProjectExplorer.Project.Updater.EnvironmentId</variable>
  <value type="QByteArray">{1ee59395-7d14-4766-8512-4e3807d80e2b}</value>
 </data>
 <data>
  <variable>ProjectExplorer.Project.Updater.FileVersion</variable>
  <value type="int">15</value>
 </data>
</qtcreator>
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        