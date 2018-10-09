#include <ctime>
#include <cstdlib>
#include <vector>
#include <queue>
#include <string>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
typedef unsigned int UI;
typedef unsigned long long ULL;

const int hashEXACT = 0;
const int hashALPHA = 1;
const int hashBETA  = 2;
const int TOTALNUM = 25;
const int TOTALKIND = 12;
const int UPPER_RANGE_L = 11, UPPER_RANGE_R = 16;
const int LOWER_RANGE_L = 0, LOWER_RANGE_R = 5;
const int H = 17;
const int W = 5;
const int dx[8] = {-1, 1, 0, 0, 1, 1, -1, -1};
const int dy[8] = {0, 0, -1, 1, 1, -1, 1, -1};
const int INF = 1 << 25;
int s[24] = {128000, 64000, 32000, 16000, 8000, 4000, 2000, 1000, 35000, 70000, 35000, INF, 
 -128000, -64000, -32000, -16000, -8000, -4000, -2000, -1000, -35000, -70000, -35000, -INF};
const int test = (1 << 20) - 1;

int rounds = 0;
int id;
int map[H][W];
int mp[H][W], judge[H][W], his[H][W][H][W] ,hit, cnt, score;
UI key0, side0, keycheck0[24][H][W];
ULL keycheck1[24][H][W], keycheck2[24][H][W], keycheck3[24][H][W], key1, key2, key3, side1, side2, side3; 
int no = 1 << 30, win = (1 << 25) - 50, turn = 0,  maxdepth = 1, maxvalue = 1 << 25, step = 0, pos = 0;
double tle = 0.0;

int f[H][W] = {
0, 0, 0, 0, 0,
1, 1, 1, 1, 1,
1, 0, 0, 0, 1,
1, 0, 0, 0, 1,
1, 0, 0, 0, 1,
1, 1, 1, 1, 1,
1, 0, 1, 0, 1,
0, 0, 0, 0, 0,
1, 0, 1, 0, 1,
0, 0, 0, 0, 0,
1, 0, 1, 0, 1,
1, 1, 1, 1, 1,
1, 0, 0, 0, 1,
1, 0, 0, 0, 1,
1, 0, 0, 0, 1,
1, 1, 1, 1, 1,
0, 0, 0, 0, 0
};

int y[H][W] = {
0, 0, 0, 0, 0,
0, 0, 0, 0, 0,
0, 1, 0, 1, 0,
0, 0, 1, 0, 0,
0, 1, 0, 1, 0,
0, 0, 0, 0, 0,
0, 0, 0, 0, 0,
0, 0, 0, 0, 0,
0, 0, 0, 0, 0,
0, 0, 0, 0, 0,
0, 0, 0, 0, 0,
0, 0, 0, 0, 0,
0, 1, 0, 1, 0,
0, 0, 1, 0, 0,
0, 1, 0, 1, 0,
0, 0, 0, 0, 0,
0, 0, 0, 0, 0 
};

int h[H][W] = {
0, 1, 0, 1, 0,
0, 0, 0, 0, 0,
0, 0, 0, 0, 0,
0, 0, 0, 0, 0,
0, 0, 0, 0, 0,
0, 0, 0, 0, 0,
0, 0, 0, 0, 0,
0, 0, 0, 0, 0,
0, 0, 0, 0, 0,
0, 0, 0, 0, 0,
0, 0, 0, 0, 0,
0, 0, 0, 0, 0,
0, 0, 0, 0, 0,
0, 0, 0, 0, 0,
0, 0, 0, 0, 0,
0, 0, 0, 0, 0,
0, 1, 0, 1, 0,
};

int l[H][W] = {
0, 0, 0, 0, 0,
0, 0, 1, 0, 1,
0, 1, 0, 1, 0,
1, 0, 1, 0, 1,
0, 1, 0, 1, 0,
1, 0, 1, 0, 0,
0, 0, 0, 0, 0,
0, 0, 0, 0, 0,
0, 0, 0, 0, 0,
0, 0, 0, 0, 0,
0, 0, 0, 0, 0,
0, 0, 1, 0, 1,
0, 1, 0, 1, 0,
1, 0, 1, 0, 1,
0, 1, 0, 1, 0,
1, 0, 1, 0, 0,
0, 0, 0, 0, 0
};

