/*************************************************************************************/

//  Szkielet programu do tworzenia modelu sceny 3-D z wizualizacj¹ osi  
//  uk³adu wspó³rzêdnych dla rzutowania perspektywicznego

/*************************************************************************************/
#include <Windows.h>
#include <GL/glut.h>
#include <iostream>
#include <cmath>

using namespace std;

typedef float point3[3];
typedef float point2[2];

int model = 1;
//static GLfloat theta[] = { 0.0, 0.0, 0.0 };

const float N = 100;

point3 tabXYZ[100][100];
point3 tabVectorNormal[100][100];
point2 UV[100][100];

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



void Egg()
{
	float numerU = 0;
	float numerV = 0;
	float distance = 1 / (N - 2);

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			float u = numerU;
			float v = numerV;
			point2 a = { u,v };

			memcpy(UV[i][j], a, sizeof(a));

			float rownanieX = (-90 * pow(u, 5) + 225 * pow(u, 4) - 270 * pow(u, 3) + 180 * pow(u, 2) - 45 * (u))*cos(3.14*(v));
			float rownanieY = (160 * pow(u, 4) - 320 * pow(u, 3) + 160 * pow(u, 2));
			float rownanieZ = (-90 * pow(u, 5) + 225 * pow(u, 4) - 270 * pow(u, 3) + 180 * pow(u, 2) - 45 * (u))*sin(3.14*(v));
			point3 ej = { rownanieX, rownanieY, rownanieZ };

			memcpy(tabXYZ[i][j], ej, sizeof(ej));

			//if (u >= 0.5) u = -u;
			//if (v >= 0.5) v = -v;
			float xU = (-450 * pow(u, 4) + 900 * pow(u, 3) - 810 * pow(u, 2) + 360 * (u)-45)*cos(3.14*(v));
			float xV = 3.14*(90 * pow(u, 5) - 225 * pow(u, 4) + 270 * pow(u, 3) - 180 * pow(u, 2) + 45 * (u))*sin(3.14*(v));
			float yU = 640 * pow(u, 3) - 960 * pow(u, 2) + 320 * (u);
			float yV = 0;
			float zU = (-450 * pow(u, 4) + 900 * pow(u, 3) - 810 * pow(u, 2) + 360 * (u)-45)*sin(3.14*(v));
			float zV = -3.14*(90 * pow(u, 5) - 225 * pow(u, 4) + 270 * pow(u, 3) - 180 * pow(u, 2) + 45 * (u))*cos(3.14*(v));

			GLfloat first = yU * zV - zU * yV;
			GLfloat second = zU * xV - xU * zV;
			GLfloat third = xU * yV - yU * xV;

			float vectorLength = sqrt((pow(first, 2)) + (pow(second, 2)) + (pow(third, 2)));

			if (u >= 0.5) {
				first *= -1;
				second *= -1;
				third *= -1;
			}

			first = first / vectorLength;
			second = second / vectorLength;
			third = third / vectorLength;


			point3 vectorNormal = { first,second,third };
			memcpy(tabVectorNormal[i][j], vectorNormal, sizeof(vectorNormal));
			//glColor3f(1.0f, 0.0f, 0.0f);  

			if (i > 0 && j > 0) {
				glBegin(GL_TRIANGLES);
				glNormal3fv(tabVectorNormal[i - 1][j - 1]);
				glVertex3fv(tabXYZ[i - 1][j - 1]);

				glNormal3fv(tabVectorNormal[i - 1][j]);
				glVertex3fv(tabXYZ[i - 1][j]);

				glNormal3fv(tabVectorNormal[i][j]);
				glVertex3fv(tabXYZ[i][j]);
				glEnd();

				glBegin(GL_TRIANGLES);
				glNormal3fv(tabVectorNormal[i - 1][j - 1]);
				glVertex3fv(tabXYZ[i - 1][j - 1]);

				glNormal3fv(tabVectorNormal[i][j - 1]);
				glVertex3fv(tabXYZ[i][j - 1]);

				glNormal3fv(tabVectorNormal[i][j]);
				glVertex3fv(tabXYZ[i][j]);
				glEnd();
			}
			numerV += distance;
		}
		numerU += distance;
		numerV = 0;
	}
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

		if ((elewacja < (1.5*3.141592)) && (elewacja >(0.5*3.141592)))
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

	Egg();
	glFlush();
	glutSwapBuffers();


}


void MyInit(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	/*************************************************************************************/

	/*************************************************************************************/

	// Definicja materia³u z jakiego zrobiony jest czajnik 

	GLfloat mat_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
	// wspó³czynniki ka =[kar,kag,kab] dla œwiat³a otoczenia

	GLfloat mat_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	// wspó³czynniki kd =[kdr,kdg,kdb] œwiat³a rozproszonego

	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	// wspó³czynniki ks =[ksr,ksg,ksb] dla œwiat³a odbitego                

	GLfloat mat_shininess = { 20.0 };
	// wspó³czynnik n opisuj¹cy po³ysk powierzchni


	/*************************************************************************************/
	// Definicja Ÿród³a œwiat³a


	GLfloat light_position[] = { -20.0, 0.0, 10.0, 1.0 };
	GLfloat light_position1[] = { 20.0, 0.0, 10.0, 1.0 };
	// po³o¿enie Ÿród³a


	GLfloat light_ambient[] = { 0.1, 0, 0, 1.0 };
	GLfloat light_ambient1[] = { 0, 0, 0.1, 1.0 };

	GLfloat light_diffuse[] = { 1.0, 0, 0, 1.0 };
	GLfloat light_diffuse1[] = { 0, 0, 1.0, 1.0 };
	
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_specular1[] =  { 1.0, 1.0, 1.0, 1.0 };

	GLfloat att_constant = { 1.0 };
	GLfloat att_constant1 = { 1.0 };

	GLfloat att_linear = { static_cast<float>(0.05) };
	GLfloat att_linear1 = { static_cast<float>(0.05) };

	GLfloat att_quadratic = { static_cast<float>(0.001) };
	GLfloat att_quadratic1 = { static_cast<float>(0.001) };


	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);


	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, att_constant);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, att_linear);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, att_quadratic);

	glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular1);
	glLightfv(GL_LIGHT1, GL_POSITION, light_position1);

	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, att_constant1);
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, att_linear1);
	glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, att_quadratic1);


	glShadeModel(GL_SMOOTH); 
	glEnable(GL_LIGHTING);   
	glEnable(GL_LIGHT0);     
	glEnable(GL_LIGHT1);    
	glEnable(GL_DEPTH_TEST); 

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

	glutCreateWindow("Jajeczko oœwietlone ca³kiem");

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


