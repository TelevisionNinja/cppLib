#include "mathUtils.h"
#include "arrayUtils.h"
#include <cmath>
#include <numbers> // pi

/**
 * 
 * @param base 
 * @param power 
 * @return double 
 */
double tvnj::exponentiationBySquaring(double base, unsigned int power) {
    double result = 1;
    double exponentiation = base;
    unsigned int i = power;

    while (i != 0) { // i > 0
        if (i % 2 != 0) {
            result *= exponentiation;
        }

        exponentiation *= exponentiation;
        i >>= 1;
    }

    return result;
}

/**
 * 
 * @param base 
 * @param power 
 * @return double 
 */
double tvnj::exponentiationBySquaring(double base, int power) {
    double result = 1;
    double exponentiation = base;
    bool isNegative = power < 0;
    int i = power;

    if (isNegative) {
        i *= -1;
    }

    while (i != 0) { // i > 0
        if (i % 2 != 0) {
            result *= exponentiation;
        }

        exponentiation *= exponentiation;
        i >>= 1;
    }

    if (isNegative) {
        return 1 / result;
    }

    return result;
}

/**
 * @brief time complexity: O(n)
 * 
 * @param std::vector<double> 
 * @param std::vector<double> 
 * @return double 
 */
double tvnj::integrate_trapezoid(std::vector<double> y, std::vector<double> x) {
    double sum = 0;

    for (size_t i = 0; i < x.size() - 1; i++) {
        size_t next_index = i + 1;
        sum += (x[next_index] - x[i]) * (y[next_index] + y[i]);
    }

    return sum / 2; // moved the constant out to do only one division
}

/**
 * @brief slope formula
 * 
 * @param x_one 
 * @param y_one 
 * @param x_two 
 * @param y_two 
 * @return double 
 */
double tvnj::slope(double x_one, double y_one, double x_two, double y_two) {
    return (y_two - y_one) / (x_two - x_one);
}

/**
 * @brief time complexity: O(n + m)
 * 
 * @param interpolated_x 
 * @param x 
 * @param y 
 * @return std::vector<double> 
 */
std::vector<double> tvnj::linear_interpolation(std::vector<double> interpolated_x, std::vector<double> x, std::vector<double> y) {
    std::vector<double> interpolated_y;

    if (y.size() < 2 || x.size() < 2 || interpolated_x.size() == 0) {
        return interpolated_y;
    }

    size_t interpolated_x_index = 0;
    size_t i = 0;

    // these vars are in this scope so thay can be used for interpolation after the interval
    double x_one = x[i];
    double y_one = y[i];
    double x_two = x[i + 1];
    double y_two = y[i + 1];
    double current_slope = tvnj::slope(x_one, y_one, x_two, y_two);

    // interpolate values before the interval
    while (interpolated_x_index < interpolated_x.size() && interpolated_x[interpolated_x_index] < x[0]) {
        double interpolated_value = current_slope * (interpolated_x[interpolated_x_index] - x_one) + y_one;
        interpolated_y.push_back(interpolated_value);
        interpolated_x_index++;
    }

    // interpolate values in the interval
    while (i < x.size() - 1 && interpolated_x_index < interpolated_x.size()) {
        x_one = x[i];
        y_one = y[i];

        i++;

        if (x_one == interpolated_x[interpolated_x_index]) {
            interpolated_y.push_back(y_one);
            interpolated_x_index++;
        }
        else {
            x_two = x[i];
            y_two = y[i];
            current_slope = tvnj::slope(x_one, y_one, x_two, y_two);

            while (interpolated_x_index < interpolated_x.size() && interpolated_x[interpolated_x_index] < x_one) {
                double interpolated_value = current_slope * (interpolated_x[interpolated_x_index] - x_one) + y_one;
                interpolated_y.push_back(interpolated_value);
                interpolated_x_index++;
            }
        }
    }

    // interpolate values after the interval
    x_two = x[i];
    y_two = y[i];
    current_slope = tvnj::slope(x_one, y_one, x_two, y_two);

    while (interpolated_x_index < interpolated_x.size()) {
        double interpolated_value = current_slope * (interpolated_x[interpolated_x_index] - x_one) + y_one;
        interpolated_y.push_back(interpolated_value);
        interpolated_x_index++;
    }

    return interpolated_y;
}

/**
 * @brief time complexity: O(n)
 * 
 * create a list of evenly spaced points
 * 
 * @param min 
 * @param max 
 * @param samples 
 * @return std::vector<double> 
 */
std::vector<double> tvnj::linear_space(double min, double max, size_t samples) {
    std::vector<double> arr;
    double sum = min;
    samples--;
    double interval_size = (max - min) / samples;
    size_t i = 0;

    while (i < samples) {
        arr.push_back(sum);
        sum += interval_size;
        i++;
    }

    arr.push_back(max);

    return arr;
}

/**
 * @brief 
 * 
 * @param x 
 * @param x_one 
 * @param y_one 
 * @param x_two 
 * @param y_two 
 * @return double 
 */
double tvnj::linear_interpolation_single_point(double x, double x_one, double y_one, double x_two, double y_two) {
    return tvnj::slope(x_one, y_one, x_two, y_two) * (x - x_one) + y_one;
}

/**
 * @brief time complexity: O(n)
 * 
 * @param y 
 * @param x 
 * @param initial 
 * @return std::vector<double> 
 */
std::vector<double> tvnj::integrate_cumulative_trapezoid(std::vector<double> y, std::vector<double> x, double initial) {
    std::vector<double> sums;
    double sum = 0;

    if (initial != NULL) {
        sum = initial;
        sums.push_back(sum);
    }

    for (size_t i = 0; i < x.size() - 1; i++) {
        size_t next_index = i + 1;
        sum += (x[next_index] - x[i]) * (y[next_index] + y[i]) / 2;
        sums.push_back(sum);
    }

    return sums;
}

std::vector<double> tvnj::scalar_multiplication(double scalar, std::vector<double> array) {
    std::vector<double> new_vector;
    size_t i = 0;
    while (i < array.size()) {
        new_vector.push_back(array[i] * scalar);
        i++;
    }
    return new_vector;
}

std::vector<double> tvnj::scalar_division(double scalar, std::vector<double> array) {
    std::vector<double> new_vector;
    size_t i = 0;
    while (i < array.size()) {
        new_vector.push_back(array[i] / scalar);
        i++;
    }
    return new_vector;
}

