// ----------------  Definicions matematicas -------------------------- //
#define PI 3.1415926
#define UNIDADE_GRAO_EN_RADIANS 0.017453f

// ----------------  Definicions OBXECTOS -------------------------- //

// Definimos os id dos elementos decorativos
#define ID_PEDRA1 1
#define ID_PEDRA2 2
#define ID_PEDRA3 3
#define ID_ARBORE1 4
#define ID_ARBORE2 5
#define ID_ARBORE3 6
#define ID_HERBA 7

// ----------------  Definicions CAMARA -------------------------- //

// Tipos de movementos da camara
#define XIRO_CAMARA_DEREITA 1
#define XIRO_CAMARA_ESQUERDA 2
#define XIRO_CAMARA_ARRIBA 3
#define XIRO_CAMARA_ABAIXO 4
#define ACERCAR_CAMARA 5
#define AFASTAR_CAMARA 6

// Definimos os planos NEAR e FAR da camara
#define NEAR 0.1f
#define FAR 400.0f

// Definimos a maxima e minima distancia a que se pode alonxar a camara
#define MIN_DIST_CAMARA_XERAL 1.0f
#define MAX_DIST_CAMARA_XERAL 400.0f

// Definimos os incrementos ao acercar e alonxar a camara
#define INCREMENTO_RADIO_CAMARA_XERAL 0.5f

// Definimos os incrementos ao xirar a camara
#define INCREMENTO_XIRO_CAMARA_XERAL 3.0f*UNIDADE_GRAO_EN_RADIANS

// Modos da camara
#define MODO_CAMARA_PRIMEIRA_PERSOA 1
#define MODO_CAMARA_VISTA_XERAL 2
#define MODO_CAMARA_TERCEIRA_PERSOA 3

// ----------------  Definicions MOVEMENTOS -------------------------- //
#define VELOCIDADE_BASE_ENEMIGOS 1.0f
#define VELOCIDADE_BASE_PERSONAXE 5.0f
#define VELOCIDADE_BASE_BALA 20.0f

# define INCREMENTO_XIRO_PERSONAXE 50.0f*UNIDADE_GRAO_EN_RADIANS


// ----------------  Definicions TIPOS FIGURAS -------------------------- //
#define FIGURA_CADRADO 1
#define FIGURA_CUBO 2
#define FIGURA_CUBO_SKYBOX 3
#define FIGURA_CARGADA 4

// ----------------  Definicions SUELO -------------------------- //
#define ESCALA_SUELO 0.08f


// ----------------  Definicions LUCES -------------------------- //
#define LUZ_DIRECCIONAL 0
#define LUZ_POSICIONAL 1
#define LUZ_FOCAL 2

// ---------------- Definicions MINIMAPA -------------------------- //
#define PROPORCION_MINIMAPA 0.75f

// ---------------- Definicions COLISIONS -------------------------- //
#define DIST_COLISION_BALA 1.5f