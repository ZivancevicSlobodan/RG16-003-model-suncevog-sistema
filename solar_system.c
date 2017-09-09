#include <stdlib.h>
#include <math.h>
#include<stdio.h>
#include <GL/glut.h>

/* Deklaracije funkcija */

void onDisplay(void);
static void onReshape(int width, int height);
static void onTimer(int value);
void mouse(int button, int state, int x, int y);
void mouseMove(int x, int y);
void keyboard(unsigned char key, int x, int y);
void specialKeys(int key, int xx, int yy);
void drawCircle(float cx, float cy, float r, int num_segments);
void renderBitmapString(float x, float y, float z, void *font,char *string);
void processMenuEvents(int option);
void createMenu();
void drawMoons();


/*Flegovi tajmera*/
static float hours;
static int timerActive;

/*Flegovi za funkcionalnosti sa tastature*/
int showOrbits = 1;
int showMoons = 0;
int showLabels = 1;



/*Globalne promenljive potrebne za kretanje po sceni*/
float angle = 0, angle1 = 0;
float lx = 0, lz = -1, ly = 0;
float x = 0, z = 5, y = 0.0;
float fraction = 0.1;
float deltaAngle = 0;
int xOrigin = -1;
float deltaAngle1 = 0;
int yOrigin = -1;


/*Podrazumevani font*/
void *font = GLUT_BITMAP_TIMES_ROMAN_24;

int main(int argc, char **argv)
{
    /*Inicijalizacija glut-a*/
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(1500, 1000);
    glutCreateWindow("Solar system");

    /*callback funkcije*/
    
    glutDisplayFunc(onDisplay);
    glutReshapeFunc(onReshape);
    glutMouseFunc(mouse);
    glutMotionFunc(mouseMove);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);

    /*padajuci meni desnim klikom misa*/
    createMenu();

    
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();

    return 0;
}

/*Funkcija onReshape sprecava izoblicenje slike pri promeni velicine prozora*/

