#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-8;
const double pi = acos(-1);
typedef complex <double> point;
typedef point vec;
#define X real()
#define Y imag()

struct line {
    point s, t;
    double ang;
    line() {}
    line(point a, point b): s(a), t(b), ang(arg(b - a)) {}
};



//Basic
int dcmp(double x) {return x < -eps ? -1 : x > eps;}
bool zero(vec v) {return !dcmp(v.X) && !dcmp(v.Y);}

double sqr(double x) {return x * x;}
double dis(point a, point b) {return abs(a - b);}

double cross(vec a, vec b) {return a.X * b.Y - a.Y * b.X;}
double cross(point a, point b, point c) {return cross(b - a, c - a);}
double dot(vec a, vec b) {return a.X * b.X + a.Y * b.Y;}
double dot(point a, point b, point c) {return dot(b - a, c - a);}

vec dir(line ln) {return ln.t - ln.s;}
vec normal(vec v) {return vec(-v.Y, v.X);}
vec unit(vec v) {return v / abs(v);}

vec proj(vec v, vec n) {return n * dot(v, n) / norm(n);}
point proj(point p, line ln) {return ln.s + proj(p - ln.s, dir(ln));}
vec reflect(vec v, vec n) {return proj(v, n) * 2.0 - v;}
point reflect(point p, line ln) {return ln.s + reflect(p - ln.s, dir(ln));}

vec rotate(vec v, double a) {return v * polar(1.0, a);}
double angle(vec a, vec b) {return arg(b / a);}



//Line
double len(line ln) {return abs(ln.s - ln.t);}

bool onseg(point p, line ln) {
    return dcmp(cross(p, ln.s, ln.t)) == 0 && dcmp(dot(p, ln.s, ln.t)) <= 0;
}

double distoline(point p, line ln) {return fabs(cross(p, ln.s, ln.t)) / len(ln);}
double distoseg(point p, line ln) {
    if (dcmp(dot(ln.s, ln.t, p)) <= 0) return dis(p, ln.s);
    if (dcmp(dot(ln.t, ln.s, p)) <= 0) return dis(p, ln.t);
    return distoline(p, ln);
}

bool inter(line a, line b, point &p) {
    double s1 = cross(a.s, a.t, b.s);
    double s2 = cross(a.s, a.t, b.t);
    if (!dcmp(s1 - s2)) return false;
    p = (s1 * b.t - s2 * b.s) / (s1 - s2);
    return true;
}

bool seginter(line a, line b, point &p) {       //strict
    double s1 = cross(a.s, a.t, b.s), s2 = cross(a.s, a.t, b.t);
    if ((dcmp(s1) ^ dcmp(s2)) != -2) return false;
    double s3 = cross(b.s, b.t, a.s), s4 = cross(b.s, b.t, a.t);
    if ((dcmp(s3) ^ dcmp(s4)) != -2) return false;
    p = (s1 * b.t - s2 * b.s) / (s1 - s2);
    return true;
}



//Triangle
double area(double a, double b, double c) {
    double p = (a + b + c) * 0.5;
    return sqrt(p * (p - a) * (p - b) * (p - c));
}

double angle(double a, double b, double c) {
    return acos((sqr(a) + sqr(b) - sqr(c)) / (2 * a * b));
}

point circumcenter(point A, point B, point C) {
    double d1 = dot(A, B, C), d2 = dot(B, C, A), d3 = dot(C, A, B);
    double c1 = d2 * d3, c2 = d1 * d3, c3 = d1 * d2, c = c1 + c2 + c3;
    if (!dcmp(c)) return A;
    return ((c2 + c3) * A + (c1 + c3) * B + (c1 + c2) * C) / (2 * c);
}

point incenter(point A, point B, point C) {
    double a = abs(B - C), b = abs(C - A), c = abs(A - B);
    if (!dcmp(a + b + c)) return A;
    return (a * A + b * B + c * C) / (a + b + c);
}

point centroid(point A, point B, point C) {
    return (A + B + C) / 3.0;
}

point orthocenter(point A, point B, point C) {
    double d1 = dot(A, B, C), d2 = dot(B, C, A), d3 = dot(C, A, B);
    double c1 = d2 * d3, c2 = d1 * d3, c3 = d1 * d2, c = c1 + c2 + c3;
    if (!dcmp(c)) return A;
    return (c1 * A + c2 * B + c3 * C) / c;
}

