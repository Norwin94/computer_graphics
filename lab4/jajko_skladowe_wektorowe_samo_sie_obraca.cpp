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
	glRotated(330, 1.0, 0.0, 0.0);
	glTranslated(0.0, 0.0, 0.0);

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
	Egg();
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
	glutIdleFunc(spinEgg);
	system("pause");
	return 0;
}