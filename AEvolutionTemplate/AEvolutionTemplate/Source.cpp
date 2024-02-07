#include "pch.h"

/*
 * Guide to Expanding the AEvolution API with Custom Bindings
 * ==========================================================
 *
 * This framework allows for the extension of the AEvolution API through custom bindings.
 * By linking to the `AEvolutionCore.lib` and including the necessary header files from the
 * 'AEvolutionCore\AEvolutionCore\include' directory, you can create custom interfaces for
 * various programming languages or frameworks.
 *
 * Getting Started:
 * ----------------
 * 1. Include the AEvolutionCore headers in your source files. This is essential for accessing
 *    the core functionalities of AEvolutionCore. For example, in your pch.h file, you would have:
 *
 *    #include "..\\..\\AEvolutionCore\\AEvolutionCore\\include\\App.h"
 *    #include "..\\..\\AEvolutionCore\\AEvolutionCore\\include\\Project.h"
 *    #include "..\\..\\AEvolutionCore\\AEvolutionCore\\include\\ItemManager.h"
 *    #include "..\\..\\AEvolutionCore\\AEvolutionCore\\include\\MessageQueue.h"
 *    #include "..\\..\\AEvolutionCore\\AEvolutionCore\\include\\UUID.hpp"
 *
 *    Ensure your project settings are configured to locate these headers correctly.
 *
 * 2. Link your project to `AEvolutionCore.lib`. This has been pre-configured in the project settings,
 *    but verify that the paths align with your project structure.
 * 
 * 3. 'AEvolutionCore.lib' is built with the C++17 standard. Ensure your project is configured to use the
 *    same standard.
 * 
 * 4. 'AEvolutionCore.lib' is already set up to communicate with the 'AEvolution.aex' plugin. This framework is simply to write bindings
 *    in other languages. For Python bindins, the translation was quite straightforward. For other languages, you may need to write
 *    additional code, or even new wrapper classes, to facilitate the communication between the AEvolutionCore and the target language.
 * 
 *
 * Writing Custom Bindings:
 * ------------------------
 * To extend the API, you will write wrappers around the core classes (e.g., App, Project) and expose
 * them through your chosen API. This involves creating function bindings that translate the C++
 * class methods to your target language or framework's method calls.
 *
 * Example Template for Python Bindings:
 *
 * For AEvolutionPy, we created 'PyCore.h' and 'PyCore.cpp' files containing the Python API bindings.
 * These files utilize pybind11 to wrap the AEvolutionCore classes and expose them as Python modules.
 * Here's a simplified structure:
 *
 * PyCore.h:
 * ---------
 * // Forward declarations and include directives for pybind11 and AEvolutionCore headers.
 *
 * PyCore.cpp:
 * -----------
 * // Implement the wrapper functions, class bindings, and module definitions using pybind11.
 *
 * source.cpp:
 * -----------
 * // Include 'PyCore.h' and utilize its binding functions to expose the AEvolutionCore functionalities
 * // as a Python module.
 *
 * Note:
 * -----
 * - Ensure your environment is set up for both C++ and the target language (e.g., Python) development.
 * - Pay close attention to memory management and type conversions, as these can be sources of errors
 *   in bindings.
 *
 * Expanding to Other APIs:
 * ------------------------
 * The process for other languages or frameworks will be similar but tailored to the specific
 * binding technology used. Always refer to the documentation for the binding technology for
 * best practices and guidance.
 *
 * Make sure to include the 'AEvolutionCore.dll' file in the same directory as your application for distribution.
 * 
 * Happy coding, and we look forward to seeing the innovative ways you extend AEvolution!
 */

void print(std::string message) {
	App app;
	app.reportInfo(message);
}