static void onReshape(int width, int height)
{
    /* Postavlja se viewport. */
    glViewport(0, 0, width, height);

    /* Postavljaju se parametri projekcije. */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (float) width / height, 0.1, 100);
    

    glMatrixMode(GL_MODELVIEW);
}
void onDisplay(void)
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /*ucitavamo jedinicnu matricu i postavljamo kameru*/
    /*parametri kamere su globalne promenljive koje ce se menjati pri kretanju po prozoru*/
    glLoadIdentity();
    gluLookAt(x, y, z, x + lx, y + ly, z + lz, 0, 1, 0);
    glTranslatef(-3.5, 0, 0);
    
    /*Iscrtavamo orbite ukoliko je postavljen fleg za to*/
    if (showOrbits) {
	glColor3f(1, 1, 1);
	drawCircle(0, 0, 1.25, 100);
	drawCircle(0, 0, 1.5, 100);
	drawCircle(0, 0, 1.8, 100);
	drawCircle(0, 0, 2.25, 100);
	drawCircle(0, 0, 3.2, 100);
	drawCircle(0, 0, 4.5, 100);
	drawCircle(0, 0, 5.5, 100);
	drawCircle(0, 0, 6.5, 100);
    }
    
    /* Postavljamo parametre direkcionog svetla i materijala*/
    glEnable(GL_COLOR_MATERIAL);
    GLfloat light_position[] = { 1, 1, 1, 0 };

    /* Ambijentalna boja svetla. */
    GLfloat light_ambient[] = { 0.2, 0.1, 0.1, 1 };

    /* Difuzna boja svetla. */
    GLfloat light_diffuse[] = { 0.7, 0.7, 0.7, 1 };

    /* Spekularna boja svetla. */
    GLfloat light_specular[] = { 0.9, 0.9, 0.9, 1 };

    /* Koeficijenti ambijentalne refleksije materijala. */
    GLfloat ambient_coeffs[] = { 0.1, 0.1, 0.1, 1 };

    /* Koeficijenti difuzne refleksije materijala. */
    GLfloat diffuse_coeffs[] = { 0.0, 0.0, 0.8, 1 };

    /* Koeficijenti spekularne refleksije materijala. */
    GLfloat specular_coeffs[] = { 0.1, 0.1, 0.1, 1 };




    /* Ukljucuje se osvjetljenje i podesavaju parametri svetla. */
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    /* Podesavaju se parametri materijala. */
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs);
    

    
    /*Postavljamo parametre pozicionog svetla koje se nalazi u Suncu*/
    GLfloat light_position1[] = { -1, 0, 0, 1 };
    GLfloat light_ambient1[] = { 0.2, 0.1, 0.1, 1 };

    /* Difuzna boja svetla. */
    GLfloat light_diffuse1[] = { 0.7, 0.7, 0.7, 1 };

    /* Spekularna boja svetla. */
    GLfloat light_specular1[] = { 0.9, 0.9, 0.9, 1 };


    /* Koeficijent glatkosti materijala. */
    GLfloat shininess = 1;

    /* Ukljucuje se osvjetljenje i podesavaju parametri svetla. */
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT1);
    glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
    glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse1);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular1);

  /* Podesavaju se parametri materijala. */
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);

    /*Podesavamo parametre kretanja, vrsimo transformacije i iscrtavamo Sunce i planete*/ 
    /*Funkcijom renderBitmapString ispisujemo ime nebeskog tela*/
    float sun_rotation = 360 * hours / (15 * 24);
    glPushMatrix();
    if (showLabels)
	renderBitmapString(0, 1.1, 0, (void *) font, "Sun");
    glRotatef(sun_rotation, 0, 0, 1);
    glColor3f(1, 1, 0);
    glutSolidSphere(1, 100, 100);
    glPopMatrix();

    /*Merkur*/
    float mercury_revolution = 360 * hours / (88 * 24);
    float mercury_rotation = 360 * hours / (59 * 24);
    glPushMatrix();
    glRotatef(mercury_revolution, 0, 0, 1);
    glTranslatef(1.25, 0, 0);
    if (showLabels)
	renderBitmapString(-0.1f, 0.1f, 0, (void *) font, "Mercury");
    glRotatef(mercury_rotation, 0, 0, 1);
    glColor3f(0.5, 0.5, 0.5);
    glutSolidSphere(0.05, 100, 100);
    glPopMatrix();

    /*Venera*/
    float venus_revolution = 360 * hours / (225 * 24);
    float venus_rotation = 360 * hours / (243 * 24);
    glPushMatrix();
    glRotatef(venus_revolution, 0, 0, 1);
    glTranslatef(1.5, 0, 0);
    if (showLabels)
	renderBitmapString(0, -0.2f, 0, (void *) font, "Venus");
    glRotatef(venus_rotation, 0, 0, 1);
    glColor3f(1, 0.5, 0);
    glutSolidSphere(0.1, 100, 100);
    glPopMatrix();

    /*Zemlja*/
    float earth_revolution = 360 * hours / (365 * 24);
    float earth_rotation = 360 * hours / (1 * 24);
    float moon_revolution = 360 * hours / (28 * 24);
    float moon_rotation = 360 * hours / (28 * 24);
    glPushMatrix();
    glRotatef(earth_revolution, 0, 0, 1);
    glTranslatef(1.8, 0, 0);
    if (showLabels)
	renderBitmapString(0, 0.1f, 0, (void *) font, "Earth");
    glColor3f(0.19, 0.6, 0.8);
    glutSolidSphere(0.1, 100, 100);
    glPushMatrix();
    glRotatef(moon_revolution, 0, 0, 1);
    glTranslatef(0.15, 0, 0);
    /*renderBitmapString(0.1f, 0.1f, 0, (void *)font ,"Moon");*/
    glRotatef(moon_rotation, 0, 0, 1);
    glColor3f(1, 1, 1);
    glutSolidSphere(0.025, 100, 100);
    glPopMatrix();
    glPopMatrix();

    /**Mars*/
    float mars_revolution = 360 * hours / (687 * 24);
    float mars_rotation = 360 * hours / (50 * 24);
    float fobos_revolution = 360 * hours / (7 * 24);
    float fobos_rotation = 360 * hours / (7 * 24);
    float deimos_revolution = 360 * hours / (30 * 24);
    float deimos_rotation = 360 * hours / (7 * 24);
    glPushMatrix();
    glRotatef(mars_revolution, 0, 0, 1);
    glTranslatef(2.25, 0, 0);
    if (showLabels)
	renderBitmapString(0, 0.1f, 0, (void *) font, "Mars");
    glRotatef(mars_rotation, 0, 0, 1);
    glColor3f(1, 0.25, 0);
    glutSolidSphere(0.05, 100, 100);
    glPushMatrix();
    glRotatef(fobos_revolution, 0, 0, 1);
    glTranslatef(0.1, 0, 0);
    //renderBitmapString(0.1f, 0.1f, 0, (void *)font ,"Fobos");
    glRotatef(fobos_rotation, 0, 1, 0);
    glColor3f(1, 1, 1);
    glutSolidSphere(0.02, 100, 100);
    glPopMatrix();
    glPushMatrix();
    glRotatef(deimos_revolution, 0, 0, 1);
    glTranslatef(-0.1, 0, 0);
    // renderBitmapString(0.1f, 0.1f, 0, (void *)font ,"Deimos");
    glRotatef(deimos_rotation, 0, 1, 0);
    glColor3f(1, 1, 1);
    glutSolidSphere(0.02, 100, 100);
    glPopMatrix();
    glPopMatrix();

    /*Jupiter*/
    /*Posto poslednje 4 planete imaju veliki broj satelita koji nisam mogao da predstavim na modelu*/
    /*oni su zamenjeni sa 5 generickih satelita koje iscrtava funkcija drawMoons*/
    float jupiter_revolution = 360 * hours / (12 * 365 * 24);
    float jupiter_rotation = 360 * hours / (25 * 24);
    glPushMatrix();
    glRotatef(jupiter_revolution, 0, 0, 1);
    glTranslatef(3.2, 0, 0);
    if (showLabels)
	renderBitmapString(0.1f, 0.45f, 0, (void *) font, "Jupiter");
    glRotatef(jupiter_rotation, 0, 0, 1);
    glColor3f(0.4, 0.3, 0.05);
    glutSolidSphere(0.4, 100, 100);
    drawMoons();
    glPopMatrix();
    
    /*Saturn*/
    float saturn_revolution = 360 * hours / (365 * 29 * 24);
    float saturn_rotation = 360 * hours / (25 * 24);
    glPushMatrix();
    glRotatef(saturn_revolution, 0, 0, 1);
    glTranslatef(4.5, 0, 0);
    if (showLabels)
	renderBitmapString(0.1f, 0.6f, 0, (void *) font, "Saturn");
    glRotatef(saturn_rotation, 0, 0, 1);
    glColor3f(0.4, 0.4, 0.4);
    GLUquadricObj *disk;
    disk = gluNewQuadric();
    gluDisk(disk, 0.4, 0.5, 100, 100);
    glutSolidSphere(0.3, 100, 100);
    drawMoons();
    glPopMatrix();
    
    /*Uran*/
    float uranus_revolution = 360 * hours / (365 * 84 * 24);
    float uranus_rotation = 360 * hours / (25 * 24);
    glPushMatrix();
    glRotatef(uranus_revolution, 0, 0, 1);
    glTranslatef(5.5, 0, 0);
    if (showLabels)
	renderBitmapString(0.1f, 0.2f, 0, (void *) font, "Uranus");
    glRotatef(uranus_rotation, 0, 0, 1);
    glColor3f(0.45, 0.85, 0.55);
    glutSolidSphere(0.2, 100, 100);
    drawMoons();
    glPopMatrix();
    
    /*Neptun*/
    float neptune_revolution = 360 * hours / (365 * 165 * 24);
    float neptune_rotation = 360 * hours / (25 * 24);
    glPushMatrix();
    glRotatef(neptune_revolution, 0, 0, 1);
    glTranslatef(6.5, 0, 0);
    if (showLabels)
        renderBitmapString(0.1f, 0.2f, 0, (void *) font, "Neptune");
    glRotatef(neptune_rotation, 0, 0, 1);
    glColor3f(0.2, 0.2, 0.8);
    glutSolidSphere(0.2, 100, 100);
    drawMoons();
    glPopMatrix();

    
    glutPostRedisplay();
    glutSwapBuffers();
}


