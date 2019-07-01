/*************************************************************************************/

//  Szkielet programu do tworzenia modelu sceny 3-D z wizualizacj� osi  
//  uk�adu wsp�rz�dnych dla rzutowania perspektywicznego

/*************************************************************************************/
#include <Windows.h>
#include <GL/glut.h>
#include <iostream>
#include <cmath>

using namespace std;

typedef float point3[3];

static GLfloat azymut = 0;
static GLfloat elewacja = 0;
static GLfloat R = 10;
static GLfloat Vy = 1;

static GLfloat x = R * cos(azymut) * cos(elewacja);
static GLfloat y = R * sin(elewacja);
static GLfloat z = R * sin(azymut) * cos(elewacja);

static GLfloat viewer[] = { x, y, z };

static GLfloat theta = 0.0;   
static GLfloat theta1 = 0.0;
static GLfloat pix2angle;   
static GLfloat angle2rad;    

static GLint status = 0;       
static GLint status1 = 0; 	  
							 

static int x_pos_old = 0;      
static int y_pos_old = 0;       

static int delta_x = 0;       
static int delta_y = 0;

void Axes(void)
{

point3  x_min = { -5.0, 0.0, 0.0 };
point3  x_max = { 5.0, 0.0, 0.0 };


point3  y_min = { 0.0, -5.0, 0.0 };
point3  y_max = { 0.0,  5.0, 0.0 };
point3  z_min = { 0.0, 0.0, -5.0 };
point3  z_max = { 0.0, 0.0,  5.0 };

glColor3f(1.0f, 0.0f, 0.0f);
glBegin(GL_LINES);
glVertex3fv(x_min);
glVertex3fv(x_max);
glEnd();

glColor3f(0.0f, 1.0f, 0.0f);
glBegin(GL_LINES);

glVertex3fv(y_min);
glVertex3fv(y_max);
glEnd();

glColor3f(0.0f, 0.0f, 1.0f);
glBegin(GL_LINES);

glVertex3fv(z_min);
glVertex3fv(z_max);
glEnd();
}


void Mouse(int btn, int state, int x, int y)
{
if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
{
x_pos_old = x; 
y_pos_old = y;
status = 1;
}

else if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
{
status1 = 1;
}

else
{
status = 0;       
status1 = 0;
}
}

void Motion(GLsizei x, GLsizei y)
{
delta_x = x - x_pos_old;    
delta_y = y - y_pos_old;
x_pos_old = x;       
y_pos_old = y;

glutPostRedisplay();    
}


void RenderScene(void)
{
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

glLoadIdentity();

gluLookAt(viewer[0], viewer[1], viewer[2], 0.0, 0.0, 0.0, 0.0, Vy, 0.0);

Axes();

if (status == 1)
{
theta += delta_x * pix2angle;
theta1 += delta_y * pix2angle;
azymut = theta * angle2rad;
elewacja = theta1 * angle2rad;

if (azymut <= 0) azymut += 2 * 3.141592;
if (elewacja <= 0) elewacja += 2 * 3.141592;
if (azymut > 2 * 3.141592) azymut -= 2 * 3.141592;
if (elewacja > 2 * 3.141592) elewacja -= 2 * 3.141592;

if ((elewacja < (1.5*3.141592)) && (elewacja > (0.5*3.141592)))
{
Vy = -1;
}
else Vy = 1;

x = R * cos(azymut) * cos(elewacja);
y = R * sin(elewacja);
z = R * sin(azymut) * cos(elewacja);
viewer[0] = x;
viewer[1] = y;
viewer[2] = z;

}

if (status1 == 1)
{
R += (delta_y*0.1);
if (R >= 20 || R <= 4)
{
R -= (delta_y*0.1);
}
x = R * cos(azymut) * cos(elewacja);
y = R * sin(elewacja);
z = R * sin(azymut) * cos(elewacja);
viewer[0] = x;
viewer[1] = y;
viewer[2] = z;

	}

glColor3f(1.0f, 1.0f, 1.0f);

glutSolidTeapot(3.0);
glFlush();
glutSwapBuffers();


}