std::vector<double> tvnj::vector_addition(std::vector<double> array1, std::vector<double> array2) {
    std::vector<double> new_vector;
    size_t i = 0;
    while (i < array1.size()) {
        new_vector.push_back(array1[i] + array2[i]);
        i++;
    }
    return new_vector;
}

std::vector<double> tvnj::vector_subtraction(std::vector<double> array1, std::vector<double> array2) {
    std::vector<double> new_vector;
    size_t i = 0;
    while (i < array1.size()) {
        new_vector.push_back(array1[i] - array2[i]);
        i++;
    }
    return new_vector;
}

std::vector<double> tvnj::vector_division(std::vector<double> array1, std::vector<double> array2) {
    std::vector<double> new_vector;
    size_t i = 0;
    while (i < array1.size()) {
        new_vector.push_back(array1[i] / array2[i]);
        i++;
    }
    return new_vector;
}

/**
 * @brief explicit
    for non-stiff problems
    any order differential equation

    y_n: initial y
    t: time step
    dt: time step size
    function: function(double t, std::vector<double> y) -> std::vector<double>

    returns: y_{n+1}
 * 
 * @param y_n 
 * @param t 
 * @param dt 
 * @param function 
 * @return std::vector<double> 
 */
std::vector<double> tvnj::runge_kutta_order_4_explicit_step(std::vector<double> y_n, double t, double dt, std::function<std::vector<double>(double, std::vector<double>)> function) {
    std::vector<double> k1 = function(t, y_n);
    std::vector<double> k2 = function(t + dt / 2, tvnj::vector_addition(y_n, tvnj::scalar_multiplication(dt / 2, k1)));
    std::vector<double> k3 = function(t + dt / 2, tvnj::vector_addition(y_n, tvnj::scalar_multiplication(dt / 2, k2)));
    std::vector<double> k4 = function(t + dt, tvnj::vector_addition(y_n, tvnj::scalar_multiplication(dt, k3)));

    k2 = tvnj::vector_addition(k2, k3);
    k2 = tvnj::scalar_multiplication(2, k2);

    k1 = tvnj::vector_addition(k1, k2);
    k1 = tvnj::vector_addition(k1, k4);
    k1 = tvnj::scalar_multiplication(dt / 6, k1);

    return tvnj::vector_addition(y_n, k1);
}

/**
 * @brief explicit
    for non-stiff problems
    adaptive step size
    any order differential equation

    dy_max: speed
    dy_min: accuracy
    dt_max: max time step size
    initial_step_size: starting step size
    time_span: time bounds
    function: function(double t, std::vector<double> y) -> std::vector<double>

    returns: [time_points, y]
 * 
 * @param function 
 * @param time_span 
 * @param y_i 
 * @param dt_max 
 * @param initial_step_size 
 * @param dy_max 
 * @param dy_min 
 * @return OrdinaryDifferentialEquationResult
 */
tvnj::OrdinaryDifferentialEquationResult tvnj::runge_kutta_order_4_explicit(std::function<std::vector<double>(double, std::vector<double>)> function, std::vector<double> time_span, std::vector<double> y_i, double dt_max, double initial_step_size, double dy_max, double dy_min) {
    double dt = initial_step_size;
    double t_i = time_span[0];
    double t_f = time_span[1];
    std::vector<double> time_points = {t_i};
    double t = t_i;
    std::vector<std::vector<double>> y = {y_i};
    std::vector<double> y_integrated = y_i;

    while (t < t_f) {
        std::vector<double> y_integrated_new = tvnj::runge_kutta_order_4_explicit_step(y_integrated, t, dt, function);

        // predicted next y
        std::vector<double> slope_current = function(t, y_integrated);
        std::vector<double> y_next = tvnj::vector_addition(y_integrated, tvnj::scalar_multiplication(dt, slope_current));
        std::vector<double> y_difference_1 = tvnj::vector_abs(tvnj::vector_subtraction(y_next, y_integrated_new));

        // predicted current y
        std::vector<double> slope_next = function(t + dt, y_integrated_new);
        std::vector<double> y_previous = tvnj::vector_subtraction(y_integrated_new, tvnj::scalar_multiplication(dt, slope_next));
        std::vector<double> y_difference_2 = tvnj::vector_abs(tvnj::vector_subtraction(y_integrated, y_previous));

        if (tvnj::max(y_difference_1) > dy_max || tvnj::max(y_difference_2) > dy_max) { // predicted y max
            dt /= 2;
        }
        else {
            y_integrated = y_integrated_new;
            y.push_back(y_integrated);
            t += dt;
            time_points.push_back(t);

            if (tvnj::min(y_difference_1) <= dy_min || tvnj::min(y_difference_2) <= dy_min) { // predicted y min
                dt *= 2;

                if (dt > dt_max) {
                    dt = dt_max;
                }
            }
        }
    }

    // last step
    // the loop overshoots t_f for accuracy. we then get y_{t_f} without loss of accuracy
    if (time_points[time_points.size() - 1] > t_f) {
        t = time_points[time_points.size() - 2];
        dt = t_f - t;

        y[y.size() - 1] = tvnj::runge_kutta_order_4_explicit_step(y[y.size() - 2], t, dt, function);
        time_points[time_points.size() - 1] = t_f;
    }

    struct tvnj::OrdinaryDifferentialEquationResult result;
    result.t = time_points;
    result.y = y;
    return result;
}

/**
 * @brief no overflow midpoint formula
 * 
 * @param low 
 * @param high 
 * @return double 
 */
double tvnj::midpoint_no_overflow(double low, double high) {
    return low + (high - low) / 2;
}

/**
 * @brief midpoint formula
 * 
 * @param a 
 * @param b 
 * @return double 
 */
double tvnj::midpoint(double a, double b) {
    return (a + b) / 2;
}

/**
 * @brief root finding algorithm

    a: start of interval
    b: end of interval

    returns NULL if fails
 * 
 * @param function 
 * @param a 
 * @param b 
 * @param max_iterations 
 * @return double 
 */
