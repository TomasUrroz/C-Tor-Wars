#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "gotoxy.h"
#include <conio.h>
#include <string.h>
// linea 8
#define maxcol 141
#define maxfil 46

#define DIM 6
HANDLE wHnd;

int filas = 46;
int columnas = 141;

typedef struct
{

    int id;
    char nombre[25];
    int tipo;
    unsigned int equipo;
    int vida;
    int estado;

    unsigned int  posx;
    unsigned int  posy;
    unsigned int  sp;
    unsigned int  mp;
    int armadura;
    int dmg;
    int rango;

} stUnidad;





typedef struct
{
    int id;
    char nombre[50];
    char contrasena[50];
    stUnidad ejercito[10];
} stUsuario;


/// seleccion de menu
void seleccionDeMenu (int selec);

///Herramienta de Dibujo Animado
void dibujarFila(int x, int xfin, int y, char caract);
void dibujarLineaV(int x, int y, int yfin, char caract);

///Ventana Animada
void dibujarVentana(int supizqX,int supizqY,int infderX,int infderY);

///Dibujo Logo y Titulo
void dibujarLogo(int supizqX, int supizqY);
void reDibujaLogo(int supizqX, int supizqY); //para admin
void dibujarNombre(int supizqX, int supizqY);
void dibujaC(int supizqX, int supizqY);
void dibujaguionT(int supizqX, int supizqY);
void dibujaOR(int supizqX, int supizqY);
void dibujaW(int supizqX, int supizqY);
void dibujaAR(int supizqX, int supizqY);
void dibujaS(int supizqX, int supizqY);

///Ventanita del Menu
void dibujarVentanas(int supizqX,int supizqY,int infderX,int infderY);
void limpiarVentana(int supizqX, int supizqY, int infderX,int infderY);
void limpiarVentanaAnimada(int supizqX, int supizqY, int infderX,int infderY); //para admin

///Menuces Dibujos
void dibujoMenuPrincipal(int supx,int supy);
void dibujoMenuIngresoEditor(int supx,int supy);
void dibujoMenuCrearCuenta(int supx,int supy);
void dibujoMenuJugar(int supx,int supy, int cont);
void dibujoMenuAdmin(int supx,int supy);
void dibujoMenuEditorCuentas(int supx,int supy);
void dibujoMenuModificarCuenta(int supx, int supy);
void dibujoMenuEditorEjercito(int supx, int supy);
void dibujoMenuModificarEjercito(int supx,int supy);

///no Animado
void dibujarLogoNoAnimado(int supizqX, int supizqY);
void dibujarLineaNoAnimada(int x, int xfin, int y, char caract);
void dibujarLineaVNoAnimada(int x, int y, int yfin, char caract);
void dibujarVentanaNoAnimada(int supizqX,int supizqY,int infderX,int infderY);

///Case Principal
void cazePrincipal (int colo, int Tablero[filas][columnas]);

///Case Ingreso
void cazeIngresoEditor (int colo, char archivo[]);
void limpiarCampo(int supx,int supy, char string[]);
void limpiarCampoInt(int supx,int supy, int num);
void AuxiliarCuentasEscribirPass(int dim, char pass[dim]);
stUsuario buscarCuenta(char archivo[],char user[]);                 //ARCHI busqueda.
void cerrarArchivo (FILE * archi);                           //Auxiliar ARCHI.
///Case Ingreso Juego
void cazeIngresoJuego (int colo, char archivo[],int Tablero[filas][columnas]);
void cargarEquipoUno (stUnidad ejercito[], stUnidad equipoUno[]);
void cargarEquipoDos (stUnidad ejercito[], stUnidad equipoDos[]);

///Case Crear Usuario
void cazeCrearCuenta (int colo, char archivo[]);
int cuentaRegistroArchivo(char archivo[], long tamanioBloqueEnBytes); //ARCHI cuentoRegistros.
int cargarArchivo(char archivo[], char nombre[], char pass[]);        //ARCHI carga de usuarios.

///Case Admin
void cazeAdmin (int colo, char archivo[], int caze);
void verCuentas();
void muestroCuentas(int supx,int supy);
int mostrarUsuario (stUsuario usuario, int supx, int supy);
void mostrarContenidoArchivo (char archivo[], int supx, int supy);  //ARCHI muestra struc.
void formatearCuentas(char archivo[], int supx, int supy);          //ARCHI formatea.

///caze Editor Cuentas
void cazeEditorCuentas(int colo, char archivo[]);
void cazeModificarCuenta(int colo, char archivo[], stUsuario usuario);
void mostrarCuentaExpecifica(char archivo[], stUsuario usuario, int supx, int supy);                        //ARCHI muestra especifico.
void modificarRegistroExpecifico(char archivo[], stUsuario usuario, char nombre[], char pass[],int cambio);//ARCHI modifica especifico.

///Editor de Ejercitos
void cazeEditorEjercitos(int colo, char archivo[], stUsuario usuario);
int crearTipo (stUnidad limite[], stUnidad ejercito[], int dimension, int supx, int supy);
void transformarTipo (int tipo, char tipos[]);
int contarElementoscargados(stUnidad ejercito[]);
int buscarTipo(stUnidad ejercito[], int validos, int tipo);
int validarTipo(stUnidad ejercito[], int validos,int tipo);
void cargarLimites(stUnidad limite[]);
void cargarAtributos(stUnidad limite[], stUnidad ejercito[],int validos, int supx, int supy, int limitipo, int i);
void reCargaArchivo(char archivoAlum[],stUsuario usuario, int id);


void mostrarUnidad(stUnidad recluta,int supx,int supy);
void mostrarArregloUnidad(stUnidad ejercito[], int supx,int supy);

///caze Modificar Unidad
void cazeModificarUnidad(int colo, stUnidad ejercito[]);
int buscarUnidad(stUnidad ejercito[], int id);
void modificarUnTipo (stUnidad limite[], stUnidad ejercito[], int supx, int supy,stUnidad soldadin);

void inicializarArchi(); //medidas de contingencia.

///Controla el Menu
int controlMenu();

///Auxiliar Coordenadas
void coordenadas();

///----------------------------------------------SECCION JUEGO--------------------------------------------
void barraEstado(char estado[30], char estado2[30]);
void dibujaStats(stUnidad M, int posx, int posy);

void dibujaLinea(int iniciox, int inicioy, int finx, int finy, int col, int caracter,int delay);
void dibujaCuadro(int iniciox, int inicioy, int finalx, int finaly, int col, int caracter, int delay);
void dibujaDinamico(stUnidad Equipo1[],stUnidad Equipo2[], int Tablero[filas][columnas]);

void dibujaUnidad(int posx, int posy,int tipo, int col);
void reemplazaUnidad(int posx, int posy,int finx, int finy,int tipo, int col);
void animAtaque(int posx, int posy,int finx, int finy, int equipo);
void animMuerteUnidad(int posx, int posy,int tipo);


void mueveUnidad2(int tablero[columnas][filas], int posx, int posy, int destinox, int destinoy,int color);

void dibujaLineaFisica(int tablero [columnas][filas],int iniciox, int inicioy, int finx, int finy);
void dibujaCuadroFisico(int tablero [columnas][filas],int iniciox, int inicioy, int finx, int finy);
void inicializaCuadroFisico(int tablero [columnas][filas]);
void creaTablero(int tablero[filas][columnas]);

int idUnidad(stUnidad EjercitoActivo[],int validos, int idunidad);
void entidadUnidad(int posx, int posy, int tablero[columnas][filas], int valor);
int validaMovimiento(int tablero[columnas][filas],int posx,int posy, int destinox,int destinoy);

void avanzaUnidad(int tablero[filas][columnas],stUnidad Ejercito[], int UnidadActiva);

int buscaVida(stUnidad equipo[], int pos[]);
int retornaVivo(stUnidad equipo[]);
int condicionVivos(stUnidad equipo[]);
int VerificaVivo(int id, stUnidad Equipo[]);

int checkRango(stUnidad Atacante, stUnidad Defensor);
int algunoRango(stUnidad EquipoATK[],stUnidad EquipoDEF[],int idActivo);

void ataca(stUnidad Atacante[], stUnidad Defensor[], int idatk, int iddef);

int SeleccionSwitch(int equipoActivo);
int SeleccionarEnemigo(stUnidad EquipoATK[],stUnidad EquipoDEF[], int idactivo );
void turnoUnidad(int tablero[filas][columnas], stUnidad EquipoATK[],stUnidad EquipoDEF[], int idActivo);
void juego(int tablero[filas][columnas],stUnidad equipo1[], stUnidad equipo2[]);
stUnidad creaEjercitosManual(stUnidad Equipo1[], stUnidad Equipo2[]);

///-----------------------------------------------------------------------------------------



int main()
{
    int selec;
    system ("mode con cols=141 lines=46");  ///dimensiones de la pantalla


    inicializarArchi();
    printf("Seleccione menu 1 prueba/ cualquer tecla final:");
    scanf("%i",&selec);
    hidecursor(0);


    seleccionDeMenu(selec);

    return 0;
}
void seleccionDeMenu (int selec)
{
    char colo=4;
    int Tablero[columnas][filas];

    if(selec==1)
    {
        system("cls");
        color(colo=7);
        dibujarVentanaNoAnimada(0,0,141,46);
        dibujarLogoNoAnimado(10,2);
        dibujarNombre(4,30);
        dibujarVentanaNoAnimada(90,31,117,43);
        cazePrincipal (colo, Tablero);
    }
    else
    {
        hidecursor(1);
        printf("\nPresione un numero del 1 al 9 para elegir un color:");
        fflush(stdin);    ///elige color 1azul 2verde 3celeste 4rojo 5violeta 6amarillo 7blanco 8gris 9turqueza
        colo=(getch()-48);
        color(colo);
        hidecursor(0);
        system("cls");
        dibujarVentana(0,0,141,46);
        dibujarLogo(10,2);
        dibujarNombre(4, 30);
        dibujarVentanas(90,31,117,43);
        cazePrincipal (colo, Tablero);
    }


}
///===============Funciones Auxiliares herramienta de dibujo animado===============

void dibujarLinea(int x, int xfin, int y, char caract)
{
    if(x<xfin)
    {
        while(x!=xfin)         ///pinta de izquierda para derecha
        {
            gotoxy(x,y);
            printf("%c",caract);
            x++;
            Sleep(1);
        }
    }
    else
    {
        while(x!=xfin)      ///pinta de derecha a izquierda
        {
            gotoxy(x,y);
            printf("%c",caract);
            x--;
            Sleep(1);
        }
    }
}

void dibujarLineaV(int x, int y, int yfin, char caract)
{
    if(y<yfin)
    {
        while(y!=yfin)  ///pinta de arriba a abajo
        {
            gotoxy(x,y);
            printf("%c",caract);
            y++;
            Sleep(1);
        }
    }
    else
    {
        while(y!=yfin)  ///pinta de abajo a arriba
        {
            gotoxy(x,y);
            printf("%c",caract);
            y--;
            Sleep(1);
        }
    }
}

///===============Funciones Auxiliares herramienta de dibujo NO animado===============

void dibujarLineaNoAnimada(int x, int xfin, int y, char caract)
{
    while(x!=xfin)      //   de izquierda a derecha
    {
        gotoxy(x,y);
        printf("%c",caract);
        x++;
    }
}

void dibujarLineaVNoAnimada(int x, int y, int yfin, char caract)
{

    while(y!=yfin)         //  de arriba a abajo
    {
        gotoxy(x,y);
        printf("%c",caract);
        y++;
    }
}

///===============Ventana Animada===============

void dibujarVentana(int supizqX,int supizqY,int infderX,int infderY)
{
    gotoxy(supizqX,supizqY);
    printf("%c",201);
    dibujarLinea(supizqX+1,infderX-1,supizqY,205);

    gotoxy(infderX-1,supizqY);
    printf("%c",187);
    dibujarLineaV(infderX-1, supizqY+1, infderY-1, 186);

    gotoxy(infderX-1,infderY-1);
    printf("%c",188);

    dibujarLinea(infderX-2,supizqX,infderY-1,205);

    gotoxy(supizqX,infderY-1);
    printf("%c",200);

    dibujarLineaV(supizqX, infderY-2,supizqY, 186);
}

///===============Ventana NO Animada===============

void dibujarVentanaNoAnimada(int supizqX,int supizqY,int infderX,int infderY)
{
    gotoxy(supizqX,supizqY);
    printf("%c",201);
    dibujarLineaNoAnimada(supizqX+1,infderX-1,supizqY,205);

    gotoxy(infderX-1,supizqY);
    printf("%c",187);
    dibujarLineaVNoAnimada(infderX-1, supizqY+1, infderY-1, 186);

    gotoxy(infderX-1,infderY-1);
    printf("%c",188);

    dibujarLineaNoAnimada(supizqX,infderX-1,infderY-1,205);

    gotoxy(supizqX,infderY-1);
    printf("%c",200);

    dibujarLineaVNoAnimada(supizqX, supizqY+1, infderY-1, 186);
}

///===============Dibujo Logo y Titulo===============

