#include "stdafx.h"
#include "..\CMyStack\CMyStack.h"
#include <list>

CStack<std::string> strStack;
CStack<int> intStack;
CStack<float> floatStack;

BOOST_AUTO_TEST_SUITE(Stack_can)

	BOOST_AUTO_TEST_SUITE(push_and_return_elements)

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

	BOOST_AUTO_TEST_SUITE(pop_elements_when)

		BOOST_AUTO_TEST_CASE(stack_is_not_empty)
		{
			CStack<int> numbersStack;
			int start = 0;
			int end = 10;

			for (int number = start; number <= end; number++)
			{
				numbersStack.Push(number);
			}

			for (int reverseNumber = end - 1; reverseNumber >= start; reverseNumber--)
			{
				numbersStack.Pop();
				BOOST_CHECK_EQUAL(reverseNumber, numbersStack.GetTop());
			}
		}

		BOOST_AUTO_TEST_CASE(stack_is_empty)
		{
			CStack<float> floatStack;
			BOOST_REQUIRE_NO_THROW(floatStack.Pop());
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(return_information_about_empty_when)

		BOOST_AUTO_TEST_CASE(stack_is_empty)
		{
			CStack<std::string> stack;
			BOOST_CHECK(stack.Empty());
		}

		BOOST_AUTO_TEST_CASE(stack_is_not_empty)
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

	BOOST_AUTO_TEST_CASE(stack_is_empty)
	{
		CStack<std::string> stack;
		stack.Clear();
		BOOST_CHECK(stack.Empty());
	}

	BOOST_AUTO_TEST_CASE(stack_is_not_empty)
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
		CStack<std::string> movingStack;
		movingStack.Push("string");
		CStack<std::string> newStack(std::move(movingStack));

		BOOST_CHECK_EQUAL(newStack.GetTop(), "string");
		BOOST_REQUIRE_THROW(movingStack.GetTop(), std::logic_error);
	}

	BOOST_AUTO_TEST_CASE(copied_assign_operator)
	{
		CStack<int> stackForInsertion;
		CStack<int> copiedStack;

		for (int i = -10; i < 10; i++)
		{
			stackForInsertion.Push(1);
			copiedStack.Push(1);
		}

		stackForInsertion = copiedStack;

		while (!stackForInsertion.Empty() && !copiedStack.Empty())
		{
			BOOST_CHECK_EQUAL(stackForInsertion.GetTop(), copiedStack.GetTop());
			stackForInsertion.Pop();
			copiedStack.Pop();
		}
	}

	BOOST_AUTO_TEST_CASE(moving_assign_operator)
	{
		CStack<int> stackForInsertion;
		CStack<int> movingStack;

		for (int i = -10; i < 10; i++)
		{
			movingStack.Push(1);
		}

		BOOST_CHECK_NO_THROW(movingStack.GetTop());
		stackForInsertion = std::move(movingStack);
		BOOST_REQUIRE_THROW(movingStack.GetTop(), std::logic_error);

		while (!stackForInsertion.Empty())
		{
			BOOST_CHECK_EQUAL(stackForInsertion.GetTop(), 1);
			stackForInsertion.Pop();
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

BOOST_AUTO_TEST_SUITE(Stack_copied_assign_operator)

	BOOST_AUTO_TEST_CASE(can_work_with_itself)
	{
		const float number = 12.0099f;
		CStack<float> simpleStack;
		simpleStack.Push(number);

		simpleStack = simpleStack;

		BOOST_CHECK_EQUAL(simpleStack.GetTop(), number);
		simpleStack.Pop();
		BOOST_REQUIRE_THROW(simpleStack.GetTop(), std::logic_error);
	}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Stack_moving_assign_operator)

	BOOST_AUTO_TEST_CASE(can_work_with_itself)
	{
		const float number = 12.0099f;
		CStack<float> simpleStack;
		simpleStack.Push(number);

		simpleStack = std::move(simpleStack);

		BOOST_CHECK_EQUAL(simpleStack.GetTop(), number);
		simpleStack.Pop();
		BOOST_REQUIRE_THROW(simpleStack.GetTop(), std::logic_error);
	}

BOOST_AUTO_TEST_SUITE_END()