double tvnj::bisection(std::function<double(double)> function, double a, double b, size_t max_iterations) {
    double f_a = function(a);
    double f_b = function(b);

    if (f_a * f_b >= 0) {
        return NULL;
    }

    size_t i = 0;
    double m = 0;

    while (i < max_iterations) {
        m = tvnj::midpoint(a, b);
        double f_m = function(m);

        if (f_m == 0) {
            return m;
        }
        else if (f_b * f_m < 0) {
            a = m;
            f_a = f_m;
        }
        else if (f_a * f_m < 0) {
            b = m;
            f_b = f_m;
        }
        else {
            return NULL;
        }

        i++;
    }

    return m;
}

/**
 * @brief root finding algorithm

    a: start of interval
    b: end of interval

    returns NULL if fails
 * 
 * @param function 
 * @param a 
 * @param b 
 * @param max_iterations 
 * @return double 
 */
double tvnj::secant(std::function<double(double)> function, double a, double b, size_t max_iterations) {
    double f_a = function(a);
    double f_b = function(b);

    if (f_a * f_b >= 0) {
        return NULL;
    }

    size_t i = 0;
    double m = 0;

    while (i < max_iterations) {
        m = a - f_a * (b - a) / (f_b - f_a);
        double f_m = function(m);

        if (f_m == 0) {
            return m;
        }
        else if (f_b * f_m < 0) {
            a = m;
            f_a = f_m;
        }
        else if (f_a * f_m < 0) {
            b = m;
            f_b = f_m;
        }
        else {
            return NULL;
        }

        i++;
    }

    return m;
}

/**
 * @brief root finding algorithm

    x: inital guess for x
    function: function(double x) -> double
    derivative: derivative(double x) -> double
    tolerance: accuracy of the result
    max_iterations: max iterations allowed to find the root

    returns NULL if fails
 * 
 * @param function 
 * @param x 
 * @param derivative 
 * @param tolerance 
 * @param max_iterations 
 * @return double 
 */
double tvnj::newtons_method(std::function<double(double)> function, double x, std::function<double(double)> derivative, double tolerance, size_t max_iterations) {
    size_t i = 0;

    while (i < max_iterations) {
        double f_x = function(x);

        if (std::abs(f_x) < tolerance) {
            return x;
        }

        double df_x = 0;

        if (derivative == NULL) {
            df_x = (function(x + tolerance) - f_x) / tolerance; // Approximate derivative
        }
        else {
            df_x = derivative(x);
        }

        if (df_x == 0) {
            return NULL;
        }

        x -= f_x / df_x;
        i++;
    }

    return x;
}

std::vector<double> tvnj::vector_abs(std::vector<double> array) {
    std::vector<double> new_array;
    size_t i = 0;

    while (i < array.size()) {
        new_array.push_back(std::abs(array[i]));
        i++;
    }

    return new_array;
}

bool tvnj::contains_nan_or_infinity(std::vector<double> array) {
    size_t i = 0;

    while (i < array.size()) {
        double element = array[i];

        if (std::isnan(element) || std::isinf(element)) {
            return true;
        }

        i++;
    }

    return false;
}

/**
 * @brief x: initial x guess
    t: time step
    dt: time step size
    y_previous: the addition of all previous y"s. ex: y_{n} + y_{n-1} + ...
    function: function(double t, std::vector<double> y) -> std::vector<double>
    tolerance: accuracy of the result
    max_iterations: max iterations allowed to find the fixed point

    returns: the fixed point y_{n+1}
 * 
 * @param function 
 * @param t 
 * @param dt 
 * @param x 
 * @param y_previous 
 * @param tolerance 
 * @param max_iterations 
 * @return std::vector<double> 
 */
std::vector<double> tvnj::backward_differentiation_formula_implicit_fixed_point_iteration(std::function<std::vector<double>(double, std::vector<double>)> function, double t, double dt, std::vector<double> x, std::vector<double> y_previous, double tolerance, size_t max_iterations) {
    size_t i = 0;

    while (i < max_iterations) {
        std::vector<double> y = tvnj::vector_subtraction(tvnj::scalar_multiplication(dt, function(t, x)), y_previous);

        if (tvnj::contains_nan_or_infinity(y)) {
            return x;
        }

        if (tvnj::max(tvnj::vector_abs(tvnj::vector_subtraction(x, y))) < tolerance) {
            return y;
        }

        x = y;
        i++;
    }

    return x;
}

/**
 * @brief implicit
    for stiff problems
    any order differential equation
    https://en.wikipedia.org/wiki/Backward_differentiation_formula

    y_n: initial y
    t: time step
    dt: time step size
    function: function(double t, std::vector<double> y) -> std::vector<double>
    tolerance: accuracy of the result
    max_iterations: max iterations allowed to find the fixed point

    returns: y_{n+1}
 * 
 * @param y_n 
 * @param t 
 * @param dt 
 * @param function 
 * @param tolerance 
 * @param max_iterations 
 * @return std::vector<double> 
 */
