#ifndef __FWRAP__H
#define __FWRAP__H

#if defined(_WINDLL)
#define IPQ_DLL_EXPORT __declspec(dllexport)
#else
#define IPQ_DLL_EXPORT
#endif

#if defined(FC_FUNC)
#define AccumulateLineF                   FC_FUNC (accumulatelinef,                   ACCUMULATELINEF)
#define AddErrorF                         FC_FUNC (adderrorf,                         ADDERRORF)
#define AddWarningF                       FC_FUNC (addwarningf,                       ADDWARNINGF)
#define ClearAccumulatedLinesF            FC_FUNC (clearaccumulatedlinesf,            CLEARACCUMULATEDLINESF)
#define CreateIPhreeqcF                   FC_FUNC (createiphreeqcf,                   CREATEIPHREEQCF)
#define DestroyIPhreeqcF                  FC_FUNC (destroyiphreeqcf,                  DESTROYIPHREEQCF)
#define GetComponentCountF                FC_FUNC (getcomponentcountf,                GETCOMPONENTCOUNTF)
#define GetComponentF                     FC_FUNC (getcomponentf,                     GETCOMPONENTF)
#define GetDumpFileNameF                  FC_FUNC (getdumpfilenamef,                  GETDUMPFILENAMEF)
#define GetDumpFileOnF                    FC_FUNC (getdumpfileonf,                    GETDUMPFILEONF)
#define GetDumpStringLineCountF           FC_FUNC (getdumpstringlinecountf,           GETDUMPSTRINGLINECOUNTF)
#define GetDumpStringLineF                FC_FUNC (getdumpstringlinef,                GETDUMPSTRINGLINEF)
#define GetDumpStringOnF                  FC_FUNC (getdumpstringonf,                  GETDUMPSTRINGONF)
#define GetErrorFileNameF                 FC_FUNC (geterrorfilenamef,                 GETERRORFILENAMEF)
#define GetErrorFileOnF                   FC_FUNC (geterrorfileonf,                   GETERRORFILEONF)
#define GetErrorStringLineCountF          FC_FUNC (geterrorstringlinecountf,          GETERRORSTRINGLINECOUNTF)
#define GetErrorStringLineF               FC_FUNC (geterrorstringlinef,               GETERRORSTRINGLINEF)
#define GetErrorStringOnF                 FC_FUNC (geterrorstringonf,                 GETERRORSTRINGONF)
#define GetLogFileNameF                   FC_FUNC (getlogfilenamef,                   GETLOGFILENAMEF)
#define GetLogFileOnF                     FC_FUNC (getlogfileonf,                     GETLOGFILEONF)
#define GetLogStringLineCountF            FC_FUNC (getlogstringlinecountf,            GETLOGSTRINGLINECOUNTF)
#define GetLogStringLineF                 FC_FUNC (getlogstringlinef,                 GETLOGSTRINGLINEF)
#define GetLogStringOnF                   FC_FUNC (getlogstringonf,                   GETLOGSTRINGONF)
#define GetOutputFileNameF                FC_FUNC (getoutputfilenamef,                GETOUTPUTFILENAMEF)
#define GetOutputFileOnF                  FC_FUNC (getoutputfileonf,                  GETOUTPUTFILEONF)
#define GetOutputStringLineCountF         FC_FUNC (getoutputstringlinecountf,         GETOUTPUTSTRINGLINECOUNTF)
#define GetOutputStringLineF              FC_FUNC (getoutputstringlinef,              GETOUTPUTSTRINGLINEF)
#define GetOutputStringOnF                FC_FUNC (getoutputstringonf,                GETOUTPUTSTRINGONF)
#define GetSelectedOutputColumnCountF     FC_FUNC (getselectedoutputcolumncountf,     GETSELECTEDOUTPUTCOLUMNCOUNTF)
#define GetSelectedOutputFileNameF        FC_FUNC (getselectedoutputfilenamef,        GETSELECTEDOUTPUTFILENAMEF)
#define GetSelectedOutputFileOnF          FC_FUNC (getselectedoutputfileonf,          GETSELECTEDOUTPUTFILEONF)
#define GetSelectedOutputRowCountF        FC_FUNC (getselectedoutputrowcountf,        GETSELECTEDOUTPUTROWCOUNTF)
#define GetSelectedOutputStringLineCountF FC_FUNC (getselectedoutputstringlinecountf, GETSELECTEDOUTPUTSTRINGLINECOUNTF)
#define GetSelectedOutputStringLineF      FC_FUNC (getselectedoutputstringlinef,      GETSELECTEDOUTPUTSTRINGLINEF)
#define GetSelectedOutputStringOnF        FC_FUNC (getselectedoutputstringonf,        GETSELECTEDOUTPUTSTRINGONF)
#define GetSelectedOutputValueF           FC_FUNC (getselectedoutputvaluef,           GETSELECTEDOUTPUTVALUEF)
#define GetWarningStringLineCountF        FC_FUNC (getwarningstringlinecountf,        GETWARNINGSTRINGLINECOUNTF)
#define GetWarningStringLineF             FC_FUNC (getwarningstringlinef,             GETWARNINGSTRINGLINEF)
#define LoadDatabaseF                     FC_FUNC (loaddatabasef,                     LOADDATABASEF)
#define LoadDatabaseStringF               FC_FUNC (loaddatabasestringf,               LOADDATABASESTRINGF)
#define OutputAccumulatedLinesF           FC_FUNC (outputaccumulatedlinesf,           OUTPUTACCUMULATEDLINESF)
#define OutputErrorStringF                FC_FUNC (outputerrorstringf,                OUTPUTERRORSTRINGF)
#define OutputWarningStringF              FC_FUNC (outputwarningstringf,              OUTPUTWARNINGSTRINGF)
#define RunAccumulatedF                   FC_FUNC (runaccumulatedf,                   RUNACCUMULATEDF)
#define RunFileF                          FC_FUNC (runfilef,                          RUNFILEF)
#define RunStringF                        FC_FUNC (runstringf,                        RUNSTRINGF)
#define SetDumpFileNameF                  FC_FUNC (setdumpfilenamef,                  SETDUMPFILENAMEF)
#define SetDumpFileOnF                    FC_FUNC (setdumpfileonf,                    SETDUMPFILEONF)
#define SetDumpStringOnF                  FC_FUNC (setdumpstringonf,                  SETDUMPSTRINGONF)
#define SetErrorFileNameF                 FC_FUNC (seterrorfilenamef,                 SETERRORFILENAMEF)
#define SetErrorFileOnF                   FC_FUNC (seterrorfileonf,                   SETERRORFILEONF)
#define SetErrorStringOnF                 FC_FUNC (seterrorstringonf,                 SETERRORSTRINGONF)
#define SetLogFileNameF                   FC_FUNC (setlogfilenamef,                   SETLOGFILENAMEF)
#define SetLogFileOnF                     FC_FUNC (setlogfileonf,                     SETLOGFILEONF)
#define SetLogStringOnF                   FC_FUNC (setlogstringonf,                   SETLOGSTRINGONF)
#define SetOutputFileNameF                FC_FUNC (setoutputfilenamef,                SETOUTPUTFILENAMEF)
#define SetOutputFileOnF                  FC_FUNC (setoutputfileonf,                  SETOUTPUTFILEONF)
#define SetOutputStringOnF                FC_FUNC (setoutputstringonf,                SETOUTPUTSTRINGONF)
#define SetSelectedOutputFileNameF        FC_FUNC (setselectedoutputfilenamef,        SETSELECTEDOUTPUTFILENAMEF)
#define SetSelectedOutputFileOnF          FC_FUNC (setselectedoutputfileonf,          SETSELECTEDOUTPUTFILEONF)
#define SetSelectedOutputStringOnF        FC_FUNC (setselectedoutputstringonf,        SETSELECTEDOUTPUTSTRINGONF)
#endif /* FC_FUNC */

