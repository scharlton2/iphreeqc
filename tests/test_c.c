#include <stdlib.h>
#include <IPhreeqc.h>

typedef int (*getFunc)(int);
typedef IPQ_RESULT (*setFunc)(int, int);
int TestGetSet(int, getFunc, setFunc);

int
main(int argc, const char* argv[])
{
  int id;
  int r, c;
  VAR v;

  id = CreateIPhreeqc();
  if (id < 0)
  {
    return EXIT_FAILURE;
  }

  /* Dump */
  if (TestGetSet(id, GetDumpOn, SetDumpOn))
  {
    return EXIT_FAILURE;
  }

  /* Dump string */
  if (TestGetSet(id, GetDumpStringOn, SetDumpStringOn))
  {
    return EXIT_FAILURE;
  }

  /* Error */
  if (TestGetSet(id, GetErrorOn, SetErrorOn))
  {
    return EXIT_FAILURE;
  }

  /* Log */
  if (TestGetSet(id, GetLogOn, SetLogOn))
  {
    return EXIT_FAILURE;
  }

  /* Output */
  if (TestGetSet(id, GetOutputOn, SetOutputOn))
  {
    return EXIT_FAILURE;
  }

  /* Selected output */
  if (TestGetSet(id, GetSelectedOutputOn, SetSelectedOutputOn))
  {
    return EXIT_FAILURE;
  }

  if (LoadDatabase(id, "phreeqc.dat") != 0)
  {
    OutputError(id);
    return EXIT_FAILURE;
  }

  if (RunFile(id, "ex2") != 0)
  {
    OutputError(id);
    return EXIT_FAILURE;
  }

  for (r = 0; r < GetSelectedOutputRowCount(id); ++r)
  {
    for (c = 0; c < GetSelectedOutputColumnCount(id); ++c)
    {
      if (GetSelectedOutputValue(id, r, c, &v) != IPQ_OK)
      {
        return EXIT_FAILURE;
      }
      VarClear(&v);
    }
  }
  
  if (DestroyIPhreeqc(id) != IPQ_OK)
  {
    OutputError(id);
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

int 
TestGetSet(int id, getFunc gf, setFunc sf)
{
  if (gf(id))
  {  
    return EXIT_FAILURE;
  }
  
  if (sf(id, 1) != IPQ_OK)
  {
    return EXIT_FAILURE;
  }
  
  if (!gf(id))
  {
    return EXIT_FAILURE;
  }
  
  if (sf(id,0) != IPQ_OK)
  {
    return EXIT_FAILURE;
  }
  
  return EXIT_SUCCESS;
}
