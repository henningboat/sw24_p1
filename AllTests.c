#include <stdio.h>

#include "CuTest.h"
#include "model_input.h"
#include "travel_time.h"
#include "path_finding.h"

CuSuite* CuGetSuite();
CuSuite* CuStringGetSuite();
/*
void RunAllTests(void)
{
	CuString *output = CuStringNew();
	CuSuite* suite = CuSuiteNew();

	CuSuiteAddSuite(suite, CuGetSuite());
	CuSuiteAddSuite(suite, CuStringGetSuite());

	CuSuiteRun(suite);
	CuSuiteSummary(suite, output);
	CuSuiteDetails(suite, output);
	printf("%s\n", output->buffer);
}*/
void RunAllTests(void) {
	CuString *output = CuStringNew();
	CuSuite *suite = CuSuiteNew();

	//Adding test suites:
	//TravelTime test
	CuSuiteAddSuite(suite, (CuSuite *)test_calc_GetSuite());

	//PathFinding test
	CuSuiteAddSuite(suite, (CuSuite *)test_path_GetSuite());

	//Integration Test
	//CuSuiteAddSuite(suite, (CuSuite *)test_integration_suite());



	CuSuiteRun(suite);
	CuSuiteSummary(suite, output);
	CuSuiteDetails(suite, output);
	printf("%s\n", output->buffer);
}

/*
int main(void)
{
	RunAllTests();
}
*/