int r[H][W] = {
0, 0, 0, 0, 0,
1, 0, 1, 0, 0,
0, 1, 0, 1, 0,
1, 0, 1, 0, 1,
0, 1, 0, 1, 0,
0, 0, 1, 0, 1,
0, 0, 0, 0, 0,
0, 0, 0, 0, 0,
0, 0, 0, 0, 0,
0, 0, 0, 0, 0,
0, 0, 0, 0, 0,
1, 0, 1, 0, 0,
0, 1, 0, 1, 0,
1, 0, 1, 0, 1,
0, 1, 0, 1, 0,
0, 0, 1, 0, 1,
0, 0, 0, 0, 0,
};

bool exist(int x, int y) {
    return (LOWER_RANGE_L <= x && x <= LOWER_RANGE_R && 0 <= y && y < W)
    || (UPPER_RANGE_L <= x && x <= UPPER_RANGE_R && 0 <= y && y < W)
    || ((x == 6 || x == 8 || x == 10) && (y == 0 || y == 2 || y == 4));
}

void change() {
    int x, y, xx, yy, col, kind;
    cin >> x >> y >> xx >> yy >> col >> kind;
    //cerr << "Get updates:"  << "\n";
  //  cerr << x << ' ' << y << ' ' << xx << ' ' << yy << ' ' << col << ' ' << kind << "\n";
    int tar = col * TOTALKIND + kind;
    if (x == xx && y == yy) map[x][y] = tar;
    else {
        map[x][y] = -2;
        map[xx][yy] = tar;
    }
}

UI rand32(){
    UI  r = rand() % 2;
    for(int i = 1; i <= 31; ++i) r = (r << 1) | (rand() % 2) ;
    return r;
}

ULL rand64(){
    ULL  r = rand() % 2;
    for(int i = 1; i <= 63; ++i) r = (r << 1) | (rand() % 2) ;
    return r;
}

inline int mod(int x){
  if(x <= 11) return x;
    return x - 12;
}


void key(){ 
  srand(time(NULL));
  side0 = rand32();
  for (int k = 0; k < 24; ++k) 
    for (int i = 0; i < 17; ++i) 
       for (int j = 0; j < 5; ++j)
      keycheck0[k][i][j] = rand32();
  side1 = rand64();
  for (int k = 0; k < 24; ++k) 
    for (int i = 0; i < 17; ++i) 
       for (int j = 0; j < 5; ++j)
      keycheck1[k][i][j] = rand64();
  side2 = rand64();
  for (int k = 0; k < 24; ++k) 
    for (int i = 0; i < 17; ++i) 
       for (int j = 0; j < 5; ++j)
      keycheck2[k][i][j] = rand64();
  side3 = rand64();
  for (int k = 0; k < 24; ++k) 
    for (int i = 0; i < 17; ++i) 
       for (int j = 0; j < 5; ++j)
      keycheck3[k][i][j] = rand64();
}

struct Move{
  int x, xx, y, yy;
};

Move nomove, bestmove, tem;

bool cmp(Move a, Move b){

  return his[a.x][a.y][a.xx][a.yy] > his[b.x][b.y][b.xx][b.yy]; 
}

struct node{
  ULL check1, check2, check3;
  int depth;
  int value;
  int flag;
  int step;
  Move goodmove;
};
node table[test + 1];

