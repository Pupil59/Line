#include "pch.h"
#include "CppUnitTest.h"
#include "C:\Users\LY59\Desktop\Line\MyLine\MyLine\main.cpp"
#include "C:\Users\LY59\Desktop\Line\MyLine\MyLine\global.h"
#include "C:\Users\LY59\Desktop\Line\MyLine\MyLine\global.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MyLineUnitTest
{
	TEST_CLASS(MyLineUnitTest)
	{
	public:
		
		//tool func test
		TEST_METHOD(TestMethod1)
		{
			pair<int, int> ret = getPair(5, 10);
			Assert::IsTrue(ret.first == 1 && ret.second == 2);
			ret = getPair(13, 2);
			Assert::IsTrue(ret.first == 13 && ret.second == 2);
			ret = getPair(0, 20);
			Assert::IsTrue(ret.first == 0 && ret.second == 1);
			ret = getPair(20, 0);
			Assert::IsTrue(ret.first == 1 && ret.second == 0);
			ret = getPair(0, 0);
			Assert::IsTrue(ret.first == 0 && ret.second == 0);
		}
		//line-line test
		TEST_METHOD(TestMethod2)
		{
			int ret;
			//test case 1
			initLineList(1, 1, 0, 0);
			initLineList(1, 0, 0, 1);
			initLineList(1, 2, 2, 0);
			Line_intersection();
			ret = PointList.size();
			Assert::IsTrue(ret == 3);
			initLineList(3, 1, 3, 999);
			initLineList(999, -2, -999, -2);
			Line_intersection();
			ret = PointList.size();
			Assert::IsTrue(ret == 5);
			PointList.clear();
			LineList.clear();

			//test case 2
			initLineList(0, 0, 1, 0);
			initLineList(0, 1, 0, 0);
			initLineList(99998, 11, 0, 10);
			initLineList(1, -99989, 0, 10);
			Line_intersection();
			ret = PointList.size();
			Assert::IsTrue(ret == 4);
			PointList.clear();
			LineList.clear();

			//test case 3
			initLineList(0, 5, 1, 5);
			initLineList(10, 1, 10, 2);
			initLineList(0, 0, 0, 1);
			initLineList(-12, 0, -10, 5);
			Line_intersection();
			ret = PointList.size();
			Assert::IsTrue(ret == 5);
			PointList.clear();
			LineList.clear();

		}
		//circle-circle test
		TEST_METHOD(TestMethod3)
		{
			int ret;
			//test case1
			initCircleList(5, 0, 5);
			initCircleList(0, 0, 10);
			initCircleList(-5, 0, 5);
			Circle_intersection();
			ret = floatPointList.size();
			Assert::IsTrue(ret == 3);
			CircleList.clear();
			floatPointList.clear();

			//test case2
			initCircleList(0, 5, 5);
			initCircleList(0, 0, 10);
			initCircleList(0, -15, 5);
			initCircleList(0, -1, 1);
			Circle_intersection();
			ret = floatPointList.size();
			Assert::IsTrue(ret == 3);
			CircleList.clear();
			floatPointList.clear();

			//test case3
			initCircleList(0, 5, 2);
			initCircleList(0, 0, 2);
			initCircleList(0, -5, 2);
			Circle_intersection();
			ret = floatPointList.size();
			Assert::IsTrue(ret == 0);
			initCircleList(0, 0, 7);
			Circle_intersection();
			ret = floatPointList.size();
			Assert::IsTrue(ret == 2);
			CircleList.clear();
			floatPointList.clear();

			//test case4
			initCircleList(1, 0, 2);
			initCircleList(2, 2, 1);
			initCircleList(3, -2, 6);
			Circle_intersection();
			ret = floatPointList.size();
			Assert::IsTrue(ret == 2);
			CircleList.clear();
			floatPointList.clear();

		}
		TEST_METHOD(TestMethod4)
		{
			int ret;
			//test case 1
			initCircleList(1, 0, 2);
			initCircleList(2, 2, 1);
			initCircleList(3, -2, 6);
			initLineList(-1, 4, 4, -1);
			Circle_intersection();
			CirLine_intersection();
			ret = floatPointList.size();
			Assert::IsTrue(ret == 6);
			LineList.clear();
			CircleList.clear();
			floatPointList.clear();

			//test case2

			initCircleList(5, 0, 5);
			initCircleList(0, 0, 10);
			initCircleList(-5, 0, 5);
			initLineList(0, 5, 1, 5);
			initLineList(10, 1, 10, 2);
			initLineList(0, 0, 0, 1);
			initLineList(-12, 0, -10, 5);
			Line_intersection();
			PointList2float();
			Circle_intersection();
			CirLine_intersection();
			ret = floatPointList.size();
			Assert::IsTrue(ret == 14);
			CircleList.clear();
			floatPointList.clear();
		}
	};
}