/*funkcija za animaciju koriscenjem tajmera*/
static void onTimer(int value)
{
    /* Azurira se vreme simulacije. */
    hours += 60;

    /* Forsira se ponovno iscrtavanje prozora. */
    glutPostRedisplay();

    /* Po potrebi se ponovo postavlja tajmer. */
    if (timerActive)
        glutTimerFunc(50, onTimer, 0);
}

/*callback funkcija koja registruje kada se pritisne dugme na tastaturi (ASCII karakteri) i izvrsava neku akciju*/
void keyboard(unsigned char key, int x, int y)
{

    /*pritiskom na ESC izlazimo iz programa*/
    switch (key) {
        case 27:
            exit(0);
        /*taster "o" prikazuje tj iskljucuje prikazivanje orbite planeta*/
        case 'o':
        case 'O':
            showOrbits = !showOrbits;
            break;
        /* Pokrece se simulacija. */
        case 'g':
        case 'G':
           
            if (!timerActive) {
                glutTimerFunc(50, onTimer, 0);
                timerActive = 1;
            }
            break;
        /* Pauzira se simulacija. */
        case 's':
        case 'S':
            timerActive = 0;
            break;
        /*Prikazujemo ili iskljucujemo prikazivanje satelita pritiskom na taster 'm'*/    
        case 'm':
        case 'M':
            showMoons = !showMoons;
            break;
         /*Prikazujemo ili iskljucujemo prikazivanje imena nebeskih tela*/    
        case 'l':
        case 'L':
            showLabels = !showLabels;
            break;
    }
}
/*Funkcija radi sa "posebnim", ne-ASCII tasterima na tastaturi (strelice, F1, HOME itd) */
void specialKeys(int key, int xx, int yy)
{
    switch (key) {
        /*strelicom <- pomeramo se u levo po x osi*/
        case GLUT_KEY_LEFT:
            x -= fraction;
            break;
        /*strelicom  -> pomeramo se u desno po x osi*/
        case GLUT_KEY_RIGHT:
            x += fraction;
            break;
        /*strelicom na gore ili dole pomeramo se u pravcu vektora lx, lz za vrednost fraction*/    
        case GLUT_KEY_UP:
            x += lx * fraction;
            z += lz * fraction;
            break;
        case GLUT_KEY_DOWN:
            x -= lx * fraction;
            z -= lz * fraction;
            break;
    }
}
/*callback funkcija koja registruje pritiskanje dugmeta na misu*/
void mouse(int button, int state, int x, int y)
{
    /*kada se stisne levi taster, pamtimo koordinate x i y. kada se taster otpusti azuriramo vrednosti ugloava*/
    /*i postavljamo promenljive za kretanje na -1*/
    if (button == GLUT_LEFT_BUTTON) {
	if (state == GLUT_UP) {
	    angle += deltaAngle;
	    xOrigin = -1;
	    angle1 -= deltaAngle1;
	    yOrigin = -1;

	} else {		
	    xOrigin = x;
	    yOrigin = y;
	}
    }

}

