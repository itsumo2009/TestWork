#include "verylonginteger.h"

#include <gtest/gtest.h>

TEST(VeryLongIntegerTest, shouldBeConstructFromDigitsVector)
{
    VeryLongInteger sample(QVector<qint64>({1,1}));
    EXPECT_EQ(sample.toString(), "1000000000000000001");
}

TEST(VeryLongIntegerTest, shouldCorrectAdding)
{
    VeryLongInteger left(QVector<qint64>({1,1}));
    VeryLongInteger right(QVector<qint64>({12,12}));
    left+=right;
    EXPECT_EQ(left.toString(), "13000000000000000013");
}

TEST(VeryLongIntegerTest, shouldCorrectAddingWhenOverflow)
{
    VeryLongInteger left(QVector<qint64>({1,1}));
    VeryLongInteger right(QVector<qint64>({11,1000000000000000000-1}));
    left+=right;
    EXPECT_EQ(left.toString(), "13000000000000000000");
}

TEST(VeryLongIntegerTest, shouldCorrectAddingDigitWhenOverflow)
{
    VeryLongInteger left(1);
    VeryLongInteger right(1000000000000000000-1);
    left+=right;
    EXPECT_EQ(left.toString(), "1000000000000000000");
}

TEST(VeryLongIntegerTest, shouldCorrectAddingNegativeNumber)
{
    VeryLongInteger left(1);
    VeryLongInteger right(-1000000000000000001);
    left+=right;
    EXPECT_EQ(left.toString(), "-1000000000000000000");
}
