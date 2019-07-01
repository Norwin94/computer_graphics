#include <Windows.h>
#include <GL/glut.h>
#include <iostream>

using namespace std;
typedef float point3[3];
typedef float point2[2];

int model = 1;
static GLfloat theta[] = { 0.0, 0.0, 0.0 };

const float N = 100;

point3 ***tabXYZ = new point3**[N];
point2 **UV = new point2*[N];



/*************************************************************************************/

// Funkcja rysuj¹ca osie uk³adu wspó³rzêdnych



void Axes(void)
{

	point3  x_min = { -10.0, 0.0, 0.0 };
	point3  x_max = { 10.0, 0.0, 0.0 };
	// pocz¹tek i koniec obrazu osi x

	point3  y_min = { 0.0, -10.0, 0.0 };
	point3  y_max = { 0.0,  10.0, 0.0 };
	// pocz¹tek i koniec obrazu osi y

	point3  z_min = { 0.0, 0.0, -10.0 };
	point3  z_max = { 0.0, 0.0,  10.0 };
	//  pocz¹tek i koniec obrazu osi y
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
   // glRotated(330, 1.0, 0.0, 0.0);
	//glTranslated(0.0, -7.0, 0.0);

}


/*************************************************************************************/

// Funkcja okreœlaj¹ca co ma byæ rysowane (zawsze wywo³ywana gdy trzeba 
// przerysowaæ scenê)
/*Zadaæ liczbê N, która okreœla³a bêdzie na ile przedzia³ów podzielony zostanie bok kwadratu jednostkowego dziedziny parametrycznej.

Zadeklarowaæ tablicê o rozmiarze NxN, która bêdzie s³u¿y³a do zapisywania wspó³rzednych punktów w przestrzeni 3 - D.Ka¿dy element
tablicy zawiera³ bêdzie trzy liczby bêd¹ce wspó³rzêdnymi x, y, z jednego punktu.

Na³o¿yæ na kwadrat jednostkowy dziedziny parametrycznej równomiern¹ siatkê NxN punktów.

Dla ka¿dego punktu u, v na³o¿onej w kroku poprzednim siatki, obliczyæ, przy pomocy podanych wy¿ej rówanañ
wspó³rzêdne x(u, v), y(u, v) i z(u, v) i zapisaæ je w zadeklarowanej w kroku 2 tablicy.

Wyœwietliæ na ekranie elementy tablicy wspó³rzêdnych punktów pos³uguj¹c siê konstrukcj¹ :
*/


void Try()
{



	float numerU = 0;
	float numerV = 0;
	float distance = 1 / N;

	for (int i = 0; i < N; i++)
	{
		tabXYZ[i] = new point3*[N];
		UV[i] = new point2[N];

		for (int j = 0; j < N; j++)
		{

			float u = numerU;
			float v = numerV;
			point2 a = { u,v };
			*UV[i][j] = *a;
			//cout << "u: " << numerU << "v: " << numerV << endl;
			float rownanieX = (-90 * pow(u, 5) + 225 * pow(u, 4) - 270 * pow(u, 3) + 180 * pow(u, 2) - 45 * (u))*cos(3.14*(v));
			float rownanieY = (160 * pow(u, 4) - 320 * pow(u, 3) + 160 * pow(u, 2));
			float rownanieZ = (-90 * pow(u, 5) + 225 * pow(u, 4) - 270 * pow(u, 3) + 180 * pow(u, 2) - 45 * (u))*sin(3.14*(v));
			point3 ej = { rownanieX, rownanieY, rownanieZ };
			//cout << " numerU: " << numerU << "numerV: " << numerV << "rownania: " <<rownanieX <<"   " <<  rownanieY << "     " << rownanieZ << endl;
			tabXYZ[i][j] = &ej;



			//int k = j - 1;
			//int l = i - 1;
			//if (k < 0) k = j;
			//if (l < 0) l = i;
			glBegin(GL_POINTS);

				glVertex3fv(*tabXYZ[i][j]);
			//	glVertex3fv(*tabXYZ[l][k]);

			glEnd();

			//cout << **tabXYZ[i][j] << endl;

			/*point3  x_min = { -5.0, 0.0, 0.0 };
			point3  x_max = { 5.0, 0.0, 0.0 };
			// pocz¹tek i koniec obrazu osi x
			point3 *tab[2] = { &x_min, &x_max };*/
			numerV += distance;
		}
		numerU += distance;
		numerV = 0;
		//cout << " i: "<< i << endl;
	}


	//cout << rownanieX << endl << rownanieY << endl << rownanieZ << endl << distance << endl;
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
	// Czyszczenie okna aktualnym kolorem czyszcz¹cym

	glLoadIdentity();
	// Czyszczenie macierzy bie¿¹cej

	Axes();
	glColor3f(1.0f, 1.0f, 1.0f); // Ustawienie koloru rysowania na bia³y
	glRotatef(theta[0], 1.0, 0.0, 0.0);

	glRotatef(theta[1], 0.0, 1.0, 0.0);

	glRotatef(theta[2], 0.0, 0.0, 1.0);
	glTranslated(0.0, -4.0, 0.0);
	//glutWireTeapot(3.0);
	//glRotatef(theta[0], 1.0, 0.0, 0.0);
	//glRotatef(theta[1], 0.0, 1.0, 0.0);
	//glRotatef(theta[2], 0.0, 0.0, 1.0);	
	Try();
	//Egg();
	// Narysowanie osi przy pomocy funkcji zdefiniowanej wy¿ej
	glColor3f(0.0f, 0.0f, 1.0f); // Ustawienie koloru rysowania na bia³y

								 //glRotated(90.0, 0.0, 1.0, 0.0);  // Obrót o 60 stopni
								 //glRotated(90.0, 0.0, 0.0, 1.0);
								 //glutWireTeapot(3.0); // Narysowanie obrazu czajnika do herbaty

	glFlush();
	// Przekazanie poleceñ rysuj¹cych do wykonania


	glutSwapBuffers();
	//
}