void dibujarLogo(int supizqX, int supizqY)
{
    gotoxy(supizqX,supizqY);
    printf("                   CCCCCCCC       CCCCCCCCC");
    Sleep(5);
    Beep(330,260);                                            /// esta canción es totalmente original, no la vas a encontrar en ningun lado más.
    gotoxy(supizqX,supizqY+1);
    printf("                   CCCCCCCCCC    CCCCCCCCCC");
    Sleep(5);
    Beep(294,300);
    gotoxy(supizqX,supizqY+2);
    printf("             CC    CCCCCCCCCCCCCCCCCCCCCCC");
    Sleep(5);
    Beep(278,300);
    gotoxy(supizqX,supizqY+3);
    printf("           CCCCCC  CCCCCCCCCCCCCCCCCCCCCCC    CCC");
    Sleep(5);
    Beep(247,800);
    gotoxy(supizqX,supizqY+4);
    printf("         CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC");
    Sleep(5);
    Beep(370,300);
    gotoxy(supizqX,supizqY+5);
    printf("       CCCCCCCCCCCCCCCC             CCCCCCCCCCCCCCCCC");
    Sleep(5);
    Beep(392,300);
    gotoxy(supizqX,supizqY+6);
    printf("        CCCCCCCCCCCC                    CCCCCCCCCCCCCC");
    Sleep(5);
    Beep(392,800);
    gotoxy(supizqX,supizqY+7);
    printf("          CCCCCCC                          CCCCCCCCC");
    Sleep(5);
    Beep(440,300);
    gotoxy(supizqX,supizqY+8);
    printf("    CCCCCCCCCCC         CCCCCCCCCCCCC       CCCCCCC    C");
    Sleep(5);
    Beep(494,300);
    gotoxy(supizqX,supizqY+9);
    printf("   CCCCCCCCCCC       CCCCCCCCCCCCCCCCCCC      CCCCCCCCCCC");
    Sleep(5);
    Beep(555,300);
    gotoxy(supizqX,supizqY+10);
    printf("  CCCCCCCCCCC      CCCCCCCCCCCCCCCCCCCCCCC     CCCCCCCCCC");
    Sleep(5);
    Beep(370,300);
    gotoxy(supizqX,supizqY+11);
    printf("  CCCCCCCCCC       CCCCCCCCCCCCCCCCCCCCCCC      CCCCCCCCCC");
    Sleep(5);
    Beep(330,300);
    gotoxy(supizqX,supizqY+12);
    printf("  CCCCCCCCCC      CCCCCCCCCCCCCCCCCCCCCCCCC     CCCCCCCCCC");
    Sleep(5);
    Beep(330,300);
    gotoxy(supizqX,supizqY+13);
    printf("      CCCCC       CCCCCCCCCCCCCCCCCCCCCCCCCC    CCCCCCCCCC");
    Sleep(5);
    Beep(247,300);
    gotoxy(supizqX,supizqY+14);
    printf("     CCCCCC       CCCCCCCCCCCCCCCCCCCCCCCCCC    CCCCCC");
    Sleep(5);
    Beep(330,800);
    gotoxy(supizqX,supizqY+15);
    printf("  CCCCCCCCCC      CCCCCCCCCCCCCCCCCCCCCCCCCC    CCCCCCCCCC");
    Sleep(5);
    Beep(370,300);
    gotoxy(supizqX,supizqY+16);
    printf("  CCCCCCCCCC     CCCCCC CCCCCCCCCCCCC CCCCCC    CCCCCCCCCC");
    Sleep(5);
    Beep(392,300);
    gotoxy(supizqX,supizqY+17);
    printf("  CCCCCCCCCCC   CCCCCC    CCCCCCCCCC   CCCCCC  CCCCCCCCCC");
    Sleep(5);
    Beep(370,300);
    gotoxy(supizqX,supizqY+18);
    printf("   CCCCCCCCCC   CCCCC      CCCCCCC      CCCCC  CCCCCCCCCC");
    Sleep(5);
    Beep(440,300);
    gotoxy(supizqX,supizqY+19);
    printf("    CCCCCCCCC   CCCCC      CCCCCCC      CCCCC  CCCCCCCCC");
    Sleep(5);
    Beep(494,300);
    gotoxy(supizqX,supizqY+20);
    printf("          CCC   CCCCCCCCCCCCCCCCCCCCCCCCCCCCC  CCC    C");
    Sleep(5);
    Beep(440,300);
    gotoxy(supizqX,supizqY+21);
    printf("       CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC");
    Sleep(5);
    Beep(440,800);
    gotoxy(supizqX,supizqY+22);
    printf("       CCCCCCCCCCCC  CCCCCCCCCCCCCCCCCCC CCCCCCCCCCC");
    Sleep(5);
    Beep(370,300);
    gotoxy(supizqX,supizqY+23);
    printf("         CCCCCCCCCC  CCC  CCCCCCCCCC CCC CCCCCCCCCC");
    Sleep(5);
    Beep(494,300);
    gotoxy(supizqX,supizqY+24);
    printf("           CCCCCCCC  CCC CCC CCC CCC CCC CCCCCCCC");
    Sleep(5);
    Beep(370,300);
    gotoxy(supizqX,supizqY+25);
    printf("             C       CC  CCC CCC CCC CCC    CCC");
    Sleep(5);
    Beep(294,300);
    gotoxy(supizqX,supizqY+26);
    printf("                      C  CC  CCC CCC CC");
    Sleep(5);
    Beep(294,300);
    gotoxy(supizqX,supizqY+27);
    printf("                          C  CCC CC");
    Sleep(5);
    Beep(370,300);

}

void dibujarLogoNoAnimado(int supizqX, int supizqY)
{
    gotoxy(supizqX,supizqY);
    printf("                   CCCCCCCC       CCCCCCCCC");
    gotoxy(supizqX,supizqY+1);
    printf("                   CCCCCCCCCC    CCCCCCCCCC");
    gotoxy(supizqX,supizqY+2);
    printf("             CC    CCCCCCCCCCCCCCCCCCCCCCC");
    gotoxy(supizqX,supizqY+3);
    printf("           CCCCCC  CCCCCCCCCCCCCCCCCCCCCCC    CCC");
    gotoxy(supizqX,supizqY+4);
    printf("         CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC");
    gotoxy(supizqX,supizqY+5);
    printf("       CCCCCCCCCCCCCCCC             CCCCCCCCCCCCCCCCC");
    gotoxy(supizqX,supizqY+6);
    printf("        CCCCCCCCCCCC                    CCCCCCCCCCCCCC");
    gotoxy(supizqX,supizqY+7);
    printf("          CCCCCCC                          CCCCCCCCC");
    gotoxy(supizqX,supizqY+8);
    printf("    CCCCCCCCCCC         CCCCCCCCCCCCC       CCCCCCC    C");
    gotoxy(supizqX,supizqY+9);
    printf("   CCCCCCCCCCC       CCCCCCCCCCCCCCCCCCC      CCCCCCCCCCC");
    gotoxy(supizqX,supizqY+10);
    printf("  CCCCCCCCCCC      CCCCCCCCCCCCCCCCCCCCCCC     CCCCCCCCCC");
    gotoxy(supizqX,supizqY+11);
    printf("  CCCCCCCCCC       CCCCCCCCCCCCCCCCCCCCCCC      CCCCCCCCCC");
    gotoxy(supizqX,supizqY+12);
    printf("  CCCCCCCCCC      CCCCCCCCCCCCCCCCCCCCCCCCC     CCCCCCCCCC");
    gotoxy(supizqX,supizqY+13);
    printf("      CCCCC       CCCCCCCCCCCCCCCCCCCCCCCCCC    CCCCCCCCCC");
    gotoxy(supizqX,supizqY+14);
    printf("     CCCCCC       CCCCCCCCCCCCCCCCCCCCCCCCCC    CCCCCC");
    gotoxy(supizqX,supizqY+15);
    printf("  CCCCCCCCCC      CCCCCCCCCCCCCCCCCCCCCCCCCC    CCCCCCCCCC");
    gotoxy(supizqX,supizqY+16);
    printf("  CCCCCCCCCC     CCCCCC CCCCCCCCCCCCC CCCCCC    CCCCCCCCCC");
    gotoxy(supizqX,supizqY+17);
    printf("  CCCCCCCCCCC   CCCCCC    CCCCCCCCCC   CCCCCC  CCCCCCCCCC");
    gotoxy(supizqX,supizqY+18);
    printf("   CCCCCCCCCC   CCCCC      CCCCCCC      CCCCC  CCCCCCCCCC");
    gotoxy(supizqX,supizqY+19);
    printf("    CCCCCCCCC   CCCCC      CCCCCCC      CCCCC  CCCCCCCCC");
    gotoxy(supizqX,supizqY+20);
    printf("          CCC   CCCCCCCCCCCCCCCCCCCCCCCCCCCCC  CCC    C");
    gotoxy(supizqX,supizqY+21);
    printf("       CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC");
    gotoxy(supizqX,supizqY+22);
    printf("       CCCCCCCCCCCC  CCCCCCCCCCCCCCCCCCC CCCCCCCCCCC");
    gotoxy(supizqX,supizqY+23);
    printf("         CCCCCCCCCC  CCC  CCCCCCCCCC CCC CCCCCCCCCC");
    gotoxy(supizqX,supizqY+24);
    printf("           CCCCCCCC  CCC CCC CCC CCC CCC CCCCCCCC");
    gotoxy(supizqX,supizqY+25);
    printf("             C       CC  CCC CCC CCC CCC    CCC");
    gotoxy(supizqX,supizqY+26);
    printf("                      C  CC  CCC CCC CC");
    gotoxy(supizqX,supizqY+27);
    printf("                          C  CCC CC");

}
void reDibujaLogo(int supizqX, int supizqY)
{
    gotoxy(supizqX,supizqY);
    printf("CCCCCCCCCCCCCCCCCCCCCCCCC");
    Sleep(20);
    gotoxy(supizqX,supizqY+1);
    printf("CCCCCCCCCCCCCCCCCCCCCCCCC");
    Sleep(20);
    gotoxy(supizqX,supizqY+2);
    printf("CCCCCCCCCCCCCCCCCCCCCCCCC");
    Sleep(20);
    gotoxy(supizqX,supizqY+3);
    printf("CCCCCCCCCCCCCCCCCCCCCCCCC");
    Sleep(20);
    gotoxy(supizqX,supizqY+4);
    printf("CCCCC CCCCCCCCCCCCC CCCCC");
    Sleep(20);
    gotoxy(supizqX,supizqY+5);
    printf("CCCC    CCCCCCCCCC   CCCC");
    Sleep(20);
    gotoxy(supizqX,supizqY+6);
    printf("CCC      CCCCCCC      CCC");
    Sleep(20);
    gotoxy(supizqX,supizqY+7);
    printf("CCC      CCCCCCC      CCC");
    Sleep(20);
    gotoxy(supizqX,supizqY+8);
    printf("CCCCCCCCCCCCCCCCCCCCCCCCC");
    Sleep(20);
    gotoxy(supizqX,supizqY+9);
    printf("CCCCCCCCCCCCCCCCCCCCCCCCC");
    Sleep(20);
    gotoxy(supizqX,supizqY+10);
    printf("C  CCC  CCCCCCCCCC CCC CC");
    Sleep(5);
    gotoxy(supizqX,supizqY+11);
    printf("C  CCC CCC CCC CCC CCC CC");
}

void dibujarNombre(int supizqX, int supizqY)
{
    dibujaC(supizqX, supizqY);
    Sleep(20);
    dibujaguionT(supizqX+9, supizqY);
    Sleep(20);
    dibujaOR(supizqX+27, supizqY);
    Sleep(20);
    dibujaW(supizqX+42, supizqY);
    Sleep(20);
    dibujaAR(supizqX+51, supizqY);
    Sleep(20);
    dibujaS(supizqX+63, supizqY);
    Beep(247,800);
}
void dibujaC(int supizqX, int supizqY)
{
    gotoxy(supizqX,supizqY);
    printf("%c%c%c%c%c%c%c%c%c",201,205,205,205,205,205,205,205,187);
    gotoxy(supizqX,supizqY+1);
    printf("%c %c%c%c%c%c%c%c",186,201,205,205,205,205,205,188);
    gotoxy(supizqX,supizqY+2);
    printf("%c %c     ",186,186);
    gotoxy(supizqX,supizqY+3);
    printf("%c %c     ",186,186);
    gotoxy(supizqX,supizqY+4);
    printf("%c %c%c%c%c%c%c%c",186,200,205,205,205,205,205,187);
    gotoxy(supizqX,supizqY+5);
    printf("%c%c%c%c%c%c%c%c%c",200,205,205,205,205,205,205,205,188);
}
void dibujaguionT(int supizqX, int supizqY)
{
    gotoxy(supizqX,supizqY);
    printf("            %c%c%c   ",201,205,187);
    gotoxy(supizqX,supizqY+1);
    printf("         %c%c%c%c %c%c%c%c",201,205,205,188,200,205,205,187);
    gotoxy(supizqX,supizqY+2);
    printf("%c%c%c%c%c%c%c%c %c%c%c%c %c%c%c%c",201,205,205,205,205,205,205,187,200,205,205,187,201,205,205,188);
    gotoxy(supizqX,supizqY+3);
    printf("%c%c%c%c%c%c%c%c    %c %c   ",200,205,205,205,205,205,205,188,186,186);
    gotoxy(supizqX,supizqY+4);
    printf("            %c %c   ",186,186);
    gotoxy(supizqX,supizqY+5);
    printf("            %c%c%c   ",200,205,188);
}

void dibujaOR(int supizqX, int supizqY)
{
    gotoxy(supizqX,supizqY);
    printf("             ");
    gotoxy(supizqX,supizqY+1);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c",201,205,205,205,205,205,205,187,201,205,205,205,187);
    gotoxy(supizqX,supizqY+2);
    printf("%c %c%c%c%c %c%c %c%c%c",186,201,205,205,187,186,186,201,205,188);
    gotoxy(supizqX,supizqY+3);
    printf("%c %c  %c %c%c %c  ",186,186,186,186,186,186);
    gotoxy(supizqX,supizqY+4);
    printf("%c %c%c%c%c %c%c %c  ",186,200,205,205,188,186,186,186);
    gotoxy(supizqX,supizqY+5);
    printf("%c%c%c%c%c%c%c%c%c%c%c  ",200,205,205,205,205,205,205,188,200,205,188);

}

void dibujaW(int supizqX, int supizqY)
{
    gotoxy(supizqX,supizqY);
    printf("%c%c%c   %c%c%c",201,205,187,201,205,187);
    gotoxy(supizqX,supizqY+1);
    printf("%c %c   %c %c",186,186,186,186);
    gotoxy(supizqX,supizqY+2);
    printf("%c %c%c%c%c%c %c",186,186,201,205,187,186,186);
    gotoxy(supizqX,supizqY+3);
    printf("%c %c%c %c%c %c",186,186,186,186,186,186);
    gotoxy(supizqX,supizqY+4);
    printf("%c %c%c %c%c %c",186,200,188,200,188,186);
    gotoxy(supizqX,supizqY+5);
    printf("%c%c%c%c%c%c%c%c%c",200,205,205,205,205,205,205,205,188);
}

void dibujaAR(int supizqX, int supizqY)
{
    gotoxy(supizqX,supizqY);
    printf("            ");
    gotoxy(supizqX,supizqY+1);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c",201,205,205,205,205,205,187,201,205,205,205,187);
    gotoxy(supizqX,supizqY+2);
    printf("%c %c%c%c %c%c %c%c%c",186,201,205,187,186,186,201,205,188);
    gotoxy(supizqX,supizqY+3);
    printf("%c %c%c%c %c%c %c  ",186,200,205,188,186,186,186);
    gotoxy(supizqX,supizqY+4);
    printf("%c %c%c%c %c%c %c  ",186,201,205,187,186,186,186);
    gotoxy(supizqX,supizqY+5);
    printf("%c%c%c %c%c%c%c%c%c  ",200,205,188,200,205,188,200,205,188);

}

void dibujaS(int supizqX, int supizqY)
{
    gotoxy(supizqX,supizqY);
    printf("%c%c%c%c%c%c%c%c",201,205,205,205,205,205,205,187);
    gotoxy(supizqX,supizqY+1);
    printf("%c %c%c%c%c%c%c",186,201,205,205,205,205,188);
    gotoxy(supizqX,supizqY+2);
    printf("%c %c%c%c%c%c%c",186,200,205,205,205,205,187);
    gotoxy(supizqX,supizqY+3);
    printf("%c%c%c%c%c%c %c",200,205,205,205,205,187,186);
    gotoxy(supizqX,supizqY+4);
    printf("%c%c%c%c%c%c %c",201,205,205,205,205,188,186);
    gotoxy(supizqX,supizqY+5);
    printf("%c%c%c%c%c%c%c%c",200,205,205,205,205,205,205,188);
}

///===============Auxiliar Coordenadas===============

void coordenadas()
{
    char c=0;
    int x=0;
    int y=0;
    int a;
    hidecursor(1);

    do
    {
        c=getch();
        switch(c)
        {
        case 72:
            if(y>0)    //arriba
            {
                y--;
                gotoxy(x,y);
                //printf("%c",219);
            }
            else
            {
                Beep(100,150);
            }
            break;
        case 75:
            if(x>0)
            {
                x--;    //izquierda
                gotoxy(x,y);
                //printf("%c",219);
            }
            else
            {
                Beep(100,150);
            }
            break;
        case 77:
            if(x<140)
            {
                x++;    //derecha
                gotoxy(x,y);
                //printf("%c",219);
            }
            else
            {
                Beep(100,150);
            }
            break;
        case 80:
            if(y<45)
            {
                y++;    //abajo
                gotoxy(x,y);
                //printf("%c",219);
            }
            else
            {
                Beep(100,150);
            }
            break;
        case 32:
        {
            gotoxy(x,y);    //dame cordenadas
            printf("%c%i-%i",178,x,y);
        }
        break;
        case 8:
        {
            gotoxy(x,y);    //borrar
            printf("%c",32);
        }
        break;
        case 48:
        {
            gotoxy(x,y);    //colores
            color(a);
            a++;
        }
        break;
        }

    }
    while(c!=27);
    hidecursor(0);
}

