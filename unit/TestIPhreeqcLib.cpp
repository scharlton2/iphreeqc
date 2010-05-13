#include "TestIPhreeqcLib.h"
#include "IPhreeqc.h"
#include "CVar.hxx"

#if defined(_WIN32)
#include <windows.h>
#endif

#include <cmath>
#include <cfloat>

#if defined(_WIN32) || defined(__CYGWIN32__)
// DeleteFile defined in <windows.h>
#else
int DeleteFile(const char* szPathName);
#endif

bool FileExists(const char *szPathName);

IPQ_RESULT SOLUTION(int n, double C, double Ca, double Na);
IPQ_RESULT EQUILIBRIUM_PHASES(int n, const char* phase, double si, double amount);
IPQ_RESULT USER_PUNCH(int n, const char* element, int max);
IPQ_RESULT SELECTED_OUTPUT(int n);
IPQ_RESULT DUMP(int n);


TestIPhreeqcLib::TestIPhreeqcLib(void)
{
}

TestIPhreeqcLib::~TestIPhreeqcLib(void)
{
}

void TestIPhreeqcLib::TestCreateIPhreeqc(void)
{
	int n = ::CreateIPhreeqc();
	CPPUNIT_ASSERT(n >= 0);

	if (n >= 0)
	{
		CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::DestroyIPhreeqc(n));
	}
}

void TestIPhreeqcLib::TestDestroyIPhreeqc(void)
{
	for (int i = 0; i < 10; ++i)
	{
		CPPUNIT_ASSERT_EQUAL(IPQ_BADINSTANCE, ::DestroyIPhreeqc(i));
	}

	int n = ::CreateIPhreeqc();
	CPPUNIT_ASSERT(n >= 0);

	if (n >= 0)
	{
		CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::DestroyIPhreeqc(n));
	}
}

void TestIPhreeqcLib::TestLoadDatabase(void)
{
	int n = ::CreateIPhreeqc();
	CPPUNIT_ASSERT(n >= 0);

	for (int i = 0; i < 10; ++i)
	{
		CPPUNIT_ASSERT_EQUAL(true,   ::FileExists("phreeqc.dat"));
		CPPUNIT_ASSERT_EQUAL(0,      ::LoadDatabase(n, "phreeqc.dat"));
	}

	if (n >= 0)
	{
		CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::DestroyIPhreeqc(n));
	}
}

void TestIPhreeqcLib::TestLoadDatabaseString(void)
{
	const char ex15_dat[] =
		"SOLUTION_MASTER_SPECIES\n"
		"C        CO2            2.0     61.0173         12.0111\n"
		"Cl       Cl-            0.0     Cl              35.453\n"
		"Co       Co+2           0.0     58.93           58.93   \n"
		"E        e-             0.0     0.0             0.0\n"
		"H        H+             -1.     1.008           1.008\n"
		"H(0)     H2             0.0     1.008\n"
		"H(1)     H+             -1.     1.008\n"
		"N        NH4+           0.0     14.0067         14.0067\n"
		"Na       Na+            0.0     Na              22.9898\n"
		"Nta      Nta-3          3.0     1.              1.\n"
		"O        H2O            0.0     16.00           16.00\n"
		"O(-2)    H2O            0.0     18.016\n"
		"O(0)     O2             0.0     16.00\n"
		"SOLUTION_SPECIES\n"
		"2H2O = O2 + 4H+ + 4e- \n"
		"        log_k   -86.08; -gamma  1e7   0.0\n"
		"2 H+ + 2 e- = H2\n"
		"        log_k   -3.15;  -gamma  1e7   0.0\n"
		"H+ = H+\n"
		"        log_k   0.0;    -gamma  1e7   0.0\n"
		"e- = e-\n"
		"        log_k   0.0;    -gamma  1e7   0.0\n"
		"H2O = H2O\n"
		"        log_k   0.0;    -gamma  1e7   0.0\n"
		"CO2 = CO2\n"
		"        log_k   0.0;    -gamma  1e7   0.0\n"
		"Na+ = Na+\n"
		"        log_k   0.0;    -gamma  1e7   0.0\n"
		"Cl- = Cl-\n"
		"        log_k   0.0;    -gamma  1e7   0.0\n"
		"Co+2 = Co+2\n"
		"        log_k   0.0;    -gamma  1e7   0.0\n"
		"NH4+ = NH4+\n"
		"        log_k   0.0;    -gamma  1e7   0.0\n"
		"Nta-3 = Nta-3\n"
		"        log_k   0.0;    -gamma  1e7   0.0\n"
		"Nta-3 + 3H+ = H3Nta\n"
		"        log_k   14.9;   -gamma  1e7   0.0\n"
		"Nta-3 + 2H+ = H2Nta-\n"
		"        log_k   13.3;   -gamma  1e7   0.0\n"
		"Nta-3 + H+ = HNta-2\n"
		"        log_k   10.3;   -gamma  1e7   0.0\n"
		"Nta-3 + Co+2 = CoNta-\n"
		"        log_k   11.7;   -gamma  1e7   0.0\n"
		"2 Nta-3 + Co+2 = CoNta2-4\n"
		"        log_k   14.5;   -gamma  1e7   0.0\n"
		"Nta-3 + Co+2 + H2O = CoOHNta-2 + H+\n"
		"        log_k   0.5;    -gamma  1e7   0.0\n"
		"Co+2 + H2O = CoOH+ + H+\n"
		"        log_k   -9.7;   -gamma  1e7   0.0\n"
		"Co+2 + 2H2O = Co(OH)2 + 2H+\n"
		"        log_k   -22.9;  -gamma  1e7   0.0\n"
		"Co+2 + 3H2O = Co(OH)3- + 3H+\n"
		"        log_k   -31.5;  -gamma  1e7   0.0\n"
		"CO2 + H2O = HCO3- + H+\n"
		"        log_k   -6.35;  -gamma  1e7   0.0\n"
		"CO2 + H2O = CO3-2 + 2H+\n"
		"        log_k   -16.68; -gamma  1e7   0.0\n"
		"NH4+ = NH3 + H+\n"
		"        log_k   -9.3;   -gamma  1e7   0.0\n"
		"H2O = OH- +  H+\n"
		"        log_k   -14.0;  -gamma  1e7   0.0\n"
		"END\n";

	int n = ::CreateIPhreeqc();
	CPPUNIT_ASSERT(n >= 0);

	for (int i = 0; i < 10; ++i)
	{
		CPPUNIT_ASSERT_EQUAL(0,      ::LoadDatabaseString(n, ex15_dat));
	}

	if (n >= 0)
	{
		CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::DestroyIPhreeqc(n));
	}
}

void TestIPhreeqcLib::TestLoadDatabaseMissingFile(void)
{
	CPPUNIT_ASSERT_EQUAL(false, ::FileExists("missing.file"));

	int n = ::CreateIPhreeqc();
	CPPUNIT_ASSERT(n >= 0);

	for (int i = 0; i < 10; ++i)
	{
		CPPUNIT_ASSERT_EQUAL(1, ::LoadDatabase(n, "missing.file"));
	}

	const char expected[] =
		"ERROR: LoadDatabase: Unable to open:\"missing.file\".\n";

	const char* err = ::GetErrorString(n);

	CPPUNIT_ASSERT_EQUAL( std::string(expected), std::string(err) );

	if (n >= 0)
	{
		CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::DestroyIPhreeqc(n));
	}
}

void TestIPhreeqcLib::TestLoadDatabaseWithErrors(void)
{
	CPPUNIT_ASSERT_EQUAL(true, ::FileExists("missing_e.dat"));

	int n = ::CreateIPhreeqc();
	CPPUNIT_ASSERT(n >= 0);

	for (int i = 0; i < 10; ++i)
	{
		CPPUNIT_ASSERT_EQUAL(true, ::FileExists("missing_e.dat"));
		CPPUNIT_ASSERT_EQUAL(6,    ::LoadDatabase(n, "missing_e.dat"));

		static const char *expected =
			"ERROR: Could not reduce equation to primary master species, CH4.\n"
			"ERROR: Could not reduce equation to primary master species, Cu+.\n"
			"ERROR: Could not reduce equation to primary master species, Fe+3.\n"
			"ERROR: Could not reduce equation to primary master species, H2.\n"
			"ERROR: Could not reduce equation to primary master species, Mn+3.\n"
			"ERROR: Could not reduce equation to primary master species, NH4+.\n"
			"ERROR: Could not reduce equation to primary master species, N2.\n"
			"ERROR: Could not reduce equation to primary master species, NO2-.\n"
			"ERROR: Could not reduce equation to primary master species, O2.\n"
			"ERROR: Could not reduce equation to primary master species, HS-.\n"
			"ERROR: Could not reduce equation to secondary master species, e-.\n"
			"ERROR: Non-master species in secondary reaction, e-.\n"
			"ERROR: No master species for element e.\n"
			"ERROR: Could not find primary master species for e.\n"
			"ERROR: No master species for element e.\n"
			"ERROR: Could not reduce equation to secondary master species, Hausmannite.\n"
			"ERROR: Could not reduce equation to secondary master species, Manganite.\n"
			"ERROR: Could not reduce equation to secondary master species, Pyrite.\n"
			"ERROR: Could not reduce equation to secondary master species, Pyrolusite.\n"
			"ERROR: Could not reduce equation to secondary master species, Sulfur.\n"
			"ERROR: e-, primary master species for E-, not defined.\n"
			"ERROR: Calculations terminating due to input errors.\n";

		const char* err = ::GetErrorString(n);

		CPPUNIT_ASSERT_EQUAL( std::string(expected), std::string(err) );
	}

	if (n >= 0)
	{
		CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::DestroyIPhreeqc(n));
	}
}

void TestIPhreeqcLib::TestRunAccumulated(void)
{
	int n = ::CreateIPhreeqc();
	CPPUNIT_ASSERT(n >= 0);

	CPPUNIT_ASSERT_EQUAL(0,      ::LoadDatabase(n, "phreeqc.dat"));
	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::AccumulateLine(n, "solution 12"));
	CPPUNIT_ASSERT_EQUAL(0,      ::GetOutputOn(n));
	CPPUNIT_ASSERT_EQUAL(0,      ::GetErrorOn(n));
	CPPUNIT_ASSERT_EQUAL(0,      ::GetLogOn(n));
	CPPUNIT_ASSERT_EQUAL(0,      ::GetSelectedOutputOn(n));
	CPPUNIT_ASSERT_EQUAL(0,      ::GetDumpOn(n));
	CPPUNIT_ASSERT_EQUAL(0,      ::GetDumpStringOn(n));
	CPPUNIT_ASSERT_EQUAL(0,      ::RunAccumulated(n));

	if (n >= 0)
	{
		CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::DestroyIPhreeqc(n));
	}
}

void TestIPhreeqcLib::TestRunWithErrors()
{
	const char dump_file[] = "error.inp";

	// remove dump file if it exists
	//
	if (::FileExists(dump_file))
	{
		CPPUNIT_ASSERT(::DeleteFile(dump_file));
	}

	int n = ::CreateIPhreeqc();
	CPPUNIT_ASSERT(n >= 0);

	CPPUNIT_ASSERT_EQUAL(0,      ::LoadDatabase(n, "phreeqc.dat"));
	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::AccumulateLine(n, "SOLUTION 1"));
	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::AccumulateLine(n, "	pH	7"));
	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::AccumulateLine(n, "	Na	1"));
	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::AccumulateLine(n, "PHASES"));
	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::AccumulateLine(n, "	Fix_H+"));
	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::AccumulateLine(n, "	H+ = H+"));
	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::AccumulateLine(n, "	log_k	0"));
	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::AccumulateLine(n, "EQUILIBRIUM_PHASES"));
	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::AccumulateLine(n, "	Fix_H+ -10 HCl	10"));
	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::AccumulateLine(n, "END"));
	CPPUNIT_ASSERT_EQUAL(0,      ::GetOutputOn(n));
	CPPUNIT_ASSERT_EQUAL(0,      ::GetErrorOn(n));
	CPPUNIT_ASSERT_EQUAL(0,      ::GetLogOn(n));
	CPPUNIT_ASSERT_EQUAL(0,      ::GetSelectedOutputOn(n));
	CPPUNIT_ASSERT_EQUAL(0,      ::GetDumpOn(n));
	CPPUNIT_ASSERT_EQUAL(0,      ::GetDumpStringOn(n));
	CPPUNIT_ASSERT_EQUAL(1,      ::RunAccumulated(n));

	const char expected[] =
		"ERROR: Numerical method failed on all combinations of convergence parameters\n";
	const char* err = ::GetErrorString(n);

	CPPUNIT_ASSERT_EQUAL( std::string(expected), std::string(err) );

	if (n >= 0)
	{
		CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::DestroyIPhreeqc(n));
	}

	CPPUNIT_ASSERT_EQUAL(true, ::FileExists(dump_file) );
	CPPUNIT_ASSERT(::DeleteFile(dump_file));
}

