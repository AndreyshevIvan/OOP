#include "stdafx.h"
#include "..\CMyStack\CMyStack.h"
#include <list>

CStack<std::string> strStack;
CStack<int> intStack;
CStack<float> floatStack;

BOOST_AUTO_TEST_SUITE(Stack_can)

	BOOST_AUTO_TEST_SUITE(push_and_return)

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

	BOOST_AUTO_TEST_SUITE(return_information_about_empty_when)

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

	BOOST_AUTO_TEST_SUITE(be_destroyed)

		BOOST_AUTO_TEST_CASE(without_stack_overflow_exception)
		{
			CStack<float> floatStack;
			float fNum = 13.33f;
			size_t elemCount = 20000;

			for (size_t i = 0; i < elemCount; i++)
			{
				floatStack.Push(fNum);
			}

			BOOST_CHECK_NO_THROW(floatStack.~CStack());
		}

	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Clear_stack_when)

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

BOOST_AUTO_TEST_SUITE(Stack_have)

	BOOST_AUTO_TEST_CASE(copy_constructor)
	{
		CStack<std::string> copiedStack;
		copiedStack.Push("Hello");
		copiedStack.Push("World!");

		CStack<std::string> newStack(copiedStack);

		BOOST_CHECK_EQUAL(copiedStack.GetTop(), newStack.GetTop());
		BOOST_CHECK_EQUAL(copiedStack.GetTop(), newStack.GetTop());
	}

	BOOST_AUTO_TEST_CASE(move_constructor)
	{
		CStack<std::string> moveingStack;
		moveingStack.Push("string");
		CStack<std::string> newStack(std::move(moveingStack));

		BOOST_CHECK_EQUAL(newStack.GetTop(), "string");
		BOOST_REQUIRE_THROW(moveingStack.GetTop(), std::logic_error);
	}

	BOOST_AUTO_TEST_CASE(copied_assign_operator)
	{
		CStack<int> pasteStack;
		CStack<int> copiedStack;

		for (int i = -10; i < 10; i++)
		{
			pasteStack.Push(1);
			copiedStack.Push(1);
		}

		pasteStack = copiedStack;

		while (!pasteStack.Empty() && !copiedStack.Empty())
		{
			BOOST_CHECK_EQUAL(pasteStack.GetTop(), copiedStack.GetTop());
			pasteStack.Pop();
			copiedStack.Pop();
		}
	}

	BOOST_AUTO_TEST_CASE(moveing_assign_operator)
	{
		CStack<int> pasteStack;
		CStack<int> moveingStack;

		for (int i = -10; i < 10; i++)
		{
			moveingStack.Push(1);
		}

		BOOST_CHECK_NO_THROW(moveingStack.GetTop());
		pasteStack = std::move(moveingStack);
		BOOST_REQUIRE_THROW(moveingStack.GetTop(), std::logic_error);

		while (!pasteStack.Empty())
		{
			BOOST_CHECK_EQUAL(pasteStack.GetTop(), 1);
			pasteStack.Pop();
		}
	}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Stack_can_throw_exception_when_)

	BOOST_AUTO_TEST_CASE(get_top_from_empty_stack)
	{
		CStack<std::string> stack;
		BOOST_REQUIRE_THROW(stack.GetTop(), std::logic_error);
	}

BOOST_AUTO_TEST_SUITE_END()