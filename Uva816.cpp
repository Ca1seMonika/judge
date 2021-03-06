#include<iostream>
#include<cstring>
#include<vector>
#include<map>
#include<string>
#include<queue>
#include<algorithm>
using namespace std;
const int maxn = 9 + 5;
pair<int, int> startp;
pair<int, int> endp;
map<char, string> mp[maxn][maxn];
map<char, pair<int, int> > direction = {
    {'N', make_pair(-1, 0)}, {'E', make_pair(0, 1)}, {'S', make_pair(1, 0)}, {'W', make_pair(0, -1)}
};

struct Route {
    Route(pair<int, int> p, char d, vector<pair<int, int> > rp) : p(p), d(d), rp(rp) {}
    pair<int, int> p;
    char d;
    vector<pair<int, int> > rp;

};

ostream& operator<< (ostream& os, Route& q) {
    for (int i = 0; i < q.rp.size(); i++) {
        if (i % 10 == 0) cout << endl << "  ";
        else    cout << ' ';
        cout << '(' << q.rp[i].first << ',' << q.rp[i].second << ')';
    }
    return os;
}

void clr() {
    for (int i = 0; i < maxn; i++) {
        for (int j = 0; j < maxn; j++) {
            mp[i][j].clear();
        }
    }
}

char transfer(char pd, char rl) {
    char dl[] = { 'N', 'E', 'S', 'W', '\0' };
    int tar = strchr(dl, pd) - dl;
    if (rl == 'F') {
        return pd;
    }
    else if (rl == 'L') {
        return dl[(tar - 1) < 0 ? 3 : tar - 1];
    }
    else if (rl == 'R') {
        return dl[(tar + 1) % 4];
    }
    return 0;
}

bool bfs(pair<int, int> p, char d) {
    queue<Route> q; char a;
    vector<pair<pair<int, int>, char> > mark;
    q.push(Route(p, d, { startp }));
    while (!q.empty()) {
        Route t = q.front(); q.pop();
        if (t.p.first == endp.first && t.p.second == endp.second) {
            t.rp.push_back(t.p);
            cout << t << endl;
            return true;
        }
        if (find(mark.begin(), mark.end(), make_pair(t.p, t.d)) == mark.end()) {
            mark.push_back(make_pair(t.p, t.d));
        }else {
            continue;
        }
        string s = mp[t.p.first][t.p.second][t.d];
        for (int i = 0; i < s.size(); i++) {
            a = transfer(t.d, s[i]);
            Route tq = t;
            tq.d = a;
            tq.rp.push_back(tq.p);
            tq.p.first += direction[a].first;
            tq.p.second += direction[a].second;
            q.push(tq);
        }
    }
    return false;
}
int main() {
    /*
    freopen("test.in", "r", stdin);
    freopen("test.out", "w+", stdout);*/
    int py, px;
    char str[50], c, t[10];
    while (cin >> str && strcmp(str, "END")) {
        clr();
        cin >> startp.first >> startp.second >> c >> endp.first >> endp.second;
        while (cin >> py && py && cin >> px) {
            while (cin >> t && strcmp(t, "*")) {
                mp[py][px][t[0]] = string(t + 1);
            }
        }
        cout << str;
        if (!bfs(make_pair(startp.first + direction[c].first, startp.second + direction[c].second), c))
            cout << endl << "  No Solution Possible" << endl;
    }
}