void TestIPhreeqcLib::TestRunFile(void)
{
	static const char dump_file[] = "error.inp";

	// remove dump file if it exists
	//
	if (::FileExists(dump_file))
	{
		CPPUNIT_ASSERT(::DeleteFile(dump_file));
	}

	int n = ::CreateIPhreeqc();
	CPPUNIT_ASSERT(n >= 0);

	CPPUNIT_ASSERT_EQUAL(true, ::FileExists("phreeqc.dat"));
	CPPUNIT_ASSERT_EQUAL(0,    ::LoadDatabase(n, "phreeqc.dat"));
	CPPUNIT_ASSERT_EQUAL(0,    ::GetOutputOn(n));
	CPPUNIT_ASSERT_EQUAL(0,    ::GetErrorOn(n));
	CPPUNIT_ASSERT_EQUAL(0,    ::GetLogOn(n));
	CPPUNIT_ASSERT_EQUAL(0,    ::GetSelectedOutputOn(n));
	CPPUNIT_ASSERT_EQUAL(0,    ::GetDumpOn(n));
	CPPUNIT_ASSERT_EQUAL(0,    ::GetDumpStringOn(n));
	CPPUNIT_ASSERT_EQUAL(true, ::FileExists("conv_fail.in"));
	CPPUNIT_ASSERT_EQUAL(1,    ::RunFile(n, "conv_fail.in"));

	static const char expected[] =
		"ERROR: Numerical method failed on all combinations of convergence parameters\n";
	const char* err = ::GetErrorString(n);

	CPPUNIT_ASSERT_EQUAL(std::string(expected), std::string(err));

	if (n >= 0)
	{
		CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::DestroyIPhreeqc(n));
	}

	// Note: should this file exist since GetDumpOn is false?
	CPPUNIT_ASSERT_EQUAL(true, ::FileExists(dump_file));
	CPPUNIT_ASSERT(::DeleteFile(dump_file));
}

void TestIPhreeqcLib::TestRunString(void)
{
	const char input[] =
		"TITLE Example 1.--Add uranium and speciate seawater.\n"
		"SOLUTION 1  SEAWATER FROM NORDSTROM ET AL. (1979)\n"
		"        units   ppm\n"
		"        pH      8.22\n"
		"        pe      8.451\n"
		"        density 1.023\n"
		"        temp    25.0\n"
		"        redox   O(0)/O(-2)\n"
		"        Ca              412.3\n"
		"        Mg              1291.8\n"
		"        Na              10768.0\n"
		"        K               399.1\n"
		"        Fe              0.002\n"
		"        Mn              0.0002  pe\n"
		"        Si              4.28\n"
		"        Cl              19353.0\n"
		"        Alkalinity      141.682 as HCO3\n"
		"        S(6)            2712.0\n"
		"        N(5)            0.29    gfw   62.0\n"
		"        N(-3)           0.03    as    NH4\n"
		"        U               3.3     ppb   N(5)/N(-3)\n"
		"        O(0)            1.0     O2(g) -0.7\n"
		"SOLUTION_MASTER_SPECIES\n"
		"        U       U+4     0.0     238.0290     238.0290\n"
		"        U(4)    U+4     0.0     238.0290\n"
		"        U(5)    UO2+    0.0     238.0290\n"
		"        U(6)    UO2+2   0.0     238.0290\n"
		"SOLUTION_SPECIES\n"
		"        #primary master species for U\n"
		"        #is also secondary master species for U(4)\n"
		"        U+4 = U+4\n"
		"                log_k          0.0\n"
		"        U+4 + 4 H2O = U(OH)4 + 4 H+\n"
		"                log_k          -8.538\n"
		"                delta_h        24.760 kcal\n"
		"        U+4 + 5 H2O = U(OH)5- + 5 H+\n"
		"                log_k          -13.147\n"
		"                delta_h        27.580 kcal\n"
		"        #secondary master species for U(5)\n"
		"        U+4 + 2 H2O = UO2+ + 4 H+ + e-\n"
		"                log_k          -6.432\n"
		"                delta_h        31.130 kcal\n"
		"        #secondary master species for U(6)\n"
		"        U+4 + 2 H2O = UO2+2 + 4 H+ + 2 e-\n"
		"                log_k          -9.217\n"
		"                delta_h        34.430 kcal\n"
		"        UO2+2 + H2O = UO2OH+ + H+\n"
		"                log_k          -5.782\n"
		"                delta_h        11.015 kcal\n"
		"        2UO2+2 + 2H2O = (UO2)2(OH)2+2 + 2H+\n"
		"                log_k          -5.626\n"
		"                delta_h        -36.04 kcal\n"
		"        3UO2+2 + 5H2O = (UO2)3(OH)5+ + 5H+\n"
		"                log_k          -15.641\n"
		"                delta_h        -44.27 kcal\n"
		"        UO2+2 + CO3-2 = UO2CO3\n"
		"                log_k          10.064\n"
		"                delta_h        0.84 kcal\n"
		"        UO2+2 + 2CO3-2 = UO2(CO3)2-2\n"
		"                log_k          16.977\n"
		"                delta_h        3.48 kcal\n"
		"        UO2+2 + 3CO3-2 = UO2(CO3)3-4\n"
		"                log_k          21.397\n"
		"                delta_h        -8.78 kcal\n"
		"PHASES\n"
		"        Uraninite\n"
		"        UO2 + 4 H+ = U+4 + 2 H2O\n"
		"        log_k          -3.490\n"
		"        delta_h        -18.630 kcal\n"
		"END\n"
		"\n";

	if (::FileExists("phreeqc.out"))
	{
		CPPUNIT_ASSERT(::DeleteFile("phreeqc.out"));
	}
	CPPUNIT_ASSERT_EQUAL(false, ::FileExists("phreeqc.out"));
	int n = ::CreateIPhreeqc();
	CPPUNIT_ASSERT(n >= 0);
	CPPUNIT_ASSERT_EQUAL(0, ::LoadDatabase(n, "phreeqc.dat"));
	::SetOutputOn(n, 1);
	::SetErrorOn(n, 0);
	::SetLogOn(n, 0);
	::SetSelectedOutputOn(n, 0);
	::SetDumpOn(n, 0);
	CPPUNIT_ASSERT_EQUAL(false, ::FileExists("phreeqc.out"));
	CPPUNIT_ASSERT_EQUAL(0,     ::RunString(n, input));
	CPPUNIT_ASSERT_EQUAL(true,  ::FileExists("phreeqc.out"));
	if (n >= 0)
	{
		CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::DestroyIPhreeqc(n));
	}
	if (::FileExists("phreeqc.out"))
	{
		CPPUNIT_ASSERT(::DeleteFile("phreeqc.out"));
	}
}

void TestIPhreeqcLib::TestGetSelectedOutputRowCount()
{
	int n = ::CreateIPhreeqc();
	CPPUNIT_ASSERT(n >= 0);

	CPPUNIT_ASSERT_EQUAL(true,   ::FileExists("llnl.dat"));
	CPPUNIT_ASSERT_EQUAL(0,      ::LoadDatabase(n, "llnl.dat"));

	int max = 6;

	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::SOLUTION(n, 1.0, 1.0, 1.0));
	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::EQUILIBRIUM_PHASES(n, "calcite", 0.0, 0.010));
	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::USER_PUNCH(n, "Ca", max));
	CPPUNIT_ASSERT_EQUAL(0,      ::GetOutputOn(n));
	CPPUNIT_ASSERT_EQUAL(0,      ::GetErrorOn(n));
	CPPUNIT_ASSERT_EQUAL(0,      ::GetLogOn(n));
	CPPUNIT_ASSERT_EQUAL(0,      ::GetSelectedOutputOn(n));
	CPPUNIT_ASSERT_EQUAL(0,      ::GetDumpOn(n));
	CPPUNIT_ASSERT_EQUAL(0,      ::GetDumpStringOn(n));
	CPPUNIT_ASSERT_EQUAL(0,      ::RunAccumulated(n));
	CPPUNIT_ASSERT_EQUAL(3,      ::GetSelectedOutputRowCount(n)); // rows + header

	if (n >= 0)
	{
		CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::DestroyIPhreeqc(n));
	}
}
#define USE_VAR
void TestIPhreeqcLib::TestGetSelectedOutputValue(void)
{
	int n = ::CreateIPhreeqc();
	CPPUNIT_ASSERT(n >= 0);

	CPPUNIT_ASSERT_EQUAL(0, ::LoadDatabase(n, "llnl.dat"));

	int max = 6;

	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::SOLUTION(n, 1.0, 1.0, 1.0));
	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::EQUILIBRIUM_PHASES(n, "calcite", 0.0, 0.010));
	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::USER_PUNCH(n, "Ca", max));
	CPPUNIT_ASSERT_EQUAL(0,      ::GetOutputOn(n));
	CPPUNIT_ASSERT_EQUAL(0,      ::GetErrorOn(n));
	CPPUNIT_ASSERT_EQUAL(0,      ::GetLogOn(n));
	CPPUNIT_ASSERT_EQUAL(0,      ::GetSelectedOutputOn(n));
	CPPUNIT_ASSERT_EQUAL(0,      ::GetDumpOn(n));
	CPPUNIT_ASSERT_EQUAL(0,      ::GetDumpStringOn(n));
	CPPUNIT_ASSERT_EQUAL(0,      ::RunAccumulated(n));

	/*
	EXPECTED selected.out:
			 sim	       state	        soln	      dist_x	        time	        step	          pH	          pe	           C	          Ca	          Na	     m_CO3-2	     m_CaOH+	    m_NaCO3-	    la_CO3-2	    la_CaOH+	   la_NaCO3-	     Calcite	   d_Calcite	   si_CO2(g)	 si_Siderite	    pressure	   total mol	      volume	    g_CO2(g)	     g_N2(g)	    k_Albite	   dk_Albite	    k_Pyrite	   dk_Pyrite	     s_CaSO4	     s_SrSO4	      1.name	      1.type	     1.moles	      2.name	      2.type	     2.moles	      3.name	      3.type	     3.moles	      4.name	      4.type	     4.moles	      5.name	      5.type	     5.moles	      6.name	      6.type	     6.moles
			   1	      i_soln	           1	         -99	         -99	         -99	           7	           4	 1.0000e-003	 1.0000e-003	 1.0000e-003	 4.2975e-007	 1.1819e-009	 1.1881e-009	-6.4686e+000	-8.9530e+000	-8.9507e+000	 0.0000e+000	 0.0000e+000	     -2.2870	   -999.9990	 0.0000e+000	 0.0000e+000	 0.0000e+000	 0.0000e+000	 0.0000e+000	 0.0000e+000	 0.0000e+000	 0.0000e+000	 0.0000e+000	 0.0000e+000	 0.0000e+000	        Ca+2	          aq	 9.9178e-004	     CaHCO3+	          aq	 7.5980e-006	       CaCO3	          aq	 6.2155e-007	       CaOH+	          aq	 1.1819e-009
			   1	       react	           1	         -99	           0	           1	     7.86135	       10.18	 1.1556e-003	 1.1556e-003	 1.0000e-003	 4.2718e-006	 9.7385e-009	 1.1620e-008	-5.4781e+000	-8.0388e+000	-7.9621e+000	 9.8444e-003	-1.5555e-004	     -3.0192	   -999.9990	 0.0000e+000	 0.0000e+000	 0.0000e+000	 0.0000e+000	 0.0000e+000	 0.0000e+000	 0.0000e+000	 0.0000e+000	 0.0000e+000	 0.0000e+000	 0.0000e+000	     calcite	        equi	 9.8444e-003	        Ca+2	          aq	 1.1371e-003	     CaHCO3+	          aq	 1.1598e-005	       CaCO3	          aq	 6.8668e-006	       CaOH+	          aq	 9.7385e-009
	*/

