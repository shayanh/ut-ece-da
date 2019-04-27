#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair
#define SQR(a) ((a) * (a))
#define SZ(x) ((int) (x).size())
#define ALL(x) (x).begin(), (x).end()
#define CLR(x, a) memset(x, a, sizeof x)
#define VAL(x) #x << " = " << (x) << "   "
#define FOREACH(i, x) for(__typeof((x).begin()) i = (x).begin(); i != (x).end(); i ++)
#define FOR(i, n) for (int i = 0; i < (n); i ++)
#define X first
#define Y second

typedef long long ll;
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;

const int MAXN = 100 * 1000 + 10;
const ll INF = 1e12;

ll dis[MAXN];
set<pii> s;
bool mark[MAXN];
vector<pii> adj[MAXN];
vector<int> closed[MAXN];

void dij(int start) {
	for (int i = 0; i < MAXN; i ++) dis[i] = INF;

	CLR(mark, 0); s.clear();
	mark[start] = true;
	dis[start] = 0;
	s.insert(mp(0, start));

	while (SZ(s)) {
		int x = s.begin()->Y; s.erase(s.begin());
		int t = dis[x];
		int c = 0;
		for (int i = 0; i < SZ(closed[x]); i++) {
			if (closed[x][i] == t) {
				t++;
				c++;
			}
		}

		for (int i = 0; i < SZ(adj[x]); i ++) {
			int v = adj[x][i].X;
			ll w = adj[x][i].Y + c;
			if (dis[v] > dis[x] + w) {
				if (mark[v]) s.erase(mp(dis[v], v));
				else mark[v] = true;
	
				dis[v] = dis[x] + w;
				s.insert(mp(dis[v], v));
			}
		}
	}
}

int main () {
	ios::sync_with_stdio(false);

	int n, m; cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int x, y, w; cin >> x >> y >> w; x--, y--;
		adj[x].pb(mp(y, w));
		adj[y].pb(mp(x, w));
	}
	for (int i = 0; i < n; i++) {
		int k; cin >> k;
		for (int j = 0; j < k; j++) {
			int t; cin >> t;
			closed[i].pb(t);
		}
		sort(ALL(closed[i]));
	}

	dij(0);
	cout << (dis[n - 1] == INF ? -1 : dis[n - 1]) << endl;
	return 0;
}