/*************************************************************************************/

// Funkcja ustalaj¹ca stan renderowania

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
	// Kolor czyszc¹cy (wype³nienia okna) ustawiono na czarny

}

/*************************************************************************************/

// Funkcja ma za zadanie utrzymanie sta³ych proporcji rysowanych 
// w przypadku zmiany rozmiarów okna.
// Parametry vertical i horizontal (wysokoœæ i szerokoœæ okna) s¹ 
// przekazywane do funkcji za ka¿dym razem gdy zmieni siê rozmiar okna.



void ChangeSize(GLsizei horizontal, GLsizei vertical)
{

	GLfloat AspectRatio;
	// Deklaracja zmiennej AspectRatio  okreœlaj¹cej proporcjê
	// wymiarów okna 
	if (vertical == 0)  // Zabezpieczenie przed dzieleniem przez 0
		vertical = 1;
	glViewport(0, 0, horizontal, vertical);
	// Ustawienie wielkoœciokna okna widoku (viewport)
	// W tym przypadku od (0,0) do (horizontal, vertical)  
	glMatrixMode(GL_PROJECTION);
	// Prze³¹czenie macierzy bie¿¹cej na macierz projekcji 
	glLoadIdentity();
	// Czyszcznie macierzy bie¿¹cej            
	AspectRatio = (GLfloat)horizontal / (GLfloat)vertical;
	// Wyznaczenie wspó³czynnika  proporcji okna
	// Gdy okno nie jest kwadratem wymagane jest okreœlenie tak zwanej
	// przestrzeni ograniczaj¹cej pozwalaj¹cej zachowaæ w³aœciwe
	// proporcje rysowanego obiektu.
	// Do okreslenia przestrzeni ograniczj¹cej s³u¿y funkcja
	// glOrtho(...)            
	if (horizontal <= vertical)

		glOrtho(-7.5, 7.5, -7.5 / AspectRatio, 7.5 / AspectRatio, 10.0, -10.0);
	else

		glOrtho(-7.5*AspectRatio, 7.5*AspectRatio, -7.5, 7.5, 10.0, -10.0);
	glMatrixMode(GL_MODELVIEW);
	// Prze³¹czenie macierzy bie¿¹cej na macierz widoku modelu                                   

	glLoadIdentity();
	// Czyszcenie macierzy bie¿¹cej
}

/*************************************************************************************/

// G³ówny punkt wejœcia programu. Program dzia³a w trybie konsoli



int main(int argc, char* argv[])

{

	glutInit(&argc, argv);
	glutIdleFunc(spinEgg);
	// Inicjalizuje GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	// Ustawienie trybu wyœwietlania
	// GLUT_SINGLE - pojedynczy bufor wyœwietlania
	// GLUT_RGBA - model kolorów RGB
	glutInitWindowSize(300, 300);


	glutCreateWindow("Jajco");
	// Utworzenie okna i okreœlenie treœci napisu w nag³ówku okna

	//petla();
	glutDisplayFunc(RenderScene);
	// Okreœlenie, ¿e funkcja RenderScene bêdzie funkcj¹ zwrotn¹ (callback)
	// Biblioteka GLUT bêdzie wywo³ywa³a t¹ funkcjê za ka¿dym razem, gdy
	// trzeba bêdzie przerysowaæ okno


	glutReshapeFunc(ChangeSize);
	// Dla aktualnego okna ustala funkcjê zwrotn¹ odpowiedzialn¹ za
	// zmiany rozmiaru okna

	MyInit();
	// Funkcja MyInit (zdefiniowana powy¿ej) wykonuje wszelkie  
	// inicjalizacje konieczneprzed przyst¹pieniem do renderowania

	glEnable(GL_DEPTH_TEST);


	glutMainLoop();
	// Funkcja uruchamia szkielet biblioteki GLUT

	//glutKeyboardFunc(keys);
	//glutIdleFunc(spinEgg);
	system("pause");
	return 0;
}