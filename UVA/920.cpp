#include <bits/stdc++.h>

using namespace std;

#define EPS 1e-9

bool equals(double a, double b)
{
    return fabs(a - b) < EPS;
}

class Point {
public:
    double x;
    double y;
    double z;

    Point(double xv = 0, double yv = 0, double zv = 0) : x(xv), y(yv), z(zv) {}

    bool operator==(const Point& b)
	{
	    return equals(x, b.x) && equals(y, b.y) && equals(z, b.z);
	}

	bool operator < (const Point& p) const{

		if ( x > p.x )
			return true;
		else
			return false;
	}

};

using pp = pair<Point,Point>;

double distance(const Point& P, const Point& Q)
{
    return sqrt((P.x - Q.x)*(P.x - Q.x) + (P.y - Q.y)*(P.y - Q.y) + (P.z - Q.z)*(P.z - Q.z));
}

class Line {
public:
    double a;
    double b;
    double c;

    Line(double av, double bv, double cv) : a(av), b(bv), c(cv) {}

    Line(const Point& p, const Point& q)
    {
        a = p.y - q.y;
        b = q.x - p.x;
        c = p.x * q.y - p.y * q.x;

        auto k = a ? a : b;

        a /= k;
        b /= k;
        c /= k;
    }

    bool operator==(const Line& r) const
    {
        return equals(a, r.a) && equals(b, r.b) && equals(c, r.c);
    }

    bool parallel(const Line& r) const
    {
        return equals(a, r.a) && equals(b, r.b) && !equals(c, r.c);
    }

    bool orthogonal(const Line& r) const
    {
        return equals(a * r.a + b * r.b, 0);
    }

    double distance(const Point& p) const
    {
        return fabs(a*p.x + b*p.y + c)/hypot(a, b);
    }
};

#define INF -1

pair<int, Point> intersections(const Line& r, const Line& s)
{
    auto det = r.a * s.b - r.b * s.a;

    if (equals(det, 0))
    {
        // Coincidentes ou paralelas
        int qtd = (r == s) ? INF : 0;

        return pair<int, Point>(qtd, Point()); 
    } else  
    {
        // Concorrentes
        auto x = (-r.c * s.b + s.c * r.b) / det;
        auto y = (-s.c * r.a + r.c * s.a) / det;

        return pair<int, Point>(1, Point(x, y));
    }
}

class Segment {
public:
    Point A, B;

    Segment(const Point& Av, const Point& Bv) : A(Av), B(Bv) {}

    double length() const
    {
        return hypot(A.x - B.x, A.y - B.y);
    }

    bool contains(const Point& P) const
    {
        if (A.x == B.x)
            return min(A.y, B.y) <= P.y and P.y <= max(A.y, B.y);
        else
            return min(A.x, B.x) <= P.x and P.x <= max(A.x, B.x);
    }
};

bool is_between(Point a, Point c, Point b){

	return equals(distance(a,b) + distance(c,b), distance(a,b));
}

int main(){

	int test;

	scanf("%d", &test);

	int n;

	for ( int t = 0; t < test; t++ ){

		scanf("%d", &n);

		vector < Point > v;

		int x,y;

		for ( int i = 0; i < n; i++ ){

			scanf("%d %d", &x, &y);

			v.push_back(Point(x,y));
		}

		sort(v.begin(), v.end());

		double sunny_mountain = 0.0;

		if ( n == 0 or n == 1 ){

			printf("0.0000\n");
			continue;
		}

		Point biggest_height = v[0];

		for ( int i = 0; i < n; i++ ){

			if ( v[i].y > biggest_height.y ){

				Line l = Line(biggest_height, Point(0.0,biggest_height.y));

				auto par = intersections(Line(v[i], v[i-1]), l);

				sunny_mountain += distance(par.second, v[i]);

				biggest_height = v[i];
			}
		}

		printf("%.2lf\n", sunny_mountain);
	}
	
	return 0;
}