bool tran(Move a){
          int x = a.x, y = a.y, xx = a.xx, yy = a.yy;
          turn += 1;
          if(mp[xx][yy] == 23 || mp[xx][yy] == 11) return true;
              key0 ^= side0;
              key1 ^= side1;
              key2 ^= side2;
              key3 ^= side3;
              score -= s[mp[x][y]];
              key0 ^= keycheck0[mp[x][y]][x][y];
              key1 ^= keycheck1[mp[x][y]][x][y];
              key2 ^= keycheck2[mp[x][y]][x][y];
              key3 ^= keycheck3[mp[x][y]][x][y];
              if(mp[xx][yy] != -2){
                key0 ^= keycheck0[mp[xx][yy]][xx][yy];
                key1 ^= keycheck1[mp[xx][yy]][xx][yy];
                key2 ^= keycheck2[mp[xx][yy]][xx][yy];
                key3 ^= keycheck3[mp[xx][yy]][xx][yy];
                score -= s[mp[xx][yy]];
          } 
          if(mp[xx][yy] == -2) mp[xx][yy] = mp[x][y]; 
            else if(mod(mp[xx][yy]) == 9 && mod(mp[x][y]) != 8) ;
            else if(mod(mp[xx][yy]) == 9 && mod(mp[x][y]) == 8) mp[xx][yy] = mp[x][y];
            else if(mod(mp[xx][yy]) == 10) mp[xx][yy] = -2;
            else if(mod(mp[x][y]) == 10) mp[xx][yy] = -2;
            else if(mod(mp[x][y]) < mod(mp[xx][yy])) mp[xx][yy] = mp[x][y];
            else if(mod(mp[x][y]) == mod(mp[xx][yy])) mp[xx][yy] = -2;
            else if(mod(mp[x][y]) > mod(mp[xx][yy])) ;
          mp[x][y] = -2;
          if(mp[xx][yy] != -2){
              key0 ^= keycheck0[mp[xx][yy]][xx][yy];
              key1 ^= keycheck1[mp[xx][yy]][xx][yy];
              key2 ^= keycheck2[mp[xx][yy]][xx][yy];
              key3 ^= keycheck3[mp[xx][yy]][xx][yy];
              score += s[mp[xx][yy]];
      }     
          if(!id){if((mp[16][1] >= 0 && mp[16][1] <= 10) || (mp[16][3] >= 0 && mp[16][3] <= 10))  score -= 150000;}
            else{if(mp[0][1] >= 12  || mp[0][3] >= 12)  score += 150000;}

          return false;
}


int read(int depth,int alpha, int beta, Move &mv){
  int i = key0 & test;
  // cerr <<i <<"\n";
  node A;
  A = table[i];
  int t = A.value;
  if(A.step != step) return no;
  if (A.check1 == key1 && A.check2 == key2 && A.check3 == key3) {
    if (A.value > win) t = A.value - turn;
    if (A.value < -win)  t = A.value + turn;
    if (A.depth >= depth) {
      hit++;
      if (A.flag == hashEXACT) return t;
      if (A.flag == hashALPHA && t <= alpha) return alpha;
      if (A.flag == hashBETA && t >= beta) return beta;
      mv = A.goodmove;
    }
  }
  return no;
}


void save(int value, int depth, int type, Move mv){
  int i = key0 & test;
  //cerr <<i <<"\n";
  node A;
  if (value > win)  value = value + turn;
  if (value < -win)  value = value - turn;
  A.value = value;
  A.check1 = key1;
  A.check2 = key2;
  A.check3 = key3;
  A.depth = depth;
  A.flag  = type;
  A.goodmove = mv;
  A.step = step;
  if(table[i].step != step) table[i] = A;
  else if(table[i].check1 == key1 && table[i].check2 == key2 && table[i].check3 == key3) {
    if(table[i].depth < depth) table[i] = A;
  }
  else table[i] = A;
}

struct point{
    int x,  y;
    point(int x = 0, int y = 0): x(x), y(y){}
};