#if defined(__cplusplus)
extern "C" {
#endif

  IPQ_RESULT AccumulateLineF(int *id, char *line, unsigned int line_length);
  int        AddErrorF(int *id, char *error_msg, unsigned int len);
  int        AddWarningF(int *id, char *warn_msg, unsigned int len);
  IPQ_RESULT ClearAccumulatedLinesF(int *id);
  int        CreateIPhreeqcF(void);
  int        DestroyIPhreeqcF(int *id);
  int        GetComponentCountF(int *id);
  void       GetComponentF(int *id, int* n, char* line, unsigned int line_length);
  void       GetDumpFileNameF(int *id, char* filename, unsigned int filename_length);
  int        GetDumpFileOnF(int *id);
  int        GetDumpStringLineCountF(int *id);
  void       GetDumpStringLineF(int *id, int* n, char* line, unsigned int line_length);
  int        GetDumpStringOnF(int *id);
  void       GetErrorFileNameF(int *id, char* filename, unsigned int filename_length);
  int        GetErrorFileOnF(int *id);
  int        GetErrorStringLineCountF(int *id);
  void       GetErrorStringLineF(int *id, int* n, char* line, unsigned int line_length);
  int        GetErrorStringOnF(int *id);
  void       GetLogFileNameF(int *id, char* filename, unsigned int filename_length);
  int        GetLogFileOnF(int *id);
  int        GetLogStringLineCountF(int *id);
  void       GetLogStringLineF(int *id, int* n, char* line, unsigned int line_length);
  int        GetLogStringOnF(int *id);
  void       GetOutputFileNameF(int *id, char* filename, unsigned int filename_length);
  int        GetOutputFileOnF(int *id);
  int        GetOutputStringLineCountF(int *id);
  void       GetOutputStringLineF(int *id, int* n, char* line, unsigned int line_length);
  int        GetOutputStringOnF(int *id);
  int        GetSelectedOutputColumnCountF(int *id);
  void       GetSelectedOutputFileNameF(int *id, char* filename, unsigned int filename_length);
  int        GetSelectedOutputFileOnF(int *id);
  int        GetSelectedOutputRowCountF(int *id);
  int        GetSelectedOutputStringLineCountF(int *id);
  void       GetSelectedOutputStringLineF(int *id, int* n, char* line, unsigned int line_length);
  int        GetSelectedOutputStringOnF(int *id);
  IPQ_RESULT GetSelectedOutputValueF(int *id, int *row, int *col, int *vtype, double* dvalue, char* svalue, unsigned int svalue_length);
  int        GetWarningStringLineCountF(int *id);
  void       GetWarningStringLineF(int *id, int* n, char* line, unsigned int line_length);
  int        LoadDatabaseF(int *id, char* filename, unsigned int filename_length);
  int        LoadDatabaseStringF(int *id, char* input, unsigned int input_length);
  void       OutputAccumulatedLinesF(int *id);
  void       OutputErrorStringF(int *id);
  void       OutputWarningStringF(int *id);
  int        RunAccumulatedF(int *id);
  int        RunFileF(int *id, char* filename, unsigned int filename_length);
  int        RunStringF(int *id, char* input, unsigned int input_length);
  IPQ_RESULT SetDumpFileNameF(int *id, char* fname, unsigned int fname_length);
  IPQ_RESULT SetDumpFileOnF(int *id, int* dump_on);
  IPQ_RESULT SetDumpStringOnF(int *id, int* dump_string_on);
  IPQ_RESULT SetErrorFileNameF(int *id, char* fname, unsigned int fname_length);
  IPQ_RESULT SetErrorFileOnF(int *id, int* error_file_on);
  IPQ_RESULT SetErrorStringOnF(int *id, int* error_string_on);
  IPQ_RESULT SetLogFileNameF(int *id, char* fname, unsigned int fname_length);
  IPQ_RESULT SetLogFileOnF(int *id, int* log_file_on);
  IPQ_RESULT SetLogStringOnF(int *id, int* log_string_on);
  IPQ_RESULT SetOutputFileNameF(int *id, char* fname, unsigned int fname_length);
  IPQ_RESULT SetOutputFileOnF(int *id, int* output_on);
  IPQ_RESULT SetOutputStringOnF(int *id, int* output_string_on);
  IPQ_RESULT SetSelectedOutputFileNameF(int *id, char* fname, unsigned int fname_length);
  IPQ_RESULT SetSelectedOutputFileOnF(int *id, int* selected_output_file_on);
  IPQ_RESULT SetSelectedOutputStringOnF(int *id, int* selected_output_string_on);

#if defined(__cplusplus)
}
#endif

#endif  /* __FWRAP__H */
