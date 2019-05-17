#include <iostream>
#include "xpaint.h"
#include "xmat.h"
#include <vector>
#include <list>
#include <queue>
using namespace std;

struct Pos{
    int l, c;
    Pos(int l, int c){
        this->l = l;
        this->c = c;
    }
};

vector<Pos> get_neibs(int l, int c){
    return vector<Pos> {Pos(l, c - 1), Pos(l - 1, c), Pos(l, c + 1), Pos(l + 1, c)};
}
 
bool has_value(vector<string> &mat, int l, int c, char value){
    if(l < 0 || l >= (int) mat.size())
        return false;
    if(c < 0 || c >= (int) mat[0].size())
        return false;
    return mat[l][c] == value;
}

void paint(vector<string> &mat,int l, int c, char cor_base, char cor_final){
    if(!has_value(mat, l, c, cor_base))
        return;
    mat[l][c] = cor_final;
    xmat_draw(mat);
    x_step("pathfind");
    for(auto neibs : get_neibs(l, c)){
        paint(mat, neibs.l, neibs.c, cor_base, cor_final);
    }
}


void show(vector<vector<int>>& mat_int, vector<string>& mat, queue<Pos> row){
    xmat_draw(mat);
    while(!row.empty()){
        xmat_put_circle(row.front().l, row.front().c, WHITE);
        row.pop();
    }
    for(int l = 0; l < (int) mat.size(); l++){
        for(int c = 0; c < (int) mat[0].size(); c++){
            xmat_put_number(l, c, BLACK, mat_int[l][c]);
        }
    }
    x_step("pathfind"); 

}

void floodfill(vector<vector<int>>& mat_int, vector<string>& mat, int l, int c, char cor_base, char cor_final){
    queue<Pos> row;
    row.push(Pos(l, c));
    mat[l][c] = cor_final;
    while(!row.empty()){
        Pos ref = row.front();
        row.pop();
        for(auto neibs : get_neibs(ref.l, ref.c)){
            if(has_value(mat, neibs.l, neibs.c, cor_base)){
                mat[neibs.l][neibs.c] = cor_final;
                row.push(neibs);
                show(mat_int, mat, row);
            }
        }
    }
}


int main(){
    int nl = 20, nc = 20;
    xmat_init(nl, nc);
    vector<string> mat(nl, string(nc, 'g'));
    vector<vector<int>> mat_int(nl, vector<int>(nc, -1));
    for(int l = 0; l < (int) mat.size(); l++){
        for(int c = 0; c < (int) mat[0].size(); c++){
            if(xm_rand(0, 100) < 30)
                mat[l][c] = 'r'; 
        }
    }
    xmat_draw(mat);
    x_save("pathfind");
    int l = 0, c = 0;
    puts("Digite o ponto de inicio l e c");
    scanf("%d %d", &l, &c);
    getchar();
    floodfill(mat_int, mat, l, c, mat[l][c], 'b');
    xmat_draw(mat);
    x_save("pathfind");
    x_close();
}