/*callback funkcija koja registruje kretanje misa. Koristi gornju funkciju*/
void mouseMove(int x, int y)
{
    /*u gornjoj funkciji smo se osigurali da je ova vrednost pozitivna samo kada je pritisnut levi taster misa*/
    /*menjamo vektor pravca*/
    if (xOrigin >= 0) {
	deltaAngle = (x - xOrigin) * 0.001f;
	lx = sin(angle + deltaAngle);
	lz = -cos(angle + deltaAngle);
    }
    if (yOrigin >= 0) {
	deltaAngle1 = (y - yOrigin) * 0.001f;
	ly = sin(angle1 - deltaAngle1);
	lz = -cos(angle1 - deltaAngle1);
    }
}

/*Funkcija sluzi za ispisivanje stringa. Koristimo je da ispisemo imena nebeskih tela*/

void renderBitmapString(float x, float y, float z, void *font,char *string)
{
    char *c;
    /*postavljamo boju slova na belu, pravimo raster poziciju od koordinata*/
    /*zatim u petlji ispisujemo jedan po jedan karakter stringa*/
    glColor3f(1, 1, 1);
    glRasterPos3f(x, y, z);
    for (c = string; *c != '\0'; c++) {
	glutBitmapCharacter(font, *c);
    }
}
/*funkcija kojom definisemo nas padajuci meni*/
void processMenuEvents(int option)
{

    /*svakoj opciji moramo dodeliti odredjeni broj, kojim cemo posle povezati funkcionalnost sa tekstom u meniju*/
    switch (option) {
    case 1:
	showOrbits = !showOrbits;
	break;
    case 2:
	showLabels = !showLabels;
	break;
    case 3:
	showMoons = !showMoons;
	break;
    }
}

