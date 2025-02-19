#ifndef MATHUTILSTESTS_H
#define MATHUTILSTESTS_H

#include "../src/unitTest.h"
#include "../src/mathUtils.h"
#include <cmath>
#include "../src/stringUtils.h"

std::vector<double> logistic(double t, std::vector<double> y) {
    return {0.01 * y[0] * (1 - y[0])};
}

std::vector<double> stiff(double t, std::vector<double> y) {
    double mlambda1 = -0.1;
    double mlambda2 = 1000 * mlambda1;
    return {mlambda1 * y[0], mlambda2 * y[1]};
}

tvnj::DualNumber f(tvnj::DualNumber x, tvnj::DualNumber y) {
    return x.multiply(x.add(y)).add(y.multiply(y));
}

void mathUtilsTests() {
    UNIT_TEST_EQ(tvnj::exponentiationBySquaring(-1, -2), 1);
    UNIT_TEST_EQ(tvnj::exponentiationBySquaring(-1, -1), -1);
    UNIT_TEST_EQ(tvnj::exponentiationBySquaring(-1, 0), 1);
    UNIT_TEST_EQ(tvnj::exponentiationBySquaring(-1, 1), -1);
    UNIT_TEST_EQ(tvnj::exponentiationBySquaring(-1, 2), 1);
    UNIT_TEST_EQ(tvnj::exponentiationBySquaring(-1, 3), -1);

    UNIT_TEST_EQ(tvnj::exponentiationBySquaring(1, -2), 1);
    UNIT_TEST_EQ(tvnj::exponentiationBySquaring(1, -1), 1);
    UNIT_TEST_EQ(tvnj::exponentiationBySquaring(1, 0), 1);
    UNIT_TEST_EQ(tvnj::exponentiationBySquaring(1, 1), 1);
    UNIT_TEST_EQ(tvnj::exponentiationBySquaring(1, 2), 1);
    UNIT_TEST_EQ(tvnj::exponentiationBySquaring(1, 3), 1);

    UNIT_TEST_EQ(tvnj::exponentiationBySquaring(2, -2), 1.0 / 4.0);
    UNIT_TEST_EQ(tvnj::exponentiationBySquaring(2, -1), 1.0 / 2.0);
    UNIT_TEST_EQ(tvnj::exponentiationBySquaring(2, 0), 1);
    UNIT_TEST_EQ(tvnj::exponentiationBySquaring(2, 1), 2);
    UNIT_TEST_EQ(tvnj::exponentiationBySquaring(2, 2), 4);
    UNIT_TEST_EQ(tvnj::exponentiationBySquaring(2, 3), 8);

    UNIT_TEST_EQ(tvnj::exponentiationBySquaring(-1, -2), std::pow(-1, -2));
    UNIT_TEST_EQ(tvnj::exponentiationBySquaring(-1, -1), std::pow(-1, -1));
    UNIT_TEST_EQ(tvnj::exponentiationBySquaring(-1, 0), std::pow(-1, 0));
    UNIT_TEST_EQ(tvnj::exponentiationBySquaring(-1, 1), std::pow(-1, 1));
    UNIT_TEST_EQ(tvnj::exponentiationBySquaring(-1, 2), std::pow(-1, 2));
    UNIT_TEST_EQ(tvnj::exponentiationBySquaring(-1, 3), std::pow(-1, 3));

    UNIT_TEST_EQ(tvnj::exponentiationBySquaring(1, -2), std::pow(1, -2));
    UNIT_TEST_EQ(tvnj::exponentiationBySquaring(1, -1), std::pow(1, -1));
    UNIT_TEST_EQ(tvnj::exponentiationBySquaring(1, 0), std::pow(1, 0));
    UNIT_TEST_EQ(tvnj::exponentiationBySquaring(1, 1), std::pow(1, 1));
    UNIT_TEST_EQ(tvnj::exponentiationBySquaring(1, 2), std::pow(1, 2));
    UNIT_TEST_EQ(tvnj::exponentiationBySquaring(1, 3), std::pow(1, 3));

    UNIT_TEST_EQ(tvnj::exponentiationBySquaring(2, -2), std::pow(2, -2));
    UNIT_TEST_EQ(tvnj::exponentiationBySquaring(2, -1), std::pow(2, -1));
    UNIT_TEST_EQ(tvnj::exponentiationBySquaring(2, 0), std::pow(2, 0));
    UNIT_TEST_EQ(tvnj::exponentiationBySquaring(2, 1), std::pow(2, 1));
    UNIT_TEST_EQ(tvnj::exponentiationBySquaring(2, 2), std::pow(2, 2));
    UNIT_TEST_EQ(tvnj::exponentiationBySquaring(2, 3), std::pow(2, 3));

    //------------------------

    std::vector<double> t = {0,5000};
    std::vector<double> y0 = {0.00001};
    tvnj::OrdinaryDifferentialEquationResult result = tvnj::runge_kutta_order_4_explicit(logistic, t, y0, std::numeric_limits<double>::infinity(), 0.01, 0.05, 0.01);
    std::vector<double> expectedResult = {0, 0.01, 0.03, 0.07, 0.15000000000000002, 0.31000000000000005, 0.6300000000000001, 1.27, 2.55, 5.109999999999999, 10.23, 20.47, 40.95, 81.91, 163.82999999999998, 327.66999999999996, 655.3499999999999, 819.1899999999999, 901.1099999999999, 983.0299999999999, 1064.9499999999998, 1146.87, 1228.79, 1310.71, 1392.63, 1474.5500000000002, 1556.4700000000003, 1720.3100000000002, 1884.15, 2211.83, 2539.5099999999998, 2703.35, 3031.0299999999997, 3358.7099999999996, 3522.5499999999997, 3850.2299999999996, 4177.91, 4341.75, 4669.43, 4997.110000000001, 5000};
    expectedResult = tvnj::vector_abs(tvnj::vector_subtraction(result.t, expectedResult));
    UNIT_TEST_EQ(tvnj::join(expectedResult,", "), tvnj::repeat("0.000000, ", 40) + "0.000000");

    UNIT_TEST_EQ(y0[0], 0.00001);
    UNIT_TEST_EQ(tvnj::join(t,", "), "0.000000, 5000.000000");

    result = tvnj::backward_differentiation_formula_order_6_implicit_fixed_point_iteration(logistic, t, y0, std::numeric_limits<double>::infinity(), 0.01, 0.01, 0.00001);
    expectedResult = {0, 0.01, 0.03, 0.07, 0.15000000000000002, 0.31000000000000005, 0.6300000000000001, 1.27, 2.55, 5.109999999999999, 10.23, 20.47, 40.95, 81.91, 163.82999999999998, 245.75, 327.67, 409.59000000000003, 491.51000000000005, 573.4300000000001, 655.35, 737.27, 819.1899999999999, 860.15, 901.11, 942.07, 983.0300000000001, 1023.9900000000001, 1064.95, 1105.91, 1146.8700000000001, 1187.8300000000002, 1228.7900000000002, 1269.7500000000002, 1310.7100000000003, 1351.6700000000003, 1392.6300000000003, 1433.5900000000004, 1474.5500000000004, 1515.5100000000004, 1556.4700000000005, 1597.4300000000005, 1638.3900000000006, 1679.3500000000006, 1720.3100000000006, 1761.2700000000007, 1802.2300000000007, 1843.1900000000007, 1884.1500000000008, 1925.1100000000008, 1966.0700000000008, 2007.0300000000009, 2047.990000000001, 2088.9500000000007, 2170.870000000001, 2252.790000000001, 2416.630000000001, 2744.310000000001, 3071.9900000000007, 3727.350000000001, 5000};
    expectedResult = tvnj::vector_abs(tvnj::vector_subtraction(result.t, expectedResult));
    UNIT_TEST_EQ(tvnj::join(expectedResult,", "), tvnj::repeat("0.000000, ", 60) + "0.000000");

    result = tvnj::backward_differentiation_formula_order_6_implicit_newtons_method(logistic, t, y0, std::numeric_limits<double>::infinity(), 0.01, 0.01, 0.00001);
    expectedResult = {0, 0.01, 0.05177436912674896, 0.18928453835658407, 0.5604112786032037, 1.4092889414424121, 3.1008232914799896, 6.1055887937048325, 10.955703988861247, 18.184011350364507, 35.67983933056474, 66.47211007449995, 109.56549752320656, 160.35873048764142, 212.8042600719254, 261.9352848535276, 311.0663096351298, 360.197334416732, 409.3283591983342, 458.45938397993643, 507.59040876153864, 556.7214335431408, 605.8524583247431, 654.9834831063454, 704.1145078879476, 753.2455326695499, 802.3765574511522, 851.5075822327544, 900.6386070143567, 949.769631795959, 993.5560976018763, 1037.3425634077937, 1081.129029213711, 1124.9154950196282, 1168.7019608255455, 1212.4884266314627, 1256.27489243738, 1300.0613582432973, 1343.8478240492145, 1387.6342898551318, 1431.420755661049, 1475.2072214669663, 1518.9936872728836, 1562.7801530788008, 1606.566618884718, 1650.3530846906353, 1694.1395504965526, 1737.9260163024699, 1781.7124821083871, 1825.4989479143044, 1869.2854137202216, 1913.071879526139, 1956.8583453320562, 2000.6448111379734, 2044.4312769438907, 2088.217742749808, 2127.7854637560818, 2167.3632451696612, 2209.626348589315, 2256.906572857509, 2311.845427369651, 2378.045811025434, 2461.1137026526794, 2570.8062814171753, 2726.3045440205738, 3030.238667514549, 3488.823632322417, 4199.026637336094, 5000};
    expectedResult = tvnj::vector_abs(tvnj::vector_subtraction(result.t, expectedResult));
    UNIT_TEST_EQ(tvnj::join(expectedResult,", "), tvnj::repeat("0.000000, ", 68) + "0.000000");

    t = {0,10};
    y0 = tvnj::ones<double>(2);

    result = tvnj::runge_kutta_order_4_explicit(stiff, t, y0, std::numeric_limits<double>::infinity(), 0.01, 0.01, 0.0001);
    expectedResult = {0, 0.00125, 0.0025, 0.00375, 0.005, 0.00625, 0.007500000000000001, 0.00875, 0.01, 0.01125, 0.01375, 0.01625, 0.01875, 0.021249999999999998, 0.023749999999999997, 0.028749999999999998, 0.033749999999999995, 0.03874999999999999, 0.048749999999999995, 0.05875, 0.07875, 0.09875, 0.13875, 0.15875, 0.17875, 0.21875, 0.23875, 0.27875, 0.29875, 0.31875000000000003, 0.35875, 0.37875000000000003, 0.41875, 0.43875000000000003, 0.45875000000000005, 0.49875, 0.51875, 0.5587500000000001, 0.5787500000000001, 0.5987500000000001, 0.6387500000000002, 0.6587500000000002, 0.6987500000000002, 0.7187500000000002, 0.7587500000000003, 0.7787500000000003, 0.7987500000000003, 0.8387500000000003, 0.8587500000000003, 0.8987500000000004, 0.9187500000000004, 0.9387500000000004, 0.9787500000000005, 0.9987500000000005, 1.0387500000000005, 1.0587500000000005, 1.0787500000000005, 1.1187500000000006, 1.1387500000000006, 1.1787500000000006, 1.1987500000000006, 1.2187500000000007, 1.2587500000000007, 1.2787500000000007, 1.3187500000000008, 1.3387500000000008, 1.3587500000000008, 1.3987500000000008, 1.4187500000000008, 1.4587500000000009, 1.478750000000001, 1.498750000000001, 1.538750000000001, 1.558750000000001, 1.598750000000001, 1.618750000000001, 1.638750000000001, 1.678750000000001, 1.698750000000001, 1.7387500000000011, 1.7587500000000011, 1.7987500000000012, 1.8187500000000012, 1.8387500000000012, 1.8787500000000013, 1.8987500000000013, 1.9387500000000013, 1.9587500000000013, 1.9787500000000013, 2.018750000000001, 2.038750000000001, 2.078750000000001, 2.0987500000000012, 2.1187500000000012, 2.1587500000000013, 2.1787500000000013, 2.2187500000000013, 2.2387500000000014, 2.2587500000000014, 2.2987500000000014, 2.3187500000000014, 2.3587500000000015, 2.3787500000000015, 2.3987500000000015, 2.4387500000000015, 2.4587500000000015, 2.4987500000000016, 2.5187500000000016, 2.5387500000000016, 2.5787500000000017, 2.5987500000000017, 2.6387500000000017, 2.6587500000000017, 2.6987500000000018, 2.7187500000000018, 2.738750000000002, 2.778750000000002, 2.798750000000002, 2.838750000000002, 2.858750000000002, 2.878750000000002, 2.918750000000002, 2.938750000000002, 2.978750000000002, 2.998750000000002, 3.018750000000002, 3.058750000000002, 3.078750000000002, 3.118750000000002, 3.138750000000002, 3.158750000000002, 3.198750000000002, 3.218750000000002, 3.2587500000000023, 3.2787500000000023, 3.2987500000000023, 3.3387500000000023, 3.3587500000000023, 3.3987500000000024, 3.4187500000000024, 3.4387500000000024, 3.4787500000000025, 3.4987500000000025, 3.5387500000000025, 3.5587500000000025, 3.5787500000000025, 3.6187500000000026, 3.6387500000000026, 3.6787500000000026, 3.6987500000000026, 3.7387500000000027, 3.7587500000000027, 3.7787500000000027, 3.8187500000000028, 3.8387500000000028, 3.878750000000003, 3.898750000000003, 3.918750000000003, 3.958750000000003, 3.978750000000003, 4.0187500000000025, 4.038750000000002, 4.058750000000002, 4.098750000000002, 4.118750000000001, 4.158750000000001, 4.178750000000001, 4.19875, 4.2387500000000005, 4.25875, 4.29875, 4.31875, 4.338749999999999, 4.378749999999999, 4.398749999999999, 4.438749999999999, 4.458749999999998, 4.478749999999998, 4.518749999999998, 4.538749999999998, 4.578749999999998, 4.598749999999997, 4.638749999999997, 4.658749999999997, 4.678749999999996, 4.7187499999999964, 4.738749999999996, 4.778749999999996, 4.798749999999996, 4.818749999999995, 4.858749999999995, 4.878749999999995, 4.918749999999995, 4.938749999999994, 4.958749999999994, 4.998749999999994, 5.018749999999994, 5.058749999999994, 5.078749999999993, 5.098749999999993, 5.138749999999993, 5.158749999999992, 5.198749999999992, 5.218749999999992, 5.238749999999992, 5.278749999999992, 5.298749999999991, 5.338749999999991, 5.358749999999991, 5.37874999999999, 5.41874999999999, 5.43874999999999, 5.47874999999999, 5.49874999999999, 5.518749999999989, 5.558749999999989, 5.578749999999989, 5.618749999999989, 5.638749999999988, 5.678749999999988, 5.698749999999988, 5.718749999999988, 5.758749999999988, 5.778749999999987, 5.818749999999987, 5.838749999999987, 5.858749999999986, 5.898749999999986, 5.918749999999986, 5.958749999999986, 5.978749999999986, 5.998749999999985, 6.038749999999985, 6.058749999999985, 6.098749999999985, 6.118749999999984, 6.138749999999984, 6.178749999999984, 6.1987499999999836, 6.238749999999984, 6.258749999999983, 6.278749999999983, 6.318749999999983, 6.338749999999982, 6.378749999999982, 6.398749999999982, 6.4187499999999815, 6.458749999999982, 6.478749999999981, 6.518749999999981, 6.538749999999981, 6.55874999999998, 6.59874999999998, 6.61874999999998, 6.65874999999998, 6.6787499999999795, 6.71874999999998, 6.738749999999979, 6.758749999999979, 6.798749999999979, 6.818749999999978, 6.858749999999978, 6.878749999999978, 6.8987499999999775, 6.9387499999999775, 6.958749999999977, 6.998749999999977, 7.018749999999977, 7.038749999999976, 7.078749999999976, 7.098749999999976, 7.138749999999976, 7.1587499999999755, 7.178749999999975, 7.218749999999975, 7.238749999999975, 7.278749999999975, 7.298749999999974, 7.318749999999974, 7.358749999999974, 7.3787499999999735, 7.4187499999999735, 7.438749999999973, 7.458749999999973, 7.498749999999973, 7.518749999999972, 7.558749999999972, 7.578749999999972, 7.618749999999972, 7.6387499999999715, 7.658749999999971, 7.698749999999971, 7.718749999999971, 7.758749999999971, 7.77874999999997, 7.79874999999997, 7.83874999999997, 7.8587499999999695, 7.8987499999999695, 7.918749999999969, 7.938749999999969, 7.978749999999969, 7.998749999999968, 8.038749999999968, 8.058749999999968, 8.078749999999967, 8.118749999999967, 8.138749999999966, 8.178749999999965, 8.198749999999965, 8.218749999999964, 8.258749999999964, 8.278749999999963, 8.318749999999962, 8.338749999999962, 8.358749999999961, 8.39874999999996, 8.41874999999996, 8.45874999999996, 8.478749999999959, 8.498749999999959, 8.538749999999958, 8.558749999999957, 8.598749999999956, 8.618749999999956, 8.658749999999955, 8.678749999999955, 8.698749999999954, 8.738749999999953, 8.758749999999953, 8.798749999999952, 8.818749999999952, 8.838749999999951, 8.87874999999995, 8.89874999999995, 8.93874999999995, 8.958749999999949, 8.978749999999948, 9.018749999999947, 9.038749999999947, 9.078749999999946, 9.098749999999946, 9.118749999999945, 9.158749999999944, 9.178749999999944, 9.218749999999943, 9.238749999999943, 9.258749999999942, 9.298749999999941, 9.318749999999941, 9.35874999999994, 9.37874999999994, 9.39874999999994, 9.438749999999938, 9.458749999999938, 9.498749999999937, 9.518749999999937, 9.538749999999936, 9.578749999999935, 9.598749999999935, 9.638749999999934, 9.658749999999934, 9.698749999999933, 9.718749999999932, 9.738749999999932, 9.778749999999931, 9.79874999999993, 9.83874999999993, 9.85874999999993, 9.878749999999929, 9.918749999999928, 9.938749999999928, 9.978749999999927, 9.998749999999927, 10};
    expectedResult = tvnj::vector_abs(tvnj::vector_subtraction(result.t, expectedResult));
    UNIT_TEST_EQ(tvnj::join(expectedResult,", "), tvnj::repeat("0.000000, ", 374) + "0.000000");

    result = tvnj::backward_differentiation_formula_order_6_implicit_fixed_point_iteration(stiff, t, y0, std::numeric_limits<double>::infinity(), 0.01, 2, 0.01);
    expectedResult = {0, 0.01, 0.03, 0.07, 0.11000000000000001, 0.15000000000000002, 0.19000000000000003, 0.27, 0.35000000000000003, 0.51, 0.59, 0.6699999999999999, 0.7499999999999999, 0.9099999999999999, 0.9899999999999999, 1.0699999999999998, 1.2299999999999998, 1.2699999999999998, 1.3499999999999999, 1.5099999999999998, 1.5899999999999999, 1.67, 1.8299999999999998, 1.91, 1.99, 2.07, 2.23, 2.31, 2.39, 2.5500000000000003, 2.5900000000000003, 2.6700000000000004, 2.8300000000000005, 2.9100000000000006, 2.9900000000000007, 3.150000000000001, 3.230000000000001, 3.310000000000001, 3.390000000000001, 3.550000000000001, 3.6300000000000012, 3.7100000000000013, 3.7900000000000014, 3.9500000000000015, 4.030000000000001, 4.110000000000001, 4.270000000000001, 4.310000000000001, 4.3900000000000015, 4.550000000000002, 4.630000000000002, 4.710000000000002, 4.870000000000002, 4.950000000000002, 5.030000000000002, 5.110000000000002, 5.270000000000002, 5.350000000000002, 5.430000000000002, 5.5900000000000025, 5.630000000000003, 5.710000000000003, 5.870000000000003, 5.950000000000003, 6.030000000000003, 6.190000000000003, 6.270000000000003, 6.350000000000003, 6.430000000000003, 6.590000000000003, 6.6700000000000035, 6.7500000000000036, 6.910000000000004, 6.950000000000004, 7.030000000000004, 7.190000000000004, 7.270000000000004, 7.350000000000004, 7.510000000000004, 7.550000000000004, 7.630000000000004, 7.7900000000000045, 7.8700000000000045, 7.950000000000005, 8.110000000000005, 8.150000000000004, 8.230000000000004, 8.390000000000004, 8.470000000000004, 8.550000000000004, 8.630000000000004, 8.790000000000004, 8.870000000000005, 8.950000000000005, 9.110000000000005, 9.150000000000004, 9.230000000000004, 9.390000000000004, 9.470000000000004, 9.550000000000004, 9.630000000000004, 9.790000000000004, 9.870000000000005, 9.950000000000005, 10};
    expectedResult = tvnj::vector_abs(tvnj::vector_subtraction(result.t, expectedResult));
    UNIT_TEST_EQ(tvnj::join(expectedResult,", "), tvnj::repeat("0.000000, ", 104) + "0.000000");

    result = tvnj::backward_differentiation_formula_order_6_implicit_newtons_method(stiff, t, y0, std::numeric_limits<double>::infinity(), 0.01, 2, 0.01);
    expectedResult = {0, 0.01, 0.05719575119851973, 0.19006634374413056, 0.4554536842190591, 1.1144426279006678, 6.075816958097423, 10};
    expectedResult = tvnj::vector_abs(tvnj::vector_subtraction(result.t, expectedResult));
    UNIT_TEST_EQ(tvnj::join(expectedResult,", "), tvnj::repeat("0.000000, ", 7) + "0.000000");

    //------------------------

    const size_t N = 8;
    std::vector<tvnj::ComplexNumber*> signal;

    for (size_t i = 0; i < N; i++) {
        signal.push_back(new tvnj::ComplexNumber(i, -((double) (i))));
    }

    std::vector<tvnj::ComplexNumber*> DFTResult = tvnj::discreteFourierTransform(signal);
    std::vector<double> DFTResultReal;
    std::vector<double> DFTResultImaginary;

    for (size_t i = 0; i < DFTResult.size(); i++) {
        DFTResultReal.push_back(DFTResult[i]->real);
        DFTResultImaginary.push_back(DFTResult[i]->imaginary);
    }

    std::vector<tvnj::ComplexNumber*> FFTResult = tvnj::fastFourierTransformRecursive(signal);
    std::vector<double> FFTResultReal;
    std::vector<double> FFTResultImaginary;

    for (size_t i = 0; i < FFTResult.size(); i++) {
        FFTResultReal.push_back(FFTResult[i]->real - DFTResultReal[i]);
        FFTResultImaginary.push_back(FFTResult[i]->imaginary - DFTResultImaginary[i]);

        // deal with -0.0
        if (FFTResultReal[i] < 0) {
            FFTResultReal[i] *= -1;
        }
        if (FFTResultImaginary[i] < 0) {
            FFTResultImaginary[i] *= -1;
        }
    }

    UNIT_TEST_EQ(tvnj::join(FFTResultReal,", "), tvnj::repeat("0.000000, ", DFTResult.size() - 1) +  + "0.000000");
    UNIT_TEST_EQ(tvnj::join(FFTResultImaginary,", "), tvnj::repeat("0.000000, ", DFTResult.size() - 1) +  + "0.000000");

    FFTResult = tvnj::fastFourierTransformIterative(signal);
    FFTResultReal.clear();
    FFTResultImaginary.clear();

    for (size_t i = 0; i < FFTResult.size(); i++) {
        FFTResultReal.push_back(FFTResult[i]->real - DFTResultReal[i]);
        FFTResultImaginary.push_back(FFTResult[i]->imaginary - DFTResultImaginary[i]);

        // deal with -0.0
        if (FFTResultReal[i] < 0) {
            FFTResultReal[i] *= -1;
        }
        if (FFTResultImaginary[i] < 0) {
            FFTResultImaginary[i] *= -1;
        }
    }

    UNIT_TEST_EQ(tvnj::join(FFTResultReal,", "), tvnj::repeat("0.000000, ", DFTResult.size() - 1) +  + "0.000000");
    UNIT_TEST_EQ(tvnj::join(FFTResultImaginary,", "), tvnj::repeat("0.000000, ", DFTResult.size() - 1) +  + "0.000000");

    //------------------------

    std::vector<tvnj::ComplexNumber*> inverseFourierTransformInput(DFTResult);
    DFTResult = tvnj::inverseDiscreteFourierTransform(inverseFourierTransformInput);
    DFTResultReal.clear();
    DFTResultImaginary.clear();

    for (size_t i = 0; i < DFTResult.size(); i++) {
        DFTResultReal.push_back(DFTResult[i]->real);
        DFTResultImaginary.push_back(DFTResult[i]->imaginary);
    }

    FFTResult = tvnj::inverseFastFourierTransformRecursive(inverseFourierTransformInput);
    FFTResultReal.clear();
    FFTResultImaginary.clear();

    for (size_t i = 0; i < FFTResult.size(); i++) {
        FFTResultReal.push_back(FFTResult[i]->real - DFTResultReal[i]);
        FFTResultImaginary.push_back(FFTResult[i]->imaginary - DFTResultImaginary[i]);

        // deal with -0.0
        if (FFTResultReal[i] < 0) {
            FFTResultReal[i] *= -1;
        }
        if (FFTResultImaginary[i] < 0) {
            FFTResultImaginary[i] *= -1;
        }
    }

    UNIT_TEST_EQ(tvnj::join(FFTResultReal,", "), tvnj::repeat("0.000000, ", DFTResult.size() - 1) +  + "0.000000");
    UNIT_TEST_EQ(tvnj::join(FFTResultImaginary,", "), tvnj::repeat("0.000000, ", DFTResult.size() - 1) +  + "0.000000");

    FFTResult = tvnj::inverseFastFourierTransformIterative(inverseFourierTransformInput);
    FFTResultReal.clear();
    FFTResultImaginary.clear();

    for (size_t i = 0; i < FFTResult.size(); i++) {
        FFTResultReal.push_back(FFTResult[i]->real - DFTResultReal[i]);
        FFTResultImaginary.push_back(FFTResult[i]->imaginary - DFTResultImaginary[i]);

        // deal with -0.0
        if (FFTResultReal[i] < 0) {
            FFTResultReal[i] *= -1;
        }
        if (FFTResultImaginary[i] < 0) {
            FFTResultImaginary[i] *= -1;
        }
    }

    UNIT_TEST_EQ(tvnj::join(FFTResultReal,", "), tvnj::repeat("0.000000, ", DFTResult.size() - 1) +  + "0.000000");
    UNIT_TEST_EQ(tvnj::join(FFTResultImaginary,", "), tvnj::repeat("0.000000, ", DFTResult.size() - 1) +  + "0.000000");

    FFTResultReal.clear();
    FFTResultImaginary.clear();

    for (size_t i = 0; i < FFTResult.size(); i++) {
        FFTResultReal.push_back(FFTResult[i]->real - signal[i]->real);
        FFTResultImaginary.push_back(FFTResult[i]->imaginary - signal[i]->imaginary);

        // deal with -0.0
        if (FFTResultReal[i] < 0) {
            FFTResultReal[i] *= -1;
        }
        if (FFTResultImaginary[i] < 0) {
            FFTResultImaginary[i] *= -1;
        }
    }

    UNIT_TEST_EQ(tvnj::join(FFTResultReal,", "), tvnj::repeat("0.000000, ", DFTResult.size() - 1) +  + "0.000000");
    UNIT_TEST_EQ(tvnj::join(FFTResultImaginary,", "), tvnj::repeat("0.000000, ", DFTResult.size() - 1) +  + "0.000000");

    //------------------------

    tvnj::DualNumber x(2);
    tvnj::DualNumber y(3);
    tvnj::DualNumber e(0, 1);
    UNIT_TEST_EQ(f(x.add(e), y).infinitesimal, 7);
    UNIT_TEST_EQ(f(x, y.add(e)).infinitesimal, 8);
}

#endif
