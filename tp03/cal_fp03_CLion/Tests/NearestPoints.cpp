/*
 * NearestPoints.cpp
 */

#include <limits>
#include <thread>
#include <algorithm>
#include <cmath>
#include "NearestPoints.h"
#include "Point.h"

const double MAX_DOUBLE = std::numeric_limits<double>::max();

Result::Result(double dmin, Point p1, Point p2) {
	this->dmin = dmin;
	this->p1 = p1;
	this->p2 = p2;
}

Result::Result() {
	this->dmin = MAX_DOUBLE;
	this->p1 = Point(0,0);
	this->p2 = Point(0,0);
}

/**
 * Auxiliary functions to sort vector of points by X or Y axis.
 */
static void sortByX(vector<Point> &v, int left, int right)
{
	std::sort(v.begin( ) + left, v.begin() + right + 1,
		[](Point p, Point q){ return p.x < q.x || (p.x == q.x && p.y < q.y); });
}

static void sortByY(vector<Point> &v, int left, int right)
{
	std::sort(v.begin( ) + left, v.begin() + right + 1,
		[](Point p, Point q){ return p.y < q.y || (p.y == q.y && p.x < q.x); });
}

double dist(const Point &pt1, const Point &pt2){
    double dx = pt1.x - pt2.x, dy = pt1.y - pt2.y;
    return sqrt(dx*dx + dy*dy);
}

/**
 * Brute force algorithm O(N^2).
 */
Result nearestPoints_BF(vector<Point> &vp) {
    Result ret;
	const long N = vp.size();
	for(long i = 0; i < N; ++i){
	    for(long j = i+1; j < N; ++j){
            double d = dist(vp[i], vp[j]);
            if(d < ret.dmin){
                ret = Result(d, vp[i], vp[j]);
            }
	    }
	}
	return ret;
}

/**
 * Improved brute force algorithm, that first sorts points by X axis.
 */
Result nearestPoints_BF_SortByX(vector<Point> &vp) {
	Result res;
	sortByX(vp, 0, vp.size()-1);
	const long &N = vp.size();
	for(long i = 0; i < N; ++i){
        for(long j = i+1; (j < N) && (vp[j].x < vp[i].x + res.dmin); ++j){
	        double d = dist(vp[i], vp[j]);
	        if(d < res.dmin) res = Result(d, vp[i], vp[j]);
	    }
	}
	return res;
}


/**
 * Auxiliary function to find nearest points in strip, as indicated
 * in the assignment, with points sorted by Y coordinate.
 * The strip is the part of vp between indices left and right (inclusive).
 * "res" contains initially the best solution found so far.
 */
static void npByY(vector<Point> &vp, int left, int right, Result &res){
    for(int i = left; i <= right; ++i){
        for(int j = i+1; j <= right && (vp[j].y < vp[i].y + res.dmin); ++j){
            double d = dist(vp[i], vp[j]);
            if(d < res.dmin) res = Result(d, vp[i], vp[j]);
        }
    }
}

/**
 * Recursive divide and conquer algorithm.
 * Finds the nearest points in "vp" between indices left and right (inclusive),
 * using at most numThreads.
 */
static Result np_DC(vector<Point> &vp, int left, int right, int numThreads) {
    const long N = right-left+1;
	// Base case of two points
    if(N == 2) return Result(dist(vp[left], vp[left+1]), vp[left], vp[left+1]);
	// Base case of a single point: no solution, so distance is MAX_DOUBLE
    if(N == 1) return Result();
	// Divide in halves (left and right) and solve them recursively,
	// possibly in parallel (in case numThreads > 1)
	const long m = left+N/2;
	Result lr, rr;
	if(numThreads == 1){
	    lr = np_DC(vp, left, m-1, 1);
	    rr = np_DC(vp, m, right, 1);
	}else{
	    long n1 = numThreads/2;
	    long n2 = numThreads - n1;
	    vector<Point> *pvp = &vp;
	    Result *lrp = &lr;
        thread t([=](){ *lrp = np_DC(*pvp, left, m-1, n1); });
        rr = np_DC(vp, m, right, n2);
        t.join();
	}
	// Select the best solution from left and right
    Result ret = (lr.dmin <= rr.dmin ? lr : rr);
	// Determine the strip area around middle point
    const double X = vp[m].x;
    const double Xl = X - ret.dmin,
                 Xr = X + ret.dmin;
	// Order points in strip area by Y coordinate
    long l;{
        for(l = m; l >= left; --l){
            if(vp[l].x < Xl) break;
        }
        ++l;
    }
    long r;{
        for(r = m; r <= right; ++r){
            if(vp[r].x > Xr) break;
        }
        r--;
    }
    sortByY(vp, l, r);
    // Calculate nearest points in strip area (using npByY function)
    npByY(vp, l, r, ret);
    // Reorder points in strip area back by X coordinate
    sortByX(vp, l, r);
	return ret;
}

/**
 * Defines the number of threads to be used.
 */
static int numThreads = 1;
void setNumThreads(int num)
{
	numThreads = num;
}

/*
 * Divide and conquer approach, single-threaded version.
 */
Result nearestPoints_DC(vector<Point> &vp) {
	sortByX(vp, 0, vp.size() -1);
    return np_DC(vp, 0, vp.size() - 1, 1);
}


/*
 * Multi-threaded version, using the number of threads specified
 * by setNumThreads().
 */
Result nearestPoints_DC_MT(vector<Point> &vp) {
	sortByX(vp, 0, vp.size() -1);
	return np_DC(vp, 0, vp.size() - 1, numThreads);
}
