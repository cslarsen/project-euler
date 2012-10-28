/*
 * ProjectEuler.net Problem 82
 * Solved by Christian Stigen Larsen
 *
 * Using a rather slow implementation of Dijkstra's path finding algorithm.
 */

#include <stdio.h>
#include <stdint.h>
#include <memory.h>
#include <iostream>
#include <fstream>

static uint32_t inf = (uint32_t)-1;

static const uint32_t xmax = 80;
static const uint32_t ymax = 80;

static uint32_t map[ymax][xmax];
static uint32_t dist[ymax][xmax];
static bool visited[ymax][xmax];
static uint32_t final = inf;

struct node {
  uint32_t x, y;

  node(uint32_t _x=0, uint32_t _y=0) : x(_x), y(_y)
  {
  }
};

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
  for ( size_t y=0; y<ymax; ++y )
  for ( size_t x=0; x<xmax; ++x ) {
    node i(x, y);
    uint32_t di = getdist(i);

    if ( !isvisited(i) && di < dr ) {
      r = i;
      dr = di;
    }
  }

  return r;
}

bool allvisited()
{
  // see if all target nodes have been visited
  for ( uint32_t y=0; y<ymax; ++y )
    if ( !isvisited(node(xmax-1, y)) )
      return false;

  return true;
}

void dijkstra(node& p)
{
  if ( !ok(p) || stop || isvisited(p) )
    return;

  // neighbors
  node a(p.x+1, p.y); // move right
  node b(p.x, p.y+1); // move down
  node c(p.x, p.y-1); // move up

  // tentative distances
  uint32_t d = getdist(p);
  uint32_t da = sum(d, getcost(a));
  uint32_t db = sum(d, getcost(b));
  uint32_t dc = sum(d, getcost(c));

  // update distances
  if ( !isvisited(a) && da < getdist(a) ) setdist(a, da);
  if ( !isvisited(b) && db < getdist(b) ) setdist(b, db);
  if ( !isvisited(c) && dc < getdist(c) ) setdist(c, dc);

  // mark this node
  setvisited(p);

  // has all dest nodes been visited?
  if ( allvisited() ) {
    // find the one with lowest distance
    final = getdist(node(xmax-1, 0));
    uint32_t ty=0;
    for ( ty=1; ty<ymax; ++ty ) {
      if ( getdist(node(xmax-1, ty)) < final )
        final = getdist(node(xmax-1, ty));
    }

    stop = true;
    return;
  }

  // find unvisited node with smallest distance
  node next = nextnode();
  if ( ok(next) )
    return dijkstra(next);
}

void readmap(const char* s)
{
  std::ifstream f;
  f.open(s);

  for ( size_t y=0; y<ymax; ++y )
  for ( size_t x=0; x<xmax; ++x ) {
    uint32_t v;
    f >> v;
    map[y][x] = v;
  }
}

int main()
{
  //readmap("small.txt");
  readmap("matrix.txt");

  uint32_t best = inf;

  for ( size_t Y=0; Y<ymax; ++Y ) {
    // set infinity distance for all nodes
    // set all nodes as unvisited
    for ( size_t y=0; y<ymax; ++y )
    for ( size_t x=0; x<xmax; ++x ) {
      dist[y][x] = inf;
      visited[y][x] = false;
    }

    // starting node
    node current(0,Y);
    setdist(current, getcost(current));

    // init new run
    final = inf;
    stop = false;

    dijkstra(current);

    if ( final < best ) {
      printf("Best distance so far for y=%u: %u\n", Y, final);
      best = final;
    }
  }

  printf("Smallest global distance: %u\n", best);
}