std::vector<double> tvnj::backward_differentiation_formula_order_6_implicit_fixed_point_iteration_step(std::vector<double> y_n, double t, double dt, std::function<std::vector<double>(double, std::vector<double>)> function, double tolerance, size_t max_iterations) {
    dt /= 6;

    std::vector<double> y_previous = tvnj::scalar_multiplication(-1, y_n);
    std::vector<double> y_1 = tvnj::backward_differentiation_formula_implicit_fixed_point_iteration(function, t + dt, dt, y_n, y_previous, tolerance, max_iterations);

    std::vector<double> t_1 = tvnj::scalar_multiplication(1.0/3.0, y_n);
    std::vector<double> t_2 = tvnj::scalar_multiplication(-4.0/3.0, y_1);
    y_previous = tvnj::vector_addition(t_2, t_1);
    std::vector<double> y_2 = tvnj::backward_differentiation_formula_implicit_fixed_point_iteration(function, t + dt * 2, dt * 2 / 3, y_1, y_previous, tolerance, max_iterations);

    t_1 = tvnj::scalar_multiplication(-2.0/11.0, y_n);
    t_2 = tvnj::scalar_multiplication(9.0/11.0, y_1);
    std::vector<double> t_3 = tvnj::scalar_multiplication(-18.0/11.0, y_2);
    y_previous = tvnj::vector_addition(t_2, t_1);
    y_previous = tvnj::vector_addition(t_3, y_previous);
    std::vector<double> y_3 = tvnj::backward_differentiation_formula_implicit_fixed_point_iteration(function, t + dt * 3, dt * 6 / 11, y_2, y_previous, tolerance, max_iterations);

    t_1 = tvnj::scalar_multiplication(3.0/25.0, y_n);
    t_2 = tvnj::scalar_multiplication(-16.0/25.0, y_1);
    t_3 = tvnj::scalar_multiplication(36.0/25.0, y_2);
    std::vector<double> t_4 = tvnj::scalar_multiplication(-48.0/25.0, y_3);
    y_previous = tvnj::vector_addition(t_2, t_1);
    y_previous = tvnj::vector_addition(t_3, y_previous);
    y_previous = tvnj::vector_addition(t_4, y_previous);
    std::vector<double> y_4 = tvnj::backward_differentiation_formula_implicit_fixed_point_iteration(function, t + dt * 4, dt * 12 / 25, y_3, y_previous, tolerance, max_iterations);

    t_1 = tvnj::scalar_multiplication(-12.0/137.0, y_n);
    t_2 = tvnj::scalar_multiplication(75.0/137.0, y_1);
    t_3 = tvnj::scalar_multiplication(-200.0/137.0, y_2);
    t_4 = tvnj::scalar_multiplication(300.0/137.0, y_3);
    std::vector<double> t_5 = tvnj::scalar_multiplication(-300.0/137.0, y_4);
    y_previous = tvnj::vector_addition(t_2, t_1);
    y_previous = tvnj::vector_addition(t_3, y_previous);
    y_previous = tvnj::vector_addition(t_4, y_previous);
    y_previous = tvnj::vector_addition(t_5, y_previous);
    std::vector<double> y_5 = tvnj::backward_differentiation_formula_implicit_fixed_point_iteration(function, t + dt * 5, dt * 60 / 137, y_4, y_previous, tolerance, max_iterations);

    t_1 = tvnj::scalar_multiplication(10.0/147.0, y_n);
    t_2 = tvnj::scalar_multiplication(-72.0/147.0, y_1);
    t_3 = tvnj::scalar_multiplication(225.0/147.0, y_2);
    t_4 = tvnj::scalar_multiplication(-400.0/147.0, y_3);
    t_5 = tvnj::scalar_multiplication(450.0/147.0, y_4);
    std::vector<double> t_6 = tvnj::scalar_multiplication(-360.0/147.0, y_5);
    y_previous = tvnj::vector_addition(t_2, t_1);
    y_previous = tvnj::vector_addition(t_3, y_previous);
    y_previous = tvnj::vector_addition(t_4, y_previous);
    y_previous = tvnj::vector_addition(t_5, y_previous);
    y_previous = tvnj::vector_addition(t_6, y_previous);
    std::vector<double> y_6 = tvnj::backward_differentiation_formula_implicit_fixed_point_iteration(function, t + dt * 6, dt * 60 / 147, y_5, y_previous, tolerance, max_iterations);

    return y_6;
}

std::vector<double> tvnj::scalar_addition(double scalar, std::vector<double> array) {
    std::vector<double> new_vector;
    size_t i = 0;
    while (i < array.size()) {
        new_vector.push_back(array[i] + scalar);
        i++;
    }
    return new_vector;
}

/**
 * @brief implicit
    for stiff problems
    adaptive step size
    any order differential equation

    dy_max: speed
    dy_min: accuracy
    dt_max: max time step size
    initial_step_size: starting step size
    time_span: time bounds
    function: function(double t, std::vector<double> y) -> std::vector<double>
    root_finding_tolerance: accuracy of the step result
    root_finding_max_iterations: max iterations allowed to find the fixed point in a step

    returns: [time_points, y]
 * 
 * @param function 
 * @param time_span 
 * @param y_i 
 * @param dt_max: 
 * @param initial_step_size 
 * @param dy_max 
 * @param dy_min 
 * @param root_finding_tolerance 
 * @param root_finding_max_iterations 
 * @return OrdinaryDifferentialEquationResult
 */
tvnj::OrdinaryDifferentialEquationResult tvnj::backward_differentiation_formula_order_6_implicit_fixed_point_iteration(std::function<std::vector<double>(double, std::vector<double>)> function, std::vector<double> time_span, std::vector<double> y_i, double dt_max, double initial_step_size, double dy_max, double dy_min, double root_finding_tolerance, size_t root_finding_max_iterations) {
    double dt = initial_step_size;
    double t_i = time_span[0];
    double t_f = time_span[1];
    std::vector<double> time_points = {t_i};
    double t = t_i;
    std::vector<std::vector<double>> y = {y_i};
    std::vector<double> y_integrated = y_i;

    while (t < t_f) {
        std::vector<double> y_integrated_new = tvnj::backward_differentiation_formula_order_6_implicit_fixed_point_iteration_step(y_integrated, t, dt, function, root_finding_tolerance, root_finding_max_iterations);

        // predicted next y
        std::vector<double> slope_current = function(t, y_integrated);
        std::vector<double> y_next = tvnj::vector_addition(y_integrated, tvnj::scalar_multiplication(dt, slope_current));
        std::vector<double> y_difference_1 = tvnj::vector_abs(tvnj::vector_subtraction(y_next, y_integrated_new));

        // predicted current y
        std::vector<double> slope_next = function(t + dt, y_integrated_new);
        std::vector<double> y_previous = tvnj::vector_subtraction(y_integrated_new, tvnj::scalar_multiplication(dt, slope_next));
        std::vector<double> y_difference_2 = tvnj::vector_abs(tvnj::vector_subtraction(y_integrated, y_previous));

        if (tvnj::max(y_difference_1) > dy_max || tvnj::max(y_difference_2) > dy_max) { // predicted y max
            dt /= 2;
        }
        else {
            y_integrated = y_integrated_new;
            y.push_back(y_integrated);
            t += dt;
            time_points.push_back(t);

            if (tvnj::min(y_difference_1) <= dy_min || tvnj::min(y_difference_2) <= dy_min) { // predicted y min
                dt *= 2;

                if (dt > dt_max) {
                    dt = dt_max;
                }
            }
        }
    }

    // last step
    // the loop overshoots t_f for accuracy. we then get y_{t_f} without loss of accuracy
    if (time_points[time_points.size() - 1] > t_f) {
        t = time_points[time_points.size() - 2];
        dt = t_f - t;

        y[y.size() - 1] = tvnj::backward_differentiation_formula_order_6_implicit_fixed_point_iteration_step(y[y.size() - 2], t, dt, function, root_finding_tolerance, root_finding_max_iterations);
        time_points[time_points.size() - 1] = t_f;
    }

    struct tvnj::OrdinaryDifferentialEquationResult result;
    result.t = time_points;
    result.y = y;
    return result;
}