void expand(int &n, int side, Move children[]) {
   // cerr <<depth <<'d'<<"\n";
    if(!side){
        for(int i = 16 ; i >= 0; --i)
           for(int j = 4 ; j >= 0; --j){
           if(mp[i][j] == -2 || mp[i][j] >= 12 || mp[i][j] % 12 == 9 || mp[i][j] % 12 == 11 || h[i][j] ) continue;
           if(!f[i][j]){
              for(int k = 0; k <= 3; ++k){
                int a = i + dx[k];
                int b = j + dy[k];
                if(!exist(a, b) || (mp[a][b] >= 0 && mp[a][b] <= 11)) continue;
                if( y[a][b] && mp[a][b] != -2 ) continue; 
                  else {
                    Move s; 
                    s.x = i, s.y = j, s.xx = a, s.yy = b;
                    children[++n] = s;
           //         cerr<<i<<' '<<j<<' '<<a<<' '<<b<<"\n";
                  }
              }
            }
            else if(mp[i][j] % 12 != 8){
            int a = i, b = j;
            while (true) {
                 a += 1;
                 if(!exist(a, b) && exist(a + 1, b)) a += 1;
                 if(!exist(a, b) || (mp[a][b] >= 0 && mp[a][b] <= 11)) break;
                 if( y[a][b] && mp[a][b] != -2 ) break; 
                 if(a - i >= 2 && !f[a][b]) break;
                 Move s;
                 s.x = i, s.y = j, s.xx = a, s.yy = b;
                 children[++n] = s;
                 if(mp[a][b] != -2 || !f[a][b])  break; 
        }
            a = i, b = j;
            while(true) {
                 a -= 1;
                 if(!exist(a, b) && exist(a - 1, b)) a -= 1;
                 if(!exist(a, b) || (mp[a][b] >= 0 && mp[a][b] <= 11)) break;
                 if( y[a][b] && mp[a][b] != -2 ) break; 
                 if(i - a >= 2 && !f[a][b]) break;
                 Move s;
                 s.x = i, s.y = j, s.xx = a, s.yy = b;
                 children[++n] = s;
                 if(mp[a][b] != -2 || !f[a][b])  break; 
            }
            a = i, b = j;
            while(true){
                 b += 1;
                 if(!exist(a, b) && exist(a, b + 1)) b += 1;
                 if(!exist(a, b) || (mp[a][b] >= 0 && mp[a][b] <= 11)) break;
                 if( y[a][b] && mp[a][b] != -2 ) break; 
                 if(b - j >= 2 && !f[a][b]) break;
                 Move s;
                 s.x = i, s.y = j, s.xx = a, s.yy = b;
                 children[++n] = s;
                 if(mp[a][b] != -2 || !f[a][b])  break; 
           }
           a = i, b = j;
            while (true){
                 b -= 1;
                 if(!exist(a, b) && exist(a, b - 1)) b -= 1;
                 if(!exist(a, b) || (mp[a][b] >= 0 && mp[a][b] <= 11)) break;
                 if( y[a][b] && mp[a][b] != -2 ) break; 
                 if(j - b >= 2 && !f[a][b]) break;
                 Move s;
                 s.x = i, s.y = j, s.xx = a, s.yy = b;
                 children[++n] = s;
                 if(mp[a][b] != -2 || !f[a][b])  break; 
            }
        }
        else {
           memset(judge, 0 ,sizeof(judge));
           queue<point> p;
           p.push(point(i ,j));
           judge[i][j] = 1;
           while(!p.empty()){
             point u = p.front();
             p.pop();
           int aa = u.x,  bb = u.y;
           for(int ii = 0; ii <= 3; ++ii){
                int a = aa + dx[ii];
                int b = bb + dy[ii];
             if(!exist(a, b) && exist(a + dx[ii], b + dy[ii])) a += dx[ii], b += dy[ii];
             if(!exist(a, b) || (!f[a][b] && (aa != i || bb != j)) || (mp[a][b] >= 0 && mp[a][b] <= 11) || judge[a][b]) continue;
             if( y[a][b] && mp[a][b] != -2 ) continue;
             Move s;
             s.x = i, s.y = j, s.xx = a, s.yy = b;
             children[++n] = s;
             judge[a][b] = 1;
             if(mp[a][b] == -2 && f[a][b]) p.push(point(a, b));
             //cerr<<i<<' '<<j<<' '<<a<<' '<<b<<"\n";
             }
          }
    }
      if(l[i][j]){
          int a = i + 1;
          int b = j - 1;
          if(!exist(a, b) || (mp[a][b] >= 0 && mp[a][b] <= 11) || a == 0 || a == 16) ;
           else if( y[a][b] && mp[a][b] != -2 ) ;
           else{
            Move s;
            s.x = i, s.y = j, s.xx = a, s.yy = b;
            children[++n] = s;
           }
           a = i - 1;
           b = j + 1;
          if(!exist(a, b) || (mp[a][b] >= 0 && mp[a][b] <= 11) || a == 0 || a == 16) ;
           else if( y[a][b] && mp[a][b] != -2 ) ;
           else{
            Move s;
            s.x = i, s.y = j, s.xx = a, s.yy = b;
            children[++n] = s;
           }
        if(r[i][j]){
          int a = i + 1;
          int b = j + 1;
          if(!exist(a, b) || (mp[a][b] >= 0 && mp[a][b] <= 11) || a == 0 || a == 16) ;
           else if( y[a][b] && mp[a][b] != -2 ) ;
           else{
            Move s;
            s.x = i, s.y = j, s.xx = a, s.yy = b;
            children[++n] = s;
           }
           a = i - 1;
           b = j - 1;
           if(!exist(a, b) || (mp[a][b] >= 0 && mp[a][b] <= 11) || a == 0 || a == 16 ) ;
            else if( y[a][b] && mp[a][b] != -2 ) ;
            else{
             Move s;
             s.x = i, s.y = j, s.xx = a, s.yy = b;
             children[++n] = s;
          }
        }
      }
    }
  }    
      
    else {
      for(int i = 0 ; i <= 16; ++i)
           for(int j = 0 ; j <= 4; ++j){
                if(mp[i][j] <= 11 || mp[i][j] % 12 == 9 || mp[i][j] % 12 == 11 || h[i][j]) continue;
                if(!f[i][j]){
                for(int k = 0; k <= 3; ++k){
                int a = i + dx[k];
                int b = j + dy[k];
                if(!exist(a, b) || mp[a][b] >= 12) continue;
                if( y[a][b] && mp[a][b] != -2 ) continue; 
                  else { 
                    Move s;
                    s.x = i, s.y = j, s.xx = a, s.yy = b;
                    children[++n] = s;
                  //  cerr<<i<<' '<<j<<'S'<<a<<' '<<b<<"\n";
                  }
                }
           }
           else if(mp[i][j] % 12 != 8) {
            int a = i, b = j;
            while (true) {
                 a += 1;
                 if(!exist(a, b) && exist(a + 1, b)) a += 1;
                 if(!exist(a, b) || mp[a][b] >= 12) break;
                 if( y[a][b] && mp[a][b] != -2 ) break; 
                 if(a - i >= 2 && !f[a][b]) break;
                 Move s;
                 s.x = i, s.y = j, s.xx = a, s.yy = b;
                 children[++n] = s;
                 if(mp[a][b] != -2 || !f[a][b])  break; 
           //      cerr<<i<<' '<<j<<'A'<<a<<' '<<b<<"\n";
           }
            a = i, b = j;
            while (true){
                 a -= 1;
                 if(!exist(a, b) && exist(a - 1, b)) a -= 1;
                 if(!exist(a, b) || mp[a][b] >= 12) break;
                 if( y[a][b] && mp[a][b] != -2 ) break; 
                 if(i - a >= 2 && !f[a][b]) break;
                 Move s;
                 s.x = i, s.y = j, s.xx = a, s.yy = b;
                 children[++n] = s;
             //    cerr<<i<<' '<<j<<'B'<<a<<' '<<b<<"\n"; 
                 if(mp[a][b] != -2 || !f[a][b])  break;
            }
            a = i, b = j;
            while (true){
                 b += 1;
                 if(!exist(a, b) && exist(a, b + 1)) b += 1;
                 if(!exist(a, b) || mp[a][b] >= 12) break;
                 if( y[a][b] && mp[a][b] != -2 ) break; 
                 if(b - j >= 2 && !f[a][b]) break;
                 Move s;
                 s.x = i, s.y = j, s.xx = a, s.yy = b;
                 children[++n] = s;
               //  cerr<<i<<' '<<j<<'C'<<a<<' '<<b<<"\n";
                 if(mp[a][b] != -2 || !f[a][b])  break; 
            }
            a = i, b = j;
            while(true) {
                 b -= 1;
                 if(!exist(a, b) && exist(a, b - 1)) b -= 1;
                 if(!exist(a, b) || mp[a][b] >= 12) break;
                 if( y[a][b] && mp[a][b] != -2 ) break; 
                 if(j - b >= 2 && !f[a][b]) break;
                 Move s;
                 s.x = i, s.y = j, s.xx = a, s.yy = b;
                 children[++n] = s;
                // cerr<<i<<' '<<j<<'D'<<a<<' '<<b<<"\n"; 
                 if(mp[a][b] != -2 || !f[a][b])  break; 
           }
        }
         else {
          memset(judge, 0, sizeof(judge));
          queue<point> p;
          p.push(point(i ,j));
          judge[i][j] = 1;
           while(!p.empty()){
             point u = p.front();
             p.pop();
           int aa = u.x,  bb = u.y;
           for(int ii = 0; ii <= 3; ++ii ){
                int a = aa + dx[ii];
                int b = bb + dy[ii];
             if(!exist(a, b) && exist(a + dx[ii], b + dy[ii])) a += dx[ii], b += dy[ii];
             if(!exist(a, b) || (!f[a][b] && (aa != i || bb != j)) || mp[a][b] >= 12  || judge[a][b]) continue;
             if( y[a][b] && mp[a][b] != -2 ) continue;
             Move s;
             s.x = i, s.y = j, s.xx = a, s.yy = b;
             children[++n] = s;
             judge[a][b] = 1;
             if(mp[a][b] == -2 && f[a][b]) p.push(point(a, b));
            }
          }
        }
        if(l[i][j]){
          int a = i + 1;
          int b = j - 1;
          if(!exist(a, b) || mp[a][b] >= 12 || a == 0 || a == 16) ;
           else if( y[a][b] && mp[a][b] != -2 ) ;
           else{
            Move s;
            s.x = i, s.y = j, s.xx = a, s.yy = b;
            children[++n] = s;
           }
           a = i - 1;
           b = j + 1;
          if(!exist(a, b) || mp[a][b] >= 12 || a == 0 || a == 16) ;
           else if( y[a][b] && mp[a][b] != -2 ) ;
           else{
            Move s;
            s.x = i, s.y = j, s.xx = a, s.yy = b;
            children[++n] = s;
           }
        if(r[i][j]){
          int a = i + 1;
          int b = j + 1;
          if(!exist(a, b) || mp[a][b] >= 12 || a == 0 || a == 16) ;
           else if( y[a][b] && mp[a][b] != -2 ) ;
           else{
            Move s;
            s.x = i, s.y = j, s.xx = a, s.yy = b;
            children[++n] = s;
           }
           a = i - 1;
           b = j - 1;
           if(!exist(a, b) || mp[a][b] >= 12 || a == 0 || a == 16) ;
            else if( y[a][b] && mp[a][b] != -2 ) ;
            else{
             Move s;
             s.x = i, s.y = j, s.xx = a, s.yy = b;
             children[++n] = s;
          }
        }
      }
    }
  }
} 

