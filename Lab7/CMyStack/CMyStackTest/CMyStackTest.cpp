#include "stdafx.h"
#include "..\CMyStack\CMyStack.h"

CStack<std::string> strStack;
CStack<int> intStack;
CStack<float> floatStack;

BOOST_AUTO_TEST_SUITE(stack_can_push_and_return_)

	BOOST_AUTO_TEST_CASE(string)
	{
		std::string pushStr = "Hello!";
		strStack.Push(pushStr);
		BOOST_CHECK_EQUAL(pushStr, strStack.GetTop());
	}

	BOOST_AUTO_TEST_CASE(integer_number)
	{
		int pushInt = 1000;
		intStack.Push(pushInt);
		BOOST_CHECK_EQUAL(pushInt, intStack.GetTop());
	}

	BOOST_AUTO_TEST_CASE(float_number)
	{
		float pushFloat = 13.37f;
		floatStack.Push(pushFloat);
		BOOST_CHECK_EQUAL(pushFloat, floatStack.GetTop());
	}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(stack_can_return_information_about_empty_when_)

	BOOST_AUTO_TEST_CASE(stack_empty)
	{
		CStack<std::string> stack;
		BOOST_CHECK(stack.Empty());
	}

	BOOST_AUTO_TEST_CASE(stack_not_empty)
	{
		CStack<int> stack;
		stack.Push(1000);
		BOOST_CHECK(!stack.Empty());
	}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(clear_stack_when_)

	BOOST_AUTO_TEST_CASE(stack_empty)
	{
		CStack<std::string> stack;
		stack.Clear();
		BOOST_CHECK(stack.Empty());
	}

	BOOST_AUTO_TEST_CASE(stack_not_empty)
	{
		CStack<std::string> stack;
		stack.Push("Hello");
		stack.Push("World!");
		stack.Clear();
		BOOST_CHECK(stack.Empty());
	}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(stack_have_)

	BOOST_AUTO_TEST_CASE(copy_constructor)
	{
		CStack<std::string> copiedStack;
		copiedStack.Push("Hello");
		copiedStack.Push("World!");

		CStack<std::string> newStack(copiedStack);
		
		BOOST_CHECK_EQUAL(copiedStack.GetTop(), newStack.GetTop());
		BOOST_CHECK_EQUAL(copiedStack.GetTop(), newStack.GetTop());
		copiedStack.Clear();
		newStack.Clear();
		BOOST_CHECK(copiedStack.Empty());
		BOOST_CHECK(newStack.Empty());
	}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(stack_can_throw_exception_when_)

	BOOST_AUTO_TEST_CASE(get_top_from_empty_stack)
	{
		CStack<std::string> stack;
		BOOST_REQUIRE_THROW(stack.GetTop(), std::logic_error);
	}

	BOOST_AUTO_TEST_CASE(pop_empty_stack)
	{
		CStack<std::string> stack;
		BOOST_REQUIRE_THROW(stack.Pop(), std::logic_error);

		stack.Push("Hello");
		stack.Push("World!");
		stack.Pop();
		stack.Pop();
		BOOST_REQUIRE_THROW(stack.Pop(), std::logic_error);
	}

BOOST_AUTO_TEST_SUITE_END()
