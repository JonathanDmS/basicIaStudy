#include <stdio.h>
#include <GL/glut.h>

int binario[8] = { 0,0,0,0,0,0,0,0 };
int arreglo[1000][1000];
int numeroFilas;
int numeroColumnas;

void decimal_a_binario(int numero) {
    // Creamos un arreglo para almacenar los bits del número binario
    int i = 0;
    // Convertimos el número decimal a binario
    while (numero > 0) {
        binario[i] = numero % 2;
        numero = numero / 2;
        i++;
    }
}

int calcularValorA(int i, int j) {
    int aux = 0;
    aux = (4 * arreglo[i - 1][numeroColumnas]) + (2 * arreglo[i - 1][j]) + (arreglo[i - 1][j + 1]);
    return aux;
}

int calcularValorC(int i, int j) {
    int aux = 0;
    aux = (4 * arreglo[i - 1][j - 1]) + (2 * arreglo[i - 1][j]) + (arreglo[i - 1][0]);
    return aux;
}

int calcularValorB(int i, int j) {
    int aux = 0;
    aux = (4 * arreglo[i - 1][j - 1]) + (2 * arreglo[i - 1][j]) + (arreglo[i - 1][j + 1]);
    return aux;
}

void array(int numeroFilas) {
    int centro;
    if (numeroColumnas%2==0)
        centro = numeroColumnas / 2;
    else
        centro = (numeroColumnas/2)-1;

    //condiciones iniciales
    for (int j = 0; j < numeroColumnas; j++) {
        if (j == centro)
            arreglo[0][j] = 1;
        else
            arreglo[0][j] = 0;
    }

    //llenado
    for (int i = 1; i < numeroFilas; i++) {
        for (int j = 0; j < numeroColumnas; j++) {
            if (j == 0)
                arreglo[i][j] = binario[calcularValorA(i, j)];
            else if (j == numeroColumnas-1)
                arreglo[i][j] = binario[calcularValorC(i, j)];
            else
                arreglo[i][j] = binario[calcularValorB(i, j)];
        }
    }

}



void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, numeroColumnas, numeroFilas, 0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    for (int i = 0; i < numeroFilas; i++) {
        for (int j = 0; j < numeroColumnas; j++) {
            if (arreglo[i][j] == 0) {
                glColor3f(1.0, 1.0, 1.0); // Blanco
            }
            else {
                glColor3f(0.0, 0.0, 0.0); // Negro
            }
            glBegin(GL_QUADS);
            glVertex2f(j, i*2);
            glVertex2f(j + 1, i*2);
            glVertex2f(j + 1, (i + 1)*2);
            glVertex2f(j, (i + 1)*2);
            glEnd();
        }
    }

    glFlush();
}

int main(int argc, char** argv) {
    // Probamos con números del 1 al 255

    int decimal;

    printf("Introduce la regla que quieres que te mostremos: (1-254) ");
    scanf("%d", &decimal);

    printf("Introduce el numero de columnas que deseas que se muestren: ");
    scanf("%d", &numeroColumnas);

    printf("Introduce el numero de filas a mostrar: ");
    scanf("%d", &numeroFilas);
    decimal_a_binario(decimal);
    printf("\n");
    array(numeroFilas);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(numeroColumnas *15, numeroFilas *10);
    glutCreateWindow("Automata Celular");
    glClearColor(0.0, 0.0, 0.0, 1.0); // Fondo negro
    glutDisplayFunc(display);

    glutMainLoop();
    return 0;
}
