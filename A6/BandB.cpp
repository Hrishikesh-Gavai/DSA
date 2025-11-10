#include <iostream>
using namespace std;

struct Item { int w, v; };
struct Node { int idx, w, v; double b; };

void sortByRatio(Item a[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-1-i; j++) {
            double r1 = (double)a[j].v / a[j].w;
            double r2 = (double)a[j+1].v / a[j+1].w;
            if (r1 < r2) {
                Item t = a[j]; a[j] = a[j+1]; a[j+1] = t;
            }
        }
    }
}

double bound(int idx, int W, int cw, int cv, Item a[], int n){
    if (cw >= W) return cv;
    double b = cv;
    int w = cw;
    for (int i = idx; i < n; i++) {
        if (w + a[i].w <= W) { w += a[i].w; b += a[i].v; }
        else { b += (W - w) * ((double)a[i].v / a[i].w); break; }
    }
    return b;
}

struct PQNode { double key; Node node; };
void push(PQNode heap[], int &sz, PQNode x){
    heap[++sz] = x;
    int i = sz;
    while (i > 1 && heap[i].key > heap[i/2].key) { PQNode t=heap[i]; heap[i]=heap[i/2]; heap[i/2]=t; i/=2; }
}
PQNode pop(PQNode heap[], int &sz){
    PQNode top = heap[1];
    heap[1] = heap[sz--];
    int i = 1;
    while (true) {
        int l = 2*i, r = 2*i+1, largest = i;
        if (l <= sz && heap[l].key > heap[largest].key) largest = l;
        if (r <= sz && heap[r].key > heap[largest].key) largest = r;
        if (largest == i) break;
        PQNode t = heap[i]; heap[i] = heap[largest]; heap[largest] = t;
        i = largest;
    }
    return top;
}

int main(){
    int n, W;
    cout << "Enter number of items: ";
    cin >> n;
    cout << "Enter knapsack capacity W: ";
    cin >> W;

    Item a[100];
    for (int i = 0; i < n; i++) {
        cout << "Enter weight and value of item " << (i+1) << ": ";
        cin >> a[i].w >> a[i].v;
    }

    sortByRatio(a, n);

    int best = 0;
    PQNode heap[10000]; int sz = 0; // simple max-heap priority queue
    Node root = {0, 0, 0, bound(0, W, 0, 0, a, n)};
    push(heap, sz, {root.b, root});

    while (sz > 0) {
        PQNode pqn = pop(heap, sz);
        Node u = pqn.node;
        if (u.b <= best) continue;
        if (u.idx == n) { if (u.v > best) best = u.v; continue; }

        // Include item
        if (u.w + a[u.idx].w <= W) {
            Node t = {u.idx+1, u.w + a[u.idx].w, u.v + a[u.idx].v, 0.0};
            t.b = bound(t.idx, W, t.w, t.v, a, n);
            if (t.b > best) push(heap, sz, {t.b, t});
            if (t.v > best) best = t.v;
        }
        // Exclude item
        Node s = {u.idx+1, u.w, u.v, 0.0};
        s.b = bound(s.idx, W, s.w, s.v, a, n);
        if (s.b > best) push(heap, sz, {s.b, s});
    }

    cout << "Branch and Bound optimum value = " << best << endl;
    return 0;
}