///===============Ventanas===============

void dibujarVentanas(int supizqX,int supizqY,int infderX,int infderY)
{
    gotoxy(supizqX,supizqY);
    printf("%c",201);
    dibujarLinea(supizqX+1,infderX-1,supizqY,205);

    gotoxy(infderX-1,supizqY);
    printf("%c",187);
    dibujarLineaV(infderX-1, supizqY+1, infderY-1, 186);

    gotoxy(infderX-1,infderY-1);
    printf("%c",188);

    dibujarLinea(infderX-2,supizqX,infderY-1,205);

    gotoxy(supizqX,infderY-1);
    printf("%c",200);

    dibujarLineaV(supizqX, infderY-2,supizqY, 186);
}


// Limpiar ventana
void limpiarVentana(int supizqX, int supizqY, int infderX,int infderY)   //91x  32y 116x 42y hice andar un super menu gran dia !
{
    int x,y;

    for(y=supizqY; y<infderY; y++)
    {
        for(x=supizqX; x<infderX; x++)
        {
            gotoxy(x,y);
            printf(" "); //borro el cursor
        }
    }
}

void limpiarVentanaAnimada(int supizqX, int supizqY, int infderX,int infderY)
{
    int x,y;

    for(y=supizqY; y<infderY; y++)
    {
        for(x=supizqX; x<infderX; x++)
        {
            gotoxy(x,y);
            printf(" "); //borro el cursor
            Sleep(5);
        }
    }
}

///==============Dibujar Menus==============

void dibujoMenuPrincipal(int supx,int supy)
{
    char opcionUno[20] = "Ingresar al Editor"; //pongo los parametros
    char opcionDos[20] = "Crear Cuenta";
    char opcionTres[20] = "Ingresar al Juego";
    char opcionCuatro[20] = "Salir";
    gotoxy(supx,supy);
    printf("%s",opcionUno);
    gotoxy(supx,supy+2);
    printf("%s",opcionDos);
    gotoxy(supx,supy+4);
    printf("%s",opcionTres);
    gotoxy(supx,supy+6);
    printf("%s",opcionCuatro);
}

void dibujoMenuIngresoEditor(int supx,int supy)
{
    char opcionUno[20] = "Usuario"; //pongo los parametros
    char opcionDos[20] = "Contrase";
    char opcionTres[20] = "Ingresar";
    char opcionCuatro[20] = "Volver";
    gotoxy(supx,supy);
    printf("%s",opcionUno);
    gotoxy(supx,supy+2);
    printf("%s%ca",opcionDos,164);
    gotoxy(supx,supy+4);
    printf("%s",opcionTres);
    gotoxy(supx,supy+6);
    printf("%s",opcionCuatro);
}

void dibujoMenuCrearCuenta(int supx,int supy)
{
    char opcionUno[20] = "Usuario"; //pongo los parametros
    char opcionDos[20] = "Contrase";
    char opcionTres[20] = "Crear";
    char opcionCuatro[20] = "Volver";
    gotoxy(supx,supy);
    printf("%s",opcionUno);
    gotoxy(supx,supy+2);
    printf("%s%ca",opcionDos,164);
    gotoxy(supx,supy+4);
    printf("%s",opcionTres);
    gotoxy(supx,supy+6);
    printf("%s",opcionCuatro);
}

void dibujoMenuJugar(int supx,int supy, int cont)
{
    char opcionUno[20] = "Usuario"; //pongo los parametros
    char opcionDos[20] = "Contrase";
    char opcionTres[20] = "Ingresar";
    char opcionCuatro[20] = "Volver";
    gotoxy(supx,supy);
    printf("%s %i",opcionUno, cont);
    gotoxy(supx,supy+2);
    printf("%s%ca",opcionDos,164);
    gotoxy(supx,supy+4);
    printf("%s",opcionTres);
    gotoxy(supx,supy+6);
    printf("%s",opcionCuatro);
}

void dibujoMenuAdmin(int supx,int supy)
{
    char opcionUno[20] = "Ver Cuentas"; //pongo los parametros
    char opcionDos[20] = "Editar Cuenta";
    char opcionTres[20] = "Coordenadas";
    char opcionCuatro[20] = "Formatear DB";
    char opcionCinco[20] = "Salir";
    gotoxy(supx-3,supy-1);
    printf(" Buen Dia Amo y Se%cor ",164);
    gotoxy(supx,supy);
    printf("%s",opcionUno);
    gotoxy(supx,supy+2);
    printf("%s",opcionDos);
    gotoxy(supx,supy+4);
    printf("%s",opcionTres);
    gotoxy(supx,supy+6);
    printf("%s",opcionCuatro);
    gotoxy(supx,supy+8);
    printf("%s",opcionCinco);
}

void dibujoMenuEditorCuentas(int supx,int supy)
{
    char opcionUno[20] = "Usuario"; //pongo los parametros
    char opcionDos[20] = "Buscar";
    char opcionTres[20] = "Volver";
    gotoxy(supx,supy);
    printf("%s",opcionUno);
    gotoxy(supx,supy+2);
    printf("%s",opcionDos);
    gotoxy(supx,supy+4);
    printf("%s",opcionTres);

}

void dibujoMenuModificarCuenta(int supx, int supy)
{
    char opcionUno[20] = "Cambiar Usuario"; //pongo los parametros
    char opcionDos[20] = "Cambiar Contrase";
    char opcionTres[20] = "Modificar";
    char opcionCuatro[20] = "Volver";
    gotoxy(supx,supy);
    printf("%s",opcionUno);
    gotoxy(supx,supy+2);
    printf("%s%ca",opcionDos,164);
    gotoxy(supx,supy+4);
    printf("%s",opcionTres);
    gotoxy(supx,supy+6);
    printf("%s",opcionCuatro);
}

void dibujoMenuEditorEjercito(int supx, int supy)
{
    char opcionUno[20] = "Crear Ejercito"; //pongo los parametros
    char opcionDos[20] = "Ver Ejercito";
    char opcionTres[20] = "Modificar Ejercito";
    char opcionCuatro[20] = "volver";
    gotoxy(supx,supy);
    printf("%s",opcionUno);
    gotoxy(supx,supy+2);
    printf("%s",opcionDos);
    gotoxy(supx,supy+4);
    printf("%s",opcionTres);
    gotoxy(supx,supy+6);
    printf("%s",opcionCuatro);
}

void dibujoMenuModificarEjercito(int supx,int supy)
{
    char opcionUno[20] = "ID de unidad"; //pongo los parametros
    char opcionDos[20] = "Buscar";
    char opcionTres[20] = "Volver";
    gotoxy(supx,supy);
    printf("%s",opcionUno);
    gotoxy(supx,supy+2);
    printf("%s",opcionDos);
    gotoxy(supx,supy+4);
    printf("%s",opcionTres);
}

///===============controla el menu===============

int controlMenu(int supx, int supy, int opciones, int colorcito)
{
    int x=supx, y=supy;
    char c=0;
    int respuesta=0; //este valor es el valor de y al apretar enter

    gotoxy(x,y);
    printf("%c%c",175,175);

    do
    {
        c=getch();
        switch(c)
        {
        case 72:
            if(y>supy)    //arriba
            {
                gotoxy(x,y);
                printf("  "); //borro el cursor
                y=y-2;
                gotoxy(x,y);
                printf("%c%c",175,175);
            }
            else
            {
                Beep(100,150);  //aviso de limite
            }
            break;
        case 80:
            if(y<supy+(opciones-1)*2)    //abajo
            {
                gotoxy(x,y);
                printf("  ");  //borro el cursor
                y=y+2;
                gotoxy(x,y);
                printf("%c%c",175,175);
            }
            else
            {
                Beep(100,150);
            }
            break;
        case 13:
        {
            gotoxy(x,y);    //enter
            color(colorcito+2);
            printf("%c%c",175,175); // lo muestro en otro color
            Beep(278,300);
            Sleep(200);
            color(colorcito);
            gotoxy(x,y);
            printf("  ");  //borro el cursor
            y=y-(supy-1);
            respuesta=y;
        }
        }

    }
    while(respuesta==0);

    return respuesta;

}

///===============Case Principal===============

void cazePrincipal (int colo,int Tablero[filas][columnas])
{
    char archivoUsuarios[30]= {"Usuarios.bin"};

    int supx=96,supy=33,resp;

    do
    {
        limpiarVentana(91, 32, 116,42);
        dibujoMenuPrincipal (supx,supy);
        resp=controlMenu(94,33,4, colo); // me muevo por el case
        switch(resp)
        {
        case 1:
            gotoxy(supx, supy+1);
            printf("Ingreso al editor");    ///Hecho
            Sleep(300);
            cazeIngresoEditor (colo,archivoUsuarios);
            break;
        case 3:
            gotoxy(supx, supy+3);
            printf("Ingreso crear cuenta"); ///Hecho
            Sleep(300);
            cazeCrearCuenta (colo, archivoUsuarios);
            break;
        case 5:
            gotoxy(supx, supy+5);
            printf("Ingreso al juego");    ///Hecho ///seguir al juego
            cazeIngresoJuego (colo, archivoUsuarios,Tablero);
            Sleep(300);
            break;
        case 7:
            gotoxy(supx, supy+7);
            printf("salir del programa");
            Sleep(300);
            break;
        }

    }
    while(resp!=7);

}

///===============Case Ingreso Editor===============

void cazeIngresoEditor (int colo, char archivo[])
{

    int supx=96,supy=33,resp; //var del menu
    char pass[50]="", cuenta[50]="";
    char secret[30]="admin"; //shh es secreto
    stUsuario usuario;
    int caze=1;

    limpiarVentana(91, 32, 116, 42);
    dibujoMenuIngresoEditor(supx, supy);
    do
    {
        gotoxy(supx, supy+5);
        printf("                    ");
        resp=controlMenu(94,33,4, colo);
        switch(resp)
        {
        case 1:  //ingreso cuenta
            limpiarCampo(supx,supy+1,cuenta);
            gotoxy(supx, supy+1);
            hidecursor(1);
            fflush(stdin);
            gets(cuenta);
            hidecursor(0);
            break;
        case 3:  //ingreso pass
            limpiarCampo(supx,supy+3,pass);
            gotoxy(supx, supy+3);
            hidecursor(1);
            AuxiliarCuentasEscribirPass(50, pass);  // la contracena seria como un tipo de almuerzo.
            hidecursor(0);
            break;
        case 5: //ingresar al editor basicamente valida si es 1 o mas entras si es -1 no entras.
            gotoxy(supx, supy+5);
            if(strcmp(cuenta, secret)==0 && strcmp(pass, secret)==0)
            {
                printf("Debugging code Lamda");
                limpiarCampo(supx,supy+1,cuenta);
                limpiarCampo(supx,supy+3,pass);
                cazeAdmin (colo, archivo, caze);
            }

            else
            {
                usuario=buscarCuenta(archivo, cuenta);
                if(usuario.id!=-1 && strcmp(usuario.contrasena, pass)==0)
                {
                    printf("ingresa al editor");
                    limpiarCampo(supx,supy+1,cuenta);
                    limpiarCampo(supx,supy+3,pass);
                    cazeEditorEjercitos(colo, archivo, usuario);
                }
                else
                {
                    printf("Usuario/pass Incor");
                    Sleep(2000);
                    limpiarCampo(supx,supy+1,cuenta);
                    limpiarCampo(supx,supy+3,pass);
                }
            }
            break;
        case 7:
            gotoxy(supx, supy+7);
            printf("saliendo");
            limpiarCampo(supx,supy+1,cuenta);
            limpiarCampo(supx,supy+3,pass);
            Sleep(500);
            break;
        }
    }
    while(resp!=7);

}

void limpiarCampo(int supx,int supy, char string[])
{
    int i, fin;
    fin=strlen(string);

    gotoxy(supx, supy);
    for(i=0; i<fin; i++)
    {
        printf(" ");
    }
}

void limpiarCampoInt(int supx,int supy, int num)
{
    int i, fin=1;
    while(num>=10)
    {
        num=num/10;
        fin++;
    }
    gotoxy(supx, supy);
    for(i=0; i<fin; i++)
    {
        printf("  ");
    }
}

void AuxiliarCuentasEscribirPass(int dim, char pass[])
{
    int i=0;
    char caracter;
    while((caracter=_getch())!=13)  //leo caracter por caracter y se lo asigno a ch hasta que le doy a enter.
    {
        if (caracter!=8)
        {
            pass[i]=caracter; //guardo las letras.
            i++;
            printf("%c",42); //printeo censura.
        }
        else
        {
            if(i>0)
            {
                i--;
                printf("\b \b");
            }
        }
        pass[i]='\0'; //para cerrar el string.
    }
}
stUsuario buscarCuenta(char archivo[],char cuenta[])
{
    FILE * archi=NULL;
    archi = fopen(archivo, "rb");
    stUsuario auxUsuario;
    int id =-1;
    if(archi != NULL)
    {
        while(fread(&auxUsuario, sizeof(stUsuario),1,archi)>0 && id==-1)
        {
            if(strcmp(auxUsuario.nombre, cuenta)==0)
            {

                id = auxUsuario.id;
                fseek(archi,sizeof(auxUsuario)*(id-1), SEEK_SET);
            }

        }
        if(id==-1)
            auxUsuario.id=-1;
        cerrarArchivo(archi);
    }
    return auxUsuario;
}

//CERRAR ARCHIVO
void cerrarArchivo (FILE * archi)
{
    int estado;

    estado= fclose(archi);

    if (estado!=0)
    {
        printf("Ocurrio un error Catastrofico"); //Si sucede, es realmente grave
    }
}

///===============Case Ingreso Juego===============

