#include "xpaint.h"

void tree (int x, int y, float ang, int size, int esp) {
    if (size < 10)
        return;

    int xf = x + size * xm_cos (ang);
    int yf = y - size * xm_sin (ang);
    
    //xs_color ((XColor) {xm_rand (0, 255), xm_rand (0, 255), xm_rand (0, 255)});
    xs_color((XColor){92,64, 51});
    if(size < 65)
        xs_color (GREEN);
    xd_thick_line (x, y, xf, yf, esp);
    x_step ("tree");
    
    int aleatorio = xm_rand(2,3);
    int array_angulos[aleatorio];
    if(aleatorio == 3){
        array_angulos[0] = 26;
        array_angulos[1] = 0;
        array_angulos[2] = -26;
    }else{
        array_angulos[0] = 28;
        array_angulos[1] = -28;
    }
    
    for(int i = 0; i < aleatorio; i++){
        tree (xf, yf, ang + array_angulos[i], size - xm_rand (5, 15), esp - 0.01);
    }
    
    if(size < 60){
        xs_color (RED);
        xd_filled_circle(x, y, 3);
    }
}

int main () {
    int largura = 1000, altura = 1000;
    x_open (largura, altura); 
    x_clear (BLACK);
    float ang = 90;
    int x = largura / 2;
    int y = altura - 10;
    float size = 90;
    int esp = 6;
    tree (x, y, ang, size, esp);
    x_save ("tree");
    x_close ();
    return 0;
}