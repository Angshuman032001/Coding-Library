template <class T> int sgn(T x) { return (x > 0) - (x < 0); }
template<class T>struct Point {
    typedef Point P;
    T x, y;
    explicit Point(T x=0, T y=0) : x(x), y(y) {}
    bool operator<(P p) const { return tie(x,y) < tie(p.x,p.y); }
    bool operator==(P p) const { return tie(x,y)==tie(p.x,p.y); }
    P operator+(P p) const { return P(x+p.x, y+p.y); }
    P operator-(P p) const { return P(x-p.x, y-p.y); }
    P operator*(T d) const { return P(x*d, y*d); }
    P operator/(T d) const { return P(x/d, y/d); }
    T dot(P p) const { return x*p.x + y*p.y; }
    T cross(P p) const { return x*p.y - y*p.x; }
    T cross(P a, P b) const { return (a-*this).cross(b-*this); }
    T dist2() const { return x*x + y*y; }
    double dist() const { return sqrt((double)dist2()); }
    double angle() const { return atan2(y, x); }
    P unit() const { return *this/dist(); } // makes dist()=1
    P perp() const { return P(-y, x); } // rotates +90 degrees
    P normal() const { return perp().unit(); }
    P rotate(double a) const { return P(x*cos(a)-y*sin(a),x*sin(a)+y*cos(a)); }
};

typedef Point<double> P;
bool cmp(P a, P b) {
    return a.x < b.x || (a.x == b.x && a.y < b.y);
}
bool cw(P a, P b, P c){
    return a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y) < 0;
}
bool ccw(P a, P b, P c) {
    return a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y) > 0;
}

vector<P> convexHull(vector<P> pts) {
    if (pts.size() == 1)
        return vector<P>();
    sort(pts.begin(), pts.end(), &cmp);
    P p1 = pts[0], p2 = pts.back();
    vector<P> up, down;
    up.push_back(p1);
    down.push_back(p1);
    for (int i = 1; i < (int)pts.size(); i++) {
        if (i == pts.size() - 1 || cw(p1, pts[i], p2)) {
            while (up.size() >= 2 && !cw(up[up.size()-2], up[up.size()-1], pts[i]))
                up.pop_back();
            up.push_back(pts[i]);
        }
        if (i == pts.size() - 1 || ccw(p1, pts[i], p2)) {
            while(down.size() >= 2 && !ccw(down[down.size()-2], down[down.size()-1], pts[i]))
                down.pop_back();
            down.push_back(pts[i]);
        }
    }
    vector<P>hull;
    for (int i = 0; i < (int)up.size(); i++)
        hull.push_back(up[i]);
    for (int i = down.size() - 2; i > 0; i--)
        hull.push_back(down[i]);
    return hull;
}