#if defined(USE_VAR)
	VAR v;
	::VarInit(&v);
#else
	CVar v;
#endif

	CPPUNIT_ASSERT_EQUAL(IPQ_INVALIDROW, ::GetSelectedOutputValue(n, -1, 0, &v));
	CPPUNIT_ASSERT_EQUAL(TT_ERROR, v.type);
	CPPUNIT_ASSERT_EQUAL(VR_INVALIDROW, v.vresult);

	CPPUNIT_ASSERT_EQUAL(IPQ_INVALIDROW, ::GetSelectedOutputValue(n, ::GetSelectedOutputRowCount(n), 0, &v));
	CPPUNIT_ASSERT_EQUAL(TT_ERROR, v.type);
	CPPUNIT_ASSERT_EQUAL(VR_INVALIDROW, v.vresult);

	CPPUNIT_ASSERT_EQUAL(IPQ_INVALIDCOL, ::GetSelectedOutputValue(n, 0, -1, &v));
	CPPUNIT_ASSERT_EQUAL(TT_ERROR, v.type);
	CPPUNIT_ASSERT_EQUAL(VR_INVALIDCOL, v.vresult);

	CPPUNIT_ASSERT_EQUAL(IPQ_INVALIDCOL, ::GetSelectedOutputValue(n, 0, ::GetSelectedOutputColumnCount(n), &v));
	CPPUNIT_ASSERT_EQUAL(TT_ERROR, v.type);
	CPPUNIT_ASSERT_EQUAL(VR_INVALIDCOL, v.vresult);


	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::GetSelectedOutputValue(n, 0, 0, &v));
	CPPUNIT_ASSERT_EQUAL(TT_STRING, v.type);
	CPPUNIT_ASSERT_EQUAL( std::string("sim"), std::string(v.sVal));

	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::GetSelectedOutputValue(n, 0, 1, &v));
	CPPUNIT_ASSERT_EQUAL(TT_STRING, v.type);
	CPPUNIT_ASSERT_EQUAL( std::string("state"), std::string(v.sVal));

	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::GetSelectedOutputValue(n, 0, 2, &v));
	CPPUNIT_ASSERT_EQUAL(TT_STRING, v.type);
	CPPUNIT_ASSERT_EQUAL( std::string("soln"), std::string(v.sVal));

	//{{{{{{
	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::GetSelectedOutputValue(n, 0, 3, &v));
	CPPUNIT_ASSERT_EQUAL(TT_STRING, v.type);
	CPPUNIT_ASSERT_EQUAL( std::string("dist_x"), std::string(v.sVal));

	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::GetSelectedOutputValue(n, 0, 4, &v));
	CPPUNIT_ASSERT_EQUAL(TT_STRING, v.type);
	CPPUNIT_ASSERT_EQUAL( std::string("time"), std::string(v.sVal));

	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::GetSelectedOutputValue(n, 0, 5, &v));
	CPPUNIT_ASSERT_EQUAL(TT_STRING, v.type);
	CPPUNIT_ASSERT_EQUAL( std::string("step"), std::string(v.sVal));

	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::GetSelectedOutputValue(n, 0, 6, &v));
	CPPUNIT_ASSERT_EQUAL(TT_STRING, v.type);
	CPPUNIT_ASSERT_EQUAL( std::string("pH"), std::string(v.sVal));

	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::GetSelectedOutputValue(n, 0, 7, &v));
	CPPUNIT_ASSERT_EQUAL(TT_STRING, v.type);
	CPPUNIT_ASSERT_EQUAL( std::string("pe"), std::string(v.sVal));

	int col = 7;

	// -totals C Ca Na
	++col;
	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::GetSelectedOutputValue(n, 0, col, &v));
	CPPUNIT_ASSERT_EQUAL(TT_STRING, v.type);
	CPPUNIT_ASSERT_EQUAL( std::string("C(mol/kgw)"), std::string(v.sVal));
	++col;
	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::GetSelectedOutputValue(n, 0, col, &v));
	CPPUNIT_ASSERT_EQUAL(TT_STRING, v.type);
	CPPUNIT_ASSERT_EQUAL( std::string("Ca(mol/kgw)"), std::string(v.sVal));
	++col;
	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::GetSelectedOutputValue(n, 0, col, &v));
	CPPUNIT_ASSERT_EQUAL(TT_STRING, v.type);
	CPPUNIT_ASSERT_EQUAL( std::string("Na(mol/kgw)"), std::string(v.sVal));

	// -molalities CO3-2  CaOH+  NaCO3-
	++col;
	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::GetSelectedOutputValue(n, 0, col, &v));
	CPPUNIT_ASSERT_EQUAL(TT_STRING, v.type);
	CPPUNIT_ASSERT_EQUAL( std::string("m_CO3-2(mol/kgw)"), std::string(v.sVal));
	++col;
	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::GetSelectedOutputValue(n, 0, col, &v));
	CPPUNIT_ASSERT_EQUAL(TT_STRING, v.type);
	CPPUNIT_ASSERT_EQUAL( std::string("m_CaOH+(mol/kgw)"), std::string(v.sVal));
	++col;
	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::GetSelectedOutputValue(n, 0, col, &v));
	CPPUNIT_ASSERT_EQUAL(TT_STRING, v.type);
	CPPUNIT_ASSERT_EQUAL( std::string("m_NaCO3-(mol/kgw)"), std::string(v.sVal));

	// -activities CO3-2  CaOH+  NaCO3-
	++col;
	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::GetSelectedOutputValue(n, 0, col, &v));
	CPPUNIT_ASSERT_EQUAL(TT_STRING, v.type);
	CPPUNIT_ASSERT_EQUAL( std::string("la_CO3-2"), std::string(v.sVal));
	++col;
	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::GetSelectedOutputValue(n, 0, col, &v));
	CPPUNIT_ASSERT_EQUAL(TT_STRING, v.type);
	CPPUNIT_ASSERT_EQUAL( std::string("la_CaOH+"), std::string(v.sVal));
	++col;
	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::GetSelectedOutputValue(n, 0, col, &v));
	CPPUNIT_ASSERT_EQUAL(TT_STRING, v.type);
	CPPUNIT_ASSERT_EQUAL( std::string("la_NaCO3-"), std::string(v.sVal));

	// -equilibrium_phases Calcite
	++col;
	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::GetSelectedOutputValue(n, 0, col, &v));
	CPPUNIT_ASSERT_EQUAL(TT_STRING, v.type);
	CPPUNIT_ASSERT_EQUAL( std::string("Calcite"), std::string(v.sVal));
	++col;
	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::GetSelectedOutputValue(n, 0, col, &v));
	CPPUNIT_ASSERT_EQUAL(TT_STRING, v.type);
	CPPUNIT_ASSERT_EQUAL( std::string("d_Calcite"), std::string(v.sVal));


	// -saturation_indices CO2(g) Siderite
	++col;
	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::GetSelectedOutputValue(n, 0, col, &v));
	CPPUNIT_ASSERT_EQUAL(TT_STRING, v.type);
	CPPUNIT_ASSERT_EQUAL( std::string("si_CO2(g)"), std::string(v.sVal));
	++col;
	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::GetSelectedOutputValue(n, 0, col, &v));
	CPPUNIT_ASSERT_EQUAL(TT_STRING, v.type);
	CPPUNIT_ASSERT_EQUAL( std::string("si_Siderite"), std::string(v.sVal));

	// -gases CO2(g) N2(g)
	//                      pressure "total mol" volume g_CO2(g) g_N2(g)
	++col;
	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::GetSelectedOutputValue(n, 0, col, &v));
	CPPUNIT_ASSERT_EQUAL(TT_STRING, v.type);
	CPPUNIT_ASSERT_EQUAL( std::string("pressure"), std::string(v.sVal));
	++col;
	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::GetSelectedOutputValue(n, 0, col, &v));
	CPPUNIT_ASSERT_EQUAL(TT_STRING, v.type);
	CPPUNIT_ASSERT_EQUAL( std::string("total mol"), std::string(v.sVal));
	++col;
	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::GetSelectedOutputValue(n, 0, col, &v));
	CPPUNIT_ASSERT_EQUAL(TT_STRING, v.type);
	CPPUNIT_ASSERT_EQUAL( std::string("volume"), std::string(v.sVal));
	++col;
	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::GetSelectedOutputValue(n, 0, col, &v));
	CPPUNIT_ASSERT_EQUAL(TT_STRING, v.type);
	CPPUNIT_ASSERT_EQUAL( std::string("g_CO2(g)"), std::string(v.sVal));
	++col;
	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::GetSelectedOutputValue(n, 0, col, &v));
	CPPUNIT_ASSERT_EQUAL(TT_STRING, v.type);
	CPPUNIT_ASSERT_EQUAL( std::string("g_N2(g)"), std::string(v.sVal));

	// -kinetic_reactants Albite Pyrite
	//                               k_Albite dk_Albite k_Pyrite dk_Pyrite
	++col;
	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::GetSelectedOutputValue(n, 0, col, &v));
	CPPUNIT_ASSERT_EQUAL(TT_STRING, v.type);
	CPPUNIT_ASSERT_EQUAL( std::string("k_Albite"), std::string(v.sVal));
	++col;
	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::GetSelectedOutputValue(n, 0, col, &v));
	CPPUNIT_ASSERT_EQUAL(TT_STRING, v.type);
	CPPUNIT_ASSERT_EQUAL( std::string("dk_Albite"), std::string(v.sVal));
	++col;
	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::GetSelectedOutputValue(n, 0, col, &v));
	CPPUNIT_ASSERT_EQUAL(TT_STRING, v.type);
	CPPUNIT_ASSERT_EQUAL( std::string("k_Pyrite"), std::string(v.sVal));
	++col;
	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::GetSelectedOutputValue(n, 0, col, &v));
	CPPUNIT_ASSERT_EQUAL(TT_STRING, v.type);
	CPPUNIT_ASSERT_EQUAL( std::string("dk_Pyrite"), std::string(v.sVal));

	// -solid_solutions CaSO4 SrSO4
	//                              s_CaSO4 s_SrSO4
	++col;
	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::GetSelectedOutputValue(n, 0, col, &v));
	CPPUNIT_ASSERT_EQUAL(TT_STRING, v.type);
	CPPUNIT_ASSERT_EQUAL( std::string("s_CaSO4"), std::string(v.sVal));
	++col;
	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::GetSelectedOutputValue(n, 0, col, &v));
	CPPUNIT_ASSERT_EQUAL(TT_STRING, v.type);
	CPPUNIT_ASSERT_EQUAL( std::string("s_SrSO4"), std::string(v.sVal));

	for (int i = 0; i < max; ++i)
	{
		std::ostringstream oss1, oss2, oss3;

		// 1.name
		//
		CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::GetSelectedOutputValue(n, 0, col + 1 + (i*3), &v));
		CPPUNIT_ASSERT_EQUAL(TT_STRING, v.type);
		oss1 << i + 1 << ".name";
		CPPUNIT_ASSERT_EQUAL( oss1.str(), std::string(v.sVal));

		// 1.type
		//
		CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::GetSelectedOutputValue(n, 0, col + 2 + (i*3), &v));
		CPPUNIT_ASSERT_EQUAL(TT_STRING, v.type);
		oss2 << i + 1 << ".type";
		CPPUNIT_ASSERT_EQUAL( oss2.str(), std::string(v.sVal));

		// 1.moles
		//
		CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::GetSelectedOutputValue(n, 0, col + 3 + (i*3), &v));
		CPPUNIT_ASSERT_EQUAL(TT_STRING, v.type);
		oss3 << i + 1 << ".moles";
		CPPUNIT_ASSERT_EQUAL( oss3.str(), std::string(v.sVal));
	}

	// sim
	//
	col = 0;
	//   i_soln
	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::GetSelectedOutputValue(n, 1, col, &v));
	CPPUNIT_ASSERT_EQUAL(TT_LONG, v.type);
	CPPUNIT_ASSERT_EQUAL( 1L, v.lVal );
	//   react
	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::GetSelectedOutputValue(n, 2, col, &v));
	CPPUNIT_ASSERT_EQUAL(TT_LONG, v.type);
	CPPUNIT_ASSERT_EQUAL( 1L, v.lVal );

	// state
	//
	++col;
	//   i_soln
	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::GetSelectedOutputValue(n, 1, col, &v));
	CPPUNIT_ASSERT_EQUAL(TT_STRING, v.type);
	CPPUNIT_ASSERT_EQUAL( std::string("i_soln"), std::string(v.sVal) );
	//   react
	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::GetSelectedOutputValue(n, 2, col, &v));
	CPPUNIT_ASSERT_EQUAL(TT_STRING, v.type);
	CPPUNIT_ASSERT_EQUAL( std::string("react"), std::string(v.sVal) );

	// soln
	//
	++col;
	//   i_soln
	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::GetSelectedOutputValue(n, 1, col, &v));
	CPPUNIT_ASSERT_EQUAL(TT_LONG, v.type);
	CPPUNIT_ASSERT_EQUAL( 1L, v.lVal );
	//   react
	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::GetSelectedOutputValue(n, 2, col, &v));
	CPPUNIT_ASSERT_EQUAL(TT_LONG, v.type);
	CPPUNIT_ASSERT_EQUAL( 1L, v.lVal );

	// dist_x -- sometimes as double sometimes as long (depends on state)
	//
	++col;
	//   i_soln
	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::GetSelectedOutputValue(n, 1, col, &v));
	CPPUNIT_ASSERT_EQUAL(TT_LONG, v.type);
	CPPUNIT_ASSERT_EQUAL( -99L, v.lVal );
	//   react
	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::GetSelectedOutputValue(n, 2, col, &v));
	CPPUNIT_ASSERT_EQUAL(TT_LONG, v.type);
	CPPUNIT_ASSERT_EQUAL( -99L, v.lVal );


	// time -- sometimes as double sometimes as long (depends on state)
	//
	++col;
	//   i_soln
	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::GetSelectedOutputValue(n, 1, col, &v));
	CPPUNIT_ASSERT_EQUAL(TT_LONG, v.type);
	CPPUNIT_ASSERT_EQUAL( -99L, v.lVal );
	//   react
	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::GetSelectedOutputValue(n, 2, col, &v));
	CPPUNIT_ASSERT_EQUAL(TT_DOUBLE, v.type);
	CPPUNIT_ASSERT_DOUBLES_EQUAL( 0.0, v.dVal, ::pow(10., -DBL_DIG) );

	// step
	//
	++col;
	//   i_soln
	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::GetSelectedOutputValue(n, 1, col, &v));
	CPPUNIT_ASSERT_EQUAL(TT_LONG, v.type);
	CPPUNIT_ASSERT_EQUAL(-99L, v.lVal);
	//   react
	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::GetSelectedOutputValue(n, 2, col, &v));
	CPPUNIT_ASSERT_EQUAL(TT_LONG, v.type);
	CPPUNIT_ASSERT_EQUAL(1L, v.lVal);


	// pH
	//
	++col;
	//   i_soln
	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::GetSelectedOutputValue(n, 1, col, &v));
	CPPUNIT_ASSERT_EQUAL(TT_DOUBLE, v.type);
	CPPUNIT_ASSERT_DOUBLES_EQUAL( 7.0, v.dVal, ::pow(10., -DBL_DIG) );
	//   react
	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::GetSelectedOutputValue(n, 2, col, &v));
	CPPUNIT_ASSERT_EQUAL(TT_DOUBLE, v.type);
	CPPUNIT_ASSERT_DOUBLES_EQUAL( 7.861354, v.dVal, ::pow(10., -6) );

	// pe
	//
	++col;
	//   i_soln
	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::GetSelectedOutputValue(n, 1, col, &v));
	CPPUNIT_ASSERT_EQUAL(TT_DOUBLE, v.type);
	CPPUNIT_ASSERT_DOUBLES_EQUAL( 4.0, v.dVal, ::pow(10., -DBL_DIG) );
	//   react
	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::GetSelectedOutputValue(n, 2, col, &v));
	CPPUNIT_ASSERT_EQUAL(TT_DOUBLE, v.type);
	CPPUNIT_ASSERT_DOUBLES_EQUAL( 10.4, v.dVal, ::pow(10., -1) );

	//
	// -totals C Ca Na
	//

	// C(mol/kgw)
	//
	++col;
	//   i_soln
	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::GetSelectedOutputValue(n, 1, col, &v));
	CPPUNIT_ASSERT_EQUAL(TT_DOUBLE, v.type);
	CPPUNIT_ASSERT_DOUBLES_EQUAL( 1.0000e-003, v.dVal, ::pow(10., -DBL_DIG) );
	//   react
	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::GetSelectedOutputValue(n, 2, col, &v));
	CPPUNIT_ASSERT_EQUAL(TT_DOUBLE, v.type);
	CPPUNIT_ASSERT_DOUBLES_EQUAL( 1.1556e-003, v.dVal, ::pow(10., -7) );


	// Ca(mol/kgw)
	//
	++col;
	//   i_soln
	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::GetSelectedOutputValue(n, 1, col, &v));
	CPPUNIT_ASSERT_EQUAL(TT_DOUBLE, v.type);
	CPPUNIT_ASSERT_DOUBLES_EQUAL( 1.0000e-003, v.dVal, ::pow(10., -DBL_DIG) );
	//   react
	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::GetSelectedOutputValue(n, 2, col, &v));
	CPPUNIT_ASSERT_EQUAL(TT_DOUBLE, v.type);
	CPPUNIT_ASSERT_DOUBLES_EQUAL( 1.1556e-003, v.dVal, ::pow(10., -7) );


	// Na(mol/kgw)
	//
	++col;
	//   i_soln
	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::GetSelectedOutputValue(n, 1, col, &v));
	CPPUNIT_ASSERT_EQUAL(TT_DOUBLE, v.type);
	CPPUNIT_ASSERT_DOUBLES_EQUAL( 1.0000e-003, v.dVal, ::pow(10., -DBL_DIG) );
	//   react
	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::GetSelectedOutputValue(n, 2, col, &v));
	CPPUNIT_ASSERT_EQUAL(TT_DOUBLE, v.type);
	CPPUNIT_ASSERT_DOUBLES_EQUAL( 1.0000e-003, v.dVal, ::pow(10., -7) );

	// -molalities CO3-2  CaOH+  NaCO3-
	col += 3;

	// -activities CO3-2  CaOH+  NaCO3-
	col += 3;

	// -equilibrium_phases Calcite
	col += 2;

	// -saturation_indices CO2(g) Siderite
	col += 2;

	// -gases CO2(g) N2(g)
	col += 5;

	// -kinetic_reactants Albite Pyrite
	//                               k_Albite dk_Albite k_Pyrite dk_Pyrite
	col += 4;

	// -solid_solutions CaSO4 SrSO4
	//                              s_CaSO4 s_SrSO4
	col += 2;


	// 1.name
	//
	++col;
	//   i_soln
	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::GetSelectedOutputValue(n, 1, col, &v));
	CPPUNIT_ASSERT_EQUAL(TT_STRING, v.type);
	CPPUNIT_ASSERT_EQUAL( std::string("Ca+2"),  std::string(v.sVal));
	//   react
	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::GetSelectedOutputValue(n, 2, col, &v));
	CPPUNIT_ASSERT_EQUAL(TT_STRING, v.type);
	CPPUNIT_ASSERT_EQUAL( std::string("calcite"),  std::string(v.sVal));

	// 1.type
	//
	++col;
	//   i_soln
	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::GetSelectedOutputValue(n, 1, col, &v));
	CPPUNIT_ASSERT_EQUAL(TT_STRING, v.type);
	CPPUNIT_ASSERT_EQUAL( std::string("aq"),  std::string(v.sVal));
	//   react
	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::GetSelectedOutputValue(n, 2, col, &v));
	CPPUNIT_ASSERT_EQUAL(TT_STRING, v.type);
	CPPUNIT_ASSERT_EQUAL( std::string("equi"),  std::string(v.sVal));

	// 1.moles
	//
	++col;
	//   i_soln
	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::GetSelectedOutputValue(n, 1, col, &v));
	CPPUNIT_ASSERT_EQUAL(TT_DOUBLE, v.type);
	CPPUNIT_ASSERT_DOUBLES_EQUAL( 9.9177923E-04, v.dVal, ::pow(10., -11) );
	//   react
	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::GetSelectedOutputValue(n, 2, col, &v));
	CPPUNIT_ASSERT_EQUAL(TT_DOUBLE, v.type);
	CPPUNIT_ASSERT_DOUBLES_EQUAL( 9.8444477E-03, v.dVal, ::pow(10., -10) );

	// 2.name
	//
	++col;
	//   i_soln
	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::GetSelectedOutputValue(n, 1, col, &v));
	CPPUNIT_ASSERT_EQUAL( TT_STRING, v.type );
	CPPUNIT_ASSERT_EQUAL( std::string("CaHCO3+"),  std::string(v.sVal));
	//   react
	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::GetSelectedOutputValue(n, 2, col, &v));
	CPPUNIT_ASSERT_EQUAL( TT_STRING, v.type );
	CPPUNIT_ASSERT_EQUAL( std::string("Ca+2"),  std::string(v.sVal));

	// 2.type
	//
	++col;
	//   i_soln
	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::GetSelectedOutputValue(n, 1, col, &v));
	CPPUNIT_ASSERT_EQUAL( TT_STRING, v.type );
	CPPUNIT_ASSERT_EQUAL( std::string("aq"),  std::string(v.sVal));
	//   react
	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::GetSelectedOutputValue(n, 2, col, &v));
	CPPUNIT_ASSERT_EQUAL( TT_STRING, v.type );
	CPPUNIT_ASSERT_EQUAL( std::string("aq"),  std::string(v.sVal));

	// 2.moles
	//
	++col;
	//   i_soln
	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::GetSelectedOutputValue(n, 1, col, &v));
	CPPUNIT_ASSERT_EQUAL(TT_DOUBLE, v.type);
	CPPUNIT_ASSERT_DOUBLES_EQUAL( 7.5980e-006, v.dVal, ::pow(10., -10) );
	//   react
	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::GetSelectedOutputValue(n, 2, col, &v));
	CPPUNIT_ASSERT_EQUAL(TT_DOUBLE, v.type);
	CPPUNIT_ASSERT_DOUBLES_EQUAL( 1.1371e-003, v.dVal, ::pow(10., -7) );


	// 3.name
	//
	++col;
	//   i_soln
	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::GetSelectedOutputValue(n, 1, col, &v));
	CPPUNIT_ASSERT_EQUAL( TT_STRING, v.type );
	CPPUNIT_ASSERT_EQUAL( std::string("CaCO3"),  std::string(v.sVal));
	//   react
	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::GetSelectedOutputValue(n, 2, col, &v));
	CPPUNIT_ASSERT_EQUAL( TT_STRING, v.type );
	CPPUNIT_ASSERT_EQUAL( std::string("CaHCO3+"),  std::string(v.sVal));

	// 3.type
	//
	++col;
	//   i_soln
	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::GetSelectedOutputValue(n, 1, col, &v));
	CPPUNIT_ASSERT_EQUAL( TT_STRING, v.type );
	CPPUNIT_ASSERT_EQUAL( std::string("aq"),  std::string(v.sVal));
	//   react
	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::GetSelectedOutputValue(n, 2, col, &v));
	CPPUNIT_ASSERT_EQUAL( TT_STRING, v.type );
	CPPUNIT_ASSERT_EQUAL( std::string("aq"),  std::string(v.sVal));

	// 3.moles
	//
	++col;
	//   i_soln
	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::GetSelectedOutputValue(n, 1, col, &v));
	CPPUNIT_ASSERT_EQUAL(TT_DOUBLE, v.type);
	CPPUNIT_ASSERT_DOUBLES_EQUAL( 6.2155e-007, v.dVal, ::pow(10., -11) );
	//   react
	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::GetSelectedOutputValue(n, 2, col, &v));
	CPPUNIT_ASSERT_EQUAL(TT_DOUBLE, v.type);
	CPPUNIT_ASSERT_DOUBLES_EQUAL( 1.1598e-005, v.dVal, ::pow(10., -9) );



	// 4.name
	//
	++col;
	//   i_soln
	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::GetSelectedOutputValue(n, 1, col, &v));
	CPPUNIT_ASSERT_EQUAL( TT_STRING, v.type );
	CPPUNIT_ASSERT_EQUAL( std::string("CaOH+"),  std::string(v.sVal));
	//   react
	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::GetSelectedOutputValue(n, 2, col, &v));
	CPPUNIT_ASSERT_EQUAL( TT_STRING, v.type );
	CPPUNIT_ASSERT_EQUAL( std::string("CaCO3"),  std::string(v.sVal));

	// 4.type
	//
	++col;
	//   i_soln
	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::GetSelectedOutputValue(n, 1, col, &v));
	CPPUNIT_ASSERT_EQUAL( TT_STRING, v.type );
	CPPUNIT_ASSERT_EQUAL( std::string("aq"),  std::string(v.sVal));
	//   react
	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::GetSelectedOutputValue(n, 2, col, &v));
	CPPUNIT_ASSERT_EQUAL( TT_STRING, v.type );
	CPPUNIT_ASSERT_EQUAL( std::string("aq"),  std::string(v.sVal));

	// 4.moles
	//
	++col;
	//   i_soln
	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::GetSelectedOutputValue(n, 1, col, &v));
	CPPUNIT_ASSERT_EQUAL(TT_DOUBLE, v.type);
	CPPUNIT_ASSERT_DOUBLES_EQUAL( 1.1819e-009, v.dVal, ::pow(10., -13) );
	//   react
	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::GetSelectedOutputValue(n, 2, col, &v));
	CPPUNIT_ASSERT_EQUAL(TT_DOUBLE, v.type);
	CPPUNIT_ASSERT_DOUBLES_EQUAL( 6.8668e-006, v.dVal, ::pow(10., -10) );


	// 5.name
	//
	++col;
	//   i_soln
	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::GetSelectedOutputValue(n, 1, col, &v));
	CPPUNIT_ASSERT_EQUAL( TT_EMPTY, v.type );
	//   react
	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::GetSelectedOutputValue(n, 2, col, &v));
	CPPUNIT_ASSERT_EQUAL(TT_STRING, v.type);
	CPPUNIT_ASSERT_EQUAL( std::string("CaOH+"),  std::string(v.sVal));

	// 5.type
	//
	++col;
	//   i_soln
	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::GetSelectedOutputValue(n, 1, col, &v));
	CPPUNIT_ASSERT_EQUAL( TT_EMPTY, v.type );
	//   react
	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::GetSelectedOutputValue(n, 2, col, &v));
	CPPUNIT_ASSERT_EQUAL(TT_STRING, v.type);
	CPPUNIT_ASSERT_EQUAL( std::string("aq"),  std::string(v.sVal));

	// 5.moles
	//
	++col;
	//   i_soln
	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::GetSelectedOutputValue(n, 1, col, &v));
	CPPUNIT_ASSERT_EQUAL( TT_EMPTY, v.type );
	//   react
	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::GetSelectedOutputValue(n, 2, col, &v));
	CPPUNIT_ASSERT_EQUAL( TT_DOUBLE, v.type );
	CPPUNIT_ASSERT_DOUBLES_EQUAL( 9.7385e-009, v.dVal, ::pow(10., -13) );


	// 6.name
	//
	++col;
	//   i_soln
	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::GetSelectedOutputValue(n, 1, col, &v));
	CPPUNIT_ASSERT_EQUAL( TT_EMPTY, v.type );
	//   react
	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::GetSelectedOutputValue(n, 2, col, &v));
	CPPUNIT_ASSERT_EQUAL( TT_EMPTY, v.type );

	// 6.type
	//
	++col;
	//   i_soln
	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::GetSelectedOutputValue(n, 1, col, &v));
	CPPUNIT_ASSERT_EQUAL( TT_EMPTY, v.type );
	//   react
	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::GetSelectedOutputValue(n, 2, col, &v));
	CPPUNIT_ASSERT_EQUAL( TT_EMPTY, v.type );

	// 6.moles
	//
	++col;
	//   i_soln
	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::GetSelectedOutputValue(n, 1, col, &v));
	CPPUNIT_ASSERT_EQUAL( TT_EMPTY, v.type );
	//   react
	CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::GetSelectedOutputValue(n, 2, col, &v));
	CPPUNIT_ASSERT_EQUAL( TT_EMPTY, v.type );

	if (n >= 0)
	{
		CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::DestroyIPhreeqc(n));
	}