int getScore(int side){

     return side == 0 ? score : -score;
}

int alphabeta(int depth, int alpha, int beta, int side) {   
    cnt++;
    int value, best, PV = 0, n = -1;
    Move children[180];
    Move mv, goodmove;
    mv = goodmove = nomove;
    value = read(depth,alpha,beta,mv);
    if (value != no) {if(pos >= 10) value += (rand() % 20);  return value;}
    if(((clock() - tle) / CLOCKS_PER_SEC) >= 0.98)  return no; 
    best = -no;
    int alphaflag = 1;
    if(depth <= 0){
      cnt++;
      value = getScore(side);
      save(value,depth,hashEXACT,nomove); 
      if(pos >= 10) value += (rand() % 20); 
      return value;
    }   
    else{ 
      if(mv.x != -1) children[++n] = mv;
      expand(n, side, children);  
      sort(children, children + n + 1, cmp);
      for(int i = 0 ; i <= n; ++i){
      mv = children[i];
      int x0 = mv.x, x1 = mv.xx, y0 = mv.y, y1 = mv.yy;
      UI pre0 = key0;ULL pre1 = key1, pre2 = key2, pre3 = key3;int pr0 = mp[x0][y0], pr1 = mp[x1][y1], prs = score;
      if (tran(mv)) value = maxvalue - turn;
      else {
      		if(PV){
			  value = -alphabeta(depth -1, -alpha-1, -alpha, 1 - side);
					if(value > alpha && value < beta) value = -alphabeta(depth - 1, -beta, -alpha, 1 - side);
				}
	                else value = -alphabeta(depth - 1, -beta, -alpha, 1 - side);
}
    //  if(depth == maxdepth && maxdepth == 7) cerr<<mv.x<<' '<<mv.y<<' '<<mv.xx<<' '<<mv.yy<<' '<<value<<"\n";    
      turn -= 1;
      mp[x0][y0] = pr0, mp[x1][y1] = pr1, key0 = pre0, key1 = pre1, key2 = pre2, key3 = pre3, score = prs;   
      if(value >= beta){
        cnt++;
        save(value,depth,hashBETA,children[i]);
        his[mv.x][mv.y][mv.xx][mv.yy] += depth * depth;
        return value;
     }             
     if (value > best) {
        best = value;
        goodmove = children[i];
        if(value > alpha){
          alphaflag = 0;
          PV = 1;
          alpha = value;
          if(depth == maxdepth)
          { if(((clock() - tle) / CLOCKS_PER_SEC) <= 0.98) bestmove = mv;}      
        }
      }           
    }
    his[goodmove.x][goodmove.y][goodmove.xx][goodmove.yy] += depth * depth;
    if (alphaflag == 1) save(best,depth,hashALPHA,goodmove);  
      else save(best,depth,hashEXACT,goodmove);   
    return best;
  }
}