point fermat(point A, point B, point C) {
    double a = abs(B - C), b = abs(C - A), c = abs(A - B);
    if (dot(A, B, C) / b / c < -0.5) return A;
    if (dot(B, C, A) / c / a < -0.5) return B;
    if (dot(C, A, B) / a / b < -0.5) return C;
    if (cross(A, B, C) < 0) swap(B, C);
    point CC = (B - A) * polar(1.0, -pi / 3) + A;
    point BB = (C - A) * polar(1.0, pi / 3) + A;
    point res;
    inter(line(B, BB), line(C, CC), res);
    return res;
}



//Circle
struct circle {
    point c; double r;
    circle(point c = 0, double r = 0): c(c), r(r) {}
    point pt(double a) {return c + polar(r, a);}
};

double adjust(double a) {
    while (a < -pi) a += 2 * pi;
    while (a > pi) a -= 2 * pi;
    return a;
}

int inter(circle c, line ln, point &p1, point &p2)
{
    point p = proj(c.c, ln);
    double d = dis(p, c.c);
    if (dcmp(d - c.r) > 0) return 0;
    vec v = sqrt(c.r * c.r - d * d) * unit(dir(ln));
    p1 = p - v; p2 = p + v;
    return dcmp(c.r - d) + 1;
}

int inter(circle c, line ln, double &a1, double &a2) {              //angle
    point p = proj(c.c, ln);
    double d = dis(p, c.c);
    if (dcmp(d - c.r) > 0) return 0;
    double alpha = arg(p - c.c), beta = acos(d / c.r);
    a1 = adjust(alpha - beta); a2 = adjust(alpha + beta);
    return dcmp(c.r - d) + 1;
}

int inter(circle a, circle b, point &p1, point &p2) {
    double d = dis(a.c, b.c);
    if (dcmp(d - (a.r + b.r)) > 0) return 0;                        // disjoint
    if (!dcmp(d) || dcmp(d - fabs(a.r - b.r)) < 0) return 0;        // include
    double d1 = (sqr(d) + sqr(a.r) - sqr(b.r)) / (2 * d), d2 = d - d1;
    point p = (d1 * b.c + d2 * a.c) / d;
    vec v = sqrt(sqr(a.r) - sqr(d1)) * unit(normal(b.c - a.c));
    p1 = p - v; p2 = p + v;
    return dcmp(a.r + b.r - d) + 1;
}

int inter(circle a, circle b, double &a1, double &a2) {
    double d = dis(a.c, b.c);
    if (dcmp(d - (a.r + b.r)) > 0) return 0;                        // disjoint
    if (!dcmp(d) || dcmp(d - fabs(a.r - b.r)) < 0) return 0;        // include
    double alpha = arg(b.c - a.c), beta = angle(a.r, d, b.r);
    a1 = adjust(alpha - beta); a2 = adjust(alpha + beta);
    return dcmp(a.r + b.r - d) + 1;
}

int tangent(circle c, point p, point &p1, point &p2) {
    double d = dis(p, c.c);
    if (dcmp(d - c.r) < 0) return 0;
    double d1 = c.r * c.r / d, d2 = d - d1;
    point p0 = (d1 * p + d2 * c.c) / d;
    vec v = sqrt(sqr(c.r) - sqr(d1)) * unit(normal(p - c.c));
    p1 = p0 - v; p2 = p0 + v;
    return dcmp(d - c.r) + 1;
}

int tangent(circle c, point p, double &a1, double &a2)
{
    double d = dis(p, c.c);
    if (dcmp(d - c.r) < 0) return 0;
    double alpha = arg(p - c.c), beta = acos(c.r / d);
    a1 = adjust(alpha - beta); a2 = adjust(alpha + beta);
    return dcmp(d - c.r) + 1;
}

int outer_tangent(circle a, circle b, double &a1, double &a2) {
    double d = dis(a.c, b.c);
    if (!dcmp(d) || dcmp(d - fabs(a.r - b.r)) < 0) return 0;
    double alpha = arg(b.c - a.c), beta = acos((a.r - b.r) / d);
    a1 = adjust(alpha - beta); a2 = adjust(alpha + beta);
    return dcmp(beta) + 1;
}

int inner_tangent(circle a, circle b, double &a1, double &a2) {
    double d = dis(a.c, b.c);
    if (!dcmp(d) || dcmp(d - (a.r + b.r)) < 0) return 0;
    double alpha = arg(b.c - a.c), beta = acos((a.r + b.r) / d);
    a1 = adjust(alpha - beta); a2 = adjust(alpha + beta);
    return dcmp(beta) + 1;
}
