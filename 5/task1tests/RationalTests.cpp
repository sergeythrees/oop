﻿// task1tests.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../task1/Rational.h"

BOOST_AUTO_TEST_CASE(Test_Greates_Common_Denominator)
{
	BOOST_CHECK_EQUAL(GCD(2, 3), 1u);
	BOOST_CHECK_EQUAL(GCD(3, 2), 1u);
	BOOST_CHECK_EQUAL(GCD(12, 8), 4u);
	BOOST_CHECK_EQUAL(GCD(8, 12), 4u);
	BOOST_CHECK_EQUAL(GCD(0, 2), 2u);
	BOOST_CHECK_EQUAL(GCD(2, 0), 2u);
	BOOST_CHECK_EQUAL(GCD(0, 0), 1u);
}

void VerifyRational(const CRational & r, int expectedNumerator, int expectedDenominator)
{
	BOOST_CHECK_EQUAL(r.GetNumerator(), expectedNumerator);
	BOOST_CHECK_EQUAL(r.GetDenominator(), expectedDenominator);
}

void VerifyCompoundFraction(std::pair<int, CRational> const& result, int number, int expectedNumerator, int expectedDenominator)
{
	BOOST_CHECK_EQUAL(result.first, number);
	BOOST_CHECK_EQUAL(result.second.GetNumerator(), expectedNumerator);
	BOOST_CHECK_EQUAL(result.second.GetDenominator(), expectedDenominator);
}

BOOST_AUTO_TEST_SUITE(Rational_number)
	BOOST_AUTO_TEST_CASE(is_0_by_default)
	{
		VerifyRational(CRational(), 0, 1);
	}
	BOOST_AUTO_TEST_CASE(can_be_constructed_from_integer)
	{
		VerifyRational(CRational(10), 10, 1);
		VerifyRational(CRational(-10), -10, 1);
		VerifyRational(CRational(0), 0, 1);
	}
	BOOST_AUTO_TEST_CASE(can_be_constructed_with_numerator_and_denominator)
	{
		VerifyRational(CRational(5, 2), 5, 2);
		VerifyRational(CRational(-5, 2), -5, 2);
		VerifyRational(CRational(5, -2), -5, 2);
		VerifyRational(CRational(-5, -2), 5, 2);
	}
	BOOST_AUTO_TEST_CASE(is_normalized_after_construction)
	{
		VerifyRational(CRational(6, 8), 3, 4);
		VerifyRational(CRational(6, -8), -3, 4);
		VerifyRational(CRational(-6, 8), -3, 4);
		VerifyRational(CRational(-6, -8), 3, 4);
		VerifyRational(CRational(-10, 20), -1, 2);
	}
	BOOST_AUTO_TEST_CASE(cant_have_zero_denominator)
	{
		BOOST_REQUIRE_THROW(CRational(1, 0), std::invalid_argument);
	}


