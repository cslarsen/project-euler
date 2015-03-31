#include <stdio.h>
#include <stdint.h>
#include <memory.h>

#include "map.h" // real map with size (80, 80)

/*
uint32_t map[5][5] = {
  {131, 673, 234, 103, 18},
  {201, 96, 342, 965, 150},
  {630, 803, 746, 422, 111},
  {537, 699, 497, 121, 956},
  {805, 732, 524, 37, 331},
};
*/
static const uint32_t xmax = 80;
static const uint32_t ymax = 80;

static uint32_t inf = (uint32_t)-1;
static uint32_t smallest = inf;

static uint32_t dist[ymax][xmax] = {inf};
static bool visited[ymax][xmax] = {false};

struct node {
  uint32_t x, y;

  node(uint32_t _x=0, uint32_t _y=0) : x(_x), y(_y)
  {
  }
};

static inline uint32_t path_backtrack_slow(
  const uint32_t x,
  const uint32_t y,
  uint32_t acc=0)
{
  if ( x>=xmax || y>=ymax )
    return inf;

  acc += map[y][x];

  if ( x==(xmax-1) and y==(ymax-1) ) {
    if ( acc < smallest ) {
      smallest = acc;
      printf("%u\n", acc);
    }
    return acc;
  }

  if ( acc >= smallest )
    return inf;

  uint32_t s1 = path_backtrack_slow(x+1, y, acc);
  uint32_t s2 = path_backtrack_slow(x, y+1, acc);

  return s1<s2? s1 : s2;
}

bool ok(const node& n)
{
  return n.x<xmax && n.y<ymax;
}

uint32_t getcost(const node& n)
{
  return ok(n)? map[n.y][n.x] : inf;
}

void setdist(const node& n, const uint32_t& d)
{
  if ( ok(n) )
    dist[n.y][n.x] = d;
}

uint32_t getdist(const node& n)
{
  return ok(n)? dist[n.y][n.x] : inf;
}

bool isinf(const uint32_t a)
{
  return a == inf;
}

uint32_t sum(const uint32_t a, const uint32_t b)
{
  return isinf(a) || isinf(b)? inf : a+b;
}

void setvisited(const node& n)
{
  if ( ok(n) )
    visited[n.y][n.x] = true;
}

bool isvisited(const node& n)
{
  return ok(n)? visited[n.y][n.x] : false;
}

static bool stop = false;

// Return unvisited node with smallest tentative distance
static node nextnode()
{
  node r(xmax, ymax);
  uint32_t dr = inf;

  // slow, could use a set here instead
  for ( int y=0; y<ymax; ++y )
  for ( int x=0; x<xmax; ++x ) {
    node i(x, y);
    uint32_t di = getdist(i);

    if ( !isvisited(i) && di < dr ) {
      r = i;
      dr = di;
    }
  }

  return r;
}

void dijkstra(node& p)
{
  if ( !ok(p) || stop || isvisited(p) )
    return;

  // neighbors
  node a(p.x+1, p.y);
  node b(p.x, p.y+1);

  // tentative distances
  uint32_t d = getdist(p);
  uint32_t da = sum(d, getcost(a));
  uint32_t db = sum(d, getcost(b));

  // update distances
  if ( !isvisited(a) && da < getdist(a) ) setdist(a, da);
  if ( !isvisited(b) && db < getdist(b) ) setdist(b, db);

  // mark this node
  setvisited(p);

  // has dest node been visited?
  if ( isvisited(node(xmax-1, ymax-1)) ) {
    // ...
    uint32_t final = getdist(node(xmax-1, ymax-1));
    printf("Finished with distance %u\n", final);
    stop = true;
    return;
  }

  // find unvisited node with smallest distance
  node next = nextnode();
  if ( ok(next) ) dijkstra(next);
}

int main()
{
  // set infinity distance for all nodes
  memset(&dist, inf, sizeof(dist));

  // set all nodes as unvisited
  memset(&visited, false, sizeof(visited));

  // starting node
  node current(0,0);
  setdist(current, getcost(current));

  dijkstra(current);
  printf("Smallest distance: %u\n", getdist(node(xmax-1,ymax-1)));

  // the slow but reliable algo
  //path_backtrack_slow(0,0);
}
