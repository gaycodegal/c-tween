#include <stdio.h>
#include <stdlib.h>

typedef struct s_rect {
  int x;
  int y;
  int w;
  int h;
} rect;

typedef struct s_tween {
  int *val;
  float dx;
  float dt;
  int cdx;
  int s;
  int type;
} tween;

rect *new_rect(int x, int y, int w, int h){
  rect *r = (rect *)malloc(sizeof(rect));
  r->x = x;
  r->y = y;
  r->w = w;
  r->h = h;
  return r;
}

tween *new_tween(int *val, float dx, float dt){
  tween *t = (tween *)malloc(sizeof(tween));
  printf("new tween on %p\n", val);
  t->val = val;
  t->dx = dx;
  t->dt = dt;
  t->cdx = 0;
  t->s = 0;
  t->type = 0;
  return t;
}

int dotween(tween *t, int e){
  if(t->s == 0)
    t->s = e;
  int dt = e - t->s;
  int done = 0;
  if(dt >= t->dt){
    dt = t->dt;
    done = 1;
  }
  float fdt = (float)dt / t->dt;
  int cdx = (int)(t->dx * fdt);
  *(t->val) += cdx - t->cdx;
  t->cdx = cdx;
  return !done;
}

int print_rect(rect *r){
  printf("rect: (%i %i %i %i)\n", r->x, r->y, r->w, r->h);
}

int main(char *argc, char **argv){
  printf("linear integer tweening tests\n");
  rect *r = new_rect(10,20,30,40);
  print_rect(r);
  tween *tx = new_tween(&(r->x), 10.0f, 10.0f);
  tween *ty = new_tween(&(r->y), 20.0f, 30.0f);
  tween *tw = new_tween(&(r->w), -40.0f, 30.0f);
  tween *th = new_tween(&(r->h), -110.0f, 5.0f);
  int e = 1;
  while(dotween(tx, e) + dotween(ty, e) + dotween(tw, e) + dotween(th, e)){
    ++e;
    print_rect(r);
  }
  print_rect(r);
  return 0;
}
