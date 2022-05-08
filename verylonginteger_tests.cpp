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
    VeryLongInteger right(-1000000000000000001);
    left+=right;
    EXPECT_EQ(left.toString(), "-1000000000000000000");
}
