#include <cmath>
#include <limits>

#include <gtest/gtest.h>

#include <QDebug>

#include "geodetic.h"

using namespace md::domain;

struct TestArgs
{
    double latitude;
    double longitude;
    double altitude;
    QString datum;
};

class GeodeticTest : public ::testing::TestWithParam<TestArgs>
{
public:
    GeodeticTest()
    {
    }
};

INSTANTIATE_TEST_SUITE_P(
    instantiation, GeodeticTest,
    ::testing::Values(TestArgs({ 44.5432, 31.2344, 4584.56, geo::datums::wgs84 }),
                      TestArgs({ -18.1283, -164.8748, 202.82, geo::datums::wgs84 }),
                      TestArgs({ 0, 0, 0, "" }),
                      TestArgs({ std::numeric_limits<double>::quiet_NaN(),
                                 std::numeric_limits<double>::quiet_NaN(), 0, "" }),
                      TestArgs({ std::numeric_limits<double>::quiet_NaN(),
                                 std::numeric_limits<double>::quiet_NaN(),
                                 std::numeric_limits<double>::quiet_NaN(), "" })));

TEST_P(GeodeticTest, testToVariant)
{
    TestArgs args = GetParam();

    Geodetic geodetic(args.latitude, args.longitude, args.altitude, args.datum);
    QVariantMap map = geodetic.toVariantMap();

    if (geodetic.isValidPosition())
    {
        EXPECT_DOUBLE_EQ(map.value(geo::latitude).toDouble(), args.latitude);
        EXPECT_DOUBLE_EQ(map.value(geo::longitude).toDouble(), args.longitude);
    }
    else
    {
        EXPECT_TRUE(std::isnan(map.value(geo::latitude).toDouble()));
        EXPECT_TRUE(std::isnan(map.value(geo::longitude).toDouble()));
    }

    if (geodetic.isValidAltitude())
    {
        EXPECT_FLOAT_EQ(map.value(geo::altitude).toDouble(), args.altitude);
    }
    else
    {
        EXPECT_TRUE(std::isnan(map.value(geo::altitude).toDouble()));
    }

    EXPECT_EQ(map.value(geo::datum).toString(), args.datum);
}

TEST_P(GeodeticTest, testFromVariant)
{
    TestArgs args = GetParam();

    QVariantMap map({ { geo::latitude, args.latitude },
                      { geo::longitude, args.longitude },
                      { geo::altitude, args.altitude },
                      { geo::datum, args.datum } });
    Geodetic geodetic(map);

    if (geodetic.isValidPosition())
    {
        EXPECT_DOUBLE_EQ(geodetic.latitude(), args.latitude);
        EXPECT_DOUBLE_EQ(geodetic.longitude(), args.longitude);
    }

    if (geodetic.isValidAltitude())
    {
        EXPECT_FLOAT_EQ(geodetic.altitude(), args.altitude);
    }

    EXPECT_EQ(geodetic.datum(), args.datum);
}

TEST_P(GeodeticTest, testEquality)
{
    TestArgs args = GetParam();

    Geodetic first(args.latitude, args.longitude, args.altitude, args.datum);
    Geodetic second(first.toVariantMap());

    if (first.isValidPosition())
    {
        EXPECT_DOUBLE_EQ(first.latitude(), second.latitude());
        EXPECT_DOUBLE_EQ(first.longitude(), second.longitude());
    }
    else
    {
        EXPECT_TRUE(!second.isValidPosition());
    }

    if (first.isValidAltitude())
    {
        EXPECT_FLOAT_EQ(first.altitude(), second.altitude());
    }
    else
    {
        EXPECT_TRUE(!second.isValidAltitude());
    }

    if (first.isValid() && second.isValid())
    {
        EXPECT_TRUE(first == second);
    }

    EXPECT_EQ(first.datum(), second.datum());
}

TEST_P(GeodeticTest, testNedPointZero)
{
    TestArgs args = GetParam();
    if (args.datum != geo::datums::wgs84)
        return;

    Geodetic initial(args.latitude, args.longitude, args.altitude, args.datum);
    Cartesian ned = initial.nedPoint(initial);
    if (initial.isValid())
    {
        ASSERT_TRUE(ned.isNull());
    }
    else
    {
        ASSERT_FALSE(ned.isValid());
    }

    Geodetic restored = initial.offsetted(ned);
    if (initial.isValid())
    {
        EXPECT_EQ(initial, restored);
    }
    else
    {
        ASSERT_FALSE(restored.isValid());
    }
}
