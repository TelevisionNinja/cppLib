#ifndef MATHUTILS_H
#define MATHUTILS_H

#include <vector>
#include <functional>
#include <limits>

namespace tvnj {
   double exponentiationBySquaring(double base, unsigned int power);
   double exponentiationBySquaring(double base, int power);

   /**
    * @brief time complexity: O(n)
    * 
    * @param std::vector<double> 
    * @param std::vector<double> 
    * @return double 
    */
   double integrate_trapezoid(std::vector<double> y, std::vector<double> x);

   /**
    * @brief slope formula
    * 
    * @param x_one 
    * @param y_one 
    * @param x_two 
    * @param y_two 
    * @return double 
    */
   double slope(double x_one, double y_one, double x_two, double y_two);

   /**
    * @brief time complexity: O(n + m)
    * 
    * @param interpolated_x 
    * @param x 
    * @param y 
    * @return std::vector<double> 
    */
   std::vector<double> linear_interpolation(std::vector<double> interpolated_x, std::vector<double> x, std::vector<double> y);

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
   std::vector<double> linear_space(double min, double max, int samples);

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
   double linear_interpolation_single_point(double x, double x_one, double y_one, double x_two, double y_two);

   /**
    * @brief time complexity: O(n)
    * 
    * @param y 
    * @param x 
    * @param initial 
    * @return std::vector<double> 
    */
   std::vector<double> integrate_cumulative_trapezoid(std::vector<double> y, std::vector<double> x, double initial = NULL);

   std::vector<double> scalar_multiplication(double scalar, std::vector<double> array);

   std::vector<double> scalar_division(double scalar, std::vector<double> array);

   std::vector<double> vector_addition(std::vector<double> array1, std::vector<double> array2);

   std::vector<double> vector_subtraction(std::vector<double> array1, std::vector<double> array2);

   std::vector<double> vector_division(std::vector<double> array1, std::vector<double> array2);

   /**
    * @brief explicit
       for non-stiff problems
      any order differential equation

      y_n: initial y
      t: time step
      dt: time step size
      function: function(t:double, y: std::vector<double>, args, kwargs) -> std::vector<double>

      returns: y_{n+1}
   * 
   * @param y_n 
   * @param t 
   * @param dt 
   * @param function 
   * @param args 
   * @param kwargs 
   * @return std::vector<double> 
   */
   std::vector<double> runge_kutta_order_4_explicit_step(std::vector<double> y_n, double t, double dt, std::function<std::vector<double>(double, std::vector<double>)> function);

   struct OrdinaryDifferentialEquationResult {
      std::vector<double> t;
      std::vector<std::vector<double>> y;
   };

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
      function: function(t:double, y: std::vector<double>, args, kwargs) -> std::vector<double>

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
   OrdinaryDifferentialEquationResult runge_kutta_order_4_explicit(std::function<std::vector<double>(double, std::vector<double>)> function, std::vector<double> time_span, std::vector<double> y_i, double dt_max = std::numeric_limits<double>::infinity(), double initial_step_size = 0.01, double dy_max = 0.1, double dy_min = 0.001);

   /**
    * @brief no overflow midpoint formula
    * 
    * @param low 
    * @param high 
    * @return double 
    */
   double midpoint_no_overflow(double low, double high);

   /**
    * @brief midpoint formula
    * 
    * @param a 
    * @param b 
    * @return double 
    */
   double midpoint(double a, double b);

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
   double bisection(std::function<double(double)> function, double a, double b, size_t max_iterations = 1024);

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
   double secant(std::function<double(double)> function, double a, double b, size_t max_iterations = 1024);