void show_init(int id)
{
  //give a initializing map here
  //this line : kind1 kind2 ... etc
  //Imagine that the chesses are listed from the bottom to the top, left to right
  //This is a stupid start:
  int opt[2][25] = { 9, 11, 9, 7, 6, 3, 9, 6, 7, 7, 6, 4, 8, 4, 8, 3, 5, 0, 10, 10, 1, 8, 2, 5, 2 , 
  9 ,11 ,9 ,7 ,6 ,6 ,9 ,8 ,5 ,6 ,7 ,4 ,5 ,3 ,4 ,2 ,7 ,10 ,3 ,10 ,1 ,8 ,0 ,8, 2};
  int ran = rand() % 2;
  for (int i = 0; i < 25; ++i)
    cout << opt[ran][i] << ' ';
    cout << "\n";
}

void get_init()
{
  int arr0[25], arr1[25];
  for (int i = 0; i < 25; ++i)
  {
    cin >> arr0[i];
  }
  for (int i = 0; i < 25; ++i)
  {
    cin >> arr1[i];
    arr1[i] += TOTALKIND;
  }
  map[0][0] = arr0[0];
  map[0][1] = arr0[1];
  map[0][2] = arr0[2];
  map[0][3] = arr0[3];
  map[0][4] = arr0[4];
  map[1][0] = arr0[5];
  map[1][1] = arr0[6];
  map[1][2] = arr0[7];
  map[1][3] = arr0[8];
  map[1][4] = arr0[9];
  map[2][0] = arr0[10];
  map[2][2] = arr0[11];
  map[2][4] = arr0[12];
  map[3][0] = arr0[13];
  map[3][1] = arr0[14];
  map[3][3] = arr0[15];
  map[3][4] = arr0[16];
  map[4][0] = arr0[17];
  map[4][2] = arr0[18];
  map[4][4] = arr0[19];
  map[5][0] = arr0[20];
  map[5][1] = arr0[21];
  map[5][2] = arr0[22];
  map[5][3] = arr0[23];
  map[5][4] = arr0[24];

  map[16][0] = arr1[4];
  map[16][1] = arr1[3];
  map[16][2] = arr1[2];
  map[16][3] = arr1[1];
  map[16][4] = arr1[0];
  map[15][0] = arr1[9];
  map[15][1] = arr1[8];
  map[15][2] = arr1[7];
  map[15][3] = arr1[6];
  map[15][4] = arr1[5];
  map[14][0] = arr1[12];
  map[14][2] = arr1[11];
  map[14][4] = arr1[10];
  map[13][0] = arr1[16];
  map[13][1] = arr1[15];
  map[13][3] = arr1[14];
  map[13][4] = arr1[13];
  map[12][0] = arr1[19];
  map[12][2] = arr1[18];
  map[12][4] = arr1[17];
  map[11][0] = arr1[24];
  map[11][1] = arr1[23];
  map[11][2] = arr1[22];
  map[11][3] = arr1[21];
  map[11][4] = arr1[20];
}