void MyInit(void)
{
glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

/*************************************************************************************/

//  Definicja materia�u z jakiego zrobiony jest czajnik 
//  i definicja �r�d�a �wiat�a

/*************************************************************************************/


/*************************************************************************************/
// Definicja materia�u z jakiego zrobiony jest czajnik 

GLfloat mat_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
// wsp�czynniki ka =[kar,kag,kab] dla �wiat�a otoczenia

GLfloat mat_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
// wsp�czynniki kd =[kdr,kdg,kdb] �wiat�a rozproszonego

GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
// wsp�czynniki ks =[ksr,ksg,ksb] dla �wiat�a odbitego                

GLfloat mat_shininess = { 20.0 };
// wsp�czynnik n opisuj�cy po�ysk powierzchni


/*************************************************************************************/
// Definicja �r�d�a �wiat�a


GLfloat light_position[] = { 0.0, 0.0, 10.0, 1.0 };
// po�o�enie �r�d�a


GLfloat light_ambient[] = { 0.1, 0.1, 0.1, 1.0 };
// sk�adowe intensywno�ci �wiecenia �r�d�a �wiat�a otoczenia
// Ia = [Iar,Iag,Iab]

GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
// sk�adowe intensywno�ci �wiecenia �r�d�a �wiat�a powoduj�cego
// odbicie dyfuzyjne Id = [Idr,Idg,Idb]

GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
// sk�adowe intensywno�ci �wiecenia �r�d�a �wiat�a powoduj�cego
// odbicie kierunkowe Is = [Isr,Isg,Isb]

GLfloat att_constant = { 1.0 };
// sk�adowa sta�a ds dla modelu zmian o�wietlenia w funkcji 
// odleg�o�ci od �r�d�a

GLfloat att_linear = { static_cast<float>(0.05) };
// sk�adowa liniowa dl dla modelu zmian o�wietlenia w funkcji 
// odleg�o�ci od �r�d�a

GLfloat att_quadratic = { static_cast<float>(0.001) };
// sk�adowa kwadratowa dq dla modelu zmian o�wietlenia w funkcji
// odleg�o�ci od �r�d�a

/*************************************************************************************/
// Ustawienie parametr�w materia�u i �r�d�a �wiat�a

/*************************************************************************************/
// Ustawienie patrametr�w materia�u


glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);


/*************************************************************************************/
// Ustawienie parametr�w �r�d�a

glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
glLightfv(GL_LIGHT0, GL_POSITION, light_position);

glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, att_constant);
glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, att_linear);
glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, att_quadratic);


/*************************************************************************************/
// Ustawienie opcji systemu o�wietlania sceny 

glShadeModel(GL_SMOOTH); // w�aczenie �agodnego cieniowania
glEnable(GL_LIGHTING);   // w�aczenie systemu o�wietlenia sceny 
glEnable(GL_LIGHT0);     // w��czenie �r�d�a o numerze 0
glEnable(GL_DEPTH_TEST); // w��czenie mechanizmu z-bufora 

						 /*************************************************************************************/

}


void ChangeSize(GLsizei horizontal, GLsizei vertical)
{
pix2angle = 360.0 / (float)horizontal;  
angle2rad = pix2angle * (3.141592 / 180.0);

glMatrixMode(GL_PROJECTION);

glLoadIdentity();

gluPerspective(70, 1.0, 1.0, 30.0);

if (horizontal <= vertical)
glViewport(0, (vertical - horizontal) / 2, 
	horizontal, horizontal);

else
glViewport((horizontal - vertical) / 2, 0, vertical, vertical);

glMatrixMode(GL_MODELVIEW);
glLoadIdentity();

}

int main(int argc, char* argv[])
{
glutInit(&argc, argv);

glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

glutInitWindowSize(300, 300);

glutCreateWindow("Rzutowanie perspektywiczne");

glutMouseFunc(Mouse);
glutMotionFunc(Motion);

glutDisplayFunc(RenderScene);


glutReshapeFunc(ChangeSize);

MyInit();
glEnable(GL_DEPTH_TEST);

glutMainLoop();

system("pause");
return 0;
}