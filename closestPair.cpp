#include <bits/stdc++.h>
#define ll long long
using namespace std;

struct point {
	ll x;
	ll y;
};

bool compX(point a, point b) {
	return a.x < b.x;
}

bool compY(point a, point b) {
	if(a.y < b.y)
		return true;
	if(a.y > b.y)
		return false;
	return a.x < b.x;
}

point result1, result2;
double minDist = DBL_MAX;

double euclideanDistance(point a, point b) {
	return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

double bruteMin(vector<point> &pointsByX, ll low, ll high) {
	ll i,j;
	double dist,bestDistance = DBL_MAX;
	for(i=low; i<=high; i++) {
		for(j=i+1; j<=high; j++) {
			dist = euclideanDistance(pointsByX[i], pointsByX[j]);
			if(dist < bestDistance) {
				bestDistance = dist;
				if(bestDistance < minDist) {
					minDist = bestDistance;
					result1 = pointsByX[i];
					result2 = pointsByX[j];
				}
			}
		}
	}
	return bestDistance;
}

double closestPair(vector<point> &pointsByX, vector<point> &pointsByY, ll low, ll high) {
	ll i,j,n = high - low + 1;
	if (n <= 3)	{
		return bruteMin(pointsByX, low, high);
	}

	ll mid = low + (high - low)/2;

	double distLeft = closestPair(pointsByX, pointsByY, low, mid);
	double distRight = closestPair(pointsByX, pointsByY, mid+1, high);

	double bestDistance = min(distLeft, distRight);

	vector<point> pointsInStrip;
	for(i=0; i<n; i++) {
        if(abs(pointsByY[i].x - pointsByX[mid].x) < bestDistance)
		    pointsInStrip.push_back(pointsByY[i]);
	}

	for(i=0; i<pointsInStrip.size(); i++) {
		for(j=i+1; j<pointsInStrip.size() && abs(pointsInStrip[i].y - pointsInStrip[j].y) < bestDistance; j++) {
			double dist = euclideanDistance(pointsInStrip[i], pointsInStrip[j]);
			if(dist < bestDistance) {
				bestDistance = dist;
                minDist = dist;
				result1 = pointsInStrip[i];
				result2 = pointsInStrip[j];
			}
		}
	}

	return bestDistance;
}

int main() {
	ll i,n;
	cin>>n;
	vector<point> pointsByX(n), pointsByY(n);
	for(i=0; i<n; i++) {
		cin>>pointsByX[i].x>>pointsByX[i].y;
		pointsByY[i].x = pointsByX[i].x;
		pointsByY[i].y = pointsByX[i].y;
	}
	sort(pointsByX.begin(), pointsByX.end(), compX);
	sort(pointsByY.begin(), pointsByY.end(), compY);

	cout<<"Shortest distance = "<<closestPair(pointsByX, pointsByY, 0, n-1)<<endl;
	cout<<"Points are ("<<result1.x<<","<<result1.y<<") and ("<<result2.x<<","<<result2.y<<")\n";
	return 0;
}