#if defined(USE_VAR)
	::VarClear(&v);
#endif
}

IPQ_RESULT
SOLUTION(int n, double C, double Ca, double Na)
{
	std::ostringstream oss;

	oss << "SOLUTION 1\n";
	oss << "C "  << C  << "\n";
	oss << "Ca " << Ca << "\n";
	oss << "Na " << Na << "\n";

	return ::AccumulateLine(n, oss.str().c_str());
}

IPQ_RESULT
EQUILIBRIUM_PHASES(int n, const char* phase, double si, double amount)
{
	std::ostringstream oss;

	oss << "EQUILIBRIUM_PHASES\n";
	oss << phase << " " << si << " " << amount << "\n";
	return ::AccumulateLine(n, oss.str().c_str());
}

IPQ_RESULT
USER_PUNCH(int n, const char* element, int max)
{
	std::ostringstream oss;

	oss << "USER_PUNCH\n";

	oss << "-head ";
	for (int i = 1; i <= max; ++i)
	{
		oss << i << ".name " << i << ".type " << i << ".moles ";
	}
	oss << "\n";
	oss << "-start" << "\n";
	oss << "10 n = sys(\"" << element << "\"" << ", count, names$, types$, moles)" << "\n";
	oss << "20 n = " << max << "\n";
	oss << "30 if count < " << max << " then n = count" << "\n";
	oss << "40 for i = 1 to count" << "\n";
	oss << "50 PUNCH names$(i), types$(i), moles(i)" << "\n";
	oss << "60 next i" << "\n";
	oss << "70 list" << "\n";
	oss << "-end" << "\n";
	oss << "SELECTED_OUTPUT" << "\n";
	oss << "-totals C Ca Na" << "\n";
	oss << "-molalities CO3-2  CaOH+  NaCO3-" << "\n";
	oss << "-activities CO3-2  CaOH+  NaCO3-" << "\n";
	oss << "-equilibrium_phases Calcite" << "\n";
	oss << "-saturation_indices CO2(g) Siderite" << "\n";
	oss << "-gases CO2(g) N2(g)" << "\n";
	oss << "-kinetic_reactants Albite Pyrite" << "\n";
	oss << "-solid_solutions CaSO4 SrSO4" << "\n";

	return ::AccumulateLine(n, oss.str().c_str());
}

