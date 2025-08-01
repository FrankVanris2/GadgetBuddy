/**
 * By: Frank Vanris
 * Date: 8/1/2025
 * Desc: Creating an error reporting interface for the GadgetBuddy project
*/

#ifndef ERROR_REPORTING_INTERFACE_H
#define ERROR_REPORTING_INTERFACE_H

class ErrorReportingInterface {
public:
    virtual ~ErrorReportingInterface() = default;
    virtual const char* getErrorMessage() = 0;
    virtual bool hasError() = 0;
    virtual void clearError() = 0;
};
#endif