// ----------------  Definicions matematicas -------------------------- //
#define PI 3.1415926
#define UNIDADE_GRAO_EN_RADIANS 0.017453f

// ----------------  Definicions OBXECTOS -------------------------- //

// Definimos a altura a que se situan os obxectos por encima do chan
#define ALTURA_Y 0

// ----------------  Definicions CAMARA -------------------------- //

// Tipos de camara
#define CAMARA_XERAL 2
#define CAMARA_TERCEIRA_PERSOA 3

// Tipos de movementos da camara
#define XIRO_CAMARA_DEREITA 1
#define XIRO_CAMARA_ESQUERDA 2
#define XIRO_CAMARA_ARRIBA 3
#define XIRO_CAMARA_ABAIXO 4
#define ACERCAR_CAMARA 5
#define AFASTAR_CAMARA 6

// Definimos os planos NEAR e FAR da camara
#define NEAR 0.1f
#define FAR 60.0f

// Definimos a maxima e minima distancia a que se pode alonxar a camara
#define MIN_DIST_CAMARA_XERAL 1.0f
#define MAX_DIST_CAMARA_XERAL 100.0f

// Definimos os incrementos ao acercar e alonxar a camara
#define INCREMENTO_RADIO_CAMARA_XERAL 0.1f

// Definimos os incrementos ao xirar a camara
#define INCREMENTO_XIRO_CAMARA_XERAL UNIDADE_GRAO_EN_RADIANS

// Modos da camara
#define MODO_CAMARA_INDEFINIDO 0
#define MODO_CAMARA_PRIMEIRA_PERSOA 1
#define MODO_CAMARA_VISTA_XERAL 2
#define MODO_CAMARA_TERCEIRA_PERSOA 3

// ----------------  Definicions MOVEMENTOS -------------------------- //
#define VELOCIDADE_BASE_ENEMIGOS 0.2f
#define VELOCIDADE_BASE_PERSONAXE 1.0f

# define INCREMENTO_XIRO_PERSONAXE 3.0f*UNIDADE_GRAO_EN_RADIANS


// ----------------  Definicions TIPOS FIGURAS -------------------------- //
#define FIGURA_EIXOS 0
#define FIGURA_CADRADO 1
#define FIGURA_CUBO 2
#define FIGURA_CARGADA 3

// ----------------  Definicions SUELO -------------------------- //
#define ESCALA_SUELO 2.0f