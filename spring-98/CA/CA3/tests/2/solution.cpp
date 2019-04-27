#include <iostream>
#include <vector>
#include <set>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <map>

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

const int MAXN = 100 * 1000 + 10, MAXM = 100 * 1000 + 10, MAXL = 10;

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

int par[MAXN][MAXL], h[MAXN];
int mxw[MAXN][MAXL];
bool mark[MAXN];

void dfs(int x) {
  mark[x] = true;
  for (int i = 0; i < SZ(adj[x]); i ++) {
    int v = adj[x][i].X, w = adj[x][i].Y;
    if (!mark[v]) {
      par[v][0] = x, h[v] = h[x] + 1, mxw[v][0] = w;
      dfs(v);
    }
  }
}

pii get_parent(int x, int k) {
  int mx = 0;
  for (int i = 0; i < MAXL; i ++)
    if ((1 << i) & k) {
      mx = max(mx, mxw[x][i]);
      x = par[x][i];
    }
  return mp(x, mx);
}

pii lca(int x, int y) {
  if (h[y] > h[x]) swap(x, y);  
  pii tmp = get_parent(x, h[x] - h[y]);
  x = tmp.X;
  int mx = tmp.Y;

  // cerr << VAL(mx) << endl;

  if (x == y) return mp(x, mx);

  // cerr << VAL(x) << VAL(y) << endl;

  for (int i = MAXL - 1; i >= 0; i--)
    if (par[x][i] != par[y][i]) {
      mx = max(mx, max(mxw[x][i], mxw[y][i]));
      // cerr << VAL(i) << VAL(mx) << endl;
      x = par[x][i], y = par[y][i];
    }
  mx = max(mx, max(mxw[x][0], mxw[y][0]));
  return mp(par[x][0], mx);
}

void lca_init() {
  par[0][0] = -1;
  dfs(0);
  for (int i = 1; i < MAXL; i ++)
    for (int j = 0; j < n; j ++) {
      par[j][i] = par[par[j][i - 1]][i - 1];
      mxw[j][i] = max(mxw[j][i - 1], mxw[par[j][i - 1]][i - 1]);
    }
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
  lca_init();

  int q; cin >> q;
  while (q--) {
    int x, y; cin >> x >> y; x--, y--; 

    int mx_e = lca(x, y).Y;
    
    // cerr << VAL(mst_w) << VAL(get_w[mp(x, y)]) << VAL(mx_e) << endl;

    int ans = mst_w + get_w[mp(x, y)] - mx_e;
    cout << ans << endl;
  }
  return 0;
}