/**
 * @brief x: initial x guess
    t: time step
    dt: time step size
    y_previous: the addition of all previous y"s. ex: y_{n} + y_{n-1} + ...
    function: function(double t, std::vector<double> y) -> std::vector<double>
    jacobian: jacobian(double t, std::vector<double> y) -> std::vector<double>
    tolerance: accuracy of the result
    max_iterations: max iterations allowed to find the root

    returns: the root y_{n+1}
 * 
 * @param function 
 * @param t 
 * @param dt 
 * @param x 
 * @param y_previous 
 * @param jacobian 
 * @param tolerance 
 * @param max_iterations 
 * @return std::vector<double> 
 */
std::vector<double> tvnj::backward_differentiation_formula_implicit_newtons_method(std::function<std::vector<double>(double, std::vector<double>)> function, double t, double dt, std::vector<double> x, std::vector<double> y_previous, std::function<std::vector<double>(double, std::vector<double>)> jacobian, double tolerance, size_t max_iterations) {
    size_t i = 0;

    if (jacobian == NULL) {
        while (i < max_iterations) {
            std::vector<double> f = function(t, x); // for jacobian
            std::vector<double> y = tvnj::vector_subtraction(tvnj::vector_addition(x, y_previous), tvnj::scalar_multiplication(dt, f));

            if (tvnj::contains_nan_or_infinity(y) || tvnj::max(tvnj::vector_abs(y)) < tolerance) {
                return x;
            }

            std::vector<double> x2 = tvnj::scalar_addition(tolerance, x);
            std::vector<double> f2 = function(t, x2);
            std::vector<double> j = tvnj::vector_subtraction(tvnj::ones<double>(x.size()), tvnj::scalar_multiplication(dt / tolerance, tvnj::vector_subtraction(f2, f))); // Approximate jacobian

            if (tvnj::contains<double>(j, 0)) {
                return x;
            }

            x = tvnj::vector_subtraction(x, tvnj::vector_division(y, j));
            i++;
        }
    }
    else {
        while (i < max_iterations) {
            std::vector<double> y = tvnj::vector_subtraction(tvnj::vector_addition(x, y_previous), tvnj::scalar_multiplication(dt, function(t, x)));

            if (tvnj::contains_nan_or_infinity(y) || tvnj::max(tvnj::vector_abs(y)) < tolerance) {
                return x;
            }

            std::vector<double> j = tvnj::vector_subtraction(tvnj::ones<double>(x.size()), tvnj::scalar_multiplication(dt, jacobian(t, x)));

            if (tvnj::contains<double>(j, 0)) {
                return x;
            }

            x = tvnj::vector_subtraction(x, tvnj::vector_division(y, j));
            i++;
        }
    }

    return x;
}

/**
 * @brief implicit
    for stiff problems
    any order differential equation
    https://en.wikipedia.org/wiki/Backward_differentiation_formula

    y_n: initial y
    t: time step
    dt: time step size
    function: function(double t, std::vector<double> y) -> std::vector<double>
    jacobian: jacobian(double t, std::vector<double> y) -> std::vector<double>
    tolerance: accuracy of the result
    max_iterations: max iterations allowed to find the root

    returns: y_{n+1}
 * 
 * @param y_n 
 * @param t 
 * @param dt 
 * @param function 
 * @param jacobian 
 * @param tolerance 
 * @param max_iterations 
 * @return std::vector<double> 
 */
std::vector<double> tvnj::backward_differentiation_formula_order_6_implicit_newtons_method_step(std::vector<double> y_n, double t, double dt, std::function<std::vector<double>(double, std::vector<double>)> function, std::function<std::vector<double>(double, std::vector<double>)> jacobian, double tolerance, size_t max_iterations) {
    dt /= 6;

    std::vector<double> y_previous = tvnj::scalar_multiplication(-1, y_n);
    std::vector<double> y_1 = tvnj::backward_differentiation_formula_implicit_newtons_method(function, t + dt, dt, y_n, y_previous, jacobian, tolerance, max_iterations);

    std::vector<double> t_1 = tvnj::scalar_multiplication(1.0/3.0, y_n);
    std::vector<double> t_2 = tvnj::scalar_multiplication(-4.0/3.0, y_1);
    y_previous = tvnj::vector_addition(t_2, t_1);
    std::vector<double> y_2 = tvnj::backward_differentiation_formula_implicit_newtons_method(function, t + dt * 2, dt * 2 / 3, y_1, y_previous, jacobian, tolerance, max_iterations);

    t_1 = tvnj::scalar_multiplication(-2.0/11.0, y_n);
    t_2 = tvnj::scalar_multiplication(9.0/11.0, y_1);
    std::vector<double> t_3 = tvnj::scalar_multiplication(-18.0/11.0, y_2);
    y_previous = tvnj::vector_addition(t_2, t_1);
    y_previous = tvnj::vector_addition(t_3, y_previous);
    std::vector<double> y_3 = tvnj::backward_differentiation_formula_implicit_newtons_method(function, t + dt * 3, dt * 6 / 11, y_2, y_previous, jacobian, tolerance, max_iterations);

    t_1 = tvnj::scalar_multiplication(3.0/25.0, y_n);
    t_2 = tvnj::scalar_multiplication(-16.0/25.0, y_1);
    t_3 = tvnj::scalar_multiplication(36.0/25.0, y_2);
    std::vector<double> t_4 = tvnj::scalar_multiplication(-48.0/25.0, y_3);
    y_previous = tvnj::vector_addition(t_2, t_1);
    y_previous = tvnj::vector_addition(t_3, y_previous);
    y_previous = tvnj::vector_addition(t_4, y_previous);
    std::vector<double> y_4 = tvnj::backward_differentiation_formula_implicit_newtons_method(function, t + dt * 4, dt * 12 / 25, y_3, y_previous, jacobian, tolerance, max_iterations);

    t_1 = tvnj::scalar_multiplication(-12.0/137.0, y_n);
    t_2 = tvnj::scalar_multiplication(75.0/137.0, y_1);
    t_3 = tvnj::scalar_multiplication(-200.0/137.0, y_2);
    t_4 = tvnj::scalar_multiplication(300.0/137.0, y_3);
    std::vector<double> t_5 = tvnj::scalar_multiplication(-300.0/137.0, y_4);
    y_previous = tvnj::vector_addition(t_2, t_1);
    y_previous = tvnj::vector_addition(t_3, y_previous);
    y_previous = tvnj::vector_addition(t_4, y_previous);
    y_previous = tvnj::vector_addition(t_5, y_previous);
    std::vector<double> y_5 = tvnj::backward_differentiation_formula_implicit_newtons_method(function, t + dt * 5, dt * 60 / 137, y_4, y_previous, jacobian, tolerance, max_iterations);

    t_1 = tvnj::scalar_multiplication(10.0/147.0, y_n);
    t_2 = tvnj::scalar_multiplication(-72.0/147.0, y_1);
    t_3 = tvnj::scalar_multiplication(225.0/147.0, y_2);
    t_4 = tvnj::scalar_multiplication(-400.0/147.0, y_3);
    t_5 = tvnj::scalar_multiplication(450.0/147.0, y_4);
    std::vector<double> t_6 = tvnj::scalar_multiplication(-360.0/147.0, y_5);
    y_previous = tvnj::vector_addition(t_2, t_1);
    y_previous = tvnj::vector_addition(t_3, y_previous);
    y_previous = tvnj::vector_addition(t_4, y_previous);
    y_previous = tvnj::vector_addition(t_5, y_previous);
    y_previous = tvnj::vector_addition(t_6, y_previous);
    std::vector<double> y_6 = tvnj::backward_differentiation_formula_implicit_newtons_method(function, t + dt * 6, dt * 60 / 147, y_5, y_previous, jacobian, tolerance, max_iterations);

    return y_6;
}