void cazeIngresoJuego (int colo, char archivo[],int Tablero[filas][columnas])
{

    int supx=96,supy=33,resp; //var del menu
    char pass[50]="", cuenta[50]="";
    char secret[30]= {"admin"}; //shh es secreto
    int cont=0; //cuenta los jugadores registrados para jugar
    stUsuario usuario;
    stUnidad equipoUno[6];
    stUnidad equipoDos[6];
    int caze=2;

    limpiarVentana(91, 32, 116, 42);
    do
    {

        dibujoMenuJugar(supx, supy, cont+1);
        gotoxy(supx, supy+5);
        printf("                    ");
        resp=controlMenu(94,33,4, colo);
        switch(resp)
        {
        case 1:  //ingreso cuenta
            limpiarCampo(supx,supy+1,cuenta);
            gotoxy(supx, supy+1);
            hidecursor(1);
            fflush(stdin);
            gets(cuenta);
            hidecursor(0);
            break;
        case 3:  //ingreso pass
            limpiarCampo(supx,supy+3,pass);
            gotoxy(supx, supy+3);
            hidecursor(1);
            AuxiliarCuentasEscribirPass(50, pass);
            hidecursor(0);
            break;
        case 5: //ingresar al juego basicamente valida si es 1 o mas entras si es -1 no entras.
            gotoxy(supx, supy+5);
            if(strcmp(cuenta, secret)==0 && strcmp(pass, secret)==0)
            {
                printf("Debugging code Lamda");
                limpiarCampo(supx,supy+1,cuenta);
                limpiarCampo(supx,supy+3,pass);
                cazeAdmin (colo, archivo, caze);
            }
            else
            {
                usuario=buscarCuenta(archivo, cuenta);
                if(usuario.id!=-1 && strcmp(usuario.contrasena, pass)==0)
                {
                    if (usuario.ejercito[5].id==5)
                    {
                        cont++;
                        printf("ingresa al juego %i",cont);
                        Sleep(1000);
                        if (cont==1)
                        {
                            cargarEquipoUno(usuario.ejercito, equipoUno);   /// guarda cada usuario.ejercito en cada arreglo para arrancarlo
                            limpiarCampo(supx,supy+1,cuenta);
                            limpiarCampo(supx,supy+3,pass);
                        }
                        else
                        {
                            cargarEquipoDos(usuario.ejercito, equipoDos);
                            system("cls");
                            creaTablero(Tablero);
                            juego(Tablero,equipoUno,equipoDos);
                            ///!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!ACA ARRANCA EL JUEGO!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                            cont=0;
                            system("cls");
                            dibujarVentanaNoAnimada(0,0,141,46);
                            dibujarLogoNoAnimado(10,2);
                            dibujarNombre(4,30);
                            dibujarVentanaNoAnimada(90,31,117,43);
                        }
                    }
                    else
                    {
                        printf("Sin ejercito cargado");
                        Sleep(2000);
                        limpiarCampo(supx,supy+1,cuenta);
                        limpiarCampo(supx,supy+3,pass);
                    }

                }
                else
                {
                    printf("Usuario/pass Incor");
                    Sleep(2000);
                    limpiarCampo(supx,supy+1,cuenta);
                    limpiarCampo(supx,supy+3,pass);
                }
            }
            break;
        case 7:
            gotoxy(supx, supy+7);
            printf("saliendo");
            limpiarCampo(supx,supy+1,cuenta);
            limpiarCampo(supx,supy+3,pass);
            Sleep(500);
            break;
        }
    }
    while(resp!=7);


}
///===============Carga equipos===============
void cargarEquipoUno(stUnidad ejercito[], stUnidad equipoUno[])
{
    int i=0;

    for(i=0; i<6; i++)  //si no los pasas de a uno no te los toma bien
    {
        equipoUno[i].id=ejercito[i].id;
        equipoUno[i].tipo=ejercito[i].tipo;
        strcpy(equipoUno[i].nombre,ejercito[i].nombre);
        equipoUno[i].vida=ejercito[i].vida;
        equipoUno[i].armadura=ejercito[i].armadura;
        equipoUno[i].dmg=ejercito[i].dmg;
        equipoUno[i].rango=ejercito[i].rango;
        equipoUno[i].mp=ejercito[i].mp;
        equipoUno[i].equipo=1;
        equipoUno[i].estado=1;
        equipoUno[i].sp=1;
    }
    equipoUno[0].posx=10;
    equipoUno[0].posy=15;
    equipoUno[1].posx=15;
    equipoUno[1].posy=20;
    equipoUno[2].posx=20;
    equipoUno[2].posy=15;
    equipoUno[3].posx=25;
    equipoUno[3].posy=20;
    equipoUno[4].posx=15;
    equipoUno[4].posy=25;
    equipoUno[5].posx=10;
    equipoUno[5].posy=10;
}

void cargarEquipoDos(stUnidad ejercito[], stUnidad equipoDos[])
{
    int i=0;

    for(i=0; i<6; i++)
    {
        equipoDos[i].id=ejercito[i].id;
        equipoDos[i].tipo=ejercito[i].tipo;
        strcpy(equipoDos[i].nombre,ejercito[i].nombre);
        equipoDos[i].vida=ejercito[i].vida;
        equipoDos[i].armadura=ejercito[i].armadura;
        equipoDos[i].dmg=ejercito[i].dmg;
        equipoDos[i].rango=ejercito[i].rango;
        equipoDos[i].mp=ejercito[i].mp;
        equipoDos[i].equipo=2;
        equipoDos[i].estado=1;
        equipoDos[i].sp=1;
    }
    equipoDos[0].posx=85;
    equipoDos[0].posy=15;
    equipoDos[1].posx=80;
    equipoDos[1].posy=20;
    equipoDos[2].posx=70;
    equipoDos[2].posy=20;
    equipoDos[3].posx=90;
    equipoDos[3].posy=15;
    equipoDos[4].posx=80;
    equipoDos[4].posy=25;
    equipoDos[5].posx=80;
    equipoDos[5].posy=10;
}

///===============Case Crear Cuenta===============

void cazeCrearCuenta (int colo, char archivo[])
{
    int supx=96,supy=33,resp,exito=0, cuentasregistradas=0;
    char pass[50]="", cuenta[50]="";
    char secret[30]= {"admin"};
    stUsuario usuario;

    limpiarVentana(91, 32, 116,42);
    dibujoMenuCrearCuenta( supx, supy);
    do
    {
        resp=controlMenu(94,33,4, colo);
        switch(resp)
        {
        case 1:  //ingreso cuenta
            limpiarCampo(supx,supy+1,cuenta);
            gotoxy(supx, supy+1);
            hidecursor(1);
            fflush(stdin);
            gets(cuenta);
            hidecursor(0);
            break;
        case 3:  //ingreso pass
            limpiarCampo(supx,supy+3,pass);
            gotoxy(supx, supy+3);
            hidecursor(1);
            AuxiliarCuentasEscribirPass(50, pass);  // la contracena seria como un tipo de almuerzo.
            hidecursor(0);
            break;
        case 5:
            gotoxy(supx, supy+5);
            if(strlen(cuenta)<2)
            {
                printf("usuario muy corto");
                limpiarCampo(supx,supy+1,cuenta);
                limpiarCampo(supx,supy+3,pass);
            }
            else
            {
                if (strlen(pass)<3)
                {
                    printf("pass muy corto"); // si lo sé los requisitos son sencillos
                    limpiarCampo(supx,supy+1,cuenta);
                    limpiarCampo(supx,supy+3,pass);
                    Sleep(500);

                }
                else
                {
                    usuario=buscarCuenta(archivo, cuenta);
                    if (usuario.id!=-1 || strcmp(cuenta, secret)==0) // compara tambien pass pero no afecta al funcionamiento
                    {
                        printf("Ya existe la cuenta");
                        limpiarCampo(supx,supy+1,cuenta);
                        limpiarCampo(supx,supy+3,pass);
                    }
                    else
                    {

                        cuentasregistradas=cuentaRegistroArchivo(archivo, sizeof(usuario));
                        if (cuentasregistradas<12)
                        {
                            exito=cargarArchivo(archivo, cuenta, pass);
                            if(exito==1)
                            {
                                printf("Cuenta Creada");
                                Sleep(1500);
                                gotoxy(supx, supy+5);
                                printf("              ");
                                limpiarCampo(supx,supy+1,cuenta);
                                limpiarCampo(supx,supy+3,pass);
                            }
                            else
                            {
                                printf("Hubo un problema");
                                limpiarCampo(supx,supy+1,cuenta);
                                limpiarCampo(supx,supy+3,pass);
                            }
                        }
                        else
                        {
                            printf("Max Cuentas-Admin");
                            limpiarCampo(supx,supy+1,cuenta);
                            limpiarCampo(supx,supy+3,pass);
                        }
                    }
                }
            }  //exceso de ifs si pero son necesarias las comprobaciones secuenciales y cada salida tiene un print descriptivo.
            break;
        case 7:
            Beep(278,300);
            gotoxy(supx, supy+7);
            printf("saliendo");
            limpiarCampo(supx,supy+1,cuenta);
            limpiarCampo(supx,supy+3,pass);
            Sleep(300);
            break;
        }
    }
    while(resp!=7);
}

// cuento registros para sacar el lugar de la id.
int cuentaRegistroArchivo(char archivo[], long tamanioBloqueEnBytes)
{
    int cantidad =0;

    FILE * archi=NULL;

    archi = fopen(archivo,"rb");
    if(archi!=NULL)
    {
        /// me posiciono al final del archivo
        fseek(archi,0,SEEK_END);

        /// divido la cantidad de bytes del archivo por la cant bytes de la struc
        /// me devuelve el numero de strucs que hay.
        cantidad = ftell(archi)/tamanioBloqueEnBytes;
        cerrarArchivo(archi);
    }

    return cantidad;
}

// cargo todo a struc
int cargarArchivo(char archivo[], char nombre[], char pass[])
{
    int id, exito=0;
    stUsuario cuentaNueva;

    id=cuentaRegistroArchivo(archivo, sizeof(stUsuario)); //cuento las cuentas
    id=id+1; //nueva id para la cuenta ¡incremental!
    strcpy(cuentaNueva.nombre, nombre);
    strcpy(cuentaNueva.contrasena, pass);
    cuentaNueva.id=id;


    FILE * archi=NULL;

    archi=fopen(archivo,"ab");   /// agregar algo al final.
    if (archi!=NULL)
    {
        fwrite (&cuentaNueva,sizeof(stUsuario),1, archi);
        cerrarArchivo(archi);
        exito=1;
    }
    return exito;
}

///===============Case ADMIN=============== o para los pibes, Debugging code Lamda

void cazeAdmin (int colo, char archivo[], int caze)  /// es importante para tener un control total del sistema
{
    int supx=33,supy=15,resp;

    dibujarVentanas(28,14,53,26);
    limpiarVentanaAnimada(29, 15, 52, 25);
    dibujoMenuAdmin( supx, supy);
    do
    {
        resp=controlMenu(30,15,5, colo); // me muevo por el case
        switch(resp)
        {
        case 1:
            gotoxy(supx, supy+1);
            printf("abriendo cuentas");
            verCuentas(archivo);
            break;
        case 3:
            gotoxy(supx, supy+3);
            printf("buscando");
            cazeEditorCuentas(colo, archivo);
            break;
        case 5:
            gotoxy(supx, supy+5);
            printf("GPS activado"); // la parte mas divertida del juego
            coordenadas();
            system("cls");
            dibujarLogoNoAnimado(10,2);
            dibujarNombre(4,30);
            limpiarVentana(29, 15, 52, 25);
            dibujarVentanaNoAnimada(0,0,141,46);
            dibujarVentanaNoAnimada(28,14,53,26);
            dibujarVentanaNoAnimada(90,31,117,43);
            if (caze==1)
                dibujoMenuIngresoEditor(96,33);
            else
                dibujoMenuJugar(96,33, 1);
            dibujoMenuAdmin( supx, supy);
            break;
        case 7:
            gotoxy(supx, supy+7);
            printf("Formateando");
            formatearCuentas(archivo, 90, 3);
            break;
        case 9:
            gotoxy(supx, supy+9);
            printf("salir de control");
            break;
        }
        limpiarVentana(29, 15, 52, 25);
        dibujoMenuAdmin( supx, supy);
    }
    while(resp!=9);
    limpiarVentana(84,2,135,30);
    reDibujaLogo(28, 14);

}

void verCuentas(char archivo[])
{
    int supx=86,supy=3;
    dibujarVentanas(84,2,135,30);
    limpiarVentana(85,3,134,29);
    mostrarContenidoArchivo (archivo, supx,supy);
    getch();
    limpiarVentana(84,2,135,30);
}

int mostrarUsuario (stUsuario usuario, int supx, int supy)
{
    gotoxy(supx,supy);
    printf("        id:%i",usuario.id);
    gotoxy(supx,supy+1);
    printf("    Cuenta:%s",usuario.nombre);
    gotoxy(supx,supy+2);
    printf("Contrase%ca:%s",164,usuario.contrasena);

    return supy+3;
}

void mostrarContenidoArchivo (char archivo[], int supx, int supy)
{
    int i=0, cantidad=0;
    stUsuario auxUsuario;
    FILE *archi=NULL;

    archi=fopen(archivo,"rb"); /// modo lectura

    if(archi != NULL)
    {
        cantidad=cuentaRegistroArchivo(archivo, sizeof(stUsuario));
        gotoxy(supx+33,supy);
        printf("Cuentas:%i",cantidad);
        while(fread(&auxUsuario,sizeof(stUsuario),1,archi)>0)
        {
            gotoxy(supx,supy);
            printf("-------Cuenta %i------",i+1);
            supy=mostrarUsuario(auxUsuario, supx, supy+1);
            if(supy==27)
            {
                supx=supx+25;
                supy=supy-22;
            }
            i++;
        }
        cerrarArchivo(archi);
    }
}

void formatearCuentas(char archivo[], int supx, int supy)
{
    FILE * archi;
    archi=fopen(archivo,"wb");   /// abre y formatea.
    if (archi != NULL)
    {
        gotoxy(supx,supy);
        printf("Todas las cuentas fueron Borradas");
    }
    cerrarArchivo(archi);
}

///===============Case Modificar===============

void cazeEditorCuentas(int colo, char archivo[])
{
    int supx=95,supy=4, resp;
    char cuenta[50]="";
    stUsuario usuario;
    dibujarVentanas(84,2,135,30);
    limpiarVentana(85,3,134,29);
    do
    {
        dibujoMenuEditorCuentas(supx, supy);
        resp=controlMenu(93,4,3, colo); // me muevo por el case
        switch(resp)
        {
        case 1:  //por nombre
            limpiarCampo(supx,supy+1,cuenta);
            gotoxy(supx, supy+1);
            hidecursor(1);
            fflush(stdin);
            gets(cuenta);
            hidecursor(0);
            break;
        case 3:
            gotoxy(supx, supy+3);
            usuario=buscarCuenta(archivo, cuenta);
            if (usuario.id>-1)
            {
                printf("se encontro usuario: id.%i",usuario.id);
                limpiarCampo(supx,supy+1,cuenta);
                cazeModificarCuenta(colo, archivo, usuario);
            }
            else
            {
                printf("No encontrado");
                limpiarCampo(supx,supy+1,cuenta);
            }
            break;
        case 5:
            gotoxy(supx, supy+7);
            printf("saliendo de Gestor");
            Sleep(300);
            break;
        }
    }
    while(resp!=5);
    limpiarVentana(84,2,135,30);
}