IPQ_RESULT
SELECTED_OUTPUT(int n)
{
	std::ostringstream oss;

	oss << "SELECTED_OUTPUT" << "\n";
	oss << "-file selected.out" << "\n";
	oss << "-totals C Ca Na" << "\n";

	return ::AccumulateLine(n, oss.str().c_str());
}

IPQ_RESULT
DUMP(int n)
{
	std::ostringstream oss;
	oss << "DUMP" << "\n";
	oss << "-solution 1" << "\n";
	return ::AccumulateLine(n, oss.str().c_str());
}

void TestIPhreeqcLib::TestGetSelectedOutputColumnCount(void)
{
	int n = ::CreateIPhreeqc();
	CPPUNIT_ASSERT(n >= 0);

	CPPUNIT_ASSERT_EQUAL( 0,      ::LoadDatabase(n, "llnl.dat"));
	CPPUNIT_ASSERT_EQUAL( 0,      ::GetSelectedOutputColumnCount(n) );
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::SOLUTION(n, 1.0, 1.0, 1.0) );
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::EQUILIBRIUM_PHASES(n, "calcite", 1.0, 1.0) );
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::USER_PUNCH(n, "Ca", 10) );
	CPPUNIT_ASSERT_EQUAL( 0,      ::RunAccumulated(n) );
	CPPUNIT_ASSERT_EQUAL( 62,     ::GetSelectedOutputColumnCount(n) );
	if (n >= 0)
	{
		CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::DestroyIPhreeqc(n));
	}
}

void TestIPhreeqcLib::TestAddError(void)
{
	int n = ::CreateIPhreeqc();
	CPPUNIT_ASSERT(n >= 0);

	CPPUNIT_ASSERT_EQUAL(0, ::LoadDatabase(n, "phreeqc.dat"));

	// make sure initialized to empty
	//
	const char* err = ::GetErrorString(n);
	CPPUNIT_ASSERT_EQUAL( std::string(""), std::string(err) );

	// make sure initialized to empty
	//
	const char *expected = "TESTING AddError\n";
	CPPUNIT_ASSERT_EQUAL(1, ::AddError(n, expected));

	// check 1
	//
	err = ::GetErrorString(n);
	CPPUNIT_ASSERT_EQUAL( std::string(expected), std::string(err) );

	// check increment
	//
	const char *expected2 = "XXXXXX\n";
	CPPUNIT_ASSERT_EQUAL(2, ::AddError(n, expected2));

	// check concatenation
	//
	err = ::GetErrorString(n);
	CPPUNIT_ASSERT_EQUAL( std::string(expected) + std::string(expected2), std::string(err) );


	// clear errors
	//
	CPPUNIT_ASSERT_EQUAL(0, ::LoadDatabase(n, "phreeqc.dat"));

	// make sure back to empty
	//
	err = ::GetErrorString(n);
	CPPUNIT_ASSERT_EQUAL( std::string(""), std::string(err) );

	if (n >= 0)
	{
		CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::DestroyIPhreeqc(n));
	}
}

void TestIPhreeqcLib::TestAccumulateLine(void)
{
	// TODO
}

void TestIPhreeqcLib::TestOutputError(void)
{
	// TODO
}

void TestIPhreeqcLib::TestRunWithCallback(void)
{
	// TODO
}

void TestIPhreeqcLib::TestRunNoDatabaseLoaded(void)
{
	int n = ::CreateIPhreeqc();
	CPPUNIT_ASSERT(n >= 0);

	::UnLoadDatabase(n);
	CPPUNIT_ASSERT_EQUAL( 1, ::RunAccumulated(n) );

	const char expected[] =
		"ERROR: RunAccumulated: No database is loaded\n";
	const char* err = ::GetErrorString(n);

	CPPUNIT_ASSERT_EQUAL( std::string(expected), std::string(err) );

	if (n >= 0)
	{
		CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::DestroyIPhreeqc(n));
	}
}

void TestIPhreeqcLib::TestCase1(void)
{
	// Case 1 (see do_run)
	// pr.punch == TRUE
	// punch.new_def == FALSE
	// output_isopen(OUTPUT_PUNCH) == FALSE
	// selected_output_on == TRUE

	int n = ::CreateIPhreeqc();
	CPPUNIT_ASSERT(n >= 0);

	// remove punch file if it exists
	if (::FileExists("selected.out"))
	{
		CPPUNIT_ASSERT(::DeleteFile("selected.out"));
	}
	CPPUNIT_ASSERT_EQUAL( false,      ::FileExists("selected.out") );
	CPPUNIT_ASSERT_EQUAL( true,       ::FileExists("phreeqc.dat") );
	CPPUNIT_ASSERT_EQUAL( 0,          ::LoadDatabase(n, "phreeqc.dat") );
	CPPUNIT_ASSERT_EQUAL( IPQ_OK,     ::SOLUTION(n, 1.0, 1.0, 1.0) );
	CPPUNIT_ASSERT_EQUAL( IPQ_OK,     ::USER_PUNCH(n, "Ca", 10) );
	CPPUNIT_ASSERT_EQUAL( IPQ_OK,     ::SetSelectedOutputOn(n, 1) );
	CPPUNIT_ASSERT_EQUAL( 0,          ::RunAccumulated(n) );
	CPPUNIT_ASSERT_EQUAL( true,       ::FileExists("selected.out") );
	CPPUNIT_ASSERT_EQUAL( 62,         ::GetSelectedOutputColumnCount(n) );
	CPPUNIT_ASSERT_EQUAL( IPQ_OK,     ::SOLUTION(n, 1.0, 1.0, 1.0) );
	CPPUNIT_ASSERT_EQUAL( IPQ_OK,     ::SetSelectedOutputOn(n, 1) );
	CPPUNIT_ASSERT_EQUAL( 0,          ::RunAccumulated(n) );
	CPPUNIT_ASSERT_EQUAL( true,       ::FileExists("selected.out") );
	CPPUNIT_ASSERT_EQUAL( 62,         ::GetSelectedOutputColumnCount(n) );

	if (n >= 0)
	{
		CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::DestroyIPhreeqc(n));
	}
}