/**
 * @brief implicit
    for stiff problems
    adaptive step size
    any order differential equation

    dy_max: speed
    dy_min: accuracy
    dt_max: max time step size
    initial_step_size: starting step size
    time_span: time bounds
    function: function(double t, std::vector<double> y) -> std::vector<double>
    jacobian: jacobian(double t, std::vector<double> y) -> std::vector<double>
    root_finding_tolerance: accuracy of the step result
    root_finding_max_iterations: max iterations allowed to find the root in a step

    https://www.uni-muenster.de/imperia/md/content/physik_tp/lectures/ss2017/numerische_Methoden_fuer_komplexe_Systeme_II/rkm-1.pdf

    returns: [time_points, y]
 * 
 * @param function 
 * @param time_span 
 * @param y_i 
 * @param dt_max: 
 * @param initial_step_size 
 * @param dy_max 
 * @param dy_min 
 * @param jacobian 
 * @param root_finding_tolerance 
 * @param root_finding_max_iterations 
 * @return OrdinaryDifferentialEquationResult
 */
tvnj::OrdinaryDifferentialEquationResult tvnj::backward_differentiation_formula_order_6_implicit_newtons_method(std::function<std::vector<double>(double, std::vector<double>)> function, std::vector<double> time_span, std::vector<double> y_i, double dt_max, double initial_step_size, double dy_max, double dy_min, std::function<std::vector<double>(double, std::vector<double>)> jacobian, double root_finding_tolerance, size_t root_finding_max_iterations) {
    double dt = initial_step_size;
    double t_i = time_span[0];
    double t_f = time_span[1];
    std::vector<double> time_points = {t_i};
    double t = t_i;
    std::vector<std::vector<double>> y = {y_i};
    std::vector<double> y_integrated = y_i;

    int order = 6;
    double safety_factor = 0.9;

    while (t < t_f) {
        std::vector<double> y_integrated_new = tvnj::backward_differentiation_formula_order_6_implicit_newtons_method_step(y_integrated, t, dt, function, jacobian, root_finding_tolerance, root_finding_max_iterations);

        // predicted next y
        std::vector<double> slope_current = function(t, y_integrated);
        std::vector<double> y_next = tvnj::vector_addition(y_integrated, tvnj::scalar_multiplication(dt, slope_current));
        std::vector<double> y_difference_1 = tvnj::vector_abs(tvnj::vector_subtraction(y_next, y_integrated_new));

        // predicted current y
        std::vector<double> slope_next = function(t + dt, y_integrated_new);
        std::vector<double> y_previous = tvnj::vector_subtraction(y_integrated_new, tvnj::scalar_multiplication(dt, slope_next));
        std::vector<double> y_difference_2 = tvnj::vector_abs(tvnj::vector_subtraction(y_integrated, y_previous));

        double maximum = std::max(tvnj::max(y_difference_1), tvnj::max(y_difference_2));
        if (maximum > dy_max) { // predicted y max
            if (std::isnan(maximum) || std::isinf(maximum)) {
                dt /= 2;
            }
            else {
                dt *= safety_factor * std::pow(dy_max / maximum, 1.0 / (order + 1));
            }
        }
        else {
            y_integrated = y_integrated_new;
            y.push_back(y_integrated);
            t += dt;
            time_points.push_back(t);

            double minimum = std::min(tvnj::min(y_difference_1), tvnj::min(y_difference_2));
            if (minimum <= dy_min) { // predicted y min
                if (minimum == 0) {
                    dt *= 2;
                }
                else {
                    dt *= safety_factor * std::pow(dy_min / minimum, 1.0 / order);
                }

                if (dt > dt_max) {
                    dt = dt_max;
                }
            }
        }
    }

    // last step
    // the loop overshoots t_f for accuracy. we then get y_{t_f} without loss of accuracy
    if (time_points[time_points.size() - 1] > t_f) {
        t = time_points[time_points.size() - 2];
        dt = t_f - t;

        y[y.size() - 1] = tvnj::backward_differentiation_formula_order_6_implicit_newtons_method_step(y[y.size() - 2], t, dt, function, jacobian, root_finding_tolerance, root_finding_max_iterations);
        time_points[time_points.size() - 1] = t_f;
    }

    struct tvnj::OrdinaryDifferentialEquationResult result;
    result.t = time_points;
    result.y = y;
    return result;
}

std::vector<double> tvnj::vector_power(std::vector<double> array, double power) {
    std::vector<double> new_vector;
    size_t i = 0;
    while (i < array.size()) {
        new_vector.push_back(std::pow(array[i], power));
        i++;
    }
    return new_vector;
}

