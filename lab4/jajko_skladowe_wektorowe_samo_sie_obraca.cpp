#include <Windows.h>
#include <GL/glut.h>
#include <iostream>

using namespace std;
typedef float point3[3];
typedef float point2[2];

int model = 1;
static GLfloat theta[] = { 0.0, 0.0, 0.0 };

const float N = 100;

point3 tabXYZ[100][100];
point2 UV[100][100];

point3 tabVectorNormal[100][100];

/*************************************************************************************/

// Funkcja rysuj�ca osie uk�adu wsp�rz�dnych



void Axes(void)
{

	point3  x_min = { -10.0, 0.0, 0.0 };
	point3  x_max = { 10.0, 0.0, 0.0 };
	// pocz�tek i koniec obrazu osi x

	point3  y_min = { 0.0, -10.0, 0.0 };
	point3  y_max = { 0.0,  10.0, 0.0 };
	// pocz�tek i koniec obrazu osi y

	point3  z_min = { 0.0, 0.0, -10.0 };
	point3  z_max = { 0.0, 0.0,  10.0 };
	//  pocz�tek i koniec obrazu osi y
	glColor3f(1.0f, 0.0f, 0.0f);  // kolor rysowania osi - czerwony
	glBegin(GL_LINES); // rysowanie osi x
	glVertex3fv(x_min);
	glVertex3fv(x_max);
	glEnd();

	glColor3f(0.0f, 1.0f, 0.0f);  // kolor rysowania - zielony
	glBegin(GL_LINES);  // rysowanie osi y

	glVertex3fv(y_min);
	glVertex3fv(y_max);
	glEnd();

	glColor3f(0.0f, 0.0f, 1.0f);  // kolor rysowania - niebieski

	glBegin(GL_LINES); // rysowanie osi z
	glVertex3fv(z_min);
	glVertex3fv(z_max);
	glEnd();
	glRotated(330, 1.0, 0.0, 0.0);
	glTranslated(0.0, 0.0, 0.0);

}


/*************************************************************************************/

// Funkcja okre�laj�ca co ma by� rysowane (zawsze wywo�ywana gdy trzeba 
// przerysowa� scen�)
/*Zada� liczb� N, kt�ra okre�la�a b�dzie na ile przedzia��w podzielony zostanie bok kwadratu jednostkowego dziedziny parametrycznej.

Zadeklarowa� tablic� o rozmiarze NxN, kt�ra b�dzie s�u�y�a do zapisywania wsp�rzednych punkt�w w przestrzeni 3 - D.Ka�dy element
tablicy zawiera� b�dzie trzy liczby b�d�ce wsp�rz�dnymi x, y, z jednego punktu.

Na�o�y� na kwadrat jednostkowy dziedziny parametrycznej r�wnomiern� siatk� NxN punkt�w.

Dla ka�dego punktu u, v na�o�onej w kroku poprzednim siatki, obliczy�, przy pomocy podanych wy�ej r�wana�
wsp�rz�dne x(u, v), y(u, v) i z(u, v) i zapisa� je w zadeklarowanej w kroku 2 tablicy.

Wy�wietli� na ekranie elementy tablicy wsp�rz�dnych punkt�w pos�uguj�c si� konstrukcj� :
*/


void Egg()
{
	float numerU = 0;
	float numerV = 0;
	float distance = 1 / N;

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

			GLfloat first = yU * zV - zU * yV;
			GLfloat second = zU * xV - xU * zV;
			GLfloat third = xU * yV - yU * xV;

			float vectorLength = sqrt((pow(first, 2)) + (pow(second, 2)) + (pow(third, 2)));

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

void spinEgg()
{
	theta[0] -= 0.5;
	if (theta[0] > 360.0) theta[0] -= 360.0;

	theta[1] -= 0.5;
	if (theta[1] > 360.0) theta[1] -= 360.0;

	theta[2] -= 0.5;
	if (theta[2] > 360.0) theta[2] -= 360.0;

	glutPostRedisplay();
}


void RenderScene(void)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Czyszczenie okna aktualnym kolorem czyszcz�cym

	glLoadIdentity();
	// Czyszczenie macierzy bie��cej

	Axes();
	glColor3f(1.0f, 1.0f, 1.0f); // Ustawienie koloru rysowania na bia�y
	glRotatef(theta[0], 1.0, 0.0, 0.0);

	glRotatef(theta[1], 0.0, 1.0, 0.0);

	glRotatef(theta[2], 0.0, 0.0, 1.0);
	glTranslated(0.0, -4.0, 0.0);
	//glutWireTeapot(3.0);
	//glRotatef(theta[0], 1.0, 0.0, 0.0);
	//glRotatef(theta[1], 0.0, 1.0, 0.0);
	//glRotatef(theta[2], 0.0, 0.0, 1.0);	
	Egg();
	// Narysowanie osi przy pomocy funkcji zdefiniowanej wy�ej
	glColor3f(0.0f, 0.0f, 1.0f); // Ustawienie koloru rysowania na bia�y

								 //glRotated(90.0, 0.0, 1.0, 0.0);  // Obr�t o 60 stopni
								 //glRotated(90.0, 0.0, 0.0, 1.0);
								 //glutWireTeapot(3.0); // Narysowanie obrazu czajnika do herbaty

	glFlush();
	// Przekazanie polece� rysuj�cych do wykonania


	glutSwapBuffers();
	//
}


/*************************************************************************************/

// Funkcja ustalaj�ca stan renderowania

void keys(unsigned char key, int x, int y)
{
	if (key == 'p') model = 1;
	if (key == 'w') model = 2;
	if (key == 's') model = 3;
	RenderScene();
}


void MyInit(void)
{

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	// Kolor czyszc�cy (wype�nienia okna) ustawiono na czarny
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

/*************************************************************************************/

// Funkcja ma za zadanie utrzymanie sta�ych proporcji rysowanych 
// w przypadku zmiany rozmiar�w okna.
// Parametry vertical i horizontal (wysoko�� i szeroko�� okna) s� 
// przekazywane do funkcji za ka�dym razem gdy zmieni si� rozmiar okna.



void ChangeSize(GLsizei horizontal, GLsizei vertical)
{

	GLfloat AspectRatio;
	// Deklaracja zmiennej AspectRatio  okre�laj�cej proporcj�
	// wymiar�w okna 
	if (vertical == 0)  // Zabezpieczenie przed dzieleniem przez 0
		vertical = 1;
	glViewport(0, 0, horizontal, vertical);
	// Ustawienie wielko�ciokna okna widoku (viewport)
	// W tym przypadku od (0,0) do (horizontal, vertical)  
	glMatrixMode(GL_PROJECTION);
	// Prze��czenie macierzy bie��cej na macierz projekcji 
	glLoadIdentity();
	// Czyszcznie macierzy bie��cej            
	AspectRatio = (GLfloat)horizontal / (GLfloat)vertical;
	// Wyznaczenie wsp�czynnika  proporcji okna
	// Gdy okno nie jest kwadratem wymagane jest okre�lenie tak zwanej
	// przestrzeni ograniczaj�cej pozwalaj�cej zachowa� w�a�ciwe
	// proporcje rysowanego obiektu.
	// Do okreslenia przestrzeni ograniczj�cej s�u�y funkcja
	// glOrtho(...)            
	if (horizontal <= vertical)

		glOrtho(-7.5, 7.5, -7.5 / AspectRatio, 7.5 / AspectRatio, 10.0, -10.0);
	else

		glOrtho(-7.5*AspectRatio, 7.5*AspectRatio, -7.5, 7.5, 10.0, -10.0);
	glMatrixMode(GL_MODELVIEW);
	// Prze��czenie macierzy bie��cej na macierz widoku modelu                                   

	glLoadIdentity();
	// Czyszcenie macierzy bie��cej
}

/*************************************************************************************/

// G��wny punkt wej�cia programu. Program dzia�a w trybie konsoli



int main(int argc, char* argv[])

{

	glutInit(&argc, argv);
	glutIdleFunc(spinEgg);
	// Inicjalizuje GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	// Ustawienie trybu wy�wietlania
	// GLUT_SINGLE - pojedynczy bufor wy�wietlania
	// GLUT_RGBA - model kolor�w RGB
	glutInitWindowSize(300, 300);


	glutCreateWindow("Jajco");
	// Utworzenie okna i okre�lenie tre�ci napisu w nag��wku okna

	//petla();
	glutDisplayFunc(RenderScene);
	// Okre�lenie, �e funkcja RenderScene b�dzie funkcj� zwrotn� (callback)
	// Biblioteka GLUT b�dzie wywo�ywa�a t� funkcj� za ka�dym razem, gdy
	// trzeba b�dzie przerysowa� okno


	glutReshapeFunc(ChangeSize);
	// Dla aktualnego okna ustala funkcj� zwrotn� odpowiedzialn� za
	// zmiany rozmiaru okna

	MyInit();
	// Funkcja MyInit (zdefiniowana powy�ej) wykonuje wszelkie  
	// inicjalizacje konieczneprzed przyst�pieniem do renderowania

	glEnable(GL_DEPTH_TEST);


	glutMainLoop();
	// Funkcja uruchamia szkielet biblioteki GLUT

	//glutKeyboardFunc(keys);
	glutIdleFunc(spinEgg);
	system("pause");
	return 0;
}