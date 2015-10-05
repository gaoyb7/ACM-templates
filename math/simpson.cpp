double f(double x);

double simpson(double l, double r) {
    return (f(l) + f(r) + 4.0 * f((l + r) / 2)) * (r - l) / 6;
}

double asr(double a, double b) {
    double m = (l + r) / 2;
    double s = simpson(l, r), s1 = simpson(l, m), s2 = simpson(m, r);
    if (!dcmp(s1 + s2 - s)) return s;
    return asr(l, m) + asr(m, r);
}
