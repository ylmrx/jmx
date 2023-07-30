#define AppName             "JeeMeeX"

#define AppNameUnderscore   StringChange(AppName, " ", "_")
#define AppVersion          "1.0.2"
#define AppUrl              "https://github.com/rclement/meeblip-controller"
#define AppRootDir          "D:/Users_Directory/yoann/Documents/Repos/meeblip-controller"
#define AppBuildDir         "D:/Users_Directory/yoann/Documents/Repos/meeblip-controller/build"
#define AppOutputDir        "D:/Users_Directory/yoann/Documents/Repos/meeblip-controller/build/../installer/output"
#define AppOutputBaseName   "Controller - 1.0.2 - Windows"

[Setup]
AppName                 = {#AppName}
AppVersion              = {#AppVersion}
AppVerName              = {#AppName} {#AppVersion}
AppPublisherURL         = {#AppUrl}
AppSupportURL           = {#AppUrl}
AppUpdatesURL           = {#AppUrl}
AppCopyright            = Copyright (C) 2018
LicenseFile             = {#AppRootDir}\LICENSE.txt
DefaultDirName          = {commonappdata}\{#AppName}
DisableDirPage          = yes
DefaultGroupName        = {#AppName}
DisableProgramGroupPage = no
OutputDir               = {#AppOutputDir}
OutputBaseFilename      = {#AppOutputBaseName}
Compression             = lzma
SolidCompression        = yes
Uninstallable           = yes
WizardImageFile         = {#AppRootDir}\installer\resources\innosetup-wizard-large.bmp
WizardSmallImageFile    = {#AppRootDir}\installer\resources\innosetup-wizard-small.bmp

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"

[Types]
Name: "full";   Description: "Full installation"
Name: "custom"; Description: "Custom installation"; Flags: iscustom

[Components]
Name: "{#AppNameUnderscore}";                           Description: "{#AppName}";                          Types: full custom;
Name: "{#AppNameUnderscore}/standalone_64";             Description: "Standalone (64-bit)";                 Types: full custom; Check: IsWin64;
Name: "{#AppNameUnderscore}/vst2_64";                   Description: "VST2 (64-bit)";                       Types: full custom; Check: IsWin64;
Name: "{#AppNameUnderscore}/vst3_64";                   Description: "VST3 (64-bit)";                       Types: full custom; Check: IsWin64;
Name: "{#AppNameUnderscore}_required";                  Description: "{#AppName} - Required Components";    Types: full custom; Flags: fixed;
Name: "{#AppNameUnderscore}_required/licenses";         Description: "Licenses";                            Types: full custom; Flags: fixed;
Name: "{#AppNameUnderscore}_required/factorypresets";   Description: "Factory Presets";                     Types: full custom; Flags: fixed;

[Files]
Source: "{#AppBuildDir}\Release\Standalone Plugin\{#AppName}.exe";    DestDir: "{pf64}\{#AppName}"; DestName: "{#AppName}.exe"; Components: {#AppNameUnderscore}/standalone_64; Flags: ignoreversion overwritereadonly uninsremovereadonly;

Source: "{#AppBuildDir}\Release\VST\{#AppName}.dll";      DestDir: "{pf64}\Steinberg\VstPlugins"; DestName: "{#AppName}.dll"; Components: {#AppNameUnderscore}/vst2_64; Flags: ignoreversion overwritereadonly uninsremovereadonly;

Source: "{#AppBuildDir}\Release\VST3\{#AppName}.vst3";     DestDir: "{cf64}\VST3"; DestName: "{#AppName}.vst3"; Components: {#AppNameUnderscore}/vst3_64; Flags: ignoreversion overwritereadonly uninsremovereadonly;

Source: "{#AppRootDir}\LICENSE.txt";                DestDir: "{app}\licenses";              DestName: "LICENSE.txt"; Components: {#AppNameUnderscore}_required/licenses; Flags: ignoreversion overwritereadonly uninsremovereadonly;
Source: "{#AppRootDir}\sdks\frut\LICENSE";          DestDir: "{app}\licenses\frut";         DestName: "LICENSE.txt"; Components: {#AppNameUnderscore}_required/licenses; Flags: ignoreversion overwritereadonly uninsremovereadonly;
Source: "{#AppRootDir}\sdks\grape\LICENSE";         DestDir: "{app}\licenses\grape";        DestName: "LICENSE.txt"; Components: {#AppNameUnderscore}_required/licenses; Flags: ignoreversion overwritereadonly uninsremovereadonly;
Source: "{#AppRootDir}\sdks\juce\LICENSE.md";       DestDir: "{app}\licenses\juce";         DestName: "LICENSE.txt"; Components: {#AppNameUnderscore}_required/licenses; Flags: ignoreversion overwritereadonly uninsremovereadonly;
Source: "{#AppRootDir}\sdks\pluginval\LICENSE";     DestDir: "{app}\licenses\pluginval";    DestName: "LICENSE.txt"; Components: {#AppNameUnderscore}_required/licenses; Flags: ignoreversion overwritereadonly uninsremovereadonly;
Source: "{#AppRootDir}\sdks\vst\LICENSE.txt";       DestDir: "{app}\licenses\vst";          DestName: "LICENSE.txt"; Components: {#AppNameUnderscore}_required/licenses; Flags: ignoreversion overwritereadonly uninsremovereadonly;

Source: "{#AppRootDir}\installer\presets\*";        DestDir: "{app}\presets"; Components: {#AppNameUnderscore}_required/factorypresets; Flags: ignoreversion createallsubdirs recursesubdirs overwritereadonly uninsremovereadonly skipifsourcedoesntexist;

[Icons]
Name: "{group}\{#AppName} (64-bit)";    Filename: "{pf64}\{#AppName}\{#AppName}.exe";
Name: "{group}\Uninstall";              Filename: "{uninstallexe}"