BOOST_AUTO_TEST_SUITE(ToDouble_function)
	BOOST_AUTO_TEST_CASE(should_convert_the_rational_number_to_double)
	{
		CRational rational(3, 5);
		BOOST_CHECK_CLOSE(rational.ToDouble(), 0.6, 0.01);
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(ToCompoundFraction_function)
BOOST_AUTO_TEST_CASE(should_convert_the_rational_number_to_compound_fraction)
{
	VerifyCompoundFraction(CRational(9, 4).ToCompoundFraction(), 2, 1, 4);
	VerifyCompoundFraction(CRational(-9, 4).ToCompoundFraction(), -2, -1, 4);
	VerifyCompoundFraction(CRational(1, 2).ToCompoundFraction(), 0, 1, 2);
}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(unary_operator_minus)
	BOOST_AUTO_TEST_CASE(should_return_the_rational_number_with_the_opposite_sign)
	{
		VerifyRational(-CRational(3, 5), -3, 5);
	}
	BOOST_AUTO_TEST_CASE(should_be_able_to_work_with_contstants)
	{
		CRational const a(3, 2);
		CRational const b(4, 7);
		VerifyRational(-a, -3, 2);
		VerifyRational(((-a) + 1) - 2, -5, 2);
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(unary_operator_plus)
	BOOST_AUTO_TEST_CASE(should_return_not_changed_rational_number)
	{
		VerifyRational(+CRational(3, 5), 3, 5);
		VerifyRational(+CRational(-3, 5), -3, 5);
	}
	BOOST_AUTO_TEST_CASE(should_be_able_to_work_with_contstants)
	{
		CRational const a(3, 2);
		CRational const b(4, 7);
		VerifyRational(+a, 3, 2);
		VerifyRational(((+a) - 1) + 2, 5, 2);
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(binary_operator_plus)
	BOOST_AUTO_TEST_CASE(should_return_the_sum_of_two_rational_numbers)
	{
		VerifyRational(CRational(1, 2) + CRational(1, 6), 2, 3);
	}
	BOOST_AUTO_TEST_CASE(should_return_the_sum_of_rational_number_and_integer)
	{
		VerifyRational(CRational(1, 2) + 1, 3, 2);
	}
	BOOST_AUTO_TEST_CASE(should_return_the_sum_of_integer_and_rational_number)
	{
		VerifyRational(1 + CRational(1, 2), 3, 2);
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(binary_operator_minus)
	BOOST_AUTO_TEST_CASE(should_return_the_complement_of_two_rational_numbers)
	{
		VerifyRational(CRational(1, 2) - CRational(1, 6), 1, 3);
	}
	BOOST_AUTO_TEST_CASE(should_return_the_complement_of_rational_number_and_integer)
	{
		VerifyRational(CRational(1, 2) - 1, -1, 2);
	}
	BOOST_AUTO_TEST_CASE(should_return_the_complement_of_integer_and_rational_number)
	{
		VerifyRational(1 - CRational(1, 2), 1, 2);
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(plus_equal_operator)
	BOOST_AUTO_TEST_CASE(should_add_second_rational_number_to_first_rational_number)
	{
		VerifyRational(CRational(1, 2) += CRational(1, 6), 2, 3);
	}
	BOOST_AUTO_TEST_CASE(should_add_integer_to_first_rational_number)
	{
		VerifyRational(CRational(1, 2) += 1, 3, 2);
	}
	BOOST_AUTO_TEST_CASE(should_be_able_to_work_with_constants)
	{
		CRational a(3, 2);
		CRational const b(3, 2);

		VerifyRational(((a += b) += b), 9, 2);
		VerifyRational(a, 9, 2);
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(minus_equal_operator)
	BOOST_AUTO_TEST_CASE(should_subtract_second_rational_number_from_first_rational_number)
	{
		VerifyRational(CRational(1, 2) -= CRational(1, 6), 1, 3);
	}
	BOOST_AUTO_TEST_CASE(should_subtract_integer_from_first_rational_number)
	{
		VerifyRational(CRational(1, 2) -= 1, -1, 2);
	}
	BOOST_AUTO_TEST_CASE(should_be_able_to_work_with_constants)
	{
		CRational a(3, 2);
		CRational const b(3, 2);

		VerifyRational(((a -= b) -= b), -3, 2);
		VerifyRational(a, -3, 2);
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(multiplicaton_operator)
	BOOST_AUTO_TEST_CASE(should_return_the_result_of_multiplicaton_two_rational_numbers)
	{
		VerifyRational(CRational(1, 2) * CRational(2, 3), 1, 3);
	}
	BOOST_AUTO_TEST_CASE(should_return_the_result_of_multiplicaton_rational_number_and_integer)
	{
		VerifyRational(CRational(1, 2) * -3, -3, 2);
	}
	BOOST_AUTO_TEST_CASE(should_return_the_result_of_multiplicaton_integer_and_rational_number)
	{
		VerifyRational(7 * CRational(2, 3), 14, 3);
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(division_operator)
	BOOST_AUTO_TEST_CASE(should_return_the_result_of_division_two_rational_numbers)
	{
		VerifyRational(CRational(1, 2) / CRational(2, 3), 3, 4);
	}
	BOOST_AUTO_TEST_CASE(should_return_the_result_of_division_rational_number_and_integer)
	{
		VerifyRational(CRational(1, 2) / 5, 1, 10);
	}
	BOOST_AUTO_TEST_CASE(should_return_the_result_of_division_integer_and_rational_number)
	{
		VerifyRational(7 / CRational(2, 3), 21, 2);
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(multiple_equal_operator)
	BOOST_AUTO_TEST_CASE(should_multiply_the_first_rational_number_by_second_rational_number)
	{
		VerifyRational(CRational(1, 2) *= CRational(2, 3), 1, 3);
	}
	BOOST_AUTO_TEST_CASE(should_multiply_the_rational_number_by_integer)
	{
		VerifyRational(CRational(1, 2) *= 3, 3, 2);
	}
	BOOST_AUTO_TEST_CASE(should_be_able_to_work_with_constants)
	{
		CRational a(3, 2);
		CRational const b(-3, 2);

		VerifyRational(((a *= b) *= b), 27, 8);
		VerifyRational(a, 27, 8);
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(division_and_equal_operator)
	BOOST_AUTO_TEST_CASE(should_divide_the_first_rational_number_by_second_rational_number)
	{
		VerifyRational(CRational(1, 2) /= CRational(2, 3), 3, 4);
	}
	BOOST_AUTO_TEST_CASE(should_divide_the_rational_number_by_integer)
	{
		VerifyRational(CRational(1, 2) /= 3, 1, 6);
	}
	BOOST_AUTO_TEST_CASE(should_be_able_to_work_with_constants)
	{
		CRational a(27, 8);
		CRational const b(-3, 2);

		VerifyRational(((a /= b) /= b), 3, 2);
		VerifyRational(a, 3, 2);
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(bool_operator_equal)
	BOOST_AUTO_TEST_CASE(should_return_true_if_two_rational_numbers_are_equal)
	{
		BOOST_CHECK(CRational(1, 2) == CRational(1, 2));
	}
	BOOST_AUTO_TEST_CASE(should_return_true_if_rational_number_and_integer_are_equal)
	{
		BOOST_CHECK(CRational(4, 1) == 4);
	}
	BOOST_AUTO_TEST_CASE(should_return_true_if_integer_and_rational_number_are_equal)
	{
		BOOST_CHECK(3 == CRational(3, 1));
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(bool_operator_not_equal)
	BOOST_AUTO_TEST_CASE(should_return_true_if_two_rational_numbers_are_not_equal)
	{
		BOOST_CHECK(CRational(1, 2) != CRational(2, 3));
	}
	BOOST_AUTO_TEST_CASE(should_return_true_if_rational_number_and_integer_are_equal)
	{
		BOOST_CHECK(CRational(1, 2) != 7);
		BOOST_CHECK(!(CRational(7, 1) != 7));
	}
	BOOST_AUTO_TEST_CASE(should_return_true_if_integer_and_rational_number_are_equal)
	{
		BOOST_CHECK(3 != CRational(2, 3));
		BOOST_CHECK(!(3 != CRational(3, 1)));
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(bool_operator_greater)
	BOOST_AUTO_TEST_CASE(should_return_true_if_first_rational_number_is_greater_than_second)
	{
		BOOST_CHECK(CRational(1, 2) > CRational(1, 3));
	}
	BOOST_AUTO_TEST_CASE(should_return_true_if_rational_number_is_greater_than_integer)
	{
		BOOST_CHECK(CRational(4, 1) > 3);
	}
	BOOST_AUTO_TEST_CASE(should_return_true_if_integer_is_greater_than_rational_number)
	{
		BOOST_CHECK(1 > CRational(1, 2));
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(bool_operator_less)
	BOOST_AUTO_TEST_CASE(should_return_true_if_first_rational_number_is_less_than_second)
	{
		BOOST_CHECK(CRational(1, 3) < CRational(1, 2));
	}
	BOOST_AUTO_TEST_CASE(should_return_true_if_rational_number_is_less_than_integer)
	{
		BOOST_CHECK(CRational(1, 2) < 1);
	}
	BOOST_AUTO_TEST_CASE(should_return_true_if_integer_is_less_than_rational_number)
	{
		BOOST_CHECK(1 < CRational(3, 2));
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(bool_operator_greater_or_equal)
	BOOST_AUTO_TEST_CASE(should_return_true_if_first_rational_number_is_greater_than_second_or_they_are_equal)
	{
		BOOST_CHECK(CRational(1, 2) >= CRational(1, 3));
		BOOST_CHECK(CRational(1, 2) >= CRational(1, 2));
	}
	BOOST_AUTO_TEST_CASE(should_return_true_if_rational_number_is_greater_than_integer_or_they_are_equal)
	{
		BOOST_CHECK(CRational(4, 1) >= 3);
		BOOST_CHECK(CRational(3, 1) >= 3);
	}
	BOOST_AUTO_TEST_CASE(should_return_true_if_integer_is_greater_than_rational_number_or_they_are_equal)
	{
		BOOST_CHECK(1 >= CRational(1, 2));
		BOOST_CHECK(2 >= CRational(2, 1));
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(bool_operator_less_or_equal)
	BOOST_AUTO_TEST_CASE(should_return_true_if_first_rational_number_is_less_than_second_or_they_are_equal)
	{
		BOOST_CHECK(CRational(1, 3) <= CRational(1, 2));
		BOOST_CHECK(CRational(1, 3) <= CRational(1, 3));
	}
	BOOST_AUTO_TEST_CASE(should_return_true_if_rational_number_is_less_than_integer_or_they_are_equal)
	{
		BOOST_CHECK(CRational(1, 2) <= 1);
		BOOST_CHECK(CRational(2, 1) <= 2);
	}
	BOOST_AUTO_TEST_CASE(should_return_true_if_integer_is_less_than_rational_number_or_they_are_equal)
	{
		BOOST_CHECK(1 <= CRational(3, 2));
		BOOST_CHECK(2 <= CRational(2, 1));
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(output_operator)
	BOOST_AUTO_TEST_CASE(should_output_the_rational_number_in_the_stream)
	{
		std::stringstream output = std::stringstream();
		output << CRational(7,15);
		BOOST_CHECK_EQUAL(output.str(), "7/15");
	}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
