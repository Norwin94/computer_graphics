
#include <Windows.h>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>

using namespace std;
typedef float point2[2]; //punkt w przestrzeni do rysowania kwadratow

float width = 200; //szerokosc kwadratu
int level = 3; //stopien podzialu dywanu
float defLevel = 0; //stopien perturbacji


void DrawCarpet(float x, float y, float w)
{
	point2 a = { x, y }; //definiowanie punktów w przestrzeni
	float width = w;
	int i = 0;

	point2 b = { (a[0] + width + ((rand() % 100)*defLevel)), (a[1] + ((rand() % 100)*defLevel)) };
	point2 c = { (a[0] + width + ((rand() % 100)*defLevel)), (a[1] + width + ((rand() % 100)*defLevel)) };
	point2 d = { (a[0] + ((rand() % 100)*defLevel)), (a[1] + width + ((rand() % 100)*defLevel)) };

	//tworzenie obiektu typu Polygon
	glBegin(GL_POLYGON);
	glVertex2fv(a);
	glVertex2fv(b);
	glVertex2fv(c);
	glVertex2fv(d);
	glEnd();

	//nastepny poziom w ktorym bedziemy definiowac obiekty typu Polygon, trzy razy mniejsze
	if (i > 0)
	{
		width = width / 3;
	}
}

void DrawAll(float x, float y, float width, int level)
{
	if (level > 0)
	{
		//funkcja wykorzystujaca rekurencje, poki poziom podzialu dywanu nie zejdzie do 0
		width = width / 3;
		glColor3f(((rand() % 100)*0.01), ((rand() % 100)*0.01), ((rand() % 100)*0.01));
		DrawAll(x, y, width, level - 1);
		glColor3f(((rand() % 100)*0.01), ((rand() % 100)*0.01), ((rand() % 100)*0.01));
		DrawAll(x + width, y, width, level - 1);
		glColor3f(((rand() % 100)*0.01), ((rand() % 100)*0.01), ((rand() % 100)*0.01));
		DrawAll(x + width + width, y, width, level - 1);
		glColor3f(((rand() % 100)*0.01), ((rand() % 100)*0.01), ((rand() % 100)*0.01));
		DrawAll(x, y + width, width, level - 1);

		glColor3f(((rand() % 100)*0.01), ((rand() % 100)*0.01), ((rand() % 100)*0.01));
		DrawAll(x + width + width, y + width, width, level - 1);
		glColor3f(((rand() % 100)*0.01), ((rand() % 100)*0.01), ((rand() % 100)*0.01));
		DrawAll(x, y + width + width, width, level - 1);
		glColor3f(((rand() % 100)*0.01), ((rand() % 100)*0.01), ((rand() % 100)*0.01));
		DrawAll(x + width, y + width + width, width, level - 1);
		glColor3f(((rand() % 100)*0.01), ((rand() % 100)*0.01), ((rand() % 100)*0.01));
		DrawAll(x + width + width, y + width + width, width, level - 1);
	}

	else
	{
		DrawCarpet(x, y, width);
	}

}


void RenderScene(void)

{
	glClear(GL_COLOR_BUFFER_BIT);
	// Czyszczenie okna aktualnym kolorem czyszczącym


	DrawAll(-100, -100, width, level);



	glFlush();
	// Przekazanie poleceń rysujących do wykonania

}

/*************************************************************************************/

// Funkcja ustalająca stan renderowania



void MyInit(void)

{

	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	// Kolor okna wnętrza okna - ustawiono na szary

}

/*************************************************************************************/

// Funkcja służąca do kontroli zachowania proporcji rysowanych obiektów
// niezależnie od rozmiarów okna graficznego



void ChangeSize(GLsizei horizontal, GLsizei vertical)

// Parametry horizontal i vertical (szerokość i wysokość okna) są
// przekazywane do funkcji za każdym razem, gdy zmieni się rozmiar okna

{

	GLfloat AspectRatio;

	// Deklaracja zmiennej AspectRatio określającej proporcję wymiarów okna



	if (vertical == 0)
		// Zabezpieczenie pzred dzieleniem przez 0

		vertical = 1;


	glViewport(0, 0, horizontal, vertical);
	// Ustawienie wielkościokna okna urządzenia (Viewport)
	// W tym przypadku od (0,0) do (horizontal, vertical)


	glMatrixMode(GL_PROJECTION);
	// Określenie układu współrzędnych obserwatora

	glLoadIdentity();
	// Określenie przestrzeni ograniczającej

	AspectRatio = (GLfloat)horizontal / (GLfloat)vertical;
	// Wyznaczenie współczynnika proporcji okna

	// Gdy okno na ekranie nie jest kwadratem wymagane jest 
	// określenie okna obserwatora. 
	// Pozwala to zachować właściwe proporcje rysowanego obiektu
	// Do określenia okna obserwatora służy funkcja glOrtho(...)



	if (horizontal <= vertical)

		glOrtho(-100.0, 100.0, -100.0 / AspectRatio, 100.0 / AspectRatio, 1.0, -1.0);

	else

		glOrtho(-100.0*AspectRatio, 100.0*AspectRatio, -100.0, 100.0, 1.0, -1.0);

	glMatrixMode(GL_MODELVIEW);
	// Określenie układu współrzędnych    

	glLoadIdentity();

}

/*************************************************************************************/

// Główny punkt wejścia programu. Program działa w trybie konsoli



void main(int argc, char* argv[])

{
	do
	{
		cout << "Podaj stopien podzialu dywanu [1; 5] : " << endl;
		cin >> level;
		cout << level << endl;
	} while (level > 5 || level < 1);


	do
	{
		cout << "Podaj poziom perturbacji [0; 0.1] : " << endl;
		cin >> defLevel;
		cout << defLevel << endl;
	} while (defLevel > 0.1);

	glutInit(&argc, argv);
	// Inicjalizuje GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	// Ustawienie trybu wyświetlania
	// GLUT_SINGLE - pojedynczy bufor wyświetlania
	// GLUT_RGBA - model kolorów RGB


	glutCreateWindow("Drugi program w OpenGL");
	// Utworzenie okna i określenie treści napisu w nagłówku okna


	glutDisplayFunc(RenderScene);
	// Określenie, że funkcja RenderScene będzie funkcją zwrotną (callback)
	// Biblioteka GLUT będzie wywoływała tą funkcję za każdym razem, gdy
	// trzeba będzie przerysować okno


	glutReshapeFunc(ChangeSize);
	// Dla aktualnego okna ustala funkcję zwrotną odpowiedzialną za
	// zmiany rozmiaru okna

	MyInit();
	// Funkcja MyInit (zdefiniowana powyżej) wykonuje wszelkie  
	// inicjalizacje konieczneprzed przystąpieniem do renderowania


	glutMainLoop();
	// Funkcja uruchamia szkielet biblioteki GLUT


	system("pause");

}