std::vector<double> tvnj::power_space(double start, double end, int samples, double power) {
    std::vector<double> space = tvnj::linear_space(0, 1, samples);
    space = tvnj::vector_subtraction(tvnj::ones<double>(samples), tvnj::vector_power(space, power));
    // scale normalized sequence to range [start, end]
    return tvnj::scalar_addition(start, tvnj::scalar_multiplication(end - start, space));
}

std::vector<double> tvnj::reverse_power_space(double start, double end, int samples, double power) {
    std::vector<double> space = tvnj::linear_space(0, 1, samples);
    tvnj::reverse<double>(space);
    space = tvnj::vector_subtraction(tvnj::ones<double>(samples), tvnj::vector_power(space, power));
    // scale normalized sequence to range [start, end]
    return tvnj::scalar_addition(start, tvnj::scalar_multiplication(end - start, space));
}

tvnj::ComplexNumber::ComplexNumber(double real, double imaginary, double frequency) {
    this->real = real;
    this->imaginary = imaginary;
    this->frequency = frequency;
};

tvnj::ComplexNumber::ComplexNumber(const tvnj::ComplexNumber & complexNum) {
    this->real = complexNum.real;
    this->imaginary = complexNum.imaginary;
    this->frequency = complexNum.frequency;
};

tvnj::ComplexNumber tvnj::ComplexNumber::multiply(tvnj::ComplexNumber complexNum) {
    double real = this->real * complexNum.real - this->imaginary * complexNum.imaginary;
    double imaginary = this->real * complexNum.imaginary + this->imaginary * complexNum.real;
    return tvnj::ComplexNumber(real, imaginary);
};

tvnj::ComplexNumber tvnj::ComplexNumber::multiply(double scalar) {
    double real = this->real * scalar;
    double imaginary = this->imaginary * scalar;
    return tvnj::ComplexNumber(real, imaginary);
};

tvnj::ComplexNumber tvnj::ComplexNumber::divide(tvnj::ComplexNumber complexNum) {
    const double denominator = complexNum.real * complexNum.real + complexNum.imaginary * complexNum.imaginary;
    double real = (this->real * complexNum.real + this->imaginary * complexNum.imaginary) / denominator;
    double imaginary = (this->imaginary * complexNum.real - this->real * complexNum.imaginary) / denominator;
    return tvnj::ComplexNumber(real, imaginary);
};

tvnj::ComplexNumber tvnj::ComplexNumber::divide(double scalar) {
    double real = this->real / scalar;
    double imaginary = this->imaginary / scalar;
    return tvnj::ComplexNumber(real, imaginary);
};

tvnj::ComplexNumber tvnj::ComplexNumber::add(tvnj::ComplexNumber complexNum) {
    return tvnj::ComplexNumber(this->real + complexNum.real, this->imaginary + complexNum.imaginary);
};

tvnj::ComplexNumber tvnj::ComplexNumber::subtract(tvnj::ComplexNumber complexNum) {
    return tvnj::ComplexNumber(this->real - complexNum.real, this->imaginary - complexNum.imaginary);
};

double tvnj::ComplexNumber::amplitude() {
    return std::sqrt(this->real * this->real + this->imaginary * this->imaginary);
};

double tvnj::ComplexNumber::phase() {
    return std::atan2(this->imaginary, this->real);
};

std::vector<tvnj::ComplexNumber> tvnj::discreteFourierTransform(std::vector<tvnj::ComplexNumber> &x) {
    const size_t N = x.size();
    std::vector<tvnj::ComplexNumber> frequencies;

    const double constant = -2.0 * std::numbers::pi / N;

    for (size_t k = 0; k < N; k++) {
        const double currentConstantK = constant * k;
        tvnj::ComplexNumber sum = tvnj::ComplexNumber();

        for (size_t n = 0; n < N; n++) {
            const double currentConstantn = currentConstantK * n;
            tvnj::ComplexNumber value = tvnj::ComplexNumber(std::cos(currentConstantn), std::sin(currentConstantn));
            value = x[n].multiply(value);
            sum = sum.add(value);
        }

        sum.frequency = k;

        frequencies.push_back(sum);
    }

    return frequencies;
}

void fastFourierTransformRecursiveImplementation(std::vector<tvnj::ComplexNumber> &x) {
    const size_t n = x.size();
    if (n == 1) {
        return;
    }

    const size_t nHalf = n / 2;

    std::vector<tvnj::ComplexNumber> even;
    std::vector<tvnj::ComplexNumber> odd;

    for (size_t i = 0; i < nHalf; i++) {
        even.push_back(x[i * 2]);
        odd.push_back(x[i * 2 + 1]);
    }

    fastFourierTransformRecursiveImplementation(even);
    fastFourierTransformRecursiveImplementation(odd);

    const double constant = -2.0 * std::numbers::pi / n;

    for (size_t i = 0; i < nHalf; i++) {
        const double theta = constant * i;
        tvnj::ComplexNumber t = tvnj::ComplexNumber(std::cos(theta), std::sin(theta));
        t = odd[i].multiply(t);
        x[i] = even[i].add(t);
        x[i + nHalf] = even[i].subtract(t);
    }
}

std::vector<tvnj::ComplexNumber> tvnj::fastFourierTransformRecursive(std::vector<tvnj::ComplexNumber> &x) {
    std::vector<tvnj::ComplexNumber> temp(x);

    fastFourierTransformRecursiveImplementation(temp);

    return temp;
}

size_t bit_reversal(size_t x, size_t n) {
    size_t bit = n >> 1;

    while (x & bit) {
        x ^= bit;
        bit >>= 1;
    }

    return x ^= bit;
}

std::vector<tvnj::ComplexNumber> tvnj::fastFourierTransformIterative(std::vector<tvnj::ComplexNumber> &x) {
    std::vector<tvnj::ComplexNumber> frequencies(x);
    const size_t N = frequencies.size();

    // bit reversal permutation
    size_t k = 0;

    for (size_t i = 1; i < N; i++) {
        k = bit_reversal(k, N);

        if (i < k) {
            tvnj::ComplexNumber temp = frequencies[i];
            frequencies[i] = frequencies[k];
            frequencies[k] = temp;
        }
    }

    const double constant = -2.0 * std::numbers::pi;

    for (size_t m = 2; m <= N; m *= 2) { // iterate through powers of 2
        const double theta = constant / m;
        tvnj::ComplexNumber w_m = tvnj::ComplexNumber(std::cos(theta), std::sin(theta));
        size_t mHalf = m / 2;

        for (size_t i = 0; i < N; i += m) {
            tvnj::ComplexNumber w = tvnj::ComplexNumber(1);

            for (size_t j = 0; j < mHalf; j++) {
                size_t index1 = i + j;
                size_t index2 = index1 + mHalf;

                tvnj::ComplexNumber u = frequencies[index1];
                tvnj::ComplexNumber t = frequencies[index2].multiply(w);
                frequencies[index1] = u.add(t);
                frequencies[index2] = u.subtract(t);
                w = w.multiply(w_m);
            }
        }
    }

    return frequencies;
}

