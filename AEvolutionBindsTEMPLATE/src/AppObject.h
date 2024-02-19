#pragma once

#include "../../AEvolutionPlugin/src/commands.h"
#include "MessageQueueManager.h"

// Forward declaration of wProject class
class wProject;

/**
 * @brief This class represents the application interface, providing methods to interact with projects,
 *        report logs, manage UI states, and handle color settings among other functionalities.
 */
class wApp {
public:
    // Constructors and Destructor
    wApp() = default; // Use default constructor
    ~wApp() = default; // Use default destructor

    // Project management
    wProject getProject();
    wProject newProject(); // Create a new project
    wProject openFromPath(const std::string& path); // Open a project from the specified path

    // Logging and Information
    void reportInfo(const std::string& info);
    void writeToOSConsole(const std::string& text);
    void writeToDebugLog(const std::string& subsystem, const std::string& eventType, const std::string& info);

    // Driver and Plugin
    std::tuple<A_long, A_long> driverSpecVersion();
    std::string getPluginPaths(AEGP_GetPathTypes pathType);

    // UI Management
    A_Boolean getSuppressInteractiveUI();
    void startQuietErrors();
    void endQuietErrors(bool reportQuietedErrors);
    void startUndoGroup(const std::string& undoName);
    void endUndoGroup();
    void showHideAllFloaters(bool includeToolPal);

    // Font and Color Management
    void updateFontList();
    AEGP_ColorVal paintPalGetForeColor();
    void paintPalSetForeColor(AEGP_ColorVal foreColor);
    AEGP_ColorVal paintPalGetBackColor();
    void paintPalSetBackColor(AEGP_ColorVal backColor);
    AEGP_ColorVal charPalGetFillColor(bool is_swatch);
    void charPalSetFillColor(AEGP_ColorVal fillColor);
    AEGP_ColorVal charPalGetStrokeColor(bool is_defined);
    void charPalSetStrokeColor(AEGP_ColorVal strokeColor);
    bool charPalIsFillColorUIFrontmost();

};
