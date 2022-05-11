#include "verylonginteger.h"

#include <gtest/gtest.h>

TEST(VeryLongIntegerTests, defaultShouldBeEqualZero)
{
    VeryLongInteger sample;
    EXPECT_EQ(sample.toString(), "0");
}

TEST(VeryLongIntegerTests, shouldBeConstructFromInt64)
{
    VeryLongInteger sample(1000000000000000002LL);
    EXPECT_EQ(sample.toString(), "1000000000000000002");
}

TEST(VeryLongIntegerTests, shouldBeConstructFromDigitsVector)
{
    VeryLongInteger sample(QVector<qint64>({1,21}));
    EXPECT_EQ(sample.toString(), "1000000000000000021");
}

TEST(VeryLongIntegerTests, shouldBeConstructFromString)
{
    VeryLongInteger sample(QString("1000000000000000021"));
    EXPECT_EQ(sample.toString(), "1000000000000000021");
}

TEST(VeryLongIntegerTests, shouldCorrectCompareNumbersWithLessOperator)
{
    VeryLongInteger sample(QString("1000000000000000021"));
    EXPECT_EQ(sample.toString(), "1000000000000000021");
}

TEST(VeryLongIntegerTests, shouldCorrectAdding)
{
    VeryLongInteger left(QVector<qint64>({1,1}));
    VeryLongInteger right(QVector<qint64>({12,12}));
    left+=right;
    EXPECT_EQ(left.toString(), "13000000000000000013");
}

TEST(VeryLongIntegerTests, shouldCorrectAddingWhenOverflow)
{
    VeryLongInteger left(QVector<qint64>({1,1}));
    VeryLongInteger right(QVector<qint64>({11,1000000000000000000-1}));
    left+=right;
    EXPECT_EQ(left.toString(), "13000000000000000000");
}

TEST(VeryLongIntegerTests, shouldCorrectAddingDigitWhenOverflow)
{
    VeryLongInteger left(1);
    VeryLongInteger right(1000000000000000000-1);
    left+=right;
    EXPECT_EQ(left.toString(), "1000000000000000000");
}

TEST(VeryLongIntegerTests, shouldCorrectAddingNegativeNumber)
{
    VeryLongInteger left(1);
    VeryLongInteger left_2(1000000000000000002);
    VeryLongInteger left_3(1000000000000000001);
    VeryLongInteger right(-1000000000000000001);
    left+=right;
    EXPECT_EQ(left.toString(), "-1000000000000000000");
    left_2+=right;
    EXPECT_EQ(left_2.toString(), "1");
    left_3+=right;
    EXPECT_EQ(left_3.toString(), "0");
}

TEST(VeryLongIntegerTests, shouldCorrectTrivialSubstract)
{
    VeryLongInteger left(QVector<qint64>({13,13}));
    VeryLongInteger right(QVector<qint64>({12,12}));
    left-=right;
    EXPECT_EQ(left.toString(), "1000000000000000001");
}

TEST(VeryLongIntegerTests, shouldCorrectSubstractWithOverflow)
{
    VeryLongInteger left(QVector<qint64>({12,12}));
    VeryLongInteger right(QVector<qint64>({13,13}));
    left-=right;
    EXPECT_EQ(left.toString(), "-1000000000000000001");
}

TEST(VeryLongIntegerTests, shouldCorrectSubstractNegativeNumber)
{
    VeryLongInteger left(-1);
    VeryLongInteger left_2(-1000000000000000002);
    VeryLongInteger left_3(-1000000000000000001);
    VeryLongInteger right(-1000000000000000001);
    left-=right;
    EXPECT_EQ(left.toString(), "1000000000000000000");
    left_2-=right;
    EXPECT_EQ(left_2.toString(), "-1");
    left_3-=right;
    EXPECT_EQ(left_3.toString(), "0");
}

TEST(VeryLongIntegerTests, shouldCorrectCompareNegativeAndPositive)
{
    VeryLongInteger left(1);
    VeryLongInteger right(-1000000000000000001);
    EXPECT_GT(left, right);
    EXPECT_LT(right, left);
    EXPECT_NE(left, right);
}

TEST(VeryLongIntegerTests, shouldCorrectComparePositive)
{
    VeryLongInteger left(1);
    VeryLongInteger right(1000000000000000001);
    EXPECT_LT(left, right);
    EXPECT_GT(right, left);
    EXPECT_NE(left, right);
}

TEST(VeryLongIntegerTests, shouldCorrectCompareNegative)
{
    VeryLongInteger left(-1);
    VeryLongInteger right(-1000000000000000001);
    EXPECT_GT(left, right);
    EXPECT_LT(right, left);
    EXPECT_NE(left, right);
}