std::vector<tvnj::ComplexNumber> tvnj::inverseDiscreteFourierTransform(std::vector<tvnj::ComplexNumber> &x) {
    const size_t N = x.size();
    std::vector<tvnj::ComplexNumber> frequencies;

    const double constant = 2.0 * std::numbers::pi / N;

    for (size_t k = 0; k < N; k++) {
        const double currentConstantK = constant * k;
        tvnj::ComplexNumber sum = tvnj::ComplexNumber();

        for (size_t n = 0; n < N; n++) {
            const double currentConstantn = currentConstantK * n;
            tvnj::ComplexNumber value = tvnj::ComplexNumber(std::cos(currentConstantn), std::sin(currentConstantn));
            value = x[n].multiply(value);
            sum = sum.add(value);
        }

        sum = sum.divide(N);
        sum.frequency = k;

        frequencies.push_back(sum);
    }

    return frequencies;
}

void inverseFastFourierTransformRecursiveImplementation(std::vector<tvnj::ComplexNumber> &x) {
    const size_t n = x.size();
    if (n == 1) {
        return;
    }

    const size_t nHalf = n / 2;

    std::vector<tvnj::ComplexNumber> even;
    std::vector<tvnj::ComplexNumber> odd;

    for (size_t i = 0; i < nHalf; i++) {
        even.push_back(x[i * 2]);
        odd.push_back(x[i * 2 + 1]);
    }

    inverseFastFourierTransformRecursiveImplementation(even);
    inverseFastFourierTransformRecursiveImplementation(odd);

    const double constant = 2.0 * std::numbers::pi / n;

    for (size_t i = 0; i < nHalf; i++) {
        const double theta = constant * i;
        tvnj::ComplexNumber t = tvnj::ComplexNumber(std::cos(theta), std::sin(theta));
        t = odd[i].multiply(t);
        x[i] = even[i].add(t);
        x[i + nHalf] = even[i].subtract(t);
    }
}

std::vector<tvnj::ComplexNumber> tvnj::inverseFastFourierTransformRecursive(std::vector<tvnj::ComplexNumber> &x) {
    std::vector<tvnj::ComplexNumber> temp(x);

    inverseFastFourierTransformRecursiveImplementation(temp);

    const size_t n = temp.size();
    for (size_t i = 0; i < n; i++) {
        temp[i] = temp[i].divide(n);
    }

    return temp;
}

std::vector<tvnj::ComplexNumber> tvnj::inverseFastFourierTransformIterative(std::vector<tvnj::ComplexNumber> &x) {
    std::vector<tvnj::ComplexNumber> frequencies(x);
    const size_t N = frequencies.size();

    // bit reversal permutation
    size_t k = 0;

    for (size_t i = 1; i < N; i++) {
        k = bit_reversal(k, N);

        if (i < k) {
            tvnj::ComplexNumber temp = frequencies[i];
            frequencies[i] = frequencies[k];
            frequencies[k] = temp;
        }
    }

    const double constant = 2.0 * std::numbers::pi;

    for (size_t m = 2; m <= N; m *= 2) { // iterate through powers of 2
        const double theta = constant / m;
        tvnj::ComplexNumber w_m = tvnj::ComplexNumber(std::cos(theta), std::sin(theta));
        size_t mHalf = m / 2;

        for (size_t i = 0; i < N; i += m) {
            tvnj::ComplexNumber w = tvnj::ComplexNumber(1);

            for (size_t j = 0; j < mHalf; j++) {
                size_t index1 = i + j;
                size_t index2 = index1 + mHalf;

                tvnj::ComplexNumber u = frequencies[index1];
                tvnj::ComplexNumber t = frequencies[index2].multiply(w);
                frequencies[index1] = u.add(t);
                frequencies[index2] = u.subtract(t);
                w = w.multiply(w_m);
            }
        }
    }

    for (size_t i = 0; i < N; i++) {
        frequencies[i] = frequencies[i].divide(N);
    }

    return frequencies;
}

tvnj::DualNumber::DualNumber(double real, double infinitesimal) {
    this->real = real;
    this->infinitesimal = infinitesimal;
};

tvnj::DualNumber::DualNumber(const tvnj::DualNumber & dualNum) {
    this->real = dualNum.real;
    this->infinitesimal = dualNum.infinitesimal;
};

tvnj::DualNumber tvnj::DualNumber::multiply(tvnj::DualNumber dualNum) {
    double real = this->real * dualNum.real;
    double infinitesimal = this->real * dualNum.infinitesimal + this->infinitesimal * dualNum.real;
    return tvnj::DualNumber(real, infinitesimal);
};

tvnj::DualNumber tvnj::DualNumber::multiply(double scalar) {
    double real = this->real * scalar;
    double infinitesimal = this->infinitesimal * scalar;
    return tvnj::DualNumber(real, infinitesimal);
};

tvnj::DualNumber tvnj::DualNumber::divide(tvnj::DualNumber dualNum) {
    double real = this->real / dualNum.real;
    double infinitesimal = (this->infinitesimal * dualNum.real - this->real * dualNum.infinitesimal) / (dualNum.real * dualNum.real);
    return tvnj::DualNumber(real, infinitesimal);
};

tvnj::DualNumber tvnj::DualNumber::divide(double scalar) {
    double real = this->real / scalar;
    double infinitesimal = this->infinitesimal / scalar;
    return tvnj::DualNumber(real, infinitesimal);
};

tvnj::DualNumber tvnj::DualNumber::add(tvnj::DualNumber dualNum) {
    return tvnj::DualNumber(this->real + dualNum.real, this->infinitesimal + dualNum.infinitesimal);
};

tvnj::DualNumber tvnj::DualNumber::subtract(tvnj::DualNumber dualNum) {
    return tvnj::DualNumber(this->real - dualNum.real, this->infinitesimal - dualNum.infinitesimal);
};
