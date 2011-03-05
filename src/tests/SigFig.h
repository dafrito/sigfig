#include <cxxtest/TestSuite.h>
#include "../SigFig.h"
#include <cmath>

using namespace std;

class PhysicsTests : public CxxTest::TestSuite
{
public:
	void testExactlyEqualNumbersAreEqual()
	{
		TS_ASSERT_EQUALS(SigFig(2), SigFig(2));
		TS_ASSERT_EQUALS(SigFig(2, 3), SigFig(2, 3));
	}

	void testSignumReturnsTheSign()
	{
		TS_ASSERT_EQUALS(SigFig(1).signum(), 1);
		TS_ASSERT_EQUALS(SigFig(-200).signum(), -1);
	}

	void testUnitOfASigFigIsBasedOffItsPrecision()
	{
		TS_ASSERT_EQUALS(SigFig(5).unit(), SigFig(1));
		TS_ASSERT_EQUALS(SigFig(500, 2).unit(), SigFig(pow(10, 2), 2));
	}

	void testSufficientlyUnequalValuesAreUnequal()
	{
		TS_ASSERT_DIFFERS(SigFig(1), SigFig(2));
		TS_ASSERT_DIFFERS(SigFig(34), SigFig(42));
	}


	void testPrecisionMattersWhenDeterminingEquality()
	{
		TS_ASSERT_DIFFERS(SigFig(1), SigFig(1, -3));
	}

	void testEqualNumbersCanBeFuzzy()
	{
		TS_ASSERT_EQUALS(SigFig(30, 1), SigFig(34, 1));
		TS_ASSERT_EQUALS(SigFig(-30, 1), SigFig(-34, 1));
	}

	void testValueOfASigFigCanBeRounded()
	{
		TS_ASSERT_EQUALS(SigFig(12, 1).value(), 10.0);
		TS_ASSERT_EQUALS(SigFig(22, 1).value(), 20.0);
		TS_ASSERT_EQUALS(SigFig(-28, 1).value(), -30.0);
	}

	void testAdditionAndSubtractionWorkNormally()
	{
		TS_ASSERT_EQUALS(SigFig(2) + SigFig(3), SigFig(5));
		TS_ASSERT_EQUALS(SigFig(3) - SigFig(1), SigFig(2));
		SigFig a(14);
		a -= SigFig(3);
		TS_ASSERT_EQUALS(a, SigFig(11));
		a += SigFig(3);
		TS_ASSERT_EQUALS(a, SigFig(14));
	}

	void testWorkingWithImpreciseValuesCanLeadToNoops()
	{
		TS_ASSERT_EQUALS(SigFig(100, 2) + SigFig(1), SigFig(100, 2));
		TS_ASSERT_EQUALS(SigFig(300, 2) - SigFig(1), SigFig(300, 2));
		SigFig a(50, 1);
		a += SigFig(1);
		TS_ASSERT_EQUALS(a, SigFig(50, 1));
		a -= SigFig(1);
		TS_ASSERT_EQUALS(a, SigFig(50, 1));
	}

	void testSigFigsIncrementByTheirUnits()
	{
		SigFig a(10, 1);
		TS_ASSERT_EQUALS(a++, SigFig(20, 1));
		++a;
		TS_ASSERT_EQUALS(a, SigFig(20, 1));
	}

	void testSigFigsDecrementByTheirUnits()
	{
		SigFig a(10.1, -1);
		TS_ASSERT_EQUALS(a--, SigFig(10, -1));
		--a;
		TS_ASSERT_EQUALS(a, SigFig(10, -1));
	}
};