   /**
    * @brief root finding algorithm

      x: inital guess for x
      function: function(x:double) -> double
      derivative: derivative(x:double) -> double
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
   double newtons_method(std::function<double(double)> function, double x, std::function<double(double)> derivative = NULL, double tolerance = 0.0000001, size_t max_iterations = 1024);

   std::vector<double> vector_abs(std::vector<double> array);

   bool contains_nan_or_infinity(std::vector<double> array);

   /**
    * @brief x: initial x guess
       t: time step
      dt: time step size
      y_previous: the addition of all previous y"s. ex: y_{n} + y_{n-1} + ...
      function: function(t:double, x: std::vector<double>, args, kwargs) -> std::vector<double>
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
   std::vector<double> backward_differentiation_formula_implicit_fixed_point_iteration(std::function<std::vector<double>(double, std::vector<double>)> function, double t, double dt, std::vector<double> x, std::vector<double> y_previous, double tolerance = 0.0000001, size_t max_iterations = 1024);

   /**
    * @brief implicit
       for stiff problems
      any order differential equation
      https://en.wikipedia.org/wiki/Backward_differentiation_formula

      y_n: initial y
      t: time step
      dt: time step size
      function: function(t:double, y: std::vector<double>, args, kwargs) -> std::vector<double>
      tolerance: accuracy of the result
      max_iterations: max iterations allowed to find the root

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
   std::vector<double> backward_differentiation_formula_order_6_implicit_fixed_point_iteration_step(std::vector<double> y_n, double t, double dt, std::function<std::vector<double>(double, std::vector<double>)> function, double tolerance = 0.0000001, size_t max_iterations = 1024);

   std::vector<double> scalar_addition(double scalar, std::vector<double> array);

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
      function: function(t:double, y: std::vector<double>, args, kwargs) -> std::vector<double>
      root_finding_tolerance: accuracy of the step result
      root_finding_max_iterations: max iterations allowed to find the root in a step

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
   OrdinaryDifferentialEquationResult backward_differentiation_formula_order_6_implicit_fixed_point_iteration(std::function<std::vector<double>(double, std::vector<double>)> function, std::vector<double> time_span, std::vector<double> y_i, double dt_max = std::numeric_limits<double>::infinity(), double initial_step_size = 0.01, double dy_max = 0.1, double dy_min = 0.001, double root_finding_tolerance = 0.0000001, size_t root_finding_max_iterations = 1024);

   /**
    * @brief x: initial x guess
       t: time step
      dt: time step size
      y_previous: the addition of all previous y"s. ex: y_{n} + y_{n-1} + ...
      function: function(t:double, x: std::vector<double>, args, kwargs) -> std::vector<double>
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
   std::vector<double> backward_differentiation_formula_implicit_newtons_method(std::function<std::vector<double>(double, std::vector<double>)> function, double t, double dt, std::vector<double> x, std::vector<double> y_previous, double tolerance = 0.0000001, size_t max_iterations = 1024);

   /**
    * @brief implicit
       for stiff problems
      any order differential equation
      https://en.wikipedia.org/wiki/Backward_differentiation_formula

      y_n: initial y
      t: time step
      dt: time step size
      function: function(t:double, y: std::vector<double>, args, kwargs) -> std::vector<double>
      tolerance: accuracy of the result
      max_iterations: max iterations allowed to find the root

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
   std::vector<double> backward_differentiation_formula_order_6_implicit_newtons_method_step(std::vector<double> y_n, double t, double dt, std::function<std::vector<double>(double, std::vector<double>)> function, double tolerance = 0.0000001, size_t max_iterations = 1024);

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
      function: function(t:float, y: list, args, kwargs) -> list
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
   * @param root_finding_tolerance 
   * @param root_finding_max_iterations 
   * @return OrdinaryDifferentialEquationResult
   */
   OrdinaryDifferentialEquationResult backward_differentiation_formula_order_6_implicit_newtons_method(std::function<std::vector<double>(double, std::vector<double>)> function, std::vector<double> time_span, std::vector<double> y_i, double dt_max = std::numeric_limits<double>::infinity(), double initial_step_size = 0.01, double dy_max = 0.1, double dy_min = 0.001, double root_finding_tolerance = 0.0000001, size_t root_finding_max_iterations = 1024);
}

#endif
