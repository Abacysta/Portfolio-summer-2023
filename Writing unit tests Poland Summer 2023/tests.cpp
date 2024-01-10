#include <gtest/gtest.h>
#include <vector>
#include <algorithm>

int GetProductsAmount(std::vector<int>& prices, int amountOfMoney)
{
    std::sort(prices.begin(), prices.end());
    int sum = 0;
    for (int i = 0; i < prices.size(); ++i)
    {
        sum += prices[i];
        if (sum > amountOfMoney)
        {
            return i;
        }
    }
    return prices.size();
}


TEST(GetProductsAmount, EmptyVector) {
    std::vector<int> prices = {};
    ASSERT_EQ(GetProductsAmount(prices, 10), 0);
}

TEST(GetProductsAmount, NotEnoughMoneyForAnyProduct) {
    std::vector<int> prices = { 5, 7, 9 };
    ASSERT_EQ(GetProductsAmount(prices, 4), 0);
}

TEST(GetProductsAmount, ExactMoneyForOneProduct) {
    std::vector<int> prices = { 5, 7, 9 };
    ASSERT_EQ(GetProductsAmount(prices, 5), 1);
}

TEST(GetProductsAmount, EnoughMoneyForAllProducts) {
    std::vector<int> prices = { 5, 7, 9 };
    ASSERT_EQ(GetProductsAmount(prices, 50), 3);
}

TEST(GetProductsAmount, EnoughMoneyForSomeProducts) {
    std::vector<int> prices = { 5, 7, 9 };
    ASSERT_EQ(GetProductsAmount(prices, 20), 2);
}


bool IsLeapYear(int year)
{
    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
        return true;
    else
        return false;
}

TEST(IsLeapYear, NonLeapYear) {
    ASSERT_FALSE(IsLeapYear(1997));
}

TEST(IsLeapYear, LeapYearDivisibleBy4) {
    ASSERT_TRUE(IsLeapYear(1996));
}

TEST(IsLeapYear, LeapYearDivisibleBy100ButNot400) {
    ASSERT_FALSE(IsLeapYear(1900));
}

TEST(IsLeapYear, LeapYearDivisibleBy400) {
    ASSERT_TRUE(IsLeapYear(2000));
}