void cazeModificarCuenta(int colo, char archivo[], stUsuario usuario)
{
    int supx=95,supy=19, resp, cuentacamb, passcamb, cambio;
    char cuenta[50]="", pass[50]="";
    do
    {
        dibujoMenuModificarCuenta(supx, supy);
        limpiarVentana(95,11,133,14);
        mostrarCuentaExpecifica(archivo, usuario, supx, supy);
        resp=controlMenu(93,19,4, colo); // me muevo por el case
        switch(resp)
        {
        case 1:  //cambiar usuario
            limpiarCampo(supx,supy+1,cuenta);
            gotoxy(supx, supy+1);
            hidecursor(1);
            fflush(stdin);
            gets(cuenta);
            hidecursor(0);
            cuentacamb=strlen(cuenta);
            break;
        case 3:  //cambiar pass
            limpiarCampo(supx,supy+3,pass);
            gotoxy(supx, supy+3);
            hidecursor(1);
            fflush(stdin);
            gets(pass);
            hidecursor(0);
            passcamb=strlen(pass);
            break;
        case 5: //modificar
            if(cuentacamb>0 && passcamb>0)
            {
                cambio=3;
                gotoxy(supx, supy+5);
                printf("Modificando");
                Sleep(1500);
                gotoxy(supx, supy+5);
                printf("           ");
                modificarRegistroExpecifico(archivo, usuario, cuenta, pass, cambio);
            }
            else if (cuentacamb>0)
            {
                cambio=1;
                gotoxy(supx, supy+5);
                printf("Modificando");
                Sleep(1500);
                gotoxy(supx, supy+5);
                printf("           ");
                modificarRegistroExpecifico(archivo, usuario, cuenta, pass, cambio);
            }
            else if(passcamb>0)
            {
                cambio=2;
                gotoxy(supx, supy+5);
                printf("Modificando");
                Sleep(1500);
                gotoxy(supx, supy+5);
                printf("           ");
                modificarRegistroExpecifico(archivo, usuario, cuenta, pass, cambio);
            }
            else
            {
                cambio=0;
                printf("No hay cambios");
                Sleep(1500);
                gotoxy(supx, supy+5);
                printf("              ");
            }
            limpiarCampo(supx,supy+1,cuenta);
            limpiarCampo(supx,supy+3,pass);
            gotoxy(supx, supy+5);
            printf("Modificado");
            mostrarCuentaExpecifica(archivo, usuario, supx, supy);
            break;
        case 7:
            gotoxy(supx, supy+7);
            printf("saliendo de Modificar");
            Sleep(300);
            break;
        }
    }
    while(resp!=7);
    limpiarVentana(85,3,134,29);
}

void mostrarCuentaExpecifica(char archivo[], stUsuario usuario, int supx, int supy)
{
    stUsuario auxUsuario;

    FILE * archi=NULL;

    archi=fopen(archivo,"rb");

    if (archi!=NULL)
    {
        fseek(archi,sizeof(stUsuario)*(usuario.id-1), SEEK_SET);
        fread(&auxUsuario,sizeof(stUsuario),1,archi);
        mostrarUsuario(auxUsuario,supx,supy-8);
        cerrarArchivo(archi);
    }
}

void modificarRegistroExpecifico(char archivo[], stUsuario usuario, char nombre[], char pass[], int cambio)
{
    stUsuario auxUsuario;
    FILE * archi=NULL;

    archi=fopen(archivo,"r+b");

    if (archi!=NULL)
    {

        fseek(archi, sizeof(stUsuario)*(usuario.id-1), SEEK_SET);
        fread(&auxUsuario, sizeof(stUsuario),1,archi);
        auxUsuario=usuario;

        if (cambio==3)
        {
            strcpy(auxUsuario.nombre, nombre);
            strcpy(auxUsuario.contrasena, pass);
        }
        else if(cambio==1)
        {
            strcpy(auxUsuario.nombre, nombre);
        }
        else
        {
            strcpy(auxUsuario.contrasena, pass);
        }
        fseek(archi, sizeof(stUsuario)*(usuario.id-1), SEEK_SET);
        fwrite (&auxUsuario, sizeof (stUsuario), 1, archi);
    }
    cerrarArchivo(archi);
}



///===============Case Editor Ejercitos===============

void cazeEditorEjercitos(int colo, char archivo[], stUsuario usuario)
{

    int supx=95,supy=4, resp;
    stUnidad limite[10];
    cargarLimites(limite);

    dibujarVentanas(84,2,135,30);
    limpiarVentana(85,3,134,29);

    do
    {
        dibujoMenuEditorEjercito(supx, supy);
        resp=controlMenu(93,4,4, colo); // me muevo por el case

        switch(resp)
        {
        case 1:  //por nombre
            gotoxy(supx, supy+1);
            printf("al Cuartel");
            Sleep(500);
            limpiarVentana(85,3,134,29);
            crearTipo (limite,usuario.ejercito, 5, 95, 4);
            reCargaArchivo( archivo, usuario, usuario.id);
            break;
        case 3:


            if(usuario.ejercito[0].id==0)
            {
                gotoxy(supx, supy+3);
                printf("Alistando tropas");
                Sleep(2000);
                limpiarVentana(85,3,134,29);
                mostrarArregloUnidad(usuario.ejercito, 86, 3);
                limpiarVentana(85,3,134,29);
            }
            else
            {
                gotoxy(supx, supy+3);
                printf("Las tropas no estan listas");
                Sleep(2000);
                gotoxy(supx, supy+3);
                printf("                           ");
            }
            break;
        case 5:
            gotoxy(supx, supy+5);
            printf("A las barracas");
            cazeModificarUnidad(colo, usuario.ejercito);
            reCargaArchivo( archivo, usuario, usuario.id);
            break;
        case 7:
            gotoxy(supx, supy+7);
            printf("saliendo del Cuartel");
            Sleep(300);
            break;
        }
    }
    while(resp!=7);
    limpiarVentana(84,2,135,30);
}

int crearTipo (stUnidad limite[], stUnidad ejercito[], int dimension, int supx, int supy)
{
    int tipolimite, tipo, correcto, validos=6, i=0;


    limpiarVentana(85,3,134,29);

    do
    {
        gotoxy(supx,supy+2);
        limpiarCampoInt(supx,supy+2,tipo);
        gotoxy(supx,supy);
        printf("ingrese tipo de Unidad");
        gotoxy(supx,supy+1);
        printf("1.Heroe 2.Tanque 3.Soldado 4.Para salir");
        gotoxy(supx,supy+2);
        hidecursor(1);
        scanf("%i",&tipo);
        hidecursor(0);

        switch(tipo)
        {
        case 1:

            correcto=validarTipo(ejercito, validos, tipo);
            break;
        case 2:

            correcto=validarTipo(ejercito, validos, tipo);
            break;
        case 3:

            correcto=validarTipo(ejercito, validos, tipo);
            break;
        case 4:
            gotoxy(supx,supy+2);
            printf("Eres un maldito desertor");
            break;
        default:
            gotoxy(supx,supy+2);
            printf("Valor invalido");
            Sleep(2000);
            gotoxy(supx,supy+2);
            printf("                ");
            break;
        }


        if(correcto==1)
        {
            ejercito[i].id=i;
            ejercito[i].tipo=1;
            tipolimite=1;
            cargarAtributos(limite, ejercito, validos, supx, supy+4, tipolimite, i);
            i++;
        }
        else if(correcto==2)
        {
            ejercito[i].id=i;
            ejercito[i].tipo=2;
            tipolimite=2;
            cargarAtributos(limite, ejercito, validos, supx, supy+4, tipolimite, i);
            i++;
        }

        else if(correcto==3)
        {
            ejercito[i].id=i;
            ejercito[i].tipo=3;
            tipolimite=3;
            cargarAtributos(limite, ejercito, validos, supx, supy+4, tipolimite, i);

            i++;
        }
        else
        {
            gotoxy(supx,supy+2);
            limpiarCampoInt(supx,supy+2,tipo);
            gotoxy(supx,supy+2);
            printf("No puedes agregar mas de ese tipo");
            Sleep(2000);
            gotoxy(supx,supy+2);
            printf("                                 ");
        }

    }
    while(i<validos && tipo!=4);
    limpiarVentana(85,3,134,29);
    return validos;
}


int buscarTipo(stUnidad ejercito[], int validos, int tipo)
{
    int i=0, encontrado=0;

    if(tipo==1)
    {
        while(i<validos && encontrado<1)
        {
            if(tipo==ejercito[i].tipo)
                encontrado++;
            i++;
        }
    }
    else if (tipo==2)
    {
        while(i<validos && encontrado<2)
        {
            if(tipo==ejercito[i].tipo)
                encontrado++;
            i++;
        }
    }
    return encontrado;
}

int validarTipo(stUnidad ejercito[], int validos,int tipo)
{
    int cantidad,limite,correcto;

    if(tipo==1)
    {
        limite=1;
        cantidad=buscarTipo(ejercito, validos, tipo);
        if(cantidad<limite)
        {
            correcto=1;
        }
        else
        {
            correcto=0;
        }

    }
    else if(tipo==2)
    {
        limite=2;
        cantidad=buscarTipo(ejercito, validos, tipo);
        if(cantidad<limite)
        {
            correcto=2;
        }
        else
        {
            correcto=0;
        }

    }
    else if(tipo==3)
    {
        correcto=3;
    }

    return correcto;
}

void cargarLimites(stUnidad limite[])
{

    limite[1].tipo=1;
    limite[1].estado=115;
    limite[1].vida=15;
    limite[1].armadura=10;
    limite[1].dmg=10;
    limite[1].rango=40;
    limite[1].mp=50;

    limite[2].tipo=2;
    limite[2].estado=145;
    limite[2].vida=20;
    limite[2].armadura=10;
    limite[2].dmg=15;
    limite[2].rango=35;
    limite[2].mp=45;

    limite[3].tipo=3;
    limite[3].estado=105;
    limite[3].vida=10;
    limite[3].armadura=10;
    limite[3].dmg=5;
    limite[3].rango=25;
    limite[3].mp=60;

}

void cargarAtributos(stUnidad limite[], stUnidad ejercito[],int validos, int supx, int supy, int limitipo, int i)
{
    stUnidad recluta;       //no puede haber estadisticas menores a uno
    recluta.armadura=1;
    recluta.vida=1;
    recluta.dmg=1;
    recluta.rango=1;
    recluta.mp=1;

    int lsalud=limite[limitipo].vida, larmadura=limite[limitipo].armadura, ldmg=limite[limitipo].dmg, lrango=limite[limitipo].rango, lmp=limite[limitipo].mp; // limite de stats posibles
    unsigned int salud, armadura, dmg, rango, mp;
    int puntos=limite[limitipo].estado;
    char nombre[30];
    char inValid[20]="Valores no Validos";
    recluta.id=i;
    recluta.tipo=limitipo;

    gotoxy(supx,supy);
    printf("Ingrese nombre:");
    gotoxy(supx,supy+1);
    hidecursor(1);
    fflush(stdin);
    gets(nombre);
    hidecursor(0);
    Sleep(300);
    limpiarCampo(supx,supy+1,nombre);
    strcpy(recluta.nombre, nombre);
    limpiarVentana(85,6,134,29);

    do
    {
        mostrarUnidad(recluta,supx,supy+5);
        gotoxy(supx,supy);
        printf("puntos por gastar: %i",puntos);
        gotoxy(supx,supy+1);
        printf("Ingrese salud, limite %i",lsalud);
        gotoxy(supx,supy+2);
        hidecursor(1);
        scanf("%i",&salud);
        if(salud>0)
            salud--;
        Sleep(300);
        hidecursor(0);
        limpiarCampoInt(supx,supy+2,salud);
        if(salud>lsalud || salud>puntos)
        {
            gotoxy(supx,supy+2);
            printf("%s",inValid);
            Sleep(600);
            limpiarCampoInt(supx,supy+2,salud);
        }
    }
    while(salud>lsalud || salud>puntos);

    recluta.vida=1+salud;
    puntos=puntos-salud;
    limpiarVentana(85,6,134,29);

    do
    {
        mostrarUnidad(recluta,supx,supy+5);
        gotoxy(supx,supy);
        printf("puntos por gastar: %i",puntos);
        gotoxy(supx,supy+1);
        printf("Ingrese armadura, limite %i",larmadura);
        gotoxy(supx,supy+2);
        hidecursor(1);
        scanf("%i",&armadura);
        if(armadura>0)
            armadura--;
        hidecursor(0);
        Sleep(300);
        limpiarCampoInt(supx,supy+2,armadura);
        if(armadura>larmadura || armadura>puntos)
        {
            gotoxy(supx,supy+2);
            printf("%s",inValid);
            Sleep(600);
            limpiarCampo(supx,supy+2,inValid);
        }
    }
    while(armadura>larmadura || armadura>puntos);

    recluta.armadura=1+armadura;
    puntos=puntos-armadura;
    limpiarVentana(85,6,134,29);

    do
    {
        mostrarUnidad(recluta,supx,supy+5);
        gotoxy(supx,supy);
        printf("puntos por gastar: %i",puntos);
        gotoxy(supx,supy+1);
        printf("Ingrese da%co, limite %i",164,ldmg);
        gotoxy(supx,supy+2);
        hidecursor(1);
        scanf("%i",&dmg);
        if(dmg>0)
            dmg--;
        hidecursor(0);
        Sleep(300);
        limpiarCampoInt(supx,supy+2,dmg);
        if(dmg>ldmg || dmg>puntos)
        {
            gotoxy(supx,supy+2);
            printf("%s",inValid);
            Sleep(600);
            limpiarCampo(supx,supy+2,inValid);
        }
    }
    while (dmg>ldmg || dmg>puntos);

    recluta.dmg=1+dmg;
    puntos=puntos-dmg;
    limpiarVentana(85,6,134,29);


    do
    {
        mostrarUnidad(recluta,supx,supy+5);
        gotoxy(supx,supy);
        printf("puntos por gastar: %i",puntos);
        gotoxy(supx,supy+1);
        printf("Ingrese rango, limite %i",lrango);
        gotoxy(supx,supy+2);
        hidecursor(1);
        scanf("%i",&rango);
        if(rango>0)
            rango--;
        Sleep(300);
        hidecursor(0);
        limpiarCampoInt(supx,supy+2,rango);
        if(rango>lrango || rango>puntos)
        {
            gotoxy(supx,supy+2);
            printf("%s",inValid);
            limpiarCampo(supx,supy+2,inValid);
        }
    }
    while(rango>lrango || rango>puntos);

    recluta.rango=1+rango;
    puntos=puntos-rango;
    limpiarVentana(85,6,134,29);


    do
    {
        mostrarUnidad(recluta,supx,supy+5);
        gotoxy(supx,supy);
        printf("puntos por gastar: %i",puntos);
        gotoxy(supx,supy+1);
        printf("Ingrese movilidad, limite %i",lmp);
        gotoxy(supx,supy+2);
        hidecursor(1);
        scanf("%i",&mp);
        if(mp>0)
            mp--;
        hidecursor(0);
        Sleep(300);
        limpiarCampoInt(supx,supy+2,rango);
        if(mp>lmp || mp>puntos)
        {
            gotoxy(supx,supy+2);
            printf("%s",inValid);
            Sleep(600);
            limpiarCampo(supx,supy+2,inValid);
        }
    }
    while(mp>lmp || mp>puntos);
    recluta.mp=1+mp;
    puntos=puntos-mp;
    limpiarVentana(85,6,134,29);

    limpiarVentana(85,6,134,29);
    recluta.armadura=-1;
    recluta.vida=-1;
    recluta.dmg=-1;
    recluta.rango=-1;
    recluta.mp=-1;


    ejercito[i]=recluta;
}

