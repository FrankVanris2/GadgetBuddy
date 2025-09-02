/**
 * @file ErrorReportingInterface.h
 * @author Frank Vanris
 * @date 8/1/2025
 * @brief Interface for error reporting in the GadgetBuddy project.
 *
 * This abstract class defines the required methods for error reporting,
 * enabling consistent error handling across all modules in GadgetBuddy.
 */

#ifndef ERROR_REPORTING_INTERFACE_H
#define ERROR_REPORTING_INTERFACE_H

/**
 * @class ErrorReportingInterface
 * @brief Abstract interface for error reporting functionality.
 */
class ErrorReportingInterface {
public:
    /**
     * @brief Virtual destructor.
     */
    virtual ~ErrorReportingInterface() = default;

    /**
     * @brief Get the latest error message.
     * @return Error message string.
     */
    virtual const char* getErrorMessage() = 0;

    /**
     * @brief Check if the module is currently in an error state.
     * @return True if error present, false otherwise.
     */
    virtual bool hasError() = 0;

    /**
     * @brief Clear the current error state.
     */
    virtual void clearError() = 0;
};

#endif