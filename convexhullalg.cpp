//
//  convexhullalg.cpp
//  
//
//  Created by Andrew  on 6/15/16.
//
//

#include <iostream> //finds perimeter around a house using andrew's alg
#include <algorithm>
#include <vector>
#include <math.h>
using namespace std ;
struct Point{
    int x, y ;
}graphed[10002];
bool sorter(Point a, Point b)
{
    if (a.x == b.x) return (a.y < b.y) ;
    else return (a.x < b.x) ;
}
bool ccw(Point  a, Point  b, Point c)
{
    a.x  = a.x - b.x ;
    a.y = a.y - b.y ;
    c.x  = c.x - b.x ;
    c.y = c.y - b.y ;
    return ((1LL*a.x*c.y-1LL*a.y*c.x)<=0) ; //returns true as clockwise
}
int points ;
double answer ;
int main()
{
    cin >> points ;
    for (int i =0; i < points ; i++) //cin the points
    {
        cin >> graphed[i].x >> graphed[i].y ;
    }
    sort(graphed, graphed + points, sorter) ; //sort the points by x coordinates O(nlogn)
    vector <pair<int, int>> hull ;
    vector <pair<int, int>> hull2 ;
    Point last1, last2 ;
    for (int i = 0; i < points; i++) //lower hull  Time is O(n) since you only remove a point at most once
    {
        while(hull.size() >= 2)
        {
            
            last1.x = hull[hull.size()-1].first ;
            last1.y = hull[hull.size()-1].second ;
            last2.x = hull[hull.size()-2].first;
            last2.y = hull[hull.size()-2].second ;
            if (ccw(last1, last2, graphed[i])) hull.pop_back() ;
            else break ;
        }
        hull.push_back(make_pair(graphed[i].x, graphed[i].y)) ;
    }
    for (int i = points -1; i >= 0; i--) //upper hull
    {
        while(hull2.size() >= 2)
        {
            last1.x = hull2[hull2.size()-1].first ;
            last1.y = hull2[hull2.size()-1].second ;
            last2.x = hull2[hull2.size()-2].first;
            last2.y = hull2[hull2.size()-2].second ;
            if (ccw(last1, last2, graphed[i])) hull2.pop_back() ;
            else break ;
        }
        hull2.push_back(make_pair(graphed[i].x, graphed[i].y)) ;
    }
    for (int i = 0; i < hull2.size() ; i++) //merging the hulls
    {
        hull.push_back(hull2[i]) ;
    }
    for (int i = 0; i < hull.size() ; i++) //finding the perimeter
    {
        answer += sqrt(1LL*(hull[(i+1)%hull.size()].first-hull[i].first)*(hull[(i+1)%hull.size()].first-hull[i].first) + 1LL*(hull[(i+1)%hull.size()].second-hull[i].second)*(hull[(i+1)%hull.size()].second-hull[i].second)) ;
    }
    cout <<  (long long int)(answer+0.5) << endl ;
}
