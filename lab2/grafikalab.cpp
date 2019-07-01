#include <Windows.h>
#include <GL/glut.h>
#include <iostream>

using namespace std;
typedef float point3[3];
typedef float point2[2];

#define M_PI 3.14159265358979323846

/*************************************************************************************/

// Funkcja rysuj�ca osie uk�adu wsp�rz�dnych



void Axes(void)
{

	point3  x_min = { -5.0, 0.0, 0.0 };
	point3  x_max = { 5.0, 0.0, 0.0 };
	// pocz�tek i koniec obrazu osi x
	point3 *tab[2] = {  &x_min, &x_max };

	point3  y_min = { 0.0, -5.0, 0.0 };
	point3  y_max = { 0.0,  5.0, 0.0 };
	// pocz�tek i koniec obrazu osi y

	point3  z_min = { 0.0, 0.0, -5.0 };
	point3  z_max = { 0.0, 0.0,  5.0 };
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
	glRotated(30.0, 1.0, 0.0, 0.0);

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
const float N = 100;
point3 *tabXYZ[100][100];
point2 *tab2[100][100];

void Try(void)
{
	float numerU = 0;
	float numerV = 0;
	float distance = 1 / N;
	int inter = 0;

	for (int i = 0; i < N/2; i++)
	{
		for (int j = 0; j < N; j++)
		{

			float u = numerU;
			float v = numerV;
			//cout << "u: " << numerU << "v: " << numerV << endl;
			float rownanieX = (-90 * pow(u, 5) + 255 * pow(u, 4) - 270 * pow(u, 3) + 180 * pow(u, 2) - 45 * (u))*cos(3.14*(v));
			float rownanieY = (160 * pow(u, 4) - 320 * pow(u, 3) + 160 * pow(u, 2));
			float rownanieZ = (-90 * pow(u, 5) + 255 * pow(u, 4) - 270 * pow(u, 3) + 180 * pow(u, 2) - 45 * (u))*sin(3.14*(v));
			point3 ej = { rownanieX, rownanieY, rownanieZ };
			//cout << " numerU: " << numerU << "numerV: " << numerV << "rownania: " <<rownanieX <<"   " <<  rownanieY << "     " << rownanieZ << endl;
			tabXYZ[i][j] = &ej;

			glBegin(GL_POINTS);
			glVertex3fv(*tabXYZ[i][j]);
			glEnd();

			//cout << **tabXYZ[i][j] << endl;

			/*point3  x_min = { -5.0, 0.0, 0.0 };
			point3  x_max = { 5.0, 0.0, 0.0 };
			// pocz�tek i koniec obrazu osi x
			point3 *tab[2] = { &x_min, &x_max };*/
			numerV += distance;
		}
		numerU += distance;
		numerV = 0;
		//cout << " i: "<< i << endl;
	}

	
	//cout << rownanieX << endl << rownanieY << endl << rownanieZ << endl << distance << endl;
}

void RenderScene(void)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Czyszczenie okna aktualnym kolorem czyszcz�cym

	glLoadIdentity();
	// Czyszczenie macierzy bie��cej
	Axes();
	Try();
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



void MyInit(void)
{

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	// Kolor czyszc�cy (wype�nienia okna) ustawiono na czarny

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
	// Inicjalizuje GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	// Ustawienie trybu wy�wietlania
	// GLUT_SINGLE - pojedynczy bufor wy�wietlania
	// GLUT_RGBA - model kolor�w RGB
	glutInitWindowSize(300, 300);


	glutCreateWindow("Drugi program w OpenGL");
	// Utworzenie okna i okre�lenie tre�ci napisu w nag��wku okna


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

	
	system("pause");
	return 0;
}