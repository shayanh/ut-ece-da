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

const int MAXN = 100 * 1000 + 10, MAXM = 200 * 1000 + 10;

int par2[MAXN];
pair <int, pii> e[MAXM];

int father(int x) {
	return par2[x] == -1 ? x : par2[x] = father(par2[x]);
}

bool merge(int x, int y) {
	x = father(x);
	y = father(y);
	if (x != y) par2[y] = x;
	return x != y;
}

int n, m;
int mst_w = 0;
vector<pii> adj[MAXN];

void kruskal() {
	fill(par2, par2 + n, -1);
	sort(e, e + m);
	for (int i = 0; i < m; i++) {
		int x = e[i].Y.X, y = e[i].Y.Y;
		int w = e[i].X;
		if (merge(x, y)) {
			adj[x].pb(mp(y, w));
			adj[y].pb(mp(x, w));
			mst_w += w;
		}
	}
}

bool mark[MAXN];

int dfs(int x, int target, int mx_e) {
	if (x == target) {
		return mx_e;
	}
	mark[x] = true;

	int res = 0;
	for (int i = 0; i < SZ(adj[x]); i++) {
	   int v = adj[x][i].X, w = adj[x][i].Y;
	   if (!mark[v]) {
		   res = max(res, dfs(v, target, max(mx_e, w)));
	   }
	}

	mark[x] = false;
	return res;
}

map<pii, int> get_w;

int main () {
	ios::sync_with_stdio(false);

	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int x, y, w; cin >> x >> y >> w; x--, y--;
		e[i] = mp(w, mp(x, y));
		get_w[mp(x, y)] = w;
	}
	kruskal();

	int q; cin >> q;
	while (q--) {
		int x, y; cin >> x >> y; x--, y--;

		int mx_e = dfs(x, y, 0);
		int ans = mst_w + get_w[mp(x, y)] - mx_e;
		cout << ans << endl;
	}
	return 0;
}