void TestIPhreeqcLib::TestCase2(void)
{
	// Case 2 (see do_run)
	// pr.punch == TRUE
	// punch.new_def == TRUE
	// output_isopen(OUTPUT_PUNCH) == FALSE
	// selected_output_on == TRUE

	int n = ::CreateIPhreeqc();
	CPPUNIT_ASSERT(n >= 0);

	// remove punch files if they exists
	//
	if (::FileExists("selected.out"))
	{
		::DeleteFile("selected.out");
	}
	if (::FileExists("case2.punch"))
	{
		::DeleteFile("case2.punch");
	}
	CPPUNIT_ASSERT_EQUAL( false,   ::FileExists("selected.out") );
	CPPUNIT_ASSERT_EQUAL( false,   ::FileExists("case2.punch") );
	CPPUNIT_ASSERT_EQUAL( 0,       ::LoadDatabase(n, "phreeqc.dat") );
	CPPUNIT_ASSERT_EQUAL( IPQ_OK,  ::SOLUTION(n, 1.0, 1.0, 1.0) );
	CPPUNIT_ASSERT_EQUAL( IPQ_OK,  ::USER_PUNCH(n, "Ca", 10) );
	CPPUNIT_ASSERT_EQUAL( IPQ_OK,  ::AccumulateLine(n, "-file case2.punch") ); // force have_punch_name to TRUE (see read_selected_ouput)
	CPPUNIT_ASSERT_EQUAL( IPQ_OK,  ::SetSelectedOutputOn(n, 1) );
	CPPUNIT_ASSERT_EQUAL( 0,       ::RunAccumulated(n) );
	CPPUNIT_ASSERT_EQUAL( false,   ::FileExists("selected.out") );
	CPPUNIT_ASSERT_EQUAL( true,    ::FileExists("case2.punch") );
	CPPUNIT_ASSERT_EQUAL( 62,      ::GetSelectedOutputColumnCount(n) );


	// remove punch files if they exists
	//
	if (::FileExists("selected.out"))
	{
		::DeleteFile("selected.out");
	}
	if (::FileExists("case2.punch"))
	{
		::DeleteFile("case2.punch");
	}
	CPPUNIT_ASSERT_EQUAL( false,  ::FileExists("selected.out") );
	CPPUNIT_ASSERT_EQUAL( false,  ::FileExists("case2.punch") );
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::SOLUTION(n, 1.0, 1.0, 1.0) );
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::USER_PUNCH(n, "Ca", 10) );
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::SetSelectedOutputOn(n, 1) );
	CPPUNIT_ASSERT_EQUAL( 0,      ::RunAccumulated(n) );
	CPPUNIT_ASSERT_EQUAL( false,  ::FileExists("selected.out") );
	CPPUNIT_ASSERT_EQUAL( true,   ::FileExists("case2.punch") );
	CPPUNIT_ASSERT_EQUAL( 62,     ::GetSelectedOutputColumnCount(n) );

	if (::FileExists("case2.punch"))
	{
		::DeleteFile("case2.punch");
	}
	CPPUNIT_ASSERT_EQUAL( false,  ::FileExists("case2.punch") );

	if (n >= 0)
	{
		CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::DestroyIPhreeqc(n));
	}
}

void TestIPhreeqcLib::TestPrintSelectedOutputFalse(void)
{
	int n = ::CreateIPhreeqc();
	CPPUNIT_ASSERT(n >= 0);

	// remove punch files if they exists
	//
	if (::FileExists("selected.out"))
	{
		::DeleteFile("selected.out");
	}
	CPPUNIT_ASSERT_EQUAL( false,  ::FileExists("selected.out") );

	CPPUNIT_ASSERT_EQUAL( 0,      ::LoadDatabase(n, "phreeqc.dat") );

	// add solution block
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::SOLUTION(n, 1.0, 1.0, 1.0) );

	// add selected output block
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::SELECTED_OUTPUT(n) );

	// turn off selected output
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::AccumulateLine(n, "PRINT; -selected_output false \n") );

	// run
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::SetSelectedOutputOn(n, 1) );
	CPPUNIT_ASSERT_EQUAL( 0,      ::RunAccumulated(n) );

	CPPUNIT_ASSERT_EQUAL( 0,      ::GetSelectedOutputColumnCount(n) );
	CPPUNIT_ASSERT_EQUAL( 0,      ::GetSelectedOutputRowCount(n) );


	// reset pr.punch to TRUE
	CPPUNIT_ASSERT_EQUAL( 0,      ::LoadDatabase(n, "phreeqc.dat") );

	// add solution block
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::SOLUTION(n, 1.0, 1.0, 1.0) );

	// add selected output block
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::SELECTED_OUTPUT(n) );

	// run
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::SetSelectedOutputOn(n, 1) );
	CPPUNIT_ASSERT_EQUAL( 0,      ::RunAccumulated(n) );

	CPPUNIT_ASSERT_EQUAL( 11,     ::GetSelectedOutputColumnCount(n) );
	CPPUNIT_ASSERT_EQUAL( 2,      ::GetSelectedOutputRowCount(n) );

	if (n >= 0)
	{
		CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::DestroyIPhreeqc(n));
	}
}

void TestIPhreeqcLib::TestOutputOnOff()
{
	int onoff[5];
	onoff[0] = 1;  // output_on
	onoff[1] = 0;  // error_on
	onoff[2] = 0;  // log_on
	onoff[3] = 0;  // selected_output_on
	onoff[4] = 0;  // dump_on
	TestOnOff("phreeqc.out", onoff[0], onoff[1], onoff[2], onoff[3], onoff[4]);
}

void TestIPhreeqcLib::TestErrorOnOff()
{
	int onoff[5];
	onoff[0] = 0;  // output_on
	onoff[1] = 1;  // error_on
	onoff[2] = 0;  // log_on
	onoff[3] = 0;  // selected_output_on
	onoff[4] = 0;  // dump_on
	TestOnOff("phreeqc.err", onoff[0], onoff[1], onoff[2], onoff[3], onoff[4]);
}

void TestIPhreeqcLib::TestLogOnOff()
{
	int onoff[5];
	onoff[0] = 0;  // output_on
	onoff[1] = 0;  // error_on
	onoff[2] = 1;  // log_on
	onoff[3] = 0;  // selected_output_on
	onoff[4] = 0;  // dump_on
	TestOnOff("phreeqc.log", onoff[0], onoff[1], onoff[2], onoff[3], onoff[4]);
}

void TestIPhreeqcLib::TestDumpOn()
{
	int onoff[5];
	onoff[0] = 0;  // output_on
	onoff[1] = 0;  // error_on
	onoff[2] = 0;  // log_on
	onoff[3] = 0;  // selected_output_on
	onoff[4] = 1;  // dump_on
	TestOnOff("dump.out", onoff[0], onoff[1], onoff[2], onoff[3], onoff[4]);
}

void TestIPhreeqcLib::TestSelOutOnOff()
{
	int onoff[5];
	onoff[0] = 0;  // output_on
	onoff[1] = 0;  // error_on
	onoff[2] = 0;  // log_on
	onoff[3] = 1;   // selected_output_on
	onoff[4] = 0;  // dump_on
	TestOnOff("selected.out", onoff[0], onoff[1], onoff[2], onoff[3], onoff[4]);
}

void TestIPhreeqcLib::TestOnOff(const char* FILENAME, int output_on, int error_on, int log_on, int selected_output_on, int dump_on)
{
	int dump_string_on = 0;

	int n = ::CreateIPhreeqc();
	CPPUNIT_ASSERT(n >= 0);

	// remove FILENAME if it exists
	//
	if (::FileExists(FILENAME))
	{
		::DeleteFile(FILENAME);
	}
	CPPUNIT_ASSERT_EQUAL( false,  ::FileExists(FILENAME) );

	CPPUNIT_ASSERT_EQUAL( 0,      ::LoadDatabase(n, "phreeqc.dat") );

	// add solution block
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::SOLUTION(n, 1.0, 1.0, 1.0) );

	// add selected output block
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::SELECTED_OUTPUT(n) );

	// add dump block
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::DUMP(n) );

	// run all off
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::SetDumpOn(n, 0) );
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::SetErrorOn(n, 0) );
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::SetLogOn(n, 0) );
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::SetOutputOn(n, 0) );
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::SetSelectedOutputOn(n, 0) );
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::SetDumpStringOn(n, 0) );
	CPPUNIT_ASSERT_EQUAL( 0,      ::RunAccumulated(n) );
	CPPUNIT_ASSERT_EQUAL( false,  ::FileExists(FILENAME) );
	CPPUNIT_ASSERT_EQUAL( 0,      ::LoadDatabase(n, "phreeqc.dat") );

	// add solution block
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::SOLUTION(n, 1.0, 1.0, 1.0) );

	// add selected output block
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::SELECTED_OUTPUT(n) );

	// add dump block
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::DUMP(n) );

	// run
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::SetDumpOn(n, dump_on) );
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::SetErrorOn(n, error_on) );
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::SetLogOn(n, log_on) );
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::SetOutputOn(n, output_on) );
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::SetSelectedOutputOn(n, selected_output_on) );
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::SetDumpStringOn(n, dump_string_on) );
	CPPUNIT_ASSERT_EQUAL( 0,      ::RunAccumulated(n) );
	CPPUNIT_ASSERT_EQUAL( true,   ::FileExists(FILENAME) );
	CPPUNIT_ASSERT( ::DeleteFile(FILENAME) );
	CPPUNIT_ASSERT_EQUAL( 0,      ::LoadDatabase(n, "phreeqc.dat") );

	// add solution block
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::SOLUTION(n, 1.0, 1.0, 1.0) );

	// add selected output block
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::SELECTED_OUTPUT(n) );

	// add dump block
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::DUMP(n) );

	// run
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::SetDumpOn(n, 0) );
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::SetErrorOn(n, 0) );
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::SetLogOn(n, 0) );
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::SetOutputOn(n, 0) );
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::SetSelectedOutputOn(n, 0) );
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::SetDumpStringOn(n, 0) );
	CPPUNIT_ASSERT_EQUAL( 0,      ::RunAccumulated(n) );
	CPPUNIT_ASSERT_EQUAL( false,  ::FileExists(FILENAME) );
	CPPUNIT_ASSERT_EQUAL( 0,      ::LoadDatabase(n, "phreeqc.dat") );

	// add solution block
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::SOLUTION(n, 1.0, 1.0, 1.0) );

	// add selected output block
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::SELECTED_OUTPUT(n) );

	// add dump block
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::DUMP(n) );

	// run
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::SetDumpOn(n, dump_on) );
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::SetErrorOn(n, error_on) );
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::SetLogOn(n, log_on) );
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::SetOutputOn(n, output_on) );
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::SetSelectedOutputOn(n, selected_output_on) );
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::SetDumpStringOn(n, dump_string_on) );
	CPPUNIT_ASSERT_EQUAL( 0,      ::RunAccumulated(n) );
	CPPUNIT_ASSERT_EQUAL( true,   ::FileExists(FILENAME) );
	CPPUNIT_ASSERT( ::DeleteFile(FILENAME) );

	if (n >= 0)
	{
		CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::DestroyIPhreeqc(n));
	}
}


void TestIPhreeqcLib::TestLongHeadings(void)
{
	char long_header[] = "this_is_a_long_header_0123456789012345678901234567890123456789";
	char long_value[]  = "this_is_a_long_value_01234567890123456789012345678901234567890";

	int n = ::CreateIPhreeqc();
	CPPUNIT_ASSERT(n >= 0);

	CPPUNIT_ASSERT_EQUAL(0, ::LoadDatabase(n, "phreeqc.dat"));

	std::ostringstream oss;
	oss << "SOLUTION" << "\n";

	oss << "SELECTED_OUTPUT" << "\n";
	oss << "-reset false" << "\n";

	oss << "USER_PUNCH" << "\n";
	oss << "-head " <<  long_header << "\n";
	oss << "-start" << "\n";
	oss << "10 PUNCH \"" << long_value << "\"\n";
	oss << "-end" << "\n";
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::AccumulateLine(n, oss.str().c_str()) );

	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::SetOutputOn(n, 0) );
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::SetErrorOn(n, 0) );
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::SetLogOn(n, 0) );
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::SetSelectedOutputOn(n, 0) );
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::SetDumpOn(n, 0) );
	CPPUNIT_ASSERT_EQUAL( 0,      ::RunAccumulated(n) );

	CPPUNIT_ASSERT_EQUAL( 2,      ::GetSelectedOutputRowCount(n));
	CPPUNIT_ASSERT_EQUAL( 1,      ::GetSelectedOutputColumnCount(n));

	CVar v;
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::GetSelectedOutputValue(n, 0, 0, &v));
	CPPUNIT_ASSERT_EQUAL( TT_STRING, v.type);
	CPPUNIT_ASSERT_EQUAL( std::string(long_header), std::string(v.sVal));

	CVar v1;
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::GetSelectedOutputValue(n, 1, 0, &v1));
	CPPUNIT_ASSERT_EQUAL( TT_STRING, v1.type);
	CPPUNIT_ASSERT_EQUAL( std::string(long_value), std::string(v1.sVal));

	CPPUNIT_ASSERT_EQUAL( IPQ_INVALIDCOL, ::GetSelectedOutputValue(n, 1, 1, &v1));
	CPPUNIT_ASSERT_EQUAL( IPQ_INVALIDROW, ::GetSelectedOutputValue(n, 2, 0, &v1));

	if (n >= 0)
	{
		CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::DestroyIPhreeqc(n));
	}
}