void make_decision(int &x, int &y, int &xx, int &yy) {         
          tle = clock();
		  step++;
		  //cerr << "Step"<<step<<"\n";
		  int b1 = 0, b2 = 0, b3 = 0, b4 = 0, c1 = 7, c2 = 20; 
          score = 0;
          key0 = rand32(), key1 = rand64(), key2 = rand64(), key3 = rand64();
          memset(his, 0, sizeof(his));
          for(int i = 16 ; i >= 0; --i)
           for(int j = 4 ; j >= 0; --j){
            if(map[i][j] == 8) b1++;
            if(map[i][j] == 20) b2++;
            //if(map[i][j] == 10) b3++;
            //if(map[i][j] == 22) b4++;
            if(map[i][j] >= 0 && map[i][j] <= 8) c1 = min(map[i][j], c1);
            if(map[i][j] >= 12 && map[i][j] <= 20) c2 = min(map[i][j], c2);
       } 
          if(b1 == 3) s[8] = 20000;
            else if(b1 == 2) s[8] = 35000;
            else if(b1 == 1) s[8] = 65000;
          if(b2 == 3) s[20] = -20000;
            else if(b2 == 2) s[20] = -35000;
            else if(b2 == 1) s[20] = -65000;
          s[10] = s[c1] / 2;
          s[22] = s[c2] / 2; 
          s[10] = min(s[10], 35000);
          s[22] = max(s[22], -35000);
          for(int i = 16 ; i >= 0; --i)
           for(int j = 4 ; j >= 0; --j){
              mp[i][j] = map[i][j];
              if(mp[i][j] != -2){ key0 ^= keycheck0[mp[i][j]][i][j], key1 ^= keycheck1[mp[i][j]][i][j],
			  key2 ^= keycheck2[mp[i][j]][i][j], key3 ^= keycheck3[mp[i][j]][i][j];
              score += s[mp[i][j]];
              }
          }         
          for(maxdepth = 1 ; maxdepth <= 20; maxdepth++){
              cnt = 0 , hit = 0;
              int v = alphabeta(maxdepth, -maxvalue, maxvalue, id);
              //cerr<<maxdepth<<' '<<cnt<<' '<<hit<<":   "<<bestmove.x<<' '<<bestmove.y<<' '<<bestmove.xx<<' '<<bestmove.yy<<' '<<v<<"\n";
			  if(((clock() - tle) / CLOCKS_PER_SEC) >= 0.98)  break;
			  if(v >= win && v <= maxvalue) cerr<<"Bingo!"<<"\n";
              his[bestmove.x][bestmove.y][bestmove.xx][bestmove.yy] += INF;
              his[tem.x][tem.y][tem.xx][tem.yy] -= INF;
              tem = bestmove;
          }
         // cerr<<"Stop in depth "<<maxdepth<<"\n";
          x = bestmove.x, y = bestmove.y ,xx = bestmove.xx, yy = bestmove.yy;  
          if(mp[xx][yy] == -2) pos++;
          else pos = 0;
          //cerr << "Trying " << x << ", " << y << " to " << xx << ", " << yy << "\n";
          return;
}

inline void end() {
    std::cout << "END\n" << std::flush;
}

int main() {   
    key();
    nomove.x = -1;
    nomove.y = -1;
    nomove.xx = -1;
    nomove.yy = -1;
    tem.x = 0;
    tem.y = 0;
    tem.xx = 0;
    tem.yy = 0;
    memset(table, 0, (test + 1) * sizeof(node));

    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {
            map[i][j] = -2;
        }
    }
    string op;
    while (true) {
        cin >> op;
        if (op == "id") {
            cin >> id;
      //  cerr << id << "\n";
            cout << "linhonghao" << "\n";
            end();
    } else if (op == "refresh") {
      get_init();
        } else if (op == "init") {
      show_init(id);
      end();
    } else if (op == "message") {
            change();
        } else if (op == "action") {
            int x, y, xx, yy;
            make_decision(x, y, xx, yy);
            //cerr << x << " " << y << " " << xx << " " << yy << "\n";
            cout << x << " " << y << " " << xx << " " << yy << "\n";
            end();
        }
    }
} 

 
