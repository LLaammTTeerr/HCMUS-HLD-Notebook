struct pt {
    double x, y;
};

bool cmp (pt a, pt b) {
    return a.x < b.x || a.x == b.x && a.y < b.y;
}

bool cw (pt a, pt b, pt c) {
    return a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y) < 0;
}

bool ccw (pt a, pt b, pt c) {
    return a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y) > 0;
}

void convex_hull (vector<pt>& a) {
    if (a.size() == 1  || (a.size() == 2 && a[0].x == a[1].x && a[0].y == a[1].y)) {
        cout << 1 << endl;
        cout << a[0].x << " " << a[0].y << endl;
        return;
    }

    sort (a.begin(), a.end(), &cmp);

    pt p1 = a[0],  p2 = a.back();

    vector<pt> up, down;
    up.push_back (p1);
    down.push_back (p1);

    for(int i = 1; i < a.size(); ++i) {
        if(i == a.size() - 1 || cw(p1, a[i], p2)) {
            while(up.size() >= 2 
                && !cw (up[up.size()-2], up[up.size()-1], a[i]))
                    up.pop_back();

            up.push_back(a[i]);
        }

        if (i == a.size() - 1 || ccw(p1, a[i], p2)) {
            while (down.size() >= 2 
                && !ccw(down[down.size() - 2], down[down.size() - 1], a[i]))
                    down.pop_back();
            down.push_back(a[i]);
        }
    }
    
    cout << down.size() + up.size() - 2 << endl;
    for(int i = 0; i < down.size(); i++) 
        cout << down[i].x << " " << down[i].y << endl;
    for(int i = up.size() - 2; i > 0; i--) 
        cout << up[i].x << " " << up[i].y << endl;
}