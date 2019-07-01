/*************************************************************************************/

//  Szkielet programu do tworzenia modelu sceny 3-D z wizualizacj¹ osi  
//  uk³adu wspó³rzêdnych dla rzutowania perspektywicznego

/*************************************************************************************/
#include <Windows.h>
#include <GL/glut.h>
#include <iostream>
#include <cmath>

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

using namespace std;

typedef float point3[3];
typedef float point2[2];

int model = 1;
//static GLfloat theta[] = { 0.0, 0.0, 0.0 };

const float N = 20;

point3 tabXYZ[20][20];
point3 tabVectorNormal[20][20];
point2 UV[20][20];

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
	/*glBegin(GL_LINES);

	glVertex3fv(y_min);
	glVertex3fv(y_max);
	glEnd();
	*/
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
	float distance = 1 / (N - 1) ;

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

			float xU = (-450 * pow(u, 4) + 900 * pow(u, 3) - 810 * pow(u, 2) + 360 * (u)-45)*cos(3.14*(v));
			float xV = 3.14*(90 * pow(u, 5) - 225 * pow(u, 4) + 270 * pow(u, 3) - 180 * pow(u, 2) + 45 * (u))*sin(3.14*(v));
			float yU = 640 * pow(u, 3) - 960 * pow(u, 2) + 320 * (u);
			float yV = 0;
			float zU = (-450 * pow(u, 4) + 900 * pow(u, 3) - 810 * pow(u, 2) + 360 * (u)-45)*sin(3.14*(v));
			float zV = -3.14*(90 * pow(u, 5) - 225 * pow(u, 4) + 270 * pow(u, 3) - 180 * pow(u, 2) + 45 * (u))*cos(3.14*(v));

			float vectorLength = sqrt((pow(xU, 2)) + (pow(xV, 2)) + (pow(yU, 2)) + (pow(yV, 2)) + (pow(zU, 2)) + (pow(zV, 2)));

			xU = xU / vectorLength;
			xV = xV / vectorLength;
			yU = yU / vectorLength;
			yV = yV / vectorLength;
			zU = zU / vectorLength;
			zV = zV / vectorLength;

			GLfloat first = yU * zV - zU * yV;
			GLfloat second = zU * xV - xU * zV;
			GLfloat third = xU * yV - yU * xV;
			point3 vectorNormal = { first,second,third };
			memcpy(tabVectorNormal[i][j], vectorNormal, sizeof(vectorNormal));
			//glColor3f(1.0f, 0.0f, 0.0f);  

			if (i > 0 && j > 0) {
				glBegin(GL_TRIANGLES);
			//	glNormal3fv(tabVectorNormal[i - 1][j - 1]);

				glVertex3fv(tabXYZ[i - 1][j - 1]);
				glTexCoord2f(i-1, j-1);
			//	glNormal3fv(tabVectorNormal[i - 1][j]);
				glVertex3fv(tabXYZ[i - 1][j]);
				glTexCoord2f(i-1,j);
			//	glNormal3fv(tabVectorNormal[i][j]);
				glVertex3fv(tabXYZ[i][j]);
				glTexCoord2f(i,j);
				glEnd();

				glBegin(GL_TRIANGLES);
				//glNormal3fv(tabVectorNormal[i - 1][j - 1]);
				glVertex3fv(tabXYZ[i - 1][j - 1]);
				glTexCoord2f(i-1,j-1);
			//	glNormal3fv(tabVectorNormal[i][j - 1]);
				glVertex3fv(tabXYZ[i][j - 1]);
				glTexCoord2f(i,j-1);
			//	glNormal3fv(tabVectorNormal[i][j]);
				glVertex3fv(tabXYZ[i][j]);
				glTexCoord2f(i,j);
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
	// Ustawienie koloru rysowania na bia³y
	Egg();

	glFlush();
	glutSwapBuffers();


}




GLbyte *LoadTGAImage(const char *FileName, GLint *ImWidth, GLint *ImHeight, GLint *ImComponents, GLenum *ImFormat)
{

	/*************************************************************************************/

	// Struktura dla nag³ówka pliku  TGA



#pragma pack(1)            

	typedef struct
	{
		GLbyte    idlength;
		GLbyte    colormaptype;
		GLbyte    datatypecode;
		unsigned short    colormapstart;
		unsigned short    colormaplength;
		unsigned char     colormapdepth;
		unsigned short    x_orgin;
		unsigned short    y_orgin;
		unsigned short    width;
		unsigned short    height;
		GLbyte    bitsperpixel;
		GLbyte    descriptor;
	}TGAHEADER;

#pragma pack(8)

	FILE *pFile;
	TGAHEADER tgaHeader;
	unsigned long lImageSize;
	short sDepth;
	GLbyte    *pbitsperpixel = NULL;


	/*************************************************************************************/

	// Wartoœci domyœlne zwracane w przypadku b³êdu 

	*ImWidth = 0;
	*ImHeight = 0;
	*ImFormat = GL_BGR_EXT;
	*ImComponents = GL_RGB8;

	pFile = fopen(FileName, "rb");
	if (pFile == NULL)return NULL;


	/*************************************************************************************/
	// Przeczytanie nag³ówka pliku 


	fread(&tgaHeader, sizeof(TGAHEADER), 1, pFile);


	/*************************************************************************************/

	// Odczytanie szerokoœci, wysokoœci i g³êbi obrazu 

	*ImWidth = tgaHeader.width;
	*ImHeight = tgaHeader.height;
	sDepth = tgaHeader.bitsperpixel / 8;


	/*************************************************************************************/
	// Sprawdzenie, czy g³êbia spe³nia za³o¿one warunki (8, 24, lub 32 bity) 

	if (tgaHeader.bitsperpixel != 8 && tgaHeader.bitsperpixel != 24 && tgaHeader.bitsperpixel != 32)
		return NULL;

	/*************************************************************************************/

	// Obliczenie rozmiaru bufora w pamiêci

	lImageSize = tgaHeader.width * tgaHeader.height * sDepth;

	/*************************************************************************************/

	// Alokacja pamiêci dla danych obrazu


	pbitsperpixel = (GLbyte*)malloc(lImageSize * sizeof(GLbyte));

	if (pbitsperpixel == NULL)
		return NULL;

	if (fread(pbitsperpixel, lImageSize, 1, pFile) != 1)
	{
		free(pbitsperpixel);
		return NULL;
	}
	/*************************************************************************************/

	// Ustawienie formatu OpenGL
	switch (sDepth)
	{
	case 3:
		*ImFormat = GL_BGR_EXT;
		*ImComponents = GL_RGB8;
		break;

	case 4:
		*ImFormat = GL_BGRA_EXT;
		*ImComponents = GL_RGBA8;
		break;

	case 1:
		*ImFormat = GL_LUMINANCE;
		*ImComponents = GL_LUMINANCE8;
		break;

	};

	fclose(pFile);

	return pbitsperpixel;

}

/*************************************************************************************/

/*************************************************************************************/
// Funkcja ustalaj¹ca stan renderowania
/*************************************************************************************/

void MyInit(void)
{
	/*************************************************************************************/
	// Zmienne dla obrazu tekstury
	GLbyte *pBytes;
	GLint ImWidth, ImHeight, ImComponents;
	GLenum ImFormat;

	// ..................................       
	//       Pozosta³a czêœæ funkcji MyInit()

	// ..................................

	/*************************************************************************************/

	// Teksturowanie bêdzie prowadzone tyko po jednej stronie œciany 
	//glEnable(GL_CULL_FACE);
	/*************************************************************************************/

	//  Przeczytanie obrazu tekstury z pliku o nazwie tekstura.tga

	pBytes = LoadTGAImage("t_1024.tga", &ImWidth, &ImHeight, &ImComponents, &ImFormat);
	/*************************************************************************************/

	// Zdefiniowanie tekstury 2-D 
	glTexImage2D(GL_TEXTURE_2D, 0, ImComponents, ImWidth, ImHeight, 0, ImFormat, GL_UNSIGNED_BYTE, pBytes);
	/*************************************************************************************/

	// Zwolnienie pamiêci
	free(pBytes);
	/*************************************************************************************/

	// W³¹czenie mechanizmu teksturowania
	glEnable(GL_TEXTURE_2D);

	/*************************************************************************************/

	// Ustalenie trybu teksturowania
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	/*************************************************************************************/

	// Okreœlenie sposobu nak³adania tekstur
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	/*************************************************************************************/

	//  Definicja materia³u z jakiego zrobiony jest czajnik 
	//  i definicja Ÿród³a œwiat³a

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


	GLfloat light_position[] = { 0.0, 0.0, 10.0, 1.0 };
	// po³o¿enie Ÿród³a


	GLfloat light_ambient[] = { 0.1, 0.1, 0.1, 1.0 };
	// sk³adowe intensywnoœci œwiecenia Ÿród³a œwiat³a otoczenia
	// Ia = [Iar,Iag,Iab]

	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	// sk³adowe intensywnoœci œwiecenia Ÿród³a œwiat³a powoduj¹cego
	// odbicie dyfuzyjne Id = [Idr,Idg,Idb]

	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	// sk³adowe intensywnoœci œwiecenia Ÿród³a œwiat³a powoduj¹cego
	// odbicie kierunkowe Is = [Isr,Isg,Isb]

	GLfloat att_constant = { 1.0 };
	// sk³adowa sta³a ds dla modelu zmian oœwietlenia w funkcji 
	// odleg³oœci od Ÿród³a

	GLfloat att_linear = { static_cast<float>(0.05) };
	// sk³adowa liniowa dl dla modelu zmian oœwietlenia w funkcji 
	// odleg³oœci od Ÿród³a

	GLfloat att_quadratic = { static_cast<float>(0.001) };
	// sk³adowa kwadratowa dq dla modelu zmian oœwietlenia w funkcji
	// odleg³oœci od Ÿród³a

	/*************************************************************************************/
	// Ustawienie parametrów materia³u i Ÿród³a œwiat³a

	/*************************************************************************************/
	// Ustawienie patrametrów materia³u


	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);


	/*************************************************************************************/
	// Ustawienie parametrów Ÿród³a

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, att_constant);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, att_linear);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, att_quadratic);


	/*************************************************************************************/
	// Ustawienie opcji systemu oœwietlania sceny 

	glShadeModel(GL_SMOOTH); // w³aczenie ³agodnego cieniowania
	glEnable(GL_LIGHTING);   // w³aczenie systemu oœwietlenia sceny 
	glEnable(GL_LIGHT0);     // w³¹czenie Ÿród³a o numerze 0
	glEnable(GL_DEPTH_TEST); // w³¹czenie mechanizmu z-bufora 

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

/*************************************************************************************/
// Funkcja wczytuje dane obrazu zapisanego w formacie TGA w pliku o nazwie 
// FileName, alokuje pamiêæ i zwraca wskaŸnik (pBits) do bufora w którym 
// umieszczone s¹ dane. 
// Ponadto udostêpnia szerokoœæ (ImWidth), wysokoœæ (ImHeight) obrazu
// tekstury oraz dane opisuj¹ce format obrazu wed³ug specyfikacji OpenGL 
// (ImComponents) i (ImFormat).
// Jest to bardzo uproszczona wersja funkcji wczytuj¹cej dane z pliku TGA.
// Dzia³a tylko dla obrazów wykorzystuj¹cych 8, 24, or 32 bitowy kolor.
// Nie obs³uguje plików w formacie TGA kodowanych z kompresj¹ RLE.
/*************************************************************************************/





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




