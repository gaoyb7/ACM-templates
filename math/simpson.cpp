double f(double x);

double simpson(double a, double b) {
    return (f(a) + f(b) + 4.0 * f((a + b) / 2)) * (b - a) / 6;
}

double asr(double a, double b) {
    double m = (a + b) / 2;
    double s = simpson(a, b), s1 = simpson(a, m), s2 = simpson(m, b);
    if (!dcmp(s1 + s2 - s)) return s;
    return asr(a, m) + asr(m, b);
}