void mostrarUnidad(stUnidad recluta,int supx,int supy)
{
    gotoxy(supx,supy);
    printf("       id:%i",recluta.id+1);
    if(recluta.tipo==1)
    {
        gotoxy(supx,supy+1);
        printf("     Tipo:Heroe");
    }
    else if(recluta.tipo==2)
    {
        gotoxy(supx,supy+1);
        printf("     Tipo:Tanque");
    }
    else
    {
        gotoxy(supx,supy+1);
        printf("     Tipo:Soldado");
    }
    gotoxy(supx,supy+2);
    printf("   Nombre:%s",recluta.nombre);
    gotoxy(supx,supy+3);
    printf("    Salud:%i",recluta.vida);
    gotoxy(supx,supy+4);
    printf(" Armadura:%i",recluta.armadura);
    gotoxy(supx,supy+5);
    printf("     Dano:%i",recluta.dmg);
    gotoxy(supx,supy+6);
    printf("    Rango:%i",recluta.rango);
    gotoxy(supx,supy+7);
    printf("Movilidad:%i",recluta.mp);
}

void mostrarArregloUnidad(stUnidad ejercito[], int supx,int supy)
{
    int i;

    limpiarVentana(85,3,134,29);
    for(i=0; i<6; i++)
    {
        if(ejercito[i].mp!=0)
        {
            mostrarUnidad(ejercito[i], supx,supy);
            supy=supy+9;
        }
        if(supy==30)
        {
            supx=supx+25;
            supy=supy-27;
        }
    }
    getch();
    limpiarVentana(85,3,134,29);
}

///===============Case Modificar Unidad===============

void cazeModificarUnidad(int colo, stUnidad ejercito[])
{
    int supx=95,supy=4, resp;           ///con este case apruebo strucs, archivos, etc QUE LOCURA.
    int id;
    stUnidad limite[10];
    cargarLimites(limite);
    dibujarVentanas(84,2,135,30);
    limpiarVentana(85,3,134,29);

    do
    {
        dibujoMenuModificarEjercito(supx, supy);
        resp=controlMenu(93,4,3, colo); // me muevo por el case
        switch(resp)
        {
        case 1:  //por id
            limpiarCampoInt(supx,supy+1,id);
            gotoxy(supx, supy+1);
            hidecursor(1);
            scanf("%i",&id);
            hidecursor(0);
            break;
        case 3:
            id=id-1;
            gotoxy(supx, supy+3);
            id=buscarUnidad(ejercito, id);
            if (id>-1)
            {
                printf("se encontro unidad: id.%i",ejercito->id+1);
                limpiarCampoInt(supx,supy+1,id);
                mostrarUnidad(ejercito[id], supx,supy+10);
                gotoxy(supx, supy+19);
                printf("presione una tecla para continuar");
                getch();
                modificarUnTipo(limite,ejercito,95,4,ejercito[id]);
            }
            else
            {
                printf("ID No encontrada");
                limpiarCampoInt(supx,supy+1,id);
            }
            break;
        case 5:
            gotoxy(supx, supy+7);
            printf("saliendo de Gestor");
            Sleep(500);
            gotoxy(supx, supy+7);
            printf("                   ");
            break;
        }
    }
    while(resp!=5);
}

///Buscar Unidad

int buscarUnidad(stUnidad ejercito[], int id)
{
    int i=0, encontrado=-1;

    while(i<6 && encontrado==-1)
    {
        if(id==ejercito[i].id)
            encontrado=i;
        i++;
    }
    return encontrado;
}

void modificarUnTipo (stUnidad limite[], stUnidad ejercito[], int supx, int supy,stUnidad soldadin)
{
    int tipolimite, tipo, correcto, validos=6, i;

    limpiarVentana(85,3,134,12);

    i=soldadin.id;
    gotoxy(supx,supy+2);
    limpiarCampoInt(supx,supy+2,tipo);
    gotoxy(supx,supy);
    printf("ingrese tipo de Unidad");
    gotoxy(supx,supy+1);
    printf("1.Heroe 2.Tanque 3.Soldado 4.salir");
    gotoxy(supx,supy+2);
    hidecursor(1);
    scanf("%i",&tipo);
    hidecursor(0);

    switch(tipo)
    {
    case 1:
        if(soldadin.tipo==1)
            ejercito[i].tipo=3;
        correcto=validarTipo(ejercito, validos, tipo);
        break;
    case 2:
        if(soldadin.tipo==2)
            ejercito[i].tipo=3;
        correcto=validarTipo(ejercito, validos, tipo);
        break;
    case 3:

        correcto=validarTipo(ejercito, validos, tipo);
        break;
    case 4:
        gotoxy(supx,supy+2);
        printf("Eres un maldito desertor");
        correcto=4;
        break;
    default:
        gotoxy(supx,supy+2);
        printf("Valor invalido");
        Sleep(2000);
        gotoxy(supx,supy+2);
        printf("                ");
        break;
    }


    if(correcto==1)
    {
        soldadin.tipo=1;
        tipolimite=1;
        cargarAtributos(limite, ejercito, validos, supx, supy+4, tipolimite, i);
        soldadin.estado=1;

    }
    else if(correcto==2)
    {
        soldadin.tipo=2;
        tipolimite=2;
        cargarAtributos(limite, ejercito, validos, supx, supy+4, tipolimite, i);
        soldadin.estado=1;

    }
    else if(correcto==3)
    {
        soldadin.tipo=3;
        tipolimite=3;
        cargarAtributos(limite, ejercito, validos, supx, supy+4, tipolimite, i);
        soldadin.estado=1;

    }
    else if (correcto==4)
    {
        gotoxy(supx,supy+2);
        limpiarCampoInt(supx,supy+2,tipo);
        gotoxy(supx,supy+2);
        printf("Ya vete de aqui");
        Sleep(1000);
    }
    else
    {
        gotoxy(supx,supy+2);
        limpiarCampoInt(supx,supy+2,tipo);
        gotoxy(supx,supy+2);
        printf("No puedes agregar mas de ese tipo");
        Sleep(2000);
        gotoxy(supx,supy+2);
        printf("                                 ");
    }

    limpiarVentana(85,3,134,29);
}

///===============Archivos===============

void reCargaArchivo(char archivo[],stUsuario usuario, int id)
{
    stUsuario auxUsuario;

    FILE * archi;

    archi=fopen(archivo,"r+b");

    if (archi!=NULL)
    {
        fseek(archi, sizeof(stUsuario)*(id-1), SEEK_SET);
        auxUsuario=usuario;
        fwrite (&auxUsuario, sizeof (stUsuario), 1, archi);

        cerrarArchivo(archi);
    }
}

void inicializarArchi()
{
    char archivoUsuarios[30]= {"Usuarios.bin"};

    FILE *archi;
    archi =fopen(archivoUsuarios, "rb");

    if (archi !=NULL) // intenta leer
    {
        cerrarArchivo(archi);
    }
    else
    {

        archi=fopen(archivoUsuarios,"wb");   /// abre y formatea.

        cerrarArchivo(archi);
    }
}







///-------------------------------------------CAPA VISUAL----------------------------------------

void dibujaLinea(int iniciox, int inicioy, int finx, int finy, int col, int caracter,int delay)
{
    int x=iniciox, y=inicioy;
    //toma coordenadas de incio por parametro y se mueve a la pos deseada en cuanlquiera de los dos ejes y direcciones
    //Puede realizar dibujos de "L" o lineas simples del color y tipo deseado al recibir el caracter por param
    ///recibe el delay por parametro para realizar animaciones
    if(x<finx)
    {
        while(x<finx)
        {
            color(col);
            gotoxy(x,y);
            printf("%c",caracter);
            x++;
            Sleep(delay);
        }
    }
    else if (x>finx)
    {
        while(x>finx)
        {
            color(col);
            gotoxy(x,y);
            printf("%c",caracter);
            x--;
            Sleep(delay);
        }

    }
    if(y<finy)
    {
        while(y<finy)
        {
            color(col);
            gotoxy(x,y);
            printf("%c",caracter);
            y++;
            Sleep(delay);
        }
    }
    else if(y>finy)
    {
        while(y>finy)
        {
            color(col);
            gotoxy(x,y);
            printf("%c",caracter);
            y--;
            Sleep(delay);
        }

    }
}

void dibujaCuadro(int iniciox, int inicioy, int finalx, int finaly, int col, int caracter, int delay)
{
    int x=iniciox, y=inicioy;
    //toma coordenadas de incio por parametro y se mueve a la pos deseada en en trayecto diagonal creando un cuadrado
//recibe por parametro el caracter a imprimir, siendo 219 la pared !! no te olvides
    dibujaLinea(x, y,finalx,finaly,col,caracter,delay);
    dibujaLinea(finalx,finaly,x,y,col,caracter,delay);

}


void barraEstado(char estado[30], char estado2[30])
{
    ///ver como hacer para que los caracteres no salgan de los limites dibujados, por ahora hace display de 2 strings en posicion fija
    // problema, no vuelve y pisa lo que ya hay sino que arranca una linea nueva en cada caso
    int x=50, y=43;
    gotoxy(x,y);
    printf("                              ");
    gotoxy(x,y);
    printf("%s",estado);
    gotoxy(x,y+1);
    printf("                              ");
    gotoxy(x,y+1);
    printf("%s",estado2);
    /// tal unidad hizo esto, o no te podes mover etc

}
void dibujaStats(stUnidad M, int posx, int posy)
{
    int i=0, vida=0;
    gotoxy(posx, posy);
    if(M.equipo==1)
    {
        color(1);
        printf("%c",219);
    }
    else
    {
        color(4);
        printf("%c",219);
    }
    color(14);
    vida=M.vida;

    if(M.vida<=0)
    {
        printf("Id %d, %s - MUERTO      ",M.id,M.nombre);
    }
    else if(M.vida<5)
    {
        printf("Id %d, %s - HP 0%d   - A %d - ",M.id,M.nombre,M.vida,M.armadura);


        for(i=0; i<M.vida; i++)
        {
            printf("%c", 176);
        }

    }
    else if(M.vida<10)
    {
        printf("Id %d, %s - HP 0%d - A %d - ",M.id,M.nombre,M.vida,M.armadura);

        for(i=0; i<M.vida; i++)
        {
            printf("%c", 177);
        }

    }
    else if(M.vida<=25)
    {
        printf("Id %d, %s - HP %d - A %d - ",M.id,M.nombre,M.vida,M.armadura);

        for(i=0; i<M.vida; i++)
        {
            printf("%c", 178);
        }



    }
    //printf("vida %d",vida);

    vida=M.vida;
    while(vida<20)
    {
        printf(" ");
        vida++;
    }

}






void dibujaUnidad(int posx, int posy,int tipo, int col)
{

    color(col);
    if (col!=0)
    {


        if (tipo==1)
        {

            gotoxy(posx-1, posy-1);
            printf("%c",145);
            gotoxy(posx, posy-1);
            printf("%c",190);
            gotoxy(posx+1, posy-1);
            printf("%c",145);

            gotoxy(posx-1, posy);
            printf("%c",159);
            gotoxy(posx, posy);
            printf("%c",177);
            gotoxy(posx+1, posy);
            printf("%c",209);

            gotoxy(posx-1, posy+1);
            printf("%c",202);
            gotoxy(posx, posy+1);
            printf("%c",0);
            gotoxy(posx+1, posy+1);
            printf("%c",202);

        }
        else if(tipo==2)
        {
            if(col==2)
            {
                ///dibujo invertido del tanque para equipo 2
                gotoxy(posx-1, posy-1);
                printf("%c",201);
                gotoxy(posx, posy-1);
                printf("%c",205);
                gotoxy(posx+1, posy-1);
                printf("%c",187);

                gotoxy(posx+1, posy);
                printf("%c",204);
                gotoxy(posx, posy);
                printf("%c",148);
                gotoxy(posx-1, posy);
                printf("%c",205);

                gotoxy(posx-1, posy+1);
                printf("%c",200);
                gotoxy(posx, posy+1);
                printf("%c",205);
                gotoxy(posx+1, posy+1);
                printf("%c",188);

            }
            else
            {
                gotoxy(posx-1, posy-1);
                printf("%c",201);
                gotoxy(posx, posy-1);
                printf("%c",205);
                gotoxy(posx+1, posy-1);
                printf("%c",187);

                gotoxy(posx-1, posy);
                printf("%c",204);
                gotoxy(posx, posy);
                printf("%c",148);
                gotoxy(posx+1, posy);
                printf("%c",205);

                gotoxy(posx-1, posy+1);
                printf("%c",200);
                gotoxy(posx, posy+1);
                printf("%c",205);
                gotoxy(posx+1, posy+1);
                printf("%c",188);
            }

        }
        else if(tipo==3)
        {

            gotoxy(posx-1, posy-1);
            printf("%c",0);
            gotoxy(posx, posy-1);
            printf("%c",184);
            gotoxy(posx+1, posy-1);
            printf("%c",0);

            gotoxy(posx-1, posy);
            printf("%c",206);
            gotoxy(posx, posy);
            printf("%c",176);
            gotoxy(posx+1, posy);
            printf("%c",209);

            gotoxy(posx-1, posy+1);
            printf("%c",202);
            gotoxy(posx, posy+1);
            printf("%c",0);
            gotoxy(posx+1, posy+1);
            printf("%c",202);

        }
    }

    else
    {
        gotoxy(posx-1, posy-1);
        printf("%c",219);
        gotoxy(posx, posy-1);
        printf("%c",219);
        gotoxy(posx+1, posy-1);
        printf("%c",219);

        gotoxy(posx-1, posy);
        printf("%c",219);
        gotoxy(posx, posy);
        printf("%c",219);
        gotoxy(posx+1, posy);
        printf("%c",219);

        gotoxy(posx-1, posy+1);
        printf("%c",219);
        gotoxy(posx, posy+1);
        printf("%c",219);
        gotoxy(posx+1, posy+1);
        printf("%c",219);

    }

}


void animMuerteUnidad(int posx, int posy,int tipo)
{
    color(0);
    gotoxy(posx-1, posy-1);
    printf("%c",219);
    gotoxy(posx, posy-1);
    printf("%c",219);
    gotoxy(posx+1, posy-1);
    printf("%c",219);
    gotoxy(posx-1, posy);
    printf("%c",219);
    gotoxy(posx, posy);
    printf("%c",219);
    gotoxy(posx+1, posy);
    printf("%c",219);
    gotoxy(posx-1, posy+1);
    printf("%c",219);
    gotoxy(posx, posy+1);
    printf("%c",219);
    gotoxy(posx+1, posy+1);
    printf("%c",219);

    color(4);
    gotoxy(posx,posy);
    if (tipo==1)
    {
        Sleep(5);
        gotoxy(posx-2, posy-2);
        printf("%c",145);
        gotoxy(posx, posy-2);
        printf("%c",190);
        gotoxy(posx+2, posy-2);
        printf("%c",145);
        Sleep(8);
        gotoxy(posx-2, posy);
        printf("%c",159);
        gotoxy(posx, posy);
        printf("%c",177);
        gotoxy(posx+2, posy);
        printf("%c",209);
        Sleep(10);
        gotoxy(posx-2, posy+2);
        printf("%c",202);
        gotoxy(posx, posy+2);
        printf("%c",0);
        gotoxy(posx+2, posy+2);
        printf("%c",202);
        Sleep(13);
    }
    else if(tipo==2)
    {
        Sleep(5);
        gotoxy(posx-2, posy-2);
        printf("%c",201);
        gotoxy(posx, posy-2);
        printf("%c",205);
        gotoxy(posx+2, posy-2);
        printf("%c",187);
        Sleep(8);
        gotoxy(posx-2, posy);
        printf("%c",204);
        gotoxy(posx, posy);
        printf("%c",148);
        gotoxy(posx+2, posy);
        printf("%c",205);
        Sleep(10);
        gotoxy(posx-2, posy+2);
        printf("%c",200);
        gotoxy(posx, posy+2);
        printf("%c",205);
        gotoxy(posx+2, posy+2);
        printf("%c",188);
        Sleep(13);
    }
    else if(tipo==3)
    {
        Sleep(5);
        gotoxy(posx-2, posy-2);
        printf("%c",0);
        gotoxy(posx, posy-2);
        printf("%c",184);
        gotoxy(posx+2, posy-2);
        printf("%c",0);
        Sleep(8);
        gotoxy(posx-2, posy);
        printf("%c",206);
        gotoxy(posx, posy);
        printf("%c",176);
        gotoxy(posx+2, posy);
        printf("%c",209);
        Sleep(10);
        gotoxy(posx-2, posy+2);
        printf("%c",202);
        gotoxy(posx, posy+2);
        printf("%c",0);
        gotoxy(posx+2, posy+2);
        printf("%c",202);
        Sleep(13);
    }
    Sleep(500);
    color(0);
    gotoxy(posx-2, posy-2);
    printf("%c",219);
    gotoxy(posx, posy-2);
    printf("%c",219);
    gotoxy(posx+2, posy-2);
    printf("%c",219);
    gotoxy(posx-2, posy);
    printf("%c",219);
    gotoxy(posx, posy);
    printf("%c",219);
    gotoxy(posx+2, posy);
    printf("%c",219);
    gotoxy(posx-2, posy+2);
    printf("%c",219);
    gotoxy(posx, posy+2);
    printf("%c",219);
    gotoxy(posx+2, posy+2);
    printf("%c",219);




}















