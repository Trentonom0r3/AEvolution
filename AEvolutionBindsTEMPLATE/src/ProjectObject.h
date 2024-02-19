#pragma once

#include "../../AEvolutionPlugin/src/commands.h"
#include "MessageQueueManager.h"
#include <memory> // Include for std::unique_ptr
#include <string> // Include for std::string

class wItem; // Forward declaration for wItem
class wFolder; // Forward declaration for wFolder

/**
 * @brief Represents a project, encapsulating operations such as saving, opening, and managing project properties.
 */
class wProject {
public:
    // Constructors
    wProject(); // Default constructor
    explicit wProject(AE_Project project) : project(project) {} // Initialize with AE_Project
    explicit wProject(const std::string& path); // Initialize with a project path

    // Destructor
    ~wProject() = default; // Default destructor

    // Project properties and management
    std::string projectName(); // Get the name of the project
    std::string projectPath(); // Get the path of the project
    std::unique_ptr<wItem> activeItem(); // Get the currently active item in the project
    wFolder rootFolder(); // Get the root folder of the project

    // Project operations
    void saveToPath(const std::string& path); // Save the project to the specified path
    void saveAs(const std::string& path); // Save the project to a new location

    // Time and Bit Depth settings
    AEGP_TimeDisplay3 timeDisplay(); // Get the current time display setting
    void setTimeDisplay(AEGP_TimeDisplay3 time_display); // Set the time display setting
    AEGP_ProjBitDepth bitDepth(); // Get the bit depth of the project
    void setBitDepth(AEGP_ProjBitDepth bit_depth); // Set the bit depth of the project

    // Status checks
    bool isDirty(); // Check if the project has unsaved changes

private:
    AE_Project project; // Internal representation of a project
};
