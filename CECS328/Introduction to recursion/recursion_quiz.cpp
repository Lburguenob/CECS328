#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <limits>
#include <string>

using namespace std;

struct Point {
    double x, y;
};

double euclideanDistance(const Point& a, const Point& b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return sqrt(dx*dx + dy*dy);
}

double closestPairDistance(const vector<Point>& pts) {
    double best = numeric_limits<double>::infinity();

    for (size_t i = 0; i < pts.size(); i++) {
        for (size_t j = i + 1; j < pts.size(); j++) {
            double d = euclideanDistance(pts[i], pts[j]);
            if (d < best) best = d;
        }
    }
    return best;
}

vector<Point> loadPoints(const string& filename) {
    vector<Point> pts;
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error: Could not open " << filename << endl;
        return pts;
    }

    string line;
    while (getline(file, line)) {
        // Remove braces and commas
        for (char& c : line) {
            if (c == '{' || c == '}' || c == ',')
                c = ' ';
        }

        stringstream ss(line);
        double x, y;
        if (ss >> x >> y) {
            pts.push_back({x, y});
        }
    }

    return pts;
}

int main() {
    vector<string> files = {
        "1.txt", "2.txt", "3.txt", "4.txt", "5.txt",
        "6.txt", "7.txt", "8.txt", "9.txt", "10-3.txt"
    };

    for (const string& fname : files) {
        vector<Point> pts = loadPoints(fname);

        if (pts.size() < 2) {
            cout << fname << ": Not enough points\n";
            continue;
        }

        double best = closestPairDistance(pts);
        cout << fname << " → Closest distance = " << best << endl;
    }

    return 0;
}