void animAtaque(int posx, int posy,int finx, int finy, int equipo)
{
    color(5);
    int x=posx,y=posy;

    if(equipo==1)
    {
        x=x+2;
    }
    else
    {
        x=x-2;
    }
    gotoxy(x,y);
    printf("%c",157);
    Sleep(50);
    color(0);


    if(x<finx || y<finy)
    {
        while(x<finx || y<finy)
        {

            color(4);

            if(x<finx)
            {

                gotoxy(x,y);
                color(0);
                printf("%c",126);
                x++;
            }
            if(y<finy)
            {
                gotoxy(x,y);
                color(0);
                printf("%c",126);
                y++;
            }
            gotoxy(x,y);
            color(4);
            printf("%c",126);
            Sleep(4);
        }
    }
    else if(x>finx || y>finy)
    {
        while(x>finx || y>finy)
        {
            Sleep(25);
            if(x>finx)
            {
                gotoxy(x,y);
                color(0);
                printf("%c",126);
                x--;
            }
            if(y>finy)
            {
                gotoxy(x,y);
                color(0);
                printf("%c",126);
                y--;
            }
            gotoxy(x,y);
            color(4);
            printf("%c",126);
            Sleep(4);
        }

    }
    gotoxy(x,y);
    printf(" "); // asi no quedan balas perdidas
}



void reemplazaUnidad(int posx, int posy,int finx, int finy,int tipo, int col)
{
    int x=posx,y=posy;
    if(x<finx || y<finy)
    {
        while(x<finx || y<finy)
        {

            if(x<finx)
            {
                gotoxy(x,y);
                dibujaUnidad(x,y,tipo,0);
                x++;
            }
            if(y<finy)
            {
                gotoxy(x,y);
                dibujaUnidad(x,y,tipo,0);
                y++;
            }
            dibujaUnidad(x,y,tipo,col);
            Sleep(15);
        }

    }
    else if(x>finx || y>finy)
    {
        if(x>finx)
        {
            gotoxy(x,y);
            dibujaUnidad(x,y,tipo,0);
            x--;
        }
        if(y>finy)
        {
            gotoxy(x,y);
            dibujaUnidad(x,y,tipo,0);
            y--;
        }
        dibujaUnidad(x,y,tipo,col);
        Sleep(15);
    }
}

void dibujaDinamico(stUnidad Equipo1[],stUnidad Equipo2[], int Tablero[filas][columnas])
{
    ///dinamico o bum

    int i=0,flag=0, y2=35,posx1=10,posy1=15/*posx2=80,posy2=10*/;

    for(int aux=0; aux<6 ; aux++)
    {
        dibujaStats(Equipo1[aux], 7, y2);
        dibujaStats(Equipo2[aux], 72, y2);
        y2++;
        /*
           Equipo1[aux].posx=posx1;
           Equipo1[aux].posy=posy1;

           Equipo2[aux].posx=posx2;
           Equipo2[aux].posy=posy2;


           posy1=posy1+5;
           posy2=posy2+5;

         posx1=posx1+5;
        posx2=posx2-5;
        */
    }

//reemplazar valores estaticos por parametro dinamico
//romper en subfunciones
    flag=condicionVivos(Equipo1);
    if(flag!=-1)
    {
        for(i=0; i<6; i++)
        {
            flag=VerificaVivo(i,Equipo1);
            if(flag==1)
            {
                gotoxy(posx1,posy1);
                dibujaUnidad(Equipo1[i].posx,Equipo1[i].posy,Equipo1[i].tipo,1);/// el valor al final es el color de la unidad, determinado por el equipo
                entidadUnidad(Equipo1[i].posx,Equipo1[i].posy,Tablero,1);
            }
            else
            {
                dibujaUnidad(Equipo1[i].posx,Equipo1[i].posy,Equipo1[i].tipo,0);
                entidadUnidad(Equipo1[i].posx,Equipo1[i].posy,Tablero,0);
            }

        }
    }




    flag=condicionVivos(Equipo2);
    if(flag!=-1)
    {
        for(i=0; i<6; i++)
        {
            flag=VerificaVivo(i,Equipo2);
            if(flag==1)
            {
                gotoxy(posx1,posy1);
                dibujaUnidad(Equipo2[i].posx,Equipo2[i].posy,Equipo2[i].tipo,2);
                entidadUnidad(Equipo2[i].posx,Equipo2[i].posy,Tablero,1);
            }
            else
            {
                dibujaUnidad(Equipo2[i].posx,Equipo2[i].posy,Equipo2[i].tipo,0);
                entidadUnidad(Equipo2[i].posx,Equipo2[i].posy,Tablero,0);
            }
        }
    }

}



///--------------------------------------------MALLA DE COLISIONES/FISICA-------------------------------------------

void dibujaLineaFisica(int tablero [columnas][filas],int iniciox, int inicioy, int finx, int finy)
{
    int x=iniciox, y=inicioy;
//las columnas son los valores de x y las filas los valores de y, se puede usar en ambas direcciones simplemente invirtiendo los param de entrada
// el valor de "1" va a ser tomado internamente como una pared
    if(x<finx)
    {
        while(x<finx)
        {

            gotoxy(x,y);
            tablero[x][y]=1;
            //printf("%i",tablero[x][y]);
            x++;
        }
    }
    else if(x>finx)
    {
        while(x>finx)
        {
            gotoxy(x,y);
            tablero[x][y]=1;
            //printf("%i",tablero[x][y]); ///solo para testeo y recibir confirmacion visual
            x--;
        }
    }
    if(y<finy)
    {
        while(y<finy)
        {

            gotoxy(x,y);
            tablero[x][y]=1;
            // printf("%i",tablero[x][y]);
            y++;
        }
    }
    else if(y>finy)
    {
        while(y>finy)
        {
            gotoxy(x,y);
            tablero[x][y]=1;
            // printf("%i",tablero[x][y]);
            y--;
        }
    }
}

void dibujaCuadroFisico(int tablero [columnas][filas],int iniciox, int inicioy, int finx, int finy)
{
    //toma coordenadas de incio por parametro y se mueve a la pos deseada en en trayecto diagonal creando un cuadrado(pedorramente)
    int x=iniciox, y=inicioy;


    dibujaLineaFisica(tablero,x, y,finx,finy);
    dibujaLineaFisica(tablero,finx, finy,x,y);

}

void inicializaCuadroFisico(int tablero [columnas][filas]) ///por ahi se puede reemplazar directamente inicializando en el main en 0
{
    int f=0, c=0;
    //rellena el mapa con dato null para no encontrar basura

    while(f<filas-16) ///crotada, ver como embellecer
    {
        tablero[c][f]=00;
        //printf("%i",tablero[c][f]);

        while(c<columnas)
        {
            tablero[c][f]=00;
            //printf("%i",tablero[c][f]);
            c++;
        }
        c=0;
        f++;
    }
}

void creaTablero(int tablero[filas][columnas])
{

    hidecursor(1);
    inicializaCuadroFisico(tablero); //funcion que setea a null todos los valores dentro de la matriz de trabajo
    dibujaCuadroFisico(tablero,0,0,140,30); //crea los muros internos asignandoles valor de "1", proceso paralelizado por la capa grafica
    dibujaLineaFisica(tablero,0,29,140,29);


    dibujaCuadro(0,0,140,45,4,178,0); //stage principal
    dibujaLinea(1,29,140,29,4,223,0); // horizontal separa tablero de stats
    dibujaLinea(65,29,65,43,4,186,0); //vertical abajo

    dibujaCuadro(49,42,82,45,6,177,0); //barra estado

    dibujaCuadro(4,34,60,41,5,177,0); //equipo 1
    dibujaCuadro(20,30,40,32,5,176,0);
    gotoxy(21,31);
    printf("      EQUIPO 1");

    dibujaCuadro(68,34,126,41,7,177,0);
    dibujaCuadro(84,30,106,32,7,176,0);
    gotoxy(85,31);
    printf("      EQUIPO 2");

    ///para crear objetos va con ese parametrizaje, la parte fisica tiene que ser 1/3 menor que la visual



///elige color 1azul 2verde 3celeste 4rojo 5violeta 6amarillo 7blanco 8gris 9turqueza  (+48 le tenes que agregar kevin)
    ///objetos en el mapa, tambien se pueden dibujar partes de dif color
    dibujaCuadroFisico(tablero,100,5,105,8);
    dibujaCuadro(101,6,106,9,5,178,1);

    dibujaCuadroFisico(tablero,115,19,117,27);
    dibujaCuadro(116,20,118,28,8,178,1);

    dibujaCuadroFisico(tablero,49,19,51,18);
    dibujaCuadro(50,20,52,17,3,219,1);
}

///--------------------------------------------MOVIMIENTO DE UNIDADES / FISICO Y VISUAL ---------------------------------------------

void entidadUnidad(int posx, int posy, int tablero[columnas][filas], int valor)
{

///el valor int tomado por paramtro permite que la funcion sea usada para borrar unidades del mapa (reiniciando la posicion a 0)
    gotoxy(posx,posy);
    tablero[posx][posy]=valor;
    //printf("%i",tablero[posx][posy]);

}



int validaMovimiento(int tablero[columnas][filas],int posx, int posy, int destinox,int destinoy)
{
    int flag=1;

    if(posx<destinox)
    {
        if(tablero[posx+3][posy]==1 || tablero[posx+3][posy+1]==1 || tablero[posx+3][posy+2]==1 || tablero[posx+3][posy-1]==1 || tablero[posx+3][posy-2]==1)
        {
            flag=-1;
        }
    }
    else if(posx>destinox)
    {
        if(tablero[posx-3][posy]==1 || tablero[posx-3][posy+1]==1 || tablero[posx-3][posy+2]==1 || tablero[posx-3][posy-1]==1 || tablero[posx-3][posy-2]==1)
        {
            flag=-1;
        }
    }

    if(posy<destinoy)
    {
        if(tablero[posx][posy+3]==1 || tablero[posx+1][posy+3]==1 || tablero[posx+2][posy+3]==1 || tablero[posx-1][posy+3]==1 || tablero[posx-2][posy+3]==1)
        {

            flag=-1;
        }
    }
    else if(posy>destinoy)
    {
        if(tablero[posx][posy-3]==1 || tablero[posx+1][posy-3]==1 || tablero[posx+2][posy-3]==1 || tablero[posx-1][posy-3]==1 || tablero[posx-2][posy-3]==1)
        {
            flag=-1;
        }
    }



    return flag;
}


void mueveUnidad2(int tablero[columnas][filas], int posx, int posy, int destinox, int destinoy,int color)
{
    int valido=0;

    valido=validaMovimiento(tablero,posx,posy,destinox,destinoy);

//retorna 1 si el movimiento es posible o -1 de no serlo, evalua 2 lugares fuera del centro de la unidad dado que son los ocupados por la ent fisica
    if(valido==1)
    {
        gotoxy(posx,posy);
        entidadUnidad(posx,posy,tablero,0);

        gotoxy(destinox,destinoy);
        entidadUnidad(destinox,destinoy,tablero,1);

    }
    else if (valido==-1)
    {

        Beep(750, 800);

    }

}


///Fue necesario modificar la funcion para que reciba todo el arreglo junto con el id de unidad activa, sino no modificaba los datos dentro de la estructura

void avanzaUnidad(int tablero[filas][columnas],stUnidad  Ejercito[],int UnidadActiva)
{
    int posx=0, posy=0, mp=0, posible=1, flag=0;
    char control;
    int col=Ejercito[UnidadActiva].equipo;
    hidecursor(0);
    posx=Ejercito[UnidadActiva].posx;
    posy=Ejercito[UnidadActiva].posy;
    mp=Ejercito[UnidadActiva].mp;
    dibujaUnidad(posx,posy,Ejercito[UnidadActiva].tipo, col);
    barraEstado("  Presione espacio para salir  ", "  del movimiento y atacar  ");
    do
    {
        fflush(stdin);
        control=getch();

        posible=validaMovimiento(tablero,posx,posy,posx,posy);
        if(posible>0 && Ejercito[UnidadActiva].vida >0 )
        {
            switch(control)
            {
            case 72: //abajo
                posible=validaMovimiento(tablero,posx,posy,posx,posy-1);
                if(posible>0)
                {
                    hidecursor(0);
                    mueveUnidad2(tablero,posx,posy,posx,posy-1, col);//fisica
                    reemplazaUnidad(posx,posy,posx,posy-1,Ejercito[UnidadActiva].tipo,col); //grafica ---- unir las dos dentro de mueveunidad2 despues de debuggear

                    mp--;
                    posy=posy-1;

                }
                break;
            case 75://izquierda
                posible=validaMovimiento(tablero,posx,posy,posx-1,posy);

                if(posible>0)
                {
                    hidecursor(0);
                    mueveUnidad2(tablero,posx,posy,posx-1,posy, col);
                    reemplazaUnidad(posx,posy,posx-1,posy,Ejercito[UnidadActiva].tipo,col);
                    mp--;
                    posx=posx-1;
                }
                break;
            case 77://derecha
                posible=validaMovimiento(tablero,posx,posy,posx+1,posy);
                if(posible>0)
                {
                    hidecursor(0);
                    mueveUnidad2(tablero,posx,posy,posx+1,posy, col);
                    reemplazaUnidad(posx,posy,posx+1,posy,Ejercito[UnidadActiva].tipo,col);
                    mp--;
                    posx=posx+1;
                    break;
                }
            case 80://arriba
                posible=validaMovimiento(tablero,posx,posy,posx,posy+1);
                if(posible>0)
                {
                    hidecursor(0);
                    reemplazaUnidad(posx,posy,posx,posy+1,Ejercito[UnidadActiva].tipo,col);
                    mueveUnidad2(tablero,posx,posy,posx,posy+1, col);

                    mp--;
                    posy=posy+1;
                    break;
                }
                Sleep(10);
            case 32:
                flag=1;
                break;

            }
        }
        Ejercito[UnidadActiva].posx=posx;
        Ejercito[UnidadActiva].posy=posy;
        // gotoxy(50,38);
        //printf("Posx=%d \nPosy=%d",Ejercito[UnidadActiva].posx,Ejercito[UnidadActiva].posy);

    }
    while(mp>0 && flag==0);
    Ejercito[UnidadActiva].posx=posx;
    Ejercito[UnidadActiva].posy=posy;
    //gotoxy(50,40);

    //printf("Posx final=%d \nPosy final=%d",Ejercito[UnidadActiva].posx,Ejercito[UnidadActiva].posy);

}


