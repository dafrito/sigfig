#include <cxxtest/TestSuite.h>
#include "SigFig.h"
#include <cmath>

using namespace std;

class PhysicsTests : public CxxTest::TestSuite
{
public:
	void testEqualNumbers()
	{
		TS_ASSERT_EQUALS(SigFig(2), SigFig(2));
		TS_ASSERT_EQUALS(SigFig(2, 3), SigFig(2, 3));
	}

	void testBasicProperties()
	{
		TS_ASSERT_EQUALS(SigFig(1).signum(), 1);
		TS_ASSERT_EQUALS(SigFig(-200).signum(), -1);
	}

	void testSigFigHasUnitValues()
	{
		TS_ASSERT_EQUALS(SigFig(5).unit(), SigFig(1));
		TS_ASSERT_EQUALS(SigFig(500, 2).unit(), SigFig(pow(10, 2), 2));
	}

	void testUnequalNumbers()
	{
		TS_ASSERT_DIFFERS(SigFig(1), SigFig(2));
		TS_ASSERT_DIFFERS(SigFig(34), SigFig(42));
		TS_ASSERT_DIFFERS(SigFig(1), SigFig(1, -3));
	}

	void testEqualNumbersCanBeFuzzy()
	{
		TS_ASSERT_EQUALS(SigFig(30, 1), SigFig(34, 1));
		TS_ASSERT_EQUALS(SigFig(-30, 1), SigFig(-34, 1));
	}

	void testFindAnBestValueOfASigFig()
	{
		TS_ASSERT_EQUALS(SigFig(12, 1).value(), 10.0);
		TS_ASSERT_EQUALS(SigFig(22, 1).value(), 20.0);
		TS_ASSERT_EQUALS(SigFig(-28, 1).value(), -30.0);
	}

	void testAddingTwoSigFigs()
	{
		TS_ASSERT_EQUALS(SigFig(1) + SigFig(1), SigFig(2));
		TS_ASSERT_EQUALS(SigFig(1) + SigFig(-1), SigFig(0));
	}

	void testAddingASigFig()
	{
		SigFig a(14);
		a += 3;
		TS_ASSERT_EQUALS(a, SigFig(17));
	}

	void testSubtractingSigFigs()
	{
		TS_ASSERT_EQUALS(SigFig(3) - SigFig(1), SigFig(2));
	}

	void testSubtractingFromASigFig()
	{
		SigFig a(14);
		a -= 3;
		TS_ASSERT_EQUALS(a, SigFig(11));
	}

	void testPrefixIncrementingASigFig()
	{
		SigFig a(10, 1);
		TS_ASSERT_EQUALS(++a, SigFig(20, 1));
		SigFig b(10, -1);
		TS_ASSERT_EQUALS(++b, SigFig(10.1, -1));
	}

	void testPostfixIncrementingASigFig()
	{
		SigFig a(10, 1);
		TS_ASSERT_EQUALS(a++, SigFig(20, 1));
		TS_ASSERT_EQUALS(a, SigFig(10, 1));
	}

	void testDecrementingASigFig()
	{
		SigFig a(10.1, -1);
		TS_ASSERT_EQUALS(a--, SigFig(10, 1));
	}
};