void TestIPhreeqcLib::TestDatabaseKeyword()
{
	int n = ::CreateIPhreeqc();
	CPPUNIT_ASSERT(n >= 0);

	CPPUNIT_ASSERT_EQUAL( 0,      ::LoadDatabase(n, "phreeqc.dat"));
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::SetOutputOn(n, 0) );
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::SetErrorOn(n, 0) );
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::SetLogOn(n, 0) );
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::SetSelectedOutputOn(n, 0) );
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::SetDumpOn(n, 0) );
	CPPUNIT_ASSERT_EQUAL( 1,      ::RunFile(n, "dump"));

	const char *exp_errs =
		"ERROR: Gas not found in PHASES data base, Amm(g).\n"
		"ERROR: Calculations terminating due to input errors.\n";

	const char* err = ::GetErrorString(n);
	CPPUNIT_ASSERT_EQUAL(std::string(exp_errs), std::string(err));

	const char *exp_warn =
		"WARNING: DATABASE keyword is ignored by IPhreeqc.\n"
		"WARNING: Cell-lengths were read for 1 cells. Last value is used till cell 100.\n"
		"WARNING: No dispersivities were read; disp = 0 assumed.\n"
		"WARNING: Could not find element in database, Amm.\n"
		"	Concentration is set to zero.\n";

	const char* warn = ::GetWarningString(n);
	CPPUNIT_ASSERT_EQUAL(std::string(exp_warn), std::string(warn));

	if (n >= 0)
	{
		CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::DestroyIPhreeqc(n));
	}
}

void TestIPhreeqcLib::TestDumpString()
{
	int n = ::CreateIPhreeqc();
	CPPUNIT_ASSERT(n >= 0);

	CPPUNIT_ASSERT_EQUAL(0,       ::LoadDatabase(n, "phreeqc.dat"));

	// add solution block
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::SOLUTION(n, 1.0, 1.0, 1.0) );

	// add dump block
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::DUMP(n) );

	// run
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::SetOutputOn(n, 0) );
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::SetErrorOn(n, 0) );
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::SetLogOn(n, 0) );
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::SetSelectedOutputOn(n, 0) );
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::SetDumpOn(n, 0) );
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::SetDumpStringOn(n, 1) );
	CPPUNIT_ASSERT_EQUAL( 0,      ::RunAccumulated(n) );

	const char *expected =
#if defined(_MSC_VER)
		"SOLUTION_RAW       1 \n"
		"  -temp              25\n"
		"  -total_h           111.0132593403\n"
		"  -total_o           55.509043478605\n"
		"  -cb                0.0021723831003929\n"
		"  -totals\n"
		"    C(4)   0.0010000000000376\n"
		"    Ca   0.001000000004331\n"
		"    H(0)   1.4149476909313e-025\n"
		"    Na   0.001\n"
		"  -Isotopes\n"
		"  -pH                7\n"
		"  -pe                4\n"
		"  -mu                0.0028961089894362\n"
		"  -ah2o              0.99994915105857\n"
		"  -mass_water        1\n"
		"  -total_alkalinity  0.00082761690826911\n"
		"  -activities\n"
		"    C(-4)   -67.370522674574\n"
		"    C(4)   -6.4415889265024\n"
		"    Ca   -3.1040445240857\n"
		"    E   -4\n"
		"    H(0)   -25.15\n"
		"    Na   -3.0255625287599\n"
		"    O(0)   -42.080044167952\n"
		"  -gammas\n";
#endif
#if defined(__GNUC__)
		"SOLUTION_RAW       1 \n"
		"  -temp              25\n"
		"  -total_h           111.0132593403\n"
		"  -total_o           55.509043478605\n"
		"  -cb                0.0021723831003928\n"
		"  -totals\n"
		"    C(4)   0.0010000000000376\n"
		"    Ca   0.001000000004331\n"
		"    H(0)   1.4149476909313e-25\n"
		"    Na   0.001\n"
		"  -Isotopes\n"
		"  -pH                7\n"
		"  -pe                4\n"
		"  -mu                0.0028961089894362\n"
		"  -ah2o              0.99994915105857\n"
		"  -mass_water        1\n"
		"  -total_alkalinity  0.00082761690826912\n"
		"  -activities\n"
		"    C(-4)   -67.370522674574\n"
		"    C(4)   -6.4415889265024\n"
		"    Ca   -3.1040445240857\n"
		"    E   -4\n"
		"    H(0)   -25.15\n"
		"    Na   -3.0255625287599\n"
		"    O(0)   -42.080044167952\n"
		"  -gammas\n";
#endif

	const char* dump_str = ::GetDumpString(n);
	CPPUNIT_ASSERT_EQUAL(std::string(expected), std::string(dump_str));

	if (n >= 0)
	{
		CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::DestroyIPhreeqc(n));
	}
}

void TestIPhreeqcLib::TestGetDumpLineCount(void)
{
	int n = ::CreateIPhreeqc();
	CPPUNIT_ASSERT(n >= 0);

	CPPUNIT_ASSERT_EQUAL( 0,      ::LoadDatabase(n, "phreeqc.dat"));

	// add solution block
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::SOLUTION(n, 1.0, 1.0, 1.0) );

	// add dump block
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::DUMP(n) );

	// run
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::SetOutputOn(n, 0) );
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::SetErrorOn(n, 0) );
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::SetLogOn(n, 0) );
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::SetSelectedOutputOn(n, 0) );
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::SetDumpOn(n, 0) );
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::SetDumpStringOn(n, 1) );
	CPPUNIT_ASSERT_EQUAL( 0,      ::RunAccumulated(n) );
	CPPUNIT_ASSERT_EQUAL( 26,     ::GetDumpLineCount(n) );

	if (n >= 0)
	{
		CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::DestroyIPhreeqc(n));
	}
}

void TestIPhreeqcLib::TestGetDumpLine(void)
{
	int n = ::CreateIPhreeqc();
	CPPUNIT_ASSERT(n >= 0);

	CPPUNIT_ASSERT_EQUAL( 0,      ::LoadDatabase(n, "phreeqc.dat"));

	// add solution block
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::SOLUTION(n, 1.0, 1.0, 1.0) );

	// add dump block
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::DUMP(n) );

	// run
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::SetOutputOn(n, 0) );
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::SetErrorOn(n, 0) );
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::SetLogOn(n, 0) );
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::SetSelectedOutputOn(n, 0) );
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::SetDumpOn(n, 0) );
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::SetDumpStringOn(n, 1) );
	CPPUNIT_ASSERT_EQUAL( 0,      ::RunAccumulated(n) );
	CPPUNIT_ASSERT_EQUAL( 26,     ::GetDumpLineCount(n) );

	int line = 0;
#if defined(_MSC_VER)
	CPPUNIT_ASSERT_EQUAL( std::string("SOLUTION_RAW       1 "),                    std::string(::GetDumpLine(n, line++)) );
	CPPUNIT_ASSERT_EQUAL( std::string("  -temp              25"),                  std::string(::GetDumpLine(n, line++)) );
	CPPUNIT_ASSERT_EQUAL( std::string("  -total_h           111.0132593403"),      std::string(::GetDumpLine(n, line++)) );
	CPPUNIT_ASSERT_EQUAL( std::string("  -total_o           55.509043478605"),     std::string(::GetDumpLine(n, line++)) );
	CPPUNIT_ASSERT_EQUAL( std::string("  -cb                0.0021723831003929"),  std::string(::GetDumpLine(n, line++)) );
	CPPUNIT_ASSERT_EQUAL( std::string("  -totals"),                                std::string(::GetDumpLine(n, line++)) );
	CPPUNIT_ASSERT_EQUAL( std::string("    C(4)   0.0010000000000376"),            std::string(::GetDumpLine(n, line++)) );
	CPPUNIT_ASSERT_EQUAL( std::string("    Ca   0.001000000004331"),               std::string(::GetDumpLine(n, line++)) );
	CPPUNIT_ASSERT_EQUAL( std::string("    H(0)   1.4149476909313e-025"),          std::string(::GetDumpLine(n, line++)) );
	CPPUNIT_ASSERT_EQUAL( std::string("    Na   0.001"),                           std::string(::GetDumpLine(n, line++)) );
	CPPUNIT_ASSERT_EQUAL( std::string("  -Isotopes"),                              std::string(::GetDumpLine(n, line++)) );
	CPPUNIT_ASSERT_EQUAL( std::string("  -pH                7"),                   std::string(::GetDumpLine(n, line++)) );
	CPPUNIT_ASSERT_EQUAL( std::string("  -pe                4"),                   std::string(::GetDumpLine(n, line++)) );
	CPPUNIT_ASSERT_EQUAL( std::string("  -mu                0.0028961089894362"),  std::string(::GetDumpLine(n, line++)) );
	CPPUNIT_ASSERT_EQUAL( std::string("  -ah2o              0.99994915105857"),    std::string(::GetDumpLine(n, line++)) );
	CPPUNIT_ASSERT_EQUAL( std::string("  -mass_water        1"),                   std::string(::GetDumpLine(n, line++)) );
	CPPUNIT_ASSERT_EQUAL( std::string("  -total_alkalinity  0.00082761690826911"), std::string(::GetDumpLine(n, line++)) );
	CPPUNIT_ASSERT_EQUAL( std::string("  -activities"),                            std::string(::GetDumpLine(n, line++)) );
	CPPUNIT_ASSERT_EQUAL( std::string("    C(-4)   -67.370522674574"),             std::string(::GetDumpLine(n, line++)) );
	CPPUNIT_ASSERT_EQUAL( std::string("    C(4)   -6.4415889265024"),              std::string(::GetDumpLine(n, line++)) );
	CPPUNIT_ASSERT_EQUAL( std::string("    Ca   -3.1040445240857"),                std::string(::GetDumpLine(n, line++)) );
	CPPUNIT_ASSERT_EQUAL( std::string("    E   -4"),                               std::string(::GetDumpLine(n, line++)) );
	CPPUNIT_ASSERT_EQUAL( std::string("    H(0)   -25.15"),                        std::string(::GetDumpLine(n, line++)) );
	CPPUNIT_ASSERT_EQUAL( std::string("    Na   -3.0255625287599"),                std::string(::GetDumpLine(n, line++)) );
	CPPUNIT_ASSERT_EQUAL( std::string("    O(0)   -42.080044167952"),              std::string(::GetDumpLine(n, line++)) );
	CPPUNIT_ASSERT_EQUAL( std::string("  -gammas"),                                std::string(::GetDumpLine(n, line++)) );
#endif

#if defined(__GNUC__)
	CPPUNIT_ASSERT_EQUAL( std::string("SOLUTION_RAW       1 "),                    std::string(::GetDumpLine(n, line++)) );
	CPPUNIT_ASSERT_EQUAL( std::string("  -temp              25"),                  std::string(::GetDumpLine(n, line++)) );
	CPPUNIT_ASSERT_EQUAL( std::string("  -total_h           111.0132593403"),      std::string(::GetDumpLine(n, line++)) );
	CPPUNIT_ASSERT_EQUAL( std::string("  -total_o           55.509043478605"),     std::string(::GetDumpLine(n, line++)) );
	CPPUNIT_ASSERT_EQUAL( std::string("  -cb                0.0021723831003928"),  std::string(::GetDumpLine(n, line++)) );
	CPPUNIT_ASSERT_EQUAL( std::string("  -totals"),                                std::string(::GetDumpLine(n, line++)) );
	CPPUNIT_ASSERT_EQUAL( std::string("    C(4)   0.0010000000000376"),            std::string(::GetDumpLine(n, line++)) );
	CPPUNIT_ASSERT_EQUAL( std::string("    Ca   0.001000000004331"),               std::string(::GetDumpLine(n, line++)) );
	CPPUNIT_ASSERT_EQUAL( std::string("    H(0)   1.4149476909313e-25"),           std::string(::GetDumpLine(n, line++)) );
	CPPUNIT_ASSERT_EQUAL( std::string("    Na   0.001"),                           std::string(::GetDumpLine(n, line++)) );
	CPPUNIT_ASSERT_EQUAL( std::string("  -Isotopes"),                              std::string(::GetDumpLine(n, line++)) );
	CPPUNIT_ASSERT_EQUAL( std::string("  -pH                7"),                   std::string(::GetDumpLine(n, line++)) );
	CPPUNIT_ASSERT_EQUAL( std::string("  -pe                4"),                   std::string(::GetDumpLine(n, line++)) );
	CPPUNIT_ASSERT_EQUAL( std::string("  -mu                0.0028961089894362"),  std::string(::GetDumpLine(n, line++)) );
	CPPUNIT_ASSERT_EQUAL( std::string("  -ah2o              0.99994915105857"),    std::string(::GetDumpLine(n, line++)) );
	CPPUNIT_ASSERT_EQUAL( std::string("  -mass_water        1"),                   std::string(::GetDumpLine(n, line++)) );
	CPPUNIT_ASSERT_EQUAL( std::string("  -total_alkalinity  0.00082761690826912"), std::string(::GetDumpLine(n, line++)) );
	CPPUNIT_ASSERT_EQUAL( std::string("  -activities"),                            std::string(::GetDumpLine(n, line++)) );
	CPPUNIT_ASSERT_EQUAL( std::string("    C(-4)   -67.370522674574"),             std::string(::GetDumpLine(n, line++)) );
	CPPUNIT_ASSERT_EQUAL( std::string("    C(4)   -6.4415889265024"),              std::string(::GetDumpLine(n, line++)) );
	CPPUNIT_ASSERT_EQUAL( std::string("    Ca   -3.1040445240857"),                std::string(::GetDumpLine(n, line++)) );
	CPPUNIT_ASSERT_EQUAL( std::string("    E   -4"),                               std::string(::GetDumpLine(n, line++)) );
	CPPUNIT_ASSERT_EQUAL( std::string("    H(0)   -25.15"),                        std::string(::GetDumpLine(n, line++)) );
	CPPUNIT_ASSERT_EQUAL( std::string("    Na   -3.0255625287599"),                std::string(::GetDumpLine(n, line++)) );
	CPPUNIT_ASSERT_EQUAL( std::string("    O(0)   -42.080044167952"),              std::string(::GetDumpLine(n, line++)) );
	CPPUNIT_ASSERT_EQUAL( std::string("  -gammas"),                                std::string(::GetDumpLine(n, line++)) );
#endif

	// remaining lines should be empty
	CPPUNIT_ASSERT_EQUAL( std::string(""), std::string(::GetDumpLine(n, line++)) );
	CPPUNIT_ASSERT_EQUAL( std::string(""), std::string(::GetDumpLine(n, line++)) );
	CPPUNIT_ASSERT_EQUAL( std::string(""), std::string(::GetDumpLine(n, line++)) );
	CPPUNIT_ASSERT_EQUAL( std::string(""), std::string(::GetDumpLine(n, line++)) );

	// negative lines should be empty
	CPPUNIT_ASSERT_EQUAL( std::string(""), std::string(::GetDumpLine(n, -1)) );
	CPPUNIT_ASSERT_EQUAL( std::string(""), std::string(::GetDumpLine(n, -2)) );
	CPPUNIT_ASSERT_EQUAL( std::string(""), std::string(::GetDumpLine(n, -3)) );
	CPPUNIT_ASSERT_EQUAL( std::string(""), std::string(::GetDumpLine(n, -4)) );

	if (n >= 0)
	{
		CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::DestroyIPhreeqc(n));
	}
}

void TestIPhreeqcLib::TestGetComponentCount(void)
{
	int n = ::CreateIPhreeqc();
	CPPUNIT_ASSERT(n >= 0);

	CPPUNIT_ASSERT_EQUAL( 0,      ::LoadDatabase(n, "phreeqc.dat") );

	// add solution block
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::SOLUTION(n, 1.0, 1.0, 1.0) );

	// run
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::SetOutputOn(n, 0) );
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::SetErrorOn(n, 0) );
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::SetLogOn(n, 0) );
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::SetSelectedOutputOn(n, 0) );
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::SetDumpOn(n, 0) );
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::SetDumpStringOn(n, 0) );
	CPPUNIT_ASSERT_EQUAL( 0,      ::RunAccumulated(n) );
	CPPUNIT_ASSERT_EQUAL( 3,      ::GetComponentCount(n) );

	if (n >= 0)
	{
		CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::DestroyIPhreeqc(n));
	}
}

void TestIPhreeqcLib::TestGetComponent(void)
{
	int n = ::CreateIPhreeqc();
	CPPUNIT_ASSERT(n >= 0);

	CPPUNIT_ASSERT_EQUAL( 0,      ::LoadDatabase(n, "phreeqc.dat") );

	// add solution block
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::SOLUTION(n, 1.0, 1.0, 1.0) );

	// run
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::SetOutputOn(n, 0) );
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::SetErrorOn(n, 0) );
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::SetLogOn(n, 0) );
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::SetSelectedOutputOn(n, 0) );
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::SetDumpOn(n, 0) );
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::SetDumpStringOn(n, 0) );
	CPPUNIT_ASSERT_EQUAL( 0,      ::RunAccumulated(n) );
	CPPUNIT_ASSERT_EQUAL( 3,      ::GetComponentCount(n) );

	CPPUNIT_ASSERT_EQUAL( std::string(""),   std::string(::GetComponent(n, -2)) );
	CPPUNIT_ASSERT_EQUAL( std::string(""),   std::string(::GetComponent(n, -1)) );

	CPPUNIT_ASSERT_EQUAL( std::string("C"),  std::string(::GetComponent(n, 0)) );
	CPPUNIT_ASSERT_EQUAL( std::string("Ca"), std::string(::GetComponent(n, 1)) );
	CPPUNIT_ASSERT_EQUAL( std::string("Na"), std::string(::GetComponent(n, 2)) );

	CPPUNIT_ASSERT_EQUAL( std::string(""),   std::string(::GetComponent(n, 3)) );
	CPPUNIT_ASSERT_EQUAL( std::string(""),   std::string(::GetComponent(n, 4)) );
	CPPUNIT_ASSERT_EQUAL( std::string(""),   std::string(::GetComponent(n, 5)) );

	if (n >= 0)
	{
		CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::DestroyIPhreeqc(n));
	}
}
void TestIPhreeqcLib::TestGetErrorLine(void)
{
	int n = ::CreateIPhreeqc();
	CPPUNIT_ASSERT(n >= 0);

	CPPUNIT_ASSERT_EQUAL( 0,      ::LoadDatabase(n, "phreeqc.dat") );
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::SetOutputOn(n, 0) );
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::SetErrorOn(n, 0) );
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::SetLogOn(n, 0) );
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::SetSelectedOutputOn(n, 0) );
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::SetDumpOn(n, 0) );
	CPPUNIT_ASSERT_EQUAL( 1,      ::RunFile(n, "dump") );

	CPPUNIT_ASSERT_EQUAL( 2,      ::GetErrorLineCount(n) );
	CPPUNIT_ASSERT_EQUAL( std::string("ERROR: Gas not found in PHASES data base, Amm(g)."),    std::string(::GetErrorLine(n, 0)) );
	CPPUNIT_ASSERT_EQUAL( std::string("ERROR: Calculations terminating due to input errors."), std::string(::GetErrorLine(n, 1)) );

	if (n >= 0)
	{
		CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::DestroyIPhreeqc(n));
	}
}

void TestIPhreeqcLib::TestGetWarningLine(void)
{
	int n = ::CreateIPhreeqc();
	CPPUNIT_ASSERT(n >= 0);

	CPPUNIT_ASSERT_EQUAL( 0,      ::LoadDatabase(n, "phreeqc.dat") );
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::SetOutputOn(n, 0) );
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::SetErrorOn(n, 0) );
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::SetLogOn(n, 0) );
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::SetSelectedOutputOn(n, 0) );
	CPPUNIT_ASSERT_EQUAL( IPQ_OK, ::SetDumpOn(n, 0) );
	CPPUNIT_ASSERT_EQUAL( 1,      ::RunFile(n, "dump") );

	CPPUNIT_ASSERT_EQUAL( 5,      ::GetWarningLineCount(n) );
	CPPUNIT_ASSERT_EQUAL( std::string("WARNING: DATABASE keyword is ignored by IPhreeqc."),                              std::string(::GetWarningLine(n, 0)) );
	CPPUNIT_ASSERT_EQUAL( std::string("WARNING: Cell-lengths were read for 1 cells. Last value is used till cell 100."), std::string(::GetWarningLine(n, 1)) );
	CPPUNIT_ASSERT_EQUAL( std::string("WARNING: No dispersivities were read; disp = 0 assumed."),                        std::string(::GetWarningLine(n, 2)) );
	CPPUNIT_ASSERT_EQUAL( std::string("WARNING: Could not find element in database, Amm."),                              std::string(::GetWarningLine(n, 3)) );
	CPPUNIT_ASSERT_EQUAL( std::string("	Concentration is set to zero."),                                                 std::string(::GetWarningLine(n, 4)) );

	if (n >= 0)
	{
		CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::DestroyIPhreeqc(n));
	}
}

void TestIPhreeqcLib::TestPitzer(void)
{
	CPPUNIT_ASSERT_EQUAL(true, ::FileExists("../database/pitzer.dat"));

	int id = ::CreateIPhreeqc();
	CPPUNIT_ASSERT(id >= 0);

	CPPUNIT_ASSERT_EQUAL(::LoadDatabase(id, "../database/pitzer.dat"), 0);

	CPPUNIT_ASSERT_EQUAL(::AccumulateLine(id, "SOLUTION 1"),            IPQ_OK);
	CPPUNIT_ASSERT_EQUAL(::AccumulateLine(id, "units mol/kgw"),         IPQ_OK);
	CPPUNIT_ASSERT_EQUAL(::AccumulateLine(id, "pH    7"),               IPQ_OK);
	CPPUNIT_ASSERT_EQUAL(::AccumulateLine(id, "temp  25"),              IPQ_OK);
	CPPUNIT_ASSERT_EQUAL(::AccumulateLine(id, "Mg    0.1    charge"),   IPQ_OK);
	CPPUNIT_ASSERT_EQUAL(::AccumulateLine(id, "Cl    0"),               IPQ_OK);
	CPPUNIT_ASSERT_EQUAL(::AccumulateLine(id, "S(6)  1.0612244897959"), IPQ_OK);
	CPPUNIT_ASSERT_EQUAL(::AccumulateLine(id, "EQUILIBRIUM_PHASES 1"),  IPQ_OK);
	CPPUNIT_ASSERT_EQUAL(::AccumulateLine(id, "Halite       0 10"),     IPQ_OK);
	CPPUNIT_ASSERT_EQUAL(::AccumulateLine(id, "Sylvite      0 10"),     IPQ_OK);
	CPPUNIT_ASSERT_EQUAL(::AccumulateLine(id, "Bischofite   0 0"),      IPQ_OK);
	CPPUNIT_ASSERT_EQUAL(::AccumulateLine(id, "Carnallite   0 0"),      IPQ_OK);
	CPPUNIT_ASSERT_EQUAL(::AccumulateLine(id, "Epsomite     0 0"),      IPQ_OK);
	CPPUNIT_ASSERT_EQUAL(::AccumulateLine(id, "Kieserite    0 0"),      IPQ_OK);
	CPPUNIT_ASSERT_EQUAL(::AccumulateLine(id, "END"),                   IPQ_OK);

	// this fails -r4375
	// fixed in -r4380
	CPPUNIT_ASSERT_EQUAL(::RunAccumulated(id), 0);

	if (id >= 0)
	{
		CPPUNIT_ASSERT_EQUAL(IPQ_OK, ::DestroyIPhreeqc(id));
	}
}