///-----------------------------------------------------------JUEGO---------------------------------------------------------------------

int condicionVivos(stUnidad equipo[]) ///recorre todo el equipo y retorna 1 si hay alguna unidad viva, -1 si estan todos muertos
{
    int i=0, flag=-1;

    while(equipo[i].estado !=1  && i<5)
    {
        i++;
    }
    if(equipo[i].estado ==1)
    {
        flag=1;
    }
    return flag;
}

int retornaVivo(stUnidad equipo[]) ///retorna la posicion en el arreglo de la primer unidad viva que encuentra, para cuando falla el target primario
{
    int i=0, flag=-1;

    while(equipo[i].estado !=1  && i<5)
    {
        i++;
    }
    if(equipo[i].estado ==1)
    {
        flag=i;
    }
    return flag;
}



int VerificaVivo(int id, stUnidad Equipo[]) ///verifica si una unidad individual esta vivo para poder seleccionarla
{
    int flag=-1;
    if(Equipo[id].estado==1)
    {
        flag=1;
    }
    return flag;
}

int checkRango(stUnidad Atacante, stUnidad Defensor)
{
    int flag = -1,llega = 0;
    int posx = abs(Atacante.posx - Defensor.posx);
    int posy = 0;

    if(Atacante.posy > 26 &&  Defensor.posy < 26)
    {
        posy = abs((Atacante.posy/10)- Defensor.posy);

    }
    else if(Defensor.posy > 26 && Atacante.posy < 26)
    {
        posy = abs((Defensor.posy/10)- Atacante.posy);

    }
    else if(Defensor.posy > 26 && Atacante.posy > 26)
    {
        posy = abs((Defensor.posy/10)- (Atacante.posy/10));
    }
    else
    {
        posy = abs(Atacante.posy - Defensor.posy);
    }

    llega = posx + posy;
    if(Atacante.rango >= llega)
    {
        flag = 1;
    }
    return flag;
}

///problema, es necesario pasar la catndaid de enemigos validos para saber cuanto contar
int algunoRango(stUnidad EquipoATK[],stUnidad EquipoDEF[],int idActivo)
{
    int i=0, validos=3,flag=-1, pos=-1;

    while(i<validos && flag!=1)
    {
        flag=checkRango(EquipoATK[idActivo],EquipoDEF[i]);

        i++;
    }
    gotoxy(50,25);
    //   printf("Flag es %d", flag);
    if (flag==1)
    {
        pos=i;
    }
    gotoxy(50,26);
    //   printf("pos es %d", pos);

    if(flag==-1)
    {
        barraEstado("No hay enemigos en alcanze","pasando el turno");
    }
    return pos;
}
///si hay al menos un enemigo en rango retorna su posicion dentro del arreglo. si no retorna -1



void ataca(stUnidad Atacante[], stUnidad Defensor[], int idatk, int iddef)
{
///modificar, seguro no funciona porque no tiene el array entero
    if(checkRango(Atacante[idatk], Defensor[iddef])==1)
    {
        Defensor[iddef].vida -= Atacante[idatk].dmg;
        Beep(150,200);
    }
    if(Defensor[iddef].vida <=0)
    {
        Defensor[iddef].estado =-1;

        animMuerteUnidad(Defensor[iddef].posx,Defensor[iddef].posy,Defensor[iddef].tipo);
        Beep(300,100);
        Sleep(10);
        Beep(400,100);
        Sleep(10);
        Beep(500,100);
        barraEstado("Unidad enemiga muerta","");

    }
}

int SeleccionSwitch(int equipoActivo)
{

    char c=0;
    int x=5;
    int y=35;
    int a=4;
    int respuesta=-1; //este valor es el valor de y al apretar enter
    int opciones=5;

    //printf("%c%c",175,175);

    if(equipoActivo==2)
    {
        x=70;
    }
    gotoxy(x,y);
    hidecursor(0);
    do
    {
        c=getch();
        switch(c)
        {
        case 72:
            if(y>35)    //arriba
            {
                gotoxy(x,y);
                printf("  "); //borro el cursor
                y=y-1;
                gotoxy(x,y);
                printf("%c%c",175,175);
            }
            else
            {
                Beep(100,150);
            }
            break;
        case 80:
            if(y<35+opciones)    //abajo   s
            {
                gotoxy(x,y);
                printf("  ");  //borro el cursor
                y=y+1;
                gotoxy(x,y);
                printf("%c%c",175,175);


            }
            else
            {
                Beep(100,150);
            }
            break;
        case 13:
        {
            gotoxy(x,y);    //enter
            color(2);
            printf("%c%c",175,175);
            Sleep(2);
            gotoxy(x,y);
            color(a);
            printf("%c%c",175,175);
            respuesta=y-35;
            Sleep(10);
            gotoxy(x,y);
            printf("  ");
        }
        }

    }
    while(respuesta==-1);

    return respuesta;

}


int SeleccionarEnemigo(stUnidad EquipoATK[],stUnidad EquipoDEF[], int idactivo )
{

    //maximo unidades unidades por equipo de 6
    int idEnemigo=-1, flag=0,equipo=0;
    char exit=0;
/// if en rango, retornar id enemigo.. pero solo retorna uno, el seleccionado. hay que hacer la seleccion dentro.
//chequear que el id de enemigo sea valido porque este vivo

//id de unidad activa para hacer la comprobacion de rango

    equipo=EquipoDEF[0].equipo;


    do
    {


        do
        {

            idEnemigo=SeleccionSwitch(equipo);
            //printf("Id enemigo %d ",idEnemigo);
//idenemigo es la posicion tal como se ve dentro del juego, que tambien es la posicion de la unidad en el arreglo
            //idEnemigo=0;
            flag=VerificaVivo(idEnemigo,EquipoDEF);
            if(flag!=1)
            {
                barraEstado("Error, la unidad esta muerta", "Seleccione otra unidad");
            }
        }
        while(flag!=1);





// si el flag es 1 la unidad esta viva, ahora a comprobar rango..

        flag=checkRango(EquipoATK[idactivo],EquipoDEF[idEnemigo]);
        if(flag==-1)
        {
            barraEstado("Error,enemigo demasiado lejos", "Presione enter para salir");
        }

        fflush(stdin);
        exit=getch();

    }
    while(flag!=1 && exit!=13);




    if (flag==1)
    {
        return  idEnemigo;
    }
    else
    {
        return -1;
    }

}

///Primero hago un while en el que comparo el rango del atacante con el del primer enemigo en el arreglo, si tiene rango return id del enemigo
//Despues vas iterando y te va devolviendo las ids de los que puede atacar. Estas se guardan en un arreglo de enemigos en rango.

void encuentraRango(stUnidad Atacante, stUnidad equipoDEF [], int ids[])
{

    int qcy =0,i=0,validos =0,flag=0, vivos[6];

    validos = buscaVida(equipoDEF, vivos);

    while( flag <validos )
    {

        qcy = idUnidad(equipoDEF, 6, vivos[flag]);

        if(checkRango(Atacante,equipoDEF[qcy])!=-1)
        {

            ids[i] = checkRango(Atacante, equipoDEF[qcy]);

            i++;
        }

        flag++;

    }
}

int buscaVida(stUnidad equipo[], int pos[])
{
    int i=0, validos =0;

    while(i<6)
    {
        if(equipo[i].vida>0)
        {
            pos[i] = equipo[i].id;
            validos ++;
        }
        i++;
    }

    return validos;
}


///la funcion de turno de unidad tiene.. recibe unidad por parametro, usa avanzaunidad para moverlo
/// ataca unidad que revisa si hay unidades dentro de alcance y el intercambio de datos
//requiere ser previamente seleccionada con el switch de seleccion

void turnoUnidad(int tablero[filas][columnas], stUnidad EquipoATK[],stUnidad EquipoDEF[], int idActivo)
{
    //Se requiere pasar el tablero para hacer las colisiones con avanza unidad
    //equipo atacante y defensor van cambiando al correr los turnos y invierte el parametro
    /// recibe el arreglo de unidad, junto con la posicion de unidad que fue dada cuando se selecciono

    int idEnemigo=-1, colorTurno=0;

    colorTurno=EquipoATK[idActivo].equipo;


    if (colorTurno==1)
    {
        dibujaCuadro(0,0,140,45,colorTurno,178,0);
        colorTurno=2;
    }
    else
    {
        dibujaCuadro(0,0,140,45,colorTurno,178,0);
        colorTurno=1;
    }
    avanzaUnidad(tablero,EquipoATK, idActivo);
    idEnemigo=algunoRango(EquipoATK,EquipoDEF,idActivo);
//printf("idenemigo %d", idEnemigo);
    if (idEnemigo!=-1)
    {

        idEnemigo=SeleccionarEnemigo(EquipoATK,EquipoDEF,idActivo);

//la comprobacion de rango se realiza ya directamente desde el selecciona enemigo, devolviendo si o si un enemigo valido o 0
//falta agrega que seleccione en pantalla la unidad enemiga

        {
            if (idEnemigo!=-1)
                if(checkRango(EquipoATK[idActivo],EquipoDEF[idEnemigo])==1)
                {
                    animAtaque(EquipoATK[idActivo].posx,EquipoATK[idActivo].posy,EquipoDEF[idEnemigo].posx,EquipoDEF[idEnemigo].posy,EquipoATK[idActivo].equipo);
                    ataca(EquipoATK,EquipoDEF,idActivo,idEnemigo);
                    barraEstado("Se ataco exitosamente al enemigo","                       ");


                }
        }
    }
    /*if(EquipoATK[idActivo].equipo==1)
    {
          dibujaDinamico(EquipoATK,EquipoDEF,tablero);
    }else
    {
    dibujaDinamico(EquipoDEF,EquipoATK,tablero);
    }
    */
    fflush(stdin);
}

void juego(int tablero[filas][columnas],stUnidad equipo1[], stUnidad equipo2[])
{
    dibujaDinamico(equipo1,equipo2,tablero);
///hacer pasaje de validos de equipos, para evitar complicaciones recomiendo que los equipos siempre tengan la misma cantidad de unidades
//se puede hacer un if check que si un equipo tiene menos unidades se copie la ultima o algo asi.. o forzarlo en la carga y listo
    barraEstado("Bienvenido al juego!","Empieza el equipo izquierdo");
    int i=0, vivo=-1, flag=0;

    while(condicionVivos(equipo1)==1 && condicionVivos(equipo2)==1 && flag==0)
    {

        dibujaDinamico(equipo1,equipo2,tablero);


        if(VerificaVivo(i,equipo1)==1)
        {
            turnoUnidad(tablero,equipo1,equipo2,i);//dibuja dinamico dentro de turnounidad
            dibujaDinamico(equipo1,equipo2,tablero);

        }
        else if (VerificaVivo(i,equipo1)==-1)
        {
            vivo=retornaVivo(equipo1);
            if(vivo!=-1)
            {

                turnoUnidad(tablero,equipo1,equipo2,vivo);
                dibujaDinamico(equipo1,equipo2,tablero);

            }
        }
        gotoxy(30,30);
        //printf("flag es %d",flag);
        //system("pause");
        if(condicionVivos(equipo2)==-1)
        {
            flag=1;
        }

///se soluciona separando los turnos de los equipos

        if (flag==0)
        {
            if(VerificaVivo(i,equipo2)==1)
            {
                turnoUnidad(tablero,equipo2,equipo1,i);
                dibujaDinamico(equipo1,equipo2,tablero);

            }
            else if (VerificaVivo(i,equipo2)==-1)
            {
                vivo=retornaVivo(equipo2);
                //printf("la unidad %d esta viva",vivo);
                if(vivo!=-1)
                {
                    turnoUnidad(tablero,equipo2,equipo1,vivo);
                    dibujaDinamico(equipo1,equipo2,tablero);
                    gotoxy(0,0);
                }
            }
        }
        i++;
    }






    gotoxy(60,35);
    printf("Se salio del loop principal");
    if(condicionVivos(equipo1)==1 && condicionVivos(equipo2)==-1)
    {
        system("cls");
        dibujaCuadro(35,10,100,30,7,219,1);
        gotoxy(60,15);
        printf("El jugador 1 gano!");
        Sleep(4000);
    }
    if(condicionVivos(equipo1)==-1 && condicionVivos(equipo2)==1)
    {
        system("cls");
        dibujaCuadro(35,10,100,30,7,219,1);
        gotoxy(60,15);
        printf("El jugador 2 gano!");
        Sleep(4000);
    }



}

void creaEquipoUno(stUnidad Equipo1[], stUnidad Equipo2[])
{

    stUnidad emps= {0,"Emps",1,1,20,1,10,15,1,50,15,15,40};
    stUnidad sang= {1,"Sang",1,1,15,1,15,20,1,50,15,12,35};
    stUnidad dread= {2,"Dread",2,1,15,1,20,15,1,50,15,12,35};
    stUnidad preda= {3,"Preda",2,1,15,1,25,20,1,50,15,12,35};
    stUnidad Sm= {4,"SM  ",3,1,12,1,15,25,1,50,15,10,25};
    stUnidad Sm2= {5,"SM2 ",3,1,12,1,10,10,1,50,15,10,25};

    Equipo1[0]=emps;
    Equipo1[1]=sang;
    Equipo1[2]=dread;
    Equipo1[3]=preda;
    Equipo1[4]=Sm;
    Equipo1[5]=Sm2;

}

void creaEquipoDos(stUnidad Equipo1[], stUnidad Equipo2[])
{

    stUnidad horus= {0,"horus",1,2,20,1,85,15,1,50,15,15,40};
    stUnidad prabo= {1,"prabo",1,2,15,1,80,20,1,50,15,12,35};
    stUnidad cdread= {2,"C Dread",2,2,15,1,70,20,1,50,15,12,35};
    stUnidad cpred= {3,"C Preda",2,2,15,1,90,15,1,50,15,12,35};
    stUnidad Cm= {4,"CM   ",3,2,12,1,80,25,1,50,15,10,25};
    stUnidad Cm2= {5,"CM2  ",3,2,12,1,80,10,1,50,15,10,25};

    Equipo2[0]=horus;
    Equipo2[1]=prabo;
    Equipo2[2]=cdread;
    Equipo2[3]=cpred;
    Equipo2[4]=Cm;
    Equipo2[5]=Cm2;
}


///-------------------------------------------FUNCIONES DE SOPORTE VARIAS----------------------------------------------

int idUnidad(stUnidad EjercitoActivo[],int validos, int id)
{
    int pos=0, i=0;
    for(i=0; i<validos; i++)
    {
        if(EjercitoActivo[i].id==id)
        {
            pos=i;
        }
    }
    return pos;
}


