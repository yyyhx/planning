#pragma once

#include <Eigen/Dense>
#include <array>
#include <memory>
#include <vector>

#include "r_function.h"
//struct Point {
//  double x, y;
//};

class PiecewiseBezierFit3 {
 public:
  PiecewiseBezierFit3(const std::vector<Point> &points, double maxError);

  void fitCurve(const std::vector<Point> &points, double maxError);

  std::vector<std::array<Point, 4>> getControlPoints() const;
  std::vector<std::vector<Point>> getPiecewiseBezierCurvesPoints() const;

 private:
  std::vector<std::array<Point, 4>> control_points_;
  std::vector<std::vector<Point>> piecewise_bezier_curve_;

 public:
  std::vector<std::shared_ptr<RFunction>> RFuns;

  static double dot(const Point &p1, const Point &p2);

  Point q(const std::array<Point, 4> &ctrlPoly, double t);
  Point qprime(const std::array<Point, 4> &ctrlPoly, double t);
  Point qprimeprime(const std::array<Point, 4> &ctrlPoly, double t);
  Point normalize(const Point &v);

  std::vector<double> chordLengthParameterize(const std::vector<Point> &points);

  std::array<Point, 4> generateBezierControlPoint(
      const std::vector<Point> &points, const std::vector<double> &parameters,
      const Point &leftTangent, const Point &rightTangent);
  std::vector<std::array<Point, 4>>
  fitCubicBezier(const std::vector<Point> &points, const Point &leftTangent,
                 const Point &rightTangent, double error);

  std::vector<double> reparameterize(const std::array<Point, 4> &bezier,
                                     const std::vector<Point> &points,
                                     const std::vector<double> &parameters);
  double newtonRaphsonRootFind(const std::array<Point, 4> &bez,
                               const Point &point, double u);
  std::pair<double, int> computeMaxError(const std::vector<Point> &points,
                                         const std::array<Point, 4> &bez,
                                         const std::vector<double> &parameters);
  double binomial_coefficient(int n, int k);
  std::vector<Point> bezier_curve(const std::array<Point, 4> &control_points,
                                  int num_points);
  void generate_bezier_curves(
      const std::vector<std::array<Point, 4>> &control_points_list,
      int num_points);
  double getSdfDis(double x, double y, int p = 2);
  void composeTrimmingSdf();
  //  Point q2(const std::array<Point, 3> &ctrlPoly, double t);
  //  Point qprime2(const std::array<Point, 3> &ctrlPoly, double t);
  //  Point qprimeprime2(const std::array<Point, 3> &ctrlPoly, double t);
  //  std::array<Point, 3> computeControlPoint2(const std::vector<Point> &points, const Point &leftTangent, const Point &rightTangent);
  Point BezierII(int degree, const std::vector<Point> &V, double t);
  double objective_function(const Eigen::Vector2d &p1,
                            const Eigen::VectorXd &t_values,
                            const std::vector<Eigen::Vector2d> &points,
                            const std::vector<Eigen::Vector2d> &samples);
  Eigen::Vector2d cal_bezier_value(double t, const Eigen::Vector2d &p0,
                                   const Eigen::Vector2d &p1,
                                   const Eigen::Vector2d &p2);
  Eigen::Vector2d compute_gradient(const Eigen::Vector2d &p1,
                                   const Eigen::VectorXd &t_values,
                                   const std::vector<Eigen::Vector2d> &points,
                                   const std::vector<Eigen::Vector2d> &samples,
                                   double epsilon = 1e-6);
  std::array<Point, 3>
  calBezierControlPoint(const std::vector<Eigen::Vector2d> &points,
                        const Eigen::VectorXd &t_values,
                        const std::vector<Eigen::Vector2d> &samples,
                        double learning_rate = 0.01, int max_iterations = 1000);
};