void createMenu()
{

    /*Pravimo meni i dodajemo u funkcije u njega*/
    glutCreateMenu(processMenuEvents);

    glutAddMenuEntry("Orbits", 1);
    glutAddMenuEntry("Labels", 2);
    glutAddMenuEntry("Moons", 3);

    /*definisemo dugme kojim se meni aktivira*/
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}
/*funkcija za iscrtavanje krugova (orbita)*/
void drawCircle(float cx, float cy, float r, int num_segments)
{
    glBegin(GL_LINE_LOOP);
    for (int ii = 0; ii < num_segments; ii++) {
	float theta =
	    2 * 3.1415926f * (float) ii / (float) num_segments;

	float x = r * cosf(theta);	 
	float y = r * sinf(theta);	

	glVertex2f(x + cx, y + cy);	

    }
    glEnd();
}

void drawMoons()
{
    float revolution = 360 * hours / (30 * 24);
    float rotation = 360 * hours / (7 * 24);
    if (showMoons) {
	glPushMatrix();
	glRotatef(revolution, 0, 0, 1);
	glTranslatef(0.55, 0, 0);
	glRotatef(rotation, 0, 1, 0);
	glColor3f(1, 1, 1);
	glutSolidSphere(0.03, 100, 100);
	glPopMatrix();
	glPushMatrix();
	glRotatef(revolution, 0, 1, 1);
	glTranslatef(-0.52, 0, 0);
	glRotatef(rotation, 0, 1, 0);
	glColor3f(1, 1, 1);
	glutSolidSphere(0.05, 100, 100);
	glPopMatrix();
	glPushMatrix();
	glRotatef(revolution, 1, 0, 1);
	glTranslatef(0, 0.52, 0);
	glRotatef(rotation, 0, 1, 0);
	glColor3f(1, 1, 1);
	glutSolidSphere(0.05, 100, 100);
	glPopMatrix();
	glPushMatrix();
	glRotatef(revolution, 0, 1, 0);
	glTranslatef(0, 0, 0.52);
	glRotatef(rotation, 0, 1, 0);
	glColor3f(1, 1, 1);
	glutSolidSphere(0.05, 100, 100);
	glPopMatrix();
	glPushMatrix();
	glRotatef(revolution, 1, 0, 1);
	glTranslatef(0, -0.52, 0);
	glRotatef(rotation, 0, 1, 0);
	glColor3f(1, 1, 1);
	glutSolidSphere(0.05, 100, 100);
        glPopMatrix